// simm_init.c
// Joon H. Shim shimm@stanford.edu


//=============================================================================
// INCLUDES
//=============================================================================
#include <universal_323.h>
#include "simm_init_323.h"

//=============================================================================
// DEFINITION
//=============================================================================
#define BAUMGARTE_STAB 20
#define ASSEMBLY_TOL 1e-7
#define NO_ERROR	0
#define OVERBUMP	1
#define CANTCONTINUE	2
#define USER_FLAG	3
#define NO_FLAG       0
#define IMPACT_FLAG	1
#define BAD_STATE	2
#define CONS_VIOL	3

//=============================================================================
// DATA
//=============================================================================
OutputOptions oo;
char current_dir[CHARBUFFER];
SystemInfo si;

//=============================================================================
// EXTERNALS
//=============================================================================
extern SDModelStruct sdm;
extern char buffer[];
extern char errorbuffer[];
extern SBoolean verbose;
extern MotionData* kinetics_data = NULL;
extern int impact_calc = NO;

//_____________________________________________________________________________
/**
 * This routine (called by integrate()) computes system derivatives, given the 
 * time and state of the system.  It returns a user flag if impacts are found.
 */
void calc_derivatives(double t, double y[], double dy[], double param[], int *status)
{
   int i, err;
#if CONTACT_DETECTION
   int calc_impact = NO;
#endif

	*status = NO_FLAG;

	sdstate(t, y, &y[sdm.nq]);
	err = check_for_sderror("CALC_DERIVATIVES");
	if (err)
      goto allDone;

	/* calc muscle derivatives */
	calc_muscle_derivatives(t, y, dy, param, &err);

	sdumotion(t, y, &y[sdm.nq]);
	sduforce(t, y, &y[sdm.nq]);
	sdderiv(dy, &dy[sdm.nq]);

#if CONTACT_DETECTION
	/* determine contact points */
	determine_contacts(y, dy);
	get_contact_info();
   get_bilat_contact_info();

	if (sdm.num_contacts == 0)
      goto allDone;

	/* check for impacts, if any are found, set the flag and return.
	 * If integration has stopped and find_impacts has called deriv,
	 * don't set any flags (not ignoring impacts)
    */
	for (i = 0; i < sdm.num_contacts; i++)
   {
		if ((sdm.contacts[i].contact_type == IMPACT) && (param[0] < 0))
      {
			*status = IMPACT_FLAG;
			goto allDone;
		}
   }

	/* if no impacts were found, find resting contact forces, apply them,
	 * and calculate accelerations
    */
	sdstate(t, y, &y[sdm.nq]);
	sdumotion(t, y, &y[sdm.nq]);
	sduforce(t, y, &y[sdm.nq]);

   compute_contact_forces(calc_impact);
	apply_forces_at_contacts(sdm.num_contacts, sdm.contacts);

	sdderiv(dy, &dy[sdm.nq]);
#endif

	err = check_for_sderror("CALC_DERIVATIVES: alldone");

allDone:
    /* We're done with calculating derivatives.  If an error occurred, we'll
     * assume it means the integrator picked a bad time/state for this guess,
     * and we'll reject the guess.  This will make the integrator cut its
     * step size, hopefully producing a better guess next time.
     *
     * If the error is "singular mass matrix" we'll ignore it, however,
     * since in this case that's just an artifact of our use of massless
     * frames when in certain configurations and does not actually cause
     * problems.
     *
     * If we reject this guess, we'll clear out dy[] which may contain
     * garbage (e.g. NaNs) resulting from the bad state.
     */
	if (err == 43 || err == 44)
   {
      print_final_information(t, y, dy, &si);
      error(exit_program, "A joint is in gimbal lock.");
   }
   if ((err != 0) && (err != 47))
   {
		printf("\nBAD STATE\n");
		print_state(y, dy);
		*status = BAD_STATE;
		error(exit_program, "deriv");
   } 

}

