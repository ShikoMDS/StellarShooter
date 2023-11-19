#include "App.h"

App::App() : MWindow(sf::VideoMode(800, 600), "Stellar Shooter"), MAudio(MConfig), MGame(MConfig, MAudio)
{
	MConfig.loadFromFile("config.ini");
	MConfig.applySettings(MWindow);
	MAudio.updateVolume();

	// The Game object (game) is now a member variable and is constructed here
	// No need to create a local Game object
}

App::~App()
{
	// Clean up resources
	if (!MConfig.saveToFile("config.ini")) 
	{
		std::cerr << "Warning: Failed to save configuration to file." << std::endl;
	}
	// Other destructor logic...
}

void App::run()
{
	// Show the main menu before starting the game
	Menu MainMenu(MWindow, MGame, MConfig, MAudio); // Pass a reference to Game
	MainMenu.show();

	// Main game loop (if needed)
	while (MWindow.isOpen())
	{
		processInput();
		update();
		render();
	}
}

void App::processInput()
{
	sf::Event Event{};
	while (MWindow.pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			MWindow.close();
		}

		// Handle other input events for player movement, shooting, etc.
	}

	// Process input for the player
	MPlayer.update();
}

void App::update()
{
	// Update game logic, including player, enemies, traps, etc.
}

void App::render()
{
	MWindow.clear();

	// Draw game elements, UI, etc.
	//player.draw(window);

	MWindow.display();
}

void App::loadConfig()
{
	// Load configuration settings from a file using Config
	// Apply settings to the window, player, or other components
}

void App::saveProgress()
{
	// Save game progress using SaveGameManager
	// Save player position, level, and other relevant information
}
