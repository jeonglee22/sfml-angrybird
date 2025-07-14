#pragma once
#include "SpriteGo.h"
class PhysicsBody : public SpriteGo
{
public:
	enum class Type
	{
		Invisible,
		Block,
		Pig,
	};

protected:
	b2BodyDef bodyDef = b2DefaultBodyDef();;
	b2ShapeDef shapeDef;
	b2BodyId bodyId;
	b2ShapeId shapeId;
	Type bodyType = Type::Invisible;

	bool setBody = false;

	sf::Vector2f initPos = { 0.f,0.f };
	sf::Vector2f texSize = { 1.f,1.f };
	b2Rot rotation = b2Rot_identity;

	float density = 1.f;
	float friction = 0.f;
	float restitution = 0.f;
	float rollingResistance = 0.f;

public:
	PhysicsBody(Type ty = Type::Invisible, const std::string& texPlayerId = "", const std::string& name = "");
	virtual ~PhysicsBody() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetBoxSize(float width, float height);
	void SetBoxPos(float x, float y);
	void SetBoxFactor(float fric, float res, float dens = 1.f, float roll = 0.f);
	void SetTransform();
};