//_____________________________________________________________________________
/**
 * This function is used to apply forces to the body segments.
 * The first section of code determines the current frame for the external
 * force data, if any exist. You may want to change this code, depending
 * on what type of external force[s] you want to apply, and how many
 * frames of data there are. Sduforce() then calls the functions to
 * apply the muscles forces, the restraint torques, and the external
 * forces, respectively.  It also calls the functions to apply spring
 * forces for spring-based contact.
 */

int sduforce(double t, double q[], double u[])
{

	if (kinetics_data)
      apply_external_forces(t, kinetics_data);
	
   apply_muscle_forces(&sdm);

   apply_joint_restraint_torques(&sdm, q);

   apply_spring_forces(&sdm);

   check_for_sderror("SDUFORCE");

   return 1;
}

//_____________________________________________________________________________
/**
 * Apply prescribed motions to fixed and prescribed gencoords 
 */
int sdumotion(double t, double q[], double u[])
{

   set_fixed_gencoords(&sdm);

   set_prescribed_gencoords(t, q, u, &sdm, kinetics_data);

   return 1;

}

//_____________________________________________________________________________
/**
 * Calculate position errors for constrained gencoords 
 */
void sduperr(double t, double q[], double errors[])
{
   int i, j, q_ind, constraint_num;
   double q_ind_value, q_dep_value, q_value, u_ind_value = 0.0, a_ind_value = 0.0;
   ConstraintObject *co;

   /* constrained gencoords */
   for (i=0; i<sdm.nq; i++)
   {
      if (sdm.q[i].type == constrained_q)
      {
         q_ind = sdm.q[i].q_ind;
         q_ind_value = q[q_ind] * sdm.q[q_ind].conversion;
         q_dep_value = q[i];
         q_value = interpolate_spline(q_ind_value, sdm.q[i].constraint_func,
            zeroth, u_ind_value, a_ind_value) / sdm.q[i].conversion;
         errors[sdm.q[i].constraint_num] = q_dep_value - q_value;
      }
   }

   /* constraint objects */
   for (i = 0; i < sdm.num_constraint_objects; i++)
   {
      co = &sdm.constraint_object[i];
      if (co->active == no)
         continue;
      for (j = 0; j < co->numPoints; j++)
      {
         constraint_num = co->points[j].constraint_num;
         errors[constraint_num] = calculate_constraint_position_error(co, PERR, j);
      }
   }
}

//_____________________________________________________________________________
/**
 * Calculate velocity errors for constrained gencoords.
 */
void sduverr(double t, double q[], double u[], double errors[])
{
   int i, j, q_ind, constraint_num;
   double q_ind_value, u_ind_value, u_dep_value, a_ind_value = 0.0, v_value;
   ConstraintObject *co;

   /* constrained gencoords */
   for (i=0; i<sdm.nq; i++)
   {
      if (sdm.q[i].type == constrained_q)
      {
         q_ind = sdm.q[i].q_ind;
         q_ind_value = q[q_ind] * sdm.q[q_ind].conversion;
         u_ind_value = u[q_ind] * sdm.q[q_ind].conversion;
         u_dep_value = u[i];
         v_value = interpolate_spline(q_ind_value, sdm.q[i].constraint_func,
            first, u_ind_value, a_ind_value)/sdm.q[i].conversion;
         errors[sdm.q[i].constraint_num] = u_dep_value - v_value;
      }
   }

   /* constraint objects */
   for (i = 0; i < sdm.num_constraint_objects; i++)
   {
      co = &sdm.constraint_object[i];
      if (co->active == no)
         continue;
      
      for (j = 0; j < co->numPoints; j++)
      {
         constraint_num = co->points[j].constraint_num;
         errors[constraint_num] = calculate_constraint_velocity_error(co, j);
      }
   }
}


//_____________________________________________________________________________
/**
 * Calculate acceleration errors for constrained gencoords. 
 */
