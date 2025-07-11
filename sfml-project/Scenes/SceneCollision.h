#pragma once
#include "Scene.h"

class Block;
class Ball;

class SceneCollision : public Scene
{
protected:
	sf::RectangleShape ground;
	Ball* ball;
	Block* block;
	sf::RectangleShape start;

	bool isShoot;
	sf::Vector2i mouseStart;
	sf::Vector2i mouseEnd;

	float COR = 0.3f;

public:
	SceneCollision();
	~SceneCollision() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

