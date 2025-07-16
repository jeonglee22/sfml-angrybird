#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void Button::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = -1;

	SetOrigin(Origins::MC);

	SpriteGo::Init();
}

void Button::Release()
{
	SpriteGo::Release();
}

void Button::Reset()
{
	SpriteGo::Reset();

	originAlpha = sprite.getColor().a;
}

void Button::Update(float dt)
{
	SpriteGo::Update(dt);

	if(SCENE_MGR.GetCurrentScene())
	{
		float mouseDistance = Utils::Distance(position, SCENE_MGR.GetCurrentScene()->ScreenToUi(InputMgr::GetMousePosition()));

		if (mouseDistance < sprite.getTexture()->getSize().x * 0.5)
		{
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, originAlpha * 0.5f));
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				DoFunc();
			}
		}
		else
		{
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, originAlpha));
		}
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Button::DoFunc()
{
	switch (type)
	{
	case Button::Type::Void:
		if(voidfunc)
		{
			voidfunc();
		}
		break;
	case Button::Type::buttonCount:
		break;
	default:
		break;
	}
}
