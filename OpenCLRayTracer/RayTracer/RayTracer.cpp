#include "RayTracer.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../Core/Utilities.h"

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

int RayTracer::rayTriangleIntersect(Ray& ray, Triangle& triangle, glm::vec3& intersectionPoint)
{
	double rayOrigin[3]{ ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z };
	double rayDirection[3]{ ray.getDirection().x, ray.getDirection().y, ray.getDirection().z };

	double triangleA[3]{ triangle.getPointA().x, triangle.getPointA().y, triangle.getPointA().z };
	double triangleB[3]{ triangle.getPointB().x, triangle.getPointB().y, triangle.getPointB().z };
	double triangleC[3]{ triangle.getPointC().x, triangle.getPointC().y, triangle.getPointC().z };

	double u = 0;
	double v = 0;
	double t = 0;

	int result = 0;
	result = RayTracer::intersectTriangle(rayOrigin, rayDirection, triangleA, triangleB, triangleC, &t, &u, &v);

	if (result == 1)
	{
		//get intersection point
		intersectionPoint = ray.getOrigin() + (ray.getDirection() * (float)t);
	}

	return result;
}

std::vector<unsigned char> RayTracer::rayTrace2DTriangle(Triangle triangle, glm::vec2 screenDim, glm::vec3 colour)
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
			ray.setOrigin(glm::vec3(x, y, 0));
			ray.setDirection(glm::vec3(proj * glm::vec4(0, 0, 1, 1)));

			//ray trace the triangle
			int result = RayTracer::rayTriangleIntersect(ray, triangle, glm::vec3());
			
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

std::vector<unsigned char> RayTracer::rayTraceSphere(Sphere sphere, glm::vec2 screenDim, glm::vec3 colour) 
{
	std::vector<unsigned char> pixels;
	//set the vector size to contain at least the number of pixels * 4 bytes for RGBA 
	pixels.reserve((screenDim.x * screenDim.y) * 4);

	//set the projection matrix for the ray tracer
	glm::mat4 proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.0f, 100.0f);

	//loop through all the pixels
	for (unsigned int y = 0; y < screenDim.y; y++)
	{
		for (unsigned int x = 0; x < screenDim.x; x++)
		{
			//generate the ray
			Ray ray;
			ray.setOrigin(glm::vec3(x, y, 0));
			ray.setDirection(glm::vec3(proj * glm::vec4(0, 0, 1, 1)));

			//generate the light direction
			glm::vec3 L = sphere.getCenter() - glm::vec3(ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z);

			//
			float tca = glm::dot(L, glm::vec3(ray.getDirection().x, ray.getDirection().y, ray.getDirection().z));
			
			//check if the ray has glanced of the bounds of the sphere
			if (tca < 0)
			{
				//r
				pixels.push_back(0);
				//g
				pixels.push_back(0);
				//b
				pixels.push_back(0);
				//alpha
				pixels.push_back(255);
			}
			else
			{
				//check if the ray has completly missed the sphere
				float distanceSquared = glm::dot(L, L) - (tca * tca);
				if (distanceSquared > (sphere.getRadius() * sphere.getRadius()))
				{
					//r
					pixels.push_back(0);
					//g
					pixels.push_back(0);
					//b
					pixels.push_back(0);
					//alpha
					pixels.push_back(255);
				}
				else
				{
					//the hit coordinate
					float thc = sqrt((sphere.getRadius() * sphere.getRadius()) - distanceSquared);
					float t0 = tca - thc;
					float t1 = tca + thc;

					//calculate the distance to the sphere
					float distance = glm::distance(t0, t1);
					distance = Utilities::normaliseFloat(distance, 0.0f, (sphere.getRadius() + sphere.getRadius()));

					//r
					pixels.push_back((int)(distance * colour.x));
					//g					
					pixels.push_back((int)(distance * colour.y));
					//b
					pixels.push_back((int)(distance * colour.z));
					//alpha
					pixels.push_back(255);
				}
			}
		}
	}

	return pixels;
}

