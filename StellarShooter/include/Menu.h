#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"
#include "Audio.h"

class Menu
{
public:
	Menu(sf::RenderWindow& Window, Game& Game, Config& Settings, Audio& Audio);
	void show();

private:
	sf::RenderWindow& MWindow;
	Game& MGame;
	Config& MConfig;
	Audio& MAudio;

	sf::Font MFont;
	sf::Text MTitleText;
	sf::Text MPlayText;
	sf::Text MExitText;

	static bool isTextClicked(const sf::Text& Text, const sf::Vector2i& MousePos);
};
