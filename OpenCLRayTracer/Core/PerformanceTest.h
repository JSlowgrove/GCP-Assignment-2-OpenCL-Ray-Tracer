#pragma once
#include <windows.h>
#include <cstdint>
#include "Utilities.h"

/**
@brief Contains details and functions for use with testing performance.
*/
class PerformanceTest
{
public:
	/**
	@brief Constructs PerformanceTest.
	*/
	PerformanceTest();

	/**
	@brief Destructs PerformanceTest.
	*/
	~PerformanceTest();

	/**
	@brief A function to start the performance test. 
	This is to be called when the test is to be started.
	*/
	void testStart();

	/**
	@brief A function to get the results of the performance test.
	This returns the time taken in seconds.
	@returns The time taken in seconds.
	*/
	uint64_t testFinish();

private:
	///The elapsed number of ticks
	LARGE_INTEGER startingTime;
	///The number of ticks-per-second
	LARGE_INTEGER frequency;
};