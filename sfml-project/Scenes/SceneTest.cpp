#include "stdafx.h"
#include "SceneTest.h"

SceneTest::SceneTest()
	: Scene(SceneIds::Test)
{
}

void SceneTest::Init()
{
	Scene::Init();

	auto size = FRAMEWORK.GetWindowSizeF();

	start.setSize({ 20.f,20.f });
	start.setOrigin({ 10.f,10.f });
	start.setPosition({ 100.f, 500.f });

	ground.setSize({ size.x, 200.f });
	ground.setOrigin({ size.x / 2.f , 100.f });
	ground.setPosition({ size.x / 2.f , 700.f });
	ground.setFillColor(sf::Color::Green);

	ball.setRadius(10.f);
	ball.setOrigin({ 10.f,10.f });
	velocity = 500.f;
	
	isShoot = false;
}

void SceneTest::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();
}

void SceneTest::Update(float dt)
{
	Scene::Update(dt);
	
	if(InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isShoot = false;
		velocity = 500.f;
		mouseStart = InputMgr::GetMousePosition();
		ball.setPosition((sf::Vector2f)mouseStart);
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		mouseEnd = InputMgr::GetMousePosition();
		direction = Utils::GetNormal((sf::Vector2f)(mouseStart - mouseEnd));
		isShoot = true;
	}
	if(isShoot)
	{
		direction += 0.5f * sf::Vector2f(0, 2500.f) * dt * dt;
		ball.setPosition(ball.getPosition() + velocity * dt * direction);
	}

	if (ball.getPosition().y >= 590.f)
	{
		ball.setPosition({ ball.getPosition().x, 590.f });
		direction.y *= -1.f;
		velocity *= COR;
		if (velocity <= 10.f)
		{
			velocity = 0.f;
		}
	}
}

void SceneTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(start);
	window.draw(ground);
	if(isShoot)
	{
		window.draw(ball);
	}
}