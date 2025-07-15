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
	ShootCountUI* countUI = nullptr;

	std::vector<Bird*> birds;
	std::vector<Block*> blocks;
	std::vector<Pig*> pigs;
	int blockCount = 5;
	int pigCount = 5;

	int tryCount = 0;
	int tryMax = 5;

	int subStepCount = 4;
	float timeStep = 1.0f / 60.0f;
	float timeValue = 0.f;

	float viewResetMax = 2.0f;
	float viewReset = 0.f;

	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;

	sf::Vector2f initViewPos = FRAMEWORK.GetWindowSizeF() * 0.5f;
	sf::Vector2f initViewSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f currentViewPos;
	sf::Vector2f currentViewSize;

	bool isShoot = false;
	bool birdReady = true;
	bool isViewMoving = false;

public:
	SceneStage1();
	~SceneStage1() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool GetViewMoving() { return isViewMoving; }

	void LoadBlockInfo(const std::string& filePath);
	void CheckPhysicsBodyCollision();
	void CheckObjectsDead();
	void ObjectsReset();

	void ViewControl(const sf::Vector2f& mousePos);
	void Restart();
};

