/*******************************************************************************

   PIPETOOLS.C

   Authors: Peter Loan
            Krystyne Blaikie

   Copyright (c) 1996-2005 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains routines that implement various
      mathematical functions and other utilities. Every one operates
      exclusively on the formal parameter list, and so does not change any
      external variables or other general model or plot structures.

   Routines:
      mstrcpy                    : copies one string to another, mallocing first
      convert_point              : converts a point from one frame to another
      convert_point2             : alternate version of convert_point
      copy_4x4matrix             : copies a 4x4 matrix
      malloc_function            : mallocs space for a spline function
      realloc_function           : reallocs a spline function
      free_function              : frees a spline function
      make_zero_func             : makes a Y=0.0 2-point spline function
      init_spline_func           : fills in part of a spline function
      finish_spline_func         : finishes setting up a spline function
      setup_spline_structs       : sets up spline structs in MotionData struct
      verify_assembly            : checks gencoord values in assembled model
      vector_intersects_matte    : checks intersection of vector and force matte
      apply_external_forces      : applies external forces and torques to segs
      get_applied_force          : gets current force value from MotionData struct
      get_applied_torque         : gets current torque value from MotionData struct
      set_fixed_gencoords        : prescribed Q,U,A of 'fixed' joints
      set_prescribed_gencoords   : prescribed Q,U,A of 'prescribed' gencoords
      set_prescribed_motion      : turns on/off prescribed motion for certain Qs
      calc_joint_torques         : calcs joint torques for a time step
      calc_initial_joint_torques : calcs joint torques for first two steps
      calc_next_joint_torques    : calcs joint torques for next time step
      calc_corrective_torques    : calcs corrective torque to track motion
      add_torques_to_motion_data : adds data to MotionData to hold ID torques
		apply_joint_restraint_torques : applies torques to restrain joint motion
      get_muscle_param_value     : returns current value of named parameter
      check_for_sderror          : check if any SD/FAST errors have been posted
      init_joints                : initialize joint structure in sdm
      calc_system_energy         : calculates total system energy
      free_motion_data           : frees a MotionData struct

*******************************************************************************/

#include "universal.h"
#include "gcvspl.h"

/*************** DEFINES (for this file only) *********************************/


/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/


/**************** GLOBAL VARIABLES (used in only a few files) *****************/



/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern char buffer[];
extern dpModelStruct* sdm;
extern dpSimulationParameters params;

/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/
static void make_quaternion(Quat q, const double axis[3], double angle);
static void rotate_matrix_by_quat(double m[][4], const Quat q);
static void quat_to_matrix (Quat q, double m[][4]);



/* MSTRCPY: this routine is like strcpy(), but it first mallocs space for
 * the copy of the string.
 */
ReturnCode mstrcpy(char* dest_str[], char original_str[])
{

   if ((*dest_str = 
   	(char*)simm_malloc(STRLEN(original_str)*sizeof(char))) == NULL)
      return (code_bad);

   (void)strcpy(*dest_str,original_str);
   return (code_fine);
}


/* CONVERT_POINT: converts a point from one reference frame to another,
 * overwriting the original point.
 */
void convert_point(double pt[], int frame1, int frame2)
{
   int i;
   double vec[3], pt_g[3], origin_g[3], origin[] = {0.0,0.0,0.0};

   /* Convert pt to the ground frame */
   if (frame1 != GROUND)
   {
      sdpos(frame1,pt,pt_g);
   }
   else
   {
      for (i=0; i<3; i++)
         pt_g[i] = pt[i];
   }

   /* Convert the origin of frame2 to the ground frame */
   if (frame2 != GROUND)
   {
      sdpos(frame2,origin,origin_g);
   }
   else
   {
      for (i=0; i<3; i++)
         origin_g[i] = origin[i];
   }

   /* Form a vector from the origin of frame2 to pt,
    * expressed in the ground frame.
    */
   for (i=0; i<3; i++)
      vec[i] = pt_g[i] - origin_g[i];

   /* Convert vec from the ground frame to frame2,
    * storing the result in pt.
    */
   if (frame2 != GROUND)
      sdtrans(GROUND,vec,frame2,pt);
   else
   {
      for (i=0; i<3; i++)
         pt[i] = vec[i];
   }

}

/* CONVERT_POINT2: converts a point from frame1 to frame2, storing result
 * in separate array.
 */
void convert_point2(int frame1, double p1[], int frame2, double p2[])
{
   double loc1[3], loc2[3], com[3] = {0.0, 0.0, 0.0}, cm2[3];

	sdpos(frame1, p1, loc1);
	sdpos(frame2, com, cm2);
	sdvsub(loc1, cm2, loc2);
	sdtrans(GROUND, loc2, frame2, p2);

}


/* COPY_4x4MATRIX: copies a 4x4 matrix. */
void copy_4x4matrix(double from[][4], double to[][4])
{

   to[0][0] = from[0][0];
   to[0][1] = from[0][1];
   to[0][2] = from[0][2];
   to[0][3] = from[0][3];
   to[1][0] = from[1][0];
   to[1][1] = from[1][1];
   to[1][2] = from[1][2];
   to[1][3] = from[1][3];
   to[2][0] = from[2][0];
   to[2][1] = from[2][1];
   to[2][2] = from[2][2];
   to[2][3] = from[2][3];
   to[3][0] = from[3][0];
   to[3][1] = from[3][1];
   to[3][2] = from[3][2];
   to[3][3] = from[3][3];

}



/* MALLOC_FUNCTION: this routine mallocs space for a spline function. */

ReturnCode malloc_function(dpSplineFunction* func, int numpoints)
{
   if (func == NULL)
      return code_bad;

   func->coefficient_array_size = 0;
   func->defined = dpNo;

   if ((func->x = (double*)simm_calloc(numpoints, sizeof(double))) == NULL)
      return code_bad;
   if ((func->y = (double*)simm_calloc(numpoints, sizeof(double))) == NULL)
      return code_bad;
   if ((func->b = (double*)simm_calloc(numpoints, sizeof(double))) == NULL)
      return code_bad;
   if ((func->c = (double*)simm_calloc(numpoints, sizeof(double))) == NULL)
      return code_bad;
   if ((func->d = (double*)simm_calloc(numpoints, sizeof(double))) == NULL)
      return code_bad;

   func->coefficient_array_size = numpoints;
   func->type = dpNaturalCubic;
   func->defined = dpYes;

   return code_fine;
}



/* REALLOC_FUNCTION: this routine reallocs the arrays in a spline structure. */

