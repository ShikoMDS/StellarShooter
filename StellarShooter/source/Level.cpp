// Level.cpp
#include "Level.h"


Level::Level() {
    // Load textures or any other initial setup
}

Level::~Level() {
    unloadLevel();
}

bool Level::loadFromFile(const std::string& Filename) {
    std::ifstream File(Filename);
    if (!File.is_open()) {
        std::cerr << "Failed to open level file: " << Filename << std::endl;
        return false;
    }

    std::string Line;
    size_t Y = 0;
    while (std::getline(File, Line)) {
        for (size_t X = 0; X < Line.size(); ++X) {
            createLevelElement(Line[X], X * tileSize, Y * tileSize);
        }
        Y++;
    }
    File.close();
    return true;
}

void Level::createLevelElement(char type, float x, float y) {
    switch (type) {
    case 'x':
        walls.push_back(new Character(CharTypeWall, x, y));
        break;
    case 't':
        traps.push_back(new Character(CharTypeTrap, x, y));
        break;
    case 'e': // Enemy
        enemies.push_back(new Enemy(x, y));
        break;
    case 'w':
        winTile = new Character(CharTypeWin, x, y);
        break;
    case 's':
        playerPosition = sf::Vector2f(x, y);
        break;
        // Additional cases as needed
    }
}

void Level::draw(sf::RenderWindow& Window) const {
    for (const auto& wall : walls) {
        Window.draw(wall->getSprite());
    }
    for (const auto& trap : traps) {
        Window.draw(trap->getSprite());
    }
    for (const auto& enemy : enemies) {
        Window.draw(enemy->getSprite());
    }
    if (winTile) {
        Window.draw(winTile->getSprite());
    }
}

void Level::unloadLevel() {
    for (auto& wall : walls) delete wall;
    walls.clear();

    for (auto& trap : traps) delete trap;
    traps.clear();

    for (auto& enemy : enemies) delete enemy;
    enemies.clear();

    delete winTile;
    winTile = nullptr;
}

const sf::Vector2f& Level::getPlayerPosition() const {
    return playerPosition;
}

const std::vector<Character*>& Level::getWalls() const {
    return walls;
}

const std::vector<Enemy*>& Level::getEnemies() const {
    return enemies;
}

void Level::update() {
    // Update logic for the level
    // For example, update enemies, traps, or other dynamic elements within the level
    for (auto& enemy : enemies) {
        enemy->update(MPlayer.getPosition()); // Assuming enemies chase the player
    }
    // ... other update logic ...
}
