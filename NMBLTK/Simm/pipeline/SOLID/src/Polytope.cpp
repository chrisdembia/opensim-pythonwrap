#include "Polytope.h"
#define TOL2 1e-6

#define DEBUG_CONTAINS 0
#define DEBUG_CLIP 0
#define DEBUG_INTERSECT 0

/* Check if a 3D point is inside a 3D polytope. This function assumes
 * that the point is in the plane of the polytope.
 */
bool Polytope::contains(Point& p) const
{
int i, count = 0, v1, v2;
double s, t, dist, maxDist;
Point pProj, pmid, p2, int_pt;
bool found_v1 = false, found_v2 = false, found_p = false;

   /* if the point is equal to one of the vertices of the polygon, 
    * it is contained in the polygon */
   for (i = 0; i < numVerts(); i++) {
      if (points_equal(p, (*this)[i], 1e-6) == true) {
         if (DEBUG_CONTAINS) printf("p = v%d\n", i);
	      return(true);
      }
   }

   /* First project the point onto the plane of the polytope,
    * in case it's not quite in the plane already.
    */
   dist = dot(p,(*this).normal) + (*this).d;
   pProj = p - dist * (*this).normal;

   /* Form a vector from pProj to the midpoint of the first and second
    * vertices of the polytope, and then extend it far enough so
    * that it definitely extends beyond the polygon.
    */

   /* Find square of distance to farthest vertex */
   for (maxDist = 0.0, i = 0; i < numVerts(); i++)
   {
      dist = distance2(pProj,(*this)[i]);
      if (dist > maxDist)
	 maxDist = dist;
   }
   pmid = ((*this)[0] + (*this)[1]) * 0.5;

   if (points_equal(p2, pProj, 1e-8) == true)
   {
      /* pProj is on the edge from vertex 0 to vertex 1 */
      return true;
   }
   else
   {
      /* p2 is a point on the line from pProj to pmid, and
       * is twice as far from pProj as is the farthest vertex.
       */
      Vector v = pmid - pProj;
      p2 = pmid + 2.0*maxDist/v.length2() * v;
   }

   if (DEBUG_CONTAINS)
   {
      printf("\n   p  = %f %f %f\n", pProj[0], pProj[1], pProj[2]);
      printf("   p2 = %f %f %f\n", p2[0], p2[1], p2[2]);
   }

   for (i = 0; i < numVerts(); i++)
   {
      if (DEBUG_CONTAINS)	printf("   int. with v%d-v%d?  ", i, (i+1)%numVerts());
      if (intersectLineSegments(pProj, p2, (*this)[i], (*this)[(i+1)%numVerts()], 
      	int_pt, s, t, ILS_TOL) == true ) {
		if (DEBUG_CONTAINS)  {
			printf("yes\n");
			printf("\tv%d = %f %f %f\n", i, (*this)[i][0], (*this)[i][1], 
					(*this)[i][2]);
			printf("\tv%d = %f %f %f\n", i+1, (*this)[(i+1)%numVerts()][0],
					 (*this)[(i+1)%numVerts()][1], (*this)[(i+1)%numVerts()][2]);
			printf("\tint = %f %f %f  ", int_pt[0], int_pt[1], int_pt[2]);
			printf(" s = %3.3f t = %3.3f  ", s, t);
			}
			
			count++;
			
			/* check whether or not the intersection point is a vertex of poly */
	 		if (EQUAL_WITHIN_TOLERANCE(s, 0.0, TOLERANCE)) {
	 			if (DEBUG_CONTAINS)	printf("int = v%d  ", i); 
	 			found_v1 = true; v1 = i;
	 		}
	 		if (EQUAL_WITHIN_TOLERANCE(s, 1.0, TOLERANCE)) {
	 			if (DEBUG_CONTAINS)	printf("int = v%d  ", (i+1)%numVerts());
	 			found_v2 = true; v2 = (i+1)%numVerts();
			}
			/* check whether or not the intersection point = pProj */
			if	(points_equal(pProj, int_pt, TOLERANCE) == true)	{
				if (DEBUG_CONTAINS)	printf("int pt = pProj  ");
				found_p = true;
			}
			if (DEBUG_CONTAINS) printf("\n");
		} else if (DEBUG_CONTAINS) printf("no\n");
   }
	if (DEBUG_CONTAINS)	printf("   count = %d\n", count);

	/* if the same vertex on POLY was found twice, remove one from count */
	if ((found_v1 == true && found_v2 == true) && (v1 == v2)) {
		if (DEBUG_CONTAINS)	printf("   same vertex found twice (v%d)\n", v1); 
		count--;
	}
	/* if the intersection was the same as the point, remove from count */
	if (found_p == true) {
		if (DEBUG_CONTAINS) printf("   int pt = pProj\n");
		count--;
	}
	if (DEBUG_CONTAINS)	printf("   count = %d,  count / 2 = %d\n", count, count % 2);
	
	/* if an odd number of crossings was found, point is within poly */
   if ((count % 2) == 1) {
       if (DEBUG_CONTAINS) printf("   pProj is within poly\n"); 
	/*	if (DEBUG_CONTAINS) printf("try again\n");
		pmid = ((*this)[1] + (*this)[2]) * 0.5;
		count = 0;
		found_v1 = false; found_v2 = false; found_p = false;
		if (points_equal(p2, pProj, 1e-8) == true) {
    			 return true;
                } else {
 		     Vector v = pmid - pProj;
 		     p2 = pmid + 2.0*maxDist/v.length2() * v;
 		}
  		 for (i = 0; i < numVerts(); i++)
  		 {
     		       if (DEBUG_CONTAINS)	printf("   int. with v%d-v%d?  ", i, (i+1)%numVerts());
		if (intersectLineSegments(pProj, p2, (*this)[i], (*this)[(i+1)%numVerts()], 
      	int_pt, s, t, ILS_TOL) == true ) {	
		
		if (DEBUG_CONTAINS) {	printf("yes\n");
			printf("\tv%d = %f %f %f\n", i, (*this)[i][0], (*this)[i][1], 
					(*this)[i][2]);
			printf("\tv%d = %f %f %f\n", i+1, (*this)[(i+1)%numVerts()][0],
					 (*this)[(i+1)%numVerts()][1], (*this)[(i+1)%numVerts()][2]);
			printf("\tint = %f %f %f  ", int_pt[0], int_pt[1], int_pt[2]);
			printf(" s = %3.3f t = %3.3f  ", s, t);
			}

			count++;
			if (EQUAL_WITHIN_TOLERANCE(s, 0.0, TOLERANCE)) {
	 			if (DEBUG_CONTAINS)	printf("int = v%d  ", i); 
	 			found_v1 = true; v1 = i;
	 		}
	 		if (EQUAL_WITHIN_TOLERANCE(s, 1.0, TOLERANCE)) {
	 			if (DEBUG_CONTAINS)	printf("int = v%d  ", (i+1)%numVerts());
	 			found_v2 = true; v2 = (i+1)%numVerts();
			}
			if	(points_equal(pProj, int_pt, TOLERANCE) == true)	{
				if (DEBUG_CONTAINS)	printf("int pt = pProj  ");
				found_p = true;
			}
			if (DEBUG_CONTAINS) printf("\n");
		} else if (DEBUG_CONTAINS) printf("no\n");
   		}
	if (DEBUG_CONTAINS)	printf("   count = %d\n", count);
	if ((found_v1 == true && found_v2 == true) && (v1 == v2)) {
		if (DEBUG_CONTAINS)	printf("   same vertex found twice (v%d)\n", v1); 
		count--;
	}
	if (found_p == true) {
		if (DEBUG_CONTAINS) printf("   int pt = pProj\n");
		count--;
	}
	if (DEBUG_CONTAINS)	printf("   count = %d,  count / 2 = %d\n", count, count % 2);

       if ((count % 2) == 1) 
         return true;
       else return false;
*/
	return true;
   }
 if (DEBUG_CONTAINS) printf("   pProj is not in Poly\n");
   return false;
}

