#include "Splash.h"

Splash::Splash(StateManager* stateManager, SDL_Renderer* renderer, glm::vec2 dimensions)
	: State(stateManager, renderer, dimensions),
	splash(new Texture("Assets/img/splash.png", renderer)),
	splashTimer(new Timer(5.0f))
{
	//Initialise universal speed
	universalSpeed = new float(0.0f);
}

Splash::~Splash()
{
	//Delete pointers
	delete universalSpeed;
	delete splash;
}

bool Splash::input()
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
		}
	}
	return true;
}

void Splash::update(float dt)
{
	//Update the timer
	splashTimer->upadateTimer(dt);

	//exit the splash screen if the timer is up
	if (splashTimer->checkTimer())
	{
		stateManager->changeState(new MainState(stateManager, renderer, dimensions));
		return;
	}
}

void Splash::draw()
{
	//draw the image
	splash->pushToScreen(renderer, glm::vec2(0.0f,0.0f));
}