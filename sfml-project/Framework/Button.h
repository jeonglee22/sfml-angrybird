#pragma once
#include "SpriteGo.h"
class Button : public SpriteGo
{
public:
	enum class Type
	{
		None = -1,
		Void,

		buttonCount,
	};
protected:
	std::function<void()> voidfunc;

	bool isClicked = false;

	Type type;

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

	void SetButtonFunc(const std::function<void()>& func) { voidfunc = func; }
	void DoFunc();
};

