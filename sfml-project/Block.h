#pragma once
#include "PhysicsBody.h"
class Block : public PhysicsBody
{
protected:
	int hp = 0;
	int maxHp = 100;
	bool isDead = false;

public:
	Block(const std::string& texId = "", const std::string& name = "");
	virtual ~Block() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	b2ShapeId GetShapeId() { return shapeId; }
	int GetHp() { return hp; }

	void SetInitPos(const sf::Vector2f& pos) { SetBoxPos(pos.x, pos.y); }
	void SetDisable() { b2Body_Disable(bodyId); }
	void SetEnable() { b2Body_Enable(bodyId); }
	void SetHP(int hp) { maxHp = hp; }

	void TakeDamage(int damage);

	bool IsDead() { return isDead; }
	void SetNotDead() { isDead = false; }
};

