/*
  SOLID - Software Library for Interference Detection
  Copyright (C) 1997-1998  Gino van den Bergen

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public
  License along with this library; if not, write to the Free
  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  Please send remarks, questions and bug reports to gino@win.tue.nl,
  or write to:
                  Gino van den Bergen
		  Department of Mathematics and Computing Science
		  Eindhoven University of Technology
		  P.O. Box 513, 5600 MB Eindhoven, The Netherlands
*/

#include "Convex.h"
#include "BBox.h"
#include "Transform.h"
#include "Complex.h"
#include "Polytope.h"
#include "Polygon.h"
#include <3d/Point.h>

#define V_TOL 0.005	/*0.001*/
#define DEBUG_TYPE 0
#define DEBUG_CENTROID 0
#define DEBUG_CLIP 0
#define TODO 1

extern TotalContact totalCon;

Scalar rel_error = 1e-6; // relative error in the computed distance
Scalar abs_error = 1e-10; // absolute error if the distance is almost zero

BBox Convex::bbox(const Transform& t) const {
  Point min(t.getOrigin()[X] + 
	    dot(t.getBasis()[X], support(-t.getBasis()[X])) - abs_error,
	    t.getOrigin()[Y] + 
	    dot(t.getBasis()[Y], support(-t.getBasis()[Y])) - abs_error,
	    t.getOrigin()[Z] + 
	    dot(t.getBasis()[Z], support(-t.getBasis()[Z])) - abs_error); 
  Point max(t.getOrigin()[X] + 
	    dot(t.getBasis()[X], support(t.getBasis()[X])) + abs_error,
	    t.getOrigin()[Y] + 
	    dot(t.getBasis()[Y], support(t.getBasis()[Y])) + abs_error,
	    t.getOrigin()[Z] + 
	    dot(t.getBasis()[Z], support(t.getBasis()[Z])) + abs_error); 
  return BBox(min, max);
}

static Point p[4];    // support points of object A in local coordinates 
static Point q[4];    // support points of object B in local coordinates 
static Vector y[4];   // support points of A - B in world coordinates

static int bits;      // identifies current simplex
static int last;      // identifies last found support point
static int last_bit;  // last_bit = 1<<last
static int all_bits;  // all_bits = bits|last_bit 

static Scalar det[16][4]; // cached sub-determinants

#ifdef STATISTICS
int num_iterations = 0;
int num_irregularities = 0;
#endif

void copyPoint(Point& from, double to[])
{
   to[0] = from[0];
   to[1] = from[1];
   to[2] = from[2];
}

void copyVector(Vector& from, double to[])
{
   to[0] = from[0];
   to[1] = from[1];
   to[2] = from[2];
}

void copy_vector(double from[], double to[])
{
   to[0] = from[0];
   to[1] = from[1];
   to[2] = from[2];
}

double distPointVector(const Point& p, const Point& p1, const Point& p2)
{

   Vector v1 = p2 - p1;
   Vector v2 = p - p1;

   v1.normalize();
   double d = dot(v1,v2);
   double dist = v2.length2() - d*d;

   if (dist <= 0.0)
     return 0.0;

   return sqrt(dist);

}

Vector crossEdges(int e1, const Polytope& p1, int e2, const Polytope& p2,
		  const Transform& b2a, Point& pa)
{
Point intpt;
double junk1, junk2;

   int i1 = e1;
   int i2 = p1.nextVertex(e1);
   Point pt1 = p1[i1];
   Point pt2 = p1[i2];
   Vector v1 = p1[i2] - p1[i1];
   v1.normalize();

   i1 = e2;
   i2 = p2.nextVertex(e2);
   Point pt3 = b2a(p2[i1]);
   Point pt4 = b2a(p2[i2]);
   Vector vec = p2[i2] - p2[i1];
   vec.normalize();
   const Matrix m = b2a.getBasis();
   Vector v2 = m * vec;
   v2.normalize();

   Vector v3 = cross(v1,v2);

   /* find the actual intersection point of the two edges */
   if (p1.intersectLineSegments(pt1, pt2, pt3, pt4, intpt, junk1, junk2, ILS_TOL) == true) {
      /* if the contact point is not the same as the int pt, replace it */   
      if (points_equal(intpt, pa, TOLERANCE) == false) {
	  pa = intpt;
      }
   }
   if (EQUAL_WITHIN_TOLERANCE(v3.length2(),0.0,TOLERANCE))
   {
      /* Tweak v1 a bit, re-normalize, and then
       * cross v1 and v2 again to get v3.
       */
      if (EQUAL_WITHIN_TOLERANCE(v1[0],1.0,TOLERANCE) ||
	  EQUAL_WITHIN_TOLERANCE(v1[0],-1.0,TOLERANCE))
	 v1[1] += 0.1;
      else
	 v1[0] += 0.1;
      v1.normalize();
      v3 = cross(v1,v2);
//printf("vectors parallel\n");
   }
   if (v3.length() != 0.0)
      v3.normalize();

   /* v3 is expressed in the reference frame of p1.
    * If v3 points into p1, then flip its direction.
    * If v3 is less than 90 degrees from v (which
    * points from the contact point to the centroid
    * of p1), then flip v3.
    */

   Vector v = p1.centroid() - pa;
   if (angle(v,v3) < 90.0 * DEG_TO_RAD)
      v3 *= -1.0;

   return v3;

}


Vector aveEdgesAtVertex(int v, const Polytope& p)
{

   int i1 = (v + 1) % p.numVerts();
   int i2 = (v + p.numVerts() - 1) % p.numVerts();

   Vector v1 = p[i1] - p[v];
   v1.normalize();

   Vector v2 = p[i2] - p[v];
   v2.normalize();

   Vector vec = (v1 + v2) * 0.5;
   vec.normalize();

   return vec;

}

