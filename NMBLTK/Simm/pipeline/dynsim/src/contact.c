/*******************************************************************************

	CONTACT.C
	
   Author: Krystyne Blaikie

   Copyright (c) 2000-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains the main functions for detecting
      rigid-body contact.
	
	Partial list of routines:
      determine_contacts:          create list of contact points and bilat. contacts
      contact_callback:            enter contact information
      apply_forces_at_contacts:    apply forces stored in list at contact points
      get_contact_info:            fill kinematic information into contact list
      get_rel_vel:                 determine the relative velocity at a contact point
      get_norm_rel_vel:            determine the normal rel. vel. at contact point
      get_tang_rel_vel:            determine the tangential rel. vel. at a contact pt
      print_contact_list:          print information in contact list to screen
      copy_cnode:                  copy a node into a new node
	
*******************************************************************************/

#if CONTACT_DETECTION
#include "universal.h"
#include "pipesolid.h"

/*************** DEFINES (for this file only) *********************************/
#define IMPACT_THRESHOLD_VEL -1e-6
#define SEP_VEL_THRESHOLD 1e-6
#define COINCIDENT_TOL	1e-3

/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;								/* defined in sdfor.c */
extern dpSimulationParameters params;           /* defined in main.c */
extern ObjectInfo object_info;						/* defined in object.c */
extern char buffer[];				               /* defined in readtools.c */


/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
int** pathptrs;
int print_contacts = NO;

/***************** GLOBAL FUNCTION PROTOTYPES *********************************/
void contact_callback(dpPolyhedronStruct *ph1, dpPolyhedronStruct *ph2, 	
                      ContactPair *cp, int num_contacts, ContactReport* contact);

/***************** STATIC FUNCTION PROTOTYPES *********************************/
static void make_pin_contacts(double y[], int jnt, int axis);
static void make_slider_contacts(double y[], int jnt, int axis);
static void make_cylindrical_contacts(double y[], int jnt, int transl, int rot);
static void make_ujoint_contacts(double y[], int jnt, int axis1, int axis2);
static void make_planar_contacts(double y[], int jnt, int t1, int t2, int rot);
static void make_ball_contacts(int jnt);
static void make_fixed_contacts(int jnt);
static void enter_node_info(int body1, int body2, double outb_pt[3],
	                         double inb_norm[3]);
static void get_joint_axis(double y[], int jnt, int axis, double jnt_axis[]);
static void get_orthogonal_axes(double jnt_axis[], double norm1[], double norm2[]);
static int enterpath(int j, int k, int newend);
static ReturnCode setpath(int list[]);
static void printpaths(void);
static int find_joint_between_simm_segments(int from, int to);
static dpBoolean joint_is_free(int jnt);
static void make_constrained_contacts(int jnt, double y[]);

/* initialize contact info in model struct */
void init_contact_info(void)
{
   sdm->num_contacts = 0;
   sdm->num_bilat_contacts = 0;

   sdm->contacts_size = 100;
   sdm->bilat_contacts_size = 100;

   sdm->contacts = (dpContactInfo*)malloc(sdm->contacts_size * sizeof(dpContactInfo));
   sdm->bilat_contacts = (dpContactInfo*)malloc(sdm->bilat_contacts_size * sizeof(dpContactInfo));
}


/* check that no initial contact points are IMPACTS, since they cannot
 * be handled properly at the beginning of the simulation.
 */
void check_for_initial_penetration(double y[], double dy[])
{

   int i;
   double mag, nv[3];

	sdstate(0.0, y, &y[sdm->nq]);
	determine_contacts(y, dy);
	for (i = 0; i < sdm->num_contacts; i++)
   {
		mag = get_norm_rel_vel(i, nv);
		if (mag < 0)
      {
         store_motion_frame(params.startTime, y);
			sim_message(exit_program, "INITIAL PENETRATION: CANNOT CONTINUE.");
		}
	}

	check_for_sderror("INIT PENETRATION");
}


/* DETERMINE_CONTACTS: call the SOLID routines to find contact points
 * between object pairs.  Create a list of bilateral contact points.
 */
void determine_contacts(double y[], double dy[])
{
   int i;
   double pos[3], mat[3][3], mat2[3][3], quat[4], com[3] = {0.0, 0.0, 0.0};
   ContactObject* obj;

   /* reset the number of contacts before searching */
   sdm->num_contacts = 0;
   sdm->num_bilat_contacts = 0;

   /* calculate accelerations */
   sdderiv(dy, &dy[sdm->nq]);

	/* set the position and orientation of contact objects (other than
    * ground), and transform them
    */
   for (i = 0; i < object_info.num_objects; i++)
   {
      obj = &object_info.object[i];
      if (obj->ph->body_segment != -1)
      {
         sdpos(obj->ph->body_segment, com, pos);
         sdorient(obj->ph->body_segment, mat);
         transpose_3x3matrix(mat, mat2);
         sddc2quat(mat2, &quat[0], &quat[1], &quat[2], &quat[3]);
         transform_solid_object(obj->ph, pos, quat);
      }
   }

	/* call the SOLID routine (which calls CONTACT_CALLBACK to fill in the
    * contact records) to find all contact points.
    */
   if (object_info.num_pairs > 0)
      calc_solid_contacts();

   /* create bilateral contact list */
   create_bilateral_contacts(y);

   check_for_sderror("DETERMINE_CONTACTS");
}


/* CONTACT_CALLBACK stores the information about all the contact points in a 
 * given contact pair.  All the contact information is return by SOLID in the
 * contact Report (CONTACT) and the number of contacts (NUM_CONTACTS).
 * Information about the two objects of the contact pair is stored in PH1 and 
 * PH2.
 * The information about each contact point is stored in the 
 * sdm->CONTACTS array,
 * and the total number of contacts (sdm->NUM_CONTACTS) is increased.
 */
void contact_callback(dpPolyhedronStruct *ph1, dpPolyhedronStruct *ph2, 
	                   ContactPair *cp, int num_contacts, ContactReport* contact)
{
   int i, body1, body2, contact_body;
   double norm1[3], norm2[3], contact_norm[3], outward_norm[3];

   if (sdm->num_contacts + num_contacts > sdm->contacts_size)
   {
      sdm->contacts_size += 100;
      sdm->contacts = (dpContactInfo*)realloc(sdm->contacts, 
         sdm->contacts_size * sizeof(dpContactInfo));
   }

   for (i = 0; i < num_contacts; i++)
   {
      sdm->contacts[sdm->num_contacts].body1 = body1 = ph1->body_segment;
      sdm->contacts[sdm->num_contacts].body2 = body2 = ph2->body_segment;
		
      /* contact points in body frame from body center of mass */
      sdvcopy(contact[i].p1, sdm->contacts[sdm->num_contacts].pt1);
      sdvcopy(contact[i].p2, sdm->contacts[sdm->num_contacts].pt2);

		/* The outward normal should point from body 1 to body 2 and be expressed
		 * in the GROUND frame.  If body 2 is returned as the contact body, the
		 * outward normal should be flipped.
		 */
      switch(contact[i].contact_body)
      {
         case(1):
            contact_body = body1;
            sdvcopy(contact[i].contact_normal, contact_norm);
            sdvcopy(contact_norm, outward_norm);
            break;
         case(2):
            contact_body = body2;
            sdvcopy(contact[i].contact_normal, contact_norm);
            sdvmul(-1.0, contact_norm, outward_norm);
            break;
         default:
            sim_message(exit_program, "Invalid contact body in contact_callback.");
      }

      sdtrans(contact_body, outward_norm, GROUND, outward_norm);
      sdvcopy(outward_norm, sdm->contacts[sdm->num_contacts].outward_norm);

		/* the normal on body1 is opposite to the outward normal
		 * the normal on body2 is in the same direction as outward normal.
       */
      sdvmul(-1.0, outward_norm, norm1);
      sdvcopy(outward_norm, norm2);

      /* store body normals in body frames */
      sdtrans(GROUND, norm1, body1, sdm->contacts[sdm->num_contacts].norm1);
      sdtrans(GROUND, norm2, body2, sdm->contacts[sdm->num_contacts].norm2);

      sdm->contacts[sdm->num_contacts].coef_rest = cp->restitution;
      sdm->contacts[sdm->num_contacts].mu_dynamic = cp->dynamic_friction;
      sdm->contacts[sdm->num_contacts].mu_static = cp->static_friction;
	
		switch(contact[i].type1)
      {
			case(0):
            sprintf(sdm->contacts[sdm->num_contacts].type1, "VERTEX");
			   break;
			case(1):
            sprintf(sdm->contacts[sdm->num_contacts].type1, "EDGE");
            break;
			case(2):
            sprintf(sdm->contacts[sdm->num_contacts].type1, "FACE");
            break;
		};
		switch(contact[i].type2)
      {
			case(0):
            sprintf(sdm->contacts[sdm->num_contacts].type2, "VERTEX");
			   break;
			case(1):
            sprintf(sdm->contacts[sdm->num_contacts].type2, "EDGE");
            break;
			case(2):
            sprintf(sdm->contacts[sdm->num_contacts].type2, "FACE");
            break;
		};

      /* don't handle FACE-FACE contacts */
      if (STRINGS_ARE_EQUAL(sdm->contacts[sdm->num_contacts].type1, "FACE") &&
         STRINGS_ARE_EQUAL(sdm->contacts[sdm->num_contacts].type2, "FACE")) 
      {
         continue;
      }
		make_vector(sdm->contacts[sdm->num_contacts].cont_frc, 0.0, 0.0, 0.0);
		sdm->num_contacts++;
	
		sprintf(buffer, "CONTACT CALLBACK (body1 = %d, body2 = %d, contact_body = %d)", body1, 
         body2, contact_body);
		check_for_sderror(buffer);
	}
}


