#include "stdafx.h"
#include "SceneStage1.h"
#include "SpriteGo.h"
#include "Bird.h"
#include "Block.h"
#include "Pig.h"
#include "rapidcsv.h"
#include "ShootCountUI.h"
#include "InvisiblePhysicsBody.h"

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
	texIds.push_back("graphics/Angrybirds/ShootStand.png");
	texIds.push_back("graphics/Angrybirds/StandRight.png");
	texIds.push_back("graphics/Angrybirds/StandLeft.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	background = (SpriteGo*)AddGameObject(new SpriteGo("graphics/LevelOne.png"));
	background->SetScale({ 1.f, 768.f / 1082.f });
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;

	ground = (InvisiblePhysicsBody*)AddGameObject(new InvisiblePhysicsBody());
	stand = (InvisiblePhysicsBody*)AddGameObject(new InvisiblePhysicsBody());

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			shootStand.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/Angrybirds/StandRight.png")));
			shootStand[i]->SetOrigin(Origins::TL);
			shootStand[i]->SetPosition({ 143.f, 550.f });
		}
		else
		{
			shootStand.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/Angrybirds/StandLeft.png")));
			shootStand[i]->SetOrigin(Origins::TR);
			shootStand[i]->SetPosition({ 159.f, 545.f });
		}
		shootStand[i]->SetScale({ 1.f,0.7f });
		shootStand[i]->sortingLayer = SortingLayers::Foreground;
		if(i == 0)
			shootStand[i]->sortingOrder = -1;
		else
			shootStand[i]->sortingOrder = 1;
	}

	for(int i =0; i< tryMax; i++)
	{
		birds.push_back((Bird*)AddGameObject(new Bird("graphics/Angrybirds/RedBird1.png", "Bird")));
	}

	LoadBlockInfo("StageStructures/Stage1.csv");

	pig = (Pig*)AddGameObject(new Pig("graphics/Angrybirds/PigOriginal.png", "Pig"));
	pig->SetInitPos({900.f, 480.f - 30.f });

	countUI = (ShootCountUI*)AddGameObject(new ShootCountUI());

	Scene::Init();
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
	ground->SetBoxFactor(1.f, 0.5f);

	Scene::Enter();

	sf::Vector2u standTexSize = TEXTURE_MGR.Get("graphics/Angrybirds/ShootStand.png").getSize();

	stand->SetBoxSize(standTexSize.x * 0.2f, standTexSize.y * 0.5f * 0.7f);
	stand->SetBoxPos(150.f, (560.f + birds[0]->GetCollisionRadius() + standTexSize.y * 0.7f * 0.5f));
	stand->SetBoxFactor(1.f, 0.5f);
	stand->Reset();

	birds[tryCount]->SetBirdEnable();
	countUI->SetCount(birds.size());
}

void SceneStage1::Update(float dt)
{
	Scene::Update(dt);

	timeValue += dt;
	if (timeValue >= timeStep)
	{
		b2World_Step(FRAMEWORK.GetWorldID(), timeStep, subStepCount);
		//bird->Shoot();
		for (int i = 0; i < tryCount; i++)
		{
			birds[i]->SetTransform();
		}
		if(tryCount < 5)
		{
			if (birds[tryCount]->GetShoot())
			{
				birds[tryCount]->SetTransform();
				if (birds[tryCount]->CheckBirdStop())
				{
					tryCount++;
					countUI->SetCount(birds.size() - tryCount);
					if (tryCount < 5)
					{
						birds[tryCount]->SetBirdEnable();
					}
				}
			}
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
			birds[i]->Reset();
			birds[i]->SetShoot(false);

		}
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
		blocks.push_back((Block*)AddGameObject(new Block(row[0])));
		blocks[i]->SetInitPos({ std::stof(row[1]), std::stof(row[2]) });
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
