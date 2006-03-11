/*******************************************************************************

   DERIVS.C

   Authors: Peter Loan
            Chris Raasch (func3)
            Lisa Schutte (func4)
            Felix Zajac (func5)
            Ning Lan (func6)
            Steven Piazza (func7)

   Copyright (c) 1996-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains 10 routines to calculate state derivatives
      for dimensionless muscle-tendon models. The routines are named
      muscle_deriv_func1() through muscle_deriv_func10(), and each one
      calculates all of a muscle's derivatives for a particular muscle-tendon
      model.

   Routines:
      muscle_deriv_func1  : 3 states (act, fiber_len, fiber_vel), no pennation
      muscle_deriv_func2  : 3-state model, pennation included
      muscle_deriv_func3  : like func2 plus 4th state for muscle power
      muscle_deriv_func4  : 2 states (act, fiber_len), non-zero passive force
      muscle_deriv_func5  : 1 state (act), infinitely stiff tendon
      muscle_deriv_func6  : 4 state
      muscle_deriv_func7  : 0 state, ligament model
      muscle_deriv_func8  : unused
      muscle_deriv_func9  : unused
      muscle_deriv_func10 : unused

*******************************************************************************/

#include "universal.h"


/* A 3-state model, with states of activation, muscle fiber length, and muscle
 * fiber velocity. It should not be used for muscles with resting tendon lengths
 * of zero because it will always calculate a muscle force of zero.
 */
int muscle_deriv_func1(double time, dpMuscleStruct* ms, double state[],
		                 double dstate[], double* muscle_force)
{
   int numStates = 3;
   int activation = 0, fiber_length = 1, fiber_velocity = 2;
   double exc, tendon_force, fiber_force, muscle_mass;
   double normstate[3], normdstate[3], norm_tendon_length;
   double norm_muscle_tendon_length;
   double c_tau, mass_param, c_act_1, c_act_2;

   c_tau = get_muscle_param_value(ms,"timescale");
   mass_param = get_muscle_param_value(ms,"mass");
   c_act_1 = get_muscle_param_value(ms,"activation1");
   c_act_2 = get_muscle_param_value(ms,"activation2");

   /* Assume that the excitation level has been calculated and stored in the muscle
    * structure before the integrator is called. See note in main.c for details.
    */
   exc = ms->excitation_level;

   /* Normalize the muscle states */
   normstate[activation] = state[activation];
   normstate[fiber_length] = state[fiber_length] / (*(ms->optimal_fiber_length));
   normstate[fiber_velocity] = state[fiber_velocity] * (c_tau / (*(ms->optimal_fiber_length)));
  
   /* Compute normalized muscle state derivatives */
   normdstate[activation] = (exc - normstate[activation]) * (c_act_1 * exc + c_act_2);
   normdstate[fiber_length] = normstate[fiber_velocity];
   norm_muscle_tendon_length = calc_muscle_tendon_length(ms) / (*(ms->optimal_fiber_length));
   norm_tendon_length = norm_muscle_tendon_length - normstate[fiber_length];

   tendon_force = calc_tendon_force(ms, norm_tendon_length);
   fiber_force = calc_fiber_force(ms, normstate[activation], normstate[fiber_length],
				  normstate[fiber_velocity]);

   muscle_mass = mass_param * (*(ms->optimal_fiber_length)/c_tau) *
      (*(ms->optimal_fiber_length)/c_tau);
   normdstate[fiber_velocity] = (tendon_force - fiber_force)/muscle_mass;

   /* Un-normalize the muscle state derivatives */
   dstate[activation] = normdstate[activation] / c_tau;
   dstate[fiber_length] = normdstate[fiber_length] * (*(ms->optimal_fiber_length)) / c_tau;
   dstate[fiber_velocity] = normdstate[fiber_velocity] *
                            (*(ms->optimal_fiber_length)) / (c_tau * c_tau);
  
   /* Store tendon force (same as muscle-tendon force) in the muscle structure,
    * and don't let it go below zero.
    */
   ms->force = tendon_force * (*(ms->max_isometric_force));
   if (ms->force < 0.0)
      ms->force = 0.0;

   *muscle_force = ms->force;

   return numStates;
}



