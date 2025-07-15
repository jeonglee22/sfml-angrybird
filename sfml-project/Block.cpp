#include "stdafx.h"
#include "Block.h"

Block::Block(const std::string& texId, const std::string& name)
	: PhysicsBody(Type::Block, texId, name)
{
}

void Block::Init()
{
	PhysicsBody::Init();
}

void Block::Release()
{
	PhysicsBody::Release();

	b2DestroyBody(bodyId);
	bodyId = b2_nullBodyId;
}

void Block::Reset()
{
	PhysicsBody::Reset();

	hp = maxHp;
}

void Block::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Block::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Block::TakeDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, maxHp);
	if (hp == 0)
	{
		isDead = true;
	}
}
