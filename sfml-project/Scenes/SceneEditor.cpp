#include "stdafx.h"
#include "rapidcsv.h"
#include "SceneEditor.h"
#include "BackGround.h"
#include "EditBoxUI.h"
#include "SpriteGo.h"
#include "RectGo.h"
#include "Button.h"

int SceneEditor::mapNumber = 1;

SceneEditor::SceneEditor()
	: Scene(SceneIds::Editor)
{
}

void SceneEditor::Init()
{
	texIds.push_back("graphics/LevelOne.png");
	texIds.push_back("graphics/Sky.png");
	texIds.push_back("graphics/redo.png");
	texIds.push_back("graphics/save.png");
	texIds.push_back("graphics/PigButton.png");
	texIds.push_back("graphics/BlockButton.png");
	texIds.push_back("graphics/Angrybirds/PigOriginal.png");
	for (int i = 1; i < 5; i++)
	{
		texIds.push_back("graphics/EditorObjects/WoodSquareBlock" + std::to_string(i) + ".png");
		texIds.push_back("graphics/EditorObjects/StoneSquareBlock" + std::to_string(i) + ".png");
		texIds.push_back("graphics/EditorObjects/GlassSquareBlock" + std::to_string(i) + ".png");
	}
	for (int i = 1; i < 3; i++)
	{
		texIds.push_back("graphics/EditorObjects/WoodStick" + std::to_string(i) + ".png");
		texIds.push_back("graphics/EditorObjects/StoneStick" + std::to_string(i) + ".png");
		texIds.push_back("graphics/EditorObjects/GlassStick" + std::to_string(i) + ".png");
	}

	background = (BackGround*)AddGameObject(new BackGround("graphics/LevelOne.png", "graphics/Sky.png"));

	boxUI = (EditBoxUI*)AddGameObject(new EditBoxUI());
	redo = (Button*)AddGameObject(new Button("graphics/redo.png"));
	save = (Button*)AddGameObject(new Button("graphics/save.png"));
	objectBound = (RectGo*)AddGameObject(new RectGo());
	objectBound->SetColor(sf::Color(0, 0, 0, 100));

	Scene::Init();

	objectBound->sortingOrder = -1;
	
	redo->sortingOrder = 10;
	save->sortingOrder = 10;
}

void SceneEditor::Enter()
{
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter(FRAMEWORK.GetWindowSizeF() * 0.5f);

	worldView.setSize(initViewSize);
	worldView.setCenter(initViewPos);
	currentViewPos = initViewPos;
	currentViewSize = initViewSize;

	Scene::Enter();
	
	auto redoFunc = [this]() {
		if(spriteCount > 0)
		{
			spriteCount--;
			RemoveGameObject(spriteInserts[spriteCount]);
			spriteInserts.pop_back();
		}
	};
	redo->SetButtonFunc(redoFunc);
	redo->SetScale({ 0.75f,0.75f });
	sf::Vector2f redoButtonSize = (sf::Vector2f)TEXTURE_MGR.Get(redo->GetTextureId()).getSize();
	redo->SetPosition({ redoButtonSize.x * 0.6f + 80.f, redoButtonSize.y * 0.6f});

	auto saveFunc = [this]() { SaveField(); };
	save->SetButtonFunc(saveFunc);
	save->SetScale({ 0.6f,0.6f });
	sf::Vector2f saveButtonSize = (sf::Vector2f)TEXTURE_MGR.Get(save->GetTextureId()).getSize();
	save->SetPosition({ saveButtonSize.x * 0.6f, saveButtonSize.y * 0.5f});

	backgroundSize = background->GetTotalSize();

	objectBound->SetSize({ backgroundSize.width * 0.5f, backgroundSize.height });
	objectBound->SetPosition({ backgroundSize.left + backgroundSize.width * 0.75f, backgroundSize.top + backgroundSize.height * 0.5f });
	objectBound->SetOrigin(sf::Vector2f( backgroundSize.width * 0.5f, backgroundSize.height ) * 0.5f);
}

void SceneEditor::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		mouseStart = (sf::Vector2f)InputMgr::GetMousePosition();
	}
	else if (InputMgr::GetMouseButton(sf::Mouse::Right))
	{
		ViewControl((sf::Vector2f)InputMgr::GetMousePosition());
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		spriteChoosed = boxUI->GetMousePosSprite();
		if (spriteChoosed != nullptr)
		{
			isChoosed = true;
			spriteInserts.push_back((SpriteGo*)AddGameObject( new SpriteGo(spriteChoosed->GetTextureId())));
			spriteInserts[spriteCount]->Reset();
			spriteInserts[spriteCount]->SetOrigin(Origins::MC);
			spriteInserts[spriteCount]->sortingLayer = SortingLayers::UI;
			spriteInserts[spriteCount]->sortingOrder = 5;
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isChoosed)
	{
		spriteInserts[spriteCount]->SetPosition(ScreenToUi(InputMgr::GetMousePosition()));
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isChoosed)
	{
		sf::Vector2f mouseUiPos = ScreenToUi(InputMgr::GetMousePosition());
		sf::Vector2f mouseWorldPos = ScreenToWorld(InputMgr::GetMousePosition());
		if (Utils::PointInTransformBounds(objectBound->GetRect(), objectBound->GetRect().getLocalBounds(), mouseWorldPos) &&
			!Utils::PointInTransformBounds(boxUI->GetBody(), boxUI->GetBody().getLocalBounds(), mouseUiPos))
		{
			sf::Vector2f spritePos = spriteInserts[spriteCount]->GetPosition();
			sf::Vector2f newPos = ScreenToWorld(UiToScreen(spritePos));
			spriteInserts[spriteCount]->SetPosition(newPos);
			spriteInserts[spriteCount]->sortingLayer = SortingLayers::Foreground;
			spriteInserts[spriteCount]->sortingOrder = 0;
			spriteChoosed = nullptr;
			isChoosed = false;
			spriteCount++;
		}
		else
		{
			RemoveGameObject(spriteInserts[spriteCount]);
			spriteInserts.pop_back();
			isChoosed = false;
		}
	}
}

void SceneEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneEditor::ViewControl(const sf::Vector2f& mousePos)
{
	currentViewPos.x += (mouseStart - mousePos).x;
	currentViewPos.y += (mouseStart - mousePos).y;

	ViewClamp();

	mouseStart = mousePos;
	worldView.setCenter(currentViewPos);
}

void SceneEditor::ViewClamp()
{
	float topLimit = backgroundSize.top + currentViewSize.y * 0.5f;
	float bottomLimit = backgroundSize.top + backgroundSize.height - currentViewSize.y * 0.5f;
	float leftLimit = backgroundSize.left + currentViewSize.x * 0.5f;
	float rightLimit = backgroundSize.left + backgroundSize.width - currentViewSize.x * 0.5f;

	currentViewPos.x = Utils::Clamp(currentViewPos.x, leftLimit, rightLimit);
	currentViewPos.y = Utils::Clamp(currentViewPos.y, topLimit, bottomLimit);
}

void SceneEditor::SaveField()
{
	rapidcsv::Document doc("graphics/EditorMaps/Map" + std::to_string(SceneEditor::mapNumber) + ".csv");
	doc.SetColumnName(0, "BLOCK_COUNT");
	doc.SetColumnName(1, "PIG_COUNT");
	//doc.SetCell(0, 0, SceneEditor::blockCount );
}
