/*******************************************************************************

   OBJECT.C

   Authors: Peter Loan
            Krystyne Blaikie

   Copyright (c) 1996-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains functions that read in descriptions of
      objects used by the rigid-body contact detection code.

   Routines:
   read_object:              read object definitions from parameters file
   read_object_group:        read object group definitions
   read_contact_pair:        read contact pair definitions
   init_object_info:         initialize object structures
   check_object_info:        check that all contact objects are properly defined
   enter_object:             enters an object into the master list
   enter_group:              enters a contact group into the master list
   show_object_info:         display contact object information to screen
   check_file_type:          determine type of bone file
   preread_init_polygon:     initialize a polygon
   preread_init_vertex:      initialize a vertex
   preread_init_polyhedron:  initialize a polyhedron
   postread_init_polyhedron: init polyhedron after reading from file
   flip_bytes:               flip bytes in a binary file
   read_binary:              read a number from a binary file
   read_binary_array:        read an array from a binary file
   read_binary_file:         read a binary bone file
   read_ascii_file:          read an ascii bone file
   read_old_ascii_file:      read an old ascii bone file
   copy_polyhedron:          copy a polyhedron
   copy_vertex:              copy a vertex
   copy_polygon:             copy a polygon
   free_polyhedron:          free a polyhedron
   check_polyhedron:         check the consistency of a polyhedron
   calc_polygon_normal:      calculate a polygon normal
   make_vert_poly_lists:     make a list of polygons used by a vertex
   read_polyhedron:          read polyhedron information from a bone file

*******************************************************************************/

#include "universal.h"
#include <fcntl.h>

#if CONTACT_DETECTION
#include "pipesolid.h"
#endif

/*************** DEFINES (for this file only) *********************************/
/* constants */
#define COLLINEAR_EPSILON 0.001

/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
static char new_ascii_label[] = "NORM_ASCII";
static char obj_error_text[] = "Error in parameters file:";

#ifdef WIN32
  static int filekey = 0x85000000;  /* byte-flipped 133 */
#else
  static int filekey = 133;         /* = 0x00000085 */
#endif

/*************** GLOBAL VARIABLES (used in only a few files) ******************/
#if CONTACT_DETECTION
ObjectInfo object_info;
#endif


/*************** EXTERNED VARIABLES (declared in another .c file) *************/
extern dpModelStruct* sdm;
extern char buffer[];            /* defined in readtools.c */
extern char current_dir[];
extern char *bone_path;

/***************** GLOBAL FUNCTION PROTOTYPES *********************************/
#if CONTACT_DETECTION
extern void contact_callback(dpPolyhedronStruct *ph1, dpPolyhedronStruct *ph2, 	
	ContactPair *cp, int num_contacts, ContactReport* contact);
#endif

/*************** STATIC FUNCTION PROTOTYPES (used in this file only) **********/
#if CONTACT_DETECTION
static int enter_object(char name[], EnterMode mode);
static int enter_group(char name[], EnterMode mode);
#endif
static FileType check_file_type(char filename[]);
static void preread_init_polygon(dpPolygonStruct* p);
static void preread_init_vertex(dpVertexStruct* v, int index);
static void preread_init_polyhedron(dpPolyhedronStruct* ph);
static void postread_init_polyhedron(dpPolyhedronStruct* ph);
static void flip_bytes(char* buf, int size);
static int read_binary(int fd, char* buf, int size);
static int read_binary_array(int fd, char* buf, int n, int size);
static ReturnCode read_binary_file(dpPolyhedronStruct* ph, char filename[]);
static ReturnCode read_ascii_file(dpPolyhedronStruct* ph, char filename[]);
static ReturnCode read_old_ascii_file(dpPolyhedronStruct* ph, char filename[]);
static void copy_vertex(dpVertexStruct* from, dpVertexStruct* to);
static void copy_polygon(dpPolygonStruct* from, dpPolygonStruct* to);
static void free_polyhedron(dpPolyhedronStruct* ph, dpBoolean free_ph);
static ReturnCode check_polyhedron(dpPolyhedronStruct* ph);
static void calc_polygon_normal(dpPolyhedronStruct* ph, dpPolygonStruct* p);
static void make_vert_poly_lists(dpPolyhedronStruct* ph);


#if CONTACT_DETECTION
/* read an object definition from parameters file:
 * object name, filename, segment name
 * Read the polyhedron and store the object.
 */
