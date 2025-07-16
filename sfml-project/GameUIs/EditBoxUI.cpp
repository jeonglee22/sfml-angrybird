#include "stdafx.h"
#include "EditBoxUI.h"
#include "Block.h"
#include "Button.h"
#include "Pig.h"

EditBoxUI::EditBoxUI(const std::string& name)
	: GameObject(name)
{
}

void EditBoxUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void EditBoxUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void EditBoxUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void EditBoxUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void EditBoxUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void EditBoxUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	body.setSize(bodySize);
	body.setOutlineColor(sf::Color::Black);
	body.setOutlineThickness(5.f);
	SetPosition(bodyPos);
	SetOrigin(Origins::MC);

	plate.setOrigin(sf::Vector2f( bodySize.x * 0.9f, bodySize.y * 0.8f ) * 0.5f);
	plate.setPosition(bodyPos + platePos);
	plate.setOutlineColor(sf::Color::Black);
	plate.setOutlineThickness(5.f);
	plate.setSize({bodySize.x * 0.9f, bodySize.y * 0.8f});

	blockButton = new Button("graphics/BlockButton.png", "BlockButton");
	blockButton->SetOrigin(Origins::MC);
	
	pigButton = new Button("graphics/PigButton.png", "PigButton");
	pigButton->SetOrigin(Origins::MC);

	for (int i = 0; i < pigCount; i++)
	{
		pigs.push_back(new SpriteGo("graphics/Angrybirds/PigOriginal.png", "Pig"));
		pigs[i]->SetOrigin(Origins::MC);
		pigs[i]->SetActive(false);
	}
	for (int i = 0; i < blockCount; i++)
	{
		if(i <= 3)
			blocks.push_back(new SpriteGo("graphics/EditorObjects/WoodSquareBlock"+ std::to_string(i + 1) + ".png", "Block"));
		else if(i <= 5)
			blocks.push_back(new SpriteGo("graphics/EditorObjects/WoodStick" + std::to_string(i - 3) + ".png", "Block"));
		else if(i <= 9)
			blocks.push_back(new SpriteGo("graphics/EditorObjects/StoneSquareBlock" + std::to_string(i - 5) + ".png", "Block"));
		else if(i <= 11)
			blocks.push_back(new SpriteGo("graphics/EditorObjects/StoneStick" + std::to_string(i - 9) + ".png", "Block"));
		else if(i <= 15)
			blocks.push_back(new SpriteGo("graphics/EditorObjects/GlassSquareBlock" + std::to_string(i - 11) + ".png", "Block"));
		else if (i <= 17)
			blocks.push_back(new SpriteGo("graphics/EditorObjects/GlassStick" + std::to_string(i - 15) + ".png", "Block"));
		blocks[i]->SetOrigin(Origins::MC);
		blocks[i]->SetActive(false);
		blocks[i]->SetScale({ 0.7f, 0.7f });
	}

	auto ShowBlocks = [this]() {
		for (int i = 0; i < blockCount; i++)
		{
			blocks[i]->SetActive(true);
		}
		for (int i = 0; i < pigCount; i++)
		{
			pigs[i]->SetActive(false);
		}
	};
	blockButton->SetButtonFunc(ShowBlocks);

	auto ShowPigs = [this]() {
		for (int i = 0; i < blockCount; i++)
		{
			blocks[i]->SetActive(false);
		}
		for (int i = 0; i < pigCount; i++)
		{
			pigs[i]->SetActive(true);
		}
	};
	pigButton->SetButtonFunc(ShowPigs);
}

void EditBoxUI::Release()
{
}

void EditBoxUI::Reset()
{
	pigButton->Reset();
	blockButton->Reset();
	blockButton->SetPosition(blockButtonPos + bodyPos);
	pigButton->SetPosition(pigButtonPos + bodyPos);

	for (int i = 0; i < blockCount; i++)
	{
		blocks[i]->Reset();
		blocks[i]->SetPosition(bodyPos + sf::Vector2f((i%3 - 1) * blockinterval.x, (i / 3 - 2) * blockinterval.y));
	}
	for (int i = 0; i < pigCount; i++)
	{
		pigs[i]->Reset();
		pigs[i]->SetPosition(bodyPos + sf::Vector2f((i % 3 - 1) * blockinterval.x, (i / 3 - 2) * blockinterval.y));
	}
}

void EditBoxUI::Update(float dt)
{
	pigButton->Update(dt);
	blockButton->Update(dt);
}

void EditBoxUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(plate);
	blockButton->Draw(window);
	pigButton->Draw(window);
	for (int i = 0; i < blockCount; i++)
	{
		blocks[i]->Draw(window);
	}
	for (int i = 0; i < pigCount; i++)
	{
		pigs[i]->Draw(window);
	}
}

SpriteGo* EditBoxUI::GetMousePosSprite()
{
	if (SCENE_MGR.GetCurrentScene())
	{
		Scene* scene = SCENE_MGR.GetCurrentScene();
		sf::Vector2f mousePos = scene->ScreenToUi(InputMgr::GetMousePosition());
		for (auto block : blocks)
		{
			if (block->GetActive())
			{
				if (Utils::PointInTransformBounds(block->GetSprite(), block->GetLocalBounds(), mousePos))
				{
					return block;
				}
			}
		}
		for (auto pig : pigs)
		{
			if (pig->GetActive())
			{
				if (Utils::PointInTransformBounds(pig->GetSprite(), pig->GetLocalBounds(), mousePos))
				{
					return pig;
				}
			}
		}
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}
