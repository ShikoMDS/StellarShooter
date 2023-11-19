#pragma once

#include <SFML/Audio.hpp>
#include "Config.h"

class Audio
{
public:
	explicit Audio(const Config& Config);

	void updateVolume();

	void playShootSound(); // Function for player shoot sound
	void playPlayerHitSound(); // Function for player hit sound
	void playEnemyHitSound(); // Function for enemy hit sound
	void playDeathSound(); // Function for death sound
	void playMenuMusic();
	void playGameMusic();

private:
	sf::SoundBuffer MShootBuffer;
	sf::SoundBuffer MPlayerHitBuffer;
	sf::SoundBuffer MEnemyHitBuffer;
	sf::SoundBuffer MDeathBuffer;

	sf::Sound MShootSound;
	sf::Sound MPlayerHitSound;
	sf::Sound MEnemyHitSound;
	sf::Sound MDeathSound;

	sf::Music MMenuMusic;
	sf::Music MBattleMusic;

	const Config& MConfig;
};