/* Model 2 is just like model 1 except that the fiber velocity equation accounts
 * for the pennation angle of the fibers. As with model 1, this one should not be
 * used for muscles with resting tendon lengths of zero.
 */

int muscle_deriv_func2(double time, dpMuscleStruct* ms, double state[],
		                 double dstate[], double* muscle_force)
{
   int numStates = 3;
   int activation = 0, fiber_length = 1, fiber_velocity = 2;
   double exc, tendon_force, fiber_force, muscle_mass;
   double normstate[3], normdstate[3], norm_tendon_length, ca, ta;
   double norm_muscle_tendon_length, mass_term, vel_term, pennation_angle;
   double c_tau, mass_param, c_act_1, c_act_2;

   c_tau = get_muscle_param_value(ms,"timescale");
   mass_param = get_muscle_param_value(ms,"mass");
   c_act_1 = get_muscle_param_value(ms,"activation1");
   c_act_2 = get_muscle_param_value(ms,"activation2");

   /* Assume that the excitation level has been calculated and stored in the muscle
    * structure before the integrator is called. See note in formain.c for details.
    */
   exc = ms->excitation_level;

   /* Normalize the muscle states */
   normstate[activation] = state[activation];
   normstate[fiber_length] = state[fiber_length] / (*(ms->optimal_fiber_length));
   normstate[fiber_velocity] = state[fiber_velocity] * (c_tau / (*(ms->optimal_fiber_length)));
  
   /* Compute normalized muscle state derivatives */
   normdstate[activation] = (exc - normstate[activation]) * (c_act_1 * exc + c_act_2);
   normdstate[fiber_length] = normstate[fiber_velocity];
   pennation_angle = calc_pennation(normstate[fiber_length], 1.0, (*(ms->pennation_angle)));
   ca = cos(DEG_TO_RAD*pennation_angle);
   ta = tan(DEG_TO_RAD*pennation_angle);
   norm_muscle_tendon_length = calc_muscle_tendon_length(ms) / (*(ms->optimal_fiber_length));
   norm_tendon_length = norm_muscle_tendon_length - normstate[fiber_length]*ca;
   tendon_force = calc_tendon_force(ms, norm_tendon_length);
   fiber_force = calc_fiber_force(ms, normstate[activation], normstate[fiber_length],
				                      normstate[fiber_velocity]);

   muscle_mass = mass_param * (*(ms->optimal_fiber_length) / c_tau) *
                 (*(ms->optimal_fiber_length)/c_tau);
   mass_term = (tendon_force * ca - fiber_force * ca * ca) / muscle_mass;
   vel_term = normstate[fiber_velocity] * normstate[fiber_velocity] * ta * ta /
              normstate[fiber_length];
   normdstate[fiber_velocity] = mass_term + vel_term;

   /* Un-normalize the muscle state derivatives */
   dstate[activation] = normdstate[activation] / c_tau;
   dstate[fiber_length] = normdstate[fiber_length] * (*(ms->optimal_fiber_length)) / c_tau;
   dstate[fiber_velocity] = normdstate[fiber_velocity] *
                            (*(ms->optimal_fiber_length)) / (c_tau * c_tau);

   /* Store tendon force (same as muscle-tendon force) in the muscle structure,
    * and don't let it go below zero.
    */
   ms->force = tendon_force * (*(ms->max_isometric_force));
   if (ms->force < 0.0)
      ms->force = 0.0;

   *muscle_force = ms->force;

   return numStates;
}



/* Model 3 is just like model 2 but with a fourth state for muscle energy,
 * which is the integral of the power applied to the body segments. It should
 * not be used for muscles with resting tendon lengths of zero because it
 * will always calculate a muscle force of zero. This model was designed by
 * Chris Raasch, Ph.D.
 */

