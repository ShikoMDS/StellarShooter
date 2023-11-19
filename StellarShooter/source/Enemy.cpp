#include "Enemy.h"

Enemy::Enemy(const float X, const float Y) : Character(CharTypeEnemy, X, Y), Speed(1.0f)
{
	// Additional initialization if needed
}

sf::Vector2f Enemy::calculateMovement(const sf::Vector2f& PlayerPosition) const
{
	sf::Vector2f Direction = PlayerPosition - getPosition();

	// Normalize the direction vector
	const float Length = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
	if (Length != 0)
	{
		Direction.x /= Length;
		Direction.y /= Length;
	}

	// Multiply by speed
	Direction.x *= Speed;
	Direction.y *= Speed;

	// Return the calculated direction for the enemy to move
	return Direction;
}
