#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Audio.h"
#include "Config.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	Game(Config& Settings, Audio& Audio);
	~Game();

	void start(sf::RenderWindow& Window);
	void attemptEnemyMove(Enemy& enemy, const sf::Vector2f& movement);
	bool willCollideWithWall(const Character& character, float deltaX, float deltaY);
	
	// Function to restart the level
	void restartLevel();


private:
	Level MLevel;
	Player MPlayer;
	Config& MConfig;
	Audio& MAudio;
	sf::Font MFont;

	sf::FloatRect resumeButtonBounds;
	sf::FloatRect menuButtonBounds;

	std::vector<Enemy> enemies;

	bool MIsPaused;

	void processInput();
	void attemptPlayerMove(const sf::Vector2f& movement);
	bool willCollideWithWall(float deltaX, float deltaY);
	void togglePause();
	void processConfiguration();
	void update();
	void checkAndResolveEnemyCollisions();
	void resolveEnemyCollision(Enemy& enemy1, Enemy& enemy2);

	void loadLevel(const std::string& levelPath); // Function to load a level
	bool isColliding(const sf::FloatRect& bounds1, const sf::FloatRect& bounds2);
	std::string currentLevelPath; // Store the path of the current level
};
