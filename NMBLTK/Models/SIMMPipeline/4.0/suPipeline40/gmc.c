/*******************************************************************************

   GMC.C

   Author: Peter Loan
           Krystyne Blaikie
           contributions from Chris Raasch and Lisa Schutte

   Copyright (c) 1992-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains utility routines for calculating various
      muscle properties such as length, force, and velocity. It also contains
      the main GMC routines which control the calculation of muscle state
      derivatives, calc_derivatives(), and the application of muscle forces
      to the body segments, apply_muscle_forces().

   Routines:
      calc_muscle_derivatives      : calculates derivatives of muscle states
      calc_passive_force           : calculates passive force in muscle fibers
      calc_tendon_force            : calculates tendon force
      calc_force_velocity          : calcs force scaling factor due to fiber vel
      calc_active_force            : calculates active force in muscle fibers
      calc_fiber_force             : calculates total force in muscle fibers
      calc_excitation              : calculates excitation of muscle
      calc_distance_between_points : calcs distance between two points
      calc_muscle_tendon_length    : calculates muscle-tendon length
      calc_pennation               : calculates current fiber pennation angle
      init_muscle_states           : initializes all muscle states
      assign_muscle_states         : stores all muscle state values
      apply_muscle_forces          : applies muscle forces to body segments
      calc_muscle_moment_arms      : calcs moment arms for all muscles
      calc_muscle_tendon_force     : calcs static force in muscle-tendon unit
      calc_muscle_tendon_velocity  : calcs velocity of muscle-tendon unit
      calc_muscle_seg_velocity     : calcs velocity of one segment of muscle path
      calc_fiber_velocity          : calcs muscle fiber velocity given force
      calc_nonzero_passive_force   : calcs passive force in muscle
      count_muscle_states          : counts total muscle states in all muscles
      calc_muscle_power            : calculates power muscle applies to segments

*******************************************************************************/

#include "universal.h"
extern int sim_message( ErrorAction action, const char* format, ... );


/*************** DEFINES (for this file only) *********************************/
#define MAX_ITERATIONS 100
#define ERROR_LIMIT 0.01

/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
static int (*muscle_init_func[])() =
{
muscle_init_func1, muscle_init_func2, muscle_init_func3, muscle_init_func4,
muscle_init_func5, muscle_init_func6, muscle_init_func7, muscle_init_func8,
muscle_init_func9, muscle_init_func10
};

static int (*muscle_deriv_func[])() =
{
muscle_deriv_func1, muscle_deriv_func2, muscle_deriv_func3, muscle_deriv_func4,
muscle_deriv_func5, muscle_deriv_func6, muscle_deriv_func7, muscle_deriv_func8,
muscle_deriv_func9, muscle_deriv_func10
};

static int (*muscle_assign_func[])() =
{
muscle_assign_func1, muscle_assign_func2, muscle_assign_func3, muscle_assign_func4,
muscle_assign_func5, muscle_assign_func6, muscle_assign_func7, muscle_assign_func8,
muscle_assign_func9, muscle_assign_func10
};

/**************** GLOBAL VARIABLES (used in only a few files) *****************/


/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;
extern char buffer[];   /* defined in readtools.c */

/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/
static double calc_muscle_seg_velocity(double p1[], int seg1, double p2[], int seg2);



/* CALC_MUSCLE_DERIVATIVES: this routine calls the appropriate 
 * muscle_deriv_func to calculate muscle state derivatives.
 */
void calc_muscle_derivatives(double time, double state[], double dstate[], 
	                          double param[], int* status)
{
   int i, start_index, muscle_model_index;
   int (*deriv_func)();
   double muscle_force;
   dpMuscleStruct* ms;

   /* Skip past the NQ and NU portions of the state vector, start at the 
    * muscle states.
    */
   start_index = sdm->nq + sdm->nu;
   
   /* For each muscle, calculate the derivatives of its states */
   for (i = 0; i < sdm->num_muscles; i++)
   {
      ms = &sdm->muscles[i];

      check_wrapping_points(ms, state);

      muscle_model_index = *(ms->muscle_model_index);

      /* Look up the function pointer from array of func pointers for which
       * the index was stored in the muscle structure.
       */
      deriv_func = muscle_deriv_func[muscle_model_index];

      /* User-supplied derivative routines are expected to fill in the
       * muscle_force param, below, and indicate how many states that
       * muscle occupies in the state vector.
       */
      start_index +=
         deriv_func(time, ms, &state[start_index], &dstate[start_index],
            &muscle_force);
   }
   check_for_sderror("CALC_MUSC_DERIV");
}


/* CALC_PASSIVE_FORCE: this routine calculates the passive force in the muscle
 * fibers. It includes the contribution of the passive force-length curve as
 * well as the damping effects due to contraction velocity.
 */

double calc_passive_force(dpMuscleStruct* ms, double norm_fiber_length,
			  double norm_fiber_velocity)
{

   double passive_force, flcomponent;

   flcomponent = interpolate_spline(norm_fiber_length,
				    ms->passive_force_len_curve,zeroth,1.0,1.0);

   if (flcomponent < 0.0)
      flcomponent = 0.0;

   passive_force = flcomponent + get_muscle_param_value(ms,"damping") *
      norm_fiber_velocity;

   return (passive_force);

}



