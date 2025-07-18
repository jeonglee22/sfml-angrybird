#pragma once
#include "GameObject.h"
#include "TextGo.h"

class TextGo;
class Button;
class SpriteGo;

class GameResult : public GameObject
{
public:
	enum class EndType
	{
		GameOver,
		GameClear
	};
protected:
	sf::RectangleShape body;
	sf::RectangleShape side;

	TextGo* gameText = nullptr;
	Button* home = nullptr;
	Button* restart = nullptr;
	Button* next = nullptr;

	std::vector<SpriteGo*> laughSprites;

	sf::Vector2f homeButtonPos = { -150.f, 250.f };
	sf::Vector2f restartButtonPos = {0.f, 250.f};
	sf::Vector2f nextButtonPos = {150.f, 250.f};
	sf::Vector2f textPos = {0.f, -200.f};
	sf::Vector2f laughSpritePosCenter = {0.f, 0.f};

	bool isClear;

public:
	GameResult(const std::string& name = "");
	virtual ~GameResult() = default;

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

	void SetTextString(const std::string& str) { gameText->SetString(str); }
	void ShowResult();
	void SetClear(bool b) { isClear = b; }
	bool GetClear() const { return isClear; }
};

