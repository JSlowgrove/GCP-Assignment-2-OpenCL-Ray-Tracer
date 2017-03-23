#pragma once

#include <SDL.h>
#include <string.h>
#include <glm/glm.hpp>

///Forward declaration of StateManager for the pointer to the StateManager.
class StateManager;

/**
@brief Contains State functions and data to be inherited by all other states.
*/
class State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param dimensions The screen dimensions.
	*/
	State(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions);

	/**
	@brief A virtual destructor for the State object.
	*/
	virtual ~State();

	/**
	@brief A pure virtual function to handle the user input for use with the State.
	@returns If false then quit State.
	*/
	virtual bool input() = 0;

	/**
	@brief A pure virtual function to update the State to allow the State to run.
	@param dt The delta time.
	*/
	virtual void update(float deltaTime) = 0;

	/**
	@brief A pure virtual function to draw to the screen using the renderer.
	*/
	virtual void draw() = 0;

protected:
	///A pointer to the state manager.
	StateManager* stateManager;
	///A pointer to the renderer.
	SDL_Renderer* renderer;
	///The screen dimensions.
	glm::vec2 dimensions;
};