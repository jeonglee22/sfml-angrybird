#pragma once
#include "Scene.h"

class Button;
class SpriteGo;

class SceneChooseStage : public Scene
{
public:
	enum class ButtonType
	{
		start,
		home,
		editor,
	};
protected:
	SpriteGo* background = nullptr;
	Button* edit = nullptr;

	std::vector<Button*> stageButtons;
	std::vector<SpriteGo*> blockSprites;
	int buttonCount = 15;

	int clearedMaps = 1;

	sf::Vector2f initViewPos = FRAMEWORK.GetWindowSizeF() * 0.5f;
	sf::Vector2f initViewSize = FRAMEWORK.GetWindowSizeF();

public:
	SceneChooseStage();
	~SceneChooseStage() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;

	void GoEditScene();
};