bool intersect_polygons(const Polytope* polyA, const Polytope* polyB, 
const Transform& b2a, Point &centroid)
{
int		i, j, index = 0;
int		polyA_num_verts, polyB_num_verts, polyC_num_verts;
int		num_intersections = 0;
int		v1, v2, v3, v4, v, i1, i2, nA, nB;
int		b_vert_found = 0, num_b_used = 0;
double	lenA, lenB, s1, s2;
Point		vert1, vert2, vert3, vert4, vert, pt;
Point		polyC_vertices[100];
bool		found1 = false, found2 = false;
bool		a_vert_used[100], b_vert_used[100];
Transform a2b;
unsigned int polyC_indices[100];

   a2b.invert(b2a);

	for (i = 0; i < 100; i++) a_vert_used[i] = b_vert_used[i] = false;
	polyA_num_verts = (*polyA).numVerts();
	polyB_num_verts = (*polyB).numVerts();

	if (DEBUG_CENTROID) {
		for (i = 0; i < polyA_num_verts; i++) {
			pt = a2b((*polyA)[i]);
			printf("a%d = % f % f % f ( % f % f % f)\n", i, (*polyA)[i][0], (*polyA)[i][1],
				 (*polyA)[i][2], pt[0], pt[1], pt[2]);
		}
		for (i = 0; i < polyB_num_verts; i++) {
			pt = b2a((*polyB)[i]);
			printf("b%d = % f % f % f ( % f % f % f)\n", i, (*polyB)[i][0],
				 (*polyB)[i][1], (*polyB)[i][2], pt[0], pt[1], pt[2]);
		}
	}



/* check which vertices are contained in other polygon */
/*printf("check which vertices are in other polygon\n");
	for (i = 0; i < polyA_num_verts; i++) {
		pt = a2b((*polyA)[i]);
		printf("is v%da in B? ", i);
		if (polyB->contains(pt) == true) printf("yes\n");
		else printf("no\n");
	}
	for (i = 0; i < polyB_num_verts; i++) {
		pt = b2a((*polyB)[i]); 
		printf("is v%db in A?  ", i);
		if (polyA->contains(pt) == true) printf("yes\n");
		else printf("no\n");
	}
//exit(0);
*/
	/* everything done in polyA frame */
	/* check each edge in polyA for intersection with each edge in polyB */
	for (i = 0; i < polyA_num_verts; i++) {
		v1 = i;
		v2 = (*polyA).nextVertex(i);
		vert1 = (*polyA)[v1];
		vert2 = (*polyA)[v2];
		if (DEBUG_CENTROID)	printf("i = %d  %d-%d\n", i, v1, v2);

		for (j = 0; j < polyB_num_verts; j++) {
			found1 = found2 = false;
			v3 = j;
			v4 = (*polyB).nextVertex(j);
			vert3 = b2a((*polyB)[v3]);
			vert4 = b2a((*polyB)[v4]);
			if (DEBUG_CENTROID)	printf("   j = %d  %d-%d ", j, v3, v4);
			/* if the two edges intersect and the intersection is not a vertex
			 * on edgeB (ie int pt != v3 or v4, increase the intersection counter
			 * and store the point in the new array */
			if (polyA->intersectLineSegments(vert1, vert2, vert3, vert4, pt, lenB,
				lenA, ILS_TOL) == true)  {
				/* if the pt is not a vertex on edgeB */
				if ((points_equal(vert3, pt, TOLERANCE) == false) &&
						(points_equal(vert4, pt, TOLERANCE) == false)) {
					if (DEBUG_CENTROID)  
						printf("int pt = % f % f % f ", pt[0], pt[1], pt[2]);
					if (points_equal(vert1, pt, TOLERANCE) == true) {
						if (a_vert_used[v1] == false) { 		
							if (DEBUG_CENTROID) printf("  (v%da)  p%d\n",v1, index);
							a_vert_used[v1] = true;
							polyC_vertices[index++] = pt;
						} else {
							if (DEBUG_CENTROID) printf("  (v%da)  already used\n", v1);
						}
							num_intersections++;
					} else if (points_equal(vert2, pt, TOLERANCE) == true) {
						if (a_vert_used[v2] == false) {
							if (DEBUG_CENTROID) printf("  (v%da)  p%d\n", v2, index);
							a_vert_used[v2] = true;
							polyC_vertices[index++] = pt;
						} else {
							if (DEBUG_CENTROID) printf("  (v%da)  already used\n", v2);
						}
							num_intersections++;
					} else {
						if (DEBUG_CENTROID) printf("  p%d\n", index);
						num_intersections++;
						polyC_vertices[index++] = pt;					
					}
					/* if the same edgeA gets intersected more than once by edges in
					 * B, store the indices of the intersection points in the array 
					 * and store their distances along edgeA
					 */
					if (found1== false) {
						found1 = true;
						s1 = lenA;
						i1 = index - 1;
					} else if (found2 == false) {
						found2 = true;
						s2 = lenA;
						i2 = index - 1;
					}

					/* Check whether or not the endpoint of edgeB (vert4) is
				 	* contained in polyA.  If it is, the endpoint is a new poly
				 	* vertex and is added to the array.  Keep checking vertices in B
				 	* and adding them	to the list if they are contained in A.  
				 	* Repeat until a v4 is not contained in A.
				 	*/
					v = v4;
					while (1) {
						vert = b2a((*polyB)[v]);
						if (DEBUG_CENTROID) printf("\tis v%db (% f % f % f) in A?", v,
							 vert[0], vert[1], vert[2]);
						if (polyA->contains(vert) == true) {
							if (b_vert_used[v] == false) {
								if (DEBUG_CENTROID) printf("  yes  p%d\n", index);
								polyC_vertices[index++] = vert;
								b_vert_used[v] = true;
								num_b_used++;
							} else {
								if (DEBUG_CENTROID) printf("  already there\n");
							}
							v = (*polyB).nextVertex(v);
						} else {
							if (DEBUG_CENTROID)	printf("  no\n");
							break;
						}
						if (v == v4) break;
					}
					
				} else {
					if (DEBUG_CENTROID)	printf("int_pt is vertex %d on B\n", 
						(lenB == 0) ? v3: v4);
					b_vert_found++;
				}
			} else {
				if (DEBUG_CENTROID)	printf("do not intersect\n");
			}
		} /* end for j */
		/* if two intersection points were found on the same edge, check that they
		 * occur in the right order (the first point should be closer to v1: 
		 *	lenA1 < lenA2).  If not, swap them */
		if ((found1 == true) && (found2 == true)) {
			found1 =  found2 = false;
 			if (s1 > s2) {
 				pt = polyC_vertices[i1];
 				polyC_vertices[i1] = polyC_vertices[i2];
 				polyC_vertices[i2] = pt;
 				if (DEBUG_CENTROID) printf("swap p%d and p%d\n", i1, i2);
 			}
			s1 = s2 = 0.0;
		}
		/* Check whether or not the startpoint of edgeA (vert1) is contained 
		 * in polyB.  If it is, the startpoint is a new polyC vertex and is 
		 * added to the array.  Keep checking vertices in A and adding them
		 * to the list if they are contained in B.  Repeat until a v1 is
		 * not contained in B.
		 */
		vert = a2b(vert1);
		v = v1;
		while (1) {
			vert = a2b((*polyA)[v]);
			if (DEBUG_CENTROID)
				printf("is v%da (% f % f % f) in B?", v, vert[0], vert[1], vert[2]);
			if (polyB->contains(vert) == true) {
				if (a_vert_used[v] == false) {
					if (DEBUG_CENTROID) printf("  yes  p%d\n", index);
					polyC_vertices[index++] = b2a(vert);
					a_vert_used[v] = true;
				} else if (DEBUG_CENTROID)	printf("  already there\n");
				v = (*polyA).nextVertex(v);
			} else {
				if (DEBUG_CENTROID)	printf("  no\n");
				break;
			}
			if (v == v1) break;
		}
	} /* end for i */

	if (DEBUG_CENTROID) {
		printf("num intersections = %d\n", num_intersections);
		printf("b verts used = %d\n", num_b_used);
		printf("b verts found = %d\n", b_vert_found);
	}
	if (DEBUG_CENTROID)
		for (i = 0; i < index; i++)
			printf("p%d = % f % f % f\n", i, polyC_vertices[i][0],
			 polyC_vertices[i][1], polyC_vertices[i][2]);

	/* if no intersections were found, one of the polygons is entirely within
	 * the other.  The new polygon contains all the vertices of the inner
	 * polygon. */
	if (num_intersections == 0)  {
		if (DEBUG_CENTROID) printf("NO INTERSECTIONS recalculate points\n");
		index = 0;
		for (i = 0; i < polyA_num_verts; i++) {
			pt = a2b((*polyA)[i]);
			if (polyB->contains(pt) == true) {
				polyC_vertices[index++] = b2a(pt);
			}
		}
		nA = index;
		index = 0;
		for (i = 0; i < polyB_num_verts; i++) {
			pt = b2a((*polyB)[i]); 
			if (polyA->contains(pt) == true) {
				polyC_vertices[index++] = pt;
			}
		}
		nB = index;
//		printf("nA = %d, nB = %d\n", nA, nB);
		if (nA > nB) {
			index = 0;
			for (i = 0; i < polyA_num_verts; i++) {
				pt = a2b((*polyA)[i]);
				if (polyB->contains(pt) == true) 
					polyC_vertices[index++] = b2a(pt);
			}
		}
	}
	
	/* if an odd number of intersections was found, some of the vertices
	 * were not included, go through both polygon, find all contained vertices
	 * that were not already included in the list, and include them */
	if ((num_intersections % 2) == 1) {
		if (DEBUG_CENTROID) printf("ODD NUMBER OF INTERSECTIONS\n");
		for (i = 0; i < polyA_num_verts; i++) {
			pt = a2b((*polyA)[i]);
			if ((polyB->contains(pt) == true) && (a_vert_used[i] == false)) {
				polyC_vertices[index++] = b2a(pt);
			//	printf("add p%da\n", i);
			}
		}
		for (i = 0; i < polyB_num_verts; i++) {
			pt = b2a((*polyB)[i]); 
			if ((polyA->contains(pt) == true) && (b_vert_used[i] == false)) {
				polyC_vertices[index++] = pt;
			//	printf("add p%db\n", i);
			}
		}		
	}
	if (index == 0) {printf("No intersections found\n"); return(false);}
	/* create a new polygon polyC from all the points found, and find and return
	 * its centroid */
	VertexBase vb(polyC_vertices);
	polyC_num_verts = index;
	for (i = 0; i < polyC_num_verts; i++)	polyC_indices[i] = i;
	
	Polygon polyC(vb, polyC_num_verts, polyC_indices);
	centroid = polyC.centroid();

	if (DEBUG_CENTROID)	{
		for (i = 0; i < polyC.numVerts(); i++)
			printf("p%d = % f % f % f\n", i, polyC[i][0], polyC[i][1],polyC[i][2]);
		printf("centroid = %f %f %f\n", centroid[0], centroid[1], centroid[2]);
	}

	if (polyA->contains(centroid) == false) {
		printf("centroid not in A\n"); 
//		for (i = 0; i < polyC.numVerts(); i++)
//			printf("p%d = % f % f % f\n", i, polyC[i][0], polyC[i][1],polyC[i][2]);
printf("centroid = %f %f %f\n", centroid[0], centroid[1], centroid[2]);
exit(0);	
	return(false);
	}
	centroid = a2b(centroid);
	if (polyB->contains(centroid) == false) {
		printf("centroid not in B\n");
//		for (i = 0; i < polyC.numVerts(); i++)
//			printf("p%d = % f % f % f\n", i, polyC[i][0], polyC[i][1],polyC[i][2]);
	centroid = b2a(centroid);

printf("centroid = %f %f %f\n", centroid[0], centroid[1], centroid[2]);

exit(0);
		return(false);

	}
	centroid = b2a(centroid);
//		printf("centroid = %f %f %f\n", centroid[0], centroid[1], centroid[2]);
	return(true);
}


