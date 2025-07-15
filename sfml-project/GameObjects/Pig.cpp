#include "stdafx.h"
#include "Pig.h"

Pig::Pig(const std::string& texId, const std::string& name)
	: PhysicsBody(Type::Pig, texId, name)
{
}

void Pig::Init()
{
	PhysicsBody::Init();
}

void Pig::Release()
{
	PhysicsBody::Release();

	b2DestroyBody(bodyId);
	bodyId = b2_nullBodyId;
}

void Pig::Reset()
{
	SpriteGo::Reset();

	hp = maxHp;

	SetPosition(initPos * SCALE);
	SetRotation(0.f);
	if (!setBody)
	{
		bodyDef.position = b2Vec2{ initPos.x , initPos.y  };
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
		shapeId = b2CreateCircleShape(bodyId, &shapeDef, &circleBox);
		b2Shape_EnableHitEvents(shapeId, true);

		setBody = true;
	}
	else
	{
		b2Body_SetTransform(bodyId, b2Vec2{ initPos.x , initPos.y }, b2Rot{ 1.f,0.f });
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

void Pig::TakeDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		isDead = true;
	}
}
