#pragma once
#include "Scene.h"

class SpriteGo;
class Bird;
class Block;
class Pig;
class ShootCountUI;
class PhysicsBody;
class ShootStand;
class BackGround;

class SceneStage1 : public Scene
{
protected:
	PhysicsBody* ground = nullptr;
	PhysicsBody* leftWall = nullptr;
	PhysicsBody* rightWall = nullptr;
	ShootStand* shootStand = nullptr;
	ShootCountUI* countUI = nullptr;
	BackGround* background = nullptr;

	std::vector<Bird*> birds;
	std::vector<Block*> blocks;
	std::vector<Pig*> pigs;

	int blockCount = 0;
	int pigCount = 0;
	int objCount = 0;
	int birdCount = 0;

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
	sf::Vector2f minViewSize = { FRAMEWORK.GetWindowRatio() * 600.f , 600.f };
	sf::Vector2f maxViewSize = { FRAMEWORK.GetWindowRatio() * 1568.f , 1568.f };

	bool isShoot = false;
	bool birdReady = true;
	bool isViewMoving = false;
	bool isZoomOut = false;
	bool isZoomIn = false;

	sf::FloatRect backgroundSize;

public:
	SceneStage1();
	~SceneStage1() = default;

	void Init() override;
	void Exit() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool GetViewMoving() { return isViewMoving; }

	void LoadBlockInfo(const std::string& filePath);
	void CheckPhysicsBodyCollision();
	void CheckObjectsDead();
	void ObjectsReset();
	void SetObjectTransform();
	void DeleteObjects();

	void ViewControl(const sf::Vector2f& mousePos);
	void ViewReset(float dt);
	void ViewFollowing(float dt);
	void ViewClamp();
	void Restart();

	void ZoomIn(float dt);
	void ZoomOut(float dt);
};

