#include "stdafx.h"
#include "Bird.h"

Bird::Bird(const std::string& texPlayerId, const std::string& name)
	:PhysicsBody(Type::Bird, texPlayerId, name)
{
}

void Bird::Init()
{
	PhysicsBody::Init();

	initPos = { 80.f / SCALE, 660.0f / SCALE };
}

void Bird::Release()
{
	PhysicsBody::Release();
}

void Bird::Reset()
{
	SpriteGo::Reset();

	SetPosition(initPos * SCALE);
	SetRotation(0.f);
	if (!setBody)
	{
		bodyDef.position = b2Vec2{ initPos.x, initPos.y };
		bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

		collisionRadius = sprite.getTexture()->getSize().x * 0.5f * 0.8f;
		b2Circle circleBox;
		circleBox.center = { 0.f, 0.f };
		circleBox.radius = collisionRadius / SCALE;

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = .5f;
		shapeDef.material.friction = 0.6f;
		shapeDef.material.rollingResistance = 0.5f;
		shapeDef.material.restitution = 0.5f;
		shapeId = b2CreateCircleShape(bodyId, &shapeDef, &circleBox);
		b2Shape_EnableHitEvents(shapeId, true);

		SetDisable();
		setBody = true;
	}
	else
	{
		if (isRestart)
		{
			b2Body_SetTransform(bodyId, b2Vec2{ initPos.x , initPos.y  }, b2Rot{ 1.f,0.f });
			isRestart = false;
			SetDisable();
		}
		else
		{
			b2Body_SetTransform(bodyId, b2Vec2{ shootPos.x, shootPos.y}, b2Rot{ 1.f,0.f });
		}
		b2Body_SetAngularVelocity(bodyId, 0.f);
		b2Body_SetLinearVelocity(bodyId, b2Vec2_zero);
	}
}

void Bird::Update(float dt)
{
	PhysicsBody::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !isCharging && !isShoot && canShoot)
	{
		if (Utils::PointInTransformBounds(sprite, GetLocalBounds(), (sf::Vector2f)InputMgr::GetMousePosition()))
		{
			isCharging = true;
			mouseStart = (sf::Vector2f)InputMgr::GetMousePosition();
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isCharging && canShoot)
	{
		mouseEnd = (sf::Vector2f)InputMgr::GetMousePosition();
		direction = Utils::GetNormal(mouseStart - mouseEnd);
		float distance = Utils::Clamp(Utils::Distance(mouseStart, mouseEnd), minCharge, maxCharge);

		sf::Vector2f Force(direction.x * forceAmount * (distance / maxCharge), direction.y * forceAmount * (distance / maxCharge));
		b2Body_ApplyForceToCenter(bodyId, b2Vec2{ Force.x, Force.y }, true);
		isShoot = true;
		isCharging = false;
	}
}

void Bird::Draw(sf::RenderWindow& window)
{
	PhysicsBody::Draw(window);
}