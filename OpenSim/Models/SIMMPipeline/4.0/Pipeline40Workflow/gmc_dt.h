double calc_tendon_force_dt(dpMuscleStruct* ms, double norm_tendon_length);
double calc_norm_fiber_velocity_dt(dpMuscleStruct* ms, double activation,
			   double active_force, double velocity_dependent_force);
double calc_active_force_dt(dpMuscleStruct* ms, double norm_fiber_length);
double calc_passive_fiber_force_dt(dpMuscleStruct* ms, double norm_fiber_length);
double sim_ss_muscle_tendon_force(dpMuscleStruct* ms,double excitation);

double calc_pennation_dt(double fiber_length, double optimal_fiber_length,
						 double initial_pennation_angle);
