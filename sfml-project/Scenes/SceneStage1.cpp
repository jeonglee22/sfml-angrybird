#include "stdafx.h"
#include "SceneStage1.h"
#include "SpriteGo.h"
#include "Bird.h"

SceneStage1::SceneStage1()
	: Scene(SceneIds::Stage1)
{
}

void SceneStage1::Init()
{
	texIds.push_back("graphics/RedBird.png");
	texIds.push_back("graphics/LevelOne.png");

	background = (SpriteGo*) AddGameObject(new SpriteGo("graphics/LevelOne.png"));
	background->SetScale({ 1280.f / 909.f, 1.f});
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;

	groundBody.position = b2Vec2{ 640.f / SCALE, 720.f / SCALE };
	groundBodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &groundBody);

	b2Polygon groundBox = b2MakeBox(FRAMEWORK.GetWindowBounds().width * 0.5f / SCALE, 80.f / SCALE);
	groundShapeDef = b2DefaultShapeDef();
	groundShapeDef.material.friction = 1.f;
	groundShapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);

	bird = (Bird*)AddGameObject(new Bird("graphics/RedBird.png", "Bird"));

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

	ball.setRadius(bird->GetCollisionRadius());
	ball.setOrigin({ bird->GetCollisionRadius(),bird->GetCollisionRadius() });
	ball.setPosition({ bird->GetPosition().x , bird->GetPosition().y });
	ball.setFillColor(sf::Color::Blue);
}

void SceneStage1::Update(float dt)
{
	Scene::Update(dt);
	if(bird->GetShoot())
	{
		timeValue += dt;
		if (timeValue >= timeStep)
		{
			b2World_Step(FRAMEWORK.GetWorldID(), timeStep, subStepCount);
			//bird->Shoot();
			b2Vec2 position = b2Body_GetPosition(bird->GetBodyId());
			b2Rot rotation = b2Body_GetRotation(bird->GetBodyId());
			bird->SetPosition({ position.x * SCALE, position.y * SCALE });
			bird->SetRotation(b2Rot_GetAngle(rotation) * 180 / B2_PI);
			ball.setPosition({ position.x * SCALE, position.y * SCALE });
			ball.setRotation(b2Rot_GetAngle(rotation) * 180 / B2_PI);
			timeValue = 0.f;
		}
	}
#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		bird->Reset();
		bird->SetShoot(false);
		ball.setPosition({ bird->GetPosition().x , bird->GetPosition().y });
	}
#endif // DEBUG
}

void SceneStage1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	window.draw(ball);
}

