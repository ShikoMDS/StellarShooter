#include "Game.h"

Game::Game(Config& Settings, Audio& Audio) : MConfig(Settings), MAudio(Audio), MIsPaused(false)
{
	// Rest of your constructor code

	if (!MFont.loadFromFile("Resources/Fonts/Pixeled.ttf"))
	{
		// Handle font loading error
	}
}


Game::~Game()
{
}

void Game::start(sf::RenderWindow& Window)
{
	// Calculate the view size to zoom in (2x zoom)
	//sf::Vector2u windowSize = Window.getSize();
	//sf::View view(sf::FloatRect(0.f, 0.f, windowSize.x / 2.0f, windowSize.y / 2.0f));


	MAudio.playGameMusic();
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Resources/Sprites/Player.png")) {
		// Handle texture loading error
		return;
	}

	MPlayer.setTexture(playerTexture);


	// Load initial level or start a new game
	loadLevel("Resources/Levels/level1.txt");

	// Game loop
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Window.close();
			}
			else if (event.type == sf::Event::GainedFocus)
			{
				// Resume game activities
			}
			else if (event.type == sf::Event::LostFocus)
			{
				// Pause game activities
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
			{
				togglePause();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f mousePos = static_cast<sf::Vector2f>(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)));

					if (MIsPaused) {
						if (resumeButtonBounds.contains(mousePos)) {
							// Resume button clicked
							togglePause();
						}
						else if (menuButtonBounds.contains(mousePos)) {
							// Menu button clicked
							// Handle transition to menu
						}
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

			// In Game::start method
			for (auto& enemy : MLevel.getEnemies()) {
				sf::Vector2f movement = enemy->calculateMovement(MPlayer.getPosition());
				attemptEnemyMove(*enemy, movement);
			}

			// Check collision with traps
			for (const auto& trap : MLevel.getTraps()) {
				if (isColliding(MPlayer.getGlobalBounds(), trap->getGlobalBounds())) {
					// Handle collision with a trap (e.g., reduce player health)
					MLevel.unloadLevel();
					restartLevel();
				}
			}

			// Check collision with enemies
			for (const auto& enemy : MLevel.getEnemies()) {
				if (isColliding(MPlayer.getGlobalBounds(), enemy->getGlobalBounds())) {
					// Handle collision with an enemy (e.g., reduce player health or restart level)
					MLevel.unloadLevel();
					restartLevel();
				}
			}

			// Check and resolve collisions between enemies
			checkAndResolveEnemyCollisions();

			// Optionally, set the view's center to the player's position or another focal point
			//view.setCenter(MPlayer.getPosition());
			//Window.setView(view);
		}

		processConfiguration();

		Window.clear();

		// Draw game elements, UI, etc.
		MLevel.draw(Window);
		MPlayer.draw(Window); // Draw the player

		if (MIsPaused) {
			sf::Text PausedText("Paused", MFont, 30);
			PausedText.setPosition(100, 100); // Set to appropriate position

			sf::Text resumeText("Resume", MFont, 24);
			resumeText.setPosition(100, 150); // Set to appropriate position
			resumeButtonBounds = resumeText.getGlobalBounds(); // Get the bounds

			sf::Text menuText("Menu", MFont, 24);
			menuText.setPosition(100, 200); // Set to appropriate position
			menuButtonBounds = menuText.getGlobalBounds(); // Get the bounds

			Window.draw(PausedText);
			Window.draw(resumeText);
			Window.draw(menuText);
		}


		Window.display();
	}
}

void Game::attemptEnemyMove(Enemy& enemy, const sf::Vector2f& movement) {
	// Check collision separately for each axis
	if (!willCollideWithWall(enemy, movement.x, 0.0f)) {
		enemy.move(movement.x, 0.0f);
	}
	if (!willCollideWithWall(enemy, 0.0f, movement.y)) {
		enemy.move(0.0f, movement.y);
	}
}

