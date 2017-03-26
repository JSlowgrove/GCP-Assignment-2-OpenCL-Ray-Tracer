#include "MainState.h"

#include <vector>
#include <math.h>
#include <cstdint>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

MainState::MainState(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions)
	: State(stateManager, renderer, dimensions)
{
	//initalise the loading text
	loadingWithOpenCL = new Texture("Assets/img/loadingOpenCL.png", renderer);
	loadingWithoutOpenCL = new Texture("Assets/img/loading.png", renderer);

	//Initialise universal speed
	universalSpeed = new float(0.0f);
	
	//intialise cube
	initaliseTenCubes();

	//Initalise trace window
	traceDim = glm::vec2(699, 409);
	tracePos = glm::vec2(12, 157);

	//Initalise the text
	timeText = new Text("Time Taken: ", "Assets/font/isl_jupiter.ttf", 60, renderer, 255, 255, 255);
	helpText = new Text("Press H for help", "Assets/font/isl_jupiter.ttf", 40, renderer, 0, 255, 0);
	performanceText = new Text("0 ms", "Assets/font/isl_jupiter.ttf", 60, renderer, 255, 255, 255);

	//Initalise the background
	background = new Texture("Assets/img/background.png", renderer);

	traced = false;

	//initialise the performance tester
	tester = new PerformanceTest();
}

MainState::~MainState()
{
	//delete pointers
	delete universalSpeed;
	delete rayTrace;
	delete background;
	delete loadingWithOpenCL;
	delete loadingWithoutOpenCL;
	delete timeText;
	delete helpText;
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
				drawLoadingWithoutOpenCL();
				tester->testStart();
				runRayTrace(false);
				performanceText->setText(getTimeToDraw(tester->testFinish() * 0.001f) + "ms");
				break;

			case SDLK_RETURN:
				//CPU Render
				drawLoadingWithOpenCL();
				tester->testStart();
				runRayTrace(true);
				performanceText->setText(getTimeToDraw(tester->testFinish() * 0.001f) + "ms");
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
	helpText->pushToScreen(glm::vec2(240.0f, 0.0f));
	timeText->pushToScreen(glm::vec2(10.0f, 50.0f));
	performanceText->pushToScreen(glm::vec2(300.0f, 50.0f));
}

void MainState::runRayTrace(bool useOpenCL)
{
	//make sure the texture is not a null pointer
	if (rayTrace != NULL)
	{
		delete rayTrace;
	}

	//set the projection matrix for the ray tracer
	glm::mat4 proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.0f, 100.0f);

	//generate the ray directions
	glm::vec4 rayDirection = glm::vec4(proj * glm::vec4(0, 0, 1, 1));

	//ray trace
	std::vector<unsigned char> trace = RayTracer::rayTraceBoxes(boxes, traceDim, rayDirection, useOpenCL);
	Utilities::logI("Box Ray Trace Ran");

	//ray trace output path
	std::string outputPath = "RayTraceOutput/RayTraceOutput[" + Utilities::getCurrentDateAndTime() + ".png";

	//generate a png with a ray trace
	Utilities::generatePNG(outputPath.c_str(), trace, traceDim.x, traceDim.y);

	//display the generated ray trace image
	rayTrace = new Texture(outputPath, renderer);

	traced = true;
}

void MainState::drawLoadingWithOpenCL()
{
	loadingWithOpenCL->pushToScreen(renderer, tracePos);

	//display renderer
	SDL_RenderPresent(renderer);
}

void MainState::drawLoadingWithoutOpenCL()
{
	loadingWithoutOpenCL->pushToScreen(renderer, tracePos);

	//display renderer
	SDL_RenderPresent(renderer);
}

std::string MainState::getTimeToDraw(float time)
{
	std::stringstream stream;
	stream.precision(3);
	stream << std::fixed << time;
	return stream.str();
}

void MainState::initaliseOneCube()
{
	boxes.push_back(Box(50.0f, glm::vec3(150.0f, 50.0f, -200.0f), 45.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(0.0f, 0.0f, 255.0f));
}

void MainState::initaliseFiveCubes()
{
	initaliseOneCube();
	boxes.push_back(Box(50.0f, glm::vec3(250.0f, 50.0f, -200.0f), 45.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(0.0f, 255.0f, 0.0f));
	boxes.push_back(Box(25.0f, glm::vec3(100.0f, 50.0f, -200.0f), 135.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(255.0f, 0.0f, 0.0f));
	boxes.push_back(Box(35.0f, glm::vec3(100.0f, 0.0f, -200.0f), 20.0f, glm::vec3(1, 1, 1)));
	boxes.back().setColour(glm::vec3(0.0f, 255.0f, 255.0f));
	boxes.push_back(Box(15.0f, glm::vec3(0.0f, 200.0f, -300.0f), 225.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(255.0f, 0.0f, 255.0f));
}

void MainState::initaliseTenCubes()
{
	initaliseFiveCubes();
	boxes.push_back(Box(30.0f, glm::vec3(250.0f, 25.0f, -200.0f), 17.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(255.0f, 255.0f, 0.0f));
	boxes.push_back(Box(50.0f, glm::vec3(300.0f, 50.0f, -200.0f), 5.0f, glm::vec3(1, 1, 0)));
	boxes.push_back(Box(50.0f, glm::vec3(250.0f, 200.0f, -250.0f), 320.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(0.0f, 0.0f, 255));
	boxes.push_back(Box(25.0f, glm::vec3(60.0f, 50.0f, -100.0f), 30.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(150.0f, 200.0f, 200.0f));
	boxes.push_back(Box(35.0f, glm::vec3(100.0f, 190.0f, -100.0f), 340.0f, glm::vec3(1, 1, 0)));
	boxes.back().setColour(glm::vec3(90.0f, 255.0f, 90.0f));
}
