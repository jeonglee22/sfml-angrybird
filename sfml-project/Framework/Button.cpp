#include "stdafx.h"
#include "Button.h"
#include "TextGo.h"

Button::Button(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void Button::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = -1;

	SetOrigin(Origins::MC);

	text = new TextGo("fonts/angrybirds-regular.ttf");
	text->SetOrigin(Origins::MC);

	SpriteGo::Init();
}

void Button::Release()
{
	SpriteGo::Release();
}

void Button::Reset()
{
	text->Reset();

	SpriteGo::Reset();
	
	text->SetPosition(position);

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
			text->SetFillColor(sf::Color(text->GetText().getFillColor().r, 
				text->GetText().getFillColor().g,
				text->GetText().getFillColor().b,
				originAlpha * 0.5f));
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				DoFunc();
			}
		}
		else
		{
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, originAlpha));
			text->SetFillColor(sf::Color(text->GetText().getFillColor().r,
				text->GetText().getFillColor().g,
				text->GetText().getFillColor().b,
				originAlpha));
		}
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	text->Draw(window);
}

void Button::SetInitState()
{
	sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, originAlpha));
	text->SetFillColor(sf::Color(text->GetText().getFillColor().r,
		text->GetText().getFillColor().g,
		text->GetText().getFillColor().b,
		originAlpha));
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
