#include "Enemy.h"

Enemy::Enemy(float x, float y) : Character(CharTypeEnemy, x, y), speed(1.0f)
{
	// Additional initialization if needed
}

void Enemy::update(const sf::Vector2f& playerPosition) {
    followPlayer(playerPosition);
}

void Enemy::followPlayer(const sf::Vector2f& playerPosition) {
    // Calculate the direction vector between the enemy and the player
    sf::Vector2f direction = playerPosition - getPosition();

    // Normalize the direction vector (so its length is 1)
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    // Multiply the normalized direction by the enemy's speed
    direction.x *= speed;
    direction.y *= speed;

    // Uncomment the below line to check for collisions with the game's collision function
    // if (!game.willCollideWithWall(*this, direction.x, direction.y)) {
    move(direction.x, direction.y);
    // }

    // Debugging: Output the enemy's new position and the direction it is moving
    std::cout << "Enemy position: (" << getPosition().x << ", " << getPosition().y << ")" << std::endl;
    std::cout << "Player position: (" << playerPosition.x << ", " << playerPosition.y << ")" << std::endl;
    std::cout << "Calculated direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
}