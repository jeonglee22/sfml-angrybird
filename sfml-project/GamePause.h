#pragma once
#include "GameObject.h"

class Button;

class GamePause :
    public GameObject
{
protected:
	sf::RectangleShape body;
	sf::RectangleShape side;
		
	Button* home = nullptr;
	Button* restart = nullptr;

	sf::Vector2f homeButtonPos = { 0.f, -100.f };
	sf::Vector2f restartButtonPos = { 0.f, 100.f };

public:
	GamePause(const std::string& name = "");
	virtual ~GamePause() = default;

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
};

