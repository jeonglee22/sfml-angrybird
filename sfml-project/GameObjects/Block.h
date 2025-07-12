#pragma once
#include "SpriteGo.h"
class Block : public SpriteGo
{
protected:
	b2BodyDef bodyDef;
	b2BodyId bodyId;

	bool setBody = false;

	sf::Vector2f initPos;
	sf::Vector2f texSize;

public:
	Block(const std::string& texPlayerId, const std::string& name = "");
	virtual ~Block() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetInitPos(const sf::Vector2f& pos) { initPos = pos; }
	void SetTransform();
};

