#pragma once
class HitBox
{
public:
	enum class Type
	{
		Rectangle,
		Circle,
	};

	HitBox();
	Type type;

	sf::RectangleShape rect;
	sf::CircleShape circle;

	void UpdateTransform(const sf::Transformable& tr, const sf::FloatRect& localBounds);
	void UpdateTransform(const sf::Transformable& tr, float radius);
	void Draw(sf::RenderWindow& window);

	void SetType(Type ty) { type = ty; }
};

