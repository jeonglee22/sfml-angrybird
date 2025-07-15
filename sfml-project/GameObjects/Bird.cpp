#include "stdafx.h"
#include "Bird.h"

Bird::Bird(const std::string& texPlayerId, const std::string& name)
	:PhysicsBody(Type::Bird, texPlayerId, name)
{
}

void Bird::Init()
{
	PhysicsBody::Init();

	initPos = { 80.f / SCALE, 660.0f / SCALE };
}

void Bird::Release()
{
	PhysicsBody::Release();
}

void Bird::Reset()
{
	SpriteGo::Reset();

	SetPosition(initPos * SCALE);
	SetRotation(0.f);

	bodyDef.position = b2Vec2{ initPos.x, initPos.y };
	bodyId = b2CreateBody(FRAMEWORK.GetWorldID(), &bodyDef);

	collisionRadius = sprite.getTexture()->getSize().x * 0.5f * 0.8f;
	b2Circle circleBox;
	circleBox.center = { 0.f, 0.f };
	circleBox.radius = collisionRadius / SCALE;

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = .5f;
	shapeDef.material.friction = 0.6f;
	shapeDef.material.rollingResistance = 0.5f;
	shapeDef.material.restitution = 0.5f;
	shapeId = b2CreateCircleShape(bodyId, &shapeDef, &circleBox);
	b2Shape_EnableHitEvents(shapeId, true);

	SetDisable();
}

void Bird::Update(float dt)
{
	PhysicsBody::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !isCharging && !isShoot )
	{
		if (Utils::PointInTransformBounds(sprite, GetLocalBounds(), (sf::Vector2f)InputMgr::GetMousePosition()))
		{
			isCharging = true;
			mouseStart = GetPosition();
		}
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isCharging && !isShoot)
	{
		mouseEnd = (sf::Vector2f)InputMgr::GetMousePosition();
		direction = Utils::GetNormal(mouseEnd - mouseStart);
		chargeDistance = Utils::Clamp(Utils::Distance(mouseStart, mouseEnd), minCharge, maxCharge);
		sf::Vector2f newPos = mouseStart + (chargeDistance - sprite.getTexture()->getSize().x * 0.3f) * direction;

		SetPosition(newPos);
		SetRotation(Utils::Angle(Utils::GetNormal(mouseStart - mouseEnd)));

		b2Body_SetTransform(bodyId, 
			b2Vec2{ position.x / SCALE, position.y / SCALE }, 
			b2Rot_identity);
	}
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isCharging && !isShoot)
	{
		direction *= -1.f;
		SetBirdEnable();
		sf::Vector2f Force(direction.x * forceAmount * (chargeDistance / maxCharge), direction.y * forceAmount * (chargeDistance / maxCharge));
		b2Body_ApplyForceToCenter(bodyId, b2Vec2{ Force.x, Force.y }, true);
		isShoot = true;
		isCharging = false;
	}
}

void Bird::Draw(sf::RenderWindow& window)
{
	PhysicsBody::Draw(window);
}

bool Bird::CheckFinishShoot()
{
	float posX = position.x;
	float posY = position.y;
	bool posOut = posX <= shootPos.x * SCALE - 200.f ||
		posX >= shootPos.x * SCALE + 200.f ||
		posY <= shootPos.y * SCALE - 200.f ||
		posY >= shootPos.y * SCALE + 50.f;
	b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
	bool stop = velocity.x <= std::numeric_limits<float>::epsilon() &&
		velocity.y <= std::numeric_limits<float>::epsilon();
	return posOut && stop;
}

void Bird::SetStartPos()
{
	b2Body_SetTransform(bodyId, b2Vec2{ shootPos.x, shootPos.y }, b2Rot{ 1.f,0.f });
	SetPosition(shootPos * SCALE);
	SetRotation(0.f);

	b2Body_SetAngularVelocity(bodyId, 0.f);
	b2Body_SetLinearVelocity(bodyId, b2Vec2_zero);
}

void Bird::SetShootingState()
{
	b2Body_SetAngularVelocity(bodyId, 0.f);
	b2Body_SetLinearVelocity(bodyId, b2Vec2_zero);
}

void Bird::SetInitPos()
{
	b2Body_SetTransform(bodyId, b2Vec2{ initPos.x , initPos.y }, b2Rot{ 1.f,0.f });
	isRestart = false;
	SetDisable();

	SetPosition(initPos * SCALE);
	SetRotation(0.f);

	b2Body_SetAngularVelocity(bodyId, 0.f);
	b2Body_SetLinearVelocity(bodyId, b2Vec2_zero);
}