void read_object(FILE** fp)
{
   int seg, obj_num;
   ReturnCode rc;
   dpBodyStruct* body;
   dpPolyhedronStruct ph;
   dpPolyhedronStruct* ph_ptr;
   char str1[CHARBUFFER], str2[CHARBUFFER], str3[CHARBUFFER];
   char filename[CHARBUFFER];

   if (fscanf(*fp,"%s %s %s", str1, str2, str3) != 3)
      sim_message(exit_program, "%s bad object definition.", obj_error_text);

   if (enter_group(str1,just_checking_element) != -1)
      sim_message(exit_program, "%s object name %s was already used as a group name.", obj_error_text, str3);

   if ((seg = enter_segment(sdm, str3)) == -2)
      sim_message(exit_program, "%s unknown segment name (%s) in object definition.", obj_error_text, str3);

   ph.body_segment = seg;
	
   strcpy(filename, str2);
   if (read_polyhedron(&ph, filename) == code_bad)
      sim_message(exit_program, "Could not read %s...Exiting.", str1);

	/* If you make it to here, then the polyhedron was successfully loaded,
	 * and the segment name matched one in the model, so add the object to
	 * the list, and store the polyhedron in the body segment structure.
	 */
   mstrcpy(&ph.name, str1);
   obj_num = enter_object(str1, defining_element);

   body = &sdm->body_segment[seg + 1];

   if (body->num_objects == 0)
      body->object = (dpPolyhedronStruct**)simm_malloc(sizeof(dpPolyhedronStruct*));
   else
      body->object = (dpPolyhedronStruct**)simm_realloc(body->object,
         (body->num_objects+1)*sizeof(dpPolyhedronStruct*),&rc);

   ph_ptr = body->object[body->num_objects++] = 
      (dpPolyhedronStruct*)simm_malloc(sizeof(dpPolyhedronStruct));

   copy_polyhedron(&ph,ph_ptr);

   object_info.object[obj_num].ph = ph_ptr;

   make_solid_object(ph_ptr);
}


/* read an object group definition from the parameters file.
 * Read the group name and the objects in the group.
 */
void read_object_group(FILE** fp)
{
   int num;
   ObjectGroup* grp;
   ReturnCode rc;
   char name[CHARBUFFER];

   if (fscanf(*fp, "%s", name) != 1)
      sim_message(exit_program, "%s bad group definition - %s.", obj_error_text, name);

   if (enter_object(name, just_checking_element) != -1)
      sim_message(exit_program, "%s group name %s was already used as an object name.", obj_error_text, name);

   num = enter_group(name, defining_element);
   grp = &object_info.group[num];
   grp->num_objects = 0;

   while (1)
   {
      if (fscanf(*fp,"%s", name) != 1)
         sim_message(exit_program, "%s bad group definition - \"%s\" (Did not find end_group).", obj_error_text, name);

		if (STRINGS_ARE_EQUAL(name,"end_group"))
		{
			return;
		}
		if (++grp->num_objects == 1)
			grp->object_num = (int*)simm_malloc(sizeof(int));
		else
			grp->object_num = (int*)simm_realloc(grp->object_num,
					      grp->num_objects*sizeof(int),&rc);

		grp->object_num[grp->num_objects-1] = enter_object(name, declaring_element);
   }
}

/* read the definition of a contact pair from the parameters file
 * read the two object names, the coefficient of restitution and the friction
 * coefficients and store the information.
*/
void read_contact_pair(FILE** fp)
{

   ReturnCode rc;
   char str1[CHARBUFFER], str2[CHARBUFFER];
   ContactPair* cp;
   double coef_rest, mu_dynamic, mu_static;

   if (fscanf(*fp, "%s %s %lf %lf %lf", str1, str2, &coef_rest, &mu_static, &mu_dynamic) != 5)
      sim_message(exit_program, "%s incomplete contact_pair definition: coef rest, dynamic friction, static friction must be specified.", 
	      obj_error_text);

   if (object_info.num_pairs == 0)
      object_info.pair = (ContactPair*)simm_malloc(sizeof(ContactPair));
   else
      object_info.pair = (ContactPair*)simm_realloc(object_info.pair,
				 (object_info.num_pairs+1)*sizeof(ContactPair),&rc);
   cp = &object_info.pair[object_info.num_pairs++];

   mstrcpy(&cp->name1,str1);
   mstrcpy(&cp->name2,str2);

   cp->callback = contact_callback;
   cp->restitution = coef_rest;
   cp->static_friction = mu_static;
   cp->dynamic_friction = mu_dynamic;

}

/* initialize object information structure */
void init_object_info(void)
{

   object_info.num_objects = 0;
   object_info.num_groups = 0;
   object_info.num_pairs = 0;

   solid_pre_init();
}