bool compute_contact_types(const Convex& a, Point& pa,
			     const Convex& b, Point& pb, const Transform& b2a,
			     ContactReport& report)
{

   int i,  v1, v2, vertexA, vertexB, edgeA, edgeB;
   double d, minVertDistA, minVertDistB, minEdgeDistA, minEdgeDistB;
   int minVertDistAIndex, minVertDistBIndex, minEdgeDistAIndex, minEdgeDistBIndex;
   const Polytope* polyA = dynamic_cast<const Polytope*>(&a);
   const Polytope* polyB = dynamic_cast<const Polytope*>(&b);
   ContactCases conCase;
   Vector vert1, vert2;
   Point amidpt, bmidpt, p1, p2, p3, p4, a_in_B, b_in_A;
   bool vAe1pB, vAe2pB, vBe1pA, vBe2pA, eApB, eBpA;
   Transform a2b;
   a2b.invert(b2a);

   if (!polyA || !polyB)
   {
printf("!polyA || !polyB\n");
      report.type1 = FACE;
      report.type2 = EDGE;
      copy_vector(report.normal1,report.contact_normal);
      report.contact_body = 1;
      return true;
   }

   /* STEP 1
    * If the polygons' normals are 180 degrees apart, then
    * treat it as a FACE-FACE intersection, regardless of
    * which feature of A hits B.
    */
   Vector vec1(report.normal1);
   Vector v(report.normal2);
   const Matrix m = b2a.getBasis();
   Vector vec2 = m * v;

	if (DEBUG_TYPE) {
		printf("\npa = %f %f %f\n", pa[0], pa[1], pa[2]);
		printf("pb = %f %f %f\n", pb[0], pb[1], pb[2]);
		printf("na = %f %f %f\n", vec1[0], vec1[1], vec1[2]);
		printf("nb = %f %f %f\n", vec2[0], vec2[1], vec2[2]);
		printf("v = %f %f %f\n", v[0], v[1], v[2]);
	}

   if (DEBUG_TYPE)
      printf("STEP 1:\n");
   if (angle(vec1,vec2) > 179.90 * DEG_TO_RAD)
   {
      if (DEBUG_TYPE)	 
	printf("F-F: normals 180 deg apart (%f)\n", angle(vec1, vec2) * RAD_TO_DEG);
      report.type1 = FACE;
      report.type2 = FACE;
//printf("na = %f %f %f\n", vec1[0], vec1[1], vec1[2]);
//printf("nb = %f %f %f\n", vec2[0], vec2[1], vec2[2]);
//		printf("\npa = %f %f %f\n", pa[0], pa[1], pa[2]);
//		printf("pb = %f %f %f\n", pb[0], pb[1], pb[2]);

      /* Find the intersection of the two faces, and set the contact
       * point to be the centroid of this intersection ( in polyA frame).
       */
	Point pt;
	if (intersect_polygons(polyA, polyB, b2a, pt) == false) {
		if (DEBUG_TYPE) printf("No centroid found\n");
		return false;
	} else {
		for (i = 0; i < 3; i++) {
			report.p1[i] = pt[i];
			report.p2[i] = (a2b(pt))[i];
		}
		report.contact_body = 2;
		copy_vector(report.normal2, report.contact_normal);
		if (DEBUG_TYPE) {
		 printf("p1 = %f %f %f\n", report.p1[0], report.p1[1], report.p1[2]);
		printf("p2 = %f %f %f\n", report.p2[0], report.p2[1], report.p2[2]);
		}

		return true;
	}
   }
   if (DEBUG_TYPE)
      printf("angle between nA and nB = %f - not F-F\n", angle(vec1, vec2)*RAD_TO_DEG);

   /* STEP 2
    * Calculate which feature (vertex, edge) the contact point
    * is closest to.
    * vertexA = index of vertex that pa is closest to, -1 if closest to edge
    * edgeA = index of edge that pa is closest to, -1 if closest to vertex
    * vertexB = index of vertex that pb is closest to, -1 if closest to edge
    * edgeB = index of edge that pb is closest to, -1 if closest to vertex
    */

   vertexA = -1;
   edgeA = -1;
   for (i=0, minVertDistA=99999.9; i<polyA->numVerts(); i++)
   {
	   d = ::distance(pa,(*polyA)[i]);
      if (EQUAL_WITHIN_TOLERANCE(d,0.0,TOLERANCE))
      {
	 vertexA = i;
	 break;
      }
      else if (d < minVertDistA)
      {
	 minVertDistA = d;
	 minVertDistAIndex = i;
      }
   }
   if (vertexA == -1)
   {
      for (i=0, minEdgeDistA=99999.9; i<polyA->numVerts(); i++)
      {
	 v1 = i;
	 v2 = polyA->nextVertex(i);
	 d = distPointVector(pa,(*polyA)[v1],(*polyA)[v2]);
	 if (EQUAL_WITHIN_TOLERANCE(d,0.0,TOLERANCE))
	 {
	    edgeA = i;
	    minEdgeDistA = d;
	    break;
	 }
	 else if (d < minEdgeDistA)
	 {
	    minEdgeDistA = d;
	    minEdgeDistAIndex = i;
	 }
      }
   }
   vertexB = -1;
   edgeB = -1;
   for (i=0, minVertDistB=99999.9; i<polyB->numVerts(); i++)
   {
	   d = ::distance(pb,(*polyB)[i]);
      if (EQUAL_WITHIN_TOLERANCE(d,0.0,TOLERANCE))
      {
	 vertexB = i;
	 break;
      }
      else if (d < minVertDistB)
      {
	 minVertDistB = d;
	 minVertDistBIndex = i;
      }
   }
   if (vertexB == -1)
   {
      for (i=0, minEdgeDistB=99999.9; i<polyB->numVerts(); i++)
      {
	 v1 = i;
	 v2 = polyB->nextVertex(i);
	 d = distPointVector(pb,(*polyB)[v1],(*polyB)[v2]);
	 if (EQUAL_WITHIN_TOLERANCE(d,0.0,TOLERANCE))
	 {
	    edgeB = i;
	    minEdgeDistB = d;
	    break;
	 }
	 else if (d < minEdgeDistB)
	 {
	    minEdgeDistB = d;
	    minEdgeDistBIndex = i;
	 }
      }
   }

   if (DEBUG_TYPE)
   {
      printf("STEP 2:\n");
      printf("vertexA = %d, edgeA = %d, vertexB = %d, edgeB = %d\n",
	     vertexA, edgeA, vertexB, edgeB);
      printf("minVertDistA = %lf, minEdgeDistA = %lf\n", minVertDistA, minEdgeDistA);
      printf("minVertDistB = %lf, minEdgeDistB = %lf\n", minVertDistB, minEdgeDistB);
   }

   /* STEP 3
    * If the contact still shows up as F-F, change it to
    * one of the other cases. Since you already checked for
    * "true" F-F (normals 180 degrees apart), then this case
    * should not be F-F. Find the smallest of the four values,
    * and use it to force this case into one of the other 
    */
   if (DEBUG_TYPE) printf("STEP 3:\n");
   if (vertexA == -1 && edgeA == -1 && vertexB == -1 && edgeB == -1)
   {
      if (minVertDistA < minVertDistB)
      {
	 if (minEdgeDistA < minEdgeDistB)
	 {
	    if (minVertDistA < minEdgeDistA)
	       vertexA = minVertDistAIndex;
	    else
	       edgeA = minEdgeDistAIndex;
	 }
	 else
	 {
	    if (minVertDistA < minEdgeDistB)
	       vertexA = minVertDistAIndex;
	    else
	       edgeB = minEdgeDistBIndex;
	 }
      }
      else
      {
	 if (minEdgeDistA < minEdgeDistB)
	 {
	    if (minVertDistB < minEdgeDistA)
	       vertexB = minVertDistBIndex;
	    else
	       edgeA = minEdgeDistAIndex;
	 }
	 else
	 {
	    if (minVertDistB < minEdgeDistB)
	       vertexB = minVertDistBIndex;
	    else
	       edgeB = minEdgeDistBIndex;
	 }
      }
      if (DEBUG_TYPE)
      printf("vertexA = %d, edgeA = %d, vertexB = %d, edgeB = %d\n",
	     vertexA, edgeA, vertexB, edgeB);
   }


   /* STEP 4
    * Now calculate the following properties:
    * vAe1pB = true if edge going into vA lies on polyB
    * vAe2pB = true if edge coming out of vA lies on polyB
    * vBe1pA = true if edge going into vB lies on polyA
    * vBe2pA = true if edge coming out of vB lies on polyA
    * eApB = true if eA lies on polyB
    * eBpA = true if eB lies on polyA
    */
   vAe1pB = vAe2pB = vBe1pA = vBe2pA = eApB = eBpA = false;

   if (vertexA != -1)
   {
      p1 = a2b((*polyA)[vertexA]);
      p2 = a2b((*polyA)[polyA->nextVertex(vertexA)]);
      p3 = a2b((*polyA)[polyA->previousVertex(vertexA)]);
      Vector v1 = p1 - p2;
      v1.normalize();
      Vector v2 = p1 - p3;
      v2.normalize();
      Vector v3 = polyB->getNormal();
      if (EQUAL_WITHIN_TOLERANCE(dot(v1,v3),0.0,TOLERANCE))
	 vAe2pB = true;
      if (EQUAL_WITHIN_TOLERANCE(dot(v2,v3),0.0,TOLERANCE))
	 vAe1pB = true;
   }

   if (edgeA != -1)
   {
      p1 = a2b((*polyA)[edgeA]);
      p2 = a2b((*polyA)[polyA->nextVertex(edgeA)]);
      Vector v1 = p1 - p2;
      v1.normalize();
      Vector v2 = polyB->getNormal();
      if (EQUAL_WITHIN_TOLERANCE(dot(v1,v2),0.0,TOLERANCE))
	 eApB = true;
   }

   if (vertexB != -1)
   {
      p1 = b2a((*polyB)[vertexB]);
      p2 = b2a((*polyB)[polyB->nextVertex(vertexB)]);
      p3 = b2a((*polyB)[polyB->previousVertex(vertexB)]);
      Vector v1 = p1 - p2;
      v1.normalize();
      Vector v2 = p1 - p3;
      v2.normalize();
      Vector v3 = polyA->getNormal();
      if (EQUAL_WITHIN_TOLERANCE(dot(v1,v3),0.0,TOLERANCE))
	 vBe2pA = true;
      if (EQUAL_WITHIN_TOLERANCE(dot(v2,v3),0.0,TOLERANCE))
	 vBe1pA = true;
   }

   if (edgeB != -1)
   {
      p1 = b2a((*polyB)[edgeB]);
      p2 = b2a((*polyB)[polyB->nextVertex(edgeB)]);
      Vector v1 = p1 - p2;
      v1.normalize();
      Vector v2 = polyA->getNormal();
      if (EQUAL_WITHIN_TOLERANCE(dot(v1,v2),0.0,TOLERANCE))
	 eBpA = true;
   }

   if (DEBUG_TYPE)
   {
      printf("STEP 4:\n");
      printf("vAe1pB = %d, vAe2pB = %d\n", vAe1pB, vAe2pB);
      printf("vBe1pA = %d, vBe2pA = %d\n", vBe1pA, vBe2pA);
      printf("eApB = %d, eBpA = %d\n", eApB, eBpA);
   }

   /* STEP 5
    * Now split the 9 possible cases (V-V, V-E, V-F, E-V, E-E, E-F,
    * F-V, F-E, F-F) into the six acceptable cases (V-F, E-E, E-F,
    * F-V, F-E, F-F).
    */
   if (DEBUG_TYPE)  printf("STEP 5:\n");
   if (vertexA != -1 && vertexB != -1)
   {
      if (DEBUG_TYPE) printf("vA != -1 && vB != -1\n");
      if (vAe1pB == true)
      {
	 conCase = EDGE_FACE;
	 edgeA = polyA->previousVertex(vertexA);
      }
      else if (vAe2pB == true)
      {
	 conCase = EDGE_FACE;
	 edgeA = vertexA;
      }
      else if (vBe1pA == true)
      {
	 conCase = FACE_EDGE;
	 edgeB = polyB->previousVertex(vertexB);
      }
      else if (vBe2pA == true)
      {
	 conCase = FACE_EDGE;
	 edgeB = vertexB;
      }
      else
      {
	 /* Decide whether this is F-V or V-F.
	  * If all vertices of one polygon are on the same
	  * side of the other, the other is the face.
	  */
	 double dist;
	 int count, nv = polyB->numVerts();
	 Vector v1, v2, v3;
	 v2 = polyA->getNormal();
	 v3 = (*polyA)[0];
	 d = dot(v2,v3);
	 for (i=0, count=0; i<polyB->numVerts(); i++)
	 {
	    v1 = b2a((*polyB)[i]);
	    dist = dot(v1,v2) - d;
	    if (dist < -V_TOL)
	       count--;
	    else if (dist > V_TOL)
	       count++;
	    else
	       nv--;
	 }
	 /* nv is the number of vertices of B that are not on the
	  * plane of polygon A. If ABS(count) equals nv, then all
	  * of the other vertices of B are all on one side of A.
	  */
	 if (ABS(count) == nv)
	    conCase = FACE_VERTEX;
	 else
	    conCase = VERTEX_FACE;
      }
   }
   else if (vertexA != -1 && edgeB != -1)
   {
      if (DEBUG_TYPE) printf("vA != -1 && eB != -1\n");
      if (vAe1pB == true)
      {
	 conCase = EDGE_FACE;
	 edgeA = polyA->previousVertex(vertexA);
      }
      else if (vAe2pB == true)
      {
	 conCase = EDGE_FACE;
	 edgeA = vertexA;
      }
      else if (eBpA == true)
      {
	 conCase = FACE_EDGE;
      }
      else
      {
	 conCase = VERTEX_FACE;
      }
   }
   else if (vertexA != -1 && edgeB == -1)
   {
      if (DEBUG_TYPE) printf("vA != -1 && eB != -1\n");
      if (vAe1pB == true)
      {
	 conCase = EDGE_FACE;
	 edgeA = polyA->previousVertex(vertexA);
      }
      else if (vAe2pB == true)
      {
	 conCase = EDGE_FACE;
	 edgeA = vertexA;
      }
      else
      {
	 conCase = VERTEX_FACE;
      }
   }
   else if (edgeA != -1 && vertexB != -1)
   {
       if (DEBUG_TYPE) printf("eA != -1 && vB != -1\n");
     if (vBe1pA == true)
      {
	 conCase = FACE_EDGE;
	 edgeB = polyB->previousVertex(vertexB);
      }
      else if (vBe2pA == true)
      {
	 conCase = FACE_EDGE;
	 edgeB = vertexB;
      }
      else if (eApB == true)
      {
	 conCase = EDGE_FACE;
      }
      else
      {
	 conCase = FACE_VERTEX;
      }
   }
   else if (edgeA != -1 && edgeB != -1)
   {
      if (DEBUG_TYPE) printf("eA != -1 && eB != -1\n");
      if (eApB == true)
	 conCase = EDGE_FACE;
      else if (eBpA == true)
	 conCase = FACE_EDGE;
      else
	 conCase = EDGE_EDGE;
   }
   else if (edgeA != -1 && edgeB == -1)
   {
      if (DEBUG_TYPE) printf("eA != -1 && eB == -1\n");
	conCase = EDGE_FACE;
   }
   else if (edgeA == -1 && vertexB != -1)
   {
      if (DEBUG_TYPE) printf("eA == -1 && vB != -1\n");
      if (vBe1pA == true)
      {
	 conCase = FACE_EDGE;
	 edgeB = polyB->previousVertex(vertexB);
      }
      else if (vBe2pA == true)
      {
	 conCase = FACE_EDGE;
	 edgeB = vertexB;
      }
      else
      {
	 conCase = FACE_VERTEX;
      }
   }
   else if (edgeA == -1 && edgeB != -1)
   {
      if (DEBUG_TYPE) printf("eA == -1 && eB != -1\n");
     conCase = FACE_EDGE;
   }
   else if (edgeA == -1 && edgeB == -1)
   {
      if (DEBUG_TYPE) printf("eA == -1 && eB == -1\n");
      printf("F-F, should not be here!\n");
   }

   if (DEBUG_TYPE)
   {
      printf("conCase = %d  (", conCase);
      switch(conCase) {
         case(VERTEX_FACE): printf("VERTEX_FACE)\n"); break;
	 case(FACE_VERTEX): printf("FACE_VERTEX)\n"); break;
         case(EDGE_EDGE): printf("EDGE_EDGE)\n"); break;
	 case(FACE_EDGE): printf("FACE_EDGE)\n"); break;
	 case(EDGE_FACE): printf("EDGE_FACE)\n"); break;
	 case(FACE_FACE): printf("FACE_FACE)\n"); break;
      }
      printf("vertexA = %d, edgeA = %d, vertexB = %d, edgeB = %d\n",
	     vertexA, edgeA, vertexB, edgeB);
   }

   /* STEP 6
    * Now fill in the contact report structure.
    */
   if (DEBUG_TYPE) printf("STEP 6:\n");
   switch (conCase)
   {
      case VERTEX_FACE:
         report.type1 = VERTEX;
	 report.type2 = FACE;
	 report.contact_body = 2;
	 copy_vector(report.normal2,report.contact_normal);
         if (DEBUG_TYPE)	printf("V-F\n");
         break;

      case EDGE_EDGE:
         if (DEBUG_TYPE)	printf("E-E\n");
	 report.type1 = EDGE;
	 report.type2 = EDGE;
	 report.contact_body = 2;
	 v = crossEdges(edgeB,*polyB,edgeA,*polyA,a2b, pb);
p2 = pb;
p1 = b2a(pb);

copyPoint(p2, report.p2);
copyPoint(p1, report.p1);
	 if (EQUAL_WITHIN_TOLERANCE(v.length(), 0.0, TOLERANCE))
	    copy_vector(report.normal2,report.contact_normal);
	 else
	    copyVector(v,report.contact_normal);
	 break;
      case EDGE_FACE:
         if (DEBUG_TYPE)	printf("E-F\n");
	 p1 = a2b((*polyA)[edgeA]);
	 p2 = a2b((*polyA)[polyA->nextVertex(edgeA)]);
	//	report.type1 = EDGE;
	// 	report.type2 = FACE;
	// 	report.contact_body = 2;
	// 	copy_vector(report.normal2,report.contact_normal);
	 
	 if (eApB == true) {
		report.type1 = EDGE;
	 	report.type2 = FACE;
	 	report.contact_body = 2;
	 	copy_vector(report.normal2,report.contact_normal);
	             /* clip the edge against the face */
	    polyB->clipEdge(p1,p2,p3,p4);
	    bmidpt = (p3 + p4) * 0.5;
	    copyPoint(bmidpt,report.p2);
	    amidpt = b2a(bmidpt);
	    copyPoint(amidpt,report.p1);
            if (DEBUG_CLIP) {
		   printf("clip p1 and p2 on face\n");	
		   printf("\tp1 = %f %f %f\n", p1[0], p1[1], p1[2]);
		   printf("\tp2 = %f %f %f\n", p2[0], p2[1], p2[2]);
		   printf("get new points: \n");
		   printf("\tp3 = %f %f %f\n", p3[0], p3[1], p3[2]);
		   printf("\tp4 = %f %f %f\n", p4[0], p4[1], p4[2]);
		   printf("\tp = %f %f %f\n", bmidpt[0], bmidpt[1], bmidpt[2]);
            }
	    if (DEBUG_TYPE) {
               printf("Clip edgeA along faceB\n");
               printf("pa = %f %f %f\n", amidpt[0], amidpt[1], amidpt[2]);
               printf("pb = %f %f %f\n", bmidpt[0], bmidpt[1], bmidpt[2]);
            } 
	 }
	else
	{
		report.type1 = FACE;
	 	report.type2 = EDGE;
	 	report.contact_body = 1;
	 	copy_vector(report.normal1,report.contact_normal);
	}
	 break;
      case FACE_VERTEX:
         if (DEBUG_TYPE)	printf("F-V\n");
	a_in_B = a2b(pa);
	b_in_A = b2a(pb);
//printf("pa = %f %f %f\n", pa[0], pa[1], pa[2]);
//printf("in B = %f %f %f\n", a_in_B[0], a_in_B[1], a_in_B[2]);
//printf("pb = %f %f %f\n", pb[0], pb[1], pb[2]);
//printf("in A = %f %f %f\n", b_in_A[0], b_in_A[1], b_in_A[2]);
if ((polyA->contains(b_in_A) == false) && (polyB->contains(a_in_B) == true)) {
	copyPoint(a_in_B, report.p2);
	if (DEBUG_TYPE) printf("pB not in A, transform pB to pA\n");
} else if ((polyB->contains(a_in_B) == false) && (polyA->contains(b_in_A) == true)) {
	copyPoint(b_in_A, report.p1);
	if (DEBUG_TYPE) printf("pA not in B, transform pA to pB\n");
} else if ((polyA->contains(b_in_A) == false) && (polyB->contains(a_in_B) == false)) {
	if (DEBUG_TYPE) printf("Point not in A or B\n");
return(false);	
//exit(0);
}
if (DEBUG_TYPE) {
printf("p1 = %f %f %f\n", report.p1[0], report.p1[1], report.p1[2]);
printf("p2 = %f %f %f\n", report.p2[0], report.p2[1], report.p2[2]);
}
	 report.type1 = FACE;
	 report.type2 = VERTEX;
	 report.contact_body = 1;
	 copy_vector(report.normal1,report.contact_normal);
	 break;
      case FACE_EDGE:
         if (DEBUG_TYPE)	printf("F-E\n");
	 p1 = b2a((*polyB)[edgeB]);
	 p2 = b2a((*polyB)[polyB->nextVertex(edgeB)]);
	 report.type1 = FACE;
	 report.type2 = EDGE;
	 report.contact_body = 1;
	 copy_vector(report.normal1,report.contact_normal);
	 if (eBpA == true)	{
	 /* clip the edge against the face */
	 polyA->clipEdge(p1,p2,p3,p4);
//	printf("p3 = %f %f %f\n", p3[0], p3[1], p3[2]);
//	printf("p4 = %f %f %f\n", p4[0], p4[1], p4[2]);
	 amidpt = (p3 + p4) * 0.5;
	 copyPoint(amidpt,report.p1);
	 bmidpt = a2b(amidpt);
	 copyPoint(bmidpt,report.p2);
//	printf("p1 = %f %f %f\n", amidpt[0], amidpt[1], amidpt[2]);
//	printf("p2 = %f %f %f\n", bmidpt[0], bmidpt[1], bmidpt[2]);
//exit(0);
	}
	 break;
      case FACE_FACE:
if (DEBUG_TYPE)	printf("F-F\n");
	 report.type1 = FACE;
	 report.type2 = FACE;
	 report.contact_body = 2;
	 copy_vector(report.normal2,report.contact_normal);
	 break;
   }
//p1 = report.p1;
//p2 = report.p2;
//if (polyA->contains(p1) == false) {
//	printf("p1 = %f %f %f\n", p1[0], p1[1], p1[2]);
//	printf("p1 not in A\n"); exit(0);}
//if (polyB->contains(p2) == false) {printf("p2 not in B\n"); exit(0);}

return true;
}