/* CALC_TENDON_FORCE: this routine calculates the force in tendon by finding
 * tendon strain and using it to interpolate the tendon force-length curve.
 */

double calc_tendon_force(dpMuscleStruct* ms, double norm_tendon_length)
{

   double tendon_strain, norm_resting_length, tendon_force;

   norm_resting_length = (*(ms->resting_tendon_length)) /
      (*(ms->optimal_fiber_length));

   tendon_strain =  (norm_tendon_length - norm_resting_length) /
      norm_resting_length;

   if (tendon_strain < 0.0)
      tendon_force = 0.0;
   else
      tendon_force = interpolate_spline(tendon_strain,
					ms->tendon_force_len_curve,zeroth,1.0,1.0);

   return (tendon_force);

}



/* CALC_FORCE_VELOCITY: this routine calculates the effect that fiber
 * contraction velocity has on muscle force. It uses the fiber velocity
 * to interpolate the force-velocity curve, giving a scaling factor for
 * the muscle force.
 */

double calc_force_velocity(dpMuscleStruct* ms, double norm_fiber_velocity)
{

   double velocity_factor;

   velocity_factor = interpolate_spline(norm_fiber_velocity,
					ms->force_vel_curve,zeroth,1.0,1.0);

   return (velocity_factor);

}  



/* CALC_ACTIVE_FORCE: this routine calculates the active component of force
 * in the muscle fibers. It uses the current fiber length to interpolate the
 * active force-length curve. The effects of activation level and contraction
 * velocity are not included in this routine.
 */

double calc_active_force(dpMuscleStruct* ms, double norm_fiber_length)
{

   double active_force;

   active_force = interpolate_spline(norm_fiber_length,
				     ms->active_force_len_curve,zeroth,1.0,1.0);

   if (active_force < 0.0)
      active_force = 0.0;
   
   return (active_force);
   
}



/* CALC_FIBER_FORCE: this routine calculates the total force in the muscle
 * fibers. It includes the effects of active force, passive force, activation,
 * and contraction velocity.
 */

double calc_fiber_force(dpMuscleStruct* ms, double activation,
			 double norm_fiber_length, double norm_fiber_velocity)
{

   double fiber_force, active_force, passive_force, velocity_factor;

   active_force = calc_active_force(ms,norm_fiber_length);
   passive_force = calc_passive_force(ms,norm_fiber_length,norm_fiber_velocity);
   velocity_factor = calc_force_velocity(ms,norm_fiber_velocity);

   fiber_force = activation*active_force*velocity_factor + passive_force;

   return (fiber_force);

}



/* CALC_EXCITATION: this routine calculates the level of excitation in a muscle.
 * The excitation levels and times given in the muscle input file define a
 * step function, natural cubic spline, or GCV spline of excitation for the muscle.
 * This routine uses the current time to find the desired level of excitation.
 */

double calc_excitation(dpMuscleStruct* ms, double time, double state[])
{

   double abscissa;
   dpSplineFunction* exc;

   exc = ms->excitation;

   if (exc == NULL || exc->numpoints <= 0)
      return 0.0;

   if (ms->excitation_abscissa == TIME)
      abscissa = time;
   else
      abscissa = state[ms->excitation_abscissa] * sdm->q[ms->excitation_abscissa].conversion;

   return interpolate_spline(abscissa, exc, zeroth, 0.0, 0.0);

}



/* CALC_DISTANCE_BETWEEN_POINTS: this routine calculates the distance
 * between two points, which may or may not be expressed in the same body
 * segment reference frame. It uses SD/FAST utility routines to convert both
 * points to the ground reference frame, then calculates the distance
 * between them.
 */

double calc_distance_between_points(double p1[], int n1, double p2[], int n2)
{

   int sdbody1, sdbody2;
   double ans, x, inertial_p1[3], inertial_p2[3];

   sdbody1 = n1;
   sdbody2 = n2;

   /* Convert the two points to the ground (inertial) reference frame */

   sdpos(sdbody1,p1,inertial_p1);
   sdpos(sdbody2,p2,inertial_p2);

   x = ((inertial_p1[XX]-inertial_p2[XX])*(inertial_p1[XX]-inertial_p2[XX]) +
	(inertial_p1[YY]-inertial_p2[YY])*(inertial_p1[YY]-inertial_p2[YY]) +
	(inertial_p1[ZZ]-inertial_p2[ZZ])*(inertial_p1[ZZ]-inertial_p2[ZZ]));

   ans = sqrt(x);

   return (ans);

}



/* CALC_MUSCLE_TENDON_LENGTH: this routine finds the total length of a
 * muscle-tendon actuator. It assumes that check_wrapping_points() has
 * already been called to determine which muscle attachment points should
 * be used to define the muscle path.
 */

