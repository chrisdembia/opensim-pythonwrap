/*******************************************************************************

   INITS.C

   Authors: Peter Loan
            Krystyne Blaikie

   Copyright (c) 1996-2005 MusculoGraphics, a division of Motion Analysis Corp.
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
      muscle_init_func8  : unused
      muscle_init_func9  : unused
      muscle_init_func10 : 1 state (fiber_len), used only for optimize_muscle_activations()

*******************************************************************************/

#include "universal.h"

extern char buffer[];

int muscle_init_func1(dpMuscleStruct *ms, double state[])
{
   int i, numStates = 3;
   int activation = 0, fiber_length = 1, fiber_velocity = 2;
   
   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 1);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 1);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 1);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 1);

   /* Initialize the muscle states to default values. */
   state[activation] = 0.0;
   state[fiber_length] = *(ms->optimal_fiber_length);
   state[fiber_velocity] = 0.0;

   /* Now override these defaults with as many initial values as were specified in the
    * parameters file (as long as it's not more than numStates).
    */
   for (i = 0; i < MIN(ms->numStateParams, numStates); i++)
      state[i] = ms->stateParams[i];

   /* Now store some of the state values in the muscle structure. */
   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];

   return numStates;
}


int muscle_init_func2(dpMuscleStruct *ms, double state[])
{
   int i, numStates = 3;
   int activation = 0, fiber_length = 1, fiber_velocity = 2;

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

   /* Initialize the muscle states to default values. Fiber_length is calculated later. */
   state[activation] = 0.0;
   state[fiber_velocity] = 0.0;

   /* Now override these defaults with as many initial values as were specified in the
    * parameters file (as long as it's not more than numStates).
    */
   for (i = 0; i < MIN(ms->numStateParams, numStates); i++)
      state[i] = ms->stateParams[i];

   /* If the initial value of fiber_length was not specified in the parameters
    * file, calculate it assuming static equilibrium. The function
    * calc_muscle_tendon_force() includes pennation in the muscle model.
    */
   if (ms->numStateParams < 2)
   {
      calc_muscle_tendon_force(ms, state[activation]);
      state[fiber_length] = ms->fiber_length;
   }
   else
   {
      ms->fiber_length = state[fiber_length];
   }

   /* Now store some of the state values in the muscle structure. */
   ms->dynamic_activation = state[activation];

   return numStates;
}


int muscle_init_func3(dpMuscleStruct *ms, double state[])
{
   int i, numStates = 4;
   int activation = 0, fiber_length = 1, fiber_velocity = 2, energy = 3;

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

   /* Initialize the muscle states to default values. Fiber_length is calculated later. */
   state[activation] = 0.0;
   state[fiber_velocity] = 0.0;
   state[energy] = 0.0;

   /* Now override these defaults with as many initial values as were specified in the
    * parameters file (as long as it's not more than numStates).
    */
   for (i = 0; i < MIN(ms->numStateParams, numStates); i++)
      state[i] = ms->stateParams[i];

   /* If the initial value of fiber_length was not specified in the parameters
    * file, calculate it assuming static equilibrium. The function
    * calc_muscle_tendon_force() includes pennation in the muscle model.
    */
   if (ms->numStateParams < 2)
   {
      calc_muscle_tendon_force(ms, state[activation]);
      state[fiber_length] = ms->fiber_length;
   }
   else
   {
      ms->fiber_length = state[fiber_length];
   }

   /* Now store some of the state values in the muscle structure. */
   ms->dynamic_activation = state[activation];
   ms->mechanical_energy = state[energy];

   return numStates;
}


int muscle_init_func4(dpMuscleStruct *ms, double state[])
{
   int i, numStates = 2;
   int activation = 0, fiber_length = 1;

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

   /* Initialize the muscle states to default values. Fiber_length is calculated later. */
   state[activation] = 0.0;

   /* Now override these defaults with as many initial values as were specified in the
    * parameters file (as long as it's not more than numStates).
    */
   for (i = 0; i < MIN(ms->numStateParams, numStates); i++)
      state[i] = ms->stateParams[i];

   /* If the initial value of fiber_length was not specified in the parameters
    * file, calculate it assuming static equilibrium. The function
    * calc_muscle_tendon_force() includes pennation in the muscle model.
    */
   if (ms->numStateParams < 2)
   {
      calc_muscle_tendon_force(ms, state[activation]);
      state[fiber_length] = ms->fiber_length;
   }
   else
   {
      ms->fiber_length = state[fiber_length];
   }

   /* Now store some of the state values in the muscle structure. */
   ms->dynamic_activation = state[activation];

   return numStates;
}