int muscle_deriv_func3(double time, dpMuscleStruct* ms, double state[],
		                 double dstate[], double* muscle_force)
{
   int numStates = 4;
   int activation = 0, fiber_length = 1, fiber_velocity = 2, energy = 3;
   double exc, ca, ta, tendon_force, fiber_force, muscle_mass;
   double normstate[4], normdstate[4], norm_tendon_length;
   double pennation_angle, mass_term, vel_term, norm_muscle_tendon_length;
   double c_tau, mass_param, c_act_1, c_act_2;

   c_tau = get_muscle_param_value(ms,"timescale");
   mass_param = get_muscle_param_value(ms,"mass");
   c_act_1 = get_muscle_param_value(ms,"activation1");
   c_act_2 = get_muscle_param_value(ms,"activation2");

   /* Assume that the excitation level has been calculated and stored in the muscle
    * structure before the integrator is called. See note in formain.c for details.
    */
   exc = ms->excitation_level;

   /* Normalize the muscle states */
   normstate[activation] = state[activation];
   normstate[fiber_length] = state[fiber_length] / (*(ms->optimal_fiber_length));
   normstate[fiber_velocity] = state[fiber_velocity] * (c_tau / (*(ms->optimal_fiber_length)));
   normstate[energy] = state[energy];
  
   /* Compute normalized muscle state derivatives */
   normdstate[activation] = (exc - normstate[activation]) * (c_act_1 * exc + c_act_2);
   normdstate[fiber_length] = normstate[fiber_velocity];
   pennation_angle = calc_pennation(normstate[fiber_length], 1.0, (*(ms->pennation_angle)));
   ca = cos(DEG_TO_RAD*pennation_angle);
   ta = tan(DEG_TO_RAD*pennation_angle);
   norm_muscle_tendon_length = calc_muscle_tendon_length(ms) / (*(ms->optimal_fiber_length));
   norm_tendon_length = norm_muscle_tendon_length - normstate[fiber_length]*ca;
   tendon_force = calc_tendon_force(ms,norm_tendon_length);
   fiber_force = calc_fiber_force(ms,normstate[activation], normstate[fiber_length],
				                      normstate[fiber_velocity]);

   muscle_mass = mass_param * (*(ms->optimal_fiber_length)/c_tau) *
                 (*(ms->optimal_fiber_length)/c_tau);
   mass_term = (tendon_force*ca - fiber_force*ca*ca) / muscle_mass;
   vel_term = normstate[fiber_velocity] * normstate[fiber_velocity] * ta * ta / normstate[fiber_length];
   normdstate[fiber_velocity] = mass_term + vel_term;
   calc_muscle_power(ms);
   normdstate[energy] = ms->applied_power;

   /* Un-normalize the muscle state derivatives */
   dstate[activation] = normdstate[activation] / get_muscle_param_value(ms,"timescale");
   dstate[fiber_length] = normdstate[fiber_length] * (*(ms->optimal_fiber_length)) / c_tau;
   dstate[fiber_velocity] = normdstate[fiber_velocity] *
      (*(ms->optimal_fiber_length)) / (c_tau * c_tau);
   dstate[energy] = normdstate[energy];
  
   /* Store tendon force (same as muscle-tendon force) in the muscle structure,
    * and don't let it go below zero.
    */
   ms->force = tendon_force * (*(ms->max_isometric_force));
   if (ms->force < 0.0)
      ms->force = 0.0;

   *muscle_force = ms->force;

   return numStates;
}



/* Model 4 is a 2-state model which was designed to improve performance
 * and accuracy from the 3-state model (model 2). It does not include
 * muscle mass, but uses an inverse force-velocity relation which
 * includes damping. It should not be used for muscles with resting tendon
 * lengths of zero because it will always calculate a muscle force of zero.
 * This model was developed by Lisa Schutte, Ph.D.
 */