void compute_det() {
  static Scalar dp[4][4];

  for (int i = 0, bit = 1; i < 4; ++i, bit <<=1) 
    if (bits & bit) dp[i][last] = dp[last][i] = dot(y[i], y[last]);
  dp[last][last] = dot(y[last], y[last]);

  det[last_bit][last] = 1;
  for (int j = 0, sj = 1; j < 4; ++j, sj <<= 1) {
    if (bits & sj) {
      int s2 = sj|last_bit;
      det[s2][j] = dp[last][last] - dp[last][j]; 
      det[s2][last] = dp[j][j] - dp[j][last];
      for (int k = 0, sk = 1; k < j; ++k, sk <<= 1) {
	if (bits & sk) {
	  int s3 = sk|s2;
	  det[s3][k] = det[s2][j] * (dp[j][j] - dp[j][k]) + 
	               det[s2][last] * (dp[last][j] - dp[last][k]);
	  det[s3][j] = det[sk|last_bit][k] * (dp[k][k] - dp[k][j]) + 
	               det[sk|last_bit][last] * (dp[last][k] - dp[last][j]);
	  det[s3][last] = det[sk|sj][k] * (dp[k][k] - dp[k][last]) + 
	                  det[sk|sj][j] * (dp[j][k] - dp[j][last]);
	}
      }
    }
  }
  if (all_bits == 15) {
    det[15][0] = det[14][1] * (dp[1][1] - dp[1][0]) + 
                 det[14][2] * (dp[2][1] - dp[2][0]) + 
                 det[14][3] * (dp[3][1] - dp[3][0]);
    det[15][1] = det[13][0] * (dp[0][0] - dp[0][1]) + 
                 det[13][2] * (dp[2][0] - dp[2][1]) + 
                 det[13][3] * (dp[3][0] - dp[3][1]);
    det[15][2] = det[11][0] * (dp[0][0] - dp[0][2]) + 
                 det[11][1] * (dp[1][0] - dp[1][2]) +  
                 det[11][3] * (dp[3][0] - dp[3][2]);
    det[15][3] = det[7][0] * (dp[0][0] - dp[0][3]) + 
                 det[7][1] * (dp[1][0] - dp[1][3]) + 
                 det[7][2] * (dp[2][0] - dp[2][3]);
  }
}

