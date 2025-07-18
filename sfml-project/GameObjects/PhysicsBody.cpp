#include "stdafx.h"
#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(Type ty, const std::string& texPlayerId, const std::string& name)
	:SpriteGo(texPlayerId, name), bodyType(ty)
{
}

void PhysicsBody::Init()
{
	SpriteGo::Init();
	if(bodyType != Type::Invisible)
	{
		sortingLayer = SortingLayers::Foreground;
		sortingOrder = 0;

		bodyDef.type = b2_dynamicBody;

		SetOrigin(Origins::MC);
	}
	setBody = false;
}

void PhysicsBody::Release()
{
	/*std::cout << bodyId.index1 << std::endl;*/
	if(0 < bodyId.index1 && bodyId.index1 < 128)
	{
		b2DestroyBody(bodyId);
		bodyId = b2_nullBodyId;
	}

	SpriteGo::Release();
}

void PhysicsBody::Reset()
{
	if (bodyType != Type::Invisible)
	{
		SpriteGo::Reset();
	}

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	SetPosition(initPos * SCALE);
	SetRotation(0.f);

	if (!setBody)
	{
		bodyDef.position = b2Vec2{ initPos.x, initPos.y };
		bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

		b2Polygon groundBox = b2MakeBox(texSize.x, texSize.y);
		shapeDef = b2DefaultShapeDef();
		shapeDef.density = density;
		shapeDef.material.friction = friction;
		shapeDef.material.restitution = restitution;
		shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &groundBox);
		setBody = true;
	}
	else
	{
		b2Body_SetTransform(bodyId, b2Vec2{ initPos.x, initPos.y }, b2Rot_identity);
		if(bodyType == Type::Invisible)
		{
			b2Polygon newBox = b2MakeBox(texSize.x, texSize.y);
			b2Shape_SetPolygon(shapeId, &newBox);
			b2Shape_SetFriction(shapeId, friction);
			b2Shape_SetRestitution(shapeId, restitution);
			b2Shape_SetDensity(shapeId, density, true);
		}
	}
}

void PhysicsBody::Update(float dt)
{
	SpriteGo::Update(dt);
}

void PhysicsBody::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void PhysicsBody::SetBoxSize(float width, float height)
{
	texSize.x = width / SCALE;
	texSize.y = height / SCALE;
}

void PhysicsBody::SetBoxPos(float x, float y)
{
	initPos.x = x / SCALE;
	initPos.y = y / SCALE;
}

void PhysicsBody::SetBoxFactor(float fric, float res, float dens, float roll)
{
	density = dens;
	friction = fric;
	restitution = res;
	rollingResistance = roll;
}

void PhysicsBody::SetTransform()
{
	b2Vec2 position = b2Body_GetPosition(bodyId);
	b2Rot rotation = b2Body_GetRotation(bodyId);
	SetPosition({ position.x * SCALE, position.y * SCALE });
	SetRotation(b2Rot_GetAngle(rotation) * 180 / B2_PI);
}