int muscle_deriv_func4(double time, dpMuscleStruct* ms, double state[],
		                 double dstate[], double* muscle_force)
{
   int numStates = 2;
   int activation = 0, fiber_length = 1;
   double exc, tendon_force, active_force;
   double passive_force, velocity_dependent_force;
   double normstate[2], normdstate[2], norm_tendon_length, ca;
   double norm_muscle_tendon_length, pennation_angle;
   double h, w, new_fiber_length, new_pennation_angle, new_ca;
   double c_tau, c_act_1, c_act_2;

   c_tau = get_muscle_param_value(ms,"timescale");
   c_act_1 = get_muscle_param_value(ms,"activation1");
   c_act_2 = get_muscle_param_value(ms,"activation2");

   /* Assume that the excitation level has been calculated and stored in the muscle
    * structure before the integrator is called. See note in formain.c for details.
    */
   exc = ms->excitation_level;

   /* Normalize the muscle states */
   normstate[activation] = state[activation];
   normstate[fiber_length] = state[fiber_length] / (*(ms->optimal_fiber_length));
  
   /* Compute normalized muscle state derivatives */
   if (exc >= normstate[activation])
      normdstate[activation] = (exc - normstate[activation]) *
	 (c_act_1 * exc + c_act_2);
   else
      normdstate[activation] = (exc - normstate[activation]) * c_act_2;

   pennation_angle = calc_pennation(normstate[fiber_length], 1.0, (*(ms->pennation_angle)));
   ca = cos(DEG_TO_RAD*pennation_angle);
   norm_muscle_tendon_length = calc_muscle_tendon_length(ms) / (*(ms->optimal_fiber_length));
   norm_tendon_length = norm_muscle_tendon_length - normstate[fiber_length] * ca;
   tendon_force = calc_tendon_force(ms, norm_tendon_length);
   passive_force = calc_nonzero_passive_force(ms, normstate[fiber_length],0.0);
   active_force = calc_active_force(ms, normstate[fiber_length]);

   /* If pennation equals 90 degrees, fiber length equals muscle width and fiber
    * velocity goes to zero.  Pennation will stay at 90 until tendon starts to
    * pull, then "stiff tendon" approximation is used to calculate approximate
    * fiber velocity (a kluge, I know)
    */

   if (EQUAL_WITHIN_ERROR(ca,0.0))
   {
      if (EQUAL_WITHIN_ERROR(tendon_force,0.0))
      {
         normdstate[fiber_length] = 0.0;
         ms->fiber_velocity = 0.0;
      }
      else
      {
         h = norm_muscle_tendon_length - (*(ms->resting_tendon_length));
         w = (*(ms->optimal_fiber_length)) * sin((*(ms->pennation_angle)) * DEG_TO_RAD);
         new_fiber_length = sqrt(h*h + w*w) / (*(ms->optimal_fiber_length));
         new_pennation_angle = calc_pennation(new_fiber_length, 1.0,
                                              (*(ms->pennation_angle)));
         new_ca = cos(new_pennation_angle);
         normdstate[fiber_length] = calc_muscle_tendon_velocity(ms) *
                                    c_tau / (*(ms->optimal_fiber_length)) * new_ca;
         ms->fiber_velocity = normdstate[fiber_length];
      }
   }
   else
   {
      velocity_dependent_force = tendon_force / ca - passive_force;
      normdstate[fiber_length] = calc_fiber_velocity(ms, normstate[activation],
				                                         active_force, velocity_dependent_force);
   }

   /* Un-normalize the muscle state derivatives */
   dstate[activation] = normdstate[activation] / c_tau;
   dstate[fiber_length] = normdstate[fiber_length] * (*(ms->optimal_fiber_length)) / c_tau;

   /* Store tendon force (same as muscle-tendon force) in the muscle structure,
    * and don't let it go below zero.
    */
   ms->force = tendon_force * (*(ms->max_isometric_force));
   if (ms->force < 0.0)
      ms->force = 0.0;

   *muscle_force = ms->force;

   return numStates;
}



/* Model 5 is a 1-state model that was designed to be significantly faster
 * than any other model. It uses an infinitely stiff tendon to remove
 * the fiber_len state, leaving only activation dynamics. This model can be
 * used for muscles which have resting tendon lengths of zero. The model was
 * designed by Felix Zajac, Ph.D., at Stanford University.
 */