double calc_muscle_tendon_length(dpMuscleStruct* ms)
{

   int start, end;

   ms->muscle_tendon_length = 0.0;             /* start: length = 0.0 */

   /* Find musculotendon length by summing the lengths of the individual
    * muscle segments. The mp[] array contains only "active" muscle
    * points (e.g., inactive via points are not included).
    */
   for (start = 0; start < ms->num_points - 1; start++)
   {
      end = start + 1;

      /* If both points are wrap points on the same wrap object, then this muscle
       * segment wraps over the surface of a wrap object, so just add in the
       * pre-calculated distance.
       */
      if (onSameWrapObject(ms, start, end) == dpYes)
      {
         ms->muscle_tendon_length += ms->mp[end]->wrap_distance;
      }
      else
      {
         ms->muscle_tendon_length +=
            calc_distance_between_points(ms->mp[start]->point,ms->mp[start]->segment,
            ms->mp[end]->point,ms->mp[end]->segment);
      }
   }

   return ms->muscle_tendon_length;

}


/* CALC_PENNATION: this routine calculates the current pennation angle in a
 * muscle. Pennation angle increases as muscle fibers shorten. The modeling
 * assumption implicit in this routine is that muscles have constant volume.
 * It returns the current pennation angle in degrees, which is restricted to
 * the range 0 to 90.
 */
   
double calc_pennation(double fiber_length, double optimal_fiber_length,
		      double initial_pennation_angle)
{

   double value;

   value = optimal_fiber_length * sin(DEG_TO_RAD*initial_pennation_angle) /
      fiber_length;

   if (value <= 0.0)
      return (0.0);
   else if (value >= 1.0)
      return (90.0);
   else
      return (RAD_TO_DEG * asin(value));

}



/* INIT_MUSCLE_STATES: this routine initializes all of the muscle states.
 * It uses the init_func index in the muscle structure to call the right
 * muscle_init_func() for each muscle.
 */

void init_muscle_states(dpModelStruct* sdm, double state[])
{

   int i, start_index, func_index;
   int (*user_func)();
   
   start_index = sdm->nq + sdm->nu;
   for (i=0; i<sdm->num_muscles; i++)
   {
      check_wrapping_points(&sdm->muscles[i],state);
      func_index = *(sdm->muscles[i].muscle_model_index);
      user_func = muscle_init_func[func_index];
      start_index += user_func(&sdm->muscles[i],&state[start_index]);
   }

}



/* ASSIGN_MUSCLE_STATES: this routine stores the muscle states in the muscle
 * structure (or wherever the user chooses) after each integration step.
 * It uses the assign_func index in the muscle structure to call the right
 * muscle_assign_func() for each muscle.
 */

void assign_muscle_states(dpModelStruct* sdm, double time, double state[])
{

   int i, start_index, func_index;
   int (*user_func)();
   
   start_index = sdm->nq + sdm->nu;
   for (i=0; i<sdm->num_muscles; i++)
   {
      func_index = *(sdm->muscles[i].muscle_model_index);
      user_func = muscle_assign_func[func_index];
      start_index += user_func(time,&sdm->muscles[i],&state[start_index]);
   }
   check_for_sderror("ASSIGN_MUSCLE_STATES");
}



/* APPLY_MUSCLE_FORCES: this routine applies the muscle forces to the body
 * segments. It does so without calculating moment arms and joint torques.
 * Rather, for each muscle it pulls on the body segment where the muscle 
 * originates, and on the body segment where the muscle inserts. Moment arms
 * and joint torques are only calculated if the user has set the appropriate
 * output parameters to yes.
 */
void apply_muscle_forces(dpModelStruct* sdm)
{
   int i, k, sdbody1, sdbody2, start, end;
   double force_vector[3], norm_force_vector[3], body_force_vector[3];
   double inertial_pt1[3], inertial_pt2[3];
   dpMuscleStruct* ms;

	for (i=0; i<sdm->num_muscles; i++)
	{
		ms = &sdm->muscles[i];

		/* Loop thru the list of muscle points. For each pair of
		 * adjacent muscle points which span a joint, you want
		 * to apply a force to both ends of that muscle segment.
		 * The mp[] array contains only "active" muscle
       * points (e.g., inactive via points are not included).
       */
      for (start = 0; start < ms->num_points - 1; start++)
      {
			end = start + 1;

			sdbody1 = ms->mp[start]->segment;
			sdbody2 = ms->mp[end]->segment;

			if (sdbody1 != sdbody2)  /* if body segments are not the same, a */
				  /* joint is spanned */
			{
				/* Calculate direction of force in the ground (inertial)
				 * reference frame.
				 */

				sdpos(sdbody1, ms->mp[start]->point, inertial_pt1);
				sdpos(sdbody2, ms->mp[end]->point, inertial_pt2);

				for (k=0; k<3; k++)
					force_vector[k] = inertial_pt2[k] - inertial_pt1[k];

				normalize_vector(force_vector, norm_force_vector);

				/* Apply the force to the first body segment
				 * First transform the vector into the body's reference frame,
				 * then multiply it by the magnitude of the muscle force.
				 * Since the vector goes from the first body to the second,
				 * you multiply it by the positive magnitude because you're
				 * pulling on the body segment.
				 */
            sdtrans(GROUND, norm_force_vector, sdbody1, body_force_vector);
            for (k = 0; k < 3; k++)
               body_force_vector[k] *= ms->force;
            sdpointf(sdbody1, ms->mp[start]->point, body_force_vector);

            /* Apply the muscle force to the second body segment,
             * using the same technique as above. In this case,
             * the body_force_vector points towards the second
             * body, so you want to multiply it by the negative
             * magnitude of the force so that you pull on the segment.
             */
            sdtrans(GROUND,norm_force_vector,sdbody2,body_force_vector);
            for (k=0; k<3; k++)
               body_force_vector[k] *= -ms->force;
            sdpointf(sdbody2,ms->mp[end]->point,body_force_vector);
			}
		}
	}
	check_for_sderror("APPLY_MUSC_FORCE");
}


