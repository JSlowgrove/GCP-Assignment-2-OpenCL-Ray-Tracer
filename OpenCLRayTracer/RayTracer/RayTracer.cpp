#include "RayTracer.h"

#include "glm/gtc/matrix_transform.hpp"

//Ref: http://cs.lth.se/tomas_akenine-moller
int RayTracer::intersectTriangle(double orig[3], double dir[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *t, double *u, double *v)
{
	double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	double det, inv_det;

	/* find vectors for two edges sharing vert0 */
	SUB(edge1, vert1, vert0);
	SUB(edge2, vert2, vert0);

	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);

	if (det > -EPSILON && det < EPSILON)
		return 0;
	inv_det = 1.0 / det;

	/* calculate distance from vert0 to ray origin */
	SUB(tvec, orig, vert0);

	/* calculate U parameter and test bounds */
	*u = DOT(tvec, pvec) * inv_det;
	if (*u < 0.0 || *u > 1.0)
		return 0;

	/* prepare to test V parameter */
	CROSS(qvec, tvec, edge1);

	/* calculate V parameter and test bounds */
	*v = DOT(dir, qvec) * inv_det;
	if (*v < 0.0 || *u + *v > 1.0)
		return 0;

	/* calculate t, ray intersects triangle */
	*t = DOT(edge2, qvec) * inv_det;

	return 1;
}

int RayTracer::rayTriangleIntersect(Ray& ray, Triangle& triangle)
{
	double rayOrigin[3]{ ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z };
	double rayDirection[3]{ ray.getDirection().x, ray.getDirection().y, ray.getDirection().z };

	double triangleA[3]{ triangle.getPointA().x, triangle.getPointA().y, triangle.getPointA().z };
	double triangleB[3]{ triangle.getPointB().x, triangle.getPointB().y, triangle.getPointB().z };
	double triangleC[3]{ triangle.getPointC().x, triangle.getPointC().y, triangle.getPointC().z };

	double t = 0;
	double u = 0;
	double v = 0;

	return RayTracer::intersectTriangle(rayOrigin, rayDirection, triangleA, triangleB, triangleC, &t, &u, &v);
}

std::vector<unsigned char> RayTracer::rayTraceTriangle(Triangle triangle, glm::vec2 screenDim, glm::vec3 colour)
{
	std::vector<unsigned char> pixels;
	//set the vector size to contain at least the number of pixels * 4 bytes for RGBA 
	pixels.reserve((screenDim.x * screenDim.y) * 4);

	//set the projection matrix for the ray tracer
	glm::mat4 proj = glm::ortho(0.0f, screenDim.x, screenDim.y, 0.0f, 0.0f, 1000.0f);

	//loop through all the pixels
	for (unsigned int y = 0; y < screenDim.y; y++)
	{
		for (unsigned int x = 0; x < screenDim.x; x++)
		{
			//generate the ray
			Ray ray;
			ray.setOrigin(glm::vec4(x, y, 0, 1));
			ray.setDirection(proj * glm::vec4(0, 0, 1, 1));

			//ray trace the triangle
			int result = RayTracer::rayTriangleIntersect(ray, triangle);
			
			//if the result is equal 1 set red channel to in red
			pixels.push_back(result == 1 ? colour.x : 0);
			//if the result is equal 1 set green channel to in green
			pixels.push_back(result == 1 ? colour.y : 0);
			//if the result is equal 1 set blue channel to in blue
			pixels.push_back(result == 1 ? colour.z : 0);
			//alpha
			pixels.push_back(255);
		}
	}

	return pixels;
}