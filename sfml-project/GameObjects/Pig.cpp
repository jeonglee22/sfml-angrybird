#include "stdafx.h"
#include "Pig.h"

Pig::Pig(const std::string& texPlayerId, const std::string& name)
	: SpriteGo(texPlayerId, name)
{
}

void Pig::Init()
{
	SpriteGo::Init();

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;

	//initPos = sf::Vector2f{ , };

	SetOrigin(Origins::MC);
}

void Pig::Release()
{
	SpriteGo::Release();

	b2DestroyBody(bodyId);
	bodyId = b2_nullBodyId;
}

void Pig::Reset()
{
	SpriteGo::Reset();

	hp = maxHp;

	SetPosition(initPos);
	SetRotation(0.f);
	if (!setBody)
	{
		bodyDef.position = b2Vec2{ initPos.x / SCALE, initPos.y / SCALE };
		bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

		collisionRadius = sprite.getTexture()->getSize().x * 0.5f * 0.8f;
		b2Circle circleBox;
		circleBox.center = { 0.f, 0.f };
		circleBox.radius = collisionRadius / SCALE;

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 0.5f;
		shapeDef.material.friction = 0.3f;
		shapeDef.material.rollingResistance = 0.2f;
		shapeDef.material.restitution = 0.5f;
		bodyShape = b2CreateCircleShape(bodyId, &shapeDef, &circleBox);
		std::cout << "Pig : " << bodyShape.index1 << ", " << bodyShape.generation << ", " << bodyShape.world0 << std::endl;
		b2Shape_EnableHitEvents(bodyShape, true);

		setBody = true;
	}
	else
	{
		b2Body_SetTransform(bodyId, b2Vec2{ initPos.x / SCALE, initPos.y / SCALE }, b2Rot{ 1.f,0.f });
	}
}

void Pig::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Pig::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Pig::SetTransform()
{
	b2Vec2 position = b2Body_GetPosition(bodyId);
	b2Rot rotation = b2Body_GetRotation(bodyId);
	SetPosition({ position.x * SCALE, position.y * SCALE });
	SetRotation(b2Rot_GetAngle(rotation) * 180 / B2_PI);
}

void Pig::TakeDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		isDead = true;
	}
}
