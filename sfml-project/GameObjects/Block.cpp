#include "stdafx.h"
#include "Block.h"

Block::Block(const std::string& texPlayerId, const std::string& name)
	: SpriteGo(texPlayerId,name)
{
}

void Block::Init()
{
	SpriteGo::Init();

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;

	//initPos = sf::Vector2f{ , };

	SetOrigin(Origins::MC);
}

void Block::Release()
{
	SpriteGo::Release();

	/*b2DestroyBody(bodyId);
	bodyId = b2_nullBodyId;*/
}

void Block::Reset()
{
	SpriteGo::Reset();

	SetPosition(initPos);
	SetRotation(0.f);
	if (!setBody)
	{
		bodyDef.position = b2Vec2{ initPos.x / SCALE, initPos.y / SCALE };
		bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);
		texSize = (sf::Vector2f)sprite.getTexture()->getSize();
		b2Polygon bodyBox = b2MakeBox(texSize.x * 0.5f / SCALE, texSize.y * 0.5f / SCALE);

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 0.2f;
		shapeDef.material.friction = 0.5f;
		shapeDef.material.restitution = 0.5f;
		bodyShape = b2CreatePolygonShape(bodyId, &shapeDef, &bodyBox);
		b2Shape_EnableHitEvents(bodyShape, true);

		setBody = true;
	}
	else
	{
		b2Body_SetTransform(bodyId, b2Vec2{ 150.f / SCALE, 550.0f / SCALE }, b2Rot{ 1.f,0.f });
	}
}

void Block::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Block::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Block::SetTransform()
{
	b2Vec2 position = b2Body_GetPosition(bodyId);
	b2Rot rotation = b2Body_GetRotation(bodyId);
	SetPosition({ position.x * SCALE, position.y * SCALE });
	SetRotation(b2Rot_GetAngle(rotation) * 180 / B2_PI);
}
