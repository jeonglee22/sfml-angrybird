#pragma once
#include "PhysicsBody.h"
class Bird : public PhysicsBody
{
public:
	enum class BirdType
	{
		None = -1,
		Red,
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
	float forceAmount = 1000.f;
	float flyingDirection = 1.f;
	float despawnTimeMax = 3.f;
	float despawnTime = 0.f;

	BirdType birdType;

	sf::Vector2f shootPos = { 50.f / SCALE, 570.f / SCALE };

	bool isRestart = false;
	bool isUseAbility = true;

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
	bool GetCharging() { return isCharging; }
	float GetMaxCharge() { return maxCharge; }
	float GetMinCharge() { return minCharge; }
	float GetCollisionRadius() { return collisionRadius; }
	float GetFlyingDirection() { return flyingDirection; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }

	void SetBirdEnable() {b2Body_Enable(bodyId);}
	void SetDisable() { b2Body_Disable(bodyId); }
	void SetShoot(bool b) { isShoot = b; }
	void SetRestart(bool re) { isRestart = re; }
	void SetAbilityUse(bool b) { isUseAbility = b; }

	bool CheckFinishShoot();

	void SetStartPos();
	void SetShootingState();
	void SetInitPos();
	void SetInitPos(const sf::Vector2f& initPos);

	void UseAbility();
};

