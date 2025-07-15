#pragma once
#include "Scene.h"
class SceneStart : public Scene
{
protected:
	sf::Vector2f initViewPos = FRAMEWORK.GetWindowSizeF() * 0.5f;
	sf::Vector2f initViewSize = FRAMEWORK.GetWindowSizeF();

	float viewTimeMax = 2.f;
	float viewTime = 0.f;

public:
	SceneStart();
	~SceneStart() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

