#pragma once
#include "Scene.h"
class SceneTest : public Scene
{

protected:
	sf::CircleShape ball;
	sf::RectangleShape start;
	sf::RectangleShape ground;

	sf::Vector2f direction;
	float velocity;

	bool isShoot;
	sf::Vector2i mouseStart;
	sf::Vector2i mouseEnd;

	float COR = 0.3f;

public:
	SceneTest();
	~SceneTest() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

