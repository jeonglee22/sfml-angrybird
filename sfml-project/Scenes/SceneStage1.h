#pragma once
#include "Scene.h"
class SceneStage1 : public Scene
{
protected:

public:
	SceneStage1();
	~SceneStage1() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