/* check object definitions */
void check_object_info(void)
{
   int i, j, k, errors = 0;
   ContactObject *obj1, *obj2;
   ObjectGroup *grp1, *grp2;
   ContactPair* cp;

	for (i = 0; i < object_info.num_objects; i++)
	{
		if (object_info.object[i].defined == dpNo)
		{
			sim_message(recover, "%s Object \"%s\" undefined.", obj_error_text, object_info.object[i].name);
			errors++;
		}
	}

	for (i = 0; i < object_info.num_groups; i++)
	{
		if (object_info.group[i].defined == dpNo &&
			STRINGS_ARE_NOT_EQUAL("all",object_info.group[i].name))
		{
			sim_message(recover, "%s Group %s undefined.", obj_error_text, object_info.group[i].name);
			errors++;
		}
	}

   /* If the user used a group called "all" and didn't define it,
    * define it here as a group containing every object.
    */
	for (i = 0; i < object_info.num_groups; i++)
	{
		if (object_info.group[i].defined == dpNo &&
			STRINGS_ARE_EQUAL("all",object_info.group[i].name))
		{
			object_info.group[i].num_objects = object_info.num_objects;
			object_info.group[i].object_num = 	
				(int*)simm_malloc(object_info.num_objects*sizeof(int));
			for (j=0; j<object_info.num_objects; j++)
				object_info.group[i].object_num[j] = j;
			object_info.group[i].defined = dpYes;
      }
   }

	for (i = 0; i < object_info.num_pairs; i++)
	{
		cp = &object_info.pair[i];
		if ((cp->element1 = enter_object(cp->name1, just_checking_element)) != -1)
		{
			cp->type1 = PAIR_OBJECT;
		}
		else
		{
		  if ((cp->element1 = enter_group(cp->name1,just_checking_element)) == -1)
			{
				sim_message(recover, "%s contact pair - \"%s\" is not an object or group name.",
		    		obj_error_text, cp->name1);
				errors++;
			}
			else
			{
				cp->type1 = PAIR_GROUP;
			}
		}

		if ((cp->element2 = enter_object(cp->name2,just_checking_element)) != -1)
		{
			cp->type2 = PAIR_OBJECT;
		}
		else
		{
		  if ((cp->element2 = enter_group(cp->name2,just_checking_element)) == -1)
			{
				sim_message(recover, "%s contact_pair - \"%s\" is not an object or group name.",
					obj_error_text, cp->name2);
				errors++;
			}
			else
			{
				cp->type2 = PAIR_GROUP;
			}
		}
	}

   if (errors > 0)
      sim_message(exit_program, "");

	solid_post_init();
	
   /* Now register response types and callback functions for each
    * contact pair (each pair of objects for which you want to
    * check for contacts). The response type is set to ALL_POINTS
    * by default, meaning that you want the contact detection code
    * to return all intersections between the two objects. If you want
    * the code to return only the first intersection point it finds,
    * set the response type to ONE_POINT.
    * The default callback function is contact_callback(), which is
    * used for all pairs of objects. If you want to set different
    * callbacks for different pairs of objects, you will need to add
    * some code to the for loop below.
    */

	for (i = 0; i < object_info.num_pairs; i++)
	{
		cp = &object_info.pair[i];

		if (cp->type1 == PAIR_OBJECT)
		{
			obj1 = &object_info.object[cp->element1];
			if (cp->type2 == PAIR_OBJECT)
			{
				obj2 = &object_info.object[cp->element2];
				make_contact_response(obj1->ph, obj2->ph, cp, ALL_POINTS);
            sdm->body_segment[obj1->ph->body_segment + 1].contactable = dpYes;
            sdm->body_segment[obj2->ph->body_segment + 1].contactable = dpYes;
			}
			else
			{
				grp2 = &object_info.group[cp->element2];
				for (j=0; j<grp2->num_objects; j++)
				{
					obj2 = &object_info.object[grp2->object_num[j]];
					make_contact_response(obj1->ph, obj2->ph, cp, ALL_POINTS);
               sdm->body_segment[obj1->ph->body_segment + 1].contactable = dpYes;
               sdm->body_segment[obj2->ph->body_segment + 1].contactable = dpYes;
				}
			}
		}
		else
      {
			grp1 = &object_info.group[cp->element1];
			for (j=0; j<grp1->num_objects; j++)
			{
				obj1 = &object_info.object[grp1->object_num[j]];
				if (cp->type2 == PAIR_OBJECT)
				{
					obj2 = &object_info.object[cp->element2];
					make_contact_response(obj1->ph, obj2->ph, cp, ALL_POINTS);
               sdm->body_segment[obj1->ph->body_segment + 1].contactable = dpYes;
               sdm->body_segment[obj2->ph->body_segment + 1].contactable = dpYes;
				}
				else
				{
					grp2 = &object_info.group[cp->element2];
					for (k=0; k<grp2->num_objects; k++)
					{
						obj2 = &object_info.object[grp2->object_num[j]];
						make_contact_response(obj1->ph, obj2->ph, cp, ALL_POINTS);
                  sdm->body_segment[obj1->ph->body_segment + 1].contactable = dpYes;
                  sdm->body_segment[obj2->ph->body_segment + 1].contactable = dpYes;
					}
				}
			}
		}
	}
   for (i = 0; i < sdm->num_body_segments; i++)
      if (STRINGS_ARE_EQUAL(sdm->body_segment[i].name, "ground"))
         sdm->body_segment[i].contactable = dpNo;
}




static int enter_object(char name[], EnterMode mode)
{
   int i;
   ReturnCode rc;

	for (i = 0; i < object_info.num_objects; i++)
	{
		if (STRINGS_ARE_EQUAL(name, object_info.object[i].name))
		{
			if (mode == defining_element)
			{
				if (object_info.object[i].defined == dpYes)
					sim_message(exit_program, "Error in parameters file: Object \"%s\" redefined.", name);
				else
					object_info.object[i].defined = dpYes;
			}
			return i;
		}
	}

	if (mode == just_checking_element)
		return -1;

	if (object_info.num_objects == 0)
		object_info.object = 
			(ContactObject*)simm_malloc(sizeof(ContactObject));
	else
		object_info.object = (ContactObject*)simm_realloc(object_info.object,
				  (object_info.num_objects+1)*sizeof(ContactObject),&rc);

	mstrcpy(&object_info.object[object_info.num_objects].name, name);

	if (mode == defining_element)
		object_info.object[object_info.num_objects].defined = dpYes;
	else
		object_info.object[object_info.num_objects].defined = dpNo;

	return object_info.num_objects++;
}


