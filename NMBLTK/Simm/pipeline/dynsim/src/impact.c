/*******************************************************************************

	IMPACT.C

   Author: Krystyne Blaikie

   Copyright (c) 2000-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

	Description: This file contains functions to compute impulses, apply forces
      and calculate post-impact state given a list of contact points.

   Routines:
      handle_impacts:        calculate and apply impulses
      apply_impulses:        determines velocities after impact
      show_impact_info:      prints impact information to the console
      show_post_impact_info: prints impact information to the console

*******************************************************************************/

#if CONTACT_DETECTION

#include "universal.h"

/*************** DEFINES (for this file only) *********************************/
#define DISPLAY_IMPACT NO

/***************************** GLOBAL VARIABLES *******************************/
int impact_calc;


/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;			/* defined in sdfor.c */
extern SystemInfo si;

/************************ STATIC FUNCTION PROTOTYPES **************************/
static void apply_impulses(double param[]);
static void show_impact_info(char *string);
static void show_post_impact_info(double sys_energy1);


/* Handle impacts.  Determine impulse forces and post-impact state */

/* The param[] array */
static int CURRENT_TIME = 0;				/* time */	
static int QS = 1;							/* index of q's in param array */
static int US;									/* position of the original u's */
static int NEW_US;							/* position of the new u's */
static int PARAMLEN;							/* length of the array */

void handle_impacts(double t, double y[], double dy[])
{
   int i, compute_impact = NO;
   double *param, rel_vel[3], norm_vel;
   double sys_energy;

   sdderiv(dy, &dy[sdm->nq]);

   if (DISPLAY_IMPACT)
   {
      show_impact_info("PRE_IMPACT");
      calc_system_energy(&si);
      sys_energy = si.system_energy;
      sim_message(none, "Find impulse due to contacts\n");
      fflush(stdout);
   }

   /* initialize indices into param array */
   US = QS + sdm->nq;
   NEW_US = US + sdm->nu;
   PARAMLEN = QS + sdm->neq + sdm->nu;

   /* allocate space for parameter array */
   param = (double *)simm_malloc(PARAMLEN * sizeof(double));
	
   /* initialize the parameter array */
   param[CURRENT_TIME] = t;
   for (i = 0; i < sdm->neq; i++)
      param[QS+i] = y[i];

	/* store the change in velocity in ACC record in contact list (instead
    * of acceleration) to solve the LCP).
	 * delta_v = v' - v; v' = -1 * coef_rest * v
    * if the contact is not an impact,  the change in velocity equals the
    * current velocity so the post-impact velocity is set to zero
    */
   get_contact_info();
   get_bilat_contact_info();
   for (i = 0; i < sdm->num_contacts; i++)
   {
      norm_vel = get_norm_rel_vel(i, rel_vel);
      if (sdm->contacts[i].contact_type == dpImpact)
         sdm->contacts[i].acc = (1 + sdm->contacts[i].coef_rest) * norm_vel;
      else
         sdm->contacts[i].acc = norm_vel; 
   }

   /* determine impulsive forces by solving LCP, and store them in the
    * CONT_FRC field in the contact list
    */
   compute_impact = YES;
   compute_contact_forces(compute_impact);
   compute_impact = NO;

   /* apply the impulses and update the state */
   apply_impulses(param);
   for (i = 0; i < sdm->nu; i++)
      y[sdm->nq + i] = param[NEW_US + i];
   sdstate(t, y, &param[NEW_US]);

   /* store the impulse in the body record for display */
   for (i = 0; i < sdm->num_contacts; i++)
   {
      if (VECTOR_MAGNITUDE(sdm->contacts[i].cont_frc) != 0.0)
      {
         sdtrans(GROUND, sdm->contacts[i].cont_frc, sdm->contacts[i].body1, 
            sdm->body_segment[sdm->contacts[i].body1 + 1].impact_force);
         sdvmul(-1.0, sdm->body_segment[sdm->contacts[i].body1 + 1].impact_force,
            sdm->body_segment[sdm->contacts[i].body1 + 1].impact_force);

         sdtrans(GROUND, sdm->contacts[i].cont_frc, sdm->contacts[i].body2, 
            sdm->body_segment[sdm->contacts[i].body2 + 1].impact_force);

         sdvadd(sdm->body_segment[sdm->contacts[i].body1 + 1].mass_center, 
            sdm->contacts[i].pt1, 
            sdm->body_segment[sdm->contacts[i].body1 + 1].impact_point);
         sdvadd(sdm->body_segment[sdm->contacts[i].body2 + 1].mass_center, 
            sdm->contacts[i].pt2, 
            sdm->body_segment[sdm->contacts[i].body2 + 1].impact_point);
      }
   }

   if (DISPLAY_IMPACT)
      show_post_impact_info(sys_energy);

   check_for_sderror("HANDLE IMPACTS");
   free(param);

}


