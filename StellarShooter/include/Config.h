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

	[[nodiscard]] int getSoundVolume() const; // Add this function
	[[nodiscard]] int getMusicVolume() const; // Add this function

	void adjustVolume(int& Volume, int Step);

	void incrementSoundVolume(); // Add this function
	void decrementSoundVolume(); // Add this function
	void incrementMusicVolume();
	void decrementMusicVolume();

	// Add other necessary functions and variables here

private:
	bool MVSyncEnabled;
	unsigned int MFrameRate;

	int MSoundVolume; // Add this member variable
	int MMusicVolume; // Add this member variable
	int MIncrement;
	int MDecrement;

	std::string MType;
	std::chrono::high_resolution_clock::time_point MLastVolumeChangeTime = std::chrono::high_resolution_clock::now();

};