ReturnCode realloc_function(dpSplineFunction* func, int size)
{

   ReturnCode rc1, rc2, rc3, rc4, rc5;

   func->x = (double*)simm_realloc(func->x,size*sizeof(double),&rc1);
   func->y = (double*)simm_realloc(func->y,size*sizeof(double),&rc2);
   func->b = (double*)simm_realloc(func->b,size*sizeof(double),&rc3);
   func->c = (double*)simm_realloc(func->c,size*sizeof(double),&rc4);
   func->d = (double*)simm_realloc(func->d,size*sizeof(double),&rc5);

   if (rc1 == code_bad || rc2 == code_bad || rc3 == code_bad || rc4 == code_bad || rc5 == code_bad)
      return code_bad;

   func->coefficient_array_size = size;

   return code_fine;

}

/* FREE_FUNCTION: frees a spline function. */

void free_function(dpSplineFunction* func)
{
   if (func == NULL)
      return;

   FREE_IFNOTNULL(func->x);
   FREE_IFNOTNULL(func->y);
   FREE_IFNOTNULL(func->b);
   FREE_IFNOTNULL(func->c);
   FREE_IFNOTNULL(func->d);

   func->numpoints = func->coefficient_array_size = 0;
   func->defined = dpNo;
}

/* MAKE_ZERO_FUNC: makes a 2-point spline function from min_x to max_x
 * with Y values of 0.0.
 */
ReturnCode make_zero_func(dpSplineFunction* sf, double min_x, double max_x)
{
   int num_points = 2;
   sf->type = dpStepFunction;
   sf->cutoff_frequency = 0.0;
   sf->coefficient_array_size = sf->numpoints = 0;
   sf->defined = dpNo;
   sf->x = sf->y = sf->b = sf->c = sf->d = NULL;

   if ((sf->x = (double*)simm_malloc(num_points * sizeof(double))) == NULL)
      return code_bad;
   if ((sf->y = (double*)simm_malloc(num_points * sizeof(double))) == NULL)
      return code_bad;

   sf->coefficient_array_size = sf->numpoints = num_points;
   sf->defined = dpYes;

   sf->x[0] = min_x;
   sf->x[1] = max_x;

   sf->y[0] = sf->y[1] = 0.0;

   return code_fine;
}


/* INIT_SPLINE_FUNC: this function mallocs space for the X and Y coordinates
 * of a spline function, and fills in the Y coords. It sets the spline type
 * so that later on (in setup_spline_structs()) the X coords can be filled in and
 * the spline coefficients calculated (depending on the type). If type = step_func,
 * then the X and Y coords are used as control points in a step function, not a
 * spline.
 */

ReturnCode init_spline_func(dpSplineFunction* sf, double Ycoords[], int numpoints, dpSplineType type,
                            double cutoffFrequency)
{
   int i;

   sf->type = type;
   sf->cutoff_frequency = cutoffFrequency;
   sf->coefficient_array_size = sf->numpoints = 0;
   sf->defined = dpNo;
   sf->x = sf->y = sf->b = sf->c = sf->d = NULL;

   if ((sf->x = (double*)simm_malloc(numpoints*sizeof(double))) == NULL)
      return code_bad;
   if ((sf->y = (double*)simm_malloc(numpoints*sizeof(double))) == NULL)
      return code_bad;

   if (sf->type == dpNaturalCubic)
   {
      if ((sf->b = (double*)simm_malloc(numpoints*sizeof(double))) == NULL)
         return code_bad;
      if ((sf->c = (double*)simm_malloc(numpoints*sizeof(double))) == NULL)
         return code_bad;
      if ((sf->d = (double*)simm_malloc(numpoints*sizeof(double))) == NULL)
         return code_bad;
   }
   else if (sf->type == dpGCVSpline)
   {
      if ((sf->c = (double*)simm_malloc(numpoints*sizeof(double))) == NULL)
         return code_bad;
   }
	else if (sf->type == dpLinear)
	{
      if ((sf->b = (double*)simm_malloc(numpoints*sizeof(double))) == NULL)
         return code_bad;
	}

   sf->coefficient_array_size = sf->numpoints = numpoints;
   sf->defined = dpYes;

   for (i = 0; i < numpoints; i++)
      sf->y[i] = Ycoords[i];

   return code_fine;
}


/* FINISH_SPLINE_FUNC: this function calculates the spline coordinates, depending
 * on the type. If type = step_func then the data is used as a step function,
 * not a spline.
 */
ReturnCode finish_spline_func(dpSplineFunction* sf)
{
   if (sf == NULL)
      return code_fine;

	if (sf->type == dpLinear)
	{
		int i;

		if (sf->numpoints < 2)
		{
			sim_message(abort_action, "Error: linear function must have at least 2 points.\n");
			return code_bad;
		}

		/* For a linear function, the slope of each segment is stored in the b array. */
		for (i = 0; i < sf->numpoints - 1; i++)
		{
			sf->b[i] = (sf->y[i+1] - sf->y[i]) / (sf->x[i+1] - sf->x[i]);
		}
		sf->b[sf->numpoints - 1] = sf->b[sf->numpoints - 2];
	}
   else if (sf->type == dpNaturalCubic)
   {
      calc_spline_coefficients(sf);
   }
   else if (sf->type == dpGCVSpline)
   {
      int i, ier = 0;
      double val, sampling_rate, *weight_x = NULL, *weight_y = NULL, *work = NULL;
      int mode = 1; // Mode for GCVSPL function chosen to specify smoothing parameter directly
      int order = 5; //5th order for quintic spline
      int half_order = (order + 1) / 2; // GCVSPL works with the half order
      int k = 1; // Only one colum of y data is splined at a time

      sampling_rate = 1.0 / (sf->x[1] - sf->x[0]);

      // Allocate memory as needed
      weight_x = (double*)simm_malloc(sf->numpoints*sizeof(double));
      weight_y = (double*)simm_malloc(1*sizeof(double));
      work = (double*)simm_malloc((6*(sf->numpoints*half_order+1)+sf->numpoints)*sizeof(double));

      // Assign weights
      for (i = 0; i < sf->numpoints; i++)
         weight_x[i] = 1.0;
      weight_y[0] = 1.0;

      // Calculate GCVSPL version of cut-off frequency. If cut-off frequency is <= 0.0,
      // set val = -1.0 so that dpNo smoothing is performed.
      if (sf->cutoff_frequency <= 0.0)
         val = 0.0;
      else
         val = sampling_rate / pow(2.0*M_PI*sf->cutoff_frequency/pow(sqrt(2.0)-1.0,0.5/half_order), 2.0*half_order);

      gcvspl(sf->x, sf->y, &sf->numpoints, weight_x, weight_y, &half_order, 
             &sf->numpoints, &k, &mode, &val, sf->c, &sf->numpoints, work, &ier);

		free(weight_x);
      free(weight_y);
      free(work);

      if (ier > 0)
      {
         if (ier == 1)
            sim_message(abort_action, "GCV spline error: Only %d coordinates specified (%d or more are required).",
                    sf->numpoints, order + 1);
         else if (ier == 2)
            sim_message(abort_action, "GCV spline error: X coordinates do not consistently increase in value.");
         else
            sim_message(abort_action, "Error code returned by gcvspl() = %d.", ier);
         return code_bad;
      }
   }

   return code_fine;
}


