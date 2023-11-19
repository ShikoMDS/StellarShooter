#pragma once

#include <chrono>
#include <SFML/Graphics.hpp>

class Config
{
public:
	Config();

	bool loadFromFile(const std::string& FilePath);
	bool saveToFile(const std::string& FilePath);

	void applySettings(sf::RenderWindow& Window) const;

	[[nodiscard]] int getSoundVolume() const;
	[[nodiscard]] int getMusicVolume() const;

	void adjustVolume(int& Volume, int Step);

	void incrementSoundVolume();
	void decrementSoundVolume();
	void incrementMusicVolume();
	void decrementMusicVolume();

private:
	bool MVSyncEnabled;
	unsigned int MFrameRate;

	int MSoundVolume;
	int MMusicVolume;
	int MIncrement;
	int MDecrement;

	std::string MType;
	std::chrono::high_resolution_clock::time_point MLastVolumeChangeTime = std::chrono::high_resolution_clock::now();
};
