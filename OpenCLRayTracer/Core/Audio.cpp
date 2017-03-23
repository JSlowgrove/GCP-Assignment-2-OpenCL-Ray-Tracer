#include "Audio.h"

Audio::Audio(std::string file)
{
	//Load sound from file
	audio = Mix_LoadWAV(file.c_str());
	if (audio == NULL)
	{
		//Failed loading file
		Utilities::logE("Failed to load " + file + ", Error is: " + std::string(Mix_GetError()));
	}
}

Audio::~Audio()
{
	//Free the sound effect
	Mix_FreeChunk(audio);
	audio = NULL;
	//Delete the pointers
	delete audio;
}

void Audio::playEffect()
{
	//Play the sound
	Mix_PlayChannel(-1, audio, 0);
}