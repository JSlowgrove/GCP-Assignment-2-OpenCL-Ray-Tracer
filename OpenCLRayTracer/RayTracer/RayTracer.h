#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Ray.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Box.h"

//Macros
// Ref: http://cs.lth.se/tomas_akenine-moller
#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 

namespace RayTracer
{
	//Ref: http://cs.lth.se/tomas_akenine-moller
	int intersectTriangle(double orig[3], double dir[3],
		double vert0[3], double vert1[3], double vert2[3],
		double *t, double *u, double *v);

	//A function to test for a ray triangle intersection
	int rayTriangleIntersect(Ray& ray, Triangle& triangle, glm::vec3& intersectionPoint);

	int rayTriangleIntersect(Ray& ray, glm::vec4& a, glm::vec4& b, glm::vec4& c, glm::vec3& intersectionPoint, float& distance);

	std::vector<unsigned char> rayTraceBoxes(std::vector<Box> boxes, glm::vec2 screenDim);
	//ray trace a triangle
	std::vector<unsigned char> rayTrace2DTriangle(Triangle triangle, glm::vec2 screenDim, glm::vec3 colour);

	//ray trace a sphere
	std::vector<unsigned char> rayTraceSphere(Sphere sphere, glm::vec2 screenDim, glm::vec3 colour);

	//ray trace a box
	std::vector<unsigned char> rayTraceBox(Box box, glm::vec2 screenDim, glm::vec3 colour);

	//ray trace a triangle
	int rayTriangleIntersect(Ray& ray, glm::vec4& a, glm::vec4& b, glm::vec4& c, glm::vec3& intersectionPoint);
};
