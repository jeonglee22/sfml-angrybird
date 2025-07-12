#include "stdafx.h"
#include "Bird.h"

Bird::Bird(const std::string& texPlayerId,const std::string& name)
	: SpriteGo(texPlayerId, name)
{
}

void Bird::Init()
{
	SpriteGo::Init();

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;

	SetOrigin(Origins::MC);
}

void Bird::Release()
{
	SpriteGo::Release();

	b2DestroyBody(bodyId);
	bodyId = b2_nullBodyId;
}

void Bird::Reset()
{
	SpriteGo::Reset();

	bodyId = b2_nullBodyId;

	SetPosition({ 100.f, 550.0f});
	SetRotation(0.f);
	bodyDef.position = b2Vec2{ GetPosition().x / SCALE, GetPosition().y / SCALE };
	bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

	collisionRadius = sprite.getTexture()->getSize().x * 0.5f * 0.8f;
	b2Circle circleBox;
	circleBox.center = { 0.f, 0.f };
	circleBox.radius = collisionRadius / SCALE;

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.material.friction = 0.2f;
	shapeDef.material.rollingResistance = 0.2f;
	shapeDef.material.restitution = 0.5f;
	b2CreateCircleShape(bodyId, &shapeDef, &circleBox);
}

void Bird::Update(float dt)
{
	SpriteGo::Update(dt);

	if(InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !isCharging && !isShoot)
	{
		if(Utils::PointInTransformBounds(sprite, GetLocalBounds(), (sf::Vector2f)InputMgr::GetMousePosition()))
		{
			isCharging = true;
			mouseStart = (sf::Vector2f)InputMgr::GetMousePosition();
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isCharging)
	{
		mouseEnd = (sf::Vector2f) InputMgr::GetMousePosition();
		direction = Utils::GetNormal((sf::Vector2f)(mouseStart - mouseEnd));
		isShoot = true;
		b2Body_ApplyForceToCenter(bodyId, b2Vec2{ direction.x * 1000, direction.y * 1000 }, true);
	}/*
	if(isShoot)
	{
		direction += 0.5f * sf::Vector2f(0, 2500.f) * dt * dt;
		ball.setPosition(ball.getPosition() + velocity * dt * direction);
	}*/
}

void Bird::Draw(sf::RenderWindow& window)
{
	//if(isShoot)
	//{
		SpriteGo::Draw(window);
	//}
}
