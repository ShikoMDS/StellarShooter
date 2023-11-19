#include "Menu.h"

Menu::Menu(sf::RenderWindow& Window, Game& Game, Config& Settings, Audio& Audio)
	: MWindow(Window), MGame(Game), MConfig(Settings), MAudio(Audio)
{
	if (!MFont.loadFromFile("Resources/Fonts/Pixeled.ttf"))
	{
		// Handle font loading error
	}

	MTitleText.setFont(MFont);
	MTitleText.setString("Main Menu");
	MTitleText.setCharacterSize(30);
	MTitleText.setPosition(200.f, 50.f);

	MPlayText.setFont(MFont);
	MPlayText.setString("Play");
	MPlayText.setCharacterSize(20);
	MPlayText.setPosition(250.f, 150.f);

	MExitText.setFont(MFont);
	MExitText.setString("Exit");
	MExitText.setCharacterSize(20);
	MExitText.setPosition(250.f, 200.f);
}

void Menu::show()
{
	MAudio.playMenuMusic();
	while (MWindow.isOpen())
	{
		sf::Event Event{};
		while (MWindow.pollEvent(Event))
		{

			if (Event.type == sf::Event::Closed)
			{
				MWindow.close();
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i MousePos = sf::Mouse::getPosition(MWindow);

				if (isTextClicked(MPlayText, MousePos))
				{
					std::cout << "Play button clicked!" << std::endl;
					MGame.start(MWindow);
				}
				else if (isTextClicked(MExitText, MousePos))
				{
					MWindow.close();
				}
			}

			// Volume control
			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Equal)
				{
					MConfig.incrementSoundVolume();
					MAudio.updateVolume();
				}
				else if (Event.key.code == sf::Keyboard::Hyphen)
				{
					MConfig.decrementSoundVolume();
					MAudio.updateVolume();
				}
				else if (Event.key.code == sf::Keyboard::Add)
				{
					MConfig.incrementMusicVolume();
					MAudio.updateVolume();
				}
				else if (Event.key.code == sf::Keyboard::Subtract)
				{
					MConfig.decrementMusicVolume();
					MAudio.updateVolume();
				}
			}
		}

		MWindow.clear();
		MWindow.draw(MTitleText);
		MWindow.draw(MPlayText);
		MWindow.draw(MExitText);
		MWindow.display();
	}
}

bool Menu::isTextClicked(const sf::Text& Text, const sf::Vector2i& MousePos)
{
	return Text.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePos));
}
