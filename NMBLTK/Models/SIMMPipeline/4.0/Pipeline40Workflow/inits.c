/*******************************************************************************

   INITS.C

   Authors: Peter Loan
            Krystyne Blaikie

   Copyright (c) 1996-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains 10 routines to initialize the states
      for dimensionless muscle-tendon models. The routines are named
      muscle_init_func1() through muscle_init_func10(), and each one
      initializes all of a muscle's states for a particular muscle-tendon
      model. The routine should be called at the beginning of your
      program, before entering the integration loop.

   Routines:
      muscle_init_func1  : 3 states (act, fiber_len, fiber_vel), no pennation
      muscle_init_func2  : 3-state model, pennation included
      muscle_init_func3  : like func2 plus 4th state for muscle power
      muscle_init_func4  : 2 states (act, fiber_len), non-zero passive force
      muscle_init_func5  : 1 state (act), infinitely stiff tendon
      muscle_init_func6  : 4 states
      muscle_init_func7  : 0 state, ligament model
      muscle_init_func8  : 2 states (act, fiber_len), parameterized constituitive equations
      muscle_init_func9  : same as func8, except that m-t length and velocity must be set prior
      muscle_init_func10 : unused

*******************************************************************************/

#include "universal.h"

extern char buffer[];

static int (*muscle_deriv_func[])() =
{
muscle_deriv_func1, muscle_deriv_func2, muscle_deriv_func3, muscle_deriv_func4,
muscle_deriv_func5, muscle_deriv_func6, muscle_deriv_func7, muscle_deriv_func8,
muscle_deriv_func9, muscle_deriv_func10
};

int muscle_init_func1(dpMuscleStruct *ms, double state[])
{
   int activation = 0, fiber_length = 1, fiber_velocity = 2;
   
   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 1);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 1);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 1);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 1);

   state[activation] = ms->dynamic_activation = 0.0;
   state[fiber_length] = ms->fiber_length = *(ms->optimal_fiber_length);
   state[fiber_velocity] = 0.0;

   return 3;       /* number of states for this muscle model */
}


int muscle_init_func2(dpMuscleStruct *ms, double state[])
{
   int activation = 0, fiber_length = 1, fiber_velocity = 2;

   /* Find static equilibrium for muscle. Use activation = 0.0 to
    * get initial fiber and tendon lengths for the muscle-tendon
    * actuator at the start of the simulation. This routine
    * includes pennation angle in the muscle model.
    */
   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 2);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 2);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 2);

   if (ms->pennation_angle == NULL)
      sim_message(exit_program, "Muscle %s (model %d): pennation_angle undefined", ms->name, 2);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 2);

   state[activation] = ms->dynamic_activation = 0.0;
   state[fiber_velocity] = 0.0;

   calc_muscle_tendon_force(ms, ms->dynamic_activation);

   state[fiber_length] = ms->fiber_length;

   return 3;       /* number of states for this muscle model */
}


int muscle_init_func3(dpMuscleStruct *ms, double state[])
{
   int activation = 0, fiber_length = 1, fiber_velocity = 2, energy = 3;

   /* Find static equilibrium for muscle. Use activation = 0.0 to
    * get initial fiber and tendon lengths for the muscle-tendon
    * actuator at the start of the simulation. This routine
    * includes pennation angle in the muscle model.
    */

   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 3);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 3);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 3);

   if (ms->pennation_angle == NULL)
      sim_message(exit_program, "Muscle %s (model %d): pennation_angle undefined.", ms->name, 3);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 3);

   state[activation] = ms->dynamic_activation = 0.0;
   state[fiber_velocity] = 0.0;
   state[energy] = 0.0;

   calc_muscle_tendon_force(ms, ms->dynamic_activation);

   state[fiber_length] = ms->fiber_length;

   return 4;       /* number of states for this muscle model */
}


