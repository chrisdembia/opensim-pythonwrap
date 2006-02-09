#include <stdio.h>
#include <fstream.h> //alex
#include <SOLID/solid.h>

#include <assert.h>

#include <3D/Point.h>
#include <3D/Quaternion.h>
#include <vector.h>

#define SPACE_SIZE 5
#define NUM_ITER 1

typedef vector<Point> PointList;

typedef struct MyObject {
  int id;
} MyObject; 

/* ARGSUSED */
void collide1(void * client_data, DtObjectRef obj1, DtObjectRef obj2,
	      const DtCollData *coll_data)
{

   printf("p1: %lf %lf %lf\n", coll_data->point1[0],
	  coll_data->point1[1], coll_data->point1[2]);
   printf("p2: %lf %lf %lf\n", coll_data->point2[0],
	  coll_data->point2[1], coll_data->point2[2]);

}

/* ARGSUSED */
void collide2(void * client_data, DtObjectRef obj1, DtObjectRef obj2,
	      const DtCollData *coll_data) {
  FILE *stream = (FILE *)client_data;
  fprintf(stream, "Object %d interferes with object %d\n", 
	  (*(MyObject *)obj1).id, (*(MyObject *)obj2).id);
}

void make_first(void);
void make_second(void);

MyObject object1, object2;
DtShapeRef shape;
DtShapeRef shape2;

int main(int argc, char *argv[])
{

   make_first();

   make_second();

   dtDisableCaching();

   dtSetDefaultResponse(collide1, DT_WITNESSED_RESPONSE, stdout);

   dtTest();

   dtDeleteObject(&object1);
   dtDeleteObject(&object2);

//   dtDeleteShape(shape);
//   dtDeleteShape(shape2);

   return 0;
}

   PointList points;
   Point point;

void make_first(void)
{

   object1.id = 1;

   shape = dtNewComplexShape();

   point[0] = 0.1;
   point[1] = 0.0;
   point[2] = 0.0;
   points.push_back(point);
   point[0] = 1.0;
   point[1] = 0.0;
   point[2] = 0.0;
   points.push_back(point);
   point[0] = 0.5;
   point[1] = 1.0;
   point[2] = 0.0;
   points.push_back(point);

   dtVertexBase(&points[0]);

   dtBegin(DT_POLYGON);
   dtVertexIndex(0);
   dtVertexIndex(1);
   dtVertexIndex(2);
   dtEnd();

   dtEndComplexShape();

   dtCreateObject(&object1, shape);

}

   PointList points2;
   Point point2;

void make_second(void)
{

   object2.id = 2;

   shape2 = dtNewComplexShape();

   point2[0] = 0.1;
   point2[1] = 0.5;
   point2[2] = 0.5;
   points2.push_back(point2);
   point2[0] = 0.5;
   point2[1] = 0.5;
   point2[2] = -0.5;
   points2.push_back(point2);
   point2[0] = 1.0;
   point2[1] = 0.5;
   point2[2] = 0.5;
   points2.push_back(point2);

   dtVertexBase(&points2[0]);

   dtBegin(DT_POLYGON);
   dtVertexIndex(0);
   dtVertexIndex(1);
   dtVertexIndex(2);
   dtEnd();

   dtEndComplexShape();

   dtCreateObject(&object2, shape2); 

}
