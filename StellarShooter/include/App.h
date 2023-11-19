#pragma once

#include <SFML/Graphics.hpp>

#include "Audio.h"
#include "Config.h"
#include "Level.h"
#include "Player.h"
#include "Menu.h"
#include "Game.h"

class App
{
public:
	App();
	~App();

	void run();

private:
	void processInput();
	void update();
	void render();

	void loadConfig();
	void saveProgress();
	

	sf::RenderWindow MWindow;
	Player MPlayer;
	Config MConfig;
	Audio MAudio;
	Level MLevel;
	Game MGame;
	// Add other necessary variables and functions here
};
