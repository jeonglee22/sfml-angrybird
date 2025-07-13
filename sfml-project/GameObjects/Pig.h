#pragma once
#include "SpriteGo.h"
class Pig : public SpriteGo
{
protected:
	b2BodyDef bodyDef;
	b2BodyId bodyId;
	float collisionRadius;

	bool setBody = false;

	sf::Vector2f initPos = { 0.f, 0.f };
	sf::Vector2f texSize;

	int hp = 0;
	int maxHp = 100;

public:
	Pig(const std::string& texPlayerId, const std::string& name = "");
	virtual ~Pig() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInitPos(const sf::Vector2f& pos) { initPos = pos; }
	void SetTransform();
};

