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

//=========================================================================================================//

//Ref: http://cs.lth.se/tomas_akenine-moller
int intersectTriangle(float orig[3], float dir[3],
	float vert0[3], float vert1[3], float vert2[3],
	float *t, float *u, float *v)
{
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det, inv_det;

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

//=========================================================================================================//

float rayTriangleIntersect(float4 rayOriginIn, float4 rayDirectionIn, float4 a, float4 b, float4 c,
	float4 intersectionPoint)
{
	float rayOrigin[3] = { rayOriginIn.x, rayOriginIn.y, rayOriginIn.z };
	float rayDirection[3] = { rayDirectionIn.x, rayDirectionIn.y, rayDirectionIn.z };

	float triangleA[3] = { a.x, a.y, a.z };
	float triangleB[3] = { b.x, b.y, b.z };
	float triangleC[3] = { c.x, c.y, c.z };

	float u = 0;
	float v = 0;
	float t = 0;

	int result = 0;
	result = intersectTriangle(rayOrigin, rayDirection, triangleA, triangleB, triangleC, &t, &u, &v);

	if (result == 1)
	{
		//get intersection point
		intersectionPoint = rayOriginIn + (rayDirectionIn * (float)t);
		return (float)t;
	}

	return (float)result;
}

//=========================================================================================================//

float normaliseFloat(float numToNorm, float minNum, float maxNum)
	{
		float normalisedNum;

		//normalise the number using the min and max value
		normalisedNum = (numToNorm - minNum) / (maxNum - minNum);

		return normalisedNum;
	}

//=========================================================================================================//

__kernel void RayTrace(unsigned int numberOfBoxes, float4 rayDirection,
	__global float4* vertices, __global float4* colours, __global float4* rayOrigins, __global int* pixels)
{
	float4 intersectionPoint;
	float dist = 0.0f;

	float closestPoint = -1000.0f;
	float4 closestColour = (float4)(0.0f, 0.0f, 0.0f, 0.0f);

	int index = 0;

	//loop through all of the boxes
	for (unsigned int box = 0; box < numberOfBoxes; box++)
	{
		//loop through all the triangles in the box
		for (int i = 0; i < 12; i++)
		{
			//ray trace the triangle
			dist = rayTriangleIntersect(rayOrigins[get_global_id(0)], rayDirection, vertices[index],
				vertices[index + 1], vertices[index + 2],
				intersectionPoint);
			if (dist != 0.0f)
			{
				//check if this point is closer
				if (dist > closestPoint)
				{
					closestPoint = dist;
					closestColour = colours[box];
				}
			}

			index += 3;
		}
	}

	float colourDist = normaliseFloat(closestPoint, 0.0f, 300.0f);

	if (colourDist < 0.0f)
	{
		colourDist = 0.0f;
	}

	//r
	pixels[get_global_id(0) * 4] = colourDist * closestColour.x;
	//g
	pixels[(get_global_id(0) * 4) + 1] = colourDist * closestColour.y;
	//b
	pixels[(get_global_id(0) * 4) + 2] = colourDist * closestColour.z;
	//alpha
	pixels[(get_global_id(0) * 4) + 3] = 255;

}