void sduaerr(double t, double q[], double u[], double udot[], double errors[])
{
   int i, j, q_ind, constraint_num;
   double q_ind_value, u_ind_value, a_ind_value, a_dep_value;
   double a_value;
   ConstraintObject *co;

   /* constrained gencoords */
   for (i=0; i<sdm.nq; i++)
   {
      if (sdm.q[i].type == constrained_q)
      {
	      q_ind = sdm.q[i].q_ind;
	      q_ind_value = q[q_ind] * sdm.q[q_ind].conversion;
	      u_ind_value = u[q_ind] * sdm.q[q_ind].conversion;
	      a_ind_value = udot[q_ind] * sdm.q[q_ind].conversion;
	      a_dep_value = udot[i];
         a_value = interpolate_spline(q_ind_value, sdm.q[i].constraint_func, second,
            u_ind_value, a_ind_value)/sdm.q[i].conversion;
         errors[sdm.q[i].constraint_num] = a_dep_value - a_value;
      }
   }

   /* constraint objects */
   for (i = 0; i < sdm.num_constraint_objects; i++)
   {
      co = &sdm.constraint_object[i];
      if (co->active == no)
         continue;
      
      for (j = 0; j < co->numPoints; j++)
      {
         constraint_num = co->points[j].constraint_num;
         errors[constraint_num] = calculate_constraint_acceleration_error(co, j);
      }
   }
}

//_____________________________________________________________________________
/**
 * calculate and apply constraint forces for constrained gencoords. 
 */
void sduconsfrc(double t, double q[], double u[], double mults[])
{
   int i, j, k, q_ind, constraint_num;
   double q_ind_value, torque, u_ind_value, a_ind_value = 0.0, int_spline;
   ConstraintObject *co;
 
   for (i=0; i<sdm.nq; i++)
   {
      if (sdm.q[i].type == constrained_q)
      {
         q_ind = sdm.q[i].q_ind;
         q_ind_value = q[q_ind] * sdm.q[q_ind].conversion;
         u_ind_value = sdm.q[q_ind].conversion;

	      sdhinget(sdm.q[i].joint,sdm.q[i].axis,mults[sdm.q[i].constraint_num]);

         int_spline = interpolate_spline(q_ind_value, sdm.q[i].constraint_func,
            first, u_ind_value, a_ind_value) / sdm.q[i].conversion;
         torque = -mults[sdm.q[i].constraint_num] * int_spline;

         sdhinget(sdm.q[q_ind].joint,sdm.q[q_ind].axis,torque);
      }
   }

   /* constraint objects */
   for (i = 0; i < sdm.num_constraint_objects; i++)
   {
      co = &sdm.constraint_object[i];
      if (co->active == no)
         continue;

      for (j = 0; j < co->numPoints; j++)
      {
         constraint_num = co->points[j].constraint_num;
         apply_constraint_forces(co, mults[constraint_num], j);
      }
   }
   check_for_sderror("SDUCONSFRC");

}

//_____________________________________________________________________________
/**
 * Initialize the model.
 */
void init_model(void)
{

   int i, info[50];

   oo.contact_forces = yes;
   oo.hinge_torques = no;
   oo.joint_reaction_forces = no;
   oo.joint_reaction_torques = no;
   oo.mass_center_positions = no;
   oo.mass_center_velocities = no;
   oo.muscle_moment_arms = no;
   oo.muscle_joint_torques = no;
   oo.total_muscle_joint_torques = no;
   oo.muscle_activations = yes;
   oo.muscle_lengths = no;
   oo.muscle_forces = yes;
   oo.system_energy = no;
   oo.num_spring_forces = 10;

	sdinfo(info);
	sdm.num_body_segments = info[1] + 1;	/* include ground */
	sdm.nq = info[2] + info[7];
	sdm.nu = info[2];
	sdm.num_closed_loops = info[4];
	sdm.num_joints = info[1] + info[4]; /* nbod + nloop */
   sdm.num_constraints = info[3];
   sdm.num_user_constraints = info[10];
   sdm.num_springs = 0;
   sdm.num_spring_floors = 0;
   sdm.num_force_mattes = 0;
   sdm.spring_array_size = ARRAY_INCREMENT;
   sdm.spring_floor_array_size = ARRAY_INCREMENT;
   sdm.force_matte_array_size = ARRAY_INCREMENT;
   sdm.step_size = 0.01;
   sdm.start_time = 0.0;
   sdm.end_time = 1.0;

	init_qs();
	init_segments();
	init_joints();
   init_wrap_objects();
   init_constraint_objects();

#if CONTACT_DETECTION
   makepaths();

   for (i = 0; i < sdm.num_body_segments; i++)
   {
      sdm.body_segment[i].num_objects = 0;
      make_vector(sdm.body_segment[i].impact_force, 0.0, 0.0, 0.0);
      make_vector(sdm.body_segment[i].impact_point, 0.0, 0.0, 0.0);
      make_vector(sdm.body_segment[i].contact_force, 0.0, 0.0, 0.0);
   }
#endif
}

