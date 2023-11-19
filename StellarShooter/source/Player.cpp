#include "Player.h"

Player::Player() : MSpeed(5.0f)
{
	// Set other properties of the player shape
}

Player::~Player()
{
	// Clean up resources
}

void Player::update()
{
	float MoveX = 0.0f, MoveY = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		MoveX -= getSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		MoveX += getSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		MoveY -= getSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		MoveY += getSpeed();
	}

	// Check for collisions here

	move(MoveX, MoveY);
}

void Player::draw(sf::RenderWindow& Window) const
{
	Window.draw(MSprite);
}

void Player::setTexture(const sf::Texture& Texture)
{
	MSprite.setTexture(Texture);
}

void Player::setPosition(const sf::Vector2f NewPosition)
{
	this->MSprite.setPosition(NewPosition);
}

sf::Vector2f Player::getPosition() const
{
	return MSprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
	return MSprite.getGlobalBounds();
}

void Player::move(const float OffsetX, const float OffsetY)
{
	MSprite.move(OffsetX, OffsetY);
}

float Player::getSpeed() const
{
	return MSpeed;
}

void Player::setCollisionDirection(const sf::Vector2f& Direction)
{
	LastCollisionDirection = Direction;
}

bool Player::canMoveInDirection(const sf::Vector2f& Direction) const
{
	// If the direction is opposite to the collision direction, movement is allowed
	if ((Direction.x < 0 && LastCollisionDirection.x > 0) ||
		(Direction.x > 0 && LastCollisionDirection.x < 0) ||
		(Direction.y < 0 && LastCollisionDirection.y > 0) ||
		(Direction.y > 0 && LastCollisionDirection.y < 0))
	{
		return true;
	}
	// No movement in the direction of the last collision
	return (Direction.x == 0 || LastCollisionDirection.x == 0) &&
		(Direction.y == 0 || LastCollisionDirection.y == 0);
}
