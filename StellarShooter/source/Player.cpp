// Player.cpp
#include "Player.h"

Player::Player() : MSpeed(5.0f)
{
	
	// Set other properties of the player shape if needed
}

Player::~Player()
{
	// Clean up resources if needed
}

void Player::update()
{
	// Handle player input for movement
	// ...

	// Update player logic
	// You can handle movement here if needed
}

void Player::draw(sf::RenderWindow& Window)
{
	Window.draw(MSprite);
}

void Player::setTexture(const sf::Texture& texture)
{
	MSprite.setTexture(texture);
}

void Player::setPosition(sf::Vector2f NewPosition)
{
	this->MSprite.setPosition(NewPosition);
}

sf::Vector2f Player::getPosition() const
{
	return MSprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const {
	return MSprite.getGlobalBounds(); // or replace `sprite` with your graphical object
}

void Player::move(float offsetX, float offsetY) {
	MSprite.move(offsetX, offsetY);
}

float Player::getSpeed() const
{
	return MSpeed;
}

void Player::setCollisionDirection(const sf::Vector2f& direction) {
	lastCollisionDirection = direction;
}

bool Player::canMoveInDirection(const sf::Vector2f& direction) const {
	// If the direction is opposite to the collision direction, movement is allowed
	if ((direction.x < 0 && lastCollisionDirection.x > 0) ||
		(direction.x > 0 && lastCollisionDirection.x < 0) ||
		(direction.y < 0 && lastCollisionDirection.y > 0) ||
		(direction.y > 0 && lastCollisionDirection.y < 0)) {
		return true;
	}
	// No movement in the direction of the last collision
	return (direction.x == 0 || lastCollisionDirection.x == 0) &&
		(direction.y == 0 || lastCollisionDirection.y == 0);
}