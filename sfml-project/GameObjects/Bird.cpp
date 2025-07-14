#include "stdafx.h"
#include "Bird.h"

Bird::Bird(const std::string& texPlayerId, const std::string& name)
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

	/*b2DestroyBody(bodyId);
	bodyId = b2_nullBodyId;*/
}

void Bird::Reset()
{
	SpriteGo::Reset();

	SetPosition(initPos);
	SetRotation(0.f);
	if(!setBody)
	{
		bodyDef.position = b2Vec2{ initPos.x / SCALE, initPos.y / SCALE };
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
		bodyShape = b2CreateCircleShape(bodyId, &shapeDef, &circleBox);
		std::cout << "Bird : " << bodyShape.index1 << ", " << bodyShape.generation << ", " << bodyShape.world0 << std::endl;
		b2Shape_EnableHitEvents(bodyShape, true);

		SetDisable();
		setBody = true;
	}
	else
	{
		b2Body_SetTransform(bodyId, b2Vec2{ shootPos.x / SCALE, shootPos.y / SCALE }, b2Rot{ 1.f,0.f });
		b2Body_SetAngularVelocity(bodyId, 0.f);
		b2Body_SetLinearVelocity(bodyId, b2Vec2_zero);
	}
}

void Bird::Update(float dt)
{
	SpriteGo::Update(dt);

	if(InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !isCharging && !isShoot && canShoot)
	{
		if(Utils::PointInTransformBounds(sprite, GetLocalBounds(), (sf::Vector2f)InputMgr::GetMousePosition()))
		{
			isCharging = true;
			mouseStart = (sf::Vector2f)InputMgr::GetMousePosition();
		}
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isCharging && canShoot)
	{
		mouseEnd = (sf::Vector2f) InputMgr::GetMousePosition();
		direction = Utils::GetNormal(mouseStart - mouseEnd);
		float distance = Utils::Clamp(Utils::Distance(mouseStart, mouseEnd), minCharge, maxCharge);
		isShoot = true;
		std::cout << distance << std::endl;
		sf::Vector2f Force(direction.x * forceAmount * (distance / maxCharge), direction.y * forceAmount * (distance / maxCharge));
		b2Body_ApplyForceToCenter(bodyId, b2Vec2{ Force.x, Force.y }, true);
		isCharging = false;
	}
}

void Bird::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Bird::SetTransform()
{
	b2Vec2 position = b2Body_GetPosition(bodyId);
	b2Rot rotation = b2Body_GetRotation(bodyId);
	SetPosition({ position.x * SCALE, position.y * SCALE });
	SetRotation(b2Rot_GetAngle(rotation) * 180 / B2_PI);
}