static int enter_group(char name[], EnterMode mode)
{
   int i;
   ReturnCode rc;
   ObjectGroup* grp;

	for (i=0; i<object_info.num_groups; i++)
	{
		if (STRINGS_ARE_EQUAL(name,object_info.group[i].name))
		{
			if (mode == defining_element)
			{
				if (object_info.group[i].defined == dpYes)
					sim_message(exit_program, "Error in parameters file: Group \"%s\" redefined.", name);
				else
					object_info.group[i].defined = dpYes;
			}
			return i;
		}
	}

	if (mode == just_checking_element)
		return -1;

	if (object_info.num_groups == 0)
		object_info.group = (ObjectGroup*)simm_malloc(sizeof(ObjectGroup));
	else
		object_info.group = (ObjectGroup*)simm_realloc(object_info.group,
				     (object_info.num_groups+1)*sizeof(ObjectGroup), &rc);

	grp = &object_info.group[object_info.num_groups++];

	mstrcpy(&grp->name, name);

	if (mode == defining_element)
		grp->defined = dpYes;
	else
		grp->defined = dpNo;

	return object_info.num_groups - 1;
}


void show_object_info(void)
{
   int i, j, obj_num;

	sim_message(none, "\nOBJECT INFO");
	sim_message(none, "%d objects:", object_info.num_objects);
	for (i = 0; i < object_info.num_objects; i++)
   {
		sim_message(none, "\tobject %s (%d) has polyhedron struct:",
			object_info.object[i].name, i);
		sim_message(none, "\t\tname: %s\n\t\tbody_segment: %d", 
			(&object_info.object[i])->ph->name,
			(&object_info.object[i])->ph->body_segment);
	}
		
	sim_message(none, "%d pairs:", object_info.num_pairs);
	for (i = 0; i < object_info.num_pairs; i++)
   {
		sim_message(none, "\tpair %d:", i);
		sim_message(none, "\t  %-10s\t%-10s", "OBJECT 1", "OBJECT2");
		sim_message(none, "\t  %-10s\t%-10s", object_info.pair[i].name1,
			object_info.pair[i].name2);
		sim_message(none, "\t  %d (", object_info.pair[i].element1);
		if (object_info.pair[i].type1 == PAIR_OBJECT)
         sim_message(none, "object)");
		else
         sim_message(none, "group)");
		sim_message(none, "\t%d (", object_info.pair[i].element2);
		if (object_info.pair[i].type2 == PAIR_OBJECT)
         sim_message(none, "object)");
		else
         sim_message(none, "group)");
	}
	
	sim_message(none, "%d groups:", object_info.num_groups);
	for (i = 0; i < object_info.num_groups; i++)
   {
		sim_message(none, "\tgroup %s (%d)", object_info.group[i].name, i);
		sim_message(none, " has %d objects", object_info.group[i].num_objects);
		for (j = 0; j < object_info.group[i].num_objects; j++)
      {
			obj_num = object_info.group[i].object_num[j];
			sim_message(none, "\t  %d: object %d (%s)", j, obj_num, 
				(&object_info.object[obj_num])->ph->name);
		}
	}
}

#endif /* CONTACT_DETECTION */


static FileType check_file_type(char filename[])
{

   int fpb, fkb;
   char fkey[100];
   FILE* fpa;
   FileType ft = unknown;

#ifdef WIN32
   if ((fpb = open(filename,O_RDONLY | O_BINARY)) == -1)
#else
   if ((fpb = open(filename,O_RDONLY)) == -1)
#endif
   {
      return file_not_found;
   }
   else
   {
      read(fpb,(char*)&fkb,sizeof(int));
      if (fkb == filekey)
         ft = binary;
      else
         ft = unknown;
      close(fpb);
   }

   if (ft == unknown)
   {
      if ((fpa = simm_fopen(filename,"r")) == NULL)
      {
         return file_not_found;
      }
      else
      {
         fscanf(fpa,"%s", fkey);
         if (STRINGS_ARE_EQUAL(fkey,new_ascii_label))
            ft = new_ascii;
         else
            ft = old_ascii;
         fclose(fpa);
      }
   }

   return ft;
}


static void preread_init_polygon(dpPolygonStruct* p)
{
   p->num_vertices = 0;
   p->vertex_index = NULL;
   p->d = 0.0;
}

static void preread_init_vertex(dpVertexStruct* v, int index)
{
   v->coord[0] = v->coord[1] = v->coord[2] = 0.0;
   v->normal[0] = v->normal[1] = v->normal[2] = 0.0;
   v->polygon_count = 0;
   v->polygons = NULL;
}


static void preread_init_polyhedron(dpPolyhedronStruct* ph)
{
   ph->name = NULL;
   ph->vertex = NULL;
   ph->polygon = NULL;

   ph->num_vertices = 0;
   ph->num_polygons = 0;

   ph->bc.x1 = MAXMDOUBLE;
   ph->bc.x2 = MINMDOUBLE;
   ph->bc.y1 = MAXMDOUBLE;
   ph->bc.y2 = MINMDOUBLE;
   ph->bc.z1 = MAXMDOUBLE;
   ph->bc.z2 = MINMDOUBLE;
}


static void postread_init_polyhedron(dpPolyhedronStruct* ph)
{
   int i;

   for (i=0; i<ph->num_polygons; i++)
      calc_polygon_normal(ph,&ph->polygon[i]);

   make_vert_poly_lists(ph);
}


/* ---------------------------------------------------------------------------
   BINARY COMPATIBILITY ROUTINES:  the following 3 routines are used to support
     reading [IRIX] binary bone files on little-endian Win32 machines.  -- KMS 12/17/98
------------------------------------------------------------------------------ */
static void flip_bytes(char* buf, int size)
{
   char* p = buf;
   char* q = buf + size - 1;

   for ( ; p < q; p++, q--)
   {
      char c = *p;

      *p = *q;
      *q = c;
   }
}