int muscle_init_func4(dpMuscleStruct *ms, double state[])
{
   int activation = 0, fiber_length = 1;

   /* Find static equilibrium for muscle. Use activation = 0.0 to
    * get initial fiber and tendon lengths for the muscle-tendon
    * actuator at the start of the simulation. This routine
    * includes pennation angle in the muscle model.
    */

   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 4);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 4);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 4);

   if (ms->pennation_angle == NULL)
      sim_message(exit_program, "Muscle %s (model %d): pennation_angle undefined.", ms->name, 4);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 4);

   state[activation] = ms->dynamic_activation = 0.0;

   calc_muscle_tendon_force(ms, ms->dynamic_activation);

   state[fiber_length] = ms->fiber_length;

   return 2;       /* number of states for this muscle model */
}


int muscle_init_func5(dpMuscleStruct *ms, double state[])
{
   int activation = 0;

   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 5);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 5);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 5);

   if (ms->pennation_angle == NULL)
      sim_message(exit_program, "Muscle %s (model %d): pennation_angle undefined.", ms->name, 5);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 5);

   state[activation] = 0.0;

   return 1;       /* number of states for this muscle model */
}


int muscle_init_func6(dpMuscleStruct *ms, double state[])
{
   int activation = 0, fiber_length = 1, heat_energy = 2, mechanical_energy = 3;

   /* Find static equilibrium for muscle. Use activation = 0.0 to
    * get initial fiber and tendon lengths for the muscle-tendon
    * actuator at the start of the simulation. This routine
    * includes pennation angle in the muscle model.
    */

   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 6);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 6);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 6);

   if (ms->pennation_angle == NULL)
      sim_message(exit_program, "Muscle %s (model %d): pennation_angle undefined.", ms->name, 6);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 6);

   state[activation] = ms->dynamic_activation = 0.0;
   state[heat_energy] = ms->heat_energy = 0.0;
   state[mechanical_energy] = ms->mechanical_energy = 0.0;

   calc_muscle_tendon_force(ms, ms->dynamic_activation);

   state[fiber_length] = ms->fiber_length;

   return 4;       /* number of states for this muscle model */
}


int muscle_init_func7(dpMuscleStruct *ms, double state[])
{
   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 7);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 7);

   if (EQUAL_WITHIN_ERROR(*(ms->resting_tendon_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): resting_tendon_length = 0.0.", ms->name, 7);

   return 0;       /* number of states for this muscle model */
}


int muscle_init_func8(dpMuscleStruct *ms, double state[])
{
   int activation = 0, fiber_length = 1;
   int muscle_model_index, ns;
   int (*deriv_func)();
   double muscle_force, dstate[2];

   /* Use the activation level and muscle length assuming they have been pre-defined 
      in the muscle structure
    */

   state[activation] = ms->dynamic_activation;

   state[fiber_length] = ms->fiber_length;

//   muscle_model_index = *(ms->muscle_model_index);

//   deriv_func = muscle_deriv_func[muscle_model_index];

//   ns =  deriv_func(0., ms, state, dstate, &muscle_force);

   return 2;       /* number of states for this muscle model */
}


int muscle_init_func9(dpMuscleStruct *ms, double state[])
{
   int activation = 0, fiber_length = 1;
   int muscle_model_index, ns;
   int (*deriv_func)();
   double muscle_force, dstate[2];

   /* Use the activation level and muscle length assuming they have been pre-defined 
      in the muscle structure
    */

   state[activation] = ms->dynamic_activation;

   state[fiber_length] = ms->fiber_length;

//   muscle_model_index = *(ms->muscle_model_index);

//   deriv_func = muscle_deriv_func[muscle_model_index];

//   ns =  deriv_func(0., ms, state, dstate, &muscle_force);

   return 2;       /* number of states for this muscle model */
}


int muscle_init_func10(dpMuscleStruct *ms, double state[])
{
   sim_message(exit_program, "Muscle %s: muscle model %d is undefined.", ms->name, 10);

   return 0;       /* number of states for this muscle model */
}
