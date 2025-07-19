#include "stdafx.h"
#include "SceneStage.h"
#include "BackGround.h"
#include "Bird.h"
#include "Block.h"
#include "Pig.h"
#include "rapidcsv.h"
#include "PhysicsBody.h"
#include "ShootStand.h"
#include "GameResult.h"
#include "GamePause.h"
#include "Button.h"

SceneStage::SceneStage()
	: Scene(SceneIds::Stage)
{
}

void SceneStage::Init()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	texIds.push_back("graphics/Angrybirds/RedBird1.png");
	texIds.push_back("graphics/LevelOne.png");
	texIds.push_back("graphics/Sky.png");
	texIds.push_back("graphics/band.png");
	texIds.push_back("graphics/band2.png");
	texIds.push_back("graphics/Angrybirds/ShootStand.png");
	texIds.push_back("graphics/Angrybirds/StandRight.png");
	texIds.push_back("graphics/Angrybirds/StandLeft.png");
	texIds.push_back("graphics/Home.png");
	texIds.push_back("graphics/Replay.png");
	texIds.push_back("graphics/nextstage.png");
	texIds.push_back("graphics/BirdLaugh.png");
	texIds.push_back("graphics/PigLaugh.png");
	texIds.push_back("graphics/pauseButton.png");

	fontIds.push_back("fonts/angrybirds-regular.ttf");

	background = (BackGround*)AddGameObject(new BackGround("graphics/LevelOne.png", "graphics/Sky.png"));

	ground = (PhysicsBody*)AddGameObject(new PhysicsBody(PhysicsBody::Type::Invisible));
	leftWall = (PhysicsBody*)AddGameObject(new PhysicsBody(PhysicsBody::Type::Invisible));
	rightWall = (PhysicsBody*)AddGameObject(new PhysicsBody(PhysicsBody::Type::Invisible));

	shootStand = (ShootStand*)AddGameObject(new ShootStand());

	gameResult = (GameResult*)AddGameObject(new GameResult());
	gamePause = (GamePause*)AddGameObject(new GamePause());

	pauseButton = (Button*)AddGameObject(new Button("graphics/pauseButton.png"));
	auto pauseFunc = [this]() {
		if(!gamePause->GetActive())
		{
			gamePause->SetActive(true);
			FRAMEWORK.SetTimeScale(0.f);
			FRAMEWORK.SetPauseFrame(true);
			isGamePause = true;
		}
		else
		{
			gamePause->SetActive(false);
			FRAMEWORK.SetTimeScale(1.f);
			FRAMEWORK.SetPauseFrame(true);
			isGamePause = false;
		}
	};
	pauseButton->SetButtonFunc(pauseFunc);

	Scene::Init();

	AddGameObject(shootStand->GetLeftPart());
	AddGameObject(shootStand->GetRightPart());
	std::vector<SpriteGo*> band = shootStand->GetBandPart();
	for (auto part : band)
	{
		AddGameObject(part);
	}
}

void SceneStage::Exit()
{
	DeleteObjects();
	Scene::Exit();
}

void SceneStage::Enter()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	LoadInfo("graphics/EditorMaps/MyMap" + std::to_string(2) + ".csv");

	initViewPos.x = shootStand->GetPosition().x;

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter(FRAMEWORK.GetWindowSizeF() * 0.5f);
	worldView.setSize(initViewSize);
	worldView.setCenter(initViewPos);
	currentViewPos = initViewPos;
	currentViewSize = initViewSize;

	ground->SetBoxSize(bounds.width * 2.f, 85.f);
	ground->SetBoxPos(bounds.width * 0.5f, bounds.height);
	ground->SetBoxFactor(0.8f, 0.5f);

	leftWall->SetBoxSize(150.f, 768.f * 0.5f);
	leftWall->SetBoxPos(bounds.width * 2.f + 150.f, bounds.height * 0.5f);
	leftWall->SetBoxFactor(0.8f, 0.5f);
	rightWall->SetBoxSize(150.f, 768.f * 0.5f);
	rightWall->SetBoxPos(bounds.width * -1.f - 150.f, bounds.height * 0.5);
	rightWall->SetBoxFactor(0.8f, 0.5f);

	pauseButton->SetPosition({ 50.f,50.f });

	Scene::Enter();

	tryMax = birdCount;

	//birds[tryCount]->SetBirdEnable();
	ObjectsReset();

	isShoot = false;
	birdReady = true;
	isViewMoving = false;
	isZoomOut = false;
	isZoomIn = false;
	isGameOver = false;
	tryCount = 0;
	timeValue = 0.f;
	viewReset = 0.f;

	birds[tryCount]->SetStartPos();
	shootStand->SetBird(birds[tryCount]);

	backgroundSize = background->GetTotalSize();
	gameResult->SetActive(false);
	gamePause->SetActive(false);
}

