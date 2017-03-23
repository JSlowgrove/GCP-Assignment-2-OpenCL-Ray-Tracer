#include "MainState.h"

#include <vector>
#include <math.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

MainState::MainState(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions)
	: State(stateManager, renderer, dimensions)/*,
	//backgroundMusic(new C_Music("Assets/Audio/[INSERTNAME].ogg"))*/
{
	//Initialise universal speed
	universalSpeed = new float(0.0f);

	//Initalise triangle
	triangle.setPointA(glm::vec3(150, 0, 0));
	triangle.setPointB(glm::vec3(0, 300, 0));
	triangle.setPointC(glm::vec3(300, 300, 0));

	//The colour to make the triangle
	glm::vec3 colour = glm::vec3(0.0f, 255.0f, 255.0f);

	//generate a png with a ray trace triangle
	Utilities::generatePNG("RayTraceOutput.png", 
		RayTracer::rayTraceTriangle(triangle, dimensions, colour), 
		dimensions.x, dimensions.y);
}

MainState::~MainState()
{
	//Stop music
	//backgroundMusic->stopMusic();
	//Delete audio pointers
	//delete backgroundMusic;
	//delete pointers
	delete universalSpeed;
}

bool MainState::input()
{
	//Check for user input
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT: //If player closes the window, end the game loop

			return false;
			break;

		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE: //If Escape is pressed, end the game loop

				return false;
				break;
			}
		}
	}
	return true;
}

void MainState::update(float dt)
{
	//Keep the music playing
	//backgroundMusic->startMusic();
}

void MainState::draw()
{
}