#pragma once

#include <SFML/Graphics.hpp>

enum CharacterType
{
	CharTypePlayer,
	CharTypeWall,
	CharTypeTrap,
	CharTypeEnemy,
	CharTypeWin,
};

class Character
{
public:
	Character(CharacterType Type, float X, float Y);

	virtual void update(); // Marked as virtual to allow overriding in derived classes
	void draw(sf::RenderWindow& Window) const;

	const sf::Sprite& getSprite() const;
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& Position);

	void move(float DeltaX, float DeltaY); // Method to move the character

	sf::FloatRect getGlobalBounds() const;

protected:
	sf::Sprite Sprite;
	sf::Texture Texture;
	CharacterType CharType;

	void loadTexture(); // Helper function to load texture based on character type
};