/* SETUP_SPLINE_STRUCTS: this function finishes initializing the spline structs
 * in a MotionData struct, after if it has been determined what the X axis is
 * (time, or frame index), and whether each data column should be splined or not.
 */
ReturnCode setup_spline_structs(dpModelStruct* sdm, MotionData* data)
{
   int i, j, k;
   double *time_values;
   ReturnCode rc = code_fine;

   /* Make a temporary array to hold the time coordinates for all data columns */
   time_values = (double*)simm_malloc(data->num_frames * sizeof(double));
   if (time_values == NULL)
      sim_message(exit_program, "Unable to allocate enough memory to read motion file.");

   if (data->time_index >= 0)
   {
      for (i = 0; i < data->num_frames; i++)
         time_values[i] = data->motiondata[data->time_index][i];
   }
   else
   {
      /* If there is no time data, assume that the frames of data should be spread
       * evenly over the entire simulation period, with the first frame starting at
       * the start of the simulation, and the last frame *starting* at the end of
       * the simulation.
       */
      if (EQUAL_WITHIN_ERROR((params.endTime - params.startTime), 0.0))
      {
         params.startTime = 0.0;
         params.endTime = data->num_frames - 1.0;
      }

      for (i = 0; i < data->num_frames; i++)
			time_values[i] = params.startTime + i * (params.endTime - params.startTime) / (data->num_frames - 1);
   }

   /* Now finish setting up the spline structs */
   for (i = 0; i < sdm->nq; i++)
   {
      if (data->q_data[i])
      {
         for (j = 0; j < data->q_data[i]->numpoints; j++)
            data->q_data[i]->x[j] = time_values[j];
         if (finish_spline_func(data->q_data[i]) == code_bad)
            goto error;
      }

      if (data->u_data[i])
      {
         for (j = 0; j < data->u_data[i]->numpoints; j++)
            data->u_data[i]->x[j] = time_values[j];
         if (finish_spline_func(data->u_data[i]) == code_bad)
            goto error;
      }

      if (data->udot_data[i])
      {
         for (j = 0; j < data->udot_data[i]->numpoints; j++)
            data->udot_data[i]->x[j] = time_values[j];
         if (finish_spline_func(data->udot_data[i]) == code_bad)
            goto error;
      }

      if (data->q_torques[i])
      {
         for (j = 0; j < data->q_torques[i]->numpoints; j++)
            data->q_torques[i]->x[j] = time_values[j];
         if (finish_spline_func(data->q_torques[i]) == code_bad)
            goto error;
      }
   }

   for (i = 0; i < data->num_musc_excitations; i++)
   {
      for (j = 0; j < data->musc_excitations[i]->numpoints; j++)
         data->musc_excitations[i]->x[j] = time_values[j];
      if (finish_spline_func(data->musc_excitations[i]) == code_bad)
         goto error;
   }

   /* For forces and torques, some of the individual components may not
    * have been defined in the input file. If a component is not defined,
    * initialize it to a two-point zero function. If it is defined, finish
    * setting it up.
    */
   for (i = 0; i < data->num_forces; i++)
   {
      for (j = 0; j < 3; j++)
      {
         if (data->forces[i]->appl_point[j].defined == dpNo)
         {
            rc = make_zero_func(&data->forces[i]->appl_point[j], time_values[0], time_values[data->num_frames]);
         }
         else
         {
            for (k = 0; k < data->forces[i]->appl_point[j].numpoints; k++)
               data->forces[i]->appl_point[j].x[k] = time_values[k];
            rc = finish_spline_func(&data->forces[i]->appl_point[j]);
         }
         if (rc == code_bad)
            goto error;
      }
      for (j = 0; j < 3; j++)
      {
         if (data->forces[i]->force_vec[j].defined == dpNo)
         {
            rc = make_zero_func(&data->forces[i]->force_vec[j], time_values[0], time_values[data->num_frames]);
         }
         else
         {
            for (k = 0; k < data->forces[i]->force_vec[j].numpoints; k++)
               data->forces[i]->force_vec[j].x[k] = time_values[k];
            rc = finish_spline_func(&data->forces[i]->force_vec[j]);
         }
         if (rc == code_bad)
            goto error;
      }
   }

   for (i = 0; i < data->num_torques; i++)
   {
      for (j = 0; j < 3; j++)
      {
         if (data->torques[i]->torque_vec[j].defined == dpNo)
         {
            rc = make_zero_func(&data->torques[i]->torque_vec[j], time_values[0], time_values[data->num_frames]);
         }
         else
         {
            for (k = 0; k < data->torques[i]->torque_vec[j].numpoints; k++)
               data->torques[i]->torque_vec[j].x[k] = time_values[k];
            rc = finish_spline_func(&data->torques[i]->torque_vec[j]);
         }
         if (rc == code_bad)
            goto error;
      }
   }

   goto cleanup;

error:
   sim_message(recover, "Error setting up spline functions for kinetics data.");
   rc = code_bad;

cleanup:
   free(time_values);

   return rc;

}



/* VERIFY_ASSEMBLY: this routine checks to see if the assembled SD/FAST model has
 * any Qs (gencoords) that violate their allowable ranges of motion. A gencoord
 * is allowed to violate its range of motion if a restraint function is defined
 * for it (the assumption being that the restraint torque will eventually pull
 * the gencoord back into range.
 */

ReturnCode verify_assembly(dpModelStruct* sdm, double state[])
{
   int i;
   dpBoolean valid = dpYes;

   for (i=0; i<sdm->nq; i++)
   {
      if (sdm->q[i].type != dpUnconstrainedQ)
         continue;
      if ((sdm->q[i].restraint_func == NULL) &&
         ((state[i]*sdm->q[i].conversion < sdm->q[i].range_start && sdm->q[i].min_restraint_func == NULL) ||
         (state[i]*sdm->q[i].conversion > sdm->q[i].range_end && sdm->q[i].max_restraint_func == NULL)))
      {
         sim_message(none, "%s out of range: value = %lf, range = %lf to %lf.",
            sdm->q[i].name, state[i]*sdm->q[i].conversion, sdm->q[i].range_start, sdm->q[i].range_end);
         valid = dpNo;
      }
   }

   if (valid == dpNo)
   {
      sim_message(none, "Assembly invalid.");
      return code_bad;
   }

   return code_fine;
}


