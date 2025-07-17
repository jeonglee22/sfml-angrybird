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
	SpriteGo* background;
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

struct StartStage1
{
	void operator()(){
		SCENE_MGR.ChangeScene(SceneIds::Stage1);
	}
};