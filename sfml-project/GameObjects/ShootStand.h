#pragma once
#include "PhysicsBody.h"

class SpriteGo;
class Bird;

class ShootStand : public PhysicsBody
{
public:
	enum class Part
	{
		Left,
		Right,
		Body,

		PartCount
	};

protected:
	SpriteGo* leftBody = nullptr;
	SpriteGo* rightBody = nullptr;
	std::vector<SpriteGo*> Band;
	Bird* bird = nullptr;

	sf::Vector2f bodyPos = { 150.f, 685.f };
	sf::Vector2f leftBodyPos = {9.f,-140.f};
	sf::Vector2f rightBodyPos = { -7.f,-135.f };
	sf::Vector2f bandBodyPos = {0.f,-115.f};
	sf::Vector2f leftBandPos = {-25.f,-115.f};
	sf::Vector2f rightBandPos = {15.f,-115.f};

	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;

	bool isShoot = false;

public:
	ShootStand(const std::string& name = "");
	~ShootStand() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	SpriteGo* GetLeftPart() { return leftBody; }
	SpriteGo* GetRightPart() { return rightBody; }
	std::vector<SpriteGo*> GetBandPart() { return Band; }

	void SetBandActive(bool b);
	void SetLeftBandRotation(float r);
	void SetRightBandRotation(float r);
	void SetBodyBandRotation(float r);
	void SetLeftBandScale(float s);
	void SetRightBandScale(float s);
	void SetBandPos(const sf::Vector2f& pos);
	void SetBird(Bird* bird) { this->bird = bird; }

	sf::Vector2f GetLeftBandPos() { return Band[(int)Part::Left]->GetPosition(); }
	sf::Vector2f GetRightBandPos() { return Band[(int)Part::Right]->GetPosition(); }
	sf::Vector2f GetBodyBandPos() { return Band[(int)Part::Body]->GetPosition(); }
	void ResetBandPos();
};