bool Game::willCollideWithWall(const Character& character, float deltaX, float deltaY) {
	sf::FloatRect futureBounds = character.getGlobalBounds();

	// Adjustments based on the character's sprite
	const float shrinkLeft = 1.5f;
	const float shrinkRight = 2.0f;
	const float shrinkTop = 2.0f;
	const float shrinkBottom = 2.0f;

	futureBounds.left += shrinkLeft;
	futureBounds.width -= (shrinkLeft + shrinkRight);
	futureBounds.top += shrinkTop;
	futureBounds.height -= (shrinkTop + shrinkBottom);

	futureBounds.left += deltaX;
	futureBounds.top += deltaY;

	for (const auto& wall : MLevel.getWalls()) {
		if (futureBounds.intersects(wall->getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

void Game::restartLevel() {
	// Reset player's position to the starting position of the level
	MPlayer.setPosition(MLevel.getPlayerPosition());

	// Reset other game states as necessary (e.g., player health, score)

	// Reload the level
	loadLevel(currentLevelPath);

	// Reset any other necessary states (e.g., enemy positions)
}

void Game::processInput() {
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x = -MPlayer.getSpeed();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x = MPlayer.getSpeed();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y = -MPlayer.getSpeed();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y = MPlayer.getSpeed();

	attemptPlayerMove(movement);
}

void Game::attemptPlayerMove(const sf::Vector2f& movement) {
	// Check and apply movement on each axis separately
	if (!willCollideWithWall(movement.x, 0.0f)) {
		MPlayer.move(movement.x, 0.0f);
	}
	if (!willCollideWithWall(0.0f, movement.y)) {
		MPlayer.move(0.0f, movement.y);
	}
}

bool Game::willCollideWithWall(float deltaX, float deltaY) {
	sf::FloatRect futureBounds = MPlayer.getGlobalBounds();

	// Adjust these values based on your sprite's specific characteristics
	const float shrinkLeft = 1.5f;
	const float shrinkRight = 2.0f;
	const float shrinkTop = 2.0f;
	const float shrinkBottom = 2.0f;

	futureBounds.left += shrinkLeft;
	futureBounds.width -= (shrinkLeft + shrinkRight);
	futureBounds.top += shrinkTop;
	futureBounds.height -= (shrinkTop + shrinkBottom);

	futureBounds.left += deltaX;
	futureBounds.top += deltaY;

	for (const auto& wall : MLevel.getWalls()) {
		if (futureBounds.intersects(wall->getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

void Game::togglePause()
{
	MIsPaused = !MIsPaused;
}

void Game::processConfiguration()
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

void Game::update() {
    // Update player...
    MPlayer.update();

    // Assuming MLevel is an instance of Level class in the Game class
    auto& enemies = MLevel.getEnemies();

    // Update each enemy
    for (auto& enemy : enemies) {
        sf::Vector2f playerPosition = MPlayer.getPosition();

        // Calculate enemy's new position
        // ... Rest of the logic ...
    }
}

void Game::checkAndResolveEnemyCollisions() {
	for (size_t i = 0; i < MLevel.getEnemies().size(); ++i) {
		for (size_t j = i + 1; j < MLevel.getEnemies().size(); ++j) {
			Enemy* enemy1 = MLevel.getEnemies()[i];
			Enemy* enemy2 = MLevel.getEnemies()[j];

			if (enemy1->getGlobalBounds().intersects(enemy2->getGlobalBounds())) {
				// Handle collision
				// For example, prevent enemies from overlapping or adjust their positions
				resolveEnemyCollision(*enemy1, *enemy2);
			}
		}
	}
}

void Game::resolveEnemyCollision(Enemy& enemy1, Enemy& enemy2) {
	// Implement collision resolution logic here
	// For example, you might push the enemies away from each other
	sf::Vector2f direction = enemy1.getPosition() - enemy2.getPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length != 0) {
		direction /= length; // Normalize the direction vector
		float overlap = 0.5f * (length - enemy1.getGlobalBounds().width);
		enemy1.move(overlap * direction.x, overlap * direction.y);
		enemy2.move(-overlap * direction.x, -overlap * direction.y);
	}
}

void Game::loadLevel(const std::string& levelPath) {
	currentLevelPath = levelPath; // Store the current level path
	MLevel.loadFromFile(levelPath); // Load the level using Level class method
	// Additional setup as needed (e.g., setting enemy positions)
	MPlayer.setPosition(MLevel.getPlayerPosition());
}

bool Game::isColliding(const sf::FloatRect& bounds1, const sf::FloatRect& bounds2) {
	return bounds1.intersects(bounds2);
}
