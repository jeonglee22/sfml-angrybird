#pragma once
#include "Scene.h"
#include "rapidcsv.h"

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
	Button* undo = nullptr;
	Button* save = nullptr;
	Button* load = nullptr;

	std::vector<SpriteGo*> spriteInserts;
	std::vector<int> HpList;
	int choosedSpriteHp = -1;
	int spriteCount = 0;
	int blockCount = 0;
	int pigCount = 0;
	int birdCount = 0;

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

	static int mapNumber;

public:
	SceneEditor();
	~SceneEditor() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void ViewControl(const sf::Vector2f& mousePos);
	void ViewClamp();
	rapidcsv::Document SaveFile();
	void SaveField();
	void LoadField();
	void LoadFile(const std::string& fileName);
	std::string tostring(wchar_t* str);
};

