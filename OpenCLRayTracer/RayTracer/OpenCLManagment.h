#pragma once

#include <string>
#include <vector>
#include <sstream> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "clew.h"

#define MEM_SIZE (128)
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

	int runOpenCL();
}