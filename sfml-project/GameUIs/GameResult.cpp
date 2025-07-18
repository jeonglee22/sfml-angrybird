#include "stdafx.h"
#include "GameResult.h"
#include "SpriteGo.h"
#include "Button.h"
#include "SceneStage.h"

GameResult::GameResult(const std::string& name)
	: GameObject(name)
{
}

void GameResult::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void GameResult::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void GameResult::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void GameResult::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void GameResult::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void GameResult::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	body.setFillColor(sf::Color::Black);
	body.setSize({ FRAMEWORK.GetWindowSizeF().x * 0.4f,FRAMEWORK.GetWindowSizeF().y });
	SetOrigin(Origins::MC);

	side.setFillColor(sf::Color(0,0,0,150));
	side.setSize({ FRAMEWORK.GetWindowSizeF().x,FRAMEWORK.GetWindowSizeF().y });
	side.setOrigin(sf::Vector2f( FRAMEWORK.GetWindowSizeF().x,FRAMEWORK.GetWindowSizeF().y ) * 0.5f);

	for (int i = 0; i < 3; i++)
	{
		laughSprites.push_back( new SpriteGo("graphics/PigLaugh.png"));
		laughSprites[i]->SetOrigin(Origins::MC);
		laughSprites[i]->Init();
	}

	gameText = new TextGo("fonts/angrybirds-regular.ttf");
	gameText->Init();
	gameText->SetOrigin(Origins::MC);
	gameText->SetCharacterSize(80.f);
	gameText->SetString("Game Clear!!");

	home = new Button("graphics/Home.png", "Home");
	home->Init();
	auto homeFunc = [this]() {
		if(isClear && (SCENE_MGR.GetStageSelect() == SCENE_MGR.GetStageCleared()))
			SCENE_MGR.SetStageCleared(SCENE_MGR.GetStageCleared() + 1);
		home->SetInitState();
		SetActive(false);
		SCENE_MGR.ChangeScene(SceneIds::ChooseStage);
		FRAMEWORK.SetTimeScale(1.f);
		};
	home->SetButtonFunc(homeFunc);

	restart = new Button("graphics/Replay.png", "Replay");
	restart->Init();
	auto restartFunc = [this]() {
		if(isClear && (SCENE_MGR.GetStageSelect() == SCENE_MGR.GetStageCleared()))
			SCENE_MGR.SetStageCleared(SCENE_MGR.GetStageCleared() + 1);
		restart->SetInitState();
		SetActive(false);
		SCENE_MGR.ChangeScene(SceneIds::Stage);
		FRAMEWORK.SetTimeScale(1.f);
		};
	restart->SetButtonFunc(restartFunc);

	next = new Button("graphics/nextstage.png", "Next");
	next->Init();
	auto nextFunc = [this]() {
		if (isClear)
		{
			next->SetInitState();
			SetActive(false);
			if (SCENE_MGR.GetStageSelect() == SCENE_MGR.GetStageCleared())
			{
				SCENE_MGR.SetStageCleared(SCENE_MGR.GetStageCleared() + 1);
				SCENE_MGR.SetStageSelect(SCENE_MGR.GetStageCleared());
			}
			else
				SCENE_MGR.SetStageSelect(SCENE_MGR.GetStageSelect() + 1);
			SCENE_MGR.ChangeScene(SceneIds::Stage);
			FRAMEWORK.SetTimeScale(1.f);
		}
		};
	next->SetButtonFunc(nextFunc);
}

void GameResult::Release()
{
}

void GameResult::Reset()
{
	SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	side.setPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);

	for (int i = 0; i < 3; i++)
	{
		laughSprites[i]->Reset();
		laughSprites[i]->SetPosition(position + laughSpritePosCenter + sf::Vector2f(150.f, 0.f) * (i - 1.f));
		laughSprites[i]->SetScale({ 2.f, 2.f });
	}

	gameText->SetPosition(position + textPos);
	gameText->Reset();

	home->SetPosition(position + homeButtonPos);
	home->SetScale({ 0.7f,0.7f });
	home->Reset();

	restart->SetPosition(position + restartButtonPos);
	restart->SetScale({ 0.7f,0.7f });
	restart->Reset();

	next->SetPosition(position + nextButtonPos);
	next->SetScale({ 0.7f,0.7f });
	next->Reset();
}

void GameResult::Update(float dt)
{
	home->Update(dt);
	restart->Update(dt);
	next->Update(dt);
	gameText->Update(dt);
	for (auto laughSprite : laughSprites)
		laughSprite->Update(dt);
}

void GameResult::Draw(sf::RenderWindow& window)
{
	window.draw(side);
	window.draw(body);
	for (auto laughSprite : laughSprites)
	{
		laughSprite->Draw(window);
	}
	gameText->Draw(window);
	home->Draw(window);
	restart->Draw(window);
	next->Draw(window);
}

void GameResult::ShowResult()
{
	for (auto laughSprite : laughSprites)
	{
		if (isClear)
		{
			laughSprite->SetTextureId("graphics/BirdLaugh.png");
			gameText->SetString("Game Clear!!");
		}
		else
		{
			laughSprite->SetTextureId("graphics/PigLaugh.png");
			gameText->SetString("Game Over!!");
		}
		laughSprite->Reset();
	}
}
