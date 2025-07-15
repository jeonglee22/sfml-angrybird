#include "stdafx.h"
#include "SceneStart.h"
#include "SpriteGo.h"

SceneStart::SceneStart()
	: Scene(SceneIds::Start)
{
}

void SceneStart::Init()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	texIds.push_back("graphics/startImage.png");

	AddGameObject(new SpriteGo("graphics/startImage.png"));

	Scene::Init();
}

void SceneStart::Enter()
{
	uiView.setSize(initViewSize);
	uiView.setCenter(initViewPos);
	worldView.setSize(initViewSize);
	worldView.setCenter(initViewPos);

	Scene::Enter();
}

void SceneStart::Update(float dt)
{
	Scene::Update(dt);

	viewTime += dt;
	if (viewTime >= viewTimeMax)
	{
		SCENE_MGR.ChangeScene(SceneIds::Stage1);
	}
}