#include "MainState.h"

#include <vector>
#include <math.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

MainState::MainState(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions)
	: State(stateManager, renderer, dimensions)
{
	//initalise the loading text
	loading = new Text("Running...", "Assets/font/isl_jupiter.ttf", 200, renderer, 255, 255, 255);

	//Initialise universal speed
	universalSpeed = new float(0.0f);
	
	//intialise cube
	boxes.push_back(Box(50.0f, glm::vec3(150.0f, 50.0f, -200.0f), 45.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(0.0f, 0.0f, 255.0f));
	boxes.push_back(Box(50.0f, glm::vec3(250.0f, 50.0f, -200.0f), 45.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(0.0f, 255.0f, 0.0f));

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
				//OpenCL Render
				//runRayTrace();
				break;

			case SDLK_RETURN:
				//CPU Render
				drawLoading();
				runRayTrace();
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

void MainState::runRayTrace()
{
	//make sure the texture is not a null pointer
	if (rayTrace != NULL)
	{
		delete rayTrace;
	}

	//set the projection matrix for the ray tracer
	glm::mat4 proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.0f, 100.0f);

	//generate the ray directions
	glm::vec3 rayDirection = glm::vec3(proj * glm::vec4(0, 0, 1, 1));

	//ray trace
	std::vector<unsigned char> trace = RayTracer::rayTraceBoxes(boxes, traceDim, rayDirection);
	Utilities::logI("Box Ray Trace Ran");

	//ray trace output path
	std::string outputPath = "RayTraceOutput/RayTraceOutput[" + Utilities::getCurrentDateAndTime() + ".png";

	//generate a png with a ray trace
	Utilities::generatePNG(outputPath.c_str(), trace, traceDim.x, traceDim.y);

	//display the generated ray trace image
	rayTrace = new Texture(outputPath, renderer);

	traced = true;
}

void MainState::drawLoading()
{
	loading->pushToScreen(glm::vec2(65.0f, 240.0f));

	//display renderer
	SDL_RenderPresent(renderer);
}
