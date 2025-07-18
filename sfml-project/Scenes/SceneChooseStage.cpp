#include "stdafx.h"
#include "SceneChooseStage.h"
#include "Button.h"
#include "SpriteGo.h"

SceneChooseStage::SceneChooseStage()
	: Scene(SceneIds::ChooseStage)
{
}

void SceneChooseStage::Init()
{
	texIds.push_back("graphics/image_level_available.png");
	texIds.push_back("graphics/image_level_selector1.png");
	texIds.push_back("graphics/image_level_blocked.png");

	fontIds.push_back("fonts/angrybirds-regular.ttf");

	AddGameObject(new SpriteGo("graphics/image_level_selector1.png"));

	for (int i = 0; i < buttonCount; i++)
	{
		stageButtons.push_back((Button*)AddGameObject(new Button("graphics/image_level_available.png")));
		blockSprites.push_back((SpriteGo*)AddGameObject(new SpriteGo("graphics/image_level_blocked.png")));
		sf::Vector2f pos = FRAMEWORK.GetWindowSizeF() * 0.5f + sf::Vector2f(((i % 5) - 2) * 200.f, (i / 5 - 1) * 200.f);
		stageButtons[i]->SetPosition(pos);
		blockSprites[i]->SetOrigin(Origins::MC);
		blockSprites[i]->sortingLayer = SortingLayers::UI;
		blockSprites[i]->sortingOrder = 1;
		blockSprites[i]->SetPosition(pos);
	}
	blockSprites[0]->SetActive(false);

	Scene::Init();

	for (int i = 0; i < buttonCount; i++)
	{
		stageButtons[i]->SetTextString(std::to_string(i + 1));
		stageButtons[i]->SetTextColor(sf::Color::Black);
		stageButtons[i]->SetTextPosition({ 0.f,0.f });
		stageButtons[i]->SetTextSize(20);
		auto func = [this, i]() {
			if(!blockSprites[i]->GetActive())
			{
				stageButtons[i]->SetInitState();
				SCENE_MGR.SetStageSelect(i + 1);
				SCENE_MGR.ChangeScene(SceneIds::Stage);
			}
		};
		stageButtons[i]->SetButtonFunc(func);
		stageButtons[i]->SetActive(false);
	}
	stageButtons[0]->SetActive(true);
}

void SceneChooseStage::Enter()
{
	uiView.setSize(initViewSize);
	uiView.setCenter(initViewPos);
	worldView.setSize(initViewSize);
	worldView.setCenter(initViewPos);

	Scene::Enter();
}

void SceneChooseStage::Update(float dt)
{
	Scene::Update(dt);
}