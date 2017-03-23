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

void Timer::resetTimerLength(float inTimerLength)
{
	//set the timer length
	timerLength = inTimerLength;

	//reset the timer
	resetTimer();
}

void Timer::setTimerLength(float inTimerLength)
{
	//set the timer length
	timerLength = inTimerLength;
}

bool Timer::checkTimer()
{
	return finished;
}