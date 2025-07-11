#include "stdafx.h"
#include "HitBox.h"

HitBox::HitBox()
{
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(1.f);

	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(1.f);
}

void HitBox::UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds)
{
	if (type == Type::Rectangle)
	{
		rect.setSize({ localBounds.width, localBounds.height });
		rect.setOutlineColor(sf::Color::Red);
		rect.setOrigin(tr.getOrigin());
		rect.setPosition(tr.getPosition());
		rect.setScale(tr.getScale());
		rect.setRotation(tr.getRotation());
	}
}
void HitBox::UpdateTransform(const sf::Transformable& tr, float radius)
{
	if (type == Type::Circle)
	{
		circle.setRadius(radius);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOrigin(tr.getOrigin());
		circle.setPosition(tr.getPosition());
		circle.setScale(tr.getScale());
		circle.setRotation(tr.getRotation());
	}
}

void HitBox::Draw(sf::RenderWindow& window)
{
	if (Variables::isDrawHitBox && type == Type::Rectangle)
	{
		window.draw(rect);
	}
	else if (Variables::isDrawHitBox && type == Type::Circle)
	{
		window.draw(circle);
	}
}
