#include "stdafx.h"
#include "ShootStand.h"

ShootStand::ShootStand(const std::string& name)
	:PhysicsBody(Type::ShootStand)
{
}

void ShootStand::Init()
{
	rightBody = new SpriteGo("graphics/Angrybirds/StandRight.png");
	rightBody->SetOrigin(Origins::TL);
	rightBody->SetPosition({ 143.f, 550.f });
	rightBody->SetScale({ 1.f,0.7f });
	rightBody->sortingLayer = SortingLayers::Foreground;
	rightBody->sortingOrder = -1;

	leftBody = new SpriteGo("graphics/Angrybirds/StandLeft.png");
	leftBody->SetOrigin(Origins::TR);
	leftBody->SetPosition({ 159.f, 545.f });
	leftBody->SetScale({ 1.f,0.7f });
	leftBody->sortingLayer = SortingLayers::Foreground;
	leftBody->sortingOrder = 1;
}

void ShootStand::Release()
{
	PhysicsBody::Release();
}

void ShootStand::Reset()
{
	rightBody->Reset();
	leftBody->Reset();

	sf::Vector2u standTexSize = TEXTURE_MGR.Get("graphics/Angrybirds/ShootStand.png").getSize();
	SetBoxSize(standTexSize.x * 0.2f, standTexSize.y * 0.5f * 0.7f);
	SetBoxPos(beforeShootPos.x, beforeShootPos.y);
	SetBoxFactor(0.8f, 0.5f);
	SetPosition(initPos * SCALE);
	SetRotation(0.f);

	bodyDef.position = b2Vec2{ beforeShootPos.x, beforeShootPos.y };
	bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

	b2Polygon groundBox = b2MakeBox(texSize.x, texSize.y);
	shapeDef = b2DefaultShapeDef();
	shapeDef.density = density;
	shapeDef.material.friction = friction;
	shapeDef.material.restitution = restitution;
	shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &groundBox);
}

void ShootStand::Update(float dt)
{
	PhysicsBody::Update(dt);
}

void ShootStand::Draw(sf::RenderWindow& window)
{
	PhysicsBody::Draw(window);
}

void ShootStand::ChangeToAfterPos()
{
	b2Body_SetTransform(bodyId, b2Vec2{ afterShootPos.x, afterShootPos.y }, rotation);
}

void ShootStand::ChangeToBeforePos()
{
	b2Body_SetTransform(bodyId, b2Vec2{ beforeShootPos.x, beforeShootPos.y }, rotation);
}