static int read_binary(int fd, char* buf, int size)
{
   int bytes_read = read(fd, buf, size);

#ifdef WIN32
   flip_bytes(buf, size);
#endif

   return bytes_read;
}

static int read_binary_array(int fd, char* buf, int n, int size)
{
   int nBytes = n * size;
   
   int bytes_read = read(fd, buf, nBytes);
   
#ifdef WIN32
   char *p = buf, *end = buf + nBytes;
   
   for ( ; p < end; p += size)
      flip_bytes(p, size);
#endif

   return bytes_read;
}


static ReturnCode read_binary_file(dpPolyhedronStruct* ph, char filename[])
{

   int i, j, fd, filekey, not_needed, num_edges;
   long correct_num_bytes, bytes_read = 0;
   float fnormal[3];

#ifdef WIN32
   if ((fd = open(filename,O_RDONLY | O_BINARY | O_RAW)) == -1)
#else
   if ((fd = open(filename,O_RDONLY)) == -1)
#endif
   {
      sim_message(none, "Unable to open file %s.", filename);
      return code_bad;
   }

   bytes_read += read_binary(fd,(char*)&filekey,sizeof(int));
   if (filekey != 133)
   {
      sim_message(none, "File %s is not a properly formatted binary file.", filename);
      return code_bad;
   }

   bytes_read += read_binary(fd,(char*)&ph->num_vertices,sizeof(int));
   bytes_read += read_binary(fd,(char*)&ph->num_polygons,sizeof(int));
   bytes_read += read_binary(fd,(char*)&not_needed,sizeof(int));
   bytes_read += read_binary(fd,(char*)&not_needed,sizeof(int));
   bytes_read += read_binary(fd,(char*)&ph->bc.x1,sizeof(double));
   bytes_read += read_binary(fd,(char*)&ph->bc.x2,sizeof(double));
   bytes_read += read_binary(fd,(char*)&ph->bc.y1,sizeof(double));
   bytes_read += read_binary(fd,(char*)&ph->bc.y2,sizeof(double));
   bytes_read += read_binary(fd,(char*)&ph->bc.z1,sizeof(double));
   bytes_read += read_binary(fd,(char*)&ph->bc.z2,sizeof(double));

   ph->vertex = (dpVertexStruct*)simm_malloc(ph->num_vertices*sizeof(dpVertexStruct));
   ph->polygon = (dpPolygonStruct*)simm_malloc(ph->num_polygons*sizeof(dpPolygonStruct));

   if (ph->vertex == NULL || ph->polygon == NULL)
      return code_bad;

   for (i=0; i<ph->num_vertices; i++)
   {
      preread_init_vertex(&ph->vertex[i],i);
      bytes_read += read_binary_array(fd, (char*) ph->vertex[i].coord,
                                      3, sizeof(double));
       /* In SD/FAST, the origin of a body's reference frame is located at the
       * center of mass. So subtract the coordinates of the center of mass
       * (w.r.t the SIMM reference frame) to get the coords of the bone vertex
       * w.r.t the center of mass. The mass center coords for segment i
       * are located in the body segment array at element i+1 (because ground
       * is -1, but is the 0th element in the array).
       */

      for (j=0; j<3; j++)
	      ph->vertex[i].coord[j] -= sdm->body_segment[ph->body_segment+1].mass_center[j];                               
   }

   for (i=0; i<ph->num_vertices; i++)
   {
      bytes_read += read_binary_array(fd, (char*) fnormal, 3, sizeof(float));
      ph->vertex[i].normal[0] = fnormal[0];
      ph->vertex[i].normal[1] = fnormal[1];
      ph->vertex[i].normal[2] = fnormal[2];
   }

   for (i=0, num_edges=0; i<ph->num_polygons; i++)
   {
      preread_init_polygon(&ph->polygon[i]);
      bytes_read += read_binary(fd, (char*) &ph->polygon[i].num_vertices, sizeof(int));
      num_edges += ph->polygon[i].num_vertices;
      ph->polygon[i].vertex_index = (int*)simm_malloc(ph->polygon[i].num_vertices*
						      sizeof(int));
   }

   for (i=0; i<ph->num_polygons; i++)
   {
      bytes_read += read_binary_array(fd, (char*) ph->polygon[i].vertex_index,
                                ph->polygon[i].num_vertices, sizeof(int));
   }
   close(fd);

   correct_num_bytes = 5*sizeof(int) + 6*sizeof(double) +
      3*ph->num_vertices*sizeof(double) + 3*ph->num_vertices*sizeof(float) +
	   ph->num_polygons*sizeof(int) + num_edges*sizeof(int);

   if (bytes_read != correct_num_bytes)
   {
      ph->num_vertices = ph->num_polygons = 0;
      sim_message(none, "Error reading file %s. Only %ld of %ld bytes read.",
         filename, bytes_read, correct_num_bytes);
      return code_bad;
   }

   /* subtract the segment's mass center from the bounding box coordinates */
   ph->bc.x1 -= sdm->body_segment[ph->body_segment+1].mass_center[0];
   ph->bc.x2 -= sdm->body_segment[ph->body_segment+1].mass_center[0];
   ph->bc.y1 -= sdm->body_segment[ph->body_segment+1].mass_center[1];
   ph->bc.y2 -= sdm->body_segment[ph->body_segment+1].mass_center[1];
   ph->bc.z1 -= sdm->body_segment[ph->body_segment+1].mass_center[2];
   ph->bc.z2 -= sdm->body_segment[ph->body_segment+1].mass_center[2];

   return code_fine;
}


