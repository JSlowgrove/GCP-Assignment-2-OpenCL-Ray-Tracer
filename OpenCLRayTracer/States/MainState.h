#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include "State.h"
#include "StateManager.h"
#include "../Core/Texture.h"
#include "../Core/Audio.h"
#include "../Core/Music.h"
#include "../Core/Text.h"
#include "../RayTracer/Ray.h"
#include "../RayTracer/RayTracer.h"
#include "../Core/PerformanceTest.h"

/**
@brief A State that contains and runs the Main State.
*/
class MainState : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param dimensions The screen dimensions.
	*/
	MainState(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions);

	/**
	@brief Destructs the State object.
	*/
	~MainState();

	/**
	@brief Handles the State input.
	@returns If false then quit the State.
	*/
	bool input();

	/**
	@brief A function to update the State.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief A function to draw the State to the screen.
	*/
	void draw();

private:
	///A pointer for the universal speed of the menu.
	float* universalSpeed;

	//The Boxes
	std::vector<Box> boxes;

	//The texture to display
	Texture* rayTrace;
	//The background texture
	Texture* background;
	//The loading screens;
	Texture* loadingWithoutOpenCL;
	Texture* loadingWithOpenCL;
	//The help image
	Texture* helpImage;

	///The performance tester
	PerformanceTest* tester;

	//The text
	Text* timeText;
	Text* helpText;
	Text* performanceText;
	Text* numberOfCubesInSceneText;
	Text* numberOfCubesInScene;

	//The dimensions of the ray trace screen
	glm::vec2 traceDim;
	//The position of the ray trace screen
	glm::vec2 tracePos;

	//A boolean for if the ray trace is done
	bool traced;

	bool help;

	int sceneNumber;

	void runRayTrace(bool useOpenCL);

	void drawLoadingWithOpenCL();

	void drawLoadingWithoutOpenCL();

	std::string getTimeToDraw(float time);

	void initaliseOneCube();
	void initaliseFiveCubes();
	void initaliseTenCubes();
};