inline bool valid(int s) {  
  for (int i = 0, bit = 1; i < 4; ++i, bit <<= 1) {
    if (all_bits & bit) {
      if (s & bit) { if (det[s][i] <= 0) return false; }
      else if (det[s|bit][i] > 0) return false;
    }
  }
  return true;
}

inline void compute_vector(int bits, Vector& v) {
  Scalar sum = 0;
  v.setValue(0, 0, 0);
  for (int i = 0, bit = 1; i < 4; ++i, bit <<= 1) {
    if (bits & bit) {
      sum += det[bits][i];
      v += y[i] * det[bits][i];
    }
  }
  v *= 1 / sum;
}

inline void compute_points(int bits, Point& p1, Point& p2) {
  Scalar sum = 0;
  p1.setValue(0, 0, 0);
  p2.setValue(0, 0, 0);
  for (int i = 0, bit = 1; i < 4; ++i, bit <<= 1) {
    if (bits & bit) {
      sum += det[bits][i];
      p1 += p[i] * det[bits][i];
      p2 += q[i] * det[bits][i];
    }
  }
  Scalar s = 1 / sum;
  p1 *= s;
  p2 *= s;
}

#ifdef USE_BACKUP_PROCEDURE

inline bool proper(int s) {  
  for (int i = 0, bit = 1; i < 4; ++i, bit <<= 1)
    if ((s & bit) && det[s][i] <= 0) return false; 
  return true;
}

