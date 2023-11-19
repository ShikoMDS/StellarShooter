#pragma once

#include "Character.h"

#include <cmath> // Include for sqrt function
#include <iostream>

class Enemy : public Character
{
public:
	Enemy(float X, float Y);

	// Method to calculate the direction of movement towards the player
	sf::Vector2f calculateMovement(const sf::Vector2f& PlayerPosition) const;

private:
	float Speed; // Speed of the enemy
};
