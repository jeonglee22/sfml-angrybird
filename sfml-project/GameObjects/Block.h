#pragma once
#include "PhysicsBody.h"
class Block : public PhysicsBody
{
protected:
	int hp = 0;
	int maxHp = 100;
	bool isDead = false;
	bool isPlayDestroySound = true;

	std::string destroySound;
	std::string damageSound;

public:
	Block(const std::string& texId = "", const std::string& name = "");
	virtual ~Block() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	b2ShapeId GetShapeId() { return shapeId; }
	int GetHp() { return hp; }

	void SetInitPos(const sf::Vector2f& pos) { SetBoxPos(pos.x, pos.y); }
	void SetHP(int hp) { maxHp = hp; }

	void TakeDamage(int damage);

	bool IsDead() { return isDead; }
	void SetNotDead() { isDead = false; }

	void SetDestroySound(const std::string& s) { destroySound = s; }
	void PlayDestroySound() { 
		if(isPlayDestroySound)
		{
			isPlayDestroySound = false;
			SOUND_MGR.PlaySfx(destroySound);
		}
	}
	void SetDamageSound(const std::string& s) { damageSound = s; }
	void PlayDamageSound() { SOUND_MGR.PlaySfx(damageSound);}
};

