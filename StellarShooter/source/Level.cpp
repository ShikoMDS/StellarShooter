// Level.cpp
#include "Level.h"


Level::Level()
{
	// Load textures or any other initial setup
}

Level::~Level()
{
	unloadLevel();
}

bool Level::loadFromFile(const std::string& Filename)
{
	std::ifstream File(Filename);
	if (!File.is_open())
	{
		std::cerr << "Failed to open level file: " << Filename << std::endl;
		return false;
	}

	std::string Line;
	size_t Y = 0;
	while (std::getline(File, Line))
	{
		for (size_t X = 0; X < Line.size(); ++X)
		{
			createLevelElement(Line[X], X * TileSize, Y * TileSize);
		}
		Y++;
	}
	File.close();
	return true;
}

void Level::createLevelElement(const char Type, const float X, const float Y)
{
	switch (Type)
	{
	case 'x': // Walls
		MWalls.push_back(new Character(CharTypeWall, X, Y));
		break;
	case 't': // Traps
		MTraps.push_back(new Character(CharTypeTrap, X, Y));
		break;
	case 'e': // Enemy
		MEnemies.push_back(new Enemy(X, Y));
		break;
	case 'w': // Win Tile
		MWinTile = new Character(CharTypeWin, X, Y);
		break;
	case 's': // Player position
		MPlayerPosition = sf::Vector2f(X, Y);
		break;
	// Additional cases as needed
	}
}

void Level::draw(sf::RenderWindow& Window) const
{
	for (const auto& Wall : MWalls)
	{
		Window.draw(Wall->getSprite());
	}
	for (const auto& Trap : MTraps)
	{
		Window.draw(Trap->getSprite());
	}
	for (const auto& Enemy : MEnemies)
	{
		Window.draw(Enemy->getSprite());
	}
	if (MWinTile)
	{
		Window.draw(MWinTile->getSprite());
	}
}

void Level::unloadLevel()
{
	for (const auto& Wall : MWalls) delete Wall;
	MWalls.clear();

	for (const auto& Trap : MTraps) delete Trap;
	MTraps.clear();

	for (const auto& Enemy : MEnemies) delete Enemy;
	MEnemies.clear();

	delete MWinTile;
	MWinTile = nullptr;
}

const sf::Vector2f& Level::getPlayerPosition() const
{
	return MPlayerPosition;
}

const std::vector<Character*>& Level::getWalls() const
{
	return MWalls;
}

const std::vector<Enemy*>& Level::getEnemies() const
{
	return MEnemies;
}

const std::vector<Character*>& Level::getTraps() const
{
	return MTraps;
}

Character* Level::getWinTile() const
{
	return MWinTile;
}

void Level::update()
{
}