static ReturnCode read_ascii_file(dpPolyhedronStruct* ph, char filename[])
{
   int i, j, rc;
   FILE* fp;

   fp = simm_fopen(filename,"r");
   if (fp == NULL)
   {
      sim_message(none, "Unable to open file %s.", filename);
      return code_bad;
   }

   /* For now, support old ASCII file type. Eventually (perhaps for SIMM/PC 1.0,
    * we'll want to remove support for this filetype (as well as for binary),
    * since the new norm will only output the new ASCII format.
    */
   rc = fscanf(fp,"%s", buffer);
   if (rc != 1 || STRINGS_ARE_NOT_EQUAL(buffer,new_ascii_label))
   {
      fclose(fp);
      sim_message(none, "Error reading header information from file %s.", filename);
      return code_bad;
   }

   rc = fscanf(fp,"%d %d", &ph->num_vertices, &ph->num_polygons);

   if (rc != 2)
   {
      fclose(fp);
      sim_message(none, "Error reading header information from file %s.", filename);
      return code_bad;
   }

   rc = fscanf(fp,"%lf %lf %lf %lf %lf %lf",
	       &ph->bc.x1, &ph->bc.x2,
	       &ph->bc.y1, &ph->bc.y2,
	       &ph->bc.z1, &ph->bc.z2);

   if (rc != 6)
   {
      fclose(fp);
      sim_message(none, "Error reading bounding box from file %s.", filename);
      return code_bad;
   }

   ph->vertex = (dpVertexStruct*)simm_malloc(ph->num_vertices*sizeof(dpVertexStruct));
   ph->polygon = (dpPolygonStruct*)simm_malloc(ph->num_polygons*sizeof(dpPolygonStruct));

   if (ph->vertex == NULL || ph->polygon == NULL)
   {
      fclose(fp);
      return code_bad;
   }

   /* read-in the vertices and vertex normals */

   for (i=0; i<ph->num_vertices; i++)
   {
      preread_init_vertex(&ph->vertex[i],i);
      fscanf(fp,"%lf %lf %lf", &ph->vertex[i].coord[0],
         &ph->vertex[i].coord[1], &ph->vertex[i].coord[2]);
      fscanf(fp,"%lf %lf %lf", &ph->vertex[i].normal[0],
         &ph->vertex[i].normal[1], &ph->vertex[i].normal[2]);
      /* In SD/FAST, the origin of a body's reference frame is located at the
       * center of mass. So subtract the coordinates of the center of mass
       * (w.r.t the SIMM reference frame) to get the coords of the bone vertex
       * w.r.t the center of mass. The mass center coords for segment i
       * are located in the body segment array at element i+1 (because ground
       * is -1, but is the 0th element in the array).
       */

      for (j=0; j<3; j++)
         ph->vertex[i].coord[j] -= sdm->body_segment[ph->body_segment+1].mass_center[j];
   }

   /* read-in the polygons (vertex indices) */

   for (i=0; i<ph->num_polygons; i++)
   {
      preread_init_polygon(&ph->polygon[i]);
      fscanf(fp,"%d", &ph->polygon[i].num_vertices);
      ph->polygon[i].vertex_index = (int*)simm_malloc(ph->polygon[i].num_vertices*
         sizeof(int));
      for (j=0; j<ph->polygon[i].num_vertices; j++)
         fscanf(fp,"%d", &ph->polygon[i].vertex_index[j]);
   }

   /* subtract the segment's mass center from the bounding box coordinates */
   ph->bc.x1 -= sdm->body_segment[ph->body_segment+1].mass_center[0];
   ph->bc.x2 -= sdm->body_segment[ph->body_segment+1].mass_center[0];
   ph->bc.y1 -= sdm->body_segment[ph->body_segment+1].mass_center[1];
   ph->bc.y2 -= sdm->body_segment[ph->body_segment+1].mass_center[1];
   ph->bc.z1 -= sdm->body_segment[ph->body_segment+1].mass_center[2];
   ph->bc.z2 -= sdm->body_segment[ph->body_segment+1].mass_center[2];

   fclose(fp);

   return code_fine;
}