/* Clip an edge against a polytope. This function assumes that the edge
 * is in the plane of the polytope.
 */
void Polytope::clipEdge(Point& p1, Point& p2, Point& p3, Point& p4) const
{
int  i;
double	s, t;
Point  int_pt, v1, v2;
bool  clip1 = false, clip2 = false;

   p3 = p1;
   p4 = p2;
if (DEBUG_CLIP)
for (i = 0; i < numVerts(); i++)
   printf("v%d = %f %f %f\n", i, (*this)[i][0], (*this)[i][1], (*this)[i][2]);


   for (i = 0; i < numVerts(); i++)
   {
      if (DEBUG_CLIP) {
         printf("p3 = %f %f %f\n", p3[0], p3[1], p3[2]);
         printf("p4 = %f %f %f\n", p4[0], p4[1], p4[2]);
         printf("p3-p4 and v%d-v%d?", i, (i+1)%numVerts());
      }
      if (intersectLineSegments(p3, p4, (*this)[i], (*this)[(i+1)%numVerts()], 
      	int_pt, s, t, CLIP_TOL) == true)
      {
         if (DEBUG_CLIP) printf("  yes");
         /* If p3 is inside the polygon, then p4 must be outside,
          * so clip the edge: replace p4 with the intersection point.  If p4
          * is inside the polygon, replace p3 with the intersection point to
          * clip the edge.  If neither point is in the polygon, two edges must
          * be clipped.  If no edges have been clipped yet, store the 
          * intersection point in v1 and keep checking.  If the first edge was
          * clipped, store the intersection point in v2.  When both clipping
          * points are found, return them in p3 and p4. 
          */
         if (this->contains(p3) == true) {
            if (points_equal(p3, int_pt, TOLERANCE) == false) {
               p4 = int_pt;
               if (DEBUG_CLIP) printf("  p3 in poly, p4 = int\n"); 
            } else {
               if (DEBUG_CLIP) printf("  int = p3, no change\n");
            }
         } else if (this->contains(p4) == true) {
            if (points_equal(p4, int_pt, TOLERANCE) == false) {
               p3 = int_pt;
               if (DEBUG_CLIP) printf("  p4 in poly, p3 = int\n"); 
            } else {
               if (DEBUG_CLIP) printf("  int = p4, no change\n");
            }
         } else	{
            if (DEBUG_CLIP) printf("  neither in poly\n");
            if (clip1 == false) {
               v1 = int_pt;
               clip1 = true;
            } else if (clip2 == false) {			
               v2 = int_pt;
               clip2 = true;
            }
            if ((clip1 == true) && (clip2 == true)) {
               p3 = v1;
               p4 = v2;
               break;
            }
         }
      } else if (DEBUG_CLIP) printf("  no\n");
   }
/* can still be a bad point if no intersections are found because the points
 * don't lie on one of the lines.  */
   if ((clip1 == false) && (clip2 == false)) {
     // printf("No intersections found between line and plane\n");
/*exit(0);*/
   }
}