/* VECTOR_INTERSECTS_MATTE: This function checks for intersection of a vector
 * and a 'force matte,' which is a planar polygon stored in a ForceMatte struct.
 */
dpBoolean vector_intersects_matte(double pt[], double vec[], dpForceMatte* fm, double inter[])
{
   int i;
   double pt2[3], t;

   pt2[0] = pt[0] + vec[0];
   pt2[1] = pt[1] + vec[1];
   pt2[2] = pt[2] + vec[2];

   /* Check to see if the vector intersects any of the polygons in the force matte.
    * intersect_line_plane() is used to get the point of intersection between the
    * vector and the plane of the polygon, and then this point is checked to see if
    * it is inside the boundaries of the polygon. Return the first intersection found.
    */
   for (i = 0; i < fm->ph->num_polygons; i++)
   {
      if (intersect_line_plane(pt, pt2, fm->ph->polygon[i].normal, fm->ph->polygon[i].d, inter, &t) == dpYes &&
         point_in_polygon3D(inter, fm->ph, i) == dpYes)
      {
         return dpYes;
      }
   }

   return dpNo;
}


/* APPLY_EXTERNAL_FORCES: This routine applies external, user-defined forces
 * and torques. A typical example of an external force is a ground-reaction.
 * force. The forces and torques are specified in a data file and are loaded
 * into a MotionData structure.  External forces in the struct are expected
 * to be with respect to the body segment origins, not their mass centers.
 * Therefore, the mass center coordinates are subtracted from the points
 * of application when the forces are applied.
 */

void apply_external_forces(double time, MotionData* data)
{

   int i, j;
   double appl_point[3], force_vec[3], torque_vec[3], intersectpt[3], appl_point2[3], force_vec2[3];

   /* Apply point forces to the body segments */
   for (i = 0; i < data->num_forces; i++)
   {
      get_applied_force(time, data, i, appl_point, force_vec);
      sdvsub(appl_point, sdm->body_segment[data->forces[i]->segment + 1].mass_center, appl_point);

      /* Forces applied to the ground segment have no effect on the simulation.
       * So assume that all ground forces should be applied to other body segments
       * using the force matte mechanism. The force vector at each time step is
       * checked for intersection with an array of force mattes (polygons defined in
       * PolyhedronStructs). If the force vector intersects a segment's force matte,
       * apply the force to that segment.
       */
      if (data->forces[i]->segment == GROUND)
      {
         /* Intersect the force vector with the force mattes. */
         for (j = 0; j < sdm->num_force_mattes; j++)
         {
            sdtrans(GROUND, force_vec, sdm->force_matte[j].segment, force_vec2);
            sdvcopy(appl_point, appl_point2);
            convert_point(appl_point2, GROUND, sdm->force_matte[j].segment);
            if (vector_intersects_matte(appl_point2, force_vec2, &sdm->force_matte[j], intersectpt) == dpYes)
            {
               /* Apply the force, and break so that no other mattes are checked. */
               sdpointf(sdm->force_matte[j].segment, appl_point2, force_vec2);
               break;
            }
         }
      }
      else
      {
         sdpointf(data->forces[i]->segment, appl_point, force_vec);
      }
   }

   /* Apply torques to the body segments */
   for (i = 0; i < data->num_torques; i++)
   {
      get_applied_torque(time, data, i, torque_vec);
      sdbodyt(data->torques[i]->segment, torque_vec);
   }

   /* Apply torques/forces to the Qs */
   for (i = 0; i < sdm->nq; i++)
   {
      if (data->q_torques[i])
		{
			sdm->q[i].torque = interpolate_spline(time, data->q_torques[i], zeroth, 1.0, 0.0);
         sdhinget(sdm->q[i].joint, sdm->q[i].axis, sdm->q[i].torque);
		}
   }
}



/* GET_APPLIED_FORCE: this function gets the current value of force in a MotionData struct.
 * It uses the current simulation time to get the value, as the X coordinate of the force
 * spline functions is time. Interpolate_spline can model both a cubic spline and a step
 * function.
 */

void get_applied_force(double time, MotionData* data, int frc_index, double appl_point[], double force_vec[])
{
   appl_point[XX] = interpolate_spline(time, &data->forces[frc_index]->appl_point[XX], zeroth, 1.0, 0.0);
   appl_point[YY] = interpolate_spline(time, &data->forces[frc_index]->appl_point[YY], zeroth, 1.0, 0.0);
   appl_point[ZZ] = interpolate_spline(time, &data->forces[frc_index]->appl_point[ZZ], zeroth, 1.0, 0.0);
   force_vec[XX] = interpolate_spline(time, &data->forces[frc_index]->force_vec[XX], zeroth, 1.0, 0.0);
   force_vec[YY] = interpolate_spline(time, &data->forces[frc_index]->force_vec[YY], zeroth, 1.0, 0.0);
   force_vec[ZZ] = interpolate_spline(time, &data->forces[frc_index]->force_vec[ZZ], zeroth, 1.0, 0.0);
}



/* GET_APPLIED_TORQUE: this function gets the current value of torque in a MotionData struct.
 * It uses the current simulation time to get the value, as the X coordinate of the torque
 * spline functions is time. Interpolate_spline can model both a cubic spline and a step
 * function.
 */

void get_applied_torque(double time, MotionData* data, int trq_index, double torque_vec[])
{
   torque_vec[XX] = interpolate_spline(time, &data->torques[trq_index]->torque_vec[XX], zeroth, 1.0, 0.0);
   torque_vec[YY] = interpolate_spline(time, &data->torques[trq_index]->torque_vec[YY], zeroth, 1.0, 0.0);
   torque_vec[ZZ] = interpolate_spline(time, &data->torques[trq_index]->torque_vec[ZZ], zeroth, 1.0, 0.0);
}



/* SET_FIXED_GENCOORDS: This routine prescribes the position, velocity, and
 * acceleration of the fixed gencoords in the model. Fixed gencorods are
 * used to implement joints in SD/FAST that should be fixed, but cannot be
 * modeled that way. Instead, a fixed joint is modeled as a pin joint whose
 * motion is prescribed to be zero.
 */

void set_fixed_gencoords(dpModelStruct* sdm)
{

   int i;

   /* for all fixed gencoords:
    *   pos = initial value
    *   vel = 0.0
    *   acc = 0.0
    */
   for (i = 0; i < sdm->nq; i++)
   {
      if (sdm->q[i].type == dpFixedQ)
      {
         sdprespos(sdm->q[i].joint, sdm->q[i].axis, sdm->q[i].initial_value / sdm->q[i].conversion);
         sdpresvel(sdm->q[i].joint, sdm->q[i].axis, 0.0);
         sdpresacc(sdm->q[i].joint, sdm->q[i].axis, 0.0);
      }
   }

}


