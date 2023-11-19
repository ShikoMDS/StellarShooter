#pragma once
#include "Character.h"

class Enemy : public Character {
public:
    Enemy(float x, float y);

    void update(const sf::Vector2f& playerPosition); // Update enemy logic, such as following the player

private:
    float speed; // Speed of the enemy

    void followPlayer(const sf::Vector2f& playerPosition); // Logic for following the player
};
