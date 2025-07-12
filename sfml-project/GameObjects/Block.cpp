#include "stdafx.h"
#include "Block.h"

Block::Block(const std::string& name)
	: GameObject(name)
{
}

void Block::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Block::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Block::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Block::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Block::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Block::Init()
{
	auto size = FRAMEWORK.GetWindowSizeF();

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	body.setFillColor(sf::Color::Green);
	
	hitBox.SetType(HitBox::Type::Rectangle);
}

void Block::Release()
{
}

void Block::Reset()
{
	SetScale({ 1.f,1.f });
	SetRotation(30.f);
}

void Block::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds());
}

void Block::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}