static ReturnCode read_old_ascii_file(dpPolyhedronStruct* ph, char filename[])
{
   int i, j, rc;
   FILE* fp;

   fp = simm_fopen(filename,"r");
   if (fp == NULL)
   {
      sim_message(none, "Unable to open file %s.", filename);
      return code_bad;
   }

   rc = fscanf(fp,"%d %d", &ph->num_vertices, &ph->num_polygons);

   if (rc != 2)
   {
      fclose(fp);
      sim_message(none, "Error reading header information from file %s.", filename);
      return code_bad;
   }

   ph->vertex = (dpVertexStruct*)simm_malloc(ph->num_vertices*sizeof(dpVertexStruct));
   ph->polygon = (dpPolygonStruct*)simm_malloc(ph->num_polygons*sizeof(dpPolygonStruct));

   if (ph->vertex == NULL || ph->polygon == NULL)
   {
      fclose(fp);
      return code_bad;
   }

   /* read-in the vertices */

   for (i=0; i<ph->num_vertices; i++)
   {
      preread_init_vertex(&ph->vertex[i],i);
      fscanf(fp,"%lf %lf %lf", &ph->vertex[i].coord[0],
	     &ph->vertex[i].coord[1], &ph->vertex[i].coord[2]);

      /* In SD/FAST, the origin of a body's reference frame is located at the
       * center of mass. So subtract the coordinates of the center of mass
       * (w.r.t the SIMM reference frame) to get the coords of the bone vertex
       * w.r.t the center of mass. The mass center coords for segment i
       * are located in the body segment array at element i+1 (because ground
       * is -1, but is the 0th element in the array).
       */

      for (j=0; j<3; j++)
	      ph->vertex[i].coord[j] -= sdm->body_segment[ph->body_segment+1].mass_center[j];
   }

   /* read-in the polygons (vertex indices) */

   for (i=0; i<ph->num_polygons; i++)
   {
      preread_init_polygon(&ph->polygon[i]);
      fscanf(fp,"%d", &ph->polygon[i].num_vertices);
      ph->polygon[i].vertex_index = (int*)simm_malloc(ph->polygon[i].num_vertices*
         sizeof(int));
      for (j=0; j<ph->polygon[i].num_vertices; j++)
      {
         fscanf(fp,"%d", &ph->polygon[i].vertex_index[j]);
         /* Old ASCII vertex numbers start at 1 */
         ph->polygon[i].vertex_index[j]--;
      }
   }

   /* subtract the segment's mass center from the bounding box coordinates */
   ph->bc.x1 -= sdm->body_segment[ph->body_segment+1].mass_center[0];
   ph->bc.x2 -= sdm->body_segment[ph->body_segment+1].mass_center[0];
   ph->bc.y1 -= sdm->body_segment[ph->body_segment+1].mass_center[1];
   ph->bc.y2 -= sdm->body_segment[ph->body_segment+1].mass_center[1];
   ph->bc.z1 -= sdm->body_segment[ph->body_segment+1].mass_center[2];
   ph->bc.z2 -= sdm->body_segment[ph->body_segment+1].mass_center[2];

   fclose(fp);

   return code_fine;
}


void copy_polyhedron(dpPolyhedronStruct* from, dpPolyhedronStruct* to)
{
   int i;

   mstrcpy(&to->name,from->name);
	to->body_segment = from->body_segment;

   to->num_vertices = from->num_vertices;
   to->vertex = (dpVertexStruct*)simm_malloc(to->num_vertices*sizeof(dpVertexStruct));

   to->num_polygons = from->num_polygons;
   to->polygon = (dpPolygonStruct*)simm_malloc(to->num_polygons*sizeof(dpPolygonStruct));

   for (i=0; i<to->num_vertices; i++)
      copy_vertex(&from->vertex[i],&to->vertex[i]);

   for (i=0; i<to->num_polygons; i++)
      copy_polygon(&from->polygon[i],&to->polygon[i]);

   to->bc.x1 = from->bc.x1;
   to->bc.x2 = from->bc.x2;
   to->bc.y1 = from->bc.y1;
   to->bc.y2 = from->bc.y2;
   to->bc.z1 = from->bc.z1;
   to->bc.z2 = from->bc.z2;
}


static void copy_vertex(dpVertexStruct* from, dpVertexStruct* to)
{
   int i;

   to->coord[0] = from->coord[0];
   to->coord[1] = from->coord[1];
   to->coord[2] = from->coord[2];
   to->normal[0] = from->normal[0];
   to->normal[1] = from->normal[1];
   to->normal[2] = from->normal[2];
   to->polygon_count = from->polygon_count;
   if (to->polygon_count > 0)
   {
      to->polygons = (int*)simm_malloc(to->polygon_count*sizeof(int));
      for (i=0; i<to->polygon_count; i++)
	      to->polygons[i] = from->polygons[i];
   }
   else
   {
      to->polygons = NULL;
   }
}


static void copy_polygon(dpPolygonStruct* from, dpPolygonStruct* to)
{
   int i;

   to->num_vertices = from->num_vertices;
   to->vertex_index = (int*)simm_malloc(to->num_vertices*sizeof(int));
   for (i=0; i<to->num_vertices; i++)
      to->vertex_index[i] = from->vertex_index[i];
   to->normal[0] = from->normal[0];
   to->normal[1] = from->normal[1];
   to->normal[2] = from->normal[2];
   to->d = from->d;
}


static void free_polyhedron(dpPolyhedronStruct* ph, dpBoolean free_ph)
{
   int i;

   FREE_IFNOTNULL(ph->name);

   for (i=0; i<ph->num_vertices; i++)
      FREE_IFNOTNULL(ph->vertex[i].polygons);

   free(ph->vertex);

   for (i=0; i<ph->num_polygons; i++)
      FREE_IFNOTNULL(ph->polygon[i].vertex_index);

   free(ph->polygon);

   if (free_ph == dpYes)
      free(ph);
}


static ReturnCode check_polyhedron(dpPolyhedronStruct* ph)
{
   int i, j;

   for (i=0; i<ph->num_polygons; i++)
   {
      for (j=0; j<ph->polygon[i].num_vertices; j++)
      {
         if (ph->polygon[i].vertex_index[j] >= ph->num_vertices ||
            ph->polygon[i].vertex_index[j] < 0)
         {
            sim_message(abort_action, "Bad polyhedron: vertex index out of range.");
            return code_bad;
         }
      }
   }

   return code_fine;
}


