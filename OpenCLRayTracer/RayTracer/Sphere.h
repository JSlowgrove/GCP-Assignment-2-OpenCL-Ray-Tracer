#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>

class Sphere
{
public:
	Sphere();
	~Sphere();

	void setCenter(glm::vec3 inCenter) { center = inCenter; };
	void setRadius(float inRad) { radius = inRad; };

	glm::vec3 getCenter() { return center; };
	float getRadius() { return radius; };
	
private:
	glm::vec3 center;
	float radius;
};