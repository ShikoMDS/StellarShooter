#pragma once

#include "Audio.h"
#include "Config.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow& Window, Game& Game, Config& Settings, Audio& Audio);
	void show() const;

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
