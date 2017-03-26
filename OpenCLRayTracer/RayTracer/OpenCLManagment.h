#pragma once

#include <string>
#include <vector>
#include <sstream> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "clew.h"
#include "glm/glm.hpp"

#define MAX_SOURCE_SIZE (0x100000)

/**
@brief A namespace that contains functions to use OpenCL.
*/
namespace OpenCLManagment
{

	/**
	@brief Load the contents of a text file in to a std::string.
	@param fileName The file name.
	@return The contents of the file in a single std::string.
	*/
	std::string loadOpenCLFile(std::string fileName);

	std::vector<int> runOpenCLRayTrace(unsigned int numberOfBoxes, glm::vec4 rayDirection,
		std::vector<glm::vec4> vertices, std::vector<glm::vec4> colours, std::vector<glm::vec4> rayOrigins, int verticiesSize,
		int coloursSize, int originsSize, int numberOfRays);

	//int runOpenCLHelloWorld();
}