int muscle_init_func5(dpMuscleStruct *ms, double state[])
{
   int i, numStates = 1;
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

   /* Initialize the muscle states to default values. */
   state[activation] = 0.0;

   /* Now override these defaults with as many initial values as were specified in the
    * parameters file (as long as it's not more than numStates).
    */
   for (i = 0; i < MIN(ms->numStateParams, numStates); i++)
      state[i] = ms->stateParams[i];

   /* Now store some of the state values in the muscle structure. */
   ms->dynamic_activation = state[activation];

   return numStates;
}


int muscle_init_func6(dpMuscleStruct *ms, double state[])
{
   int i, numStates = 4;
   int activation = 0, fiber_length = 1, heat_energy = 2, mechanical_energy = 3;

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

   /* Initialize the muscle states to default values. Fiber_length is calculated later. */
   state[activation] = 0.0;
   state[heat_energy] = 0.0;
   state[mechanical_energy] = 0.0;

   /* Now override these defaults with as many initial values as were specified in the
    * parameters file (as long as it's not more than numStates).
    */
   for (i = 0; i < MIN(ms->numStateParams, numStates); i++)
      state[i] = ms->stateParams[i];

   /* If the initial value of fiber_length was not specified in the parameters
    * file, calculate it assuming static equilibrium. The function
    * calc_muscle_tendon_force() includes pennation in the muscle model.
    */
   if (ms->numStateParams < 2)
   {
      calc_muscle_tendon_force(ms, state[activation]);
      state[fiber_length] = ms->fiber_length;
   }
   else
   {
      ms->fiber_length = state[fiber_length];
   }

   /* Now store some of the state values in the muscle structure. */
   ms->dynamic_activation = state[activation];
   ms->heat_energy = state[heat_energy];
   ms->mechanical_energy = state[mechanical_energy];

   return numStates;
}


int muscle_init_func7(dpMuscleStruct *ms, double state[])
{
   int numStates = 0;

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 7);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 7);

   if (EQUAL_WITHIN_ERROR(*(ms->resting_tendon_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): resting_tendon_length = 0.0.", ms->name, 7);

   return numStates;
}


int muscle_init_func8(dpMuscleStruct *ms, double state[])
{
   int numStates = 0;

   sim_message(exit_program, "Muscle %s: muscle model %d is undefined.", ms->name, 8);

   return numStates;
}


int muscle_init_func9(dpMuscleStruct *ms, double state[])
{
   int numStates = 0;

   sim_message(exit_program, "Muscle %s: muscle model %d is undefined.", ms->name, 9);

   return numStates;
}


int muscle_init_func10(dpMuscleStruct *ms, double state[])
{
   int i, numStates = 1;
   int fiber_length = 0;

   if (ms->optimal_fiber_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length undefined.", ms->name, 10);

   if (ms->resting_tendon_length == NULL)
      sim_message(exit_program, "Muscle %s (model %d): tendon_slack_length undefined.", ms->name, 10);

   if (ms->max_isometric_force == NULL)
      sim_message(exit_program, "Muscle %s (model %d): max_force undefined.", ms->name, 10);

   if (ms->pennation_angle == NULL)
      sim_message(exit_program, "Muscle %s (model %d): pennation_angle undefined.", ms->name, 10);

   if (EQUAL_WITHIN_ERROR(*(ms->optimal_fiber_length),0.0))
      sim_message(exit_program, "Muscle %s (model %d): optimal_fiber_length = 0.0.", ms->name, 10);

   /* Activation is not a state in this model, but it is needed to calculate fiber length
    * and fiber velocity, so its initial value can be specified in the parameters file.
    * Fiber_length is calculated later.
    */
   ms->dynamic_activation = 0.0;

   /* Now override the defaults with as many initial values as were specified in the
    * parameters file (as long as it's not more than numStates + 1). If activation is
    * specified, it comes *before* the states (to make the format consistent with the
    * other muscle models.
    */
   if (ms->numStateParams >= 1)
   {
      ms->dynamic_activation = ms->stateParams[0];
   }

   if (ms->numStateParams > 1)
   {
      for (i = 0; i < MIN(ms->numStateParams - 1, numStates); i++)
         state[i] = ms->stateParams[i + 1];

      /* Now store fiber length in the muscle structure. */
      ms->fiber_length = state[fiber_length];
   }
   else
   {
      /* If the initial value of fiber_length was not specified in the parameters
       * file, calculate it assuming static equilibrium. The function
       * calc_muscle_tendon_force() includes pennation in the muscle model.
       */
      calc_muscle_tendon_force(ms, ms->dynamic_activation);
      state[fiber_length] = ms->fiber_length;
   }

   return numStates;
}
