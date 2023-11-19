#include "Enemy.h"

Enemy::Enemy(float x, float y) : Character(CharTypeEnemy, x, y), speed(1.0f) {
    // Additional initialization if needed
}

sf::Vector2f Enemy::calculateMovement(const sf::Vector2f& playerPosition) {
    sf::Vector2f direction = playerPosition - getPosition();

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    // Multiply by speed
    direction.x *= speed;
    direction.y *= speed;

    // Return the calculated direction for the enemy to move
    return direction;
}