/* Apply force stored in CONT_FRC (in GROUND FRAME) to contact points */
void apply_forces_at_contacts(int n, dpContactInfo list[])
{
   int i;
   double frc1[3], frc2[3], pt1[3], pt2[3];

   for (i = 0; i < n; i++)
   {
      sdtrans(GROUND, list[i].cont_frc, list[i].body1, frc1);
      sdtrans(GROUND, list[i].cont_frc, list[i].body2, frc2);
      sdvmul(-1.0, frc1, frc1);
      sdvcopy(list[i].pt1, pt1);
      sdvcopy(list[i].pt2, pt2);
      sdpointf(list[i].body1, pt1, frc1);
      sdpointf(list[i].body2, pt2, frc2);
   }
   check_for_sderror("APPLY FORCES AT CONTACTS");
}


/* fill in the kinematic information for each contact point in the list: 
 * velocities, accelerations, relative velocities and accelerations,
 * and impact status.
 */
void get_contact_info(void)
{
   int i, body1, body2;
   double pt1[3], pt2[3], loc1[3], loc2[3], rel_pos[3], dist;
   double norm_rel_vel[3], norm_vel_mag;
   double acc1[3], acc2[3], rel_acc[3];

	for (i = 0; i < sdm->num_contacts; i++)
	{
		body1 = sdm->contacts[i].body1;
		body2 = sdm->contacts[i].body2;

		/* contact point in body frames */
		sdvcopy(sdm->contacts[i].pt1, pt1);
		sdvcopy(sdm->contacts[i].pt2, pt2);

		/* contact points in ground frame */
		sdpos(body1, pt1, loc1);
		sdpos(body2, pt2, loc2);

		/* distance between contact points */
		sdvsub(loc2, loc1, rel_pos);
		dist = DOT_VECTORS(rel_pos, sdm->contacts[i].outward_norm);
		sdm->contacts[i].dist = dist;

   	/* relative velocities of contact points in GROUND frame (wrt ground)*/
		sdvel(body1, pt1, sdm->contacts[i].vel1);
		sdvel(body2, pt2, sdm->contacts[i].vel2);
		get_rel_vel(i, sdm->contacts[i].rel_vel);

		norm_vel_mag = get_norm_rel_vel(i, norm_rel_vel);

		if (norm_vel_mag  < IMPACT_THRESHOLD_VEL)
			sdm->contacts[i].contact_type = dpImpact;
		else if (norm_vel_mag > SEP_VEL_THRESHOLD) 
			sdm->contacts[i].contact_type = dpSeparatingContact;
		else
			sdm->contacts[i].contact_type = dpRestingContact;
		
		/* relative accelerations of the cont pts in ground frame (wrt ground) */
		sdacc(body1, pt1, acc1);
		sdacc(body2, pt2, acc2);
		sdvsub(acc2, acc1, rel_acc);
		sdm->contacts[i].acc = DOT_VECTORS(rel_acc, sdm->contacts[i].outward_norm);
	}
	check_for_sderror("GET_CONTACT_INFO");
}


void get_bilat_contact_info(void)
{
   int i, body1, body2;
   double pt1[3], pt2[3], loc1[3], loc2[3], rel_pos[3], dist;
   double vel1[3], vel2[3];
   double acc1[3], acc2[3], rel_acc[3];

	for (i = 0; i < sdm->num_bilat_contacts; i++)
	{
		body1 = sdm->bilat_contacts[i].body1;
		body2 = sdm->bilat_contacts[i].body2;

		/* contact point in body frames */
		sdvcopy(sdm->bilat_contacts[i].pt1, pt1);
		sdvcopy(sdm->bilat_contacts[i].pt2, pt2);

		/* contact points in ground frame */
		sdpos(body1, pt1, loc1);
		sdpos(body2, pt2, loc2);

		/* distance between contact points */
		sdvsub(loc2, loc1, rel_pos);
		dist = DOT_VECTORS(rel_pos, sdm->bilat_contacts[i].outward_norm);
		sdm->contacts[i].dist = dist;

   	/* relative velocities of contact points in GROUND frame (wrt ground)*/
		sdvel(body1, pt1, vel1);
		sdvel(body2, pt2, vel2);
      sdvcopy(vel1, sdm->bilat_contacts[i].vel1);
      sdvcopy(vel2, sdm->bilat_contacts[i].vel2);
	   sdvsub(sdm->bilat_contacts[i].vel2, sdm->bilat_contacts[i].vel1, sdm->bilat_contacts[i].rel_vel);

		/* relative accelerations of the cont pts in ground frame (wrt ground) */
		sdacc(body1, pt1, acc1);
		sdacc(body2, pt2, acc2);
		sdvsub(acc2, acc1, rel_acc);
		sdm->bilat_contacts[i].acc = DOT_VECTORS(rel_acc, sdm->bilat_contacts[i].outward_norm);

      sdm->bilat_contacts[i].contact_type = dpRestingContact;
   }
	check_for_sderror("GET_BILAT_CONTACT_INFO");
}


/* get the relative velocities of each contact point in the current state */
double get_rel_vel(int cont, double rel_vel[])
{
   double vel1[3], vel2[3], mag;

   /* linear velocity of contact points in GROUND frame (wrt ground)*/
   sdvel(sdm->contacts[cont].body1, sdm->contacts[cont].pt1, vel1);
   sdvel(sdm->contacts[cont].body2, sdm->contacts[cont].pt2, vel2);
   sdvsub(vel2, vel1, rel_vel);
	
   mag = VECTOR_MAGNITUDE(rel_vel);
   check_for_sderror("GET REL VEL");

   return mag;
}


/* get the normal relative velocity of a contact point */
double get_norm_rel_vel(int i, double v_norm[])
{
   double mag, rel_vel[3], norm[3];

   get_rel_vel(i, rel_vel);
   sdvcopy(sdm->contacts[i].outward_norm, norm);
   mag = DOT_VECTORS(rel_vel, norm);
   sdvmul(mag, norm, v_norm);
   check_for_sderror("GET NORM REL VEL");

   return mag;
}


/* get the tangential relative velocity of a contact point */
double get_tang_rel_vel(int i, double v_tang[])
{
   double mag, v_norm[3], rel_vel[3], norm[3];

   get_rel_vel(i, rel_vel);
   sdvcopy(sdm->contacts[i].outward_norm, norm);
   mag = DOT_VECTORS(rel_vel, norm);
   sdvmul(mag, norm, v_norm);
   sdvsub(rel_vel, v_norm, v_tang);
   mag = VECTOR_MAGNITUDE(v_tang);
   check_for_sderror("GET TANG REL VEL");

   return mag;
}


/* create bilateral contacts for all prescribed joints that are also used
 * in contact detection. Remove any duplicate points. Specify points in
 * outboard body frame.
 */
