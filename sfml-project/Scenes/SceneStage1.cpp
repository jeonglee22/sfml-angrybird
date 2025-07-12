#include "stdafx.h"
#include "SceneStage1.h"
#include "SpriteGo.h"
#include "Bird.h"
#include "Block.h"
#include "Pig.h"

SceneStage1::SceneStage1()
	: Scene(SceneIds::Stage1)
{
}

void SceneStage1::Init()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	texIds.push_back("graphics/Angrybirds/RedBird1.png");
	texIds.push_back("graphics/LevelOne.png");
	texIds.push_back("graphics/Angrybirds/ShootStand.png");
	texIds.push_back("graphics/Angrybirds/StandRight.png");
	texIds.push_back("graphics/Angrybirds/StandLeft.png");
	texIds.push_back("graphics/StaticObjects/WoodSquareBlock1.png");
	texIds.push_back("graphics/StaticObjects/WoodSquareBlock2.png");

	background = (SpriteGo*)AddGameObject(new SpriteGo("graphics/LevelOne.png"));
	background->SetScale({ 1.f, 768.f / 1082.f });
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;

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

	bird = (Bird*)AddGameObject(new Bird("graphics/Angrybirds/RedBird1.png", "Bird"));

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

	Scene::Enter();

	groundBodyDef.position = b2Vec2{ bounds.width * 0.5f / SCALE, bounds.height / SCALE };
	groundBodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &groundBodyDef);

	b2Polygon groundBox = b2MakeBox(bounds.width * 0.5f / SCALE, 85.f / SCALE);
	groundShapeDef = b2DefaultShapeDef();
	groundShapeDef.material.friction = 1.f;
	groundShapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);

	sf::Vector2u standTexSize = TEXTURE_MGR.Get("graphics/Angrybirds/ShootStand.png").getSize();

	standBodyDef.position = b2Vec2{ 150.f / SCALE, (560.f + bird->GetCollisionRadius() + standTexSize.y * 0.7f * 0.5f) / SCALE };
	standBodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &standBodyDef);

	b2Polygon standBox = b2MakeBox(standTexSize.x * 0.2f / SCALE, standTexSize.y * 0.5f * 0.7f / SCALE);
	standShapeDef = b2DefaultShapeDef();
	standShapeDef.material.friction = 1.f;
	standShapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(standBodyId, &standShapeDef, &standBox);
}

void SceneStage1::Update(float dt)
{
	Scene::Update(dt);

	timeValue += dt;
	if (timeValue >= timeStep)
	{
		b2World_Step(FRAMEWORK.GetWorldID(), timeStep, subStepCount);
		//bird->Shoot();
		if (bird->GetShoot())
		{
			bird->SetTransform();
			timeValue = 0.f;
		}
		/*for (int i = 0; i < blockCount; i++)
		{
			blocks[i]->SetTransform();
		}*/
	}

#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		bird->Reset();
		bird->SetShoot(false);
	}
#endif
}

void SceneStage1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