/* CALC_MUSCLE_MOMENT_ARMS: this function calculates the moment arms for each
 * muscle for each generalized coordinate in the model (whether unconstrained,
 * constrained, or prescribed). It uses the current state of the system, and
 * assumes that muscle wrapping has already been determined. It is heavily based
 * on the algorithm and code supplied by Darryl Thelen, Ph.D., at Stanford University.
 */
void calc_muscle_moment_arms(double time, double state[])
{
	int i, k, sdbody1, sdbody2, start, end, info[50];
	double force_vector[3], norm_force_vector[3], body_force_vector[3];
	double inertial_pt1[3], inertial_pt2[3];
	double *dy, *mults;
	int rank, *multmap;
	dpMuscleStruct* ms;

   if (sdm->num_muscles < 1)
      return;

   /* Allocate space */
	dy = (double*)simm_malloc(sdm->neq*sizeof(double));
	mults = (double*)simm_malloc(sdm->neq*sizeof(double));
	multmap = (int*)simm_malloc(sdm->neq*sizeof(int));

   /* Loop through the muscles, finding the moment arms for each
	 * by applying a muscle force of 1 Newton and then determining
    * the resulting moments acting on the joints.
    */
	for (i = 0; i < sdm->num_muscles; i++)
   {
      if (sdm->muscles[i].output == dpYes)
      {
         /* reset the system state, clearing external forces */
         sdstate(time, state, &state[sdm->nq]);

         ms = &(sdm->muscles[i]);

         /* Loop thru the list of muscle points. For each pair of
	       * adjacent muscle points which span a joint, you want
	       * to apply a force of 1 Newton to both ends of that
          * muscle segment. The mp[] array contains only "active"
          * muscle points (e.g., inactive via points are not included).
          */
         for (start = 0; start < ms->num_points - 1; start++)
         {
            end = start + 1;

            sdbody1 = ms->mp[start]->segment;
            sdbody2 = ms->mp[end]->segment;

            if (sdbody1 != sdbody2)
            {
	    	      /* Calculate direction of force in the ground (inertial)
	     		    * reference frame.
	     		    */
               sdpos(sdbody1, ms->mp[start]->point, inertial_pt1);
               sdpos(sdbody2, ms->mp[end]->point, inertial_pt2);
               for (k = 0; k < 3; k++)
                  force_vector[k] = inertial_pt2[k] - inertial_pt1[k];
               normalize_vector(force_vector, norm_force_vector);

	    		   /* Apply a 1 Newton force to the first body segment
	     		    * First transform the vector into the body's reference frame,
	     		    */
               sdtrans(GROUND, norm_force_vector, sdbody1, body_force_vector);
               for (k = 0; k < 3; k++)
                  body_force_vector[k] *= 1.0;
               sdpointf(sdbody1, ms->mp[start]->point, body_force_vector);

    		   	/* Apply the muscle force to the second body segment,
     		   	 * using the same technique as above. In this case,
     		   	 * the body_force_vector points towards the second body, multiply by -1
     		   	 */
               sdtrans(GROUND, norm_force_vector, sdbody2, body_force_vector);
               for (k = 0; k < 3; k++)
                  body_force_vector[k] *= -1.0;
               sdpointf(sdbody2, ms->mp[end]->point, body_force_vector);
            }
         }

         /* Calculate the resulting generalized accelerations */
         sdderiv(dy, &dy[sdm->nq]);
         sdmult(mults, &rank, multmap);

		   /* Reset the state and determine the torques necessary to get the accelerations.
          * These torques are equal to the moment arms since the applied force is 1 Newton.
          */
         sdstate(time, state, &state[sdm->nq]);
         sdfulltrq(&dy[sdm->nq], mults, ms->momentarms);

         /* sdfulltrq() tends to return non-zero torques for all of the Qs,
          * even the constrained ones. But to accurately find moment arms,
          * we need sdfulltrq() to return zero torque for the constrained Qs,
          * and non-zero torques for the unconstrained Qs. This is because the
          * unconstrained Qs map to gencoords in SIMM, and you're really finding
          * moment arms for the SIMM gencoords, not the SD/FAST Qs. To do this,
          * you have to adjust the multipliers (returned by sdmult) for the
          * constrained Qs. Since the multipliers for constrained Qs are actually
          * the torques that sduconsfrc() applies to enforce the constraints,
          * the amount that you need to adjust each multiplier is the amount
          * of torque that sdfulltrq() returns for that Q. In other words,
          * given a multiplier (torque) for a constrained Q, sdfulltrq() returns
          * the user-applied torque that is needed to generate the specified
          * udots. If you add these torques together and pass them into sdfulltrq()
          * as a multiplier, then sdfulltrq() will determine that no more torque
          * is needed, as return zero for that Q.
          */
         for (k = 0; k < sdm->nq; k++)
         {
            /* If the Q is constrained, adjust its corresponding multiplier */
            if (sdm->q[k].constraint_num != -1)
            {
               /* get the index of the multiplier for this Q's constraint (stored in info[1]) */
               sdcons(sdm->q[k].constraint_num, info);

               /* add the torque that sdfulltrq() returns to this multplier */
               mults[info[1]] += ms->momentarms[k];
            }
         }

         /* Now that the multipliers have been adjusted for the constrained Qs,
          * pass them back into sdfulltrq() and get the moment arms.
          */
         sdfulltrq(&dy[sdm->nq], mults, ms->momentarms);

         /* Now multiply each moment arm by the sign of the conversion factor for
          * the corresponding Q, to adjust for negative kinematic functions.
          */
         for (k = 0; k < sdm->nq; k++)
            ms->momentarms[k] *= DSIGN(sdm->q[k].conversion);
      }
	}

	/* Reset the states */
	sdstate(time, state, &state[sdm->nq]);
	
	free(dy);
	free(mults);
	free(multmap);

	check_for_sderror("CALC_MUSCLE_MOMENT_ARMS");

}


