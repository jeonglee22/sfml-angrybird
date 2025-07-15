#pragma once
#include "Scene.h"

class SpriteGo;
class Bird;
class Block;
class Pig;
class ShootCountUI;
class PhysicsBody;
class ShootStand;

class SceneStage1 : public Scene
{
protected:
	PhysicsBody* ground;
	SpriteGo* background = nullptr;
	ShootStand* shootStand;
	Pig* pig = nullptr;
	ShootCountUI* countUI = nullptr;

	std::vector<Bird*> birds;
	std::vector<PhysicsBody*> blocks;
	int blockCount = 5;

	int tryCount = 0;
	int tryMax = 5;

	int subStepCount = 4;
	float timeStep = 1.0f / 60.0f;
	float timeValue = 0.f;

	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;

	bool isShoot = false;
	bool birdReady = true;

public:
	SceneStage1();
	~SceneStage1() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void LoadBlockInfo(const std::string& filePath);
	void CheckPigCollision();
};

