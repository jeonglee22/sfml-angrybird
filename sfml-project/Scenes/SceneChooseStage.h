#pragma once
#include "Scene.h"

class Button;

class SceneChooseStage :
    public Scene
{
protected:
	std::vector<Button*> buttons;
	int buttonCount = 1;

	sf::Vector2f initViewPos = FRAMEWORK.GetWindowSizeF() * 0.5f;
	sf::Vector2f initViewSize = FRAMEWORK.GetWindowSizeF();

public:
	SceneChooseStage();
	~SceneChooseStage() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

