#pragma once

#include <vector>
#include <SDL.h>
#include "State.h"

/**
@brief Handles the functions for all State objects.
*/
class StateManager
{
public:
	/**
	@brief Constructs the StateManager object.
	*/
	StateManager();

	/**
	@brief Destructs the StateManager object.
	*/
	~StateManager();

	/**
	@brief Adds a new state to the current stack of states.
	@param state A pointer to the State in use.
	*/
	void addState(State* state);

	/**
	@brief Changes the current State to a new State.
	@param state A pointer to the State in use.
	*/
	void changeState(State* state);

	/**
	@brief Removes the last State from the vector.
	*/
	void removeLastState();

	/**
	@brief Handles the user input for the current State on the top of the stack.
	@returns If false then quit the application.
	*/
	bool input();

	/**
	@brief Updates the current State on the top of the stack.
	@param dt The delta time for use within the update function.
	*/
	void update(float dt);

	/**
	@brief Draws the current States.
	*/
	void draw();

private:
	///The current states that are in use.
	std::vector<State*> currentStates;
};