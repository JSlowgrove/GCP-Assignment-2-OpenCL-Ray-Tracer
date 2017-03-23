#include "PerformanceTest.h"

PerformanceTest::PerformanceTest()
{
}

PerformanceTest::~PerformanceTest()
{
}

void PerformanceTest::testStart()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startingTime);
}

uint64_t PerformanceTest::testFinish()
{
	LARGE_INTEGER endingTime, elapsedMicroseconds;

	QueryPerformanceCounter(&endingTime);
	elapsedMicroseconds.QuadPart = endingTime.QuadPart - startingTime.QuadPart;


	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	elapsedMicroseconds.QuadPart *= 1000000;
	elapsedMicroseconds.QuadPart /= frequency.QuadPart;

	Utilities::logI(std::to_string(elapsedMicroseconds.QuadPart));

	return elapsedMicroseconds.QuadPart;
}