void calc_ligament_force(dpMuscleStruct* ms)
{
   double strain;

   ms->fiber_length = 0.0;
   ms->muscle_tendon_vel = 0.0;
   ms->fiber_velocity = 0.0;
   ms->tendon_velocity = 0.0;

   calc_muscle_tendon_length(ms);

   if (ms->muscle_tendon_length <= (*ms->resting_tendon_length))
   {
      ms->force = 0.0;
      ms->tendon_length = (*ms->resting_tendon_length);
      return;
   }

   ms->tendon_length = ms->muscle_tendon_length;

   /* If resting tendon length is [close to] zero, there's going to be
    * trouble since fiber length is also zero. But just set strain to zero
    * and continue on. This should result in a ligament force that is
    * always zero.
    */
   if (*ms->resting_tendon_length < ROUNDOFF_ERROR)
      strain = 0.0;
   else
      strain = (ms->tendon_length)/(*ms->resting_tendon_length) - 1.0;

   ms->force = (*ms->max_isometric_force)*
               interpolate_spline(strain, ms->tendon_force_len_curve, zeroth, 1.0, 1.0);

   return;
}


/* CALC_MUSCLE_TENDON_FORCE: this routine finds the force in a muscle, assuming
 * static equilibrium. Using the total muscle-tendon length, it finds the
 * fiber and tendon lengths so that the forces in each match. This routine
 * takes pennation angle into account, so it's definition of static equilibrium
 * is when tendon_force = fiber_force * cos(pennation_angle).
 */

