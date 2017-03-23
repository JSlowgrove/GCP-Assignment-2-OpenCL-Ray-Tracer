#include "Music.h"

Music::Music(std::string file)
{
	//Load music from file
	music = Mix_LoadMUS(file.c_str());
	if (music == NULL)
	{
		//Failed loading file
		Utilities::logE("Failed to load " + file + ", Error is: " + std::string(Mix_GetError()));
	}
}

Music::~Music()
{
	//Free the audio
	Mix_FreeMusic(music);
}

void Music::startMusic()
{
	//If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
	}
}

void Music::stopMusic()
{
	//Stops the music
	Mix_HaltMusic();
}

void Music::muteMusic()
{
	//Mutes the music
	Mix_VolumeMusic(0);
}

void Music::unmuteMusic()
{
	//Unmutes the music
	Mix_VolumeMusic(MIX_MAX_VOLUME);
}