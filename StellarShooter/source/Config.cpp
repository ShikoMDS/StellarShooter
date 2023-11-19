#include "Config.h"

#include <iostream>
#include <fstream>
#include <sstream>

Config::Config() : MVSyncEnabled(true), MFrameRate(60), MSoundVolume(80), MMusicVolume(50), MIncrement(1),
                   MDecrement(-1)
{
	// Set default values
}

bool Config::loadFromFile(const std::string& FilePath)
{
	std::ifstream ConfigFile(FilePath);

	if (!ConfigFile.is_open())
	{
		std::cerr << "Failed to open config file: " << FilePath << std::endl;
		return false;
	}

	std::string Line;
	std::string CurrentSection; // To keep track of the current section
	while (std::getline(ConfigFile, Line))
	{
		// Check for section header
		if (Line.size() > 2 && Line.front() == '[' && Line.back() == ']')
		{
			CurrentSection = Line.substr(1, Line.size() - 2);
			continue; // Skip to the next line
		}

		std::istringstream Iss(Line);
		std::string Key, Value;

		if (std::getline(Iss, Key, '=') && std::getline(Iss, Value))
		{
			if (CurrentSection == "Graphics")
			{
				if (Key == "VSyncEnabled")
				{
					MVSyncEnabled = (Value == "true");
				}
				else if (Key == "FrameRate")
				{
					MFrameRate = std::stoi(Value);
				}
			}
			else if (CurrentSection == "Audio")
			{
				if (Key == "SoundVolume")
				{
					MSoundVolume = std::stoi(Value); // Parse and set sound volume
				}
				else if (Key == "MusicVolume")
				{
					MMusicVolume = std::stoi(Value); // Parse and set music volume
				}
			}
		}
	}

	ConfigFile.close();
	return true;
}

bool Config::saveToFile(const std::string& FilePath) 
{
	std::ofstream ConfigFile(FilePath);

	if (!ConfigFile.is_open())
	{
		std::cerr << "Failed to open config file for writing: " << FilePath << std::endl;
		return false;
	}

	ConfigFile << "[Graphics]" << std::endl;
	ConfigFile << "VSyncEnabled=" << (MVSyncEnabled ? "true" : "false") << std::endl;
	ConfigFile << "FrameRate=" << MFrameRate << std::endl;

	ConfigFile << std::endl; // Add a newline between sections

	ConfigFile << "[Audio]" << std::endl;
	ConfigFile << "SoundVolume=" << MSoundVolume << std::endl;
	ConfigFile << "MusicVolume=" << MMusicVolume << std::endl;

	ConfigFile.close();

	return true;
}

void Config::applySettings(sf::RenderWindow& Window) const
{
	// Apply VSync setting
	Window.setVerticalSyncEnabled(MVSyncEnabled);

	// Apply frame rate setting
	Window.setFramerateLimit(MFrameRate);
}

int Config::getSoundVolume() const
{
	// Implement the logic to return the sound volume
	return MSoundVolume; // Assuming SoundVolume is a member variable in Config
}

int Config::getMusicVolume() const
{
	// Implement the logic to return the music volume
	return MMusicVolume; // Assuming MusicVolume is a member variable in Config
}

void Config::adjustVolume(int& Volume, const int Step)
{
	constexpr int MaxVolume = 100;
	constexpr int VolumeChangeDelay = 200; // Adjust the delay in milliseconds

	const auto CurrentTime = std::chrono::high_resolution_clock::now();
	const auto ElapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		CurrentTime - MLastVolumeChangeTime).count();

	if (ElapsedMilliseconds > VolumeChangeDelay)
	{
		const int PreviousVolume = Volume;
		if (Step > 0)
		{
			Volume = std::min(MaxVolume, Volume + Step);
		}
		else
		{
			Volume = std::max(0, Volume + Step);
		}

		std::cout << MType << " volume adjusted from " << PreviousVolume << " to " << Volume << std::endl;
		MLastVolumeChangeTime = CurrentTime;
	}
}

void Config::incrementSoundVolume()
{
	MType = "Sound";
	adjustVolume(MSoundVolume, MIncrement);
}

void Config::decrementSoundVolume()
{
	MType = "Sound";
	adjustVolume(MSoundVolume, MDecrement);
}

void Config::incrementMusicVolume()
{
	MType = "Music";
	adjustVolume(MMusicVolume, MIncrement);
}

void Config::decrementMusicVolume()
{
	MType = "Music";
	adjustVolume(MMusicVolume, MDecrement);
}
