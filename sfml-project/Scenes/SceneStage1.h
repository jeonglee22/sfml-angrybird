#pragma once
#include "Scene.h"

class SpriteGo;
class Bird;
class Block;
class Pig;

class SceneStage1 : public Scene
{
protected:
	b2BodyDef groundBodyDef = b2DefaultBodyDef();
	b2ShapeDef groundShapeDef;
	b2BodyId groundBodyId;
	b2BodyDef standBodyDef = b2DefaultBodyDef();
	b2ShapeDef standShapeDef;
	b2BodyId standBodyId;

	SpriteGo* background;
	std::vector<SpriteGo*> shootStand;
	SpriteGo* shootStandRight;
	SpriteGo* shootStandLeft;
	Bird* bird;
	Pig* pig;

	std::vector<Block*> blocks;
	int blockCount = 3;

	int subStepCount = 4;
	float timeStep = 1.0f / 60.0f;
	float timeValue = 0.f;

public:
	SceneStage1();
	~SceneStage1() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

