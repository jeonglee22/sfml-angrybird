#include "stdafx.h"
#include "SceneStart.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneStart::SceneStart()
	: Scene(SceneIds::Start)
{
}

void SceneStart::Init()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	texIds.push_back("graphics/startImage.png");

	fontIds.push_back("fonts/angrybirds-regular.ttf");

	soundIds.push_back("Sounds/Music/main_theme.mp3");

	AddGameObject(new SpriteGo("graphics/startImage.png"));
	text = (TextGo*)AddGameObject(new TextGo("fonts/angrybirds-regular.ttf"));
	text->SetOrigin(Origins::MC);
	text->SetFillColor(sf::Color::Black);
	text->GetText().setOutlineColor(sf::Color::White);
	text->GetText().setOutlineThickness(5.f);
	text->SetString("Click to Start!!");
	text->SetCharacterSize(60);

	Scene::Init();
}

void SceneStart::Enter()
{
	uiView.setSize(initViewSize);
	uiView.setCenter(initViewPos);
	worldView.setSize(initViewSize);
	worldView.setCenter(initViewPos);

	Scene::Enter();

	SOUND_MGR.PlayBgm(SOUNDBUFFER_MGR.Get("Sounds/Music/main_theme.mp3"));
	SOUND_MGR.SetBgmVolume(30.f);

	text->SetPosition(initViewPos + sf::Vector2f(0.f, 300.f));
}

void SceneStart::Update(float dt)
{
	Scene::Update(dt);

	viewTime += dt;
	if (viewTime >= viewTimeMax)
	{
		text->SetActive(!text->GetActive());
		viewTime = 0.f;
	}
	if (InputMgr::GetAnyKeyDown())
		SCENE_MGR.ChangeScene(SceneIds::ChooseStage);
}