#endif

inline bool closest(Vector& v) {
  compute_det();
  for (int s = bits; s; --s) {
    if ((s & bits) == s) {
      if (valid(s|last_bit)) {
	bits = s|last_bit;
 	compute_vector(bits, v);
	return true;
      }
    }
  }
  if (valid(last_bit)) {
    bits = last_bit;
    v = y[last];
    return true;
  }
  // Original GJK calls the backup procedure at this point.

#ifdef USE_BACKUP_PROCEDURE

  Scalar min_dist2 = INFINITY;
  for (int s = all_bits; s; --s) {
    if ((s & all_bits) == s) {
      if (proper(s)) {
	Vector u;
 	compute_vector(s, u);
	Scalar dist2 = u.length2();
	if (dist2 < min_dist2) {
	  min_dist2 = dist2;
	  bits = s;
	  v = u;
	}
      }
    }
  }

#endif 

  return false;
}

// The next function is used for detecting degenerate cases that cause 
// termination problems due to rounding errors.  
   
inline bool degenerate(const Vector& w) {
  for (int i = 0, bit = 1; i < 4; ++i, bit <<= 1) 
    if ((all_bits & bit) && y[i] == w)  return true;
  return false;
}

bool intersect(const Convex& a, const Convex& b,
	       const Transform& a2w, const Transform& b2w,
	       Vector& v) {
  Vector w;

  bits = 0;
  all_bits = 0;

#ifdef STATISTICS
  num_iterations = 0;
#endif
//printf("intersect1\n");
  do {
    last = 0;
    last_bit = 1;
    while (bits & last_bit) { ++last; last_bit <<= 1; }
    w = a2w(a.support((-v) * a2w.getBasis())) - 
      b2w(b.support(v * b2w.getBasis())); 
    if (dot(v, w) > 0) return false;
    if (degenerate(w)) {
#ifdef STATISTICS
      ++num_irregularities;
#endif
      return false;
    }
    y[last] = w;
    all_bits = bits|last_bit;
#ifdef STATISTICS
    ++num_iterations;
#endif
    if (!closest(v)) {
#ifdef STATISTICS
      ++num_irregularities;
#endif
      return false;
    }
  } 
  while (bits < 15 && !approxZero(v)); 
  return true;
}

