#pragma once
#include "GameObject.h"
#include "SpriteGo.h"

class BackGround : public GameObject
{
protected:
	sf::Sprite mainbody;
	std::string texId1;
	std::string texId2;

	std::vector<SpriteGo*> backgrounds;
	sf::Vector2f backgroundsPos = FRAMEWORK.GetWindowSizeF() * 0.5f;
	int backgroundCount = 3;

public:
	BackGround(const std::string& texId1 = "",const std::string& texId2 = "", const std::string& name = "");
	virtual ~BackGround() = default;

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

