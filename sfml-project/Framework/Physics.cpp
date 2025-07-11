#include "stdafx.h"
#include "Physics.h"
#include "SpriteGo.h"

void Physics::Collision(GameObject& obj1, GameObject& obj2)
{
	switch (CheckType(obj1, obj2))
	{
	case CollisionType::BirdBlock:
		Physics::BirdBlockCollision(obj1, obj2);
		break;
	case CollisionType::Test:
		Physics::TestCollision(obj1, obj2);
		break;
	default:
		break;
	}
}

Physics::CollisionType Physics::CheckType(GameObject& obj1, GameObject& obj2)
{
	std::string name1 = obj1.GetName();
	std::string name2 = obj2.GetName();
	if (name1 == "Bird" && name2 == "Block")
	{
		return Physics::CollisionType::BirdBlock;
	}
	else if (name1 == "Object1" && name2 == "Object2")
	{
		return Physics::CollisionType::Test;
	}
	else
	{
		return Physics::CollisionType::None;
	}
}

void Physics::BirdBlockCollision(GameObject& obj1, GameObject& obj2)
{
	float restitution = 0.5f;

}
void Physics::TestCollision(GameObject& obj1, GameObject& obj2)
{
	float restitution = 0.5f;

	sf::Vector2f dir1 = obj1.GetDirection();
	sf::Vector2f dir2 = obj2.GetDirection();

	float speed1 = obj1.GetSpeed();
	float speed2 = obj2.GetSpeed();

	float mass1 = obj1.GetMass();
	float mass2 = obj2.GetMass();
	/*float friction1 = obj1.GetFriction();
	float friction2 = obj2.GetFriction();*/

	float xSpeed1 = speed1 * dir1.x;
	float ySpeed1 = speed1 * dir1.y;
	float xSpeed2 = speed2 * dir2.x;
	float ySpeed2 = speed2 * dir2.y;

	float afterXSpeed1 = 0.f, afterYSpeed1 = 0.f, afterXSpeed2 = 0.f, afterYSpeed2 = 0.f;

	Physics::AxisCollision(mass1, mass2, xSpeed1, xSpeed2, afterXSpeed1, afterXSpeed2, restitution);
	Physics::AxisCollision(mass1, mass2, ySpeed1, ySpeed2, afterYSpeed1, afterYSpeed2, restitution);

	sf::Vector2f newDirection1 = Utils::GetNormal(sf::Vector2f(afterXSpeed1, afterYSpeed1));
	sf::Vector2f newDirection2 = Utils::GetNormal(sf::Vector2f(afterXSpeed2, afterYSpeed2));

	float newSpeed1 = afterXSpeed1 * newDirection1.x + afterYSpeed1 * newDirection1.y;
	float newSpeed2 = afterXSpeed2 * newDirection2.x + afterYSpeed2 * newDirection2.y;
	
	obj1.SetSpeed(newSpeed1);
	obj2.SetSpeed(newSpeed2);
	obj1.SetDirection(newDirection1);
	obj2.SetDirection(newDirection2);
}

void Physics::AxisCollision(float m1, float m2, float v1, float v2, float& a1, float& a2, float res)
{
	float close = std::abs(v1 - v2) * res;
	float initEnergy = m1 * v1 + m2 * v2;
	float sumMass = m1 + m2;
	a2 = (initEnergy + close * m1) / sumMass;
	a1 = (initEnergy - a2 * m2) / m1;
}