void SceneStage::Update(float dt)
{
	ShowGameResult();

	Scene::Update(dt);

	if (isGameOver || isGamePause)
	{
		FRAMEWORK.SetPauseFrame(true);
		return;
	}

	if (tryCount < tryMax)
	{
		if (birds[tryCount]->GetShoot() && birdReady)
		{
			tryCount++;
			birdReady = false;
		}

		if (tryCount > 0 && birds[tryCount-1]->CheckFinishShoot() && !birdReady)
		{
			birds[tryCount]->SetStartPos();
			shootStand->SetBird(birds[tryCount]);
			birdReady = true;
		}
	}

	if(!isZoomOut && !isZoomIn && birdReady)
		ViewReset(dt);

	timeValue += dt;
	bool following = false;
	if (timeValue >= timeStep)
	{
		b2World_Step(FRAMEWORK.GetWorldID(), timeStep, subStepCount);

		CheckObjectsDead();

		CheckPhysicsBodyCollision();

		SetObjectTransform();

		timeValue = 0.f;
		following = true;
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && birdReady)
	{
		mouseStart = (sf::Vector2f)InputMgr::GetMousePosition();
	}
	else if (InputMgr::GetMouseButton(sf::Mouse::Right) && birdReady)
	{
		ViewControl((sf::Vector2f)InputMgr::GetMousePosition());
		viewReset = 0.f;
	}

	ZoomIn(dt);
	ZoomOut(dt);

	

	if(!birdReady && following)
	{
		ViewFollowing(timeStep);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
	{
		//Restart();
		SCENE_MGR.ChangeScene(SceneIds::ChooseStage);
	}
#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		Restart();
	}
#endif
}

void SceneStage::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneStage::LoadInfo(const std::string& filePath)
{		
	rapidcsv::Document doc(filePath);
	objCount = doc.GetCell<int>(0, 0);

	for (int i = 0; i < objCount; i++)
	{
		auto row = doc.GetRow<std::string>(i + 2);
		if (std::find(texIds.begin(), texIds.end(), row[0]) == texIds.end())
			texIds.push_back(row[0]);
		if (row[10] == "Block")
		{
			blocks.push_back((Block*)AddGameObject(new Block(row[0], "Block")));
			blocks[blockCount]->SetBoxPos(std::stof(row[1]), std::stof(row[2]));
			blocks[blockCount]->SetBoxSize(std::stof(row[3]), std::stof(row[4]));
			blocks[blockCount]->SetBoxFactor(std::stof(row[5]), std::stof(row[6]), std::stof(row[7]), std::stof(row[8]));
			blocks[blockCount]->SetHP(std::stoi(row[9]));
			blocks[blockCount++]->Init();
		}
		else if(row[10] == "Pig")
		{
			pigs.push_back((Pig*)AddGameObject(new Pig(row[0], "Pig")));
			pigs[pigCount]->SetInitPos({ std::stof(row[1]), std::stof(row[2]) });
			pigs[pigCount]->SetHP(std::stoi(row[9]));
			pigs[pigCount++]->Init();
		}
		else
		{
			birds.push_back((Bird*)AddGameObject(new Bird(row[0], row[10])));
			birds[birdCount]->SetInitPos({ std::stof(row[1]), 660.f });
			birds[birdCount++]->Init();
		}
	}
}

void SceneStage::CheckPhysicsBodyCollision()
{
	b2ContactHitEvent* hitEvents = b2World_GetContactEvents(FRAMEWORK.GetWorldID()).hitEvents;
	int hitCount = b2World_GetContactEvents(FRAMEWORK.GetWorldID()).hitCount;
	for (int i = 0; i < hitCount; i++)
	{
		b2ContactHitEvent event = hitEvents[i];
		b2ShapeId shapeId1 = event.shapeIdA;
		b2ShapeId shapeId2 = event.shapeIdB;
		float speed = event.approachSpeed;
		for (int j = 0; j < objCount - birdCount; j++)
		{
			if (j <= blockCount -1 && shapeId1.index1 == blocks[j]->GetShapeId().index1)
			{
				blocks[j]->TakeDamage((int)speed * 7);
			}
			else if (j <= blockCount - 1 && shapeId2.index1 == blocks[j]->GetShapeId().index1)
			{
				blocks[j]->TakeDamage((int)speed * 7);
			}
			else if (j > blockCount - 1 && shapeId1.index1 == pigs[j - blockCount]->GetShapeId().index1)
			{
				pigs[j - blockCount]->TakeDamage((int)speed * 7);
			}
			else if (j > blockCount - 1 && shapeId2.index1 == pigs[j - blockCount]->GetShapeId().index1)
			{
				pigs[j - blockCount]->TakeDamage((int)speed * 7);
			}
		}
	}
}

