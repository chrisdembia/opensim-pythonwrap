/*******************************************************************************

   OUTPUT.C

   Authors: Krystyne Blaikie
            Peter Loan

   Copyright (c) 2000-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains functions that write out simulation variables
      to data files and the shell window.

   Routines:
   get_reaction_forces        : determine joint reaction forces and torques
   print_simulation_info      : print step info to screen
   print_final_information    : print information at end of simulation
   set_up_motion_file         : open motion file and write header and column names
   store_motion_frame         : write information to motion and also to file
   set_up_kin_out_file        : sets up the output kinetics file
   write_kin_out_frame        : writes a frame of data to kinetics file
   sum_forces_on_body         : sums the contact forces on a body
   get_time_now               : get the current time
   show_vector                : display a vector on screen
   show_array:                : display an array length n on screen
   show_matrix:               : display a MxN matrix on screen
   show_array_as_matrix       : display an array as a matrix
   time_elapsed               : calculate the time elapsed since given start time
   print_state                : display model states to screen
   print_body_info            : prints body info to console
   get_time_now               : gets the current time

*******************************************************************************/
#include "universal.h"
#include <time.h>

/*************** DEFINES (for this file only) *********************************/
#define STORE_FORCES_IN_GROUND_FRAME 0

/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
static MotionData md;

/**************** GLOBAL VARIABLES (used in only a few files) *****************/
dpBoolean verbose = dpNo;

/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;
extern dpSimulationParameters params;
extern char buffer[];
extern MotionData* kinetics_data;
extern SystemInfo si;

/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/
static void sum_forces_on_body(int body, double p[], double frc[]);



/* determine and store the joint reaction forces and torques */
void get_reaction_forces(void)
{
   int i, j;
   static double *forces = NULL, *torques = NULL;

	if (forces == NULL)
		forces = (double *)simm_malloc(sdm->num_joints * 3 * sizeof(double));
	if (torques == NULL)
		torques = (double *)simm_malloc(sdm->num_joints * 3 * sizeof(double));

	sdreac(forces, torques);
	for (i = 0; i < sdm->num_joints; i++)
   {
		for (j = 0; j < 3; j++)
		{
			sdm->joint[i].force[j] = forces[i * 3 + j];
			sdm->joint[i].torque[j] = torques[i * 3 + j];
		}
   }

   check_for_sderror("GET REACTION FORCES");

} 


/************* I/O routines *****************/

/* print information to screen at each step */
void print_simulation_info(double time, double state[], SystemInfo* si)
{

   if (verbose == dpYes)
   {
	   sim_message(none, "time = %.8lf", time);
#if CONTACT_DETECTION
      sim_message(none, "   #contacts = %d", sdm->num_contacts);
#endif 

	   sim_message(none, "kinetic_energy =   %.10", si->kinetic_energy);
	   sim_message(none, "potential_energy = %.10", si->potential_energy);
	   sim_message(none, "system_energy =    %.10", si->system_energy);
   }
   else
   {
      /* cannot use sim_message here because the time display 'scrolls' in place. */
      printf("time = %.8lf\r", time);
      fflush(stdout);
   }

}

/* display time, state and system energy when simulation stops */
void print_final_information(double time, double y[], double dy[], SystemInfo* si)
{
   double energy_change;

	sim_message(none, "t_final = %.6lf", time);
	sim_message(none, "final state:");
	print_state(y, dy);
	sim_message(none, "initial system energy = %f", si->initial_system_energy);
	sim_message(none, "final system energy   = %f", si->system_energy);
	energy_change = si->system_energy - si->initial_system_energy;
	if (energy_change > 0)
   {
		if (energy_change < 0.01) 
			sim_message(none, "gained energy (delta = %e)", energy_change);
		else
         sim_message(none, "gained energy (delta = %f)", energy_change);
   }
	else if (energy_change < 0)
   {
		if (energy_change > -0.01)
			sim_message(none, "lost energy (delta = %e)", energy_change);
		else
         sim_message(none, "lost energy (delta = %f)", energy_change);
   }
	else
   {
		sim_message(none, "no change in energy");
   }

   sim_message(none, "Simulated from time %lf to %lf.", params.startTime, time);
}


/* open output motion file and write header info and column names */
void open_output_motion_file(char filename[])
{
   int i;

	md.fp = fopen(filename, "w");
   if (md.fp == NULL)
   {
      sim_message(exit_program, "Unable to open output motion file %s.", filename);
      return;
   }

	fprintf(md.fp, "name %s\ndatacolumns %d\n", md.name, md.num_elements);
	fprintf(md.fp, "datarows %d\n", md.num_frames);
	fprintf(md.fp, "range %lf %lf\n", md.range_start, md.range_end);
	fprintf(md.fp, "cursor 1.0 1.0 0.0\n");
   fprintf(md.fp, "keys m_key\n");
   fprintf(md.fp, "wrap\n");
   fprintf(md.fp, "enforce_loops no\n");
   fprintf(md.fp, "enforce_constraints no\n");
	fprintf(md.fp, "calc_derivatives %lf\n", md.step_size);
   for (i = 0; i < md.num_events; i++)
      fprintf(md.fp, "event %lf %s\n", md.event[i].xCoord, md.event[i].name);
   fprintf(md.fp, "event_color %f %f %f\n", md.event_color[0], md.event_color[1], md.event_color[2]);
   fprintf(md.fp, "endheader\n\n");

   for (i = 0; i < md.num_elements; i++)
      fprintf(md.fp, "%s\t", md.elementnames[i]);

	fprintf(md.fp, "\n");
	fflush(md.fp);
}


