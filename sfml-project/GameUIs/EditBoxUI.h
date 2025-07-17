#pragma once
#include "GameObject.h"
#include "SpriteGo.h"

class Button;
class Scene;

class EditBoxUI : public GameObject
{
public:
	enum class Plate
	{
		Pig,
		Block,
	};

protected:
	sf::RectangleShape body;
	sf::RectangleShape plate;
	sf::RectangleShape scrollBox;
	sf::RectangleShape aboveplate;
	sf::RectangleShape belowplate;

	std::vector<SpriteGo*> blocks;
	std::vector<sf::Vector2f> blocksInitPos;
	std::vector<int> blockHPs;
	std::vector<SpriteGo*> pigs;
	std::vector<sf::Vector2f> pigsInitPos;
	std::vector<int> pigHPs;

	Button* blockButton;
	Button* pigButton;

	Scene* scene;

	sf::Vector2f bodySize = { 500.f, FRAMEWORK.GetWindowSizeF().y };
	sf::Vector2f bodyPos = {FRAMEWORK.GetWindowSizeF().x - bodySize.x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f};
	sf::Vector2f blockButtonPos = { -100.f, -FRAMEWORK.GetWindowSizeF().y * 0.5f + 70.f };
	sf::Vector2f pigButtonPos = { 100.f, -FRAMEWORK.GetWindowSizeF().y * 0.5f + 70.f };
	sf::Vector2f platePos = { 0.f, 50.f };
	sf::Vector2f abovePlatePos = { 0.f, -bodySize.y * 0.4f - 25.f };
	sf::Vector2f belosePlatePos = { 0.f, 50.f };
	sf::Vector2f blockinterval = { 150.f,100.f };
	sf::Vector2f objectsCenterPos = {0.f,0.f};
	sf::Vector2f scrollSize = { 30.f, 50.f };
	sf::Vector2f scrollPos = {bodySize.x * 0.5f - 5.f, -bodySize.y * 0.3f};

	int blockCount = 18;
	int pigCount = 10;
	Plate currentPlate;

	float minBlockYScroll;
	float minPigYScroll;
	float maxYScroll = 0.f;

	float scrollBoxYMin = bodyPos.y-bodySize.y * 0.3f;
	float scrollBoxYMax = bodySize.y - scrollSize.y * 0.5f;

	bool isScrollMove;

public:
	EditBoxUI(const std::string& name = "");
	virtual ~EditBoxUI() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	std::vector<int> GetBlockHPs() const { return blockHPs; }
	std::vector<int> GetPigHPs() const { return pigHPs; }

	SpriteGo* GetMousePosSprite(int &hp);
	sf::RectangleShape GetBody() const { return body; }
	void AddBlockTypes(const std::string& filePath);
	void AddPigTypes(const std::string& filePath);

	void AddAllObjectsPosition();
	void ResetObjectsInitPosition();
};

