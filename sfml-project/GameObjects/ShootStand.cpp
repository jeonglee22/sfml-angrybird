#include "stdafx.h"
#include "ShootStand.h"
#include "Bird.h"

ShootStand::ShootStand(const std::string& name)
	:PhysicsBody(Type::ShootStand)
{
}

void ShootStand::Init()
{
	rightBody = new SpriteGo("graphics/Angrybirds/StandRight.png");
	rightBody->SetOrigin(Origins::TL);
	rightBody->SetPosition({ 143.f, 550.f });
	rightBody->SetScale({ 1.f,0.7f });
	rightBody->sortingLayer = SortingLayers::Foreground;
	rightBody->sortingOrder = -2;

	leftBody = new SpriteGo("graphics/Angrybirds/StandLeft.png");
	leftBody->SetOrigin(Origins::TR);
	leftBody->SetPosition({ 159.f, 545.f });
	leftBody->SetScale({ 1.f,0.7f });
	leftBody->sortingLayer = SortingLayers::Foreground;
	leftBody->sortingOrder = 2;

	for (int i = 0; i < (int)Part::PartCount; i++)
	{
		Band.push_back(new SpriteGo(i == 2 ? "graphics/band2.png" : "graphics/band.png"));
		Band[i]->SetOrigin(i == 2 ? Origins::MC : Origins::MR);
		Band[i]->sortingLayer = SortingLayers::Foreground;
		Band[i]->sortingOrder = (i == 1 ? -1 : 1);
		Band[i]->SetActive(false);
	}
	Band[(int)Part::Left]->SetPosition({125.f, 570.f});
	Band[(int)Part::Right]->SetPosition({165.f, 570.f});
	Band[(int)Part::Body]->SetPosition({150.f, 570.f});
}

void ShootStand::Release()
{
	PhysicsBody::Release();
}

void ShootStand::Reset()
{
	rightBody->Reset();
	leftBody->Reset();

	sf::Vector2u standTexSize = TEXTURE_MGR.Get("graphics/Angrybirds/ShootStand.png").getSize();
	SetBoxSize(standTexSize.x * 0.2f, standTexSize.y * 0.5f * 0.7f);
	SetBoxPos(shootPos.x, shootPos.y);
	SetBoxFactor(0.8f, 0.2f);
	SetPosition(initPos * SCALE);
	SetRotation(0.f);

	bodyDef.position = b2Vec2{ initPos.x, initPos.y };
	bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

	b2Polygon groundBox = b2MakeBox(texSize.x, texSize.y);
	shapeDef = b2DefaultShapeDef();
	shapeDef.density = density;
	shapeDef.material.friction = friction;
	shapeDef.material.restitution = restitution;
	shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &groundBox);
}

void ShootStand::Update(float dt)
{
	PhysicsBody::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (Utils::PointInTransformBounds(bird->GetSprite(), bird->GetLocalBounds(), (sf::Vector2f)InputMgr::GetMousePosition()))
		{
			mouseStart = bird->GetPosition();
			SetBandActive(true);
			isShoot = true;
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isShoot)
	{
		mouseEnd = (sf::Vector2f)InputMgr::GetMousePosition();
		sf::Vector2f leftBandPos = GetLeftBandPos();
		sf::Vector2f rightBandPos = GetRightBandPos();
		float bandScale = Utils::Clamp(Utils::Distance(mouseStart, mouseEnd), bird->GetMinCharge(), bird->GetMaxCharge());
		sf::Vector2f shootPos = Utils::GetNormal(mouseEnd - mouseStart) * bandScale + mouseStart;
		
		SetLeftBandRotation(Utils::Angle(leftBandPos - shootPos));
		SetRightBandRotation(Utils::Angle(rightBandPos - shootPos));
		SetBodyBandRotation(Utils::Angle(mouseStart - shootPos));

		SetLeftBandScale(Utils::Distance(leftBandPos, shootPos));
		SetRightBandScale(Utils::Distance(rightBandPos, shootPos));
		SetBandPos(shootPos);
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isShoot)
	{
		SetLeftBandRotation(0.f);
		SetRightBandRotation(0.f);
		SetLeftBandScale(1.f);
		SetRightBandScale(1.f);
		SetBandActive(false);
		isShoot = false;
	}
}

void ShootStand::Draw(sf::RenderWindow& window)
{
	PhysicsBody::Draw(window);
}

void ShootStand::SetBandActive(bool b)
{
	for (auto band : Band)
	{
		band->SetActive(b);
	}
}

void ShootStand::SetLeftBandRotation(float r)
{
	Band[(int)Part::Left]->SetRotation(r);
}

void ShootStand::SetRightBandRotation(float r)
{
	Band[(int)Part::Right]->SetRotation(r);
}

void ShootStand::SetBodyBandRotation(float r)
{
	Band[(int)Part::Body]->SetRotation(r);
}

void ShootStand::SetLeftBandScale(float s)
{
	Band[(int)Part::Left]->SetScale({s,1.f});
}
void ShootStand::SetRightBandScale(float s)
{
	Band[(int)Part::Right]->SetScale({s,1.f});
}

void ShootStand::SetBandPos(const sf::Vector2f& pos)
{
	Band[(int)Part::Body]->SetPosition(pos);
}

