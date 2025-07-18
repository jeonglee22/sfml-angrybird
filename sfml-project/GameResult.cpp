#include "stdafx.h"
#include "GameResult.h"

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
}

void GameResult::Release()
{
}

void GameResult::Reset()
{
}

void GameResult::Update(float dt)
{
}

void GameResult::Draw(sf::RenderWindow& window)
{
}