#pragma once
#include "GameObject.h"
#include "Physics.h"
#include "HitBox.h"

class Block;

class Ball :
    public GameObject
{
protected:
	sf::CircleShape body;
	HitBox hitBox;

	bool isShoot = false;
	bool isCollision = false;

	float restitution = 0.f;

	Block* block = nullptr;
	Ball* ball2= nullptr;

public:
	Ball(const std::string& name = "");
	virtual ~Ball() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::CircleShape& GetBody() { return body; }

	void SetShoot(bool b) { isShoot = b; }
	bool GetShoot() { return isShoot; }
	void SetDirection(const sf::Vector2f& dir) { direction = dir; }
	sf::Vector2f GetDirection() { return direction; }
	void SetVelocity(float s) { speed = s; }
	float GetVelocity() { return speed; }
	float GetRadius() { return body.getRadius(); }

	void SetColor(sf::Color c) { body.setFillColor(c); }
};