int muscle_deriv_func5(double time, dpMuscleStruct* ms, double state[],
		                 double dstate[], double* muscle_force)
{
   int numStates = 1;
   int activation = 0;
   double exc, ca, h, w, fiber_force, tendon_force;
   double norm_fiber_length, norm_fiber_velocity;
   double normstate[1], normdstate[1], norm_tendon_length;
   double norm_muscle_tendon_length, pennation_angle;
   double c_tau, c_act_1, c_act_2;

   c_tau = get_muscle_param_value(ms,"timescale");
   c_act_1 = get_muscle_param_value(ms,"activation1");
   c_act_2 = get_muscle_param_value(ms,"activation2");

   /* Assume that the excitation level has been calculated and stored in the muscle
    * structure before the integrator is called. See note in formain.c for details.
    */
   exc = ms->excitation_level;

   /* Normalize the muscle states */
   normstate[activation] = state[activation];
  
   /* Compute normalized muscle state derivatives */
   if (exc - normstate[activation] >= 0.0)
      normdstate[activation] = (exc - normstate[activation]) * (c_act_1 * exc + c_act_2);
   else
      normdstate[activation] = (exc - normstate[activation]) * c_act_2;

/* Without pennation:
   norm_muscle_tendon_length = calc_muscle_tendon_length(ms) / (*(ms->optimal_fiber_length));
   norm_tendon_length = (*(ms->resting_tendon_length)) / (*(ms->optimal_fiber_length));
   norm_fiber_length = (norm_muscle_tendon_length - norm_tendon_length);
   norm_fiber_velocity = calc_muscle_tendon_velocity(ms) * c_tau / (*(ms->optimal_fiber_length));
   tendon_force = calc_fiber_force(ms,normstate[activation],norm_fiber_length,
                                   norm_fiber_velocity);
*/

   /* With pennation: */
   norm_muscle_tendon_length = calc_muscle_tendon_length(ms);
   norm_tendon_length = (*(ms->resting_tendon_length));
   h = norm_muscle_tendon_length - norm_tendon_length;
   w = (*(ms->optimal_fiber_length)) * sin((*(ms->pennation_angle))*DEG_TO_RAD);

   if (EQUAL_WITHIN_ERROR(h,0.0) || h < 0.0)
   {
      norm_fiber_length = w / (*(ms->optimal_fiber_length));
      norm_fiber_velocity = 0.0;
      tendon_force = 0.0;
   }
   else
   {
      norm_fiber_length = sqrt(h*h + w*w) / (*(ms->optimal_fiber_length));
      pennation_angle = calc_pennation(norm_fiber_length, 1.0, (*(ms->pennation_angle)));
      ca = cos(DEG_TO_RAD * pennation_angle);
      norm_fiber_velocity = calc_muscle_tendon_velocity(ms) *
	                         get_muscle_param_value(ms,"timescale") /
                            (*(ms->optimal_fiber_length)) * ca;

      fiber_force = calc_fiber_force(ms, normstate[activation], norm_fiber_length,
				                         norm_fiber_velocity);
      tendon_force = fiber_force * ca;
   }

   /* Un-normalize the muscle state derivatives */
   dstate[activation] = normdstate[activation] / c_tau;
  
   /* Store force, length, and velocity in the muscle structure */  
   ms->force = tendon_force * (*(ms->max_isometric_force));
   ms->fiber_length = norm_fiber_length * (*(ms->optimal_fiber_length));
   ms->fiber_velocity = norm_fiber_velocity * (*(ms->optimal_fiber_length)) / c_tau;

   if (ms->force < 0.0)
      ms->force = 0.0;

   *muscle_force = ms->force;

   return numStates;
}


/* Model 6 is a 4-state model that combines model 4's two states
 * with two new energy states. This model does not include
 * muscle mass, but uses an inverse force-velocity relation which
 * includes damping. It also contains a state for storing the heat
 * energy that a muscle generates as well as a state for storing the
 * mechanical energy that a muscle applies to the body segments.
 * This model should not be used for muscles which have resting tendon
 * lengths of zero because it will always calculate a muscle force of
 * zero. The model was designed and implemented by Ning Lan, Ph.D., at
 * the University of Southern California.
 */