void calc_muscle_tendon_force(dpMuscleStruct* ms, double activation)
{

   int i;
   double tendon_elastic_modulus = 1200.0;
   double tendon_max_stress = 32.0;
   double fiber_force, muscle_width, tmp_fiber_length, min_tendon_stiffness;
   double active_force, passive_force, cos_factor, fiber_stiffness;
   double old_fiber_length, length_change, tendon_stiffness, percent;
   double error_force = 0.0, old_error_force, tendon_force, tendon_strain;
   
   /* If the muscle has no fibers, then treat it as a ligament. */
   if (*ms->optimal_fiber_length < ROUNDOFF_ERROR)
   {
      calc_ligament_force(ms);
      return;
   }

   calc_muscle_tendon_length(ms);

   /* Make first guess of fiber and tendon lengths. Make fiber length equal to
    * optimal_fiber_length so that you start in the middle of the active+passive
    * force-length curve. Muscle_width is the width, or thickness, of the
    * muscle-tendon unit. It is the shortest allowable fiber length because if
    * the muscle-tendon length is very short, the pennation angle will be 90
    * degrees and the fibers will be vertical (assuming the tendon is horizontal).
    * When this happens, the fibers are as long as the muscle is wide.
    * If the resting tendon length is zero, then set the fiber length equal to
    * the muscle tendon length / cosine_factor, and find its force directly.
    */

   muscle_width = *ms->optimal_fiber_length * sin(DEG_TO_RAD*(*ms->pennation_angle));

   if (*ms->resting_tendon_length < ROUNDOFF_ERROR)
   {
      ms->tendon_length = 0.0;
      cos_factor = cos(atan(muscle_width / ms->muscle_tendon_length));
      ms->fiber_length = ms->muscle_tendon_length / cos_factor;

      active_force = interpolate_spline(ms->fiber_length / (*ms->optimal_fiber_length),
			                               ms->active_force_len_curve, zeroth, 1.0, 1.0) * activation;
      if (active_force < 0.0)
         active_force = 0.0;

      passive_force = interpolate_spline(ms->fiber_length / (*ms->optimal_fiber_length),
		                                   ms->passive_force_len_curve, zeroth, 1.0, 1.0);
      if (passive_force < 0.0)
         passive_force = 0.0;

      ms->force = (active_force + passive_force) * (*ms->max_isometric_force) * cos_factor;
      return;
   }
   else if (ms->muscle_tendon_length < (*ms->resting_tendon_length))
   {
      ms->fiber_length = muscle_width;
      ms->tendon_length = ms->muscle_tendon_length;
      ms->force = 0.0;
      return;
   }
   else
   {
      ms->fiber_length = *ms->optimal_fiber_length;
      cos_factor = cos(DEG_TO_RAD * calc_pennation(ms->fiber_length,
						 *ms->optimal_fiber_length, *ms->pennation_angle));  
      ms->tendon_length = ms->muscle_tendon_length - ms->fiber_length * cos_factor;

      /* Check to make sure tendon is not shorter than its slack length. If it
       * is, set the length to its slack length and re-compute fiber length.
       */
      if (ms->tendon_length < (*ms->resting_tendon_length))
      {
         ms->tendon_length = (*ms->resting_tendon_length);
         cos_factor = cos(atan(muscle_width / (ms->muscle_tendon_length - ms->tendon_length)));
         ms->fiber_length = (ms->muscle_tendon_length - ms->tendon_length) / cos_factor;
         if (ms->fiber_length < muscle_width)
            ms->fiber_length = muscle_width;
      }
   }

   /* Muscle-tendon force is found using an iterative method. First, you guess
    * the length of the muscle fibers and the length of the tendon, and
    * calculate their respective forces. If the forces match (are within
    * MAXIMUMERROR of each other), stop; else change the length guesses based
    * on the error and try again.
    */
   for (i=0; i<MAX_ITERATIONS; i++)
   {
      active_force = interpolate_spline(ms->fiber_length / (*ms->optimal_fiber_length),
			                               ms->active_force_len_curve, zeroth, 1.0, 1.0) * activation;
      if (active_force < 0.0)
         active_force = 0.0;

      passive_force = interpolate_spline(ms->fiber_length / (*ms->optimal_fiber_length),
		                                   ms->passive_force_len_curve, zeroth, 1.0, 1.0);
      if (passive_force < 0.0)
         passive_force = 0.0;

      fiber_force = (active_force + passive_force) * (*ms->max_isometric_force) * cos_factor;

      tendon_strain = ((ms->tendon_length) / (*ms->resting_tendon_length) - 1.0);
      if (tendon_strain < 0.0)
         tendon_force = 0.0;
      else
         tendon_force = (*ms->max_isometric_force)*
	                     interpolate_spline(tendon_strain, ms->tendon_force_len_curve, zeroth, 1.0, 1.0);

      old_error_force = error_force;
 
      error_force = tendon_force - fiber_force;

      if (DOUBLE_ABS(error_force) <= ERROR_LIMIT) /* muscle-tendon force found! */
         break;

      if (i == 0)
         old_error_force = error_force;

      if (SIGN(error_force) != SIGN(old_error_force))
      {
         percent = DOUBLE_ABS(error_force) /
	         (DOUBLE_ABS(error_force)+DOUBLE_ABS(old_error_force));
         tmp_fiber_length = old_fiber_length;
         old_fiber_length = ms->fiber_length;
         ms->fiber_length += percent * (tmp_fiber_length-ms->fiber_length);
      } 
      else
      {
         /* Estimate the stiffnesses of the tendon and the fibers. If tendon
          * stiffness is too low, then the next length guess will overshoot
          * the equilibrium point. So we artificially raise it using the
          * normalized muscle force. (active_force+passive_force) is the
          * normalized force for the current fiber length, and we assume that
          * the equilibrium length is close to this current length. So we want
          * to get force = (active_force+passive_force) from the tendon as well.
          * We hope this will happen by setting the tendon stiffness to
          * (active_force+passive_force) times its maximum stiffness.
          */
         tendon_stiffness = (*ms->max_isometric_force)/(*ms->resting_tendon_length)*
	         interpolate_spline(tendon_strain,ms->tendon_force_len_curve,first,1.0,1.0);

         min_tendon_stiffness = (active_force+passive_force)*
	         tendon_elastic_modulus*(*ms->max_isometric_force)/
	         (tendon_max_stress*(*ms->resting_tendon_length));

         if (tendon_stiffness < min_tendon_stiffness)
            tendon_stiffness = min_tendon_stiffness;

         fiber_stiffness = (*ms->max_isometric_force)/(*ms->optimal_fiber_length)*
            (interpolate_spline(ms->fiber_length/(*ms->optimal_fiber_length),
            ms->active_force_len_curve,first,1.0,1.0) +
            interpolate_spline(ms->fiber_length/(*ms->optimal_fiber_length),
            ms->passive_force_len_curve,first,1.0,1.0));

         /* determine how much the fiber and tendon lengths have to
          * change to make the error_force zero. But don't let the
	       * length change exceed half the optimal fiber length because
	       * that's too big a change to make all at once.
          */
         length_change = fabs(error_force/(fiber_stiffness/cos_factor+
            tendon_stiffness));

         if (fabs(length_change/(*ms->optimal_fiber_length)) > 0.5)
            length_change = 0.5*(*ms->optimal_fiber_length);

         /* now change the fiber length depending on the sign of the error
          * and the sign of the fiber stiffness (which equals the sign of
          * the slope of the muscle's force-length curve).
          */
         old_fiber_length = ms->fiber_length;

         if (error_force > 0.0)
            ms->fiber_length += length_change;
         else
            ms->fiber_length -= length_change;
      }

      cos_factor = cos(DEG_TO_RAD*calc_pennation(ms->fiber_length,
						 *ms->optimal_fiber_length,
						 *ms->pennation_angle));
      ms->tendon_length = ms->muscle_tendon_length - ms->fiber_length*cos_factor;

      /* Check to make sure tendon is not shorter than its slack length. If it is,
       * set the length to its slack length and re-compute fiber length.
       */
      if (ms->tendon_length < (*ms->resting_tendon_length))
      {
         ms->tendon_length = (*ms->resting_tendon_length);
         cos_factor = cos(atan(muscle_width/(ms->muscle_tendon_length-
            ms->tendon_length)));
         ms->fiber_length = (ms->muscle_tendon_length-ms->tendon_length)/cos_factor;
      }
   }

   ms->force = tendon_force;
}



