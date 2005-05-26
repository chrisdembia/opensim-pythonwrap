/*******************************************************************************

   ASSIGNS.C

   Author: Peter Loan

   Copyright (c) 1996-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description:  This file contains 10 routines to store muscle state values
      after the state variables have been integrated for a given time step.
      For example, in a muscle model where activation is a state, you would
      want to store the activation-state-variable value in the muscle structure
      after each time step so that you can print it out or write it to a file
      without having to figure out which element in the state vector it is
      every time you want to do something with it. The routines are named
      muscle_assign_func1() through muscle_assign_func10(), and each one
      stores all of a muscle's states wherever the user wants.


   Routines:
      muscle_assign_func1  : 3 states (act, fiber_len, fiber_vel), no pennation
      muscle_assign_func2  : 3-state model, pennation included
      muscle_assign_func3  : like func2 plus 4th state for muscle power
      muscle_assign_func4  : 2 states (act, fiber_len), non-zero passive force
      muscle_assign_func5  : 1 state (act), infinitely stiff tendon
      muscle_assign_func6  : 4 state
      muscle_assign_func7  : 0 state, ligament model
      muscle_assign_func8  : 2 states (act, fiber_len), parameterized constituitive equations
      muscle_assign_func9  : same as 8, except that m-t length and velocity must be set prior
      muscle_assign_func10 : unused

*******************************************************************************/

#include "universal.h"


int muscle_assign_func1(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0, fiber_length = 1, fiber_velocity = 2;

   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];
   ms->fiber_velocity = state[fiber_velocity];

   return (3);       /* number of states for this muscle model */

}


int muscle_assign_func2(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0, fiber_length = 1, fiber_velocity = 2;

   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];
   ms->fiber_velocity = state[fiber_velocity];

   return (3);       /* number of states for this muscle model */

}


int muscle_assign_func3(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0, fiber_length = 1, fiber_velocity = 2, energy = 3;

   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];
   ms->fiber_velocity = state[fiber_velocity];
   ms->mechanical_energy = state[energy];

   return (4);       /* number of states for this muscle model */

}


int muscle_assign_func4(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0, fiber_length = 1;

   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];

   return (2);       /* number of states for this muscle model */

}


int muscle_assign_func5(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0;

   ms->dynamic_activation = state[activation];

   return (1);       /* number of states for this muscle model */

}


int muscle_assign_func6(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0, fiber_length = 1, heat_energy = 2,mechanical_energy = 3;

   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];
   ms->heat_energy = state[heat_energy];
   ms->mechanical_energy = state[mechanical_energy];

   return (4);       /* number of states for this muscle model */

}


int muscle_assign_func7(double time, dpMuscleStruct *ms, double state[])
{

	ms->dynamic_activation = 0.0;
	ms->fiber_length = 0.0;

	return (0);		/* number of states for this muscle model */
}


int muscle_assign_func8(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0, fiber_length = 1;

   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];

   return (2);       /* number of states for this muscle model */

}


int muscle_assign_func9(double time, dpMuscleStruct *ms, double state[])
{

   int activation = 0, fiber_length = 1;

   ms->dynamic_activation = state[activation];
   ms->fiber_length = state[fiber_length];

   return (2);       /* number of states for this muscle model */

}


int muscle_assign_func10(double time, dpMuscleStruct *ms, double state[])
{

   return (0);       /* number of states for this muscle model */

}
