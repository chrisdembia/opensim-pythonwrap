/*******************************************************************************

   SPRING_BASED.C

   Author: Krystyne Blaikie

   Copyright (c) 2000-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains the functions to calculate and apply
      spring forces for spring-based contact.

   Routines:
      check_spring_info:      make sure spring elements are properly defined
      apply_spring_forces:    apply forces at contact springs
      calculate_spring_force: calculate the force in a spring
      enter_spring_floor:     enters a spring floor in the master list
      show_spring_info:       display information about spring elements to screen
	
*******************************************************************************/
#include "universal.h"

/*************** DEFINES (for this file only) *********************************/


/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/


/**************** GLOBAL VARIABLES (used in only a few files) *****************/


/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;

/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/


/*************************** FUNCTION PROTOTYPES ******************************/
static int enter_spring_floor(char name[]);
static void calculate_spring_force(dpSpringStruct spring, dpSpringFloor floor, 
                                   double pt1[], double pt2[], double force[]);

/* check that all elements floor elements were properly defined.
 * Set floor plane information
 */
void check_spring_info(void)
{
   int i, floor_num, errors = 0;

   /* check that the floor associated with each spring has been defined, and
    * store the index of the spring_floor
    */
   for (i = 0; i < sdm->num_springs; i++)
   {
      floor_num = enter_spring_floor(sdm->spring[i].floor_name);
      if (floor_num < 0)
      {
         sim_message(none, "Floor %s is undefined.", sdm->spring[i].floor_name);
         errors++;
      }
      else
      {
         sdm->spring[i].floor = floor_num;
      }
   }

   /* for each spring floor, copy the information from the first polygon in 
    * the polyhedron to the floor's plane information
    */
   for (i = 0; i < sdm->num_spring_floors; i++)
   {
      sdm->spring_floor[i].plane.a = sdm->spring_floor[i].ph->polygon[0].normal[0];
      sdm->spring_floor[i].plane.b = sdm->spring_floor[i].ph->polygon[0].normal[1];
      sdm->spring_floor[i].plane.c = sdm->spring_floor[i].ph->polygon[0].normal[2];
      sdm->spring_floor[i].plane.d = sdm->spring_floor[i].ph->polygon[0].d;
   }

   if (errors > 0)
      sim_message(exit_program, "");
}


/* calculate and apply forces from spring elements for spring-based contact
 * detection.
 */
void apply_spring_forces(dpModelStruct *sdm)
{
   int i;
   double pt1[3], pt2[3], force[3], frc1[3], frc2[3];
   dpSpringStruct *spring;
   dpSpringFloor floor;

   for (i = 0; i < sdm->num_springs; i++)
   {
      spring = &sdm->spring[i];
      floor = sdm->spring_floor[spring->floor];
      
      /* convert spring point into plane frame */
      convert_point2(spring->segment, spring->point, floor.segment, pt1);
   
      /* project point onto plane */
      project_point_onto_plane(pt1, &floor.plane, pt2);

      /* calculate the spring force in the floor frame */
      calculate_spring_force(*spring, floor, pt1, pt2, force);

      /* the force on the floor is in the direction opposite to the
       * floor normal. Transform the force from the floor frame to the
       * segment frame.
       */
      sdvmul(-1.0, force, frc2);
      sdtrans(floor.segment, force, spring->segment, frc1);

      /* apply forces to both segments and copy spring force into array */
      sdpointf(floor.segment, pt2, frc2);
      sdpointf(spring->segment, spring->point, frc1);
      sdvcopy(frc1, spring->force);

   }
}


/* Calculate the spring force based on the contact model presented in
 * Neptune, R.R., Wright, I.C., Bogert, A.J. van den (2000).  A method
 * for numerical simulation of single limb ground contact events: application
 * to heel-toe running.  Journal of Computer Methods in Biomechanics and
 * Biomechanical Engineering 3(4): 321-334.
 */