/* CALC_MUSCLE_TENDON_VELOCITY: this routine calculates the velocity of a muscle-
 * tendon unit. It does so by summing the velocities of the individual segments
 * in the muscle-tendon path.
 */

double calc_muscle_tendon_velocity(dpMuscleStruct* ms)
{

   int start, end;

   ms->muscle_tendon_vel = 0.0;             /* start: velocity = 0.0 */

   /* Find musculotendon velocity by summing velocities of the segments:
    * The mp[] array contains only "active" muscle
    * points (e.g., inactive via points are not included).
    */

   for (start = 0; start < ms->num_points - 1; start++)
   {
      end = start + 1;
      ms->muscle_tendon_vel +=
            calc_muscle_seg_velocity(ms->mp[start]->point,ms->mp[start]->segment,
				     ms->mp[end]->point,ms->mp[end]->segment);
   }

   return ms->muscle_tendon_vel;

}



/* CALC_MUSCLE_SEG_VELOCITY: this routine finds the velocity of one segment (piece)
 * in a muscle-tendon path.
 */

static double calc_muscle_seg_velocity(double p1[], int seg1, double p2[], int seg2)
{

   int i;
   double v1[3], v2[3], v_relative[3], vpiece;
   double inertial_p1[3], inertial_p2[3], p_relative[3], p_rel_norm[3];

   sdpos(seg1,p1,inertial_p1);
   sdvel(seg1,p1,v1);
   sdpos(seg2,p2,inertial_p2);
   sdvel(seg2,p2,v2);

   for (i=0; i<3; i++)
   {
      p_relative[i] = inertial_p2[i] - inertial_p1[i];
      v_relative[i] = v2[i] - v1[i];
   }

   normalize_vector(p_relative,p_rel_norm);
   vpiece = (v_relative[0]*p_rel_norm[XX] + v_relative[1]*p_rel_norm[YY] +
	     v_relative[2]*p_rel_norm[ZZ]);

   return (vpiece);

}



/* CALC_FIBER_VELOCITY: written by Chris Raasch and Lisa Schutte
 * this routine calculates the fiber velocity using
 * an inverse muscle force-velocity relationship with damping. It should
 * someday be replaced by a new force-velocity spline in the muscle input
 * file, but for now it includes constants as Chris and Lisa derived them
 * for their specific muscle model.
 */

double calc_fiber_velocity(dpMuscleStruct* ms, double activation,
			   double active_force, double velocity_dependent_force)
{

   double b, c, fiber_velocity, muscle_damping;
   double kv = 0.15, slope_k = 0.13, fmax = 1.4;

   muscle_damping = get_muscle_param_value(ms,"damping");

   if (velocity_dependent_force < -muscle_damping)
      fiber_velocity = velocity_dependent_force / muscle_damping;
   else if (velocity_dependent_force < activation * active_force)
   {
      c = kv * (velocity_dependent_force - activation*active_force) / muscle_damping;
      b = -kv * (velocity_dependent_force/kv + activation*active_force +
		 muscle_damping) / muscle_damping;
      fiber_velocity = (-b-sqrt(b*b-4*c)) / 2.0;
   }
   else
   {
      c = -(slope_k*kv/((muscle_damping*(kv+1))))*
	      (velocity_dependent_force-activation*active_force);
      b = -(velocity_dependent_force/muscle_damping
         -fmax*activation*active_force/muscle_damping-slope_k*kv/(kv+1));
      fiber_velocity = (-b+sqrt(b*b-4*c)) / 2.0;
   }

   /* Store fiber velocity in muscle structure */

   ms->fiber_velocity = fiber_velocity * (*(ms->optimal_fiber_length))
      / get_muscle_param_value(ms,"timescale");

   return (fiber_velocity);

}



