#pragma once
#include "GameObject.h"
class RectGo : public GameObject
{
protected:
	sf::RectangleShape rect;
	sf::Vector2f rectSize;
	sf::Color color;

public:
	RectGo(const std::string& name = "");
	virtual ~RectGo() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	void SetSize(const sf::Vector2f& s);
	void SetColor(const sf::Color& c);

	sf::RectangleShape GetRect() const { return rect; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

