#pragma once

#include <SDL.h>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "../Core/Timer.h"
#include "../Core/Texture.h"
#include "../Core/Audio.h"
#include "MainState.h"

/**
@brief A State that contains and runs the splash screen.
*/
class Splash : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param dimensions The screen dimensions.
	*/
	Splash(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions);

	/**
	@brief Destructs the State object.
	*/
	~Splash();

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
	///The splash image
	Texture* splash;
	///The timer keeping the splash screen open
	Timer* splashTimer;
};