void create_bilateral_contacts(double y[])
{
   int i, j, k, inb, outb, jnt, dof, body, unconstrained_dof;
   int dof_free[6], q, constrained_dof;
   dpJointType type;
   dpBoolean *used = NULL;
   
   used = (dpBoolean *)simm_malloc(sdm->num_joints * sizeof(dpBoolean));
   if (used == NULL)
   {
      sim_message(exit_program, "Unable to malloc necessary memory in create_bilateral_contacts().");
      return;
   }

   for (i = 0; i < sdm->num_joints; i++)
      used[i] = dpNo;
   
   for (body = 0; body < sdm->num_body_segments; body++)
   {
      if (sdm->body_segment[body].contactable == dpNo)
      {
         continue;
      }
      for (jnt = 0; jnt < sdm->num_joints; jnt++)
      {
         if (used[jnt] == dpYes)
            continue;

         if (sdm->body_segment[body].contact_joints[jnt] == dpYes)
         {
            inb = sdm->joint[jnt].inboard_body + 1;
            outb = sdm->joint[jnt].outboard_body + 1;
            if (print_contacts) 
               sim_message(none, "joint %d: %s -> %s: ", jnt, sdm->body_segment[inb].name,
                  sdm->body_segment[outb].name);
            for (i = 0; i < 6; i++)
               dof_free[i] = NO;

            dof = sdm->joint[jnt].dof;
            type = sdm->joint[jnt].jnt_type;

            unconstrained_dof = 0;
            constrained_dof = 0;
            for (i = 0; i < dof; i++)
            {
               q = sdindx(jnt, i);
               if (sdm->q[q].type == dpUnconstrainedQ)
               {
                  dof_free[i] = YES;
                  unconstrained_dof++;
               }
               else if (sdm->q[q].type == dpPrescribedQ) 
               {
                  dof_free[i] = YES;
                  unconstrained_dof++;
               }
               else if (sdm->q[q].type == dpConstrainedQ) 
               {
                  constrained_dof++;
               }
               
            }
            if (constrained_dof != 0)
            {
               if (print_contacts)
                  sim_message(none, "constrained joint ");
               make_constrained_contacts(jnt, y);
               used[jnt] = dpYes;
               continue;

            }
            switch (unconstrained_dof)
            {
               case(0):	
                  if (print_contacts)
                     sim_message(none, "0 dof: ");
                  make_fixed_contacts(jnt);
                  break;
               case(1): 
                  /* find the first FREE degree of freedom.  It's either
                   * a pin or a slider.
                   */
                  if (print_contacts)
                     sim_message(none, "1 dof ");
                  for (i = 0; i < dof; i++)
                  {
                     if (dof_free[i]) break;
                  }
                  switch(type)
                  {
                     case(dpPin):
                        make_pin_contacts(y, jnt, 0);
                        break;
                     case(dpSlider):
                        make_slider_contacts(y, jnt, 0);
                        break;
                     case(dpCylindrical):
                        if (i == 0) make_slider_contacts(y, jnt, 0);
                        else make_pin_contacts(y, jnt, 1);
                        break;
                     case(dpUniversal):
                        make_pin_contacts(y, jnt, i);
                        break;
                     case(dpPlanar):
                        if (i == 2) make_pin_contacts(y, jnt, i);
                        else make_slider_contacts(y, jnt, i);
                        break;
                     case(dpGimbal):
                        make_pin_contacts(y, jnt, i);
                        break;
                     case(dpBall):
                        make_pin_contacts(y, jnt, i);
                        break;
                     case(dpFree):
                        if (i < 3) make_slider_contacts(y, jnt, i);
                        else make_pin_contacts(y, jnt, i);
                        break; 
                     case(dpBushing):
                        if (i < 3) make_slider_contacts(y, jnt, i);
                        else make_pin_contacts(y, jnt, i);
                        break;
                     default:
                        break;
                  }
                  break;
               case(2): 
                  /* either a universal joint or  cylindrical joint */
                  if (print_contacts)
                     sim_message(none, "2 dof ");
                  if (type == dpCylindrical) 
                     make_cylindrical_contacts(y, jnt, 0, 1);
                  else if (type == dpUniversal)
                     make_ujoint_contacts(y, jnt, 0, 1);
                  else if ((type == dpBall) || (type == dpGimbal))
                  {
                     if (!dof_free[0]) make_ujoint_contacts(y, jnt, 1, 2);
                     else if (!dof_free[1]) make_ujoint_contacts(y, jnt, 0, 2);
                     else make_ujoint_contacts(y, jnt, 0, 1);
                  }
                  else if ((type == dpBushing) || (type == dpFree))
                  {
                     for (i = 0; i < 6; i++)
                        if (dof_free[i])
                           break;
                     for (j = 3; j < 6; j++)
                        if ((dof_free[j]) && (j != i))
                           break;
                     if (i < 3)
                        make_cylindrical_contacts(y, jnt, i, j);
                     else
                        make_ujoint_contacts(y, jnt, i, j);
                  }
                  break;
               case(3): 
                  /* planar or ball */
                 if (print_contacts)
                    sim_message(none, "3 dof ");
                 if (type == dpPlanar)
                     make_planar_contacts(y, jnt, 0, 1, 2);
                 else if ((type == dpGimbal) || (type == dpBall))
                     make_ball_contacts(jnt);
                 else if ((type == dpFree) || (type == dpBushing))
                 {
                    for (i = 0; i < dof; i++)
                       if (dof_free[i])
                          break;
                    if (i < 3)
                    {
                       for (j = 0; j < 3; j++)
                          if ((dof_free[j]) && (j != i))
                             break;
                       for (k = 3; k < 6; k++)
                          if (dof_free[k])
                             break;
                       make_planar_contacts(y, jnt, i, j, k);
                    }
                    else
                    {
                       make_ball_contacts(jnt);
                    }
                 }
                 break;
               case(6): 
                  if (print_contacts)
                     sim_message(none, "6 dof: free");
                  break;
               case(-1):
                  if (print_contacts)
                     sim_message(none, "constrained joint ");
                  make_constrained_contacts(jnt, y);
                  break;
               default: 
                  if (print_contacts)
                     sim_message(none, "%d dof: ", unconstrained_dof);
                  break;
            }          
            used[jnt] = dpYes;
         }
      }
   }

   FREE_IFNOTNULL(used);

   if (print_contacts)
   {
      sim_message(none, "%d bilat contacts created\n", 	sdm->num_bilat_contacts);
      print_contacts = NO;
   }

}

