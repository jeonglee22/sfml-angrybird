#pragma once
#include "SpriteGo.h"
class Bird : public SpriteGo
{
protected:
	b2BodyDef bodyDef;
	b2BodyId bodyId;
	float collisionRadius;

	bool setBody = false;

	bool isShoot = false;
	bool isCharging = false;
	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;

	float minCharge = 30.f;
	float maxCharge = 70.f;
	float forceAmount = 1200.f;

	sf::Vector2f initPos = { 150.f, 550.0f };

public:
	Bird(const std::string& texPlayerId = "", const std::string & name = "");
	virtual ~Bird() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	b2BodyId GetBodyId() { return bodyId; }
	b2BodyDef GetBodyDef() { return bodyDef; }
	bool GetShoot() { return isShoot; }
	void SetShoot(bool b) { isShoot = b; }
	float GetCollisionRadius() { return collisionRadius; }

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};

