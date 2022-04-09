#include "AABB.h"
#include "Triangle3D.h"
#include <math.h>
#include <stdio.h>


GEO::Vec3D GEO::AABB::getCenter() const
{
	// El Extent pasa por el centro y esta a la mitad desde min a max
	return { getMin() + getExtent() / 2 };
}

GEO::Vec3D GEO::AABB::getExtent() const
{
	return { _max - _min };
}






/********************************************************/

/* AABB-triangle overlap test code                      */

/* by Tomas Akenine-M�ller                              */

/* Function: int triBoxOverlap(float boxcenter[3],      */

/*          float boxhalfsize[3],float triverts[3][3]); */

/* History:                                             */

/*   2001-03-05: released the code in its first version */

/*   2001-06-18: changed the order of the tests, faster */

/*                                                      */

/* Acknowledgement: Many thanks to Pierre Terdiman for  */

/* suggestions and discussions on how to optimize code. */

/* Thanks to David Hunt for finding a ">="-bug!         */

/********************************************************/

/*
Copyright 2020 Tomas Akenine-M�ller

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <math.h>

#include <stdio.h>



#define X 0

#define Y 1

#define Z 2



#define CROSS(dest,v1,v2) \
dest[0] = v1[1] * v2[2] - v1[2] * v2[1]; \
dest[1] = v1[2] * v2[0] - v1[0] * v2[2]; \
dest[2] = v1[0] * v2[1] - v1[1] * v2[0];



#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])



#define SUB(dest,v1,v2) \
dest[0] = v1[0] - v2[0]; \
dest[1] = v1[1] - v2[1]; \
dest[2] = v1[2] - v2[2];



#define FINDMINMAX(x0,x1,x2,min,max) \
min = max = x0;   \
if (x1 < min) min = x1; \
	if (x1 > max) max = x1; \
		if (x2 < min) min = x2; \
			if (x2 > max) max = x2;



int planeBoxOverlap(float normal[3], float vert[3], float maxbox[3])	// -NJMP-

{
	int q;
	float vmin[3], vmax[3], v;

	for (q = X; q <= Z; q++)
	{
		v = vert[q];

		if (normal[q] > 0.0f)
		{
			vmin[q] = -maxbox[q] - v;	// -NJMP-
			vmax[q] = maxbox[q] - v;	// -NJMP-
		}
		else
		{
			vmin[q] = maxbox[q] - v;	// -NJMP-
			vmax[q] = -maxbox[q] - v;	// -NJMP-
		}
	}

	if (DOT(normal, vmin) > 0.0f) return 0;	// -NJMP-

	if (DOT(normal, vmax) >= 0.0f) return 1;	// -NJMP-



	return 0;

}





/*======================== X-tests ========================*/

#define AXISTEST_X01(a, b, fa, fb)			   \
p0 = a * v0[Y] - b * v0[Z];			       	   \
p2 = a * v2[Y] - b * v2[Z];			       	   \
if (p0 < p2) { min = p0; max = p2; }			\
else { min = p2; max = p0; } \
rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
if (min > rad || max < -rad) return 0;



#define AXISTEST_X2(a, b, fa, fb)			   \
p0 = a * v0[Y] - b * v0[Z];			           \
p1 = a * v1[Y] - b * v1[Z];			       	   \
if (p0 < p1) { min = p0; max = p1; }\
else { min = p1; max = p0; } \
rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
if (min > rad || max < -rad) return 0;


/*======================== Y-tests ========================*/

#define AXISTEST_Y02(a, b, fa, fb)			   \
p0 = -a * v0[X] + b * v0[Z];		      	   \
p2 = -a * v2[X] + b * v2[Z];	       	       	   \
if (p0 < p2) { min = p0; max = p2; }\
else { min = p2; max = p0; } \
rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
if (min > rad || max < -rad) return 0;


#define AXISTEST_Y1(a, b, fa, fb)			   \
p0 = -a * v0[X] + b * v0[Z];		      	   \
p1 = -a * v1[X] + b * v1[Z];	     	       	   \
if (p0 < p1) { min = p0; max = p1; }\
else { min = p1; max = p0; } \
rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
if (min > rad || max < -rad) return 0;


/*======================== Z-tests ========================*/

#define AXISTEST_Z12(a, b, fa, fb)			   \
p1 = a * v1[X] - b * v1[Y];			           \
p2 = a * v2[X] - b * v2[Y];			       	   \
if (p2 < p1) { min = p2; max = p1; }\
else { min = p1; max = p2; } \
rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
if (min > rad || max < -rad) return 0;


#define AXISTEST_Z0(a, b, fa, fb)			   \
p0 = a * v0[X] - b * v0[Y];				   \
p1 = a * v1[X] - b * v1[Y];			           \
if (p0 < p1) { min = p0; max = p1; }\
else { min = p1; max = p0; } \
rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
if (min > rad || max < -rad) return 0;


