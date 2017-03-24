#include "Utilities.h"

#include "../ExternalLibraries/lodepng.h"

namespace Utilities
{
	float getPI()
	{
		return PI;
	}

	float convertDegreeToRadian(float angle)
	{
		return (angle * PI / 180.0f);
	}

	float convertRadianToDegree(float angle)
	{
		return (angle * 180.0f / PI);
	}

	void logI(std::string message)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, message.c_str());
	}

	void logE(std::string message)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, message.c_str());
	}

	bool rectRectIntersect(glm::vec2 PosBoxA, glm::vec2 DimBoxA, glm::vec2 PosBoxB, glm::vec2 DimBoxB)
	{
		if (PosBoxA.x <= (PosBoxB.x + DimBoxB.x)
			&& PosBoxA.y <= (PosBoxB.y + DimBoxB.y)
			&& PosBoxB.x <= (PosBoxA.x + DimBoxA.x)
			&& PosBoxB.y <= (PosBoxA.y + DimBoxA.y))
		{
			return true;
		}
		return false;
	}

	void generatePNG(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
	{
		//Encode the image
		unsigned error = lodepng::encode(filename, image, width, height);

		//if there's an error, log it
		if (error)
		{
			logE("encoder error " + std::to_string(error) + ": " + lodepng_error_text(error));
		}
	}

	float normaliseFloat(float numToNorm, float minNum, float maxNum)
	{
		float normalisedNum;

		normalisedNum = (numToNorm - minNum) / (maxNum - minNum);

		return normalisedNum;
	}

}