#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Box
{
public:
	Box();
	~Box();

	std::vector<glm::vec4> getTriangleVerticies() { return triangleVerticies; }
	void storeScaleNum(float inNum) { scaleNum = inNum; }

	void matrixMultiplyTriangleVertex(unsigned int index, glm::mat4* matrix);
	float getScaleNum() { return scaleNum; }

private:
	std::vector<glm::vec4> triangleVerticies;
	float scaleNum;

	void generateBoxTriangles();
};