/* SET_PRESCRIBED_GENCOORDS: This routine prescribes the position, velocity, and
 * acceleration of the prescribed gencoords in the model, using data from the kinetics
 * file. Position data must be explicitly specified (though it can be splined or not).
 * Velocity can either be specified explicitly, or calculated from position (if position
 * data is splined). Acceleration can be specified explicitly or calculated from position
 * or velocity.
 */

void set_prescribed_gencoords(double time, double q[], double u[], dpModelStruct* sdm, MotionData* data)
{
   int i;
   double Q, U, A;

   /* set the position, velocity, and acceleration for all prescribed gencoords */
   for (i = 0; i < sdm->nq; i++)
   {
      if (sdm->q[i].type == dpPrescribedQ)
      {
         if (data && data->q_data[i])
         {
            Q = interpolate_spline(time, data->q_data[i], zeroth, 0.0, 0.0) / sdm->q[i].conversion;

            if (data->u_data[i])
               U = interpolate_spline(time, data->u_data[i], zeroth, 1.0, 0.0) / sdm->q[i].conversion;
            else if (data->q_data[i]->type != dpStepFunction)
               U = interpolate_spline(time, data->q_data[i], first, 1.0, 0.0) / sdm->q[i].conversion;
            else
               U = 0.0;

            if (data->udot_data[i])
               A = interpolate_spline(time, data->udot_data[i], zeroth, 1.0, 0.0) / sdm->q[i].conversion;
            else if (data->u_data[i] && data->u_data[i]->type != dpStepFunction)
               A = interpolate_spline(time, data->u_data[i], first, 1.0, 0.0) / sdm->q[i].conversion;
            else if (data->q_data[i]->type != dpStepFunction)
               A = interpolate_spline(time, data->q_data[i], second, 1.0, 0.0) / sdm->q[i].conversion;
            else
               A = 0.0;

            sdprespos(sdm->q[i].joint, sdm->q[i].axis, Q);
            sdpresvel(sdm->q[i].joint, sdm->q[i].axis, U);
            sdpresacc(sdm->q[i].joint, sdm->q[i].axis, A);
         }
         else
         {
            /* If the Q is prescribed but there is no data for it in the kinetics
             * file, then prescribe it to remain fixed at its initial value. This
             * is the mechanism used to handle Qs which are locked in SIMM.
             */
            sdprespos(sdm->q[i].joint, sdm->q[i].axis, sdm->q[i].initial_value / sdm->q[i].conversion);
            sdpresvel(sdm->q[i].joint, sdm->q[i].axis, 0.0);
            sdpresacc(sdm->q[i].joint, sdm->q[i].axis, 0.0);
         }
      }
   }

   check_for_sderror("SDUMOTION");
}


/* SET_PRESCRIBED_MOTION: This routine turns on/off prescribed motion for all 
 * the Qs of the specified type.
 */
void set_prescribed_motion(dpModelStruct* sdm, dpQType type, int value)
{
   int i, pres;

	/* use NU instead of NQ: don't want to try to set 4th quaternion axes */
	for (i = 0; i < sdm->nu; i++)
	{
      if (sdm->q[i].type == type)
      {
         /* Get the current state (prescribed/unprescribed) of the Q, and try to
          * change it only if it needs changing.
          */
         sdgetpres(sdm->q[i].joint, sdm->q[i].axis, &pres);
         if (value != pres)
            sdpres(sdm->q[i].joint, sdm->q[i].axis, value);
         if (check_for_sderror("SET_PRESCRIBED_MOTION") == 19)
            fprintf(stderr,"Unable to change prescribed state of %s\n", sdm->q[i].name);
      }
	}
}


/* CALC_JOINT_TORQUES: this function calculates the torques on the Qs that result from
 * the user-specified prescribed motion. It first applies all user-defined forces
 * (muscles, restraint torques, spring forces, body forces and torques, etc.) and then
 * calculates the *additional* forces/torques needed to produce the accelerations in the
 * prescribed motion. If you prescribe the motion of the system while applying muscle
 * forces or joint torques that exactly produce that motion, this function will
 * calculate and return joint torques of zero.
 * The calculated joint torques are written to the motion file if the output_joint_torques
 * parameter is set to "dpYes" in the parameters file.
 */
void calc_joint_torques(double time, double state[], double dy[])
{
	int i, info[50];
	double *mults, *mults2, *torques;
	int rank, *multmap;

   /* Allocate space */
	mults = (double*)simm_calloc(sdm->num_constraints, sizeof(double));
	mults2 = (double*)simm_malloc(sdm->num_constraints*sizeof(double));
	multmap = (int*)simm_malloc(sdm->num_constraints*sizeof(int));
	torques = (double*)simm_malloc(sdm->nq*sizeof(double));

   /* Get the multipliers for the current system state. These multipliers are the
    * torques that were applied to the Qs at the end of the last integration step.
    */
   sdmult(mults2, &rank, multmap);

   /* Form a new multiplier array with non-zero multipliers for the constrained
    * Qs and the loop constraints (if there are any closed loops). This is done
    * so that sdfulltrq() will return zero torques for those Qs, and non-zero
    * torques for the unconstrained ones (and the fixed ones, but those are not
    * output).
    */
   for (i = 0; i < sdm->nq; i++)
   {
      if (sdm->q[i].constraint_num != -1)
      {
         /* get the index of the multiplier for this Q's constraint (stored in info[1]) */
         sdcons(sdm->q[i].constraint_num, info);
         
         /* copy this multiplier to the new array */
         mults[info[1]] = mults2[info[1]];
      }
   }

   /* Now copy over the multipliers for the loop constraints. */
   if (sdm->num_closed_loops > 0)
   {
      int start = sdm->num_constraints - sdm->num_user_constraints -
                  6 * sdm->num_closed_loops;
      int end = sdm->num_constraints - sdm->num_user_constraints;

      for (i = start; i < end; i++)
         mults[i] = mults2[i];
   }

   /* Reset the system to the state for which you want the torques. */
   sdstate(time, state, &state[sdm->nq]);

   /* Apply all user forces, including external forces, muscle forces, and spring forces.
    * This must be done because these forces are included in the multipliers. If you do
    * not include them, you will get non-zero forces/torques at the constrained Qs.
    */
   sduforce(time, state, &state[sdm->nq]);

   /* Get the joint torques. */
   sdfulltrq(&dy[sdm->nq], mults, torques);

   /* Store the torques in the SDM structure */
   for (i = 0; i < sdm->nq; i++)
      sdm->q[i].torque = torques[i] * DSIGN(sdm->q[i].conversion);

	free(mults);
	free(mults2);
	free(multmap);
	free(torques);

	check_for_sderror("CALC_JOINT_TORQUES");
}