static void make_constrained_contacts(int jnt, double y[])
{
   int i, j, inb, outb, dof;
   int unconstrained_dof = 0, constrained_dof = 0;
   int dof_free[6] = {NO, NO, NO, NO, NO, NO};
   int q[3], q_ind, slider_qs = 0;
   double axis[3][3], vel[3];
   double pt[3], btj[3], axis2[3], axis3[3], jnt_axis[3], vec[3];
   double q_ind_value, u_ind;
   double slider_axis[3], pin_axis[3];

   inb = sdm->joint[jnt].inboard_body;
   outb = sdm->joint[jnt].outboard_body;
   dof = sdm->joint[jnt].dof;
 
   for (i = 0; i < dof; i++)
   {
      j = sdindx(jnt, i);
      if (sdm->q[j].type == dpUnconstrainedQ)
      {
         dof_free[i] = YES;
         unconstrained_dof++;
      }
      else if (sdm->q[j].type == dpConstrainedQ)
         constrained_dof++;
   }
   if (print_contacts)
      sim_message(none, "%d unconstrained, %d constrained, %d total\n", unconstrained_dof,
             constrained_dof, dof);

   switch (unconstrained_dof)
   {
      case(0): 
         make_pin_contacts(y, jnt, 0);
         break;
      case(1):
         /* pin or slider */
         for (i = 0; i < 6; i++)
         {
            if (dof_free[i] == YES)
               break;
         }
         if (sdm->joint[jnt].dof_type[i] == dpRotational)
         {
            make_pin_contacts(y, jnt, 2);
            break;
            /* get joint center */
            sdgetbtj(jnt, btj);
            sdvcopy(sdm->joint[jnt].axes[i], pin_axis);

            /* direction of slider axis = direction of joint center velocity
             * derivative of path the joint center is constrained to follow
             * joint axis = noramlized slider axis.
             * get two orthogonal axes.
             */
            for (j = 0; j < 3; j++)
            {
               q[j] = -1;
               make_vector(axis[j], 0.0, 0.0, 0.0);
               vel[j] = 0.0;
            }

            for (j = 0; j < 3; j++)
            {
               q[j] = sdindx(jnt, j);
               normalize_vector(sdm->joint[jnt].axes[j], axis[j]);
            }

            q_ind = sdindx(jnt, i);
            q_ind_value = y[q_ind] * sdm->q[q_ind].conversion;
            u_ind = sdm->q[q_ind].conversion;

            for (j = 0; j < 3; j++)
            {
               if (sdm->q[q[j]].type == dpConstrainedQ)
                  vel[j] = interpolate_spline(q_ind_value, sdm->q[q[j]].constraint_func, first, u_ind, 0.0);
            }

            for (j = 0; j < 3; j++)
               sdvmul(vel[j], axis[j], axis[j]);
         
            make_vector(slider_axis, 0.0, 0.0, 0.0);
            for (j = 0; j < 3; j++)
               sdvadd(axis[j], slider_axis, slider_axis);

            normalize_vector(slider_axis, slider_axis);

            /* create slider-type bilateral constraint contacts.
             * 6 points, no normals along joint axis.  Prevent rotation along
             * all three axes
             */

            if (!EQUAL_WITHIN_TOLERANCE(DOT_VECTORS(slider_axis, pin_axis), 0.0, 1e-2))
            {
               show_vector("slider", slider_axis);
               show_vector("pin", pin_axis);
               sim_message(exit_program, "Make constraints: slider and pin not orthogonal.");
            }
            sdvcross(slider_axis, pin_axis, axis3);
            normalize_vector(axis3, axis3);
         
            if (EQUAL_WITHIN_TOLERANCE(VECTOR_MAGNITUDE(slider_axis), 0.0, 1e-2))
            {
               get_orthogonal_axes(pin_axis, slider_axis, axis3);
            }
            sdvcopy(btj, pt);

            sdtrans(inb, pin_axis, outb, vec);
            sdvmul(0.1, vec, vec);
            sdvadd(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis3);
            sdvsub(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis3);
        
            sdtrans(inb, slider_axis, outb, vec);
            sdvmul(0.1, vec, vec);
            sdvadd(btj, vec, pt);
            enter_node_info(inb, outb, pt, pin_axis);
            sdvsub(btj, vec, pt);
            enter_node_info(inb, outb, pt, pin_axis);
        
            if (print_contacts)
               sim_message(none, "(pin) - created ? contacts\n");
         }
         else
         {
            /* slider joint */
            /* get joint center */
            sdgetbtj(jnt, btj);

            /* direction of slider axis = direction of joint center velocity
             * derivative of path the joint center is constrained to follow
             * joint axis = noramlized slider axis.
             * get two orthogonal axes
             */

            for (j = 0; j < 3; j++)
            {
               if ((j > dof) || (sdm->joint[jnt].dof_type[j] != dpTranslational))
               {
                  q[j] = -1;
                  make_vector(axis[j], 0.0, 0.0, 0.0);
               }
               else
               {
                  q[j] = sdindx(jnt, j);
                  sdvcopy(sdm->joint[jnt].axes[j], axis[j]);
                  slider_qs++;
               }
            }

            q_ind = sdindx(jnt, i);
            q_ind_value = y[q_ind];
            u_ind = 0.50;

            for (j = 0; j < 3; j++)
            {
               if (j > slider_qs)
                  vel[j] = 0.0;
               if (sdm->q[q[j]].type == dpUnconstrainedQ)
                  vel[j] = u_ind;
               else if (sdm->q[q[j]].type == dpConstrainedQ)
                  vel[j] = interpolate_spline(q_ind_value, sdm->q[q[j]].constraint_func, first, u_ind, 0.0);
            }
         
            for (j = 0; j < 3; j++)
               sdvmul(vel[j], axis[j], axis[j]);

            make_vector(jnt_axis, 0.0, 0.0, 0.0);
            for (j = 0; j < 3; j++)
               sdvadd(axis[j], jnt_axis, jnt_axis);
         
            normalize_vector(jnt_axis, jnt_axis);
            get_orthogonal_axes(jnt_axis, axis2, axis3);	
         
            sdvel(outb, btj, vel);
            normalize_vector(vel, vel);
            if (!vect_equal_within_tol(vel, jnt_axis, 1e-5))
            {
               sdvmul(-1.0, vel, vel);
               if (!vect_equal_within_tol(vel, jnt_axis, 1e-5))
               {
                  sim_message(none, "vel and slider axis not equal\n");
                  show_vector("vel", vel);
                  show_vector("slider", jnt_axis);
               }
            }
            /* create slider-type bilateral constraint contacts.
             * 6 points, no normals along joint axis.  Prevent rotation along
             * all three axes
             */
            sdvcopy(btj, pt);
            //joint axis - for display
            //enter_node_info(inb, outb, pt, jnt_axis);
         
            sdtrans(inb, jnt_axis, outb, vec);
            sdvmul(0.1, vec, vec);
            sdvadd(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis2);
            sdvsub(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis2);
            sdvadd(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis3);
            sdvsub(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis3);
         
            sdtrans(inb, axis2, outb, vec);
            sdvmul(0.1, vec, vec);
            sdvadd(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis3);
            sdvsub(btj, vec, pt);
            enter_node_info(inb, outb, pt, axis3);
         
            if (print_contacts)
               sim_message(none, "(slider) - created 6 contacts\n");
         }
         break;

      case(2):
         /* get joint center */
         sdgetbtj(jnt, btj);
         sdvcopy(sdm->joint[jnt].axes[1], pin_axis);

         /* direction of slider axis = direction of joint center velocity
          * derivative of path the joint center is constrained to follow
          * joint axis = normalized slider axis.
          * get two orthogonal axes.
          */

         for (j = 0; j < 3; j++)
         {
            if ((j > dof) || (sdm->joint[jnt].dof_type[j] != dpTranslational))
            {
               q[j] = -1;
               make_vector(axis[j], 0.0, 0.0, 0.0);
            }
            else
            {
               q[j] = sdindx(jnt, j);
               normalize_vector(sdm->joint[jnt].axes[j], axis[j]);
               slider_qs++;
            }
         }

         q_ind = sdindx(jnt, 0);
         q_ind_value = y[q_ind];
         u_ind = 0.50;

         for (j = 0; j < 3; j++)
         {
            if (j >= slider_qs)
               vel[j] = 0.0;
            if (sdm->q[q[j]].type == dpUnconstrainedQ)
               vel[j] = u_ind;
            else if (sdm->q[q[j]].type == dpConstrainedQ)
               vel[j] = interpolate_spline(q_ind_value, sdm->q[q[j]].constraint_func, first, u_ind, 0.0);
         }
         
         for (j = 0; j < 3; j++)
            sdvmul(vel[j], axis[j], axis[j]);
         
         make_vector(jnt_axis, 0.0, 0.0, 0.0);
         for (j = 0; j < 3; j++)
            sdvadd(axis[j], jnt_axis, jnt_axis);

         normalize_vector(jnt_axis, jnt_axis);

         /* create slider-type bilateral constraint contacts.
          * 6 points, no normals along joint axis.  Prevent rotation along
          * all three axes */
         sdvcopy(btj, pt);
         //joint axis - for display
         //enter_node_info(inb, outb, pt, jnt_axis);
         
         sdvcopy(jnt_axis, slider_axis);
        // show_vector("slider", slider_axis);
        // show_vector("pin", pin_axis);
         sdvel(outb, btj, vec);
         normalize_vector(vec, slider_axis);
         if (!EQUAL_WITHIN_TOLERANCE(DOT_VECTORS(slider_axis, pin_axis), 0.0, 1e-2))
         {
            show_vector("pin", pin_axis);
            show_vector("slider", slider_axis);
            sim_message(exit_program, "Make constraints: slider and pin not orthogonal.");
         }
         sdvcross(slider_axis, pin_axis, axis3);
         normalize_vector(axis3, axis3);
         // show_vector("axis3", axis3);
         //enter_node_info(inb, outb, btj, pin_axis);
 
         sdtrans(inb, pin_axis, outb, vec);
         sdvmul(0.1, vec, vec);
         sdvadd(btj, vec, pt);
         enter_node_info(inb, outb, pt, axis3);
         sdvsub(btj, vec, pt);
         enter_node_info(inb, outb, pt, axis3);
       
         sdtrans(inb, slider_axis, outb, vec);
         sdvmul(0.1, vec, vec);
         sdvadd(btj, vec, pt);
         enter_node_info(inb, outb, pt, pin_axis);
         sdvsub(btj, vec, pt);
         enter_node_info(inb, outb, pt, pin_axis);
    
         if (print_contacts)
            sim_message(none, "(pin) - created ? contacts\n");
         break;
   }
}


