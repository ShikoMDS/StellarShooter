#include "Character.h"

Character::Character(const CharacterType Type, const float X, const float Y) : CharType(Type)
{
	loadTexture();
	Sprite.setPosition(X, Y);
}

void Character::update()
{
	// Update logic for the character
	// This can be empty or overridden in derived classes
}

void Character::draw(sf::RenderWindow& Window) const
{
	Window.draw(Sprite);
}

const sf::Sprite& Character::getSprite() const
{
	return Sprite;
}

sf::Vector2f Character::getPosition() const
{
	return Sprite.getPosition();
}

void Character::setPosition(const sf::Vector2f& Position)
{
	Sprite.setPosition(Position);
}

void Character::move(const float DeltaX, const float DeltaY)
{
	Sprite.move(DeltaX, DeltaY);
}

sf::FloatRect Character::getGlobalBounds() const
{
	return Sprite.getGlobalBounds();
}

void Character::loadTexture()
{
	// Load different textures based on the character type
	switch (CharType)
	{
	case CharTypePlayer:
		Texture.loadFromFile("path/to/player_texture.png");
		break;
	case CharTypeWall:
		Texture.loadFromFile("Resources/Sprites/Wall.png");
		break;
	case CharTypeTrap:
		Texture.loadFromFile("Resources/Sprites/Rift.png");
		break;
	case CharTypeEnemy:
		Texture.loadFromFile("Resources/Sprites/Enemy.png");
		break;
	case CharTypeWin:
		Texture.loadFromFile("Resources/Sprites/BlackHole.png");
		break;
	// Add cases for other types
	}
	Sprite.setTexture(Texture);
}