void close_output_motion_file()
{
   if (md.fp)
      fclose(md.fp);
}


/* Open a data file for storing Qs, Us, and accelerations.
 * This file can be read by the SIMM-generated inverse dynamics
 * code in order to find joint torques.
 */
void set_up_kin_out_file(FILE **fp, char filename[])
{
   int i, num_steps;

   /* num_steps should add 1 to account for the first frame of data written
    * at the start of the simulation, and 0.99999 so that any fraction of a
    * time step at the end of the simulation gets counted.
    */
   num_steps = (params.endTime - params.startTime) / params.stepSize + 1.99999;

   remove(filename);  /* work around CodeWarrior fopen(,"w") bug */
   *fp = fopen(filename,"w");
   if (*fp == NULL)
   {
      sim_message(exit_program, "Unable to open output kinetics file %s.", filename);
      return;
   }

   fprintf(*fp,"frames %d\n", num_steps);
   fprintf(*fp,"elements %d\n", sdm->num_gencoords * 3 + 1);
   fprintf(*fp,"otherdata 0\n\n");

   fprintf(*fp, "time ");
   for (i=0; i<sdm->nq; i++)
      if (sdm->q[i].type == dpUnconstrainedQ || sdm->q[i].type == dpPrescribedQ)
 	      fprintf(*fp,"%s %s_vel %s_acc\n", sdm->q[i].name, sdm->q[i].name, sdm->q[i].name);
   fprintf(*fp,"\n");
}


/* Writes a frame of Qs, Us, and accelerations to a data file
 * that can be used for inverse dynamics.
 */
void write_kin_out_frame(double time, double y[], double dy[], FILE **fp)
{
   int i;

   fprintf(*fp, "%lf ", time);
   for (i=0; i<sdm->nq; i++)
   {
      if (sdm->q[i].type == dpUnconstrainedQ || sdm->q[i].type == dpPrescribedQ)
         fprintf(*fp,"%13.8lf %13.8lf %13.8lf\n", y[i]*sdm->q[i].conversion,
                 dy[i]*sdm->q[i].conversion, dy[sdm->nq+i]*sdm->q[i].conversion);
   }
   fprintf(*fp,"\n");
   fflush(*fp);
}


#if CONTACT_DETECTION
/* for each segment, sum all the contact forces acting on it, and average
 * the points of force application.  If forces are due to contact with
 * more than one body, display the force at the body's mass center.
 */
static void sum_forces_on_body(int body, double pt[], double frc[])
{
   int i,j, num = 0, other_body, check, change;
   double sum[3], force_mag;

   make_vector(frc, 0.0, 0.0, 0.0);
   make_vector(pt, 0.0, 0.0, 0.0);
   make_vector(sum, 0.0, 0.0, 0.0);
   num = 0;

   for (i = 0; i < sdm->num_contacts; i++)
   {
      force_mag = VECTOR_MAGNITUDE(sdm->contacts[i].cont_frc);
      if (EQUAL_WITHIN_TOLERANCE(force_mag, 0.0, 1e-3))
         continue;
      if (sdm->contacts[i].body1 == body)
      {
         sdvmul(force_mag, sdm->contacts[i].norm1, frc);
         sdvadd(frc, sum, sum);
         sdvadd(sdm->contacts[i].pt1, pt, pt);
         num++;
      }
      if (sdm->contacts[i].body2 == body)
      {
         sdvmul(force_mag, sdm->contacts[i].norm2, frc);
         sdvadd(frc, sum, sum);
         sdvadd(sdm->contacts[i].pt2, pt, pt);
         num++;
      }
   }
   sdvcopy(sum, frc);
   if (num != 0)
      sdvmul(1.0/num, pt, pt);

   /* if the body contacts two or more other bodies, move the 
    * contact point to the body center of mass.
    */
   for (i = 0; i < sdm->num_contacts; i++)
   {
      if (sdm->contacts[i].body1 == body)
      {
         other_body = sdm->contacts[i].body2;
         check = 2;
         break;
      }
      else if (sdm->contacts[i].body2 == body)
      {
         other_body = sdm->contacts[i].body1;
         check = 1;
         break;
      }
   }
   /* if the body contacts more than one other body, set the point
    * to the mass center
    */
   change = NO;
   for (j = i + 1; j < sdm->num_contacts; j++)
   {
      if ((check == 1) && (sdm->contacts[j].body1 != other_body))
      {
         change = YES;
         break;
      }
      else if ((check == 2) && (sdm->contacts[j].body2 != other_body))
      {
         change = YES;
         break;
      }
   }

	if (change == YES)
      clear_vector(pt, 3);
} 
#endif


void show_vector(char name[], double vect[])
{
   sim_message(none, "%s = %f  %f  %f", name, vect[0], vect[1], vect[2]);
}


