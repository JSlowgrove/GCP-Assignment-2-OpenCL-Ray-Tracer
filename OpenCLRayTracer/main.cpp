#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Core/Utilities.h"
#include "States/StateManager.h"
#include "States/Splash.h"
#include "States/MainState.h"

//The declaration of the main function
int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	//Copy all arguments into a string (the first argument is the executable)
	std::vector<std::string> allArgs(argv, argv + argc);

	//Log the passed in commamds
	Utilities::logI("Number of commands passed in: " + std::to_string(argc));
	Utilities::logI("Passed in commands:");
	for (unsigned int i = 0; i < allArgs.size(); i++)
	{
		Utilities::logI(allArgs[i]);
	}

	//Set the window title
	std::string title = "OpenCL Ray Tracer";

	//Set the window and target resolutions
	glm::vec2 targetRes = glm::vec2(720, 576);
	glm::vec2 windowRes = glm::vec2(720, 576);

	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Failed initialisation
		Utilities::logE("SDL failed to initialise: " + std::string(SDL_GetError()));
		return -1;
	}

	//Initialise SDL_ttf
	if (TTF_Init() < 0)
	{
		//Failed initialisation
		Utilities::logE("SDL_ttf failed to initialise: " + std::string(TTF_GetError()));
		return -1;
	}

	//Initialise SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		Utilities::logE("SDL_mixer failed to initialise: " + std::string(Mix_GetError()));
		return -1;
	}

	//Time Check
	unsigned int lastTime = SDL_GetTicks();

	//Create Window
	glm::vec2 windowPos = glm::vec2(40, 40);
	SDL_Window *window = SDL_CreateWindow(title.c_str(),
		(int)windowPos.x, (int)windowPos.y,
		(int)windowRes.x, (int)windowRes.y,
		SDL_WINDOW_SHOWN);

	//Create Renderer from the window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//Set the renderer to work out the render at this resolution and then scale it up the 
	//closest resolution it can to the windows resolution (adds bars of the render colour)
	SDL_RenderSetLogicalSize(renderer, (int)targetRes.x, (int)targetRes.y);
	
	//Setup state manager and initial state
	StateManager * stateManager = new StateManager();
	stateManager->addState(new MainState(stateManager, renderer, targetRes));

	//Start Game Loop
	bool go = true;
	while (go)
	{
		//Time Check
		unsigned int current = SDL_GetTicks();
		float deltaTime = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		//Handle the current state inputs
		go = stateManager->input();

		//Update the current state
		stateManager->update(deltaTime);

		//set draw colour to black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

		//Clear the entire screen to the set colour
		SDL_RenderClear(renderer);

		//Draw the states
		stateManager->draw();

		//display renderer
		SDL_RenderPresent(renderer);

		//Time Limiter
		if (deltaTime < (1.0f / 50.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTime)*1000.0f));
		}
	}
	//destroy data
	delete stateManager;
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}