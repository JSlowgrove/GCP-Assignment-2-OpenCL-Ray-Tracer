#include "MainState.h"

#include <vector>
#include <math.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

MainState::MainState(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions)
	: State(stateManager, renderer, dimensions)
{
	//Initialise universal speed
	universalSpeed = new float(0.0f);
	
	//intialise cube
	box = Box(50.0f, glm::vec3(150.0f, 50.0f, -150.0f), 45.0f, glm::vec3(1, 1, 0));

	//Initalise trace window
	traceDim = glm::vec2(699, 409);
	tracePos = glm::vec2(12, 157);

	//Initalise the background
	background = new Texture("Assets/img/background.png", renderer);

	traced = false;
}

MainState::~MainState()
{
	//delete pointers
	delete universalSpeed;
	delete rayTrace;
	delete background;
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

			case SDLK_SPACE:
				runRayTrace(glm::vec3(0.0f, 0.0f, 255.0f));
				break;

			case SDLK_RETURN:
				runRayTrace(glm::vec3(0.0f, 255.0f, 0.0f));
				break;
			}
		}
	}
	return true;
}

void MainState::update(float dt)
{
}

void MainState::draw()
{
	if (traced)
	{
		rayTrace->pushToScreen(renderer, tracePos);
	}
	background->pushToScreen(renderer, glm::vec2(0,0));
}

void MainState::runRayTrace(glm::vec3 colour)
{
	//make sure the texture is not a null pointer
	if (rayTrace != NULL)
	{
		delete rayTrace;
	}

	//ray trace
	std::vector<unsigned char> trace = RayTracer::rayTraceBox(box, traceDim, colour);

	//ray trace output path
	std::string outputPath = "RayTraceOutput/RayTraceOutput[" + Utilities::getCurrentDateAndTime() + ".png";

	//generate a png with a ray trace
	Utilities::generatePNG(outputPath.c_str(), trace, traceDim.x, traceDim.y);

	//display the generated ray trace image
	rayTrace = new Texture(outputPath, renderer);

	traced = true;
}