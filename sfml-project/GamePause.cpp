#include "stdafx.h"
#include "GamePause.h"
#include "Button.h"

GamePause::GamePause(const std::string& name)
	: GameObject(name)
{
}

void GamePause::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void GamePause::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void GamePause::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void GamePause::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void GamePause::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void GamePause::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	body.setFillColor(sf::Color::Black);
	body.setSize({ FRAMEWORK.GetWindowSizeF().x * 0.1f,FRAMEWORK.GetWindowSizeF().y });
	SetOrigin(Origins::MC);

	side.setFillColor(sf::Color(0, 0, 0, 150));
	side.setSize(FRAMEWORK.GetWindowSizeF());
	side.setOrigin(FRAMEWORK.GetWindowSizeF() * 0.5f);

	home = new Button("graphics/Home.png", "Home");
	home->Init();
	auto homeFunc = [this]() {
		home->SetInitState();
		SetActive(false);
		SCENE_MGR.ChangeScene(SceneIds::ChooseStage);
		FRAMEWORK.SetTimeScale(1.f);
		};
	home->SetButtonFunc(homeFunc);

	restart = new Button("graphics/Replay.png", "Replay");
	restart->Init();
	auto restartFunc = [this]() {
		restart->SetInitState();
		SetActive(false);
		SCENE_MGR.ChangeScene(SceneIds::Stage);
		FRAMEWORK.SetTimeScale(1.f);
		};
	restart->SetButtonFunc(restartFunc);
}

void GamePause::Release()
{
}

void GamePause::Reset()
{
	SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.05f,FRAMEWORK.GetWindowSizeF().y * 0.5f});
	side.setPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);

	home->SetPosition(position + homeButtonPos);
	home->SetScale({ 0.7f,0.7f });
	home->Reset();

	restart->SetPosition(position + restartButtonPos);
	restart->SetScale({ 0.7f,0.7f });
	restart->Reset();
}

void GamePause::Update(float dt)
{
	home->Update(dt);
	restart->Update(dt);
}

void GamePause::Draw(sf::RenderWindow& window)
{
	window.draw(side);
	window.draw(body);
	home->Draw(window);
	restart->Draw(window);
}