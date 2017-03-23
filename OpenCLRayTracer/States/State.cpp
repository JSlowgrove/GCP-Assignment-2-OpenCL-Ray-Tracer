#include "State.h"

State::State(StateManager * stateManager, SDL_Renderer* renderer, glm::vec2 dimensions)
	: stateManager(stateManager), renderer(renderer), dimensions(dimensions)
{
}

State::~State()
{
}