void SceneStage::ViewControl(const sf::Vector2f& mousePos)
{
	currentViewPos.x += (mouseStart - mousePos).x;
	currentViewPos.y += (mouseStart - mousePos).y;
	
	ViewClamp();

	mouseStart = mousePos;
	worldView.setCenter(currentViewPos);
}

void SceneStage::ViewReset(float dt)
{
	if ((initViewPos != currentViewPos || initViewSize != currentViewSize) && birdReady && !birds[tryCount]->GetCharging())
	{
		viewReset += dt;
		if (viewReset >= viewResetMax)
		{
			float xSizeRatio = initViewSize.x / currentViewSize.x;
			float newXratio = xSizeRatio > 1.f ? xSizeRatio - (xSizeRatio - 1.f) * dt : xSizeRatio + (1.f - xSizeRatio) * dt;
			float ySizeRatio = initViewSize.y / currentViewSize.y;
			float newYratio = ySizeRatio > 1.f ? ySizeRatio - (ySizeRatio - 1.f) * dt : ySizeRatio + (1.f - ySizeRatio) * dt;
			currentViewSize.x = initViewSize.x / newXratio;
			currentViewSize.y = initViewSize.y / newYratio;
			if (std::abs(currentViewSize.x - initViewSize.x) <= 1.f) currentViewSize.x = initViewSize.x;
			if (std::abs(currentViewSize.y - initViewSize.y) <= 1.f) currentViewSize.y = initViewSize.y;
			
			currentViewPos += Utils::GetNormal(initViewPos - currentViewPos) * 500.f * dt;
			if (std::abs(currentViewPos.x - initViewPos.x) <= 5.f) currentViewPos.x = initViewPos.x;
			if (std::abs(currentViewPos.y - initViewPos.y) <= 5.f) currentViewPos.y = initViewPos.y;

			ViewClamp();
			worldView.setSize(currentViewSize);
			worldView.setCenter(currentViewPos);
		}
	}
	else
	{
		viewReset = 0.f;
	}
}

void SceneStage::ViewFollowing(float dt)
{
	sf::Vector2f birdPos = birds[tryCount-1]->GetPosition();
	
	if (currentViewPos.y - currentViewSize.y * 0.25f >= birdPos.y)
	{
		float diff = currentViewPos.y - currentViewSize.y * 0.25f - birdPos.y;
		currentViewPos.y -= diff *0.5f;
		currentViewSize.y += diff;
		currentViewSize.x += diff * FRAMEWORK.GetWindowRatio();
	}
	if (currentViewPos.y + currentViewSize.y * 0.45f <= birdPos.y)
	{
		float diff = birdPos.y - (currentViewPos.y + currentViewSize.y * 0.45f);
		currentViewSize.y += diff;
		currentViewSize.x += diff * FRAMEWORK.GetWindowRatio();
	}

	b2Vec2 birdVelo = b2Body_GetLinearVelocity(birds[tryCount-1]->GetBodyId());
	if(std::abs(currentViewPos.x - birdPos.x) <= 1.f) currentViewPos.x = birdPos.x;
	else
	{
		if (currentViewPos.x < birdPos.x && birds[tryCount - 1]->GetFlyingDirection() == 1.f)
		{
			currentViewPos.x = Utils::Lerp(currentViewPos.x, birdPos.x, dt * 3.f);
			if (currentViewPos.x > birdPos.x) currentViewPos.x = birdPos.x;
		}
		else if (currentViewPos.x > birdPos.x && birds[tryCount - 1]->GetFlyingDirection() == -1.f)
		{
			currentViewPos.x = Utils::Lerp( birdPos.x, currentViewPos.x, dt * 3.f);
			if (currentViewPos.x < birdPos.x) currentViewPos.x = birdPos.x;
		}
	}
	ViewClamp();

	worldView.setCenter(currentViewPos);
	worldView.setSize(currentViewSize);
}

void SceneStage::ViewClamp()
{
	float topLimit = backgroundSize.top + currentViewSize.y * 0.5f;
	float bottomLimit = backgroundSize.top + backgroundSize.height - currentViewSize.y * 0.5f;
	float leftLimit = backgroundSize.left + currentViewSize.x * 0.5f;
	float rightLimit = backgroundSize.left + backgroundSize.width - currentViewSize.x * 0.5f;

	currentViewPos.x = Utils::Clamp(currentViewPos.x, leftLimit, rightLimit);
	currentViewPos.y = Utils::Clamp(currentViewPos.y, topLimit, bottomLimit);
}

void SceneStage::Restart()
{
	currentViewPos = initViewPos;
	worldView.setCenter(initViewPos);
	currentViewSize = initViewSize;
	worldView.setSize(initViewSize);
	
	ObjectsReset();
	tryCount = 0;
	birds[tryCount]->SetStartPos();
	shootStand->SetBird(birds[tryCount]);
	birdReady = true;

	timeValue = 0.f;
}

