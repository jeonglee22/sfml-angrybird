#pragma once
#include "Scene.h"

class SpriteGo;
class Bird;
class Block;

class SceneStage1 : public Scene
{
protected:
	b2BodyDef groundBody = b2DefaultBodyDef();
	b2ShapeDef groundShapeDef;
	b2BodyId groundBodyId;
	b2BodyDef shootBody = b2DefaultBodyDef();
	b2ShapeDef shootShapeDef;
	b2BodyId shootBodyId;

	SpriteGo* background;
	Bird* bird;

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