static void calc_polygon_normal(dpPolyhedronStruct* ph, dpPolygonStruct* p)
{

   int i, v1, v2, v3, nv;
   double vec1[3], vec2[3];
   double mag;

   /* Find the first three vertices which are not collinear,
    * and use them to find the surface normal.
    */

   nv = p->num_vertices;

   for (i=0; i<nv; i++)
   {
      v1 = p->vertex_index[i];
      v2 = p->vertex_index[(i+1)%nv];
      v3 = p->vertex_index[(i+2)%nv];

      MAKE_3DVECTOR(ph->vertex[v2].coord,ph->vertex[v3].coord,vec1);
      MAKE_3DVECTOR(ph->vertex[v2].coord,ph->vertex[v1].coord,vec2);

      normalize_vector(vec1,vec1);
      normalize_vector(vec2,vec2);
      cross_vectors(vec1,vec2,p->normal);
      mag = normalize_vector(p->normal,p->normal);
      if (mag >= COLLINEAR_EPSILON)
	      break;
   }

   if (i == nv)
   {
      p->normal[0] = 1.0;
      p->normal[1] = 0.0;
      p->normal[2] = 0.0;
      p->d = 0.0;
   }
   else
   {
      p->d = - ph->vertex[v1].coord[0] * p->normal[0] -
	       ph->vertex[v1].coord[1] * p->normal[1] -
	       ph->vertex[v1].coord[2] * p->normal[2];
   }
}


static void make_vert_poly_lists(dpPolyhedronStruct* ph)
{
   int i, j;
   dpVertexStruct* v;

   for (i=0; i<ph->num_vertices; i++)
   {
      FREE_IFNOTNULL(ph->vertex[i].polygons);
      ph->vertex[i].polygon_count = 0;
   }

   for (i=0; i<ph->num_polygons; i++)
   {
      for (j=0; j<ph->polygon[i].num_vertices; j++)
         ph->vertex[ph->polygon[i].vertex_index[j]].polygon_count++;
   }

   for (i=0; i<ph->num_vertices; i++)
   {
      if (ph->vertex[i].polygon_count == 0)
      {
         ph->vertex[i].polygons = NULL;
      }
      else
      {
         ph->vertex[i].polygons = (int*)simm_malloc(ph->vertex[i].polygon_count*sizeof(int));
         ph->vertex[i].polygon_count = 0;
      }
   }

   for (i=0; i<ph->num_polygons; i++)
   {
      for (j=0; j<ph->polygon[i].num_vertices; j++)
      {
         v = &ph->vertex[ph->polygon[i].vertex_index[j]];
         v->polygons[v->polygon_count++] = i;
      }
   }
}

/* Read in object polyhedron from a bone file.  If the filename is an absolute path,
 * read the file.  If not, if a bone path was specified, read the file from that path.
 * If not, try reading from the current directory, or a subdirectory called "bones".
 */
ReturnCode read_polyhedron(dpPolyhedronStruct* ph, char filename[])
{
   FileType input_file_type;
   ReturnCode code;
   char fullpath[1024];

   preread_init_polyhedron(ph);

   if (is_absolute_path(filename) == dpYes)
   {
      strcpy(fullpath, filename);
      input_file_type = check_file_type(fullpath);
   }
   else if (bone_path != NULL)
   {
      strcpy(fullpath, bone_path);
      append_if_necessary(fullpath, DIR_SEP_CHAR);
      strcat(fullpath, filename);
      input_file_type = check_file_type(fullpath);
   }
   else
   {
      input_file_type = check_file_type(filename);
      strcpy(fullpath, filename);
      if (input_file_type == file_not_found)
      {
         strcpy(fullpath, current_dir);
         append_if_necessary(fullpath, DIR_SEP_CHAR);
         strcat(fullpath, "bones");
         append_if_necessary(fullpath, DIR_SEP_CHAR);
         strcat(fullpath, filename);
         input_file_type = check_file_type(fullpath);
      }
   }

   if (input_file_type == file_not_found)
   {
      sim_message(none, "\tObject file %s not found.", fullpath);
      return code_bad;
   }
   strcpy(filename, fullpath);
   sim_message(none, "Reading object file %s... ", fullpath);

   if (input_file_type == binary)
   {
      code = read_binary_file(ph,filename);
      if (check_polyhedron(ph) == code_bad)
      {
         sim_message(none, "Validity check of object %s failed.", ph->name);
         return code_bad;
      }
      postread_init_polyhedron(ph);
   }
   else if (input_file_type == new_ascii)
   {
      code = read_ascii_file(ph,filename);
      if (check_polyhedron(ph) == code_bad)
      {
         sim_message(none, "Validity check of object %s failed.", ph->name);
         return code_bad;
      }
      postread_init_polyhedron(ph);
   }
   else /* input_file_type == old_ascii or unknown */
   {
      code = read_old_ascii_file(ph,filename);
      if (check_polyhedron(ph) == code_bad)
      {
         sim_message(none, "Validity check of object %s failed.", ph->name);
         return code_bad;
      }
      postread_init_polyhedron(ph);
   }
	sim_message(none, "Done.");

   return code;
}