void SceneStage::ShowGameResult()
{
	if (birds.size() == 0)
	{
		bool result = true;
		for (auto pig : pigs)
		{
			if (!pig->IsDead())
				result = false;
		}
		isGameOver = true;
		FRAMEWORK.SetTimeScale(0.f);
		if (result)
		{
			gameResult->SetClear(true);
		}
		else
		{
			gameResult->SetClear(false);
		}
		gameResult->SetActive(true);
		gameResult->ShowResult();
	}
	else
	{
		bool result = true;
		for (auto pig : pigs)
		{
			if (!pig->IsDead())
				result = false;
		}
		if (result)
		{
			isGameOver = true;
			FRAMEWORK.SetTimeScale(0.f);
			gameResult->SetClear(true);
			gameResult->SetActive(true);
			gameResult->ShowResult();
		}
	}
}

void SceneStage::ZoomIn(float dt)
{
	if (InputMgr::GetKey(sf::Keyboard::Z))
	{
		currentViewSize -= sf::Vector2f(100 * dt * FRAMEWORK.GetWindowRatio(), 100 * dt);
		if (currentViewSize.y <= minViewSize.y)
		{
			currentViewSize = minViewSize;
		}
		worldView.setCenter(currentViewPos);
		worldView.setSize(currentViewSize);
		isZoomIn = true;
	}
	else if (InputMgr::GetKeyUp(sf::Keyboard::Z))
	{
		isZoomIn = false;
	}
}

void SceneStage::ZoomOut(float dt)
{
	if (InputMgr::GetKey(sf::Keyboard::X))
	{
		currentViewSize += sf::Vector2f(100 * dt * FRAMEWORK.GetWindowRatio(), 100 * dt);
		if (currentViewPos.y + currentViewSize.y * 0.5f >= backgroundSize.top + backgroundSize.height)
			currentViewPos.y -= 100 * dt;
		if (currentViewPos.y - currentViewSize.y * 0.5f <= backgroundSize.top)
			currentViewPos.y += 100 * dt;
		if (currentViewPos.x + currentViewSize.x * 0.5f >= backgroundSize.left + backgroundSize.width)
			currentViewPos.x -= 100 * dt;
		if (currentViewPos.x - currentViewSize.x * 0.5f <= backgroundSize.left)
			currentViewPos.x += 100 * dt;
		if (currentViewSize.y >= backgroundSize.height)
		{
			currentViewSize = maxViewSize;
		}
		worldView.setCenter(currentViewPos);
		worldView.setSize(currentViewSize);
		isZoomOut = true;
	}
	else if (InputMgr::GetKeyUp(sf::Keyboard::X))
	{
		isZoomOut = false;
	}
}

void SceneStage::CheckObjectsDead()
{
	for(int i = 0; i< pigCount; i++)
	{
		if (pigs[i]->IsDead())
		{
			pigs[i]->SetDisable();
			pigs[i]->SetActive(false);
		}
	}
	for(int i = 0; i< blockCount; i++)
	{
		if (blocks[i]->IsDead())
		{
			blocks[i]->SetDisable();
			blocks[i]->SetActive(false);
		}
	}
}

void SceneStage::ObjectsReset()
{
	for (auto bird : birds)
	{
		bird->SetRestart(true);
		bird->SetInitPos();
		bird->SetShoot(false);
		bird->SetActive(true);
		bird->SetAbilityUse(true);
	}
	for (auto block : blocks)
	{
		block->SetEnable();
		block->Reset();
		block->SetActive(true);
		block->SetTransform();
		block->SetNotDead();
	}
	for (auto pig : pigs)
	{
		pig->SetEnable();
		pig->Reset();
		pig->SetActive(true);
		pig->SetTransform();
		pig->SetNotDead();
	}
}

void SceneStage::SetObjectTransform()
{
	for (int i = 0; i < tryCount; i++)
	{
		birds[i]->SetTransform();
	}

	for (int i = 0; i < blockCount; i++)
	{
		blocks[i]->SetTransform();
	}
	for (int i = 0; i < pigCount; i++)
	{
		pigs[i]->SetTransform();
	}
}

void SceneStage::DeleteObjects()
{
	for (auto block : blocks)
	{
		block->SetDisable();
		RemoveGameObject(block);
	}
	for (auto pig : pigs)
	{
		pig->SetDisable();
		RemoveGameObject(pig);
	}
	for (auto bird : birds)
	{
		bird->SetDisable();
		RemoveGameObject(bird);
	}
	blocks.clear();
	blockCount = 0;
	pigs.clear();
	pigCount = 0;
	birds.clear();
	birdCount = 0;
}
