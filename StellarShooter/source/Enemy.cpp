#include "Enemy.h"

#include <iostream>

Enemy::Enemy(float x, float y) : Character(CharTypeEnemy, x, y), speed(2.0f)
{
	// Additional initialization if needed
}

void Enemy::update(const sf::Vector2f& playerPosition) {
    followPlayer(playerPosition);
}

void Enemy::followPlayer(const sf::Vector2f& playerPosition) {
    sf::Vector2f direction(0.f, 0.f);
    if (playerPosition.x > getPosition().x) direction.x += speed;
    if (playerPosition.x < getPosition().x) direction.x -= speed;
    if (playerPosition.y > getPosition().y) direction.y += speed;
    if (playerPosition.y < getPosition().y) direction.y -= speed;

    move(direction.x, direction.y);

    // Debugging: Log the direction values
    std::cout << "Enemy moving towards (" << direction.x << ", " << direction.y << ")" << std::endl;

}
