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

#ifndef _POLYTOPE_H_
#define _POLYTOPE_H_

#include "Convex.h"
#include "IndexArray.h"
#include "VertexBase.h"
//#include <stdio.h>

#define ABS(a) ((a)>0?(a):(-(a)))
#define CALC_DETERMINANT(m) (((m[0][0]) * ((m[1][1])*(m[2][2]) - (m[1][2])*(m[2][1]))) - \
((m[0][1]) * ((m[1][0])*(m[2][2]) - (m[1][2])*(m[2][0]))) + \
((m[0][2]) * ((m[1][0])*(m[2][1]) - (m[1][1])*(m[2][0]))))
#define ILS_TOL 0.001
#define CLIP_TOL 1.0


class Polytope : public Convex {
public:
  Polytope(const VertexBase& b, int c, const unsigned int v[]) : 
    base(b), index(c, v), normal(1.0, 0.0, 0.0)
    {
       if (c >= 3)
       {
	  Vector vec1 = b[v[1]] - b[v[0]];
	  Vector vec2 = b[v[2]] - b[v[0]];
	  normal[X] = vec1[Y]*vec2[Z] - vec1[Z]*vec2[Y];
	  normal[Y] = vec1[Z]*vec2[X] - vec1[X]*vec2[Z];
	  normal[Z] = vec1[X]*vec2[Y] - vec1[Y]*vec2[X];
	  double mag = sqrt(normal[X]*normal[X] + normal[Y]*normal[Y] + normal[Z]*normal[Z]);
	  if (NOT_EQUAL_WITHIN_TOLERANCE(mag,0.0,1e-10))
	  {
	     normal[X] /= mag;
	     normal[Y] /= mag;
	     normal[Z] /= mag;
	  }
	  d = -normal[X]*b[v[0]][X] - normal[Y]*b[v[0]][Y] - normal[Z]*b[v[0]][Z];
       }
    }
  virtual ~Polytope() {}
  virtual Point support(const Vector&) const = 0;

  const Point& operator[](int i) const { return base[index[i]]; }
  int numVerts() const { return index.size(); }
  bool contains(Point& p) const;
  Point centroid() const;
  void clipEdge(Point& p1, Point& p2, Point& p3, Point& p4) const;
  int nextVertex(int index) const
  {
     return (index + 1) % numVerts();
  }
  int previousVertex(int index) const
  {
     return (index + numVerts() - 1) % numVerts();
  }
  void getNormal(double* norm) const
  {
     norm[X] = normal[X]; norm[Y] = normal[Y]; norm[Z] = normal[Z];
  }
  Vector getNormal() const
  {
     return normal;
  }
  bool intersectLineSegments(Point& p1, Point& p2, const Point& p3,
			     const Point& p4, Point& p5, double& s, double& t, double tol) const;

private:
  const VertexBase& base;
  IndexArray index;
  Vector normal;
  Scalar d;

};

#endif
