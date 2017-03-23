#pragma once

/**
@brief Handles timer functions.
*/
class Timer
{
public:
	/**
	@brief Constructs the timer object.
	@param float the length of the timer.
	*/
	Timer(float timerLength);

	/**
	@brief Destructs the timer object.
	*/
	~Timer();

	/**
	@brief Updates the timer using the delta time.
	@param dt The delta time.
	*/
	void upadateTimer(float dt);

	/**
	@brief Resets the timer to 0.
	*/
	void resetTimer();

	/**
	@brief Changes the timer length.
	*/
	void setTimerLength(float timerLength);


	/**
	@brief Change the timer length and reset the timer.
	*/
	void resetTimerLength(float timerLength);

	/**
	@brief Returns if the timer has finished or not.
	@returns If the timer has finished.
	*/
	bool checkTimer();

private:
	///The current time in the timer.
	float timer;
	///The length of the timer.
	float timerLength;
	///A boolean for if the timer has finished
	bool finished;
};