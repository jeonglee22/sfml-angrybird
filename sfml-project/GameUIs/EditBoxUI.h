#pragma once
#include "GameObject.h"
#include "SpriteGo.h"

class Button;

class EditBoxUI : public GameObject
{
protected:
	sf::RectangleShape body;
	sf::RectangleShape plate;
	std::vector<SpriteGo*> blocks;
	std::vector<SpriteGo*> pigs;
	Button* blockButton;
	Button* pigButton;

	sf::Vector2f bodySize = { 500.f, FRAMEWORK.GetWindowSizeF().y };
	sf::Vector2f bodyPos = {FRAMEWORK.GetWindowSizeF().x - bodySize.x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f};
	sf::Vector2f blockButtonPos = { -100.f, -FRAMEWORK.GetWindowSizeF().y * 0.5f + 70.f };
	sf::Vector2f pigButtonPos = { 100.f, -FRAMEWORK.GetWindowSizeF().y * 0.5f + 70.f };
	sf::Vector2f platePos = { 0.f, 50.f };
	sf::Vector2f blockinterval = { 150.f,100.f };

	int blockCount = 18;
	int pigCount = 10;

public:
	EditBoxUI(const std::string& name = "");
	virtual ~EditBoxUI() = default;

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

	SpriteGo* GetMousePosSprite();
	sf::RectangleShape GetBody() const { return body; }
};