bool Polytope::intersectLineSegments(Point& p1, Point& p2, const Point& p3,
				     const Point& p4, Point& p5, double& s, double& t, double tol) const
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
   	if (DEBUG_INTERSECT) printf("   Lines are parallel - no intersection\n");
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

   s = CALC_DETERMINANT(mat) / denom;

   mat[1][0] = vec2[0];
   mat[1][1] = vec2[1];
   mat[1][2] = vec2[2];

   t = CALC_DETERMINANT(mat) / denom;

   /* if the intersection is not on the line between p1 and p2 (0.0 < s < mag2),
    * or not on the line between p3 and p4 (0.0 < t < mag1), it is not valid */
   if (s < (-1.0*TOL2) || s > (mag2+TOL2) || t < (-1.0*TOL2) || t > (mag1+TOL2)) {
      if (DEBUG_INTERSECT) printf("   Point not on one line s = %f, t = %f\n", s, t);
      return false;
   }

   /* if the lines are not close enough together, there is no intersection */
   Point p3new = p3 + s * vec2;
   Point p1new = p1 + t * vec1;
   if (::distance(p1new, p3new) > tol)	{
       if (DEBUG_INTERSECT) printf("dist = %f\n", ::distance(p1new, p3new));
       return(false);
   }
   /* average the intersection points from each line segment */
   p5 = (p1new + p3new) * 0.5;

   if (DEBUG_INTERSECT) {
      printf("   p1 = %f %f %f\n", p1new[0], p1new[1], p1new[2]);
      printf("   p3 = %f %f %f\n", p3new[0], p3new[1], p3new[2]);
   }
   t /= mag1;
   s /= mag2;
   if (DEBUG_INTERSECT) printf("   t = %f, s = %f\n", t, s);
   return true;
}

double euclidianNormal(Point& p1, Point& p2)
{

   Vector v = p2 - p1;

   return sqrt(dot(v,v));

}

double triangleArea(Point p1, Point p2, Point p3)
{

   /* Find the projection of (P3-P1) onto (P2-P1). */
   Vector v12 = p2 - p1;
   Vector v13 = p3 - p1;
   double dotProd = dot(v12,v13);

   double base = euclidianNormal(p1,p2);

   /* The height of the triangle is the length of (P3-P1) after its
    * projection onto (P2-P1) has been subtracted.
    */

   double height;
   if (EQUAL_WITHIN_TOLERANCE(base,0.0,TOLERANCE))
   {
      height = 0.0;
   }
   else
   {
      double alpha = dotProd / (base * base);
      
      double a = p3[0] - p1[0] - alpha * (p2[0] - p1[0]);
      double b = p3[1] - p1[1] - alpha * (p2[1] - p1[1]);
      double c = p3[2] - p1[2] - alpha * (p2[2] - p1[2]);

      height = sqrt(a*a + b*b + c*c);
   }

   return 0.5 * base * height;

}


Point Polytope::centroid() const
{
double area, areaT;
Point p(0.0,0.0,0.0);

	if (numVerts() == 1)
		p = (*this)[0];
	else if (numVerts() == 2) {
		p = ((*this)[0] + (*this)[1]) * 0.5;
	} else {
		area = 0.0;
		Point p3 = (*this)[numVerts()-1];

		for (int i = 0; i < numVerts() - 2; i++)
		{
			Point p1 = (*this)[i];
			Point p2 = (*this)[i+1];
			areaT = triangleArea(p1,p2,p3);
			area = area + areaT;
			p += areaT * (p1 + p2 + p3) / 3.0;
		}
		p /= area;
	}
	return p;
}


