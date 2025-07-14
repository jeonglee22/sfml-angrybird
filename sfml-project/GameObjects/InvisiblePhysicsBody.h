#pragma once
#include "GameObject.h"
class InvisiblePhysicsBody : public GameObject
{
protected:
	sf::Sprite body;

	b2BodyDef bodyDef = b2DefaultBodyDef();
	b2ShapeDef shapeDef;
	b2BodyId bodyId;
	b2ShapeId shapeId;

	float boxHalfWidth = 1.f;
	float boxHalfHeight = 1.f;
	float boxPosX = 0.f;
	float boxPosY = 0.f;
	b2Rot rotation = b2Rot_identity;

	float friction = 0.f;
	float restitution = 0.f;

	bool isReset = false;

public:
	InvisiblePhysicsBody(const std::string& name = "");
	virtual ~InvisiblePhysicsBody() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetBoxSize(float width, float height);
	void SetBoxPos(float x, float y);
	void SetBoxFactor(float f, float r);
};

