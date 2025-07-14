#pragma once
#include "PhysicsBody.h"

class SpriteGo;

class ShootStand : public PhysicsBody
{
protected:
	SpriteGo* leftBody;
	SpriteGo* rightBody;

	sf::Vector2f beforeShootPos = { 150.f / SCALE, 660.f / SCALE };
	sf::Vector2f afterShootPos = { 150.f / SCALE, 700.f / SCALE };

public:
	ShootStand(const std::string& name = "");
	~ShootStand() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	void ChangeToAfterPos();
	void ChangeToBeforePos();
	SpriteGo* GetLeftPart() { return leftBody; }
	SpriteGo* GetRightPart() { return rightBody; }
};

