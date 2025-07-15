#include "stdafx.h"
#include "SceneStage1.h"
#include "BackGround.h"
#include "Bird.h"
#include "Pig.h"
#include "rapidcsv.h"
#include "ShootCountUI.h"
#include "PhysicsBody.h"
#include "ShootStand.h"

SceneStage1::SceneStage1()
	: Scene(SceneIds::Stage1)
{
}

void SceneStage1::Init()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	texIds.push_back("graphics/Angrybirds/RedBird1.png");
	texIds.push_back("graphics/Angrybirds/PigOriginal.png");
	texIds.push_back("graphics/LevelOne.png");
	texIds.push_back("graphics/band.png");
	texIds.push_back("graphics/band2.png");
	texIds.push_back("graphics/Angrybirds/ShootStand.png");
	texIds.push_back("graphics/Angrybirds/StandRight.png");
	texIds.push_back("graphics/Angrybirds/StandLeft.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	AddGameObject(new BackGround("graphics/LevelOne.png"));

	ground = (PhysicsBody*)AddGameObject(new PhysicsBody(PhysicsBody::Type::Invisible));
	shootStand = (ShootStand*)AddGameObject(new ShootStand());

	for(int i =0; i< tryMax; i++)
	{
		birds.push_back((Bird*)AddGameObject(new Bird("graphics/Angrybirds/RedBird1.png", "Bird")));
	}

	LoadBlockInfo("StageStructures/Stage1.csv");

	countUI = (ShootCountUI*)AddGameObject(new ShootCountUI());

	Scene::Init();

	AddGameObject(shootStand->GetLeftPart());
	AddGameObject(shootStand->GetRightPart());
	std::vector<SpriteGo*> band = shootStand->GetBandPart();
	for (auto part : band)
	{
		AddGameObject(part);
	}
}

void SceneStage1::Enter()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	uiView.setSize(initViewSize);
	uiView.setCenter(initViewPos);
	worldView.setSize(initViewSize);
	worldView.setCenter(initViewPos);
	currentViewPos = initViewPos;
	currentViewSize = initViewSize;

	ground->SetBoxSize(bounds.width * 1.5f, 85.f);
	ground->SetBoxPos(bounds.width * 0.5f, bounds.height);
	ground->SetBoxFactor(0.8f, 0.5f);

	pig->SetInitPos({ 1500.f, 440.f });

	Scene::Enter();

	//birds[tryCount]->SetBirdEnable();
	birds[tryCount]->SetStartPos();
	shootStand->SetBird(birds[tryCount]);
	countUI->SetCount(birds.size());
}

void SceneStage1::Update(float dt)
{
	Scene::Update(dt);

	if (tryCount < tryMax)
	{
		if (birds[tryCount]->GetShoot() && birdReady)
		{
			tryCount++;
			countUI->SetCount(tryMax - tryCount);
			birdReady = false;
		}

		if (tryCount > 0 && birds[tryCount-1]->CheckFinishShoot() && !birdReady)
		{
			birds[tryCount]->SetStartPos();
			shootStand->SetBird(birds[tryCount]);
			birdReady = true;
		}
	}

	timeValue += dt;
	if (timeValue >= timeStep)
	{
		b2World_Step(FRAMEWORK.GetWorldID(), timeStep, subStepCount);
		//bird->Shoot();
		for (int i = 0; i < tryCount; i++)
		{
			birds[i]->SetTransform();
		}
		
		for (int i = 0; i < blockCount-1; i++)
		{
			blocks[i]->SetTransform();
		}
		pig->SetTransform();
		
		CheckPigCollision();
		//std::cout << pig->IsDead() << std::endl;
		if (pig->IsDead())
		{
			pig->SetDisable();
			pig->SetActive(false);
		}

		timeValue = 0.f;
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		mouseStart = (sf::Vector2f)InputMgr::GetMousePosition();
	}
	else if (InputMgr::GetMouseButton(sf::Mouse::Left) && !birds[tryCount]->GetCharging())
	{
		ViewControl((sf::Vector2f)InputMgr::GetMousePosition());
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space) && initViewPos != currentViewPos)
	{
		currentViewPos = initViewPos;
		worldView.setCenter(initViewPos);
	}
#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		Restart();
	}
#endif
}

void SceneStage1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneStage1::LoadBlockInfo(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);
	blockCount = doc.GetCell<int>(0,0);

	blocks.clear();
	for (int i = 0; i < blockCount-1; i++)
	{
		auto row = doc.GetRow<std::string>(i+2);
		if(std::find(texIds.begin(), texIds.end(), row[0]) == texIds.end())
			texIds.push_back(row[0]);
		blocks.push_back((PhysicsBody*)AddGameObject(new PhysicsBody(PhysicsBody::Type::Block,row[0])));
		blocks[i]->SetBoxPos(std::stof(row[1]), std::stof(row[2]));
		blocks[i]->SetBoxSize(std::stof(row[3]), std::stof(row[4]));
		blocks[i]->SetBoxFactor(std::stof(row[5]), std::stof(row[6]), std::stof(row[7]), 0.f);
	}
	auto row = doc.GetRow<std::string>(blockCount + 1);
	pig = (Pig*)AddGameObject(new Pig(row[0], "Pig"));
	pig->SetInitPos({ std::stof(row[1]), std::stof(row[2]) });
}

void SceneStage1::CheckPigCollision()
{
	b2ContactHitEvent* hitEvents = b2World_GetContactEvents(FRAMEWORK.GetWorldID()).hitEvents;
	int hitCount = b2World_GetContactEvents(FRAMEWORK.GetWorldID()).hitCount;
	for (int i = 0; i < hitCount; i++)
	{
		b2ContactHitEvent event = hitEvents[i];
		b2ShapeId shapeId1 = event.shapeIdA;
		b2ShapeId shapeId2 = event.shapeIdB;
		float speed = event.approachSpeed;
		if (shapeId1.index1 == pig->GetShapeId().index1 || shapeId2.index1 == pig->GetShapeId().index1)
		{
			pig->TakeDamage((int)speed * 7);
			std::cout << pig->GetHp() << std::endl;
		}
	}
}

void SceneStage1::ViewControl(const sf::Vector2f& mousePos)
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	float newXpos = Utils::Clamp((mouseStart - mousePos).x + currentViewPos.x, -bounds.width * 0.5f , bounds.width * 1.5f);
	currentViewPos = sf::Vector2f(newXpos, currentViewPos.y);
	mouseStart = mousePos;
	worldView.setCenter(currentViewPos);
}

void SceneStage1::Restart()
{
	currentViewPos = initViewPos;
	worldView.setCenter(initViewPos);
	for (int i = 0; i < tryMax; i++)
	{
		birds[i]->SetRestart(true);
		birds[i]->SetInitPos();
		birds[i]->SetShoot(false);
	}
	tryCount = 0;
	countUI->SetCount(tryMax - tryCount);
	birds[tryCount]->SetStartPos();
	shootStand->SetBird(birds[tryCount]);
	birdReady = true;

	for (auto block : blocks)
	{
		block->Reset();
	}
	pig->Reset();
	pig->SetEnable();
	pig->SetActive(true);
	pig->SetNotDead();
}
