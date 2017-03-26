#include "Box.h"

Box::Box()
{
	//generate triangles
	generateBoxTriangles();
}

Box::~Box()
{
}

void Box::matrixMultiplyTriangleVertex(unsigned int index, glm::mat4* matrix)
{
	glm::vec4 test = *matrix * triangleVerticies[index];
	triangleVerticies[index] = *matrix * triangleVerticies[index];
}

void Box::generateBoxTriangles()
{
	triangleVerticies = {
		glm::vec4(-1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f,-1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f,-1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f,-1.0f, 1.0f, 1.0f)
	};
}
