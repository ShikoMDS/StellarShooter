#include "Game.h"

Game::Game(Config& Settings, Audio& Audio) : MConfig(Settings), MAudio(Audio), MIsPaused(false)
{
	// Rest of constructor code

	if (!MFont.loadFromFile("Resources/Fonts/Pixeled.ttf"))
	{
		// Handle font loading error
	}
}


Game::~Game() = default;

void Game::start(sf::RenderWindow& Window)
{
	// Calculate the view size to zoom in (2x zoom)
	sf::Vector2u WindowSize = Window.getSize();
	sf::View GameView(sf::FloatRect(0.f, 0.f, WindowSize.x / 2.0f, WindowSize.y / 2.0f));

	sf::View UiView(sf::FloatRect(0.f, 0.f, WindowSize.x, WindowSize.y));

	MAudio.playGameMusic();
	sf::Texture PlayerTexture;
	if (!PlayerTexture.loadFromFile("Resources/Sprites/Player.png"))
	{
		// Handle texture loading error
		return;
	}

	MPlayer.setTexture(PlayerTexture);


	// Load initial level or start a new game
	loadLevel(CurrentLevelNumber);

	// Game loop
	while (Window.isOpen())
	{
		sf::Event Event{};
		while (Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				Window.close();
			}
			else if (Event.type == sf::Event::GainedFocus)
			{
				// Resume game activities
			}
			else if (Event.type == sf::Event::LostFocus)
			{
				// Pause game activities
			}
			else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			{
				togglePause();
			}

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				if (Event.mouseButton.button == sf::Mouse::Left)
				{
					auto MousePos = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));

					if (MIsPaused)
					{
						if (ResumeButtonBounds.contains(MousePos))
						{
							// Resume button clicked
							togglePause();
						}
						else if (MenuButtonBounds.contains(MousePos))
						{
							// Menu button clicked
							// Handle transition to menu
							MAudio.playMenuMusic();
							togglePause();
							MLevel.unloadLevel();
							return;
						}
					}
				}
			}

			if (isWinScreenActive)
			{
				if (Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left)
				{
					if (auto MousePos = Window.mapPixelToCoords(sf::Mouse::getPosition(Window)); ReplayButton.
						getGlobalBounds().contains(MousePos))
					{
						// Replay button clicked
						isWinScreenActive = false;
						CurrentLevelNumber = 1;
						loadLevel(CurrentLevelNumber);
					}
					else if (MenuButton.getGlobalBounds().contains(MousePos))
					{
						// Main menu button clicked
						// Code to go to the main menu
						MAudio.playMenuMusic();
						MLevel.unloadLevel();
						CurrentLevelNumber = 1;
						isWinScreenActive = false;
						return;
					}
				}
			}
		}

		// Process input, update game logic, render, etc.
		if (Window.hasFocus() && !MIsPaused)
		{
			//MLevel.update();
			MPlayer.update(); // Update the player logic if needed
			processInput(); // Handle player input

			for (auto& Enemy : MLevel.getEnemies())
			{
				sf::Vector2f Movement = Enemy->calculateMovement(MPlayer.getPosition());
				attemptEnemyMove(*Enemy, Movement);
			}

			// Check collision with traps
			for (const auto& Trap : MLevel.getTraps())
			{
				if (isColliding(MPlayer.getGlobalBounds(), Trap->getGlobalBounds()))
				{
					// Handle collision with a trap
					MLevel.unloadLevel();
					restartLevel();
				}
			}

			// Check collision with enemies
			for (const auto& Enemy : MLevel.getEnemies())
			{
				if (isColliding(MPlayer.getGlobalBounds(), Enemy->getGlobalBounds()))
				{
					// Handle collision with an enemy
					MLevel.unloadLevel();
					restartLevel();
				}
			}

			if (playerReachedWinCondition())
			{
				advanceToNextLevel();
			}

			// Check and resolve collisions between enemies
			checkAndResolveEnemyCollisions();

			// Set the view's center to the player's position
			GameView.setCenter(MPlayer.getPosition());
		}


		processConfiguration();

		Window.clear();
		Window.setView(GameView);

		// Draw game elements, UI, etc.
		MLevel.draw(Window);
		MPlayer.draw(Window); // Draw the player

		Window.setView(UiView);
		if (MIsPaused)
		{
			sf::Text PausedText("Paused", MFont, 30);
			PausedText.setPosition(100, 100);

			sf::Text ResumeText("Resume", MFont, 24);
			ResumeText.setPosition(100, 150);
			ResumeButtonBounds = ResumeText.getGlobalBounds();

			sf::Text MenuText("Menu", MFont, 24);
			MenuText.setPosition(100, 200);
			MenuButtonBounds = MenuText.getGlobalBounds();

			Window.draw(PausedText);
			Window.draw(ResumeText);
			Window.draw(MenuText);
		}

		if (isWinScreenActive)
		{
			Window.clear(); // Clear the screen before drawing the win screen
			Window.draw(WinMessage);
			Window.draw(ReplayButton);
			Window.draw(MenuButton);
		}

		Window.display();
	}
}

void Game::attemptEnemyMove(Enemy& Enemy, const sf::Vector2f& Movement) const
{
	// Check collision separately for each axis
	if (!willCollideWithWall(Enemy, Movement.x, 0.0f))
	{
		Enemy.move(Movement.x, 0.0f);
	}
	if (!willCollideWithWall(Enemy, 0.0f, Movement.y))
	{
		Enemy.move(0.0f, Movement.y);
	}
}

bool Game::willCollideWithWall(const Character& Character, const float DeltaX, const float DeltaY) const
{
	sf::FloatRect FutureBounds = Character.getGlobalBounds();

	// Adjustments based on the enemy's sprite weirdness
	constexpr float ShrinkLeft = 1.5f;
	constexpr float ShrinkRight = 2.0f;
	constexpr float ShrinkTop = 2.0f;
	constexpr float ShrinkBottom = 2.0f;

	FutureBounds.left += ShrinkLeft;
	FutureBounds.width -= (ShrinkLeft + ShrinkRight);
	FutureBounds.top += ShrinkTop;
	FutureBounds.height -= (ShrinkTop + ShrinkBottom);

	FutureBounds.left += DeltaX;
	FutureBounds.top += DeltaY;

	for (const auto& Wall : MLevel.getWalls())
	{
		if (FutureBounds.intersects(Wall->getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

void Game::restartLevel()
{
	// Reset player's position to the starting position of the level
	MPlayer.setPosition(MLevel.getPlayerPosition());

	// Reset other game states as necessary

	// Reload the level
	loadLevel(CurrentLevelNumber);
}

void Game::processInput()
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x = -MPlayer.getSpeed();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x = MPlayer.getSpeed();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y = -MPlayer.getSpeed();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y = MPlayer.getSpeed();

	attemptPlayerMove(movement);
}

void Game::attemptPlayerMove(const sf::Vector2f& Movement)
{
	// Check and apply movement on each axis separately
	if (!playerWillCollideWithWall(Movement.x, 0.0f))
	{
		MPlayer.move(Movement.x, 0.0f);
	}
	if (!playerWillCollideWithWall(0.0f, Movement.y))
	{
		MPlayer.move(0.0f, Movement.y);
	}
}

bool Game::playerWillCollideWithWall(const float DeltaX, const float DeltaY) const
{
	sf::FloatRect FutureBounds = MPlayer.getGlobalBounds();

	// Adjustments based on the player's sprite weirdness
	constexpr float ShrinkLeft = 1.5f;
	constexpr float ShrinkRight = 2.0f;
	constexpr float ShrinkTop = 2.0f;
	constexpr float ShrinkBottom = 2.0f;

	FutureBounds.left += ShrinkLeft;
	FutureBounds.width -= (ShrinkLeft + ShrinkRight);
	FutureBounds.top += ShrinkTop;
	FutureBounds.height -= (ShrinkTop + ShrinkBottom);

	FutureBounds.left += DeltaX;
	FutureBounds.top += DeltaY;

	for (const auto& Wall : MLevel.getWalls())
	{
		if (FutureBounds.intersects(Wall->getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

void Game::togglePause()
{
	MIsPaused = !MIsPaused;
}

void Game::processConfiguration() const
{
	// Adjust sound effects volume
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
	{
		// Main keyboard '+'
		std::cout << "Main '+' key pressed" << std::endl;
		MConfig.incrementSoundVolume();
		MAudio.updateVolume();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
	{
		// Main keyboard '-'
		std::cout << "Main '-' key pressed" << std::endl;
		MConfig.decrementSoundVolume();
		MAudio.updateVolume();
	}

	// Adjust music volume
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		// Numpad '+'
		std::cout << "Numpad '+' key pressed" << std::endl;
		MConfig.incrementMusicVolume();
		MAudio.updateVolume();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		// Numpad '-'
		std::cout << "Numpad '-' key pressed" << std::endl;
		MConfig.decrementMusicVolume();
		MAudio.updateVolume();
	}
}

void Game::update()
{
	// Update player...
	MPlayer.update();

	auto& Enemies = MLevel.getEnemies();

	// Update each enemy
	for (auto& Enemy : Enemies)
	{
		sf::Vector2f PlayerPosition = MPlayer.getPosition();

		// Calculate enemy's new position
		// Rest of the logic
	}
}

void Game::checkAndResolveEnemyCollisions() const
{
	for (size_t I = 0; I < MLevel.getEnemies().size(); ++I)
	{
		for (size_t J = I + 1; J < MLevel.getEnemies().size(); ++J)
		{
			Enemy* Enemy1 = MLevel.getEnemies()[I];
			Enemy* Enemy2 = MLevel.getEnemies()[J];

			if (Enemy1->getGlobalBounds().intersects(Enemy2->getGlobalBounds()))
			{
				// Handle collision
				// Prevent enemies from overlapping or adjust their positions
				resolveEnemyCollision(*Enemy1, *Enemy2);
			}
		}
	}
}

void Game::resolveEnemyCollision(Enemy& Enemy1, Enemy& Enemy2) const
{
	// Implement collision resolution logic here
	// Push the enemies away from each other
	sf::Vector2f Direction = Enemy1.getPosition() - Enemy2.getPosition();
	const float Length = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);

	if (Length != 0)
	{
		Direction /= Length; // Normalize the direction vector
		const float Overlap = 0.1f * (Length - Enemy1.getGlobalBounds().width);
		Enemy1.move(Overlap * Direction.x, Overlap * Direction.y);
		Enemy2.move(-Overlap * Direction.x, -Overlap * Direction.y);
	}
}

void Game::loadLevel(const int LevelNumber)
{
	const std::string LevelFilename = "Resources/Levels/Level" + std::to_string(LevelNumber) + ".txt";
	if (MLevel.loadFromFile(LevelFilename))
	{
		std::cout << "Level " << LevelNumber << " loaded successfully." << std::endl;
		MPlayer.setPosition(MLevel.getPlayerPosition());
		// Reset or reinitialize other necessary elements
	}
	else
	{
		std::cerr << "Failed to load level " << LevelNumber << "." << std::endl;
		// Handle error
		MLevel.unloadLevel();
		showWinScreen();
	}
}

bool Game::isColliding(const sf::FloatRect& Bounds1, const sf::FloatRect& Bounds2)
{
	return Bounds1.intersects(Bounds2);
}

bool Game::playerReachedWinCondition() const
{
	if (MLevel.getWinTile() && isColliding(MPlayer.getGlobalBounds(), MLevel.getWinTile()->getGlobalBounds()))
	{
		return true;
	}
	return false;
}

void Game::advanceToNextLevel()
{
	MLevel.unloadLevel();
	CurrentLevelNumber++;
	loadLevel(CurrentLevelNumber);
}

void Game::showWinScreen()
{
	isWinScreenActive = true;


	// Set up the win message
	WinMessage.setFont(MFont);
	WinMessage.setString("You Win!");
	WinMessage.setCharacterSize(50);
	WinMessage.setPosition(100, 100);
	WinMessage.setFillColor(sf::Color::White);

	// Set up the replay button
	ReplayButton.setFont(MFont);
	ReplayButton.setString("Replay");
	ReplayButton.setCharacterSize(30);
	ReplayButton.setPosition(100, 200);
	ReplayButton.setFillColor(sf::Color::White);

	// Set up the main menu button
	MenuButton.setFont(MFont);
	MenuButton.setString("Main Menu");
	MenuButton.setCharacterSize(30);
	MenuButton.setPosition(100, 300);
	MenuButton.setFillColor(sf::Color::White);
}
