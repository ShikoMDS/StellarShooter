#include "Audio.h"

Audio::Audio(const Config& Config) : MConfig(Config)
{
	// Load sound and music resources
	if (!MShootBuffer.loadFromFile("path_to_shoot.wav"))
	{
		// Handle error loading shoot sound
	}

	if (!MPlayerHitBuffer.loadFromFile("path_to_player_hit.wav"))
	{
		// Handle error loading player hit sound
	}

	if (!MEnemyHitBuffer.loadFromFile("path_to_enemy_hit.wav"))
	{
		// Handle error loading enemy hit sound
	}

	if (!MDeathBuffer.loadFromFile("path_to_death.wav"))
	{
		// Handle error loading death sound
	}

	// Set sound buffers for each sound
	MShootSound.setBuffer(MShootBuffer);
	MPlayerHitSound.setBuffer(MPlayerHitBuffer);
	MEnemyHitSound.setBuffer(MEnemyHitBuffer);
	MDeathSound.setBuffer(MDeathBuffer);

	if (!MMenuMusic.openFromFile("Resources/Audio/Menu.wav"))
	{
		// Handle error loading music
	}

	if (!MBattleMusic.openFromFile("Resources/Audio/Battle.wav"))
	{
		// Handle error loading music
	}

	// Set initial volume levels
	MShootSound.setVolume(static_cast<float>(Config.getSoundVolume()));
	MPlayerHitSound.setVolume(static_cast<float>(Config.getSoundVolume()));
	MEnemyHitSound.setVolume(static_cast<float>(Config.getSoundVolume()));
	MDeathSound.setVolume(static_cast<float>(Config.getSoundVolume()));
	MMenuMusic.setVolume(static_cast<float>(Config.getMusicVolume()));
	MBattleMusic.setVolume(static_cast<float>(Config.getMusicVolume()));

	updateVolume();
}

void Audio::updateVolume()
{
	// Adjust sound and music volume based on the current settings
	MShootSound.setVolume(static_cast<float>(MConfig.getSoundVolume()));
	MPlayerHitSound.setVolume(static_cast<float>(MConfig.getSoundVolume()));
	MEnemyHitSound.setVolume(static_cast<float>(MConfig.getSoundVolume()));
	MDeathSound.setVolume(static_cast<float>(MConfig.getSoundVolume()));
	MMenuMusic.setVolume(static_cast<float>(MConfig.getMusicVolume()));
	MBattleMusic.setVolume(static_cast<float>(MConfig.getMusicVolume()));
}

void Audio::playShootSound()
{
	MShootSound.play();
}

void Audio::playPlayerHitSound()
{
	MPlayerHitSound.play();
}

void Audio::playEnemyHitSound()
{
	MEnemyHitSound.play();
}

void Audio::playDeathSound()
{
	MDeathSound.play();
}

void Audio::playMenuMusic()
{
	MBattleMusic.stop();
	MMenuMusic.setLoop(true);
	MMenuMusic.play();
}

void Audio::playGameMusic()
{
	MMenuMusic.stop();
	MBattleMusic.setLoop(true);
	MBattleMusic.play();
}
