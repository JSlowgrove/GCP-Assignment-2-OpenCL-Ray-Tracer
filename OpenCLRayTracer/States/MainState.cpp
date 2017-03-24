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

	//Initalise triangle
	triangle.setPointA(glm::vec3(150, 0, 0));
	triangle.setPointB(glm::vec3(0, 300, 0));
	triangle.setPointC(glm::vec3(300, 300, 0));

	//Initalise sphere
	sphere.setCenter(glm::vec3(dimensions.x * 0.5f, dimensions.y * 0.0f, 0));
	sphere.setRadius(250.0f);

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
	//std::vector<unsigned char> trace = RayTracer::rayTraceTriangle(triangle, traceDim, colour);
	std::vector<unsigned char> trace = RayTracer::rayTraceSphere(sphere, traceDim, colour);

	//generate a png with a ray trace
	Utilities::generatePNG("RayTraceOutput.png", trace, traceDim.x, traceDim.y);

	//display the generated ray trace image
	rayTrace = new Texture("RayTraceOutput.png", renderer);

	traced = true;
}