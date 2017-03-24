#pragma once

#include <string>
#include <SDL.h>
#include <glm/glm.hpp>
#include <vector>

///A definition of PI.
#define PI 3.141596f

/**
@brief Contains utility functions for use within the code.
*/
namespace Utilities
{
	/**
	@brief Gets the value for PI.
	@returns The value for PI.
	*/
	float getPI();

	/**
	@brief Converts the degree to a radian.
	@param angle The angle to convert.
	@returns The converted radian.
	*/
	float convertDegreeToRadian(float angle);

	/**
	@brief Converts the radian to a degree.
	@param angle The angle to convert.
	@returns The converted degree.
	*/
	float convertRadianToDegree(float angle);

	/**
	@brief Logs the information message.
	@param message The message.
	*/
	void logI(std::string message);

	/**
	@brief Logs the error message.
	@param message The message.
	*/
	void logE(std::string message);

	/**
	@brief Checks to see if two rectangles intersect
	@param PosBoxA The position of the first rectangle.
	@param DimBoxA The dimensions of the first rectangle.
	@param PosBoxB The position of the second rectangle.
	@param DimBoxB The dimensions of the second rectangle.
	@returns True if the rectangles intersect
	*/
	bool rectRectIntersect(glm::vec2 PosBoxA, glm::vec2 DimBoxA, glm::vec2 PosBoxB, glm::vec2 DimBoxB);

	void generatePNG(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

	float normaliseFloat(float numToNorm, float minNum, float maxNum);
}