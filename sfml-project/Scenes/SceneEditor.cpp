#include "stdafx.h"
#include "windows.h"
#include "commdlg.h"
#include "SceneEditor.h"
#include "BackGround.h"
#include "EditBoxUI.h"
#include "SpriteGo.h"
#include "RectGo.h"
#include "Button.h"
#include "ShootStand.h"

HWND hwnd;
int SceneEditor::mapNumber = 1;

SceneEditor::SceneEditor()
	: Scene(SceneIds::Editor)
{
}

void SceneEditor::Init()
{
	fontIds.push_back("fonts/angrybirds-regular.ttf");

	texIds.push_back("graphics/LevelOne.png");
	texIds.push_back("graphics/Sky.png");
	texIds.push_back("graphics/buttonsnontext.png");
	texIds.push_back("graphics/Angrybirds/ShootStand.png");
	texIds.push_back("graphics/Angrybirds/StandRight.png");
	texIds.push_back("graphics/Angrybirds/StandLeft.png");
	texIds.push_back("graphics/band.png");
	texIds.push_back("graphics/band2.png");
	texIds.push_back("graphics/redo.png");
	texIds.push_back("graphics/PigButton.png");
	texIds.push_back("graphics/BlockButton.png");
	texIds.push_back("graphics/BirdButton.png");

	background = (BackGround*)AddGameObject(new BackGround("graphics/LevelOne.png", "graphics/Sky.png"));

	boxUI = (EditBoxUI*)AddGameObject(new EditBoxUI());
		
	undo = (Button*)AddGameObject(new Button("graphics/redo.png"));
	save = (Button*)AddGameObject(new Button("graphics/buttonsnontext.png"));
	load = (Button*)AddGameObject(new Button("graphics/buttonsnontext.png"));

	objectBound = (RectGo*)AddGameObject(new RectGo());
	objectBound->SetColor(sf::Color(0, 0, 0, 100));
	birdBound = (RectGo*)AddGameObject(new RectGo());
	birdBound->SetColor(sf::Color(20,20, 20, 100));

	shootStand = (ShootStand*)AddGameObject(new ShootStand());

	Scene::Init();

	std::vector<std::string> texIDs = boxUI->GetTexIDs();
	for (auto& texId : texIDs)
		texIds.push_back(texId);

	AddGameObject(shootStand->GetLeftPart());
	AddGameObject(shootStand->GetRightPart());
	std::vector<SpriteGo*> band = shootStand->GetBandPart();
	for (auto part : band)
	{
		AddGameObject(part);
	}

	objectBound->sortingOrder = -1;
	
	undo->sortingOrder = 10;
	save->sortingOrder = 10;
	load->sortingOrder = 10;
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
	
	auto undoFunc = [this]() {
		if(spriteCount > 0)
		{
			spriteCount--;
			if (spriteInserts[spriteCount]->GetName() == "Pig")
			{
				pigCount--;
			}
			else if(spriteInserts[spriteCount]->GetName() == "Block")
			{
				blockCount--;
			}
			else
			{
				birdCount--;
			}
			RemoveGameObject(spriteInserts[spriteCount]);
			spriteInserts.pop_back();
		}
	};
	undo->SetButtonFunc(undoFunc);
	undo->SetScale({ 0.75f,0.75f });
	sf::Vector2f redoButtonSize = (sf::Vector2f)TEXTURE_MGR.Get(undo->GetTextureId()).getSize();
	undo->SetPosition({ redoButtonSize.x * 0.6f + 160.f, redoButtonSize.y * 0.5f});

	auto saveFunc = [this]() { SaveField(); };
	save->SetButtonFunc(saveFunc);
	save->SetScale({ 0.75f,0.75f });
	sf::Vector2f saveButtonSize = (sf::Vector2f)TEXTURE_MGR.Get(save->GetTextureId()).getSize();
	save->SetPosition({ saveButtonSize.x * 0.6f, saveButtonSize.y * 0.6f});
	save->SetTextString("Save");
	save->SetTextPosition({ 0.f,-5.f });
	
	auto loadFunc = [this]() { LoadField(); };
	load->SetButtonFunc(loadFunc);
	load->SetScale({ 0.75f,0.75f });
	sf::Vector2f loadButtonSize = (sf::Vector2f)TEXTURE_MGR.Get(load->GetTextureId()).getSize();
	load->SetPosition({ loadButtonSize.x * 0.6f + 80.f, loadButtonSize.y * 0.6f});
	load->SetTextString("Load");
	load->SetTextPosition({ 0.f,-5.f });

	backgroundSize = background->GetTotalSize();

	objectBound->SetSize({ backgroundSize.width * 0.5f, backgroundSize.height });
	objectBound->SetPosition({ backgroundSize.left + backgroundSize.width * 0.75f, backgroundSize.top + backgroundSize.height * 0.5f });
	objectBound->SetOrigin(sf::Vector2f( backgroundSize.width * 0.5f, backgroundSize.height ) * 0.5f);

	birdBound->SetSize({ 500.f, 100.f });
	birdBound->SetPosition({0,backgroundSize.top + backgroundSize.height - 130.f});
	birdBound->SetOrigin(Origins::MR);
}

void SceneEditor::Update(float dt)
{
	Scene::Update(dt);

	if (boxUI->GetCurrentPlate() != currentPlate)
	{
		if(boxUI->GetCurrentPlate() == EditBoxUI::Plate::Bird)
		{
			worldView.setCenter(birdBoundViewPos);
			currentViewPos = birdBoundViewPos;
		}
		else
		{
			if(currentPlate == EditBoxUI::Plate::Bird)
			{
				worldView.setCenter(initViewPos);
				currentViewPos = initViewPos;
			}
		}
		currentPlate = boxUI->GetCurrentPlate();
	}

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
		spriteChoosed = boxUI->GetMousePosSprite(choosedSpriteHp);
		if (spriteChoosed != nullptr)
		{
			isChoosed = true;
			spriteInserts.push_back((SpriteGo*)AddGameObject( new SpriteGo(spriteChoosed->GetTextureId(), spriteChoosed->GetName())));
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
			!Utils::PointInTransformBounds(boxUI->GetBody(), boxUI->GetBody().getLocalBounds(), mouseUiPos) &&
			spriteInserts[spriteCount]->GetName() != "Bird")
		{
			sf::Vector2f spritePos = spriteInserts[spriteCount]->GetPosition();
			sf::Vector2f newPos = ScreenToWorld(UiToScreen(spritePos));
			sf::Vector2f texSize = (sf::Vector2f) TEXTURE_MGR.Get(spriteInserts[spriteCount]->GetTextureId()).getSize();
			newPos.x = Utils::Clamp(newPos.x,
				objectBound->GetOrigin().x - objectBound->GetPosition().x + texSize.x,
				objectBound->GetOrigin().x + objectBound->GetPosition().x - texSize.x);
			spriteInserts[spriteCount]->SetPosition(newPos);
			spriteInserts[spriteCount]->sortingLayer = SortingLayers::Foreground;
			spriteInserts[spriteCount]->sortingOrder = 0;
			spriteChoosed = nullptr;
			isChoosed = false;
			if (spriteInserts[spriteCount]->GetName() == "Pig")
			{
				pigCount++;
			}
			else
			{
				blockCount++;
			}
			spriteCount++;
			HpList.push_back(choosedSpriteHp);
		}
		else if (Utils::PointInTransformBounds(birdBound->GetRect(), birdBound->GetRect().getLocalBounds(), mouseWorldPos) &&
			!Utils::PointInTransformBounds(boxUI->GetBody(), boxUI->GetBody().getLocalBounds(), mouseUiPos) &&
				spriteInserts[spriteCount]->GetName() == "Bird")
		{
			sf::Vector2f spritePos = spriteInserts[spriteCount]->GetPosition();
			sf::Vector2f newPos = ScreenToWorld(UiToScreen(spritePos));
			sf::Vector2f texSize = (sf::Vector2f)TEXTURE_MGR.Get(spriteInserts[spriteCount]->GetTextureId()).getSize();
			newPos.x = Utils::Clamp(newPos.x,
				objectBound->GetOrigin().x - objectBound->GetPosition().x + texSize.x,
				objectBound->GetOrigin().x + objectBound->GetPosition().x - texSize.x);
			spriteInserts[spriteCount]->SetPosition(newPos);
			spriteInserts[spriteCount]->sortingLayer = SortingLayers::Foreground;
			spriteInserts[spriteCount]->sortingOrder = 0;
			spriteChoosed = nullptr;
			isChoosed = false;
			birdCount++;
			spriteCount++;
			HpList.push_back(choosedSpriteHp);
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

rapidcsv::Document SceneEditor::SaveFile()
{
	rapidcsv::Document doc;
	doc.SetColumnName(0, "BLOCK_COUNT");
	doc.InsertRow(0, std::vector<int>{spriteCount});
	//doc.InsertRow
	for (int i = 0; i < spriteCount; i++)
	{
		sf::Vector2f pos = spriteInserts[i]->GetPosition();
		sf::FloatRect rect = spriteInserts[i]->GetLocalBounds();
		std::vector<std::string> info;
		info.push_back(spriteInserts[i]->GetTextureId());
		info.push_back(std::to_string(pos.x));
		info.push_back(std::to_string(pos.y));
		info.push_back(std::to_string(rect.width * 0.5f));
		info.push_back(std::to_string(rect.height * 0.5f));
		info.push_back(std::to_string(0.5f));
		info.push_back(std::to_string(0.5f));
		info.push_back(std::to_string(0.1f));
		info.push_back(std::to_string(0.f));
		info.push_back(std::to_string(HpList[i]));
		if (spriteInserts[i]->GetName() == "Pig")
		{
			info.push_back(std::to_string(1));
		}
		else if(spriteInserts[i]->GetName() == "Block")
		{
			info.push_back(std::to_string(0));
		}
		else
		{
			info.push_back(std::to_string(2));
		}
		doc.InsertRow(i + 2, info);
	}
	return doc;
}

void SceneEditor::SaveField()
{
	rapidcsv::Document doc = SaveFile();

	TCHAR filename[MAX_PATH] = L"";
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"모든 파일\0*.*\0텍스트 파일\0*.csv\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"csv";

	while(true)
	{
		if (GetSaveFileName(&ofn) != NULL)
		{
			wsprintf(filename, L"%s 파일을 저장하시겠습니까?", ofn.lpstrFile);
			MessageBox(hwnd, filename, L"저장 선택", MB_OK);

			std::string stringFileName = tostring(filename);
			doc.Save(stringFileName);
			std::cout << stringFileName << std::endl;
			mapNumber += 1;
			break;
		}
		else
		{
			continue;
		}
	}
}

void SceneEditor::LoadField()
{
	TCHAR filename[MAX_PATH] = L"";

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"모든 파일\0*.*\0텍스트 파일\0*.csv\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"csv";

	if (GetOpenFileName(&ofn) != NULL)
	{
		wsprintf(filename, L"%s 파일을 열겠습니까?", ofn.lpstrFile);
		MessageBox(hwnd, filename, L"열기 선택", MB_OK);

		std::string stringFileName = tostring(filename);
		
		LoadFile(stringFileName);
	}
}

void SceneEditor::LoadFile(const std::string& fileName)
{
	rapidcsv::Document doc(fileName);
	spriteCount = doc.GetCell<int>(0, 0);

	for (auto sprite : spriteInserts)
	{
		RemoveGameObject(sprite);
	}

	spriteInserts.clear();
	HpList.clear();
	for (int i = 0; i < spriteCount; i++)
	{
		auto row = doc.GetRow<std::string>(i + 2);
		spriteInserts.push_back((SpriteGo*)AddGameObject(new SpriteGo(row[0], std::stoi(row[10]) == 0 ? "Block" : (std::stoi(row[10]) == 2 ? "Bird" : "Pig"))));
		spriteInserts[i]->Reset();
		spriteInserts[i]->SetOrigin(Origins::MC);
		spriteInserts[i]->SetPosition({std::stof(row[1]), std::stof(row[2])});
		spriteInserts[i]->sortingLayer = SortingLayers::Foreground;
		spriteInserts[i]->sortingOrder = 0;
		HpList.push_back(std::stoi(row[9]));
	}
}

std::string SceneEditor::tostring(WCHAR* str)
{
	std::string string;
	wchar_t* oneBlock = str;
	while (*oneBlock != ' ')
	{
		std::string word;
		string += word.assign(oneBlock, oneBlock + 1);
		oneBlock++;
	}
	return string;
}