void show_array(char name[], double vect[], int start, int end)
{
   int i;

   /* Cannot use sim_message() in the first case because the array is printed
    * onto one line. For consistency, it is not used at all in this function.
    */
   if (end <= 3)
   {
      printf("%s = ", name);
      for (i = start; i < end; i++) 
         printf("% f ", vect[i]);
      printf("\n");
   }
   else
   {
      for (i = start; i < end; i++)
         printf("%s[%d] = % f", name, i, vect[i]);
   }
}


void show_matrix(char name[], double *mat[], int m, int n)
{
   int i, j;

   /* Cannot use sim_message() here because each row is printed onto one line. */
   printf("%s = \n", name);
   for (i = 0; i < m; i++)
   {
      for (j = 0; j < n; j++)
         printf("%f ", mat[i][j]);
      printf("\n");
   }
}

void show_array_as_matrix(char name[], double vec[], int n, int m)
{
   int i, j;

   /* Cannot use sim_message() here because each row is printed onto one line. */
   for (i = 0; i < (n/m); i++)
   {
      printf("%s%d = ", name, i);
      for (j = 0; j < m; j++)
      {
         printf("%f ", vec[i*m + j]);
      }
      printf("\n");
   }
} 

/* calculate the time elapsed between given start and end times */
void time_elapsed(double t_in, double t_out)
{
   double delta;
   int hr, min, sec;

	if (t_out < t_in) t_out += 24.0;
	delta = t_out - t_in;
	hr = (int) floor(delta);
	delta -= hr;
	delta *= 60;
	min = (int) floor(delta);
	delta -= min;
	delta *= 60;
	sec = (int)(delta);
	sim_message(none, "time elapsed: %d hours %d minutes and %d seconds.", hr, min, sec);
}

/* print the state vectors and gencoord information to the screen */
void print_state(double y[], double dy[])
{
   int i, pres;

   for (i = 0; i < sdm->nu; i++)
   {
      sim_message(none, "y[%2d] = %-15.15s= %12.5f %12.5f", i, sdm->q[i].name, 
         sdm->q[i].conversion * y[i], sdm->q[i].conversion * y[i+ sdm->nq]);
      sim_message(none, " %12.5f", dy[i + sdm->nq]);
      if (sdm->q[i].type == dpFixedQ)
         sim_message(none, " %s", "FIXED");
      else if (sdm->q[i].type == dpUnconstrainedQ)
         sim_message(none, " %s", "FREE");
      else if (sdm->q[i].type == dpPrescribedQ)
         sim_message(none, " %s", "PRESCRIBED");
      else if (sdm->q[i].type == dpConstrainedQ)
         sim_message(none, " %s", "CONSTRAINED");
      sdgetpres(sdm->q[i].joint, sdm->q[i].axis, &pres);
      if (pres == 0)
         sim_message(none, "(0)");
      else
         sim_message(none, "(1)");
   }

   sim_message(none, "********************************************************************************");
}

/* print all the segment information to the screen */
void print_body_info(void)
{
   int i;

   for (i = 1; i < sdm->num_body_segments; i++)
   {
      sim_message(none, "BODY %d - %s", i, sdm->body_segment[i].name);
      sim_message(none, "   mass = %f", sdm->body_segment[i].mass);
      sim_message(none, "   inertia = %f %f %f", sdm->body_segment[i].inertia[0][0],
         sdm->body_segment[i].inertia[1][1], sdm->body_segment[i].inertia[2][2]);
      show_vector("   mc", sdm->body_segment[i].mass_center);
   }
}

/* get the current time, print it to the screen and save it in hours */
double get_time_now(void)
{
   double 		hr, min, sec, time_now;
   struct tm	*ptr;
   time_t		lt;
   char			time_str[100];

	lt = time(NULL);
	ptr = localtime(&lt);
	 
	strftime(time_str, 100, "%a %b %d %H:%M:%S %p", ptr);
	sim_message(none, "%s", time_str);
	hr = ptr->tm_hour; min = ptr->tm_min; sec = ptr->tm_sec;
	time_now = hr + min / 60.0 + sec / 3600.0;

	return time_now;
}


