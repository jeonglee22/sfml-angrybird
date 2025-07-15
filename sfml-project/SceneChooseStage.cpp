#include "stdafx.h"
#include "SceneChooseStage.h"
#include "Button.h"

SceneChooseStage::SceneChooseStage()
	: Scene(SceneIds::ChooseStage)
{
}

void SceneChooseStage::Init()
{
	texIds.push_back("graphics/startbutton.png");

	for (int i = 0; i < buttonCount; i++)
	{
		buttons.push_back((Button*)AddGameObject(new Button("graphics/startbutton.png")));
		buttons[i]->SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	}

	Scene::Init();
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