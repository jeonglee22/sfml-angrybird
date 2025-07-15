#pragma once
#include "PhysicsBody.h"
class Bird : public PhysicsBody
{
public:
	enum class BirdType
	{
		None = -1,
		Original,
		Yellow,

		TypeCount,
	};
protected:
	float collisionRadius;

	bool isShoot = false;
	bool isCharging = false;
	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;
	float chargeDistance;

	float minCharge = 30.f;
	float maxCharge = 70.f;
	float forceAmount = 700.f;

	sf::Vector2f shootPos = { 150.f / SCALE, 570.f / SCALE };

	bool isRestart = false;

public:
	Bird(const std::string& texPlayerId = "", const std::string& name = "");
	virtual ~Bird() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	b2BodyId GetBodyId() { return bodyId; }
	b2ShapeId GetShapeId() { return shapeId; }
	b2BodyDef GetBodyDef() { return bodyDef; }
	bool GetShoot() { return isShoot; }
	float GetMaxCharge() { return maxCharge; }
	float GetMinCharge() { return minCharge; }
	float GetCollisionRadius() { return collisionRadius; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }

	void SetBirdEnable() {b2Body_Enable(bodyId);}
	void SetDisable() { b2Body_Disable(bodyId); }
	void SetShoot(bool b) { isShoot = b; }
	void SetRestart(bool re) { isRestart = re; }

	bool CheckBirdOut();

	void SetStartPos();
	void SetShootingState();
	void SetInitPos();
};

