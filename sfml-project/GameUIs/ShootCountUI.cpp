#include "stdafx.h"
#include "ShootCountUI.h"

ShootCountUI::ShootCountUI(const std::string& fontId, const std::string& name)
	: TextGo(fontId, name)
{
}

void ShootCountUI::Init()
{
	TextGo::Init();
}

void ShootCountUI::Release()
{
	TextGo::Release();
}

void ShootCountUI::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	TextGo::Reset();
	text.setCharacterSize(30);
	text.setColor(sf::Color::Black);
	SetCount(0);
	SetPosition({ bounds.width - 200.f, 100.f });
}

void ShootCountUI::Update(float dt)
{
	TextGo::Update(dt);
}

void ShootCountUI::Draw(sf::RenderWindow& window)
{
	TextGo::Draw(window);
}

void ShootCountUI::SetCount(int count)
{
	SetString("Count : " + std::to_string(count));
}