/* Bilateral constraints for pin joints - prevent any translation and rotation
 * about axes other than hinge axis.
 */
static void make_pin_contacts(double y[], int jnt, int axis)
{
   int inb, outb, q;
   double jnt_axis[3], axis2[3], axis3[3], btj[3], pt[3], vec[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;

	/* get joint axis and two orthogonal axes in inboard body frame */
	get_joint_axis(y, jnt, axis, jnt_axis);
	normalize_vector(jnt_axis, jnt_axis);
	get_orthogonal_axes(jnt_axis, axis2, axis3);
	sdgetbtj(jnt, btj);

   q = sdindx(jnt, axis);
	/* point at joint center with normal along hinge axis - prevent
	 * translation along hinge axis
    */
	sdvcopy(btj, pt);
   // if (sdm->q[q].type != constrained_q)
	enter_node_info(inb, outb, pt, jnt_axis);

	/* two points on either side of the joint center, with normals 
	 * orthogonal to joint axis - prevent translation and moments about
	 * non-hinge axes.
    */
	sdtrans(inb, jnt_axis, outb, vec);
	sdvmul(0.1, vec, vec);

	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis2);
	enter_node_info(inb, outb, pt, axis3);
	
	sdvsub(btj, vec, pt);	
	enter_node_info(inb, outb, pt, axis2);
	enter_node_info(inb, outb, pt, axis3);

   if (print_contacts)
      sim_message(none, "(pin) - created 5 contacts\n");
} 


/* Bilateral constraint points for slider joints.  No contact normals
 * should point in the direction of the sliding!!  Put four points
 * on the joint axis, two on either side of the joint center.  Use the
 * two orthogonal axes as the normals (other1 and other2) - prevent sliding
 * and moments about the other 2 axes.  Then put
 * two points on one of the other axes (other1) with normals in the direction
 * of the 3 axis (other2) to prevent moments about the sliding axis.
 */
static void make_slider_contacts(double y[], int jnt, int axis)
{
   int inb, outb;
   double btj[3], jnt_axis[3], vec[3], pt[3], inb_axis[3];
   double axis2[3], axis3[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;
	sdgetbtj(jnt, btj);
	
	get_joint_axis(y, jnt, axis, jnt_axis);
	get_orthogonal_axes(jnt_axis, axis2, axis3);	

	/* check that inb and outb joint axis have not rotated */
	sdvcopy(sdm->joint[jnt].axes[axis], inb_axis);
	if (!vect_equal_within_tol(inb_axis, jnt_axis, 1e-2))
   {
		show_vector("\noutboard axis", jnt_axis);
		show_vector("inboard axis ", inb_axis);
		sim_message(exit_program, "Axis of inboard and outboard body not aligned.");
	}
	
	sdvcopy(btj, pt);

	sdtrans(inb, jnt_axis, outb, vec);
	sdvmul(0.1, vec, vec);
	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis2);
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis2);
	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis3);
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis3);

	sdtrans(inb, axis2, outb, vec);
	sdvmul(0.1, vec, vec);
	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis3);
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis3);

   if (print_contacts)
      sim_message(none, "(slider) - created 6 contacts\n");

}


static void make_cylindrical_contacts(double y[], int jnt, int transl, int rot)
{
   int inb, outb;
   double jnt_axis[3], pt[3], vec[3], btj[3];
   double axis2[3], axis3[3], inb_axis[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;
	
	get_joint_axis(y, jnt, transl, jnt_axis);

	/* if the inbody and outbody vectors are not the same, the outboard body
	 * has rotated wrt the inboard and the sixdof joint is no longer
	 * constrained as cylindrical.
    */
	sdvcopy(sdm->joint[jnt].axes[transl], inb_axis);
	if (!vect_equal_within_tol(inb_axis, jnt_axis, 1e-2))
   {
		show_vector("\noutboard axis", jnt_axis);
		show_vector("inboard axis ", inb_axis);
		sim_message(exit_program, "Axis of inboard and outboard body not aligned.");
	}
	
	/* create 4 points, 2 on either side of the joint center along the
	 * transl./rot. axis.  The normal vectors are orthogonal to the joint vector
	 */
	sdtrans(inb, jnt_axis, outb, vec);
	get_orthogonal_axes(jnt_axis, axis2, axis3);
	sdgetbtj(jnt, btj);
	sdvmul(0.1, vec, vec);	
	sdvcopy(btj, pt);

	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis2);
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis2);
	
	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis3);
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, axis3);

   if (print_contacts)
      sim_message(none, "(cylindrical) - created 4 contacts\n");
}


static void make_ujoint_contacts(double y[], int jnt, int axis1, int axis2)
{
   int inb, outb,   start = 0;
   double jnt_axis1[3], jnt_axis2[3], jnt_axis3[3], pt[3], vec[3], btj[3];
   double norm[3], neg_norm[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;

	get_joint_axis(y, jnt, axis1, jnt_axis1);
	get_joint_axis(y, jnt, axis2, jnt_axis2);

	/* get a third axis */
	sdvcross(jnt_axis1, jnt_axis2, jnt_axis3);
	normalize_vector(jnt_axis3, jnt_axis3);

	/* to prevent moments about non-hinge axes, find a normal orthogonal
	 * to axis1 and axis2
    */
	sdvcross(jnt_axis1, jnt_axis2, norm);	
	sdvcross(jnt_axis1, norm, norm);

	sdgetbtj(jnt, btj);
	sdvcopy(btj, pt);
	
	/* compare norm with three jnt axes */
	sdvmul(-1.0, norm, neg_norm);
	if (!vect_equal_within_tol(norm, jnt_axis1, 1e-4)
		&& !(vect_equal_within_tol(neg_norm, jnt_axis1, 1e-4)))
   {
		enter_node_info(inb, outb, pt, jnt_axis1);
	}
	if (!vect_equal_within_tol(norm, jnt_axis2, 1e-4)
		&& !(vect_equal_within_tol(neg_norm, jnt_axis2, 1e-4)))
   {
		enter_node_info(inb, outb, pt, jnt_axis2);
	}
	if (!vect_equal_within_tol(norm, jnt_axis3, 1e-4)
		&& !(vect_equal_within_tol(neg_norm, jnt_axis3, 1e-4)))
   {
		enter_node_info(inb, outb, pt, jnt_axis3);
	}

	sdtrans(inb, jnt_axis1, outb, vec);
	sdvmul(0.1, vec, vec);
	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, norm);
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, norm);

	if (print_contacts)
      sim_message(none, "(ujoint) - created 5 contacts\n");

}


/* Bilateral contacts for planar joints resist translation in the
 * direction of the rotation axis and moments orthogonal to this axis.
 */
static void make_planar_contacts(double y[], int jnt, int t1, int t2, int rot)
{
   int inb, outb;
   double rotation_axis[3], inb_rot_axis[3], axis2[3], axis3[3];
   double btj[3], vec[3], pt[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;

	/* forces can only be applied in the direction of the hinge
	 * joint axis for planar joints.
    */
	
	get_joint_axis(y, jnt, rot, rotation_axis);
	get_orthogonal_axes(rotation_axis, axis2, axis3);

	/* check that the rotation axis in inboard frame = 
	 * rotation axis in joint info.  If not, won't work.
    */
	sdvcopy(sdm->joint[jnt].axes[rot], inb_rot_axis);
	if (!vect_equal_within_tol(inb_rot_axis, rotation_axis, 1e-4))
   {
		show_vector("\nrot axis", rotation_axis);
		show_vector("inb axis", inb_rot_axis);
		sim_message(exit_program, "Rotation axes of inboard and outboard bodies not aligned.");
	}

	/* put two contact points on each axis orthogonal to the rotation
	 * axis, with normals in the direction of the rotation axis.
    */
	sdgetbtj(jnt, btj);

	sdtrans(inb, axis2, outb, vec);
	sdvmul(0.1, vec, vec);	
	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, rotation_axis);	
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, rotation_axis);

	sdtrans(inb, axis3, outb, vec);
	sdvmul(0.1, vec, vec);	
	sdvadd(btj, vec, pt);
	enter_node_info(inb, outb, pt, rotation_axis);	
	sdvsub(btj, vec, pt);
	enter_node_info(inb, outb, pt, rotation_axis);

   if (print_contacts)
      sim_message(none, "(planar) - created 4 contacts\n");
}


