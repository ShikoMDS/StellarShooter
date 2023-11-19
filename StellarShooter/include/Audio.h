#pragma once

#include "Config.h"

#include <SFML/Audio.hpp>

class Audio
{
public:
	explicit Audio(const Config& Config);

	void updateVolume();

	void playShootSound(); 
	void playPlayerHitSound(); 
	void playEnemyHitSound(); 
	void playDeathSound(); 
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