/* CALC_INITIAL_JOINT_TORQUES: at the start of an inverse simulation, this function
 * calls calc_joint_torques() for the first and second time steps and stores the
 * torques in the q_torques[] array in the MotionData structure. This is done so
 * that the simulation knows what torques to apply during the first integration
 * interval, before any corrective torques have been calculated.
 */
void calc_initial_joint_torques(double time, double state[], double dy[], MotionData* data)
{
	int i;
	double param[1] = {-1.0};
	int status;

	set_prescribed_motion(sdm, dpPrescribedQ, 1);
	sdm->newInverseSimulation = dpNo;

	/* Calculate the torques for the second time step before the first. This is
	 * done so that when calc_initial_joint_torques() exits the torques for the first
	 * time step will be left in sdm->q[].torque, so that they can be written to
	 * the output motion file and used by the static muscle optimization function.
	 */
	calc_derivatives(time + params.stepSize, state, dy, param, &status);
	calc_joint_torques(time + params.stepSize, state, dy);

	/* Store the torques in the motion data structure. */
   for (i = 0; i < sdm->nq; i++)
	{
      if (data->q_torques[i])
		{
			dpSplineFunction* sf = data->q_torques[i];

			sf->y[1] = sdm->q[i].torque;
		}
	}

	/* Now calculate the torques for the first time step. */
	calc_derivatives(time, state, dy, param, &status);
	calc_joint_torques(time, state, dy);

	/* Store the torques in the motion data structure. Also
	 * compute the b (slope) coefficients, which depend on the
	 * y values in the first two frames.
	 */
   for (i = 0; i < sdm->nq; i++)
	{
      if (data->q_torques[i])
		{
			dpSplineFunction* sf = data->q_torques[i];

			sf->y[0] = sdm->q[i].torque;
			sf->b[0] = (sf->y[1] - sf->y[0]) / (sf->x[1] - sf->x[0]);
		}
	}

	set_prescribed_motion(sdm, dpPrescribedQ, 0);
	sdm->newInverseSimulation = dpYes;
}


/* CALC_NEXT_JOINT_TORQUES: similar to calc_joint_torques(), but calculates
 * the torques for the next time step after the current one. This is done
 * so that the inverse simulation knows what torques to apply for the
 * next integration period.
 */
void calc_next_joint_torques(double time, double state[], double dy[], MotionData* data)
{
	int i, j, status;
	double *savedState, *savedDy;
	double param[1] = {-1.0};

   /* Save the current state vector so you can restore it later. */
	savedState = (double*)simm_malloc(sdm->neq*sizeof(double));
	savedDy = (double*)simm_malloc(sdm->neq*sizeof(double));
	memcpy(savedState, state, sdm->neq * sizeof(double));
	memcpy(savedDy, state, sdm->neq * sizeof(double));

   /* Enable prescribed motion for the prescribed gencoords,
    * then prescribe them according to the data from the time
	 * step after the current one.
	 */
	sdm->newInverseSimulation = dpNo;
	set_prescribed_motion(sdm, dpPrescribedQ, 1);
	calc_derivatives(time + params.stepSize, state, dy, param, &status);

   /* Now calculate the torques required to achieve the
    * accelerations at this next time step.
	 */
	calc_joint_torques(time + params.stepSize, state, dy);

   /* Store the torques in the q_torque[] functions,
    * putting them in the appropriate time step. There is
	 * no need to adjust the function coefficients (the
	 * b[] array for dpLinear) because they will be calculated
	 * after the "corrective" torque has been added later.
	 */
	for (i = 0; i < sdm->nq; i++)
	{
		if (data->q_torques[i])
		{
		   dpSplineFunction* sf = data->q_torques[i];

			for (j = 0; j < sf->numpoints; j++)
		   {
				if (EQUAL_WITHIN_TOLERANCE(time + params.stepSize, sf->x[j], 0.0001))
			   {
					sf->y[j] = sdm->q[i].torque;
			   }
		   }
		}
	}

	/* Disable prescribed motion and restore the state
	 * to the saved one.
	 */
   set_prescribed_motion(sdm, dpPrescribedQ, 0);
   sdm->newInverseSimulation = dpYes;
   sdstate(time, savedState, &savedState[sdm->nq]);

   free(savedState);
   free(savedDy);
}


/* CALC_CORRECTIVE_TORQUES: this function calculates the additional torque needed at each
 * gencoord to keep the model tracking the input motion during an inverse simulation.
 * At each time step, the error between the actual and desired kinematics is calculated
 * and used to determine a corrective torque. This torque is added to the applied torque
 * (stored in the MotionData structure) at the *next* time step, so that during the
 * next integration interval that torque can be applied (usually with a piece-wise linear
 * interpolation).
 */
void calc_corrective_torques(double time, double q[], double u[], dpModelStruct* sdm, MotionData* data)
{
   int i, j;
   double desQ, desU, errQ, errU;
	double k1, k2, correctiveTorque;
	dpSplineFunction* sf;

   for (i = 0; i < sdm->nq; i++)
   {
		/* Corrective torques are calculated only for Qs which have kinematic data
		 * to track as well as a torque function to hold the applied torque.
		 */
		if (data && data->q_data[i] && data->q_torques[i] && sdm->q[i].type == dpPrescribedQ)
		{
			/* Calculate the desired kinematics: desQ, desU. */
			desQ = interpolate_spline(time, data->q_data[i], zeroth, 0.0, 0.0) / sdm->q[i].conversion;

			if (data->u_data[i])
				desU = interpolate_spline(time, data->u_data[i], zeroth, 1.0, 0.0) / sdm->q[i].conversion;
			else if (data->q_data[i]->type != dpStepFunction)
				desU = interpolate_spline(time, data->q_data[i], first, 1.0, 0.0) / sdm->q[i].conversion;
			else
				desU = 0.0;

			/* The error is the desired minus the actual kinematics. */
			errQ = desQ - q[i];
			errU = desU - u[i];

			k1 = sdm->q[i].pd_stiffness;
			k2 = 2.0 * sqrt(k1);

			/* Calculate the corrective torque and add it to the q_torques[]
			 * function holding this gencoord's applied torque. The corrective
			 * torque is added to the torque value at the next step, not the
			 * current one (because that torque has already been applied).
			 */
			correctiveTorque = k1 * errQ + k2 * errU;

			sf = data->q_torques[i];

			for (j = 0; j < sf->numpoints; j++)
			{
				if (EQUAL_WITHIN_TOLERANCE(time + params.stepSize, sf->x[j], 0.00001))
				{
					sf->y[j] += correctiveTorque;
					if (j - 1 >= 0)
						sf->b[j-1] = (sf->y[j] - sf->y[j-1]) / (sf->x[j] - sf->x[j-1]);
					if (j < sf->numpoints - 1)
						sf->b[j] = (sf->y[j+1] - sf->y[j]) / (sf->x[j+1] - sf->x[j]);

					/* Now store the original+corrected torques from the current time
					 * step (the one before the one calculated in this function) in the
					 * sdm->q[] array so that they can be written to the output motion
					 * file and also used by the static muscle optimization function.
					 */
					if (j > 0)
						sdm->q[i].torque = sf->y[j - 1];
					break;
				}
			}
		}
	}
}


