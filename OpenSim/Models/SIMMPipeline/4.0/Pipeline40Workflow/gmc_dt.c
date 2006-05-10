/*******************************************************************************

   GMC_DT.C

   Author: Darryl Thelen
   
   Description: This file contains additional utility routines to supplement GMC.C
      for calculating various muscle properties such as length, force, and velocity. 

*******************************************************************************/

#include "universal.h"


/*************** DEFINES (for this file only) *********************************/
#define MAX_ITERATIONS 100
#define ERROR_LIMIT 0.0001
#define PI 3.14159265358979

/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
dpMuscleStruct* MS;

int sim_ss_musderiv(double time,double ym[],double dym[],double param[],int* status);

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

/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/



/* CALC_TENDON_FORCE_DT: this routine calculates the force in tendon by finding
 * tendon strain and using it in an exponential function (JBME 2003 - Thelen)
 * FmaxTendonStrain - Function is parameterized by the tendon strain due to maximum isometric muscle force
 *     This should be specified as a dynamic parameter in the muscle file
 */

double calc_tendon_force_dt(dpMuscleStruct* ms, double norm_tendon_length)
{

   double tendon_strain, norm_resting_length, tendon_force, KToe=3, klin, ToeStrain, ToeForce, FmaxTendonStrain;

   norm_resting_length = (*(ms->resting_tendon_length)) /
      (*(ms->optimal_fiber_length));

   tendon_strain =  (norm_tendon_length - norm_resting_length) /
      norm_resting_length;

	FmaxTendonStrain = get_muscle_param_value(ms,"FmaxTendonStrain");
	ToeStrain = 0.609*FmaxTendonStrain;
	ToeForce = 0.333333;
	klin = 1.712/FmaxTendonStrain;

	if (tendon_strain>ToeStrain)
		tendon_force = klin*(tendon_strain-ToeStrain)+ToeForce;
	else if (tendon_strain>0) 
		tendon_force = ToeForce*(exp(KToe*tendon_strain/ToeStrain)-1.0)/(exp(KToe)-1);
	else
		tendon_force=0.;

	// Add on a small stiffness so that tendon never truly goes slack for non-zero tendon lengths
	tendon_force+=0.001*(1.+tendon_strain);

   return (tendon_force);

}


/* CALC_NORM_FIBER_VELOCITY_DT: written by Darryl Thelen
 * this routine calculates the normalized fiber velocity (scaled to Vmax) by inverting the
 * muscle force-velocity-activation relationship (Thelen, JBME 2003)
 * This equation is parameterized using the following dynamic parameters
 * which must be specified in the muscle file
 * Dynamic Parameters:
 *   damping - normalized passive damping in parallel with contractile element
 *   Af - velocity shape factor from Hill's equation
 *   Flen	- Maximum normalized force when muscle is lengthening
 */
double calc_norm_fiber_velocity_dt(dpMuscleStruct* ms, double activation,
			   double active_force, double velocity_dependent_force)
{
   double norm_fiber_velocity, bp;
   double Af, Flen, b, Fa, Fv;
   double fv0, F0, F1, fv1;
   double epsilon=1.e-6;

   bp = get_muscle_param_value(ms,"damping");
   Af = get_muscle_param_value(ms,"Af");
   Flen = get_muscle_param_value(ms,"Flen");

   // Don't allow zero activation
   if (activation<epsilon)
		activation=epsilon;

    Fa = activation*active_force;
    Fv = velocity_dependent_force;
    
    if (Fv<Fa) {		// Muscle shortening
		if (Fv<0) {	// Extend the force-velocity curve for negative forces using linear extrapolation
			F0=0;
			b=Fa+F0/Af;
        	fv0 = (F0-Fa)/(b+bp);
			F1=epsilon;
			b=Fa+F1/Af;
        	fv1 = (F1-Fa)/(b+bp);
			b = (F1-F0)/(fv1-fv0);
        	norm_fiber_velocity = fv0 + (Fv-F0)/b;
		}
		else {
			b=Fa+Fv/Af;
			norm_fiber_velocity = (Fv-Fa)/(b+bp);
		}
    }
    else if (Fv<(.95*Fa*Flen)) {
        	b=(2+2./Af)*(Fa*Flen-Fv)/(Flen-1.);
        	norm_fiber_velocity = (Fv-Fa)/(b+bp);
    }
	else {  // Extend the force-velocity curve for forces that exceed maximum using linear extrapolation
			F0=.95*Fa*Flen;
			b=(2+2./Af)*(Fa*Flen-F0)/(Flen-1.);
        	fv0 = (F0-Fa)/(b+bp);
			F1=(.95+epsilon)*Fa*Flen;
			b=(2+2./Af)*(Fa*Flen-F1)/(Flen-1.);
        	fv1 = (F1-Fa)/(b+bp);
			b = (fv1-fv0)/(F1-F0);
        	norm_fiber_velocity = fv0 + b*(Fv-F0);
    }

    return (norm_fiber_velocity);
}




