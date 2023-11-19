// Player.h
#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();

	void update();
	void draw(sf::RenderWindow& Window);


	void setTexture(const sf::Texture& texture);
	// Set the player's position
	void setPosition(sf::Vector2f NewPosition);

	sf::Vector2f getPosition() const;

	sf::FloatRect getGlobalBounds() const;

	// Move the player by a given offset
	void move(float offsetX, float offsetY);

	// Getter for player speed
	float getSpeed() const;

	void setCollisionDirection(const sf::Vector2f& direction);
	bool canMoveInDirection(const sf::Vector2f& direction) const;

private:
	sf::Sprite MSprite; // For simplicity, you can use a rectangle as the player representation
	float MSpeed; // Adjust the player's movement speed
	sf::Vector2f lastCollisionDirection;
};
