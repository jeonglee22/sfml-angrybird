#pragma once
#include "GameObject.h"
#include "HitBox.h"

class Block : public GameObject
{
protected:
	sf::RectangleShape body;

	HitBox hitBox;

public:
	Block(const std::string& name = "");
	virtual ~Block() = default;

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

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}
	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	HitBox& GetHitBox() { return hitBox; }
	void SetSize(const sf::Vector2f& size) { body.setSize(size); }

};