int muscle_deriv_func6(double time, dpMuscleStruct* ms, double state[],
		                 double dstate[], double* muscle_force)
{
   int numStates = 4;
   int activation = 0, fiber_length = 1, heat_energy = 2,mechanical_energy = 3;
   double exc, tendon_force, active_force, v_max;
   double passive_force, velocity_dependent_force;
   double normstate[4], normdstate[4], norm_tendon_length, ca;
   double norm_muscle_tendon_length, pennation_angle;
   double h, w, new_fiber_length, new_pennation_angle, new_ca;
   double c_tau, c_act_1, c_act_2, c_heat_r, c_heat_c1, c_heat_alpha;

   c_tau = get_muscle_param_value(ms,"timescale");
   c_act_1 = get_muscle_param_value(ms,"activation1");
   c_act_2 = get_muscle_param_value(ms,"activation2");
   c_heat_r = get_muscle_param_value(ms,"heat_r");
   c_heat_c1 = get_muscle_param_value(ms,"heat_c1");
   c_heat_alpha = get_muscle_param_value(ms,"heat_alpha");

   /* Assume that the excitation level has been calculated and stored in the muscle
    * structure before the integrator is called. See note in formain.c for details.
    */
   exc = ms->excitation_level;

   /* Normalize the muscle states */
   normstate[activation] = state[activation];
   normstate[fiber_length] = state[fiber_length] / (*(ms->optimal_fiber_length));
   normstate[heat_energy] = state[heat_energy];
   normstate[mechanical_energy] = state[mechanical_energy];

   /* Compute normalized muscle state derivatives */
   if (exc >= normstate[activation])
      normdstate[activation] = (exc - normstate[activation]) * (c_act_1 * exc + c_act_2);
   else
      normdstate[activation] = (exc - normstate[activation]) * c_act_2;

   pennation_angle = calc_pennation(normstate[fiber_length],1.0,
                                    (*(ms->pennation_angle)));
   ca = cos(DEG_TO_RAD*pennation_angle);
   norm_muscle_tendon_length = calc_muscle_tendon_length(ms) /
                               (*(ms->optimal_fiber_length));
   norm_tendon_length = norm_muscle_tendon_length - normstate[fiber_length] * ca;
   tendon_force = calc_tendon_force(ms,norm_tendon_length);
   passive_force = calc_nonzero_passive_force(ms, normstate[fiber_length], 0.0);
   active_force = calc_active_force(ms, normstate[fiber_length]);

   /* If pennation equals 90 degrees, fiber length equals muscle width and fiber
    * velocity goes to zero.  Pennation will stay at 90 until tendon starts to
    * pull, then "stiff tendon" approximation is used to calculate approximate
    * fiber velocity (a kluge, I know)
    */

   if (EQUAL_WITHIN_ERROR(ca,0.0))
   {
      if (EQUAL_WITHIN_ERROR(tendon_force,0.0))
      {
         normdstate[fiber_length] = 0.0;
         ms->fiber_velocity = 0.0;
      }
      else
      {
         h = norm_muscle_tendon_length - (*(ms->resting_tendon_length));
         w = (*(ms->optimal_fiber_length)) * sin((*(ms->pennation_angle))*DEG_TO_RAD);
         new_fiber_length = sqrt(h*h + w*w) / (*(ms->optimal_fiber_length));
         new_pennation_angle = calc_pennation(new_fiber_length,1.0,
                                              (*(ms->pennation_angle)));
         new_ca = cos(new_pennation_angle);
         normdstate[fiber_length] = calc_muscle_tendon_velocity(ms) *
            c_tau / (*(ms->optimal_fiber_length)) * new_ca;
         ms->fiber_velocity = normdstate[fiber_length] *
            (*(ms->optimal_fiber_length)) / c_tau;
      }
   }
   else
   {
      velocity_dependent_force = tendon_force / ca - passive_force;
      normdstate[fiber_length] = calc_fiber_velocity(ms, normstate[activation],
				                                         active_force, velocity_dependent_force);
   }

   v_max = *(ms->max_contraction_vel);

   if (normdstate[fiber_length] <= (0.051 * v_max / c_tau))
   {
      normdstate[heat_energy] =
         ((0.3 * c_heat_c1 + 0.7 * c_heat_c1 * active_force) *
	      ms->dynamic_activation +
         c_heat_alpha * v_max) * ms->dynamic_activation * c_heat_r;
   }
   else
   {
      normdstate[heat_energy] =
         ((0.3 * c_heat_c1 + 0.7 * c_heat_c1 * active_force) *
	      ms->dynamic_activation -
         c_heat_alpha * v_max - 0.035) * ms->dynamic_activation * c_heat_r;
   }

   calc_muscle_power(ms);
   normdstate[mechanical_energy] = ms->applied_power;

   /* Un-normalize the muscle state derivatives */
   dstate[activation] = normdstate[activation] / c_tau;
   dstate[fiber_length] = normdstate[fiber_length] * (*(ms->optimal_fiber_length)) / c_tau;
   dstate[heat_energy] = normdstate[heat_energy];
   dstate[mechanical_energy] = normdstate[mechanical_energy];

   /* Store tendon force (same as muscle-tendon force) in the muscle structure,
    * and don't let it go below zero.
    */
   ms->force = tendon_force * (*(ms->max_isometric_force));
   if (ms->force < 0.0)
      ms->force = 0.0;

   *muscle_force = ms->force;

   return numStates;
}

