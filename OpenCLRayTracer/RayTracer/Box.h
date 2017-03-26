#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Box
{
public:
	Box();
	Box(float inScale, glm::vec3 translation, float angle, glm::vec3 axis);
	~Box();

	std::vector<glm::vec4> getTriangleVerticies() { return triangleVerticies; }
	void storeScaleNum(float inNum) { scaleNum = inNum; }

	void matrixMultiplyTriangleVertex(unsigned int index, glm::mat4* matrix);
	float getScaleNum() { return scaleNum; }

	void scaleBox(float inScale);
	void translateBox(glm::vec3 translation);
	void rotateBox(float angle, glm::vec3 axis);

private:
	std::vector<glm::vec4> triangleVerticies;
	float scaleNum;
	glm::mat4 m;

	void generateBoxTriangles();
};