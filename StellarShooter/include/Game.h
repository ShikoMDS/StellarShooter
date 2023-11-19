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
	bool willCollideWithWall(const Character& character, float deltaX, float deltaY);
	bool willCollide(const sf::FloatRect& futureBounds, const std::vector<sf::Sprite>& walls);
	

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
	bool willCollideWithWall(float deltaX, float deltaY);
	void togglePause();
	void processConfiguration();
	void update();
};