/* Model 7 is a zero-state model that computes ligament forces.  Ligaments
 * are assumed to be modeled as springs with force-elongation curves given
 * by the tendon force length curve of the "muscle". This model should not
 * be used for muscles with resting tendon lengths of zero. The model was
 * developed by Stephen Piazza, Ph.D., now at Pennsylvania State University.
 */

int muscle_deriv_func7(double time, dpMuscleStruct* ms, double state[],
		                 double dstate[], double* muscle_force)
{
   int numStates = 0;
   double ligament_force, ligament_length, ligament_strain;

   /* the entire muscle-tendon unit is ligament */
	ligament_length = calc_muscle_tendon_length(ms);
	
   /* strain = (length - slack_length) / slack_length */
   if (*(ms->resting_tendon_length) < ROUNDOFF_ERROR)
      ligament_strain = 0.0;
   else
      ligament_strain = (ligament_length - (*(ms->resting_tendon_length))) /
			(*(ms->resting_tendon_length));

	/* ligament force = 0 if length < slack_length
	 *	               = Kx^2 if length > slack_length, x = strain
	 * tendon_force_length_curve should be y = X^2
	 */
	if (ligament_strain < 0.0)
		ligament_force = 0.0;
	else
		ligament_force = interpolate_spline(ligament_strain,
					                           ms->tendon_force_len_curve, zeroth, 1.0, 1.0);
	
	/* force = strain^2 * K */
	ms->force = ligament_force * (*(ms->max_isometric_force));
   if (ms->force < 0.0)
      ms->force = 0.0;

	*muscle_force = ms->force;
	
   return numStates;
}


int muscle_deriv_func8(double time, dpMuscleStruct* ms, double state[],
		       double dstate[], double* muscle_force)
{
   int numStates = 0;

   /* Make sure to set *muscle_force in this routine. */

   return numStates;
}


int muscle_deriv_func9(double time, dpMuscleStruct* ms, double state[],
		       double dstate[], double* muscle_force)
{
   int numStates = 0;

   /* Make sure to set *muscle_force in this routine. */

   return numStates;
}


int muscle_deriv_func10(double time, dpMuscleStruct* ms, double state[],
			double dstate[], double* muscle_force)
{
   int numStates = 0;

   /* Make sure to set *muscle_force in this routine. */

   return numStates;
}