//_____________________________________________________________________________
/**
 * Set on/off state of prescribed motion for all Qs based on their types.
 */
void init_motion(void)
{

   set_prescribed_motion(&sdm, unconstrained_q, 0);
   set_prescribed_motion(&sdm, constrained_q, 0);
   set_prescribed_motion(&sdm, prescribed_q, 1); 
   set_prescribed_motion(&sdm, fixed_q, 1);

   check_for_sderror("INIT_MOTION");

}

//_____________________________________________________________________________
/**
 * Set initial conditions for all Qs in the model. The initial values
 * and velocities of all Qs, regardless of type, are set here. Values
 * for unconstrained Qs are taken from the 'initial_value' field in the
 * sdm struct.
 */
void set_initial_conditions(double *t, double y[], double dy[])
{

   int i;
   double q_ind_value;

	*t = sdm.start_time;

	for (i = 0; i < sdm.neq; i++)
		y[i] = dy[i] = 0.0;
	
	for (i = 0; i < sdm.nq; i++)
   {
      if (sdm.q[i].type != constrained_q)
      {
		   y[i] = sdm.q[i].initial_value/sdm.q[i].conversion;
      }
      else
      {
         if (sdm.q[i].constraint_func == NULL)
         {
            sprintf(errorbuffer, "Constrained gencoord %s does not have a function defined.\n", sdm.q[i].name);
            error(exit_program, errorbuffer);
         }
         if (sdm.q[i].constraint_num == -1)
         {
            sprintf(errorbuffer, "Constrained gencoord %s does not have an associated constraint number.\n",
               sdm.q[i].name);
            error(exit_program, errorbuffer);
         }
         if (sdm.q[i].q_ind == -1)
         {
            sprintf(errorbuffer, "Constrained gencoord %s does not have an independent q.\n", sdm.q[i].name);
            error(exit_program, errorbuffer);
         }
         q_ind_value = y[sdm.q[i].q_ind] * sdm.q[sdm.q[i].q_ind].conversion;
         y[i] = interpolate_spline(q_ind_value,sdm.q[i].constraint_func,zeroth,0.0,0.0) / sdm.q[i].conversion;
      }
   }

   for (i = 0; i < sdm.nq; i++) 
   {
	   if (sdm.q[i].type != fixed_q)
      {
         y[i + sdm.nq] = dy[i] = sdm.q[i].initial_velocity / sdm.q[i].conversion;
      }
      else
      {
         if (sdm.q[i].initial_velocity != 0.0)
            printf("Warning: initial velocity for %s (FIXED) was not 0.0. Setting to zero...\n", sdm.q[i].name);
         y[i + sdm.nq] = dy[i] = 0.0;
      }
   }
}

//_____________________________________________________________________________
/**
 * Assmeble the model, and make sure the gencoord velocities
 * are properly set.
 */
