#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>

class Triangle
{
public:
	Triangle();
	~Triangle();

	void setPointA(glm::vec3 inPoint) { pointA = inPoint; };
	void setPointB(glm::vec3 inPoint) { pointB = inPoint; };
	void setPointC(glm::vec3 inPoint) { pointC = inPoint; };

	glm::vec3 getPointA() { return pointA; };
	glm::vec3 getPointB() { return pointB; };
	glm::vec3 getPointC() { return pointC; };

private:
	glm::vec3 pointA; // 0, -1, 0   /\  // 150, 0, 0
	glm::vec3 pointB; // -1, 1, 0  /__\ // 0, 300, 0
	glm::vec3 pointC; // 1, 1, 0        // 300, 300, 0
};