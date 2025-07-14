#pragma once
#include "TextGo.h"

class ShootCountUI : public TextGo
{
protected:
	int shootcount;

public:
	ShootCountUI(const std::string& fontId = "fonts/DS-DIGIT.ttf", const std::string& name = "");
	virtual ~ShootCountUI() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetCount(int count);
};

