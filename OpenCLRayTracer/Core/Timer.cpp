#include "Timer.h"

Timer::Timer(float timerLength) : timerLength(timerLength)
{
	resetTimer();
}

Timer::~Timer()
{	
}

void Timer::upadateTimer(float deltaTime)
{
	//Update the timer
	timer += deltaTime;
	//If the timer has finished then set the timer to finished
	if (timer >= timerLength)
	{
		finished = true;
	}
}

void Timer::resetTimer()
{
	//Set the current time to 0
	timer = 0.0f;
	//Set the timer to not be finished
	finished = false;
}

void Timer::resetTimerLength(float timerLength)
{
	//set the timer length
	this->timerLength = timerLength;

	//reset the timer
	resetTimer();
}

void Timer::setTimerLength(float timerLength)
{
	//set the timer length
	this->timerLength = timerLength;
}

bool Timer::checkTimer()
{
	return finished;
}