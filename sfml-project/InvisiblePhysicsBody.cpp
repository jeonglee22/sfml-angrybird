#include "stdafx.h"
#include "InvisiblePhysicsBody.h"

InvisiblePhysicsBody::InvisiblePhysicsBody(const std::string& name)
	: GameObject(name)
{
}

void InvisiblePhysicsBody::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void InvisiblePhysicsBody::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void InvisiblePhysicsBody::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void InvisiblePhysicsBody::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void InvisiblePhysicsBody::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void InvisiblePhysicsBody::Init()
{
}

void InvisiblePhysicsBody::Release()
{
}

void InvisiblePhysicsBody::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	if(!isReset)
	{
		bodyDef.position = b2Vec2{ boxPosX / SCALE, boxPosY / SCALE };
		bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

		b2Polygon groundBox = b2MakeBox(boxHalfWidth / SCALE, boxHalfHeight / SCALE);
		shapeDef = b2DefaultShapeDef();
		shapeDef.material.friction = friction;
		shapeDef.material.restitution = restitution;
		shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &groundBox);

		isReset = true;
	}
	else
	{
		b2Body_SetTransform(bodyId, b2Vec2{ boxPosX / SCALE, boxPosY / SCALE }, rotation);
		b2Polygon newBox = b2MakeBox(boxHalfWidth / SCALE, boxHalfHeight / SCALE);
		b2Shape_SetPolygon(shapeId, &newBox);
		b2Shape_SetFriction(shapeId, friction);
		b2Shape_SetRestitution(shapeId, restitution);
	}
}

void InvisiblePhysicsBody::Update(float dt)
{
}

void InvisiblePhysicsBody::Draw(sf::RenderWindow& window)
{
}

void InvisiblePhysicsBody::SetBoxSize(float width, float height)
{
	boxHalfWidth = width;
	boxHalfHeight = height;
}

void InvisiblePhysicsBody::SetBoxPos(float x, float y)
{
	boxPosX = x;
	boxPosY = y;
}

void InvisiblePhysicsBody::SetBoxFactor(float f, float r)
{
	friction = f;
	restitution = r;
}