/* CALC_ACTIVE_FORCE_DT: this routine calculates the active component of force
 * in the muscle fibers. It uses the current fiber length to interpolate the
 * active force-length curve - described by Gaussian curve as in Thelen, JBME 2003
 */

double calc_active_force_dt(dpMuscleStruct* ms, double norm_fiber_length) {
	double gamma, x, fl;
	gamma = get_muscle_param_value(ms,"KshapeActive");
	x=-(norm_fiber_length-1.)*(norm_fiber_length-1.)/gamma;
	fl=exp(x);
	return (fl);
}




/* CALC_PASSIVE_FIBER_FORCE_DT: written by Darryl Thelen
 * this routine calculates the passive force in the muscle fibers using
 * an exponential-linear function instead of cubic splines.
 * It always returns a non-zero force for all muscle lengths
 * This equation is parameterized using the following dynamic parameters
 * which must be specified in the muscle file
 * Dynamic Parameters:
 *   FmaxMuscleStrain - passive muscle strain due to the application of 
 *                      maximum isometric muscle force
 *	 KshapePassive - exponential shape factor
 *
 *  The normalized force due to passive stretch is given by
 *  For L < (1+maxStrain)*Lo
 *		f/f0 = exp(ks*(L-1)/maxStrain) / exp(ks)
 */

double calc_passive_fiber_force_dt(dpMuscleStruct* ms, double norm_fiber_length)
{
	double passive_force=0., strain0, slope, kshape;
   
	strain0 = get_muscle_param_value(ms,"FmaxMuscleStrain");
	kshape = get_muscle_param_value(ms,"KshapePassive");

	if (norm_fiber_length>(1+strain0)) { // Switch to a linear model at large forces
		slope=(kshape/strain0)*(exp(kshape*(1.0+strain0-1.0)/strain0)) / (exp(kshape));
		passive_force=1.0+slope*(norm_fiber_length-(1.0+strain0));
	}
	else
		passive_force = (exp(kshape*(norm_fiber_length-1.0)/strain0)) / (exp(kshape));

	return (passive_force);
}

 



//*******************************************************************************************
// SIM_SS_MUSDERIV: this routine calculates the current time derivatives of the muscle states
//*******************************************************************************************
double sim_ss_muscle_tendon_force(dpMuscleStruct* ms,double excitation) {
	int i, ny, err, which, (*init_func)(), muscle_model_index;
	double time=0., dT=0.01, integ_step, y[20], dy[20], Fp;
	double eps=0.001, tol=0.00001, ctol=0.00001, param[1], *work;
	work = (double*)simm_malloc(20*5*sizeof(double));
	// Now for each muscle at each excitation level integrate the differential equations 
	// to get the activation and fiber length at t+dT
	integ_step=0.000001;
	muscle_model_index = *(ms->muscle_model_index);
	init_func = muscle_init_func[muscle_model_index];
	ny = init_func(ms,y);
//	calc_muscle_tendon_length(ms);
	MS=ms;
	ms->excitation_level=excitation;
	sim_ss_musderiv(time,y,dy,&param[0],&err);

	sdvinteg(sim_ss_musderiv,&time,y,dy,&param[0],dT,&integ_step,ny,tol,work,&err,&which);
	Fp=ms->force;

	for (i=0;i<100;i++) {
		sdvinteg(sim_ss_musderiv,&time,y,dy,&param[0],dT,&integ_step,ny,tol,work,&err,&which);
		if (fabs(ms->force-Fp)<eps)
			break;
		else
			Fp=ms->force;
	}

	free(work);
	Fp=ms->force;
	return Fp;
}

//*******************************************************************************************
// SIM_SS_MUSDERIV: this routine calculates the current time derivatives of the muscle states
//*******************************************************************************************
int sim_ss_musderiv(double time,double ym[],double dym[],double param[],int* status)
{
	int ns, muscle_model_index, (*deriv_func)();
	double muscle_force;
	// Assume muscle-tendon length has been calculated
	muscle_model_index = *(MS->muscle_model_index);
	deriv_func = muscle_deriv_func[muscle_model_index];
	ns = deriv_func(time,MS,ym,dym,&muscle_force);
	*status=0;
	return 1;
}