bool intersect(const Convex& a, const Convex& b, const Transform& b2a, 
	       Vector& v) {
  Vector w;

  bits = 0;
  all_bits = 0;

#ifdef STATISTICS
  num_iterations = 0;
#endif
//printf("intersect2\n");
  do {
    last = 0;
    last_bit = 1;
    while (bits & last_bit) { ++last; last_bit <<= 1; }
    w = a.support(-v) - b2a(b.support(v * b2a.getBasis()));
    if (dot(v, w) > 0) return false;
    if (degenerate(w)) {
#ifdef STATISTICS
      ++num_irregularities;
#endif
      return false;
    }
    y[last] = w;
    all_bits = bits|last_bit;
#ifdef STATISTICS
    ++num_iterations;
#endif
    if (!closest(v)) {
#ifdef STATISTICS
      ++num_irregularities;
#endif
      return false;
    }
  } 
  while (bits < 15 && !approxZero(v)); 
  return true;
}





bool common_point(const Convex& a, const Convex& b,
		  const Transform& a2w, const Transform& b2w,
		  Vector& v, Point& pa, Point& pb) {
  Vector w;

  bits = 0;
  all_bits = 0;
//printf("common_point1 ");
#ifdef STATISTICS
  num_iterations = 0;
#endif

  do {
    last = 0;
    last_bit = 1;
    while (bits & last_bit) { ++last; last_bit <<= 1; }
    p[last] = a.support((-v) * a2w.getBasis());
    q[last] = b.support(v * b2w.getBasis());
    w = a2w(p[last]) - b2w(q[last]);
    if (dot(v, w) > 0)
    {
//       printf("dot v w > 0\n");
       return false;
    }
    if (degenerate(w))
    {
#ifdef STATISTICS
      ++num_irregularities;
#endif
//      printf("degenerate w\n");
      return false;
    }
    y[last] = w;
    all_bits = bits|last_bit;
#ifdef STATISTICS
    ++num_iterations;
#endif
    if (!closest(v))
    {
#ifdef STATISTICS
      ++num_irregularities;
#endif
//      printf("not closest(v)\n");
      return false;
    }
  }
  while (bits < 15 && !approxZero(v) ) ;
  compute_points(bits, pa, pb);

  ContactReport cReport;
  cReport.p1[0] = pa[0];
  cReport.p1[1] = pa[1];
  cReport.p1[2] = pa[2];
  cReport.p2[0] = pb[0];
  cReport.p2[1] = pb[1];
  cReport.p2[2] = pb[2];
  const Polytope* p = dynamic_cast<const Polytope*>(&a);
  if (p)
     p->getNormal(cReport.normal1);
  p = dynamic_cast<const Polytope*>(&b);
  if (p)
     p->getNormal(cReport.normal2);
  Transform b2a, w2a;
  w2a.invert(a2w);
  b2a.mult(b2w,w2a);
  if (compute_contact_types(a,pa,b,pb,b2a,cReport) == false) return false;

  totalCon.addContact(cReport);

//  printf("contact!\n");
  return true;
}

