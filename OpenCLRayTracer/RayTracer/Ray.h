#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>

class Ray
{
public:
	Ray();
	~Ray();

	void setOrigin(glm::vec3 inOrigin) { origin = inOrigin; };
	void setDirection(glm::vec3 inDirection) { direction = inDirection; };
	glm::vec3 getOrigin() { return origin; };
	glm::vec3 getDirection() { return direction; };

private:
	glm::vec3 origin;
	glm::vec3 direction;
};