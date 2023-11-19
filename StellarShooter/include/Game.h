#pragma once

#include "Audio.h"
#include "Config.h"
#include "Enemy.h"
#include "Level.h"
#include "Player.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(Config& Settings, Audio& Audio);
	~Game();

	void start(sf::RenderWindow& Window);
	void attemptEnemyMove(Enemy& Enemy, const sf::Vector2f& Movement) const;
	bool willCollideWithWall(const Character& Character, float DeltaX, float DeltaY) const;

	// Function to restart the level
	void restartLevel();

private:
	Level MLevel;
	Player MPlayer;
	Config& MConfig;
	Audio& MAudio;
	sf::Font MFont;

	int CurrentLevelNumber = 1; // Start with level 1

	sf::FloatRect ResumeButtonBounds;
	sf::FloatRect MenuButtonBounds;

	std::vector<Enemy> Enemies;

	bool MIsPaused;

	void processInput();
	void attemptPlayerMove(const sf::Vector2f& Movement);
	bool playerWillCollideWithWall(float DeltaX, float DeltaY) const;
	void togglePause();
	void processConfiguration() const;
	void update();
	void checkAndResolveEnemyCollisions() const;
	void resolveEnemyCollision(Enemy& Enemy1, Enemy& Enemy2) const;

	void loadLevel(int LevelNumber); // Function to load a level
	static bool isColliding(const sf::FloatRect& Bounds1, const sf::FloatRect& Bounds2);
	bool playerReachedWinCondition() const;
	void advanceToNextLevel();
	void showWinScreen();
	std::string CurrentLevelPath; // Store the path of the current level

	bool isWinScreenActive = false;
	sf::Text WinMessage;
	sf::Text ReplayButton;
	sf::Text MenuButton;
};