static void calculate_spring_force(dpSpringStruct spring, dpSpringFloor floor, 
                                   double pt1[], double pt2[], double force[])
{
   int velocity_dir, penetration;
   double coef_a, coef_b, coef_c, coef_d, coef_e, coef_f;
   double depth, p2p1[3], norm[3];
   double vel1[3], vel2[3], rel_vel[3];
   double normal_vel[3], tang_vel[3], norm_vel_mag;
   double normal_force_mag, tang_vel_mag, friction_factor1, friction_factor2;
   double normal_force[3], tangential_force[3];
   double viscous_damping_coef = 3000.0;

   coef_a = spring.param_a; /* coef. for velocity independent term */
   coef_b = spring.param_b; /* power on displacement in vel. indep. term */
   coef_c = spring.param_c; /* coef. for velocity dependent term */
   coef_d = spring.param_d; /* power on displacement in vel. dependent term */
   coef_e = spring.param_e; /* power on velocity in vel. dependent term */
   coef_f = spring.param_f; /* area normalization term (approx area associated
                             * with ground contact point div. by 32.2 cm^2 */
   norm[0] = floor.plane.a;
   norm[1] = floor.plane.b;
   norm[2] = floor.plane.c;

   /* pt1 on spring, pt2 on floor, both in floor frame */
   /* find the vector from pt2 to pt1 (along the plane normal).
    * Find the length of the vector (depth of penetration) and its
    * direction (-1 : pt is below plane, 1 : pt is above plane.
    */
   sdvsub(pt1, pt2, p2p1);
   penetration = (int)SIGN(DOT_VECTORS(p2p1, norm));
   depth = VECTOR_MAGNITUDE(p2p1);

   /* find relative velocity of pt1 wrt pt2 and convert to plane frame */
	sdvel(spring.segment, spring.point, vel1);
	sdvel(floor.segment, pt2, vel2);
	sdvsub(vel1, vel2, rel_vel);
   sdtrans(GROUND, rel_vel, floor.segment, rel_vel);

   /* find normal and tangential relative velocities */
   sdvmul(DOT_VECTORS(rel_vel, norm), norm, normal_vel);
   sdvsub(rel_vel, normal_vel, tang_vel);
   norm_vel_mag = VECTOR_MAGNITUDE(normal_vel);
   tang_vel_mag = VECTOR_MAGNITUDE(tang_vel);

   /* find the direction of the normal relative velocity
    * -1 : point is moving into the plane, 1 : point is moving away from
    * the plane
    */
   velocity_dir = (int)SIGN(DOT_VECTORS(rel_vel, norm));

   force[0] = force[1] = force[2] = 0.0;

   /* calculate the spring force if the spring point has penetrated the plane */
   if (penetration == -1)
   {
      normal_force_mag = coef_f * 
         (coef_a * pow(depth, coef_b) +
         velocity_dir * coef_c * pow(depth, coef_d) * pow(norm_vel_mag, coef_e));

      /* if the force is not pulling on the objects, calculate friction force */
      if (normal_force_mag > 0.0)
      {
         sdvmul(normal_force_mag, norm, normal_force);
         friction_factor1 = viscous_damping_coef * tang_vel_mag * coef_f;
         friction_factor2 = spring.friction * normal_force_mag;
         if (friction_factor1 > friction_factor2)
            friction_factor1 = friction_factor2;
         if (tang_vel_mag < 0.0000001)
            friction_factor1 = 0.0;
         else 
            friction_factor1 = -1.0 * friction_factor1 / tang_vel_mag;

         sdvmul(friction_factor1, tang_vel, tangential_force);
         sdvadd(tangential_force, normal_force, force);
      }
   }
}


/* given a spring_floor name, return the index of the floor in the array,
 * or -1 if it is not in the array
 */
static int enter_spring_floor(char name[])
{
   int i;

	for (i = 0; i < sdm->num_spring_floors; i++)
		if (STRINGS_ARE_EQUAL(name, sdm->spring_floor[i].name))
			return i;

   /* if name is not found in list, return -1 */
   return -1;
}


/* display info about spring components */
void show_spring_info(void)
{
   int i, spring_seg, floor_num, floor_seg;

   for (i = 0; i < sdm->num_spring_floors; i++)
   {
      sim_message(none, "floor %s:", sdm->spring_floor[i].name);
      sim_message(none, "\ton segment %d (%s)", sdm->spring_floor[i].segment,
         sdm->body_segment[sdm->spring_floor[i].segment + 1].name);
      sim_message(none, "\tPlane a: %f  b: %f  c: %f  d: %f", sdm->spring_floor[i].plane.a,
         sdm->spring_floor[i].plane.b, sdm->spring_floor[i].plane.c, 
         sdm->spring_floor[i].plane.d);
   }
   for (i = 0; i < sdm->num_springs; i++)
   {
      spring_seg = sdm->spring[i].segment;
      floor_num = sdm->spring[i].floor;
      floor_seg = sdm->spring_floor[floor_num].segment;
      sim_message(none, "spring%d:", i);
      sim_message(none, "\tattached to segment %d (%s)", spring_seg, 
         sdm->body_segment[spring_seg + 1].name);
      if (floor_num < 0)
         sim_message(none, "\t  and floor %s (not defined)", sdm->spring[i].floor_name);
      else
      {
         sim_message(none, "\t  and floor %d (%s) on segment %d (%s)", floor_num, sdm->spring[i].floor_name,
            floor_seg, sdm->body_segment[floor_seg + 1].name);
      }
      sim_message(none, "\tspring point: %f %f %f", sdm->spring[i].point[0],
         sdm->spring[i].point[1], sdm->spring[i].point[2]);
      sim_message(none, "\tparams:");
      sim_message(none, "\tfriction = %f", sdm->spring[i].friction);
      sim_message(none, "\ta = %f", sdm->spring[i].param_a);
      sim_message(none, "\tb = %f", sdm->spring[i].param_b);
      sim_message(none, "\tc = %f", sdm->spring[i].param_c);
      sim_message(none, "\td = %f", sdm->spring[i].param_d);
      sim_message(none, "\te = %f", sdm->spring[i].param_e);
      sim_message(none, "\tf = %f", sdm->spring[i].param_f);
   }
}