std::vector<unsigned char> RayTracer::rayTraceBox(Box box, glm::vec2 screenDim, glm::vec3 colour)
{
	std::vector<unsigned char> pixels;
	//set the vector size to contain at least the number of pixels * 4 bytes for RGBA 
	pixels.reserve((screenDim.x * screenDim.y) * 4);

	//set the projection matrix for the ray tracer
	glm::mat4 proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.0f, 100.0f);

	//loop through all the pixels
	for (unsigned int y = 0; y < screenDim.y; y++)
	{
		for (unsigned int x = 0; x < screenDim.x; x++)
		{
			//generate the ray
			Ray ray;
			ray.setOrigin(glm::vec3(x, y, 0));
			ray.setDirection(glm::vec3(proj * glm::vec4(0, 0, 1, 1)));

			glm::vec3 intersectionPoint;
			float dist;

			float closestPoint = -1000.0f;
			int result = 0;

			int index = 0;

			//loop through all the triangles in the box
			for (int i = 0; i < 12; i++)
			{ 
				//ray trace the triangle
				if (RayTracer::rayTriangleIntersect(ray, box.getTriangleVerticies()[index], 
					box.getTriangleVerticies()[index + 1], box.getTriangleVerticies()[index + 2], intersectionPoint, dist) == 1)
				{
					result = 1;

					//check if this point is closer
					if (dist > closestPoint)
					{
						closestPoint = dist;
					}
				}

				index += 3;
			}			

			if (result != 1)
			{
				//r
				pixels.push_back(0);
				//g
				pixels.push_back(0);
				//b
				pixels.push_back(0);
				//alpha
				pixels.push_back(255);
			}
			else
			{

				float colourDist = Utilities::normaliseFloat(closestPoint, 0.0f, 200.0f);

				if (colourDist < 0.0f)
				{
					colourDist = 0.0f;
				}

				//r
				pixels.push_back(colourDist * colour.x);
				//g					
				pixels.push_back(colourDist * colour.y);
				//b
				pixels.push_back(colourDist * colour.z);
				//alpha
				pixels.push_back(255);
			}
		}
	}

	Utilities::logI("Box Ray Trace Ran");

	return pixels;
}

int RayTracer::rayTriangleIntersect(Ray& ray, glm::vec4& a, glm::vec4& b, glm::vec4& c, glm::vec3& intersectionPoint)
{
	double rayOrigin[3]{ ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z };
	double rayDirection[3]{ ray.getDirection().x, ray.getDirection().y, ray.getDirection().z };

	double triangleA[3]{ a.x, a.y, a.z };
	double triangleB[3]{ b.x, b.y, b.z };
	double triangleC[3]{ c.x, c.y, c.z };

	double u = 0;
	double v = 0;
	double t = 0;

	int result = 0;
	result = RayTracer::intersectTriangle(rayOrigin, rayDirection, triangleA, triangleB, triangleC, &t, &u, &v);

	if (result == 1)
	{
		//get intersection point
		intersectionPoint = ray.getOrigin() + (ray.getDirection() * (float)t);
	}

	return result;
}

int RayTracer::rayTriangleIntersect(Ray& ray, glm::vec4& a, glm::vec4& b, glm::vec4& c, 
	glm::vec3& intersectionPoint, float& dist)
{
	double rayOrigin[3]{ ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z };
	double rayDirection[3]{ ray.getDirection().x, ray.getDirection().y, ray.getDirection().z };

	double triangleA[3]{ a.x, a.y, a.z };
	double triangleB[3]{ b.x, b.y, b.z };
	double triangleC[3]{ c.x, c.y, c.z };

	double u = 0;
	double v = 0;
	double t = 0;

	int result = 0;
	result = RayTracer::intersectTriangle(rayOrigin, rayDirection, triangleA, triangleB, triangleC, &t, &u, &v);

	if (result == 1)
	{
		//get intersection point
		intersectionPoint = ray.getOrigin() + (ray.getDirection() * (float)t);
		dist = (float)t;
	}

	return result;
}