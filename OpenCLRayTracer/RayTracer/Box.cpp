#include "Box.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../Core/Utilities.h"

Box::Box()
{
	//generate triangles
	generateBoxTriangles();

	//initalise colour to white
	colour = glm::vec3(255.0f, 255.0f, 255.0f);
}

Box::Box(float inScale, glm::vec3 translation, float angle, glm::vec3 axis)
{
	//generate triangles
	generateBoxTriangles();

	//Translate Box
	scaleBox(inScale);
	translateBox(translation);
	rotateBox(angle, axis);

	//initalise colour to white
	colour = glm::vec3(255.0f, 255.0f, 255.0f);
}

Box::~Box()
{
}

void Box::matrixMultiplyTriangleVertex(unsigned int index, glm::mat4* matrix)
{
	glm::vec4 test = *matrix * triangleVerticies[index];
	triangleVerticies[index] = *matrix * triangleVerticies[index];
}

void Box::scaleBox(float inScale)
{
	m = glm::scale(glm::mat4(1.0f), glm::vec3(inScale, inScale, inScale));
	for (unsigned int i = 0; i < getTriangleVerticies().size(); i++)
	{
		matrixMultiplyTriangleVertex(i, &m);
	}
	storeScaleNum(inScale);
}

void Box::translateBox(glm::vec3 translation)
{
	m = glm::translate(glm::mat4(1.0f), translation);
	for (unsigned int i = 0; i < getTriangleVerticies().size(); i++)
	{
		matrixMultiplyTriangleVertex(i, &m);
	}
}

void Box::rotateBox(float angle, glm::vec3 axis)
{
	m = glm::rotate(m, Utilities::convertDegreeToRadian(angle), axis);
	for (unsigned int i = 0; i < getTriangleVerticies().size(); i++)
	{
		matrixMultiplyTriangleVertex(i, &m);
	}
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
