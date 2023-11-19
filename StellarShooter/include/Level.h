// Level.h
#pragma once

#include "Character.h"
#include "Enemy.h"
#include "Player.h"

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Level
{
public:
	Level();
	~Level();

	bool loadFromFile(const std::string& Filename);
	void draw(sf::RenderWindow& Window) const;
	void unloadLevel();

	const sf::Vector2f& getPlayerPosition() const;
	const std::vector<Character*>& getWalls() const;
	const std::vector<Enemy*>& getEnemies() const;
	const std::vector<Character*>& getTraps() const;
	Character* getWinTile() const;

	void update();

private:
	std::vector<Character*> MWalls;
	std::vector<Character*> MTraps;
	std::vector<Enemy*> MEnemies;
	Character* MWinTile = nullptr;
	sf::Vector2f MPlayerPosition;
	Player MPlayer;

	void createLevelElement(char Type, float X, float Y);

	const float TileSize = 32.0f;
};