/* CALC_NONZERO_PASSIVE_FORCE: written by Chris Raasch and Lisa Schutte
 * this routine calculates the passive force in the muscle fibers using
 * an exponential instead of cubic splines.  This results
 * in non-zero passive force for any fiber length (and thus prevents "slack"
 * muscle/tendon problems.  It includes the contribution of an exponential
 * passive force-length curve (which equals 1.0 at norm_fiber_length = 1.5)
 * as well as the damping effects due to contraction velocity. It should
 * someday be replaced by a new passive-force spline in the muscle input
 * file, but for now it includes constants as Chris and Lisa derived them
 * for their specific muscle model.
 */

double calc_nonzero_passive_force(dpMuscleStruct* ms, double norm_fiber_length,
				  double norm_fiber_velocity)
{

   double passive_force, flcomponent;

   flcomponent = exp(8.0*(norm_fiber_length-1.0)) / exp(4.0);

   passive_force = flcomponent + get_muscle_param_value(ms,"damping") *
      norm_fiber_velocity;

   return (passive_force);

}



/* COUNT_MUSCLE_STATES: This routine counts the total number of muscle states for
 * all of the muscles in the model. Since the only place where the number of states
 * in a particular muscle model is known is in the three muscle-model routines
 * (in derivs.c, inits.c, and assigns.c), you have to call one of these routines
 * for each muscle. The assign function is called because it should be the simplest
 * and fastest routine to call. A fake state vector is created because one must be
 * passed into the assign function. This vector should be large enough to hold the
 * maximum number of states in any one muscle model.
 */

int count_muscle_states(dpModelStruct* sdm)
{
   int i, count, func_index;
   int (*user_func)();
   double fake_states[50];

   for (i = 0; i < sdm->num_muscles; i++)
      if (sdm->muscles[i].muscle_model_index == NULL)
         sim_message(exit_program, "Muscle %s: muscle_model undefined.", sdm->muscles[i].name);

   for (i=0; i<50; i++)
      fake_states[i] = 0.0;

   for (i=0, count=0; i<sdm->num_muscles; i++)
   {
      func_index = *(sdm->muscles[i].muscle_model_index);
      user_func = muscle_assign_func[func_index];
      count += user_func(0.0,&sdm->muscles[i],fake_states);
   }

   return count;
}


/* CALC_MUSCLE_POWER: This routine calculates the power that a muscle applies
 * to the body segments. To do this, it assumes that the muscle force has
 * already been calculated, and it finds the force vector and velocity of the
 * point of application for both ends of each 'free' segment.
 */

void calc_muscle_power(dpMuscleStruct* ms)
{

   int k, sdbody1, sdbody2, start, end;
   double force_vector[3], norm_force_vector[3];
   double inertial_pt1[3], inertial_pt2[3], pt_vel[3];

   ms->applied_power = 0.0;

   /* Loop thru the list of muscle points. For each pair of
    * adjacent muscle points which span a joint, you want to
    * calculate the power that the muscle applies to the two body segments.
    * The mp[] array contains only "active" muscle
    * points (e.g., inactive via points are not included).
    */

   for (start = 0; start < ms->num_points - 1; start++)
   {
      end = start + 1;

      sdbody1 = ms->mp[start]->segment;
      sdbody2 = ms->mp[end]->segment;

      if (sdbody1 != sdbody2)  /* if body segments are not same, a joint is spanned */
      {
         /* Calculate direction of force in the ground (inertial) reference frame */

         sdpos(sdbody1,ms->mp[start]->point,inertial_pt1);
         sdpos(sdbody2,ms->mp[end]->point,inertial_pt2);

         for (k=0; k<3; k++)
            force_vector[k] = inertial_pt2[k] - inertial_pt1[k];

         normalize_vector(force_vector,norm_force_vector);

         /* Calculate the power that the muscle applies to both body segments
          * The equation for applied power is:
          * power = muscle-force dotted with velocity of attachment point.
          */

         sdvel(sdbody1,ms->mp[start]->point,pt_vel);
         ms->applied_power += ms->force*(norm_force_vector[XX]*pt_vel[XX] +
            norm_force_vector[YY]*pt_vel[YY] +
            norm_force_vector[ZZ]*pt_vel[ZZ]);

         sdvel(sdbody2,ms->mp[end]->point,pt_vel);
         ms->applied_power += ms->force*(-norm_force_vector[XX]*pt_vel[XX] +
            -norm_force_vector[YY]*pt_vel[YY] +
            -norm_force_vector[ZZ]*pt_vel[ZZ]);
      }
   }

}

