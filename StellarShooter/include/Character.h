#pragma once
#include <SFML/Graphics.hpp>

enum CharacterType {
    CharTypePlayer,
    CharTypeWall,
    CharTypeTrap,
    CharTypeEnemy,
    CharTypeWin,
    // Add other character types as needed
};

class Character {
public:
    Character(CharacterType type, float x, float y);
    Character();

    virtual void update(); // Marked as virtual to allow overriding in derived classes
    void draw(sf::RenderWindow& window) const;

    const sf::Sprite& getSprite() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);

    void move(float deltaX, float deltaY); // Method to move the character

    sf::FloatRect getGlobalBounds() const;

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    CharacterType charType;

    void loadTexture(); // Helper function to load texture based on character type
};
