#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround(const std::string& texId1, const std::string& texId2, const std::string& name)
	:texId1(texId1), texId2(texId2), GameObject(name)
{
}

void BackGround::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	mainbody.setPosition(pos);
}

void BackGround::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	mainbody.setRotation(rot);
}

void BackGround::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	mainbody.setScale(s);
}

void BackGround::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	mainbody.setOrigin(o);
}

void BackGround::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(mainbody, preset);
	}
}

void BackGround::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
	for (int i = 0; i < backgroundCount; i++)
	{
		backgrounds.push_back(new SpriteGo(texId1));
		backgrounds[i]->SetOrigin(Origins::MC);
	}
	for (int i = 0; i < backgroundCount; i++)
	{
		backgrounds.push_back(new SpriteGo(texId2));
		backgrounds[i + backgroundCount]->SetOrigin(Origins::MC);
	}
}

void BackGround::Release()
{
}

void BackGround::Reset()
{
	for (int i = 0; i < backgroundCount; i++)
	{
		backgrounds[i]->Reset();
		backgrounds[i]->SetScale({ i % 2 ? 1.f : -1.f, 768.f / 1082.f});
		backgrounds[i]->SetPosition(sf::Vector2f(TEXTURE_MGR.Get(texId1).getSize().x * (i - 1.f), 0) + backgroundsPos);
	}
	for (int i = 0; i < backgroundCount; i++)
	{
		backgrounds[i + backgroundCount]->Reset();
		backgrounds[i + backgroundCount]->SetScale({ 1.f, 1.f});
		sf::Vector2f texSize = (sf::Vector2f)TEXTURE_MGR.Get(texId2).getSize();
		backgrounds[i + backgroundCount]->SetPosition(sf::Vector2f(texSize.x * (i - 1.f), 0) + sf::Vector2f(texSize.x * 0.5f, texSize.y * -0.5f));
	}
}

void BackGround::Update(float dt)
{
}

void BackGround::Draw(sf::RenderWindow& window)
{
	for (auto background : backgrounds)
	{
		background->Draw(window);
	}
}

sf::FloatRect BackGround::GetTotalSize()
{
	sf::Vector2f texSize1 = (sf::Vector2f)TEXTURE_MGR.Get(texId1).getSize();
	texSize1.y = 768.f;
	sf::Vector2f texSize2 = (sf::Vector2f)TEXTURE_MGR.Get(texId2).getSize();
	float top = -texSize2.y;
	float left = -texSize1.x;
	float width = texSize1.x*3;
	float height = texSize1.y + texSize2.y;
	return sf::FloatRect(left, top, width, height);
}
