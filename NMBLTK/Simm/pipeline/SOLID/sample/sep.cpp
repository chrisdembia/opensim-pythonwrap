#include <stdio.h>
#include <fstream.h>
#include <SOLID/solid.h>

#include <assert.h>

#include <3D/Point.h>
#include <3D/Quaternion.h>
#include <vector.h>
#include <../src/Polytope.h>
#include <../src/Polygon.h>

#define DEBUG_INTERSECT 1
#define TOL2 0.000001

bool intersectLineSegments(Point& p1, Point& p2, const Point& p3,
			   const Point& p4, Point& p5, double& s, double& t)
{

   Vector vec1 = p2 - p1;
   double mag1 = vec1.length();
   vec1.normalize();

   Vector vec2 = p4 - p3;
   double mag2 = vec2.length();
   vec2.normalize();
   Vector crossProd = cross(vec1,vec2);
   double denom = crossProd.length2();

   if (DEBUG_INTERSECT) {
      printf("\n   v1 = %f %f %f\n", vec1[0], vec1[1], vec1[2]);
      printf("   v2 = %f %f %f\n", vec2[0], vec2[1], vec2[2]);
      printf("   crossprod = %f %f %f\n", crossProd[0], crossProd[1], crossProd[2]);
      printf("   denom = %f\n", denom);
   }

   if (EQUAL_WITHIN_TOLERANCE(denom, 0.0, TOL2)) {
   	if (DEBUG_INTERSECT) printf("   Lines parallel. denom = 0.0\n");
	return false;
   }

   double mat[3][3];

   mat[0][0] = p3[0] - p1[0];
   mat[0][1] = p3[1] - p1[1];
   mat[0][2] = p3[2] - p1[2];
   mat[1][0] = vec1[0];
   mat[1][1] = vec1[1];
   mat[1][2] = vec1[2];
   mat[2][0] = crossProd[0];
   mat[2][1] = crossProd[1];
   mat[2][2] = crossProd[2];

   printf("mat1 = \n");
   printf("%13.9lf %13.9lf %13.9lf\n", mat[0][0], mat[0][1], mat[0][2]);
   printf("%13.9lf %13.9lf %13.9lf\n", mat[1][0], mat[1][1], mat[1][2]);
   printf("%13.9lf %13.9lf %13.9lf\n", mat[2][0], mat[2][1], mat[2][2]);
   printf("determinant = %13.9lf\n", CALC_DETERMINANT(mat));

   s = CALC_DETERMINANT(mat) / denom;

   mat[1][0] = vec2[0];
   mat[1][1] = vec2[1];
   mat[1][2] = vec2[2];

   printf("mat2 = \n");
   printf("%13.9lf %13.9lf %13.9lf\n", mat[0][0], mat[0][1], mat[0][2]);
   printf("%13.9lf %13.9lf %13.9lf\n", mat[1][0], mat[1][1], mat[1][2]);
   printf("%13.9lf %13.9lf %13.9lf\n", mat[2][0], mat[2][1], mat[2][2]);
   printf("determinant = %13.9lf\n", CALC_DETERMINANT(mat));

   t = CALC_DETERMINANT(mat) / denom;

   /* if the intersection is not on the line between p1 and p2 (0.0 < s < mag2),
    * or not on the line between p3 and p4 (0.0 < t < mag1), it is not valid.
    */
   if (s < (-1.0*TOL2) || s > (mag2+TOL2) || t < (-1.0*TOL2) || t > (mag1+TOL2))
   {
      if (DEBUG_INTERSECT)
	 printf("   point not on either line s = %13.9f, t = %13.9f\n", s, t);
      return false;
   }

   /* average the intersection points from each line segment */
   p5 = (p3 + s * vec2 + p1 + t * vec1) * 0.5;

   Point p3new = p3 + s * vec2;
   Point p1new = p1 + t * vec1;

   if (DEBUG_INTERSECT)
      printf("p1 = %f %f %f\n", p1new[0], p1new[1], p1new[2]);

   if (DEBUG_INTERSECT)
      printf("p3 = %f %f %f\n", p3new[0], p3new[1], p3new[2]);

   t /= mag1;
   s /= mag2;

   if (DEBUG_INTERSECT)
      printf("   t = %13.9f, s = %13.9f\n", t, s);

   return true;

}


int main(int argc, char *argv[])
{

   Point pts[5];
   double s, t;

   pts[0][0] = 3.0;
   pts[0][1] = 1.0;
   pts[0][2] = -3.0;

   pts[1][0] = -3.0;
   pts[1][1] = 1.0;
   pts[1][2] = -3.0;

   pts[2][0] = 3.999997;
   pts[2][1] = 1.006106;
   pts[2][2] = 0.500000;

   pts[3][0] = -2.000000;
   pts[3][1] = 1.000000;
   pts[3][2] = 0.500000;

   intersectLineSegments(pts[0],pts[1],pts[2],pts[3],pts[4],s,t);

}

