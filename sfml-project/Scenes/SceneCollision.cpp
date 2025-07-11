#include "stdafx.h"
#include "Ball.h"
#include "Block.h"
#include "SceneCollision.h"

SceneCollision::SceneCollision()
	: Scene(SceneIds::Collision)
{
}

void SceneCollision::Init()
{
	auto size = FRAMEWORK.GetWindowSizeF();

	ground.setSize({ size.x, 200.f });
	ground.setOrigin({ size.x / 2.f , 100.f });
	ground.setPosition({ size.x / 2.f , 700.f });
	ground.setFillColor(sf::Color::Green);

	block = (Block*)AddGameObject(new Block("Block"));
	block->SetSize({ size.x, 400.f });
	block->SetOrigin(Origins::MC);
	block->SetPosition({ 100.f,600.f });

	ball = (Ball*)AddGameObject(new Ball("Ball"));
	ball->GetBody().setRadius(10.f);
	ball->SetOrigin(Origins::MC);
	ball->SetPosition({ 100.f, 100.f });

	/*object1 = (Ball*)AddGameObject(new Ball("Object1"));
	object1->GetBody().setRadius(50.f);
	object1->SetOrigin(Origins::MC);
	object1->SetPosition({ 100.f, 400.f });
	object1->SetDirection({1.f,0.f});
	object1->SetColor(sf::Color::Red);
	object1->SetMass(100.f);

	object2 = (Ball*)AddGameObject(new Ball("Object2"));
	object2->GetBody().setRadius(50.f);
	object2->SetOrigin(Origins::MC);
	object2->SetPosition({ 400.f, 700.f });
	object2->SetDirection({0.f,-1.f});
	object2->SetColor(sf::Color::Blue);
	object2->SetMass(1000.f);*/

	Scene::Init();
}

void SceneCollision::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();
}

void SceneCollision::Update(float dt)
{
	Scene::Update(dt);

	if(!ball->GetShoot())
	{
		ball->SetPosition({ 100.f, 100.f });
	}
}

void SceneCollision::Draw(sf::RenderWindow& window)
{
	window.draw(ground);

	Scene::Draw(window);
}