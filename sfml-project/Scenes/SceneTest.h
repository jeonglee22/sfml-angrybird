#pragma once
#include "Scene.h"
class SceneTest : public Scene
{

protected:
	sf::CircleShape ball;
	sf::RectangleShape box;
	sf::RectangleShape start;
	sf::RectangleShape ground;

	b2BodyDef groundBody = b2DefaultBodyDef();
	b2ShapeDef groundShapeDef;
	b2BodyId groundBodyId;

	b2BodyDef bodyDef;
	b2BodyId bodyId;

	int subStepCount = 4;
	float timeStep = 1.0f / 60.0f;
	float timeValue = 0.f;

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
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

