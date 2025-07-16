#include "stdafx.h"
#include "RectGo.h"

RectGo::RectGo(const std::string& name)
	: GameObject(name)
{
}

void RectGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	rect.setPosition(pos);
}

void RectGo::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	rect.setRotation(rot);
}

void RectGo::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	rect.setScale(s);
}

void RectGo::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	rect.setOrigin(o);
}

void RectGo::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(rect, preset);
	}
}

void RectGo::SetColor(const sf::Color& c)
{
	color = c;
	rect.setFillColor(c);
}

void RectGo::SetSize(const sf::Vector2f& s)
{
	rectSize = s;
	rect.setSize(s);
}

void RectGo::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetOrigin(Origins::MC);
}

void RectGo::Release()
{
}

void RectGo::Reset()
{
}

void RectGo::Update(float dt)
{
}

void RectGo::Draw(sf::RenderWindow& window)
{
	window.draw(rect);
}