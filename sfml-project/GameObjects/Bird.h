#pragma once
#include "SpriteGo.h"
class Bird : public SpriteGo
{
protected:
	b2BodyDef bodyDef;
	b2BodyId bodyId;
	b2ShapeId bodyShape;
	float collisionRadius;

	bool setBody = false;

	bool isShoot = false;
	bool isCharging = false;
	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;

	float minCharge = 30.f;
	float maxCharge = 70.f;
	float forceAmount = 700.f;

	sf::Vector2f initPos = { 80.f, 660.0f };
	sf::Vector2f shootPos = { 150.f, 560.f };

	bool canShoot = true;

public:
	Bird(const std::string& texPlayerId = "", const std::string & name = "");
	virtual ~Bird() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	b2BodyId GetBodyId() { return bodyId; }
	b2ShapeId GetShapeId() { return bodyShape; }
	b2BodyDef GetBodyDef() { return bodyDef; }
	bool GetShoot() { return isShoot; }
	void SetShoot(bool b) { isShoot = b; }
	float GetCollisionRadius() { return collisionRadius; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }

	void SetTransform();
	void SetBirdEnable() { 
		b2Body_Enable(bodyId);
		Reset();
		SetTransform();
	}
	void SetDisable() { b2Body_Disable(bodyId); }

	bool CheckBirdStop() { 
		return b2Body_GetLinearVelocity(bodyId).x <= std::numeric_limits<float>::epsilon() &&
			b2Body_GetLinearVelocity(bodyId).y <= std::numeric_limits<float>::epsilon();
	}
};

