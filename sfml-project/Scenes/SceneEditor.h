#pragma once
#include "Scene.h"

class BackGround;
class EditBoxUI;
class SpriteGo;
class RectGo;
class Button;

class SceneEditor : public Scene
{
protected:
	BackGround* background = nullptr;
	EditBoxUI* boxUI = nullptr;
	RectGo* objectBound = nullptr;
	SpriteGo* spriteChoosed = nullptr;
	Button* redo = nullptr;

	std::vector<SpriteGo*> spriteInserts;
	int spriteCount = 0;

	sf::Vector2f initViewPos = { FRAMEWORK.GetWindowSizeF().x ,FRAMEWORK.GetWindowSizeF().y * 0.5f};
	sf::Vector2f initViewSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f currentViewPos;
	sf::Vector2f currentViewSize;
	sf::Vector2f minViewSize = { FRAMEWORK.GetWindowRatio() * 600.f , 600.f };
	sf::Vector2f maxViewSize = { FRAMEWORK.GetWindowRatio() * 1568.f , 1568.f };

	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;

	sf::FloatRect backgroundSize;

	float viewReset;

	bool isChoosed = false;

public:
	SceneEditor();
	~SceneEditor() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void ViewControl(const sf::Vector2f& mousePos);
	void ViewClamp();
};