void assemble_model(double t, double y[])
{
   int i, fcnt, err, *lock;

   lock = (int*)simm_malloc(sdm.nq * sizeof(int));

   for (i = 0; i < sdm.nq; i++)
   {
      if (sdm.q[i].type == fixed_q)
         lock[i] = 1;
      else
         lock[i] = 0;
   }

   /* assemble model */
   sdassemble(t, y, lock, ASSEMBLY_TOL, 500, &fcnt, &err);
   if (err)
   {
      fprintf(stderr, "Assembly failed, err = %d\n", err);
      fprintf(stderr, "Closest solution:\n");
		for (i = 0; i < sdm.nu; i++)
			printf("%s = %lf (%d)\n", sdm.q[i].name, y[i], lock[i]);
      fprintf(stderr,"\n");
      error(exit_program, "");
   }

   /* You may want to call verify_assembly() if you know for sure that
    * none of the gencoords should be outside their range of motion.
   if (verify_assembly(&sdm,y) == code_bad)
      error(exit_program, "Verify assembly failed.");
    */

   sdinitvel(t, y, lock, ASSEMBLY_TOL, 500, &fcnt, &err);
   if (err)
   {
      sprintf(buffer, "%s\n%s\n", "Velocity analysis failed.",
   	        "Check that prescribed gencoord velocities are not being set to new values");
      error(exit_program, buffer);
   }

   free(lock);

}


//_____________________________________________________________________________
/**
 * Read the kinetics input file.
 */
void set_up_kinetics_input(char filename[], MotionData** data)
{
   int i, index_pres = -1;

   if ((*data = (MotionData*)simm_malloc(sizeof(MotionData))) == NULL)
   {
      error(exit_program,"Unable to malloc enough memory to run.\n");
   }
   else if (load_kinetics_data(&sdm, *data, filename, no) == code_bad)
   {
      sprintf(buffer, "Error reading kinetics file %s\n", filename);
      error(exit_program, buffer);
   }

   /* If there is position, velocity, and acceleration data for a Q in the
   * kinetics file, make it prescribed.
   */
   if ((*data)->q_data)
   {
      int position_present, velocity_present, acceleration_present;

      for (i = 0; i < sdm.nq; i++)
      {
         /* Position data must be explicitly specified (though it can be splined or not).
          * Velocity can either be specified explicitly, or calculated from position
          * (if position data is splined). Acceleration can be specified explicitly or
          * calculated from position or velocity.
          */
         position_present = (int)((*data)->q_data[i]);
         velocity_present = (*data)->u_data[i] ||
                            ((*data)->q_data[i] && (*data)->q_data[i]->type != step_func);
         acceleration_present = (*data)->udot_data[i] ||
                                ((*data)->q_data[i] && (*data)->q_data[i]->type != step_func) ||
                                ((*data)->u_data[i] && (*data)->u_data[i]->type != step_func);
         if (position_present && velocity_present && acceleration_present)
         {
            sdm.q[i].type = prescribed_q;
            index_pres = i;
         }
      }
   }

   /* If all unconstrained gencoords are prescribed with data in the
    * kinetics file, then this is really more of an inverse dynamics
    * simulation than a forward one. So override the default values
    * of sdm.start_time, sdm.end_time, and sdm.step_size to match the
    * data in the kinetics file.
    */
   for (i = 0; i < sdm.nq; i++)
   {
      if (sdm.q[i].type == unconstrained_q)
         break;
   }
   if (i == sdm.nq)
   {
      /* No gencoords are left as unconstrained. Use index_pres, which is the
       * index of one of the Qs that is prescribed in the file, to get the
       * time of the first and last frames of data in the file. Divide this
       * time range by the number of frames to get the step size (reporting
       * interval) for the integrator.
       */
      sdm.start_time = (*data)->q_data[index_pres]->x[0];
      sdm.end_time = (*data)->q_data[index_pres]->x[(*data)->q_data[index_pres]->numpoints - 1];
      sdm.step_size = (sdm.end_time - sdm.start_time) / ((*data)->q_data[index_pres]->numpoints - 1);
   }
}