/* create output motion structure and fill in header info and column names */
void create_output_motion(char name[])
{
   int i, j, count, num_steps, num_cols = 0, body;

   mstrcpy(&md.name, name);

   /* num_frames should add 1 to account for the first frame of data written
    * at the start of the simulation, and 0.99999 so that any fraction of a
    * time step at the end of the simulation gets counted.
    */
   md.num_frames = (params.endTime - params.startTime) / params.stepSize + 1.99999;

   md.fp = 0;
   md.range_start = params.startTime;
   md.range_end = params.endTime;
   md.step_size = params.stepSize;

   if (kinetics_data)
   {
      md.num_events = kinetics_data->num_events;
      if (md.num_events > 0)
      {
         md.event = (dpMotionEvent*)simm_malloc(md.num_events * sizeof(dpMotionEvent));
         if (md.event)
         {
            for (i = 0; i < md.num_events; i++)
            {
               md.event[i].xCoord = kinetics_data->event[i].xCoord;
               mstrcpy(&md.event[i].name, kinetics_data->event[i].name);
            }
         }
      }
      else
      {
         md.event = NULL;
      }
      for (i = 0; i < 3; i++)
         md.event_color[i] = kinetics_data->event_color[i];
   }
   else
   {
      md.event_color[0] = 1.0;
      md.event_color[1] = 0.0;
      md.event_color[2] = 1.0;
   }

   /* current_frame indicates the first empty row of data */
   md.current_frame = 0;

   /* normalization */
   if (params.outputOptions.normalization != dpNoNormalization)
      num_cols++;

   /* time */
	num_cols++;

	/* gencoords */
	for (i = 0; i < sdm->nu; i++)
		if (sdm->q[i].output == dpYes)
			num_cols++;

   /* muscle activation */
	if (params.outputOptions.muscleActivations == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
            num_cols++;
   }


   /* muscle length */
	if (params.outputOptions.muscleLengths == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
            num_cols++;
   }

   /* muscle force */
	if (params.outputOptions.muscleForces == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
            num_cols++;
   }

   /* external forces and torques */
   if (kinetics_data)
   {
#if STORE_FORCES_IN_GROUND_FRAME
      num_cols += kinetics_data->num_forces * 6;
#else
      /* Use this code to store the ground-based external
       * forces in the reference frame of the segment to
       * which they are applied.
       */
      for (i = 0; i < kinetics_data->num_forces; i++)
      {
         if (kinetics_data->forces[i]->segment == GROUND)
         {
            num_cols += (6 * sdm->num_force_mattes);
         }
         else
         {
            num_cols += 6;
         }
      }
#endif
      num_cols += kinetics_data->num_torques * 3;
   }

#if CONTACT_DETECTION
	/* contact forces (px, py, pz, vx, vy, vz) (cr, cg, cb) */
	if (params.outputOptions.contactForces == dpYes)
   {
		for (i = 0; i < sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].contactable == dpYes)
         {
				num_cols += 6 + 3;
         }
		}
   }
