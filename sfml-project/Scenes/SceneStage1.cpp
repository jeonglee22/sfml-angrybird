#include "stdafx.h"
#include "SceneStage1.h"
#include "SpriteGo.h"
#include "Bird.h"
#include "Block.h"

SceneStage1::SceneStage1()
	: Scene(SceneIds::Stage1)
{
}

void SceneStage1::Init()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	texIds.push_back("graphics/Angrybirds/RedBird1.png");
	texIds.push_back("graphics/LevelOne.png");
	texIds.push_back("graphics/StaticObjects/WoodSquareBlock1.png");
	texIds.push_back("graphics/StaticObjects/WoodSquareBlock2.png");

	background = (SpriteGo*) AddGameObject(new SpriteGo("graphics/LevelOne.png"));
	background->SetScale({ 1.f, 768.f / 1082.f });
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;

	groundBody.position = b2Vec2{ bounds.width * 0.5f / SCALE, bounds.height / SCALE };
	groundBodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &groundBody);

	b2Polygon groundBox = b2MakeBox(bounds.width * 0.5f / SCALE, 85.f / SCALE);
	groundShapeDef = b2DefaultShapeDef();
	groundShapeDef.material.friction = 1.f;
	groundShapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);

	bird = (Bird*)AddGameObject(new Bird("graphics/Angrybirds/RedBird1.png", "Bird"));

	for (int i = 0; i < blockCount; i++)
	{
		blocks.push_back((Block*)AddGameObject(new Block("graphics/StaticObjects/WoodSquareBlock1.png")));
		//blocks[i]->SetInitPos({ 1200.f - i * 50.f,bounds.height - 85.f - 50.f });
		blocks[i]->SetInitPos({ 800.f,bounds.height - 85.f - 50.f * (i+1)});
	}

	Scene::Init();
}

void SceneStage1::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();

	shootBody.position = b2Vec2{ 150.f / SCALE, (550.f + bird->GetCollisionRadius() + 40.f) / SCALE };
	shootBodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &shootBody);

	b2Polygon shootBox = b2MakeBox(20.f / SCALE, 40.f / SCALE);
	shootShapeDef = b2DefaultShapeDef();
	shootShapeDef.material.friction = 1.f;
	shootShapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(shootBodyId, &shootShapeDef, &shootBox);
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
		for (int i = 0; i < blockCount; i++)
		{
			blocks[i]->SetTransform();
		}
	}
#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		bird->Reset();
		bird->SetShoot(false);
	}
#endif // DEBUG
}

void SceneStage1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

