#include <SOLID/solid.h>
#include "Complex.h"
#include <3D/Point.h>

void dtPrintObject(DtObjectRef object);

typedef vector<Point> PointList;

extern TotalContact totalCon;

ContactReport* contactReport = NULL;
int numContactReports = 0;

void solid_callback(void* client_data, DtObjectRef obj1, DtObjectRef obj2,
		    const DtCollData *coll_data);

void make_solid_object(PolyhedronStruct* ph)
{

   int i;
   Point point;
   PointList* points = new PointList;

   DtShapeRef shape = dtNewComplexShape();

   for (i=0; i<ph->num_vertices; i++)
   {
      point[0] = ph->vertex[i].coord[0];
      point[1] = ph->vertex[i].coord[1];
      point[2] = ph->vertex[i].coord[2];
      points->push_back(point);
   }
   dtVertexBase(&((*points)[0]));

   for (i=0; i<ph->num_polygons; i++)
   {
      dtBegin(DT_POLYGON);
      for (int j=0; j<ph->polygon[i].num_vertices; j++)
	 dtVertexIndex(ph->polygon[i].vertex_index[j]);
      dtEnd();
   }
   dtEndComplexShape();

   dtCreateObject(ph,shape);

}


void solid_pre_init(void)
{

}

void solid_post_init(void)
{

   dtDisableCaching();
   dtSetDefaultResponse(NULL,DT_NO_RESPONSE,NULL);

}

void make_contact_response(PolyhedronStruct* ph1, PolyhedronStruct* ph2,
			     ContactPair* cp, ResponseType type)
{

   if (type == ALL_POINTS)
      dtSetPairResponse(ph1,ph2,solid_callback,DT_TOTAL_RESPONSE,cp);
   else
      dtSetPairResponse(ph1,ph2,solid_callback,DT_WITNESSED_RESPONSE,cp);

}

void transform_solid_object(PolyhedronStruct* ph, double vec[], double quat[])
{

   dtSelectObject(ph);
   dtLoadIdentity();
   dtTranslate((DtScalar)vec[0],(DtScalar)vec[1],(DtScalar)vec[2]);
   dtRotate((DtScalar)quat[0],(DtScalar)quat[1],(DtScalar)quat[2],(DtScalar)quat[3]);

}

void calc_solid_contacts(void)
{

   /* There may be a more efficient way to calculate contacts, if
    * dtTest compares every two objects for contact and then
    * checks to see if a response is desired.
    */

   dtTest();

}

void solid_callback(void* client_data, DtObjectRef obj1, DtObjectRef obj2,
		    const DtCollData *coll_data)
{

   totalCon.mergeContacts();
   contactReport = totalCon.getContacts();
   numContactReports = totalCon.getSize();

/*
   printf("solid_callback, num = %d, ph1 = %s, ph2 = %s\n", numContactReports,
	  ((PolyhedronStruct*)(obj1))->name,
	  ((PolyhedronStruct*)(obj2))->name);

   for (int i=0; i<numContactReports; i++)
   {
      printf("p1: %lf %lf %lf\n", contactReport->p1[0],
	     contactReport->p1[1], contactReport->p1[2]);
      printf("p2: %lf %lf %lf\n", contactReport->p2[0],
	     contactReport->p2[1], contactReport->p2[2]);
   }
   fflush(stdout);
*/

   /* client_data is really a pointer to a ContactPair. This struct
    * contains a pointer to a function for handling the contact response.
    * Call this function with the polyhedra and array of contact reports.
    */
   if (client_data)
   {
      ContactPair* cp = (ContactPair*)client_data;
      cp->callback((PolyhedronStruct*)obj1, (PolyhedronStruct*)obj2,
		   cp, numContactReports, contactReport);
   }

}