/* ADD_TORQUES_TO_MOTION_DATA: this function makes sure there is a
 * function in q_torques[] for each gencoord whose motion is prescribed.
 * During an inverse simulation, the torques for each gencoord are
 * calculated and stored in these functions so they can be applied
 * to the gencoords to make the model track the input motion. If the
 * user changed params.stepSize away from the default value (the
 * time increment in the input gencoord data), then these functions
 * will not have the same number of points as the gencoord functions.
 */
void add_torques_to_motion_data(dpModelStruct* sdm, MotionData* data)
{
	int i, j, numTorqueFrames;
	double *initialY;

	/* Add 1.99999 to account for the first frame of data, and any fraction of
	 * a time step at the end of the simulation.
	 */
	numTorqueFrames = (params.endTime - params.startTime) / params.stepSize + 1.99999;

	initialY = (double*)simm_calloc(numTorqueFrames, sizeof(double));

	for (i = 0; i < sdm->nq; i++)
	{
		if (data->q_torques[i] == NULL && sdm->q[i].type == dpPrescribedQ)
		{
			data->q_torques[i] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
			init_spline_func(data->q_torques[i], initialY, numTorqueFrames, dpLinear, 0);
			for (j = 0; j < numTorqueFrames - 1; j++)
			{
				data->q_torques[i]->x[j] = params.startTime + j * params.stepSize;
				data->q_torques[i]->b[j] = 0.0;
			}
			/* The last time frame should be at exactly the end time. */
			data->q_torques[i]->x[numTorqueFrames - 1] = params.endTime;
			data->q_torques[i]->b[numTorqueFrames - 1] = 0.0;
		}
	}

	free(initialY);
}


/* APPLY_JOINT_RESTRAINT_TORQUES: This routine uses the user-defined restraint torque
 * functions to apply torques to the degrees of freedom in order to keep them from
 * going out of the desirable ranges of motion. The new method of specifying restraint
 * torques uses one function (restraint_func) which covers the complete range of motion
 * as well as off both ends. If this function is defined, use it, otherwise use the
 * old method (min_restraint_func and max_restraint_func).
 *   If you want to include damping in the restraint torques, then uncomment the
 * appropriate lines in the function, and set the dampingFactor to the desired value.
 */

void apply_joint_restraint_torques(dpModelStruct* sdm, double state[], double dstate[])
{

   int i;
   double state_value, difference, torque, dampingFactor = 1.0;

   for (i=0; i<sdm->nq; i++)
   {
      if (sdm->q[i].type == dpUnconstrainedQ || sdm->q[i].type == dpPrescribedQ)
      {
         state_value = state[i]*sdm->q[i].conversion;
         if ((sdm->q[i].restraint_func != NULL) && (sdm->q[i].function_active == dpYes))
         {
            torque = interpolate_spline(state_value, sdm->q[i].restraint_func,zeroth, 1.0, 1.0);
            /* Because the torque in this case is applied for all gencoord values
             * (though it's usually zero within the range of motion), you only want
             * to include the damping term when the torque is not zero.
             */
            //if (NOT_EQUAL_WITHIN_ERROR(torque, 0.0))
               //torque -= dampingFactor * dstate[i];
            sdhinget(sdm->q[i].joint,sdm->q[i].axis,torque);
         }
         else if (state_value < sdm->q[i].range_start && sdm->q[i].min_restraint_func != NULL)
         {
            difference = sdm->q[i].range_start - state_value;
            torque = interpolate_spline(difference, sdm->q[i].min_restraint_func, zeroth, 1.0, 1.0);
            //torque -= dampingFactor * dstate[i];
            sdhinget(sdm->q[i].joint,sdm->q[i].axis,torque);
         }
         else if (state_value > sdm->q[i].range_end && sdm->q[i].max_restraint_func != NULL)
         {
            difference = state_value - sdm->q[i].range_end;
            torque = -interpolate_spline(difference, sdm->q[i].max_restraint_func, zeroth, 1.0, 1.0);
            //torque -= dampingFactor * dstate[i];
            sdhinget(sdm->q[i].joint,sdm->q[i].axis,torque);
         }
      }
   }

}


/* GET_MUSCLE_PARAM_VALUE: This routine gives the Pipeline programmer access to the
 * muscle parameters. Since the parameters used in the dynamics code are defined
 * at runtime, the programmer who writes the muscle model code in derivs.c cannot
 * just access the parameters by looking into the muscle structure. Instead, one
 * must pass the name of the parameter into this routine, which returns the value
 * for that parameter. For completeness, this routine also gives access to the
 * SIMM/static parameters (e.g. max_isometric_force), although this routine is not
 * required for this access.
 */

double get_muscle_param_value(dpMuscleStruct* ms, char param_name[])
{
   int i;

   for (i=0; i<ms->num_dynamic_params; i++)
   {
      if (STRINGS_ARE_EQUAL(param_name,ms->dynamic_param_names[i]))
      {
         if (ms->dynamic_params[i] == NULL)
         {
            sim_message(none, "Error: %s was not specified for muscle %s.", param_name, ms->name);
            return 0.0;
         }
         else
         {
            return *ms->dynamic_params[i];
         }
      }
   }

   if (STRINGS_ARE_EQUAL(param_name,"max_force"))
   {
      if (ms->max_isometric_force == NULL)
      {
         sim_message(none, "Error: %s was not specified for muscle %s.", param_name, ms->name);
         return 0.0;
      }
      else
      {
         return *ms->max_isometric_force;
      }
   }

   if (STRINGS_ARE_EQUAL(param_name,"pennation_angle"))
   {
      if (ms->pennation_angle == NULL)
      {
         sim_message(none, "Error: %s was not specified for muscle %s.", param_name, ms->name);
         return 0.0;
      }
      else
      {
         return *ms->pennation_angle;
      }
   }

   if (STRINGS_ARE_EQUAL(param_name,"optimal_fiber_length"))
   {
      if (ms->optimal_fiber_length == NULL)
      {
         sim_message(none, "Error: %s was not specified for muscle %s.", param_name, ms->name);
         return 0.0;
      }
      else
      {
         return *ms->optimal_fiber_length;
      }
   }

   if (STRINGS_ARE_EQUAL(param_name,"tendon_slack_length"))
   {
      if (ms->resting_tendon_length == NULL)
      {
         sim_message(none, "Error: %s was not specified for muscle %s.", param_name, ms->name);
         return 0.0;
      }
      else
      {
         return *ms->resting_tendon_length;
      }
   }

   if (STRINGS_ARE_EQUAL(param_name,"max_contraction_velocity"))
   {
      if (ms->max_contraction_vel == NULL)
      {
         sim_message(none, "Error: %s was not specified for muscle %s.", param_name, ms->name);
         return 0.0;
      }
      else
      {
         return *ms->max_contraction_vel;
      }
   }

   sim_message(none, "Error: attempted to access undefined muscle parameter (%s).", param_name);
   return 0.0;
}


