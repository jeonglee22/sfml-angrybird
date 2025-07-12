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

	bodyDef.type = b2_dynamicBody;
}

void Bird::Release()
{
	SpriteGo::Release();
}

void Bird::Reset()
{
	SpriteGo::Reset();

	SetPosition({ (FRAMEWORK.GetWindowSizeF().x * 0.5f + 15.f), 50.0f});
	SetRotation(0.f);
	bodyDef.position = b2Vec2{ GetPosition().x / SCALE, GetPosition().y / SCALE };
	bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

	b2Circle circleBox;
	circleBox.center = { 0.f,0.f };
	circleBox.radius = sprite.getTexture()->getSize().x * 0.5 / SCALE;

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.material.friction = 0.2f;
	shapeDef.material.rollingResistance = 0.1f;
	shapeDef.material.restitution = 0.5f;
	b2CreateCircleShape(bodyId, &shapeDef, &circleBox);
}

void Bird::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Bird::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}