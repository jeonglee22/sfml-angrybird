#pragma once
#include "SpriteGo.h"
class Button : public SpriteGo
{
protected:
	std::function<void()> func;

	bool isClicked = false;

	sf::Uint8 originAlpha;

public:
	Button(const std::string& texId = "", const std::string& name = "");
	virtual ~Button() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() { return sprite.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};

