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

	/*groundBody.position = b2Vec2{ 640.f / SCALE, 700.f / SCALE };
	groundBodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &groundBody);
	
	b2Polygon groundBox = b2MakeBox(size.x * 0.25f / SCALE, 100.f / SCALE);
	groundShapeDef = b2DefaultShapeDef();
	groundShapeDef.material.friction = 1.f;
	groundShapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);*/

	/*bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2{ size.x * 0.5f / SCALE, 100.0f / SCALE };
	bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);
	b2Polygon dynamicBox = b2MakeBox(15.0f / SCALE, 15.0f / SCALE);
	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.material.friction = 0.3f;
	shapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

	bodyDef2 = b2DefaultBodyDef();
	bodyDef2.type = b2_dynamicBody;
	bodyDef2.position = b2Vec2{ (size.x * 0.5f + 15.f) / SCALE, 50.0f / SCALE };
	bodyId2 = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef2);
	b2Circle circleBox;
	circleBox.center = {0.f,0.f};
	circleBox.radius = 20.f / SCALE;
	b2ShapeDef shapeDef2 = b2DefaultShapeDef();
	shapeDef2.density = 1.0f;
	shapeDef2.material.friction = 0.2f;
	shapeDef2.material.rollingResistance = 0.1f;
	shapeDef2.material.restitution = 0.5f;
	b2CreateCircleShape(bodyId2, &shapeDef2, &circleBox);*/

	//start.setSize({ 20.f,20.f });
	//start.setOrigin({ 10.f,10.f });
	//start.setPosition({ 100.f, 500.f });

	/*ground.setSize({ size.x * 0.5f, 200.f });
	ground.setOrigin({ size.x * 0.5f / 2.f , 100.f });
	ground.setPosition({ groundBody.position.x * SCALE , groundBody.position.y * SCALE });
	ground.setFillColor(sf::Color::Green);*/

	/*box.setSize({ 30.f,30.f });
	box.setOrigin({ 15.f,15.f });
	box.setPosition({ size.x * 0.5f, 100.0f });
	box.setFillColor(sf::Color::Red);

	ball.setRadius(20.f);
	ball.setOrigin({ 20.f,20.f });
	ball.setPosition({ (size.x * 0.5f + 10.f) , 50.0f });
	velocity = 500.f;*/
	
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

void SceneTest::Exit()
{
	b2DestroyWorld(FRAMEWORK.GetWorldID());

	Scene::Exit();
}

void SceneTest::Update(float dt)
{
	Scene::Update(dt);
	/*timeValue += dt;
	if(timeValue >= timeStep)
	{
		b2World_Step(FRAMEWORK.GetWorldID(), timeStep, subStepCount);
		b2Vec2 position = b2Body_GetPosition(bodyId);
		b2Rot rotation = b2Body_GetRotation(bodyId);
		box.setPosition(position.x * SCALE, position.y * SCALE);
		box.setRotation(b2Rot_GetAngle(rotation) * 180 / B2_PI);

		b2Vec2 position2 = b2Body_GetPosition(bodyId2);
		b2Rot rotation2 = b2Body_GetRotation(bodyId2);
		ball.setPosition(position2.x * SCALE, position2.y * SCALE);
		ball.setRotation(b2Rot_GetAngle(rotation2) * 180 / B2_PI);
		timeValue = 0.f;
	}*/

	/*if(InputMgr::GetMouseButtonDown(sf::Mouse::Left))
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
	}*/
}

void SceneTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	//window.draw(start);
	/*window.draw(ground);
	window.draw(box);
	window.draw(ball);*/
	if(isShoot)
	{
		window.draw(ball);
	}
}