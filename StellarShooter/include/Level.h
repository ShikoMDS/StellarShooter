// Level.h
#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>

#include "Character.h" // Assuming Character class can be used for walls, traps, enemies, etc.
#include "Enemy.h"     // Assuming you have an Enemy class
#include "Player.h"

class Level {
public:
    Level();
    ~Level();

    bool loadFromFile(const std::string& Filename);
    void draw(sf::RenderWindow& Window) const;
    void unloadLevel();

    const sf::Vector2f& getPlayerPosition() const;
    const std::vector<Character*>& getWalls() const;
    const std::vector<Enemy*>& getEnemies() const;
    void update();

private:
    std::vector<Character*> walls;
    std::vector<Character*> traps;
    std::vector<Enemy*> enemies;
    Character* winTile = nullptr;
    sf::Vector2f playerPosition;
    Player MPlayer;

    void createLevelElement(char type, float x, float y);
    void clearLevel();

    const float tileSize = 32.0f;
};