/* GET_MUSCLE_PARAM_INDEX: This function is similar to get_muscle_param_value(),
 * but returns the index of the parameter, so it can be stored for faster access
 * later.
 */

int get_muscle_param_index(dpMuscleStruct* ms, char param_name[])
{
	int i;

	for (i = 0; i < ms->num_dynamic_params; i++)
	{
		if (STRINGS_ARE_EQUAL(param_name, ms->dynamic_param_names[i]))
		{
			return i;
		}
	}

	sim_message(none, "Error: %s was not specified for muscle %s.", param_name, ms->name);

	return 0; // should probably return -1, but other code may not handle it properly
}

/* Display any posted SD/FAST error messages with the name of the function
 * in which they occurred. Clear the errors. */
int check_for_sderror(char caller[])
{
   int routine, err;

   sderror(&routine, &err);

   switch (err)
   {
      case 0:
         break;
      case 19:
         sim_message(none, "%s: trying to set a non-? parameter.", caller);
         break;
      default:
         sim_message(none, "%s:", caller);
         sdprinterr(stdout);
         break;
   }
   sdclearerr();

   return err;
}


/* initialize the joint records.
 */
void init_joints(void)
{
   int info[50], slider[6], i, j;
   int axis, num_axes, q;
   double pin[3];
   
   sdm->joint = (dpJointStruct*)simm_malloc(sdm->num_joints*sizeof(dpJointStruct));
   for (i = 0; i < sdm->num_joints; i++)
   {
      sdjnt(i, info, slider);
      
      sdm->joint[i].inboard_body = info[2];
      sdm->joint[i].outboard_body = info[3];
      sdm->joint[i].first_q = info[7];
      sdm->joint[i].dof = info[4];
      sdm->joint[i].quat = info[8];
      sdm->joint[i].loop_joint = dpNo;
      for (j = 0; j < 6; j++)
      {
         if (slider[j] == 0)
            sdm->joint[i].dof_type[j] = dpRotational;
         else if (slider[j] == 1)
            sdm->joint[i].dof_type[j] = dpTranslational;
         else
            sdm->joint[i].dof_type[j] = dpNoDof;
      }
      switch(info[0])
      {
         case(1):
            sdm->joint[i].jnt_type = dpPin;
            break;
         case(2):
            sdm->joint[i].jnt_type = dpUniversal;
            break;
         case(3):
            sdm->joint[i].jnt_type = dpGimbal;
            break;
         case(4):
            sdm->joint[i].jnt_type = dpBall;
            break;
         case(5):
            sdm->joint[i].jnt_type = dpSlider;
            break;
         case(6):
            sdm->joint[i].jnt_type = dpFree;
            break;
         case(7):
            sdm->joint[i].jnt_type = dpCylindrical;
            break;
         case(8):
            sdm->joint[i].jnt_type = dpPlanar;
            break;
         case(9):
            sdm->joint[i].jnt_type = dpWeld;
            sdm->joint[i].loop_joint = dpYes;
            break;
         case(10):
            sdm->joint[i].jnt_type = dpBushing;
            break;
         case(11):
            sdm->joint[i].jnt_type = dpBearing;
            break;
         case(20):
            sdm->joint[i].jnt_type = dpReversePlanar;
            break;
         case(21):
            sdm->joint[i].jnt_type = dpReverseFree;
            break;
         case(22):
            sdm->joint[i].jnt_type = dpReverseBushing;
            break;
         case(23):
            sdm->joint[i].jnt_type = dpReverseBearing;
            break;
         default:
            sdm->joint[i].jnt_type = dpUnknownJoint;
            break;
      }
      
      num_axes = sdm->joint[i].dof;
      for (j = 0; j < num_axes; j++)
      {
         if (j < 3) axis = j;
         else axis = j - 3;
         q = sdm->joint[i].first_q + j;
         sdgetpin(i, axis, pin);
         sdvcopy(pin, sdm->joint[i].axes[j]);
      }
      for (j = 0; j < 3; j++)
         sdm->joint[i].force[j] = sdm->joint[i].torque[j] = 0.0;		
   }

}


/* CALC_SYSTEM_ENERGY: this routine calculates the total energy of the body
 * segments in the system. It does not keep track of the energy that the
 * muscles add/remove from the system, so if any muscles in the model generate
 * force, or if there are non-energy-conserving collisions, system energy will
 * not be conserved.
 */
void calc_system_energy(SystemInfo* si)
{

	sdmom(si->linear_momentum, si->angular_momentum, &si->kinetic_energy);	
	sdgetgrav(si->gravity);
	sdsys(&si->mass, si->mass_center, si->inertia);

   si->potential_energy = -(si->mass_center[1]) * si->gravity[1] * si->mass;
	si->system_energy = si->kinetic_energy + si->potential_energy;

   /* If initial_system_energy has not yet been set, set it. */
   if (EQUAL_WITHIN_ERROR(si->initial_system_energy,MINMDOUBLE))
      si->initial_system_energy = si->system_energy;

}

/* FREE_MOTION_DATA: frees a MotionData struct. */

void free_motion_data(MotionData* md)
{
   if (md)
   {
      int i;

      FREE_IFNOTNULL(md->name);

      for (i = 0; i < md->num_elements; i++)
      {
         FREE_IFNOTNULL(md->elementnames[i]);
         FREE_IFNOTNULL(md->motiondata[i]);
      }
      FREE_IFNOTNULL(md->elementnames);
      FREE_IFNOTNULL(md->motiondata);

      FREE_IFNOTNULL(md->q_data);
      FREE_IFNOTNULL(md->u_data);
      FREE_IFNOTNULL(md->udot_data);
      FREE_IFNOTNULL(md->q_torques);
      FREE_IFNOTNULL(md->musc_excitations);

      for (i = 0; i < md->num_forces; i++)
         FREE_IFNOTNULL(md->forces[i]);
      FREE_IFNOTNULL(md->forces);

      for (i = 0; i < md->num_torques; i++)
         FREE_IFNOTNULL(md->torques[i]);
      FREE_IFNOTNULL(md->torques);
   }
}
