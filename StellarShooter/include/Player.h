#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();

	void update();
	void draw(sf::RenderWindow& Window) const;


	void setTexture(const sf::Texture& Texture);
	// Set the player's position
	void setPosition(sf::Vector2f NewPosition);

	sf::Vector2f getPosition() const;

	sf::FloatRect getGlobalBounds() const;

	// Move the player by a given offset
	void move(float OffsetX, float OffsetY);

	// Getter for player speed
	float getSpeed() const;

	void setCollisionDirection(const sf::Vector2f& Direction);
	bool canMoveInDirection(const sf::Vector2f& Direction) const;

private:
	sf::Sprite MSprite;
	float MSpeed; // Adjust the player's movement speed
	sf::Vector2f LastCollisionDirection;
};