/* calculate the post-impact state by applying impulses */
static void apply_impulses(double param[])
{
   int i;
   double *q_dot, *u_dot1, *u_dot2;
   double q_ind_value, u_ind_value;
   int q_ind;

   q_dot = (double *)simm_malloc(sdm->nq * sizeof(double));
   u_dot1 = (double *)simm_malloc(sdm->nq * sizeof(double));
   u_dot2 = (double *)simm_malloc(sdm->nq * sizeof(double));

   impact_calc = NO;		

   /* determine accelerations before the impulses are applied */
   sdstate(param[CURRENT_TIME], &param[QS], &param[US]);
   sdumotion(param[CURRENT_TIME], &param[QS], &param[US]);
   sduforce(param[CURRENT_TIME], &param[QS], &param[US]);
   sdderiv(q_dot, u_dot1);
  
   impact_calc = YES;
   /* determine accelerations after the impulses are applied */
   sdstate(param[CURRENT_TIME], &param[QS], &param[US]);
   sdumotion(param[CURRENT_TIME], &param[QS], &param[US]);
   sduforce(param[CURRENT_TIME], &param[QS], &param[US]);
   apply_forces_at_contacts(sdm->num_contacts, sdm->contacts);
   apply_forces_at_contacts(sdm->num_bilat_contacts, sdm->bilat_contacts);
   sdderiv(q_dot, u_dot2);

   impact_calc = NO;

   /* find the new u's after the impulses are applied 
	 * v' = v + a * t, t = 1.0
    */
   for (i = 0; i < sdm->nu; i++)
      param[NEW_US + i] = param[US + i] + (u_dot2[i] - u_dot1[i]);
   for (i = 0; i < sdm->nu; i++)
   {
      if (sdm->q[i].type == dpConstrainedQ)
      {   
         q_ind = sdm->q[i].q_ind;
         q_ind_value = param[QS + q_ind] * sdm->q[q_ind].conversion;
         u_ind_value = param[NEW_US + q_ind] * sdm->q[q_ind].conversion;
         param[NEW_US + i] = interpolate_spline(q_ind_value, sdm->q[i].constraint_func, first, u_ind_value,
            0.0) / sdm->q[i].conversion;
      }
   }

   check_for_sderror("APPLY IMPULSES");
   free(q_dot);
   free(u_dot1);
   free(u_dot2);
}


/* display information */
static void show_impact_info(char *string)
{
   int i;
   double pos[3], vel[3], ang_vel[3], com[3] = {0.0, 0.0, 0.0};
   double mag_vel, mag_w, lin_e = 0.0, ang_e = 0.0, kin_e = 0.0, pot_e = 0.0;

   sim_message(none, "\t\t%s", string);
   for (i = 0; i < sdm->num_body_segments; i++)
   {
      if (sdm->body_segment[i].output == dpYes) 
      {
         sim_message(none, "\t\tBody: %s", sdm->body_segment[i].name);
         sdpos(i-1, com, pos);
         sdvel(i-1, com, vel);
         sdangvel(i-1, ang_vel);
         sdvmul(180.0/3.14159, ang_vel, ang_vel);
         show_vector("\t\tCM ", pos);
         show_vector("\t\tvel", vel);
         show_vector("\t\tw  ", ang_vel);

         mag_vel = VECTOR_MAGNITUDE(vel);
         mag_w = VECTOR_MAGNITUDE(ang_vel);
         sim_message(none, "\t\tv = %f, w = %f", mag_vel, mag_w);
         mag_w = DEG2RAD(mag_w);

         lin_e = 0.5 * 10 * (mag_vel * mag_vel);
         ang_e = 0.5 * 0.001 * (mag_w * mag_w);
         kin_e += lin_e + ang_e;
         pot_e += pos[1] * 10 * 9.80665;
      }
   }
   sim_message(none, "kinetic energy = %f", kin_e);
   sim_message(none, "potential energy = %f", pot_e);
   check_for_sderror("DISPLAY INFO");
}


static void show_post_impact_info(double sys_energy1)
{
   int i;
   double frc[3];

   for (i = 0; i < sdm->num_contacts; i++)
   {
      sdtrans(GROUND, sdm->contacts[i].cont_frc, sdm->contacts[i].body2, frc);
      show_vector("\t\tIMPULSE", frc);
   }

   for (i = 0; i < sdm->num_bilat_contacts; i++)
   {
      sdtrans(GROUND, sdm->bilat_contacts[i].cont_frc, sdm->bilat_contacts[i].body1, frc);
      show_vector("\t\tBILAT I", frc);
   }

   show_impact_info("POST_IMPACT");
   calc_system_energy(&si);
   sim_message(none, "\nsystem energy before = %.9f", sys_energy1);
   sim_message(none, "system energy after = %.9f", si.system_energy);
   sim_message(none, "change in energy = %.9e", si.system_energy - sys_energy1);
}

#endif