#endif

   /* spring forces (px, py, pz, vx, vy, vz) */
   if (params.outputOptions.springForces == dpYes)
   {
      for (i = 0; i < MIN(params.outputOptions.numSpringForces, sdm->num_springs); i++)
      {
         num_cols += (3 + 3);
      }
   }

	/* joint reaction forces (px, py, pz, rx, ry, rz) */
	if (params.outputOptions.jointReactionForces == dpYes) 
	{
		for (i = 0; i < sdm->num_joints; i++)
      {
			if (sdm->body_segment[sdm->joint[i].outboard_body + 1].output == dpYes)
         {
            num_cols +=  6;
         }
      }
	}
	
   /* joint reaction torques */
	if (params.outputOptions.jointReactionTorques == dpYes) 
	{
		for (i = 0; i < sdm->num_joints; i++)
      {
			if (sdm->body_segment[sdm->joint[i].outboard_body + 1].output == dpYes)
				num_cols +=  3;
		}
	}

   /* joint torques */
	if (params.outputOptions.jointTorques == dpYes)
	{
		for (i = 0; i < sdm->nq; i++)
      {
			if (sdm->q[i].output == dpYes)
			{	
				num_cols++;
			}
      }
	}

   /* muscle moment arms */
	if (params.outputOptions.muscleMomentArms == dpYes)
	{
      for (i = 0; i < sdm->num_muscles; i++)
      {
         if (sdm->muscles[i].output == dpYes)
         {
            for (j = 0; j < sdm->nq; j++)
            {
               if (sdm->q[j].output == dpYes)
                  num_cols++;
            }
         }
      }
	}

   /* muscle joint torques */
	if (params.outputOptions.muscleJointTorques == dpYes)
	{
      for (i = 0; i < sdm->num_muscles; i++)
      {
         if (sdm->muscles[i].output == dpYes)
         {
            for (j = 0; j < sdm->nq; j++)
            {
               if (sdm->q[j].output == dpYes)
                  num_cols++;
            }
         }
      }
	}

   /* total muscle joint torques */
	if (params.outputOptions.totalMuscleJointTorques == dpYes)
	{
		for (i = 0; i < sdm->nq; i++)
      {
			if (sdm->q[i].output == dpYes)
			{	
				num_cols++;
			}
      }
	}

	/* mass center positions - x, y, z */
	if (params.outputOptions.massCenterPositions == dpYes)
   {
		for (i = 1; i < sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].output == dpYes)
         {
            num_cols += 3;
         }
      }
   }
		
	/* total system energy */
	if (params.outputOptions.systemEnergy == dpYes)
		num_cols++;
	
	/* output mass center velocities (vx, vy, vz) */
	if (params.outputOptions.massCenterVelocities == dpYes)
   {
		for (i = 0; i < sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].output == dpYes)
         {
				num_cols += 3; 
			}
      }
   }

   md.num_elements = num_cols;
   md.elementnames = (char**)simm_calloc(md.num_elements, sizeof(char*));
   count = 0;

	/* normalization */
   if (params.outputOptions.normalization == dpNormalizeToOne)
      mstrcpy(&md.elementnames[count++], "factor");
   else if (params.outputOptions.normalization == dpNormalizeToOneHundred)
      mstrcpy(&md.elementnames[count++], "percent");

	/* step, time */
	mstrcpy(&md.elementnames[count++], "time");

	/* gencoords */
	for (i = 0; i < sdm->nu; i++)
		if (sdm->q[i].output == dpYes)
         mstrcpy(&md.elementnames[count++], sdm->q[i].name);
			
   /* muscle activation */
	if (params.outputOptions.muscleActivations == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
            mstrcpy(&md.elementnames[count++], sdm->muscles[i].name);
   }

   /* muscle length */
	if (params.outputOptions.muscleLengths == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
         {
            sprintf(buffer, "%s_len", sdm->muscles[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
         }
   }

   /* muscle force */
	if (params.outputOptions.muscleForces == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
         {
            sprintf(buffer, "%s_frc", sdm->muscles[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
         }
   }

   /* external forces */
   if (kinetics_data)
   {
#if STORE_FORCES_IN_GROUND_FRAME
      for (i = 0; i < kinetics_data->num_forces; i++)
      {
         sprintf(buffer, "%s_force_px", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_force_py", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_force_pz", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_force_vx", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_force_vy", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_force_vz", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
      }
#else
      /* Use this code to store the ground-based external
       * forces in the reference frame of the segment to
       * which they are applied.
       */
      for (i = 0; i < kinetics_data->num_forces; i++)
      {
         if (kinetics_data->forces[i]->segment == GROUND)
         {
            for (j = 0; j < sdm->num_force_mattes; j++)
            {
               sprintf(buffer, "%s_force_px", sdm->body_segment[sdm->force_matte[j].segment+1].name);
               mstrcpy(&md.elementnames[count++], buffer);
               sprintf(buffer, "%s_force_py", sdm->body_segment[sdm->force_matte[j].segment+1].name);
               mstrcpy(&md.elementnames[count++], buffer);
               sprintf(buffer, "%s_force_pz", sdm->body_segment[sdm->force_matte[j].segment+1].name);
               mstrcpy(&md.elementnames[count++], buffer);
               sprintf(buffer, "%s_force_vx", sdm->body_segment[sdm->force_matte[j].segment+1].name);
               mstrcpy(&md.elementnames[count++], buffer);
               sprintf(buffer, "%s_force_vy", sdm->body_segment[sdm->force_matte[j].segment+1].name);
               mstrcpy(&md.elementnames[count++], buffer);
               sprintf(buffer, "%s_force_vz", sdm->body_segment[sdm->force_matte[j].segment+1].name);
               mstrcpy(&md.elementnames[count++], buffer);
            }
         }
         else
         {
            sprintf(buffer, "%s_force_px", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_force_py", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_force_pz", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_force_vx", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_force_vy", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_force_vz", sdm->body_segment[kinetics_data->forces[i]->segment+1].name);
            mstrcpy(&md.elementnames[count++], buffer);
         }
      }
#endif
      for (i=0; i<kinetics_data->num_torques; i++)
      {
         sprintf(buffer, "%s_torque_vx", sdm->body_segment[kinetics_data->torques[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_torque_vy", sdm->body_segment[kinetics_data->torques[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_torque_vz", sdm->body_segment[kinetics_data->torques[i]->segment+1].name);
         mstrcpy(&md.elementnames[count++], buffer);
      }
   }

#if CONTACT_DETECTION
	/* contact forces */
	if (params.outputOptions.contactForces == dpYes)
   {
		for (i = 0; i < sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].contactable == dpYes)
         {
            sprintf(buffer, "%s_contact_cr", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_cg", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_cb", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_px", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_py", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_pz", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_vx", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_vy", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_contact_vz", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
			}
      }
   }
#endif
					
   /* spring forces */
   if (params.outputOptions.springForces == dpYes)
   {
      for (i = 0; i < MIN(params.outputOptions.numSpringForces, sdm->num_springs); i++)
      {
         sprintf(buffer, "%s_spring_force_px", sdm->body_segment[sdm->spring[i].segment + 1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_spring_force_py", sdm->body_segment[sdm->spring[i].segment + 1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_spring_force_pz", sdm->body_segment[sdm->spring[i].segment + 1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_spring_force_vx", sdm->body_segment[sdm->spring[i].segment + 1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_spring_force_vy", sdm->body_segment[sdm->spring[i].segment + 1].name);
         mstrcpy(&md.elementnames[count++], buffer);
         sprintf(buffer, "%s_spring_force_vz", sdm->body_segment[sdm->spring[i].segment + 1].name);
         mstrcpy(&md.elementnames[count++], buffer);
      }
   }

	/* joint reaction forces */
	if (params.outputOptions.jointReactionForces == dpYes)
   {
		for (i = 0; i < sdm->num_joints; i++)
		{
			body = sdm->joint[i].outboard_body + 1;
			if (sdm->body_segment[body].output == dpYes)
			{
            sprintf(buffer, "%s_joint_force_px", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_joint_force_py", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_joint_force_pz", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_joint_force_vx", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_joint_force_vy", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_joint_force_vz", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
			}
		}
   }
	
   /* joint reaction torques */
	if (params.outputOptions.jointReactionTorques == dpYes)
   {
		for (i = 0; i < sdm->num_joints; i++)
		{
			body = sdm->joint[i].outboard_body + 1;
			if (sdm->body_segment[body].output == dpYes)
			{
            sprintf(buffer, "%s_joint_torque_vx", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_joint_torque_vy", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "%s_joint_torque_vz", sdm->body_segment[body].name);
            mstrcpy(&md.elementnames[count++], buffer);
			}
		}
   }

   /* joint torques */
	if (params.outputOptions.jointTorques == dpYes)
   {
		for (i = 0; i < sdm->nq; i++)
			if (sdm->q[i].output == dpYes)
         {
            sprintf(buffer, "%s_torque", sdm->q[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
         }
   }

   /* muscle moment arms */
	if (params.outputOptions.muscleMomentArms == dpYes)
   {
		for (i = 0; i < sdm->num_muscles; i++)
      {
         if (sdm->muscles[i].output == dpYes)
         {
            for (j = 0; j < sdm->nq; j++)
            {
               if (sdm->q[j].output == dpYes)
               {
                  sprintf(buffer, "%s_ma_%s", sdm->muscles[i].name, sdm->q[j].name);
                  mstrcpy(&md.elementnames[count++], buffer);
               }
            }
         }
      }
   }

   /* muscle joint torques */
	if (params.outputOptions.muscleJointTorques == dpYes)
   {
		for (i = 0; i < sdm->num_muscles; i++)
      {
         if (sdm->muscles[i].output == dpYes)
         {
            for (j = 0; j < sdm->nq; j++)
            {
               if (sdm->q[j].output == dpYes)
               {
                  sprintf(buffer, "%s_torque_%s", sdm->muscles[i].name, sdm->q[j].name);
                  mstrcpy(&md.elementnames[count++], buffer);
               }
            }
         }
      }
   }

   /* total muscle joint torques */
	if (params.outputOptions.totalMuscleJointTorques == dpYes)
   {
		for (i = 0; i < sdm->nq; i++)
      {
			if (sdm->q[i].output == dpYes)
         {
            sprintf(buffer, "%s_musc_torque", sdm->q[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
         }
      }
   }

	/* mass center positions */
	if (params.outputOptions.massCenterPositions == dpYes)
   {
		for (i = 1; i <= sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].output == dpYes)
         {
            mstrcpy(&md.elementnames[count++], "ground_ball_px");
            mstrcpy(&md.elementnames[count++], "ground_ball_py");
            mstrcpy(&md.elementnames[count++], "ground_ball_pz");
			}
      }
   }

   /* system energy */
	if (params.outputOptions.systemEnergy == dpYes)
      mstrcpy(&md.elementnames[count++], "sys_energy");
	
   /* mass center velocities */
	if (params.outputOptions.massCenterVelocities == dpYes)
   {
		for (i = 0; i <= sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].output == dpYes)
         {
            sprintf(buffer, "v_%s_x", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "v_%s_y", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
            sprintf(buffer, "v_%s_z", sdm->body_segment[i].name);
            mstrcpy(&md.elementnames[count++], buffer);
         }
      }
   }

   /* Now make room for the data, which will get filled in later. */
   md.motiondata = (double**)simm_calloc(md.num_elements, sizeof(double*));
   for (i = 0; i < md.num_elements; i++)
      md.motiondata[i] = (double*)simm_calloc(md.num_frames, sizeof(double));

}


/* Store a frame of data in the output motion structure, and write
 * it to a file, if the file has been opened.
 */
void store_motion_frame(double time, double state[])
{
   int i, j, frame, imp = NO, col = 0;
   double torque, pt[3], frc[3], com[3] = {0.0, 0.0, 0.0}, vel[3];

   frame = md.current_frame++;

	/* normalization */
   if (params.outputOptions.normalization == dpNormalizeToOne)
      md.motiondata[col++][frame] = (double)frame * 0.01;
   else if (params.outputOptions.normalization == dpNormalizeToOneHundred)
      md.motiondata[col++][frame] = (double)frame;

	/* step, time */
   md.motiondata[col++][frame] = time;
	
	/* Write Qs */
	for (i = 0; i < sdm->nu; i++)
		if (sdm->q[i].output == dpYes)
         md.motiondata[col++][frame] = state[i] * sdm->q[i].conversion;

   /* muscle activation */
	if (params.outputOptions.muscleActivations == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
      {
         if (sdm->muscles[i].output == dpYes)
         {
            md.motiondata[col++][frame] = sdm->muscles[i].dynamic_activation;
         }
      }
   }

   /* muscle length */
	if (params.outputOptions.muscleLengths == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
            md.motiondata[col++][frame] = sdm->muscles[i].muscle_tendon_length;
   }

   /* muscle force */
	if (params.outputOptions.muscleForces == dpYes)
   {
      for (i = 0; i < sdm->num_muscles; i++)
         if (sdm->muscles[i].output == dpYes)
            md.motiondata[col++][frame] = sdm->muscles[i].force;
   }

   /* external forces */
   if (kinetics_data)
   {
      for (i = 0; i < kinetics_data->num_forces; i++)
      {
         get_applied_force(time, kinetics_data, i, pt, frc);

         if (kinetics_data->forces[i]->segment == GROUND)
         {
            double pt2[3], frc2[3], intersectpt[3];
            sdvsub(pt, sdm->body_segment[kinetics_data->forces[i]->segment + 1].mass_center, pt);
            /* intersect the force vector with the force planes */
#if STORE_FORCES_IN_GROUND_FRAME
            for (j = 0; j < sdm->num_force_mattes; j++)
            {
               sdtrans(GROUND, frc, sdm->force_matte[j].segment, frc2);
               sdvcopy(pt, pt2);
               convert_point(pt2, GROUND, sdm->force_matte[j].segment);
               if (vector_intersects_matte(pt2, frc2, &sdm->force_matte[j], intersectpt) == dpYes)
               {
                  md.motiondata[col++][frame] = pt[XX];
                  md.motiondata[col++][frame] = pt[YY];
                  md.motiondata[col++][frame] = pt[ZZ];
                  md.motiondata[col++][frame] = frc[XX];
                  md.motiondata[col++][frame] = frc[YY];
                  md.motiondata[col++][frame] = frc[ZZ];
                  break;
               }
            }
            if (j == sdm->num_force_mattes)
            {
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
            }
#else
            /* Use this code to store the ground-based external forces in the reference
             * frame of the segment to which they are applied.
             */
            for (j = 0; j < sdm->num_force_mattes; j++)
            {
               sdtrans(GROUND, frc, sdm->force_matte[j].segment, frc2);
               sdvcopy(pt, pt2);
               convert_point(pt2, GROUND, sdm->force_matte[j].segment);
               if (vector_intersects_matte(pt2, frc2, &sdm->force_matte[j], intersectpt) == dpYes)
               {
                  sdvadd(pt2, sdm->body_segment[sdm->force_matte[j].segment + 1].mass_center, pt2);
                  md.motiondata[col++][frame] = pt2[XX];
                  md.motiondata[col++][frame] = pt2[YY];
                  md.motiondata[col++][frame] = pt2[ZZ];
                  md.motiondata[col++][frame] = frc2[XX];
                  md.motiondata[col++][frame] = frc2[YY];
                  md.motiondata[col++][frame] = frc2[ZZ];
               }
               else
               {
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
                  md.motiondata[col++][frame] = 0.0;
               }
            }
#endif
         }
         else
         {
            md.motiondata[col++][frame] = pt[XX];
            md.motiondata[col++][frame] = pt[YY];
            md.motiondata[col++][frame] = pt[ZZ];
            md.motiondata[col++][frame] = frc[XX];
            md.motiondata[col++][frame] = frc[YY];
            md.motiondata[col++][frame] = frc[ZZ];
         }
      }

      for (i = 0; i < kinetics_data->num_torques; i++)
      {
         get_applied_torque(time, kinetics_data, i, frc);
         md.motiondata[col++][frame] = frc[XX];
         md.motiondata[col++][frame] = frc[YY];
         md.motiondata[col++][frame] = frc[ZZ];
      }
   }

#if CONTACT_DETECTION
	/* contact forces  - show contact forces in blue, impacts in red */
	if (params.outputOptions.contactForces == dpYes)
   {
		for (i = 0; i < sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].contactable == dpYes)
         {
				sdvcopy(sdm->body_segment[i].impact_force, frc);
				sdvcopy(sdm->body_segment[i].impact_point, pt);
			   if (EQUAL_WITHIN_TOLERANCE(VECTOR_MAGNITUDE(frc), 0.0, 1e-4))
            {
					sum_forces_on_body(i - 1, pt, frc);
               /* get point from segment origin */
               sdvadd(sdm->body_segment[i].mass_center, pt, pt);
               md.motiondata[col++][frame] = 0.0;
               md.motiondata[col++][frame] = 0.0;
               md.motiondata[col++][frame] = 1.0;
            }
            else 
            {
               md.motiondata[col++][frame] = 1.0;
               md.motiondata[col++][frame] = 0.0;
               md.motiondata[col++][frame] = 0.0;
            }

            md.motiondata[col++][frame] = pt[XX];
            md.motiondata[col++][frame] = pt[YY];
            md.motiondata[col++][frame] = pt[ZZ];
            md.motiondata[col++][frame] = frc[XX];
            md.motiondata[col++][frame] = frc[YY];
            md.motiondata[col++][frame] = frc[ZZ];
			}
      }
   }
	/* reset impact forces in body segment structure */
	for (i = 0; i < sdm->num_body_segments; i++)
		make_vector(sdm->body_segment[i].impact_force, 0.0, 0.0, 0.0);
#endif

   /* spring forces */
   if (params.outputOptions.springForces == dpYes)
   {
      for (i = 0; i < MIN(params.outputOptions.numSpringForces, sdm->num_springs); i++)
      {
         /* point with respect to segment origin */
         sdvadd(sdm->body_segment[sdm->spring[i].segment + 1].mass_center,
            sdm->spring[i].point, pt);
         md.motiondata[col++][frame] = pt[XX];
         md.motiondata[col++][frame] = pt[YY];
         md.motiondata[col++][frame] = pt[ZZ];
         md.motiondata[col++][frame] = sdm->spring[i].force[XX];
         md.motiondata[col++][frame] = sdm->spring[i].force[YY];
         md.motiondata[col++][frame] = sdm->spring[i].force[ZZ];
      }
   }

	/* joint reaction force - force applied by the inboard body to the 
    * outboard body displayed at the origin of the outboard body */
	if (params.outputOptions.jointReactionForces == dpYes)
   {
		for (i = 0; i < sdm->num_joints; i++)
      {
			if (sdm->body_segment[sdm->joint[i].outboard_body + 1].output == dpYes)
			{
            md.motiondata[col++][frame] = com[XX];
            md.motiondata[col++][frame] = com[YY];
            md.motiondata[col++][frame] = com[ZZ];
            md.motiondata[col++][frame] = sdm->joint[i].force[XX];
            md.motiondata[col++][frame] = sdm->joint[i].force[YY];
            md.motiondata[col++][frame] = sdm->joint[i].force[ZZ];
			}
      }
   }

   /* joint reaction torques */
   if (params.outputOptions.jointReactionTorques == dpYes)
   {
		for (i = 0; i < sdm->num_joints; i++)
      {
			if (sdm->body_segment[sdm->joint[i].outboard_body + 1].output == dpYes)
         {
            md.motiondata[col++][frame] = sdm->joint[i].torque[XX];
            md.motiondata[col++][frame] = sdm->joint[i].torque[YY];
            md.motiondata[col++][frame] = sdm->joint[i].torque[ZZ];
         }
      }
   }

   /* joint torques */
	if (params.outputOptions.jointTorques == dpYes)
	{
      for (i = 0; i < sdm->nq; i++)
      {
			if (sdm->q[i].output == dpYes)
            md.motiondata[col++][frame] = sdm->q[i].torque;
      }
	}

   /* muscle moment arms */
	if (params.outputOptions.muscleMomentArms == dpYes)
   {
		for (i = 0; i < sdm->num_muscles; i++)
      {
         if (sdm->muscles[i].output == dpYes)
         {
            for (j = 0; j < sdm->nq; j++)
               if (sdm->q[j].output == dpYes)
                  md.motiondata[col++][frame] = sdm->muscles[i].momentarms[j];
         }
      }
   }

   /* muscle joint torques */
	if (params.outputOptions.muscleJointTorques == dpYes)
   {
		for (i = 0; i < sdm->num_muscles; i++)
      {
         if (sdm->muscles[i].output == dpYes)
         {
            for (j = 0; j < sdm->nq; j++)
               if (sdm->q[j].output == dpYes)
                  md.motiondata[col++][frame] = sdm->muscles[i].momentarms[j] * sdm->muscles[i].force;
         }
      }
   }

   /* total muscle joint torques */
	if (params.outputOptions.totalMuscleJointTorques == dpYes)
	{
      for (i = 0; i < sdm->nq; i++)
      {
			if (sdm->q[i].output == dpYes)
         {
            for (j = 0, torque = 0.0; j < sdm->num_muscles; j++)
               torque += sdm->muscles[j].momentarms[i] * sdm->muscles[j].force;
            md.motiondata[col++][frame] = torque;
         }
      }
	}

	/* mass centers positions */
	if (params.outputOptions.massCenterPositions == dpYes)
   {
		for (i = 1; i < sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].output == dpYes)
         {
				sdpos(i - 1, com, pt);
            md.motiondata[col++][frame] = pt[XX];
            md.motiondata[col++][frame] = pt[YY];
            md.motiondata[col++][frame] = pt[ZZ];
			}
      }
   }

	/* system energy */
	if (params.outputOptions.systemEnergy == dpYes)
   {
      md.motiondata[col++][frame] = si.system_energy;
	}
	
   /* mass center velocities */
	if (params.outputOptions.massCenterVelocities == dpYes)
   {
		for (i = 0; i < sdm->num_body_segments; i++)
      {
			if (sdm->body_segment[i].output == dpYes)
         {
				sdvel(i - 1, com, vel);
            md.motiondata[col++][frame] = vel[XX];
            md.motiondata[col++][frame] = vel[YY];
            md.motiondata[col++][frame] = vel[ZZ];
         }
      }
	}

   /* Now write the frame to the file. */
   if (md.fp)
   {
      for (i = 0; i < md.num_elements; i++)
         fprintf(md.fp, "%12.7lf\t", md.motiondata[i][frame]);

      fprintf(md.fp, "\n");
      fflush(md.fp);
   }

	check_for_sderror("Writing to motion file");

}


void get_motion_info(dpDataSetup* dataSetup)
{
   int i;

   if (md.name)
      mstrcpy(&dataSetup->motionName, md.name);

   dataSetup->numFrames = md.num_frames;
   dataSetup->numElements = md.num_elements;
   dataSetup->elementNames = (char**)simm_malloc(dataSetup->numElements * sizeof(char*));
   
   for (i = 0; i < dataSetup->numElements; i++)
      mstrcpy(&dataSetup->elementNames[i], md.elementnames[i]);

   dataSetup->numEvents = md.num_events;
   if (dataSetup->numEvents > 0)
   {
      dataSetup->event = (dpMotionEvent*)simm_malloc(dataSetup->numEvents * sizeof(dpMotionEvent));
      if (dataSetup->event)
      {
         for (i = 0; i < dataSetup->numEvents; i++)
         {
            dataSetup->event[i].xCoord = md.event[i].xCoord;
            mstrcpy(&dataSetup->event[i].name, md.event[i].name);
         }
      }
   }
   else
   {
      dataSetup->event = NULL;
   }

   for (i = 0; i < 3; i++)
      dataSetup->eventColor[i] = md.event_color[i];
}


/* This function fills in a data structure with the last frame of
 * data that was stored in the output motion structure.
 */
void get_motion_data(dpDataFrame* dataFrame)
{
   int i, frame;

   if (md.current_frame > 0)
      frame = md.current_frame - 1;
   else
      frame = 0;

   for (i = 0; i < dataFrame->numElements; i++)
      dataFrame->elements[i] = md.motiondata[i][frame];
}
