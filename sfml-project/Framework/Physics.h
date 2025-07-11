#pragma once
#include "SpriteGo.h"

class Physics
{
public:
	enum class CollisionType
	{
		None = -1,
		Test,
		BirdBlock,
		BlockBlock,
		BirdPig,
		BlockPig,
		ground,
	};

	static void Collision(GameObject& obj1, GameObject& obj2);
	
	static CollisionType CheckType(GameObject& obj1, GameObject& obj2);

	static void BirdBlockCollision(GameObject& obj1, GameObject& obj2);
	static void TestCollision(GameObject& obj1, GameObject& obj2);

	static void AxisCollision(float m1, float m2, float v1, float v2, float& a1, float& a2, float res);
	static float GetAxisSpeed(float speed, float dir);
};

