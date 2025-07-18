#pragma once
#include "PhysicsBody.h"
class Pig : public PhysicsBody
{
protected:
	float collisionRadius;

	int hp = 0;
	int maxHp = 100;
	bool isDead = false;

public:
	Pig(const std::string& texId, const std::string& name = "");
	virtual ~Pig() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	b2ShapeId GetShapeId() { return shapeId; }
	int GetHp() { return hp; }

	void SetInitPos(const sf::Vector2f& pos) { SetBoxPos(pos.x, pos.y); }
	void SetHP(int hp) { maxHp = hp; }

	void TakeDamage(int damage);

	bool IsDead() { return isDead; }
	void SetNotDead() { isDead = false; }
};

