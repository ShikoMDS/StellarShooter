#pragma once

#include "Audio.h"
#include "Config.h"
#include "Game.h"
#include "Level.h"
#include "Menu.h"
#include "Player.h"

#include <SFML/Graphics.hpp>

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
};
