#include "stdafx.h"
#include "EditBoxUI.h"
#include "Block.h"
#include "Button.h"
#include "rapidcsv.h"
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
	plate.setSize({bodySize.x * 0.9f, bodySize.y * 0.8f});

	scrollBox.setOrigin(scrollSize * 0.5f);
	scrollBox.setPosition(bodyPos + scrollPos);
	scrollBox.setSize(scrollSize);
	scrollBox.setFillColor(sf::Color(0, 0, 0, 180));

	aboveplate.setSize({ bodySize.x, bodySize.y * 0.2f-10.f});
	aboveplate.setOrigin(aboveplate.getSize() * 0.5f + sf::Vector2f(5.f,0.f));
	aboveplate.setOutlineColor(sf::Color::Black);
	aboveplate.setOutlineThickness(5.f);
	aboveplate.setPosition(bodyPos + abovePlatePos);

	blockButton = new Button("graphics/BlockButton.png", "BlockButton");
	blockButton->SetOrigin(Origins::MC);
	
	pigButton = new Button("graphics/PigButton.png", "PigButton");
	pigButton->SetOrigin(Origins::MC);

	AddPigTypes("StageStructures/pigtype.csv");
	AddBlockTypes("StageStructures/blocktype.csv");

	auto ShowBlocks = [this]() {
		for (int i = 0; i < blockCount; i++)
		{
			blocks[i]->SetActive(true);
		}
		for (int i = 0; i < pigCount; i++)
		{
			pigs[i]->SetActive(false);
		}
		ResetObjectsInitPosition();
		currentPlate = Plate::Block;
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
		ResetObjectsInitPosition();
		currentPlate = Plate::Pig;
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
		blocksInitPos.push_back(sf::Vector2f((i % 3 - 1) * blockinterval.x, (i / 3 - 2) * blockinterval.y));
		blocks[i]->SetPosition(bodyPos + blocksInitPos[i] + objectsCenterPos);
	}
	for (int i = 0; i < pigCount; i++)
	{
		pigs[i]->Reset();
		pigsInitPos.push_back(sf::Vector2f((i % 3 - 1) * blockinterval.x, (i / 3 - 2) * blockinterval.y));
		pigs[i]->SetPosition(bodyPos + pigsInitPos[i] + objectsCenterPos);
	}

	minBlockYScroll = -((blockCount  - 1) / 3 - 4) * blockinterval.y;
	minPigYScroll = -((pigCount - 1) / 3 - 4) * blockinterval.y;
	if (minPigYScroll > 0)
	{
		minPigYScroll = 0.f;
	}
	if (minBlockYScroll > 0)
	{
		minBlockYScroll = 0.f;
	}

	scene = SCENE_MGR.GetCurrentScene();
}

void EditBoxUI::Update(float dt)
{
	pigButton->Update(dt);
	blockButton->Update(dt);

	if (InputMgr::GetWheelScroll() != 0)
	{
		float newObjectsCenterY = objectsCenterPos.y + InputMgr::GetWheelScroll() * dt * 3000.f;

		objectsCenterPos.y = Utils::Clamp(newObjectsCenterY, currentPlate == Plate::Block ? minBlockYScroll : minPigYScroll, maxYScroll);
		AddAllObjectsPosition();
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = scene->ScreenToUi(InputMgr::GetMousePosition());
		if (Utils::PointInTransformBounds(scrollBox, scrollBox.getLocalBounds(), mousePos))
		{
			isScrollMove = true;
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isScrollMove)
	{
		sf::Vector2f mousePos = scene->ScreenToUi(InputMgr::GetMousePosition());
		scrollBox.setPosition({ scrollBox.getPosition().x , Utils::Clamp(mousePos.y, scrollBoxYMin, scrollBoxYMax) });
		float scrollPercent = (scrollBox.getPosition().y - scrollBoxYMin) / (scrollBoxYMax - scrollBoxYMin);
		objectsCenterPos.y = Utils::Lerp(maxYScroll, currentPlate == Plate::Block ? minBlockYScroll : minPigYScroll, scrollPercent);
		AddAllObjectsPosition();
	}
}

void EditBoxUI::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(plate);
	
	for (int i = 0; i < blockCount; i++)
	{
		blocks[i]->Draw(window);
	}
	for (int i = 0; i < pigCount; i++)
	{
		pigs[i]->Draw(window);
	}
	window.draw(aboveplate);
	window.draw(scrollBox);
	blockButton->Draw(window);
	pigButton->Draw(window);
}

SpriteGo* EditBoxUI::GetMousePosSprite(int &hp)
{
	if (SCENE_MGR.GetCurrentScene())
	{
		Scene* scene = SCENE_MGR.GetCurrentScene();
		sf::Vector2f mousePos = scene->ScreenToUi(InputMgr::GetMousePosition());
		for (int i = 0; i < blockCount; i++)
		{
			if (blocks[i]->GetActive())
			{
				if (Utils::PointInTransformBounds(blocks[i]->GetSprite(), blocks[i]->GetLocalBounds(), mousePos))
				{
					hp = blockHPs[i];
					return blocks[i];
				}
			}
		}
		for (int i = 0; i < pigCount; i++)
		{
			if (pigs[i]->GetActive())
			{
				if (Utils::PointInTransformBounds(pigs[i]->GetSprite(), pigs[i]->GetLocalBounds(), mousePos))
				{
					hp = pigHPs[i];
					return pigs[i];
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

void EditBoxUI::AddBlockTypes(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);
	blockCount = doc.GetCell<int>(0,0);
	for (int i = 0; i < blockCount; i++)
	{
		auto row = doc.GetRow<std::string>(i + 2);
		blocks.push_back(new SpriteGo(row[0], row[1]));
		blocks[i]->SetOrigin(Origins::MC);
		blocks[i]->SetActive(false);
		blocks[i]->SetScale({ 0.7f, 0.7f });
		blockHPs.push_back(std::stoi(row[2]));
	}
}

void EditBoxUI::AddPigTypes(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);
	pigCount = doc.GetCell<int>(0, 0);
	for (int i = 0; i < pigCount; i++)
	{
		auto row = doc.GetRow<std::string>(i + 2);
		pigs.push_back(new SpriteGo(row[0], row[1]));
		pigs[i]->SetOrigin(Origins::MC);
		pigs[i]->SetActive(false);
		pigHPs.push_back(std::stoi(row[2]));
	}
}

void EditBoxUI::AddAllObjectsPosition()
{
	for (int i = 0; i < blockCount; i++)
	{
		blocks[i]->SetPosition(bodyPos + sf::Vector2f((i % 3 - 1) * blockinterval.x, (i / 3 - 2) * blockinterval.y) + objectsCenterPos);
	}
	for (int i = 0; i < pigCount; i++)
	{
		pigs[i]->SetPosition(bodyPos + sf::Vector2f((i % 3 - 1) * blockinterval.x, (i / 3 - 2) * blockinterval.y) + objectsCenterPos);
	}
}

void EditBoxUI::ResetObjectsInitPosition()
{
	objectsCenterPos = { 0.f,0.f };
	for (int i = 0; i < blockCount; i++)
	{
		blocks[i]->SetPosition(bodyPos + blocksInitPos[i] + objectsCenterPos);
	}
	for (int i = 0; i < pigCount; i++)
	{
		pigs[i]->SetPosition(bodyPos + pigsInitPos[i] + objectsCenterPos);
	}
}
