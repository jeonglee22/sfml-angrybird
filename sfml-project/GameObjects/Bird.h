#pragma once
#include "SpriteGo.h"
class Bird : public SpriteGo
{
protected:
	b2BodyDef bodyDef;
	b2BodyId bodyId;


public:
	Bird(const std::string& texPlayerId = "", const std::string & name = "");
	virtual ~Bird() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