bool triBoxOverlap(float boxcenter[3], float boxhalfsize[3], float triverts[3][3])
{
	/*    use separating axis theorem to test overlap between triangle and box */
	/*    need to test for overlap in these directions: */
	/*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
	/*       we do not even need to test these) */
	/*    2) normal of the triangle */
	/*    3) crossproduct(edge from tri, {x,y,z}-directin) */
	/*       this gives 3x3=9 more tests */

	float v0[3], v1[3], v2[3];
	//   float axis[3];

	float min, max, p0, p1, p2, rad, fex, fey, fez;		// -NJMP- "d" local variable removed
	float normal[3], e0[3], e1[3], e2[3];

	/* This is the fastest branch on Sun */
	/* move everything so that the boxcenter is in (0,0,0) */
	SUB(v0, triverts[0], boxcenter);
	SUB(v1, triverts[1], boxcenter);
	SUB(v2, triverts[2], boxcenter);



	/* compute triangle edges */
	SUB(e0, v1, v0);      /* tri edge 0 */
	SUB(e1, v2, v1);      /* tri edge 1 */
	SUB(e2, v0, v2);      /* tri edge 2 */

	/* Bullet 3:  */
	/*  test the 9 tests first (this was faster) */
	fex = fabsf(e0[X]);
	fey = fabsf(e0[Y]);
	fez = fabsf(e0[Z]);

	AXISTEST_X01(e0[Z], e0[Y], fez, fey);
	AXISTEST_Y02(e0[Z], e0[X], fez, fex);
	AXISTEST_Z12(e0[Y], e0[X], fey, fex);

	fex = fabsf(e1[X]);
	fey = fabsf(e1[Y]);
	fez = fabsf(e1[Z]);

	AXISTEST_X01(e1[Z], e1[Y], fez, fey);
	AXISTEST_Y02(e1[Z], e1[X], fez, fex);
	AXISTEST_Z0(e1[Y], e1[X], fey, fex);
	
	fex = fabsf(e2[X]);
	fey = fabsf(e2[Y]);
	fez = fabsf(e2[Z]);

	AXISTEST_X2(e2[Z], e2[Y], fez, fey);
	AXISTEST_Y1(e2[Z], e2[X], fez, fex);
	AXISTEST_Z12(e2[Y], e2[X], fey, fex);

	/* Bullet 1: */
	/*  first test overlap in the {x,y,z}-directions */
	/*  find min, max of the triangle each direction, and test for overlap in */
	/*  that direction -- this is equivalent to testing a minimal AABB around */
	/*  the triangle against the AABB */


	/* test in X-direction */
	FINDMINMAX(v0[X], v1[X], v2[X], min, max);
	if (min > boxhalfsize[X] || max < -boxhalfsize[X]) return false;


	/* test in Y-direction */
	FINDMINMAX(v0[Y], v1[Y], v2[Y], min, max);
	if (min > boxhalfsize[Y] || max < -boxhalfsize[Y]) return false;


	/* test in Z-direction */
	FINDMINMAX(v0[Z], v1[Z], v2[Z], min, max);
	if (min > boxhalfsize[Z] || max < -boxhalfsize[Z]) return false;


	/* Bullet 2: */

	/*  test if the box intersects the plane of the triangle */
	/*  compute plane equation of triangle: normal*x+d=0 */
	CROSS(normal, e0, e1);

	// -NJMP- (line removed here)

	if (!planeBoxOverlap(normal, v0, boxhalfsize)) return false;	// -NJMP-

	return true;   /* box and triangle overlaps */
}





bool GEO::AABB::AABBtri(const Triangle3D& tri) const
{
	const Vec3D mycenter = getCenter();
	const Vec3D extent = _max - _min;
	const Vec3D myhalfsize = extent / 2;
	float center[3] = {(float)mycenter.getX(), (float)mycenter.getY(), (float)mycenter.getZ()};
	float halfSize[3] = {(float)myhalfsize.getX(), (float)myhalfsize.getY(), (float)myhalfsize.getZ()};
	float triVerts[3][3] =
	{
		{(float)tri.getA().getX(), (float)tri.getA().getY(), (float)tri.getA().getZ()},
		{(float)tri.getB().getX(), (float)tri.getB().getY(), (float)tri.getB().getZ()},
		{(float)tri.getC().getX(), (float)tri.getC().getY(), (float)tri.getC().getZ()},
	};
	return triBoxOverlap(center, halfSize, triVerts);
}

bool GEO::AABB::pointInAABB(const Vec3D& point) const
{
	return point < _max && point > _min;
}


