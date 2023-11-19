#include "Character.h"

Character::Character(CharacterType type, float x, float y) : charType(type) {
    loadTexture();
    sprite.setPosition(x, y);
}

void Character::update() {
    // Update logic for the character
    // This can be empty or overridden in derived classes
}

void Character::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

const sf::Sprite& Character::getSprite() const {
    return sprite;
}

sf::Vector2f Character::getPosition() const {
    return sprite.getPosition();
}

void Character::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Character::move(float deltaX, float deltaY) {
    sprite.move(deltaX, deltaY);
}

sf::FloatRect Character::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

void Character::loadTexture() {
    // Load different textures based on the character type
    switch (charType) {
    case CharTypePlayer:
        texture.loadFromFile("path/to/player_texture.png");
        break;
    case CharTypeWall:
        texture.loadFromFile("Resources/Sprites/Wall.png");
        break;
    case CharTypeTrap:
        texture.loadFromFile("Resources/Sprites/Rift.png");
        break;
    case CharTypeEnemy:
        texture.loadFromFile("Resources/Sprites/Enemy.png");
        break;
    case CharTypeWin:
        texture.loadFromFile("Resources/Sprites/BlackHole.png");
        break;
        // Add cases for other types
    }
    sprite.setTexture(texture);
}
