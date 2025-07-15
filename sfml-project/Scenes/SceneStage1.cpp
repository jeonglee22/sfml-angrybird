#include "stdafx.h"
#include "SceneStage1.h"
#include "SpriteGo.h"
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

	background = (SpriteGo*)AddGameObject(new SpriteGo("graphics/LevelOne.png"));
	background->SetScale({ 1.f, 768.f / 1082.f });
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;

	ground = (PhysicsBody*)AddGameObject(new PhysicsBody(PhysicsBody::Type::Invisible));
	shootStand = (ShootStand*)AddGameObject(new ShootStand());

	for(int i =0; i< tryMax; i++)
	{
		birds.push_back((Bird*)AddGameObject(new Bird("graphics/Angrybirds/RedBird1.png", "Bird")));
	}

	LoadBlockInfo("StageStructures/Stage1.csv");

	pig = (Pig*)AddGameObject(new Pig("graphics/Angrybirds/PigOriginal.png", "Pig"));
	pig->SetInitPos({900.f, 480.f - 30.f });

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
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	ground->SetBoxSize(bounds.width * 0.5f, 85.f);
	ground->SetBoxPos(bounds.width * 0.5f, bounds.height);
	ground->SetBoxFactor(0.8f, 0.5f);

	Scene::Enter();

	//birds[tryCount]->SetBirdEnable();
	birds[tryCount]->SetStartPos();
	countUI->SetCount(birds.size());
}

void SceneStage1::Update(float dt)
{
	Scene::Update(dt);

	if(tryCount < tryMax)
	{
		shootStand->SetBird(birds[tryCount]);

		if (birds[tryCount]->GetShoot()) 
		{
			birds[tryCount]->SetBirdEnable();
			birds[tryCount]->SetShoot(false);
			tryCount++;
			countUI->SetCount(tryMax - tryCount);
		}

		if (tryCount > 0 && birds[tryCount-1]->CheckBirdOut())
		{
			birds[tryCount]->SetStartPos();
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
		
		for (int i = 0; i < blockCount; i++)
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

#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		for(int i = 0 ; i < tryMax; i++)
		{
			birds[i]->SetRestart(true);
			birds[i]->SetInitPos();
			birds[i]->SetShoot(false);
		}
		tryCount = 0;
		countUI->SetCount(tryMax - tryCount);
		birds[tryCount]->SetStartPos();
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
	for (int i = 0; i < blockCount; i++)
	{
		auto row = doc.GetRow<std::string>(i+2);
		if(std::find(texIds.begin(), texIds.end(), row[0]) == texIds.end())
			texIds.push_back(row[0]);
		blocks.push_back((PhysicsBody*)AddGameObject(new PhysicsBody(PhysicsBody::Type::Block,row[0])));
		blocks[i]->SetBoxPos(std::stof(row[1]), std::stof(row[2]));
		blocks[i]->SetBoxSize(std::stof(row[3]), std::stof(row[4]));
		blocks[i]->SetBoxFactor(std::stof(row[5]), std::stof(row[6]), std::stof(row[7]), 0.f);
	}
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
		if (shapeId1.index1 == pig->GetShapeId().index1 || shapeId2.index1 == pig->GetShapeId().index1)
		{
			pig->TakeDamage(20);
			std::cout << pig->GetHp() << std::endl;
		}
	}
}