bool common_point(const Convex& a, const Convex& b, const Transform& b2a,
		  Vector& v, Point& pa, Point& pb) {
  Vector w;

  bits = 0;
  all_bits = 0;

//printf("common_point2 ");
#ifdef STATISTICS
  num_iterations = 0;
#endif
  do {
    last = 0;
    last_bit = 1;
    while (bits & last_bit) { ++last; last_bit <<= 1; }
    p[last] = a.support(-v);
    q[last] = b.support(v * b2a.getBasis());
    w = p[last] - b2a(q[last]);
//       printf("v = %f %f %f\n", v[0], v[1], v[2]);
//	printf("w = %f %f %f\n", w[0], w[1], w[2]);
    if (dot(v, w) > 0)
    {
//	printf("dot v w > 0\n");
       return false;
    }
    if (degenerate(w))
    {
#ifdef STATISTICS
      ++num_irregularities;
#endif
 //     printf("degenerate w\n");
      return false;
    }
    y[last] = w;
    all_bits = bits|last_bit;
#ifdef STATISTICS
    ++num_iterations;
#endif
    if (!closest(v))
    {
#ifdef STATISTICS
      ++num_irregularities;
#endif
 //     printf("not closest(v)\n");
      return false;
    }
  }
  while (bits < 15 && !approxZero(v) );   
  compute_points(bits, pa, pb);
//printf("pa = %f %f %f\n", pa[0], pa[1], pa[2]);
//printf("pb = %f %f %f\n", pb[0], pb[1], pb[2]);

  ContactReport cReport;
  cReport.p1[0] = pa[0];
  cReport.p1[1] = pa[1];
  cReport.p1[2] = pa[2];
  cReport.p2[0] = pb[0];
  cReport.p2[1] = pb[1];
  cReport.p2[2] = pb[2];
  const Polytope* p = dynamic_cast<const Polytope*>(&a);
  if (p)
     p->getNormal(cReport.normal1);
int i; 
for (i=0; i<p->numVerts(); i++)
   {
 //  printf("v%d = %f %f %f\n", i, (*p)[i][0], (*p)[i][1], (*p)[i][2]);
  }



  p = dynamic_cast<const Polytope*>(&b);
  if (p)
     p->getNormal(cReport.normal2);
  if (compute_contact_types(a,pa,b,pb,b2a,cReport) == false) return false;

  totalCon.addContact(cReport);

 // printf("contact!\n");
  return true;
}

#ifdef STATISTICS
void catch_me() {}
#endif


void closest_points(const Convex& a, const Convex& b,
		    const Transform& a2w, const Transform& b2w,
		    Point& pa, Point& pb) {
  static Vector zero(0, 0, 0);
  
  Vector v = a2w(a.support(zero)) - b2w(b.support(zero));
  Scalar dist = v.length();

  Vector w;

//printf("closest_points1: ");
  bits = 0;
  all_bits = 0;
  Scalar mu = 0;

#ifdef STATISTICS
  num_iterations = 0;
#endif

  while (bits < 15 && dist > abs_error) {
    last = 0;
    last_bit = 1;
    while (bits & last_bit) { ++last; last_bit <<= 1; }
    p[last] = a.support((-v) * a2w.getBasis());
    q[last] = b.support(v * b2w.getBasis());
    w = a2w(p[last]) - b2w(q[last]);
    set_max(mu, dot(v, w) / dist);
    if (dist - mu <= dist * rel_error) break; 
    if (degenerate(w)) {
#ifdef STATISTICS
      ++num_irregularities;
#endif
      break;
    }
    y[last] = w;
    all_bits = bits|last_bit;
#ifdef STATISTICS
    ++num_iterations;
    if (num_iterations > 1000) catch_me();
#endif
    if (!closest(v)) {
#ifdef STATISTICS
      ++num_irregularities;
#endif
      break;
    }
    dist = v.length();
  }
  compute_points(bits, pa, pb);

  ContactReport cReport;
  cReport.p1[0] = pa[0];
  cReport.p1[1] = pa[1];
  cReport.p1[2] = pa[2];
  cReport.p2[0] = pb[0];
  cReport.p2[1] = pb[1];
  cReport.p2[2] = pb[2];
  const Polytope* p = dynamic_cast<const Polytope*>(&a);
  if (p)
     p->getNormal(cReport.normal1);

  p = dynamic_cast<const Polytope*>(&b);
  if (p)
     p->getNormal(cReport.normal2);
  Transform b2a, w2a;
  w2a.invert(a2w);
  b2a.mult(b2w,w2a);
  if (compute_contact_types(a,pa,b,pb,b2a,cReport) == false) return;

  totalCon.addContact(cReport);
//printf("yes\n");
}