static void make_ball_contacts(int jnt)
{
   int inb, outb, j;
   double norm[3], btj[3], pt[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;
	sdgetbtj(jnt, btj);

	/* for ball joints, create three points at the joint center.  Each point
	 * has a normal along one of the X, Y or Z axes to prevent translation
	 * along that axis.
    */
	for (j = 0; j < 3; j++)
   {
		make_vector(norm, 0.0, 0.0, 0.0);
		norm[j] = 1.0;
		sdvcopy(btj, pt);
		enter_node_info(inb, outb, pt, norm);
	}

   if (print_contacts)
      sim_message(none, "(ball) - created 3 contacts\n");
}


static void make_fixed_contacts(int jnt)
{
   int inb, outb, i;
   double vec[3], norm[3], btj[3], pt[3], axis[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;
	sdgetbtj(jnt, btj);

	/* create 2 contact points along each axis (X, Y, Z) - one on either side
	 * of the joint center.  Both points have normals perpendicular to axis 
	 * (Y, Z, X)
    */	 
	for (i = 0; i < 3; i++)
   {
		make_vector(axis, 0.0, 0.0, 0.0);
		axis[i] = 1.0;
		make_vector(norm, 0.0, 0.0, 0.0);
		norm[(i + 1) % 3] = 1.0;

		sdtrans(inb, axis, outb, vec);
		sdvmul(0.1, vec, vec);
		sdvadd(btj, vec, pt);
		enter_node_info(inb, outb, pt, norm);
		sdvsub(btj, vec, pt);
		enter_node_info(inb, outb, pt, norm);
	}

   if (print_contacts)
      sim_message(none, "(fixed) - created 6 contacts\n");
}


/* get the actual joint axis in the inboard body frame */
static void get_joint_axis(double y[], int jnt, int axis, double jnt_axis[])
{
   int inb, outb, dof, q3;
   double ang3, axis3[3], dc[4][4], axis2[3];

	inb = sdm->joint[jnt].inboard_body;
	outb = sdm->joint[jnt].outboard_body;
	dof = sdm->joint[jnt].dof;

	/* joints with 6 DOF - 
	 * joints with 3 DOF - 
	 * for 3 rotational axes:
	 *	 the first axis is fixed on the inboard body - just copy axis
	 *  the second axis has to be transformed backwards using the negative
	 *  angle of rotation about the third axis (get q of third rotational axis)
	 *  the third axis is fixed on the outboard body - transform it into 
	 *  the inboard frame.
	 * other joints:
	 *  pin, cyl - axis = 0, stuck on inboard body, just copy it
	 *  ujoint - axis = 0 - stuck on inboard body - just copy it
	 *           axis = 1 - stuck on outboard body - transform it to inboard
	 *                       body frame
	 */
	if (dof == 6)
   {
		if (axis >=3)	axis -= 3;
		q3 = sdindx(jnt, 5);
	}
   else if (dof == 3)
   {
		q3 = sdindx(jnt, 2);
	}
   else
   {
		if (axis == 1)
			sdtrans(outb, sdm->joint[jnt].axes[axis], inb, jnt_axis);
		else
			sdvcopy(sdm->joint[jnt].axes[axis], jnt_axis);
		return;
	}
	
	if (axis == 0)
		sdvcopy(sdm->joint[jnt].axes[axis], jnt_axis);
	else if (axis == 2) 
		sdtrans(outb, sdm->joint[jnt].axes[axis], inb, jnt_axis);
	else if (axis == 1)
   {
		sdvcopy(sdm->joint[jnt].axes[1], axis2);
		sdvcopy(sdm->joint[jnt].axes[2], axis3);
		ang3 = -1.0 * (RAD2DEG(y[q3]));
		make_4x4dircos_matrix(ang3, axis3, dc);
		transform_vec(dc, axis2);
		sdvcopy(axis2, jnt_axis);
		sdtrans(outb, jnt_axis, inb, jnt_axis);
	}
}


static void get_orthogonal_axes(double jnt_axis[], double norm1[], double norm2[])
{
   double vec[3], mag;

	/* find two normals orthogonal to joint axis.  norm1 = jnt_axis X (1 0 0)
	 * if norm1 = 0, try norm1 = jnt_axis X (0 1 0).  norm2 = jnt axis X norm1
	 */
	make_vector(vec, 1.0, 0.0, 0.0);
	sdvcross(jnt_axis, vec, norm1);

	mag = normalize_vector(norm1, norm1);

	/* if jnt_axis != norm1, norm2 = jnt_axis X norm1, else choose new n1 */
	if (!EQUAL_WITHIN_TOLERANCE(mag, 0.0, 1e-5))
   {
		sdvcross(jnt_axis, norm1, norm2);
		normalize_vector(norm2, norm2);
      sdvcross(jnt_axis, norm2, norm1);
      normalize_vector(norm1, norm1);
	}
   else
   {
		make_vector(vec, 0.0, 1.0, 0.0);
		sdvcross(jnt_axis, vec, norm1);
		normalize_vector(norm1, norm1);
		sdvcross(jnt_axis, norm1, norm2);
		normalize_vector(norm2, norm2);
	}
}


/* give inboard and outboard bodies, contact point location in  outboard frame,
 * and normal in inboard frame */
static void enter_node_info(int inb, int outb, double outb_pt[3], 
	                         double inb_norm[3])
{

   if (sdm->num_bilat_contacts >= sdm->bilat_contacts_size)
   {
      sdm->bilat_contacts_size += 100;
      sdm->bilat_contacts = (dpContactInfo*)realloc(sdm->bilat_contacts, sdm->bilat_contacts_size * sizeof(dpContactInfo));
   }

   sdm->bilat_contacts[sdm->num_bilat_contacts].body1 = inb;       
   sdm->bilat_contacts[sdm->num_bilat_contacts].body2 = outb;               
   sdvcopy(outb_pt, sdm->bilat_contacts[sdm->num_bilat_contacts].pt2);
   convert_point2(outb, sdm->bilat_contacts[sdm->num_bilat_contacts].pt2, inb, sdm->bilat_contacts[sdm->num_bilat_contacts].pt1);
	
	/* normal fixed to inbody - works better than fixed to outbody - 
	 * get increases in energy sometimes after computing impacts.
    */
   sdvcopy(inb_norm, sdm->bilat_contacts[sdm->num_bilat_contacts].norm1);
   sdtrans(inb, sdm->bilat_contacts[sdm->num_bilat_contacts].norm1, 
      outb, sdm->bilat_contacts[sdm->num_bilat_contacts].norm2);
   sdvmul(-1.0, sdm->bilat_contacts[sdm->num_bilat_contacts].norm1, 
      sdm->bilat_contacts[sdm->num_bilat_contacts].norm1);
   sdtrans(outb, sdm->bilat_contacts[sdm->num_bilat_contacts].norm2, GROUND, 
      sdm->bilat_contacts[sdm->num_bilat_contacts].outward_norm);

   make_vector(sdm->bilat_contacts[sdm->num_bilat_contacts].vel1, 0.0, 0.0, 0.0);
   make_vector(sdm->bilat_contacts[sdm->num_bilat_contacts].vel2, 0.0, 0.0, 0.0);
   make_vector(sdm->bilat_contacts[sdm->num_bilat_contacts].rel_vel, 0.0, 0.0, 0.0);
   make_vector(sdm->bilat_contacts[sdm->num_bilat_contacts].cont_frc, 0.0, 0.0, 0.0);
   sdm->bilat_contacts[sdm->num_bilat_contacts].acc = 0.0;
   sdm->bilat_contacts[sdm->num_bilat_contacts].coef_rest = 0.0;
   sdm->bilat_contacts[sdm->num_bilat_contacts].mu_dynamic = 0.0;
   sdm->bilat_contacts[sdm->num_bilat_contacts].mu_static = 0.0;
   sdm->bilat_contacts[sdm->num_bilat_contacts].contact_type = dpRestingContact;
   sprintf(sdm->bilat_contacts[sdm->num_bilat_contacts].type1, "BILAT CONT");
   sprintf(sdm->bilat_contacts[sdm->num_bilat_contacts].type2, "BILAT CONT");
   sdm->bilat_contacts[sdm->num_bilat_contacts].dist = 0.0;
   sdm->num_bilat_contacts++;
}


/* copy information from dpContactInfo into another dpContactInfo */
void copy_cnode(dpContactInfo from, dpContactInfo *to)
{
	to->body1 = from.body1;
	to->body2 = from.body2;
	sdvcopy(from.pt1, to->pt1);
	sdvcopy(from.pt2, to->pt2);
	sdvcopy(from.norm1, to->norm1);
	sdvcopy(from.norm2, to->norm2);
	sdvcopy(from.outward_norm, to->outward_norm);
	sdvcopy(from.vel1, to->vel1);
	sdvcopy(from.vel2, to->vel2);
	sdvcopy(from.rel_vel, to->rel_vel);
	sdvcopy(from.cont_frc, to->cont_frc);
	to->acc = from.acc;
	to->coef_rest = from.coef_rest;
	to->mu_dynamic = from.mu_dynamic;
	to->mu_static = from.mu_static;
	to->contact_type = from.contact_type;
	strcpy(to->type1, from.type1);
	strcpy(to->type2, from.type2);
	to->dist = from.dist;

}


/* MAKEPATHS: for each body in the model, create a list of all the joints used
 * in connecting it with every other body in the model.
 */

ReturnCode makepaths(void)
{
   
   int i, j, k, m, n, jnt, segments, old_count, np;
   int* path;
   int from, to, nsq, nj, index, numpaths = 0;
  
   /* determine the number of non-loop joints in the system */
   for (i=0, nj=0; i<sdm->num_joints; i++)
   {    
      if (sdm->joint[i].loop_joint == dpNo)
         nj++;
   }  
   
   segments = sdm->num_body_segments;
   nsq = segments*segments;

   if (pathptrs != NULL)
   {
      for (i=0; i<nsq; i++)
      {
         FREE_IFNOTNULL(pathptrs[i]);
      }
      free(pathptrs);
   }
   
   path = (int*)simm_malloc(nsq*sizeof(int));
   pathptrs = (int **)simm_malloc(nsq*sizeof(int *));
   if (path == NULL || pathptrs == NULL)
      return code_bad;
   
   for (i=0; i<nsq; i++)
      pathptrs[i] = (int *)0;
   
   /* set the path for the diagonal elements in the matrix (path = i i -1) */
   path[2] = END_OF_ARRAY;
   for (i=0; i<segments; i++)
   {
      path[0] = path[1] = i;
      if (setpath(path) == code_bad)
         return code_bad;
   }
   
   /* set the paths for all pairs of bodies directly connected by joints. 
    * Consider both directions.  Ignore loop joints and free joints 
    * (6 unconstrained DOFs).  (path = i j -1)
    */
   path[2] = END_OF_ARRAY;
   for (i=0; i<sdm->num_joints; i++)
   {
      if (sdm->joint[i].loop_joint == dpYes)
         continue;
      m = sdm->joint[i].inboard_body + 1;
      n = sdm->joint[i].outboard_body + 1;
      if (joint_is_free(i) == dpYes)
         continue;

      /* forward direction */
      path[0] = m;
      path[1] = n;
      if (setpath(path) == code_bad)
         return code_bad;

      /* reverse direction */
      path[0] = n;
      path[1] = m;
      if (setpath(path) == code_bad)
         return code_bad;
   }
   
   /* fill in the rest of the matrix elements - the paths between all pairs of bodies.
    * For each joint (known path m -> n or n -> m), look at all body pairs.  If a path
    * exists between the pair (j -> k) and k is a body in the joint (k = m or k = n),
    * add the other body (n or m) in the joint to the path (j -> n,m through k).  Do
    * not connect the bodies if k is GROUND.
    * Don't use loop joints or bodies connected by free (6dof unconstrained) joints
    * to create paths.
    */
   while (1)
   {
      old_count = numpaths;
      for (i=0; i<sdm->num_joints; i++)
      {
         if (sdm->joint[i].loop_joint == dpYes)
            continue;
         m = sdm->joint[i].inboard_body + 1;
         n = sdm->joint[i].outboard_body + 1;
         if (joint_is_free(i) == dpYes)
            continue;
         for (j=0; j<segments; j++)
         {
            for (k=0; k<segments; k++)
            {
               if (k == j)
                  continue;
               if (k == GROUND + 1)
                  continue;
               index = j*segments+k;
               /* a path exists from j->k, add m->n to create new path from j->n*/
               if (pathptrs[index] != NULL && k == m)
               {
                  if ((np = enterpath(j,k,n)) == -1)
                     return code_bad;
                  else
                     numpaths += np;
               }
               /* a path exists from j->k, add n->m to create new path from j->m*/
               if (pathptrs[index] != NULL && k == n)
               {
                  if ((np = enterpath(j,k,m)) == -1)
                     return code_bad;
                  else
                     numpaths += np;
               }
            }
         }
      }
      /* if no new paths have been added, the matrix has been filled in */
      if (numpaths == old_count)
         break;
   }
   
  
   /* Now that the paths have been made, turn them into a list of joints,
    * rather than body segments.  END_OF_ARRAY marks the end of the list, an empty
    * list, and diagonal elements of the matrix.
    */
   for (i=0; i<segments; i++)
   {
      for (j=0; j<segments; j++)
      {
         index = i*segments+j;
         if (pathptrs[index] == NULL)
         {
            pathptrs[index] = (int *)simm_malloc(sdm->num_joints + 1 * sizeof(int));
            pathptrs[index][0] = END_OF_ARRAY;
            continue;
         }
         for (k = 0; pathptrs[index][k+1] != END_OF_ARRAY; k++)
         {
            from = pathptrs[index][k];
            to = pathptrs[index][k+1];
            pathptrs[index][k] = find_joint_between_simm_segments(from,to);
         }
         pathptrs[index][k] = -1;
      }
   }
   
   /* copy information into sdm->body_segments.  For each body, make list
    * of all joints needed to connect it to all other bodies
    */
   for (i = 0; i < segments; i++)
   {
      sdm->body_segment[i].contact_joints = 
         (dpBoolean *)simm_malloc(sdm->num_joints * sizeof(dpBoolean));
      for (j = 0; j < sdm->num_joints; j++)
         sdm->body_segment[i].contact_joints[j] = dpNo;
   }

   for (i = 0; i < segments; i++)
   {
      for (j = 0; j < segments; j++)
      {
         index = i*segments + j;
         k = 0;
         while(1)
         {
            jnt = pathptrs[index][k];
            if (jnt == END_OF_ARRAY)
               break;
            sdm->body_segment[i].contact_joints[jnt] = dpYes;
            k++;
         }
      }
   }
   
   /* add loop joint information to the pathptrs and contact joints. Bodies
    * m and n should both contain the same contact joint information.
    */
   for (i = 0; i < sdm->num_joints; i++)
   {
      if (sdm->joint[i].loop_joint == dpYes)
      {
         m = sdm->joint[i].inboard_body + 1;
         n = sdm->joint[i].outboard_body + 1;
         index = m * segments + n;
         pathptrs[index][0] = i;
         pathptrs[index][1] = END_OF_ARRAY;
         index = n * segments + m;
         pathptrs[index][0] = i;
         pathptrs[index][1] = END_OF_ARRAY;
         sdm->body_segment[m].contact_joints[i] = dpYes;
         sdm->body_segment[n].contact_joints[i] = dpYes;
         for (j = 0; j < sdm->num_joints; j++)
         {
            if (sdm->body_segment[m].contact_joints[j] == dpYes)
               sdm->body_segment[n].contact_joints[j] = dpYes;
            if (sdm->body_segment[n].contact_joints[j] == dpYes)
               sdm->body_segment[m].contact_joints[j] = dpYes;
         }
      }
   }

   /* Add paths reached through loop joints for each body.  For each loop joint,
    * check whether a path exists for each body (j) to loop joint bodies (m, n).
    * If a path exists from j -> m, fill in joint information from n into j.
    * Update the pathptrs by adding paths from j->n and n->j if they don't already
    * exist.
    * If a path exists from j -> n, fill in joint information from m into j.
    * Update the pathptrs by adding paths from j->m and m->j if they don't already
    * exist.
    */
   numpaths = 0;
   while(1)
   {
      old_count = numpaths;
      for (i = 0; i < sdm->num_joints; i++)
      {
         if (sdm->joint[i].loop_joint == dpYes)
         {
            m = sdm->joint[i].inboard_body + 1;
            n = sdm->joint[i].outboard_body + 1;
            for (j = 0; j < segments; j++)
            {
               index = j * segments + m;
               /* if a path exists from j->m, create a path from j->n across the weld
                * joint.  Add all the joints used by body n to the body j record.
                * create a new path from j->n and n->j.
                */
               if (pathptrs[index][0] != END_OF_ARRAY)
               {
                  for (jnt = 0; jnt < sdm->num_joints; jnt++)
                     if (sdm->body_segment[n].contact_joints[jnt] == dpYes)
                        sdm->body_segment[j].contact_joints[jnt] = dpYes;
                  if (j == n)
                     continue;
                  index = j * segments + n;
                  if (pathptrs[index][0] == END_OF_ARRAY)
                  {
                     for (jnt = 0, k = 0; jnt < sdm->num_joints; jnt++)
                        if (sdm->body_segment[j].contact_joints[jnt] == dpYes)
                           pathptrs[index][k++] = jnt;
                        pathptrs[index][k] = END_OF_ARRAY;
                        numpaths++;
                  }
                  index = n * segments + j;
                  if (pathptrs[index][0] == END_OF_ARRAY)
                  {
                     for (jnt = 0, k = 0; jnt < sdm->num_joints; jnt++)
                        if (sdm->body_segment[j].contact_joints[jnt] == dpYes)
                           pathptrs[index][k++] = jnt;
                        pathptrs[index][k] = END_OF_ARRAY;
                        numpaths++;
                  }
               }
               
               index = j * segments + n;
               /* if a path exists from j->n, create a path from j->m across the weld
                * joint.  Add all the joints used by body m to the body j record.
                * create a new path from j->m and m->j.
                */
               if (pathptrs[index][0] != END_OF_ARRAY)
               {
                  for (jnt = 0; jnt < sdm->num_joints; jnt++)
                  {
                     if (sdm->body_segment[m].contact_joints[jnt] == dpYes)
                        sdm->body_segment[j].contact_joints[jnt] = dpYes;
                  }
                  if (j == m)
                     continue;
                  
                  index = j * segments + m;
                  if (pathptrs[index][0] == END_OF_ARRAY)
                  {
                     for (jnt = 0, k = 0; jnt < sdm->num_joints; jnt++)
                        if (sdm->body_segment[j].contact_joints[jnt] == dpYes)
                           pathptrs[index][k++] = jnt;
                     pathptrs[index][k] = END_OF_ARRAY;
                     numpaths++;
                  }
                  index = m * segments + j;
                  if (pathptrs[index][0] == END_OF_ARRAY)
                  {
                     for (jnt = 0, k = 0; jnt < sdm->num_joints; jnt++)
                        if (sdm->body_segment[j].contact_joints[jnt] == dpYes)
                           pathptrs[index][k++] = jnt;
                     pathptrs[index][k] = END_OF_ARRAY;
                     numpaths++;
                  }
               }
            }
         }
      }
      /* continue until no new additions to the path pointer array have been made. */
      if (old_count == numpaths)
         break;
   } 
   
   free(path);

   return code_fine;

}


/* return yes if the joint has 6 unconstrained degrees of freedom */
static dpBoolean joint_is_free(int jnt)
{
   int i, q;

   if ((sdm->joint[jnt].jnt_type != dpFree) && (sdm->joint[jnt].jnt_type != dpBushing)
      && (sdm->joint[jnt].jnt_type != dpReverseBushing))
      return dpNo;

   for (i = 0; i < 6; i++)
   {
      q = sdindx(jnt, i);
      if (sdm->q[q].type != dpUnconstrainedQ)
         return dpNo;
   }
   return dpYes;
}


/* find the joint between the two given segments. Return -1 if none is found */
static int find_joint_between_simm_segments(int from, int to)
{
   int i, in, out;

   /* transform from simm segment numbers to SD/FAST numbers */
   in = from - 1;
   out = to - 1;
   if (in == out)
      return -1;

   for (i = 0; i < sdm->num_joints; i++)
   {
      if ((sdm->joint[i].inboard_body == in) && (sdm->joint[i].outboard_body == out))
         return i;
      if ((sdm->joint[i].inboard_body == out) && (sdm->joint[i].outboard_body == in))
         return i;
   }
   return -1;
}


static void printpaths(void)
{
   
   int i, j, k, index;
   
   sim_message(none, "\n\n*******************\n");
   for (i=0; i<sdm->num_body_segments; i++)
   {
      for (k=0; k<sdm->num_body_segments; k++)
      {
         if (i == k)
            continue;
         index = i*sdm->num_body_segments+k;
         sim_message(none, "path from %s to %s: ", sdm->body_segment[i].name,
            sdm->body_segment[k].name);
         if (pathptrs[index] == NULL)
         {
            sim_message(none, "empty\n");
            continue;
         }

         for (j = 0; pathptrs[index][j] != -1; j++)
         {
             sim_message(none, "jnt%d ", pathptrs[index][j]);
         }
         sim_message(none, "\n");
      }
   }
   sim_message(none, "\n*******************\n\n");

}


/* ENTERPATH: This routine finds the path from j to k in the pathptrs
 * list, adds newend onto the end of it, and puts the result back in
 * pathptrs as the path from j to newend.
 */

static int enterpath(int j, int k, int newend)
{
   int i, index, path[128]; /* TODO: static size */

   index = j*sdm->num_body_segments + k;

   /* If there is already a path from j to newend, just return */
   if (pathptrs[j*sdm->num_body_segments+newend] != NULL)
      return 0;

   i = 0;
   while (pathptrs[index][i] != k)
   {
      path[i] = pathptrs[index][i];
      i++;
   }
   path[i] = k; 
   path[i+1] = newend;
   path[i+2] = END_OF_ARRAY;

   if (setpath(path) == code_bad)
      return -1;

   return 1;

}


/* SETPATH: given a list of segments, this routine finds which pathpointer
 * array should be equal to it. For example, if the list is 2 5 4 7 3,
 * then the list is the path for the segment pair (2,3).
 */

static ReturnCode setpath(int list[])
{
   int i, length, start, finish, index;

   start = list[0];
   finish = find_end_of_array(list,&length);
   index = start * sdm->num_body_segments + finish;

   pathptrs[index] = (int*)simm_malloc(length*sizeof(int));
   if (pathptrs[index] == NULL)
      return code_bad;

   for (i=0; i<length; i++)
   {
      pathptrs[index][i] = list[i];
   }

   return code_fine;
}


void print_contact_list(dpContactInfo list[], int n)
{
   int i;

   if (n == 0)
   {
      sim_message(none, "NO CONTACTS");
   }
   else
   {
      for (i = 0; i < n; i++)
      {
         sim_message(none, "\nCONTACT %d", i+1);
         sim_message(none, "    %s - %s", list[i].type1, list[i].type2);
         sim_message(none, "    on %s", sdm->body_segment[list[i].body1 + 1].name);
         show_vector("    pt", list[i].pt1);
         show_vector("    normal", list[i].norm1);
         show_vector("    vel", list[i].vel1);
         sim_message(none, "    on %s", sdm->body_segment[list[i].body2 + 1].name);
         show_vector("    pt", list[i].pt2);
         show_vector("    normal", list[i].norm2);
         show_vector("    vel", list[i].vel2);
         show_vector("    out_norm", list[i].outward_norm);
         sim_message(none, "    coef_rest = %f", list[i].coef_rest);
         show_vector("    cont_frc", list[i].cont_frc);
         sim_message(none, "    norm_rel_vel = %f", DOT_VECTORS(list[i].rel_vel, 
            list[i].outward_norm));
         if (list[i].contact_type == dpImpact)
            sim_message(none, "    IMPACT");
         else if (list[i].contact_type == dpRestingContact)
            sim_message(none, "    CONTACT");
         else if (list[i].contact_type == dpSeparatingContact) 
            sim_message(none, "    SEPARATING");
         else sim_message(none, "    UNKNOWN");
      }
   }
}

#endif






