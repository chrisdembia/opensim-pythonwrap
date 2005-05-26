/*******************************************************************************

	CONSTRAINT.C

   Authors: Krystyne Blaikie
            Peter Loan

   Copyright (c) 2002-4 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains the main functions for solving constraint
      objects and points.

*******************************************************************************/

#include <universal.h>

/*************** DEFINES (for this file only) *********************************/

/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;								/* defined in sdfor.c */

typedef struct
{
   double p2[3];
   double v2[3];
   double a2[3];
   double p1[3];
   double v1[3];
   double a1[3];
   double a;
   double b;
   double c;
   double U;
   double V;
   double Udot;
   double Vdot;
   double Tu[3];
   double Tv[3];
   double Tudot[3];
   double Tvdot[3];
   double Tudotdot[3];
   double Tvdotdot[3];
   double n[3];
   double ndot[3];
   double ndotdot[3];
   int status;
   dpBoolean reparameterized;
} ellDataStruct;
/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/

/***************** GLOBAL FUNCTION PROTOTYPES *********************************/
void CalculateResids(int numResid, int numVar, double vars[], double resids[], int *flag, 
                       void *data);
int LMsolve(ellDataStruct *solveInfo, int numVars, int numResid, double vars[], double resid[]);

/***************** STATIC FUNCTION PROTOTYPES *********************************/
static void calculatePlaneErrors(int status, double normal[], 
                                 double p0[], double p1[], double p2[], 
                                 double v0[], double v1[], double v2[],
                                 double a0[], double a1[], double a2[],
                                 double *pe, double *ve, double *ae);
static void calculateSphereErrors(int status, double r, double p1[], double p2[],
                                  double v1[], double v2[], double a1[], double a2[], 
                                  double *pe, double *ve, double *ae);
static void calculateEllipsoidErrors(int status, double r[], double p1[], double p2[],
                                     double v1[], double v2[], double a1[], double a2[], 
                                     double *pe, double *ve, double *ae);
static void calculateCylinderErrors(int status, double r, double p1[], double p2[],
                                    double v1[], double v2[], double a1[], double a2[],
                                    double *pe, double *ve, double *ae);
static void convert_point_to_constraint_object_frame(dpConstraintObject* co, double* in, double* out);
static void convert_point_from_constraint_object_frame(dpConstraintObject* co, double* in, double* out);
static void convert_vec_to_constraint_object_frame(dpConstraintObject* co, double* in, double* out);
static void convert_vec_from_constraint_object_frame(dpConstraintObject* co, double* in, double* out);


/* calculate the position error for the given point on the given constraint object */
double calculate_constraint_position_error(dpConstraintObject *co, int status, int point)
{
   int j;
   int constraint_axis, constraint_sign, pt_segment, co_segment;
   double pt_ground[3], pt_coframe[3], pt_cosegframe[3];
   double projpt_ground[3], projpt_coframe[3], projpt_cosegframe[3];
   double norm_ground[3], norm_coframe[3], norm_cosegframe[3];
   double origin[] = {0.0, 0.0, 0.0};
   double perr, junk, junk_vec[3], p1[3], p2[3];            

   constraint_axis = co->constraint_axis;
   constraint_sign = co->constraint_sign;
   co_segment = co->segment;
   
   j = point;
   pt_segment = co->points[j].segment;
   
   /* convert point to ground frame */
   sdpos(pt_segment, co->points[j].offset, pt_ground);
   /* convert point to constraint object segment frame */
   convert_point2(GROUND, pt_ground, co_segment, pt_cosegframe);
   /* convert point to constraint object frame from constraint segment frame */
   convert_point_to_constraint_object_frame(co, pt_cosegframe, pt_coframe);
   /* determine projected point, normal vector, in constraint object frame */
   determine_projected_point(co, pt_coframe, projpt_coframe, norm_coframe);
   /* determine projected point in ground and constraint object segment frame */
   convert_point_from_constraint_object_frame(co, projpt_coframe, projpt_cosegframe);
   sdpos(co_segment, projpt_cosegframe, projpt_ground);

   /* determine normal vector in the ground frame, and constraint object segment frame */
   convert_vec_from_constraint_object_frame(co, norm_coframe, norm_cosegframe);
   normalize_vector(norm_cosegframe, norm_cosegframe);
   sdtrans(co_segment, norm_cosegframe, GROUND, norm_ground);
   normalize_vector(norm_ground, norm_ground);
   
   /* calculate position error */
   /* P1 on body1, P2 on body2 - in constraint object frame */
   sdvcopy(projpt_coframe, p1);
   sdvcopy(pt_coframe, p2);
   
   if (co->constraint_type == dpConstraintPlane)
   {
      sdvmul(-1.0 * co->plane.d, norm_ground, origin);
      sdpos(pt_segment, co->points[j].offset, pt_ground);
      sdpos(co_segment, projpt_cosegframe, projpt_ground);
      
      calculatePlaneErrors(PERR, norm_coframe, origin, p1, p2, 
         junk_vec, junk_vec, junk_vec, junk_vec, junk_vec, junk_vec, &perr, &junk, &junk);
   }
   else if (co->constraint_type == dpConstraintEllipsoid)
   {
   /* pass in the position of the point on the constraint object and 
      * the constraint point in the constraint object frame */
      calculateEllipsoidErrors(PERR, co->co_radius, p1, p2,
         junk_vec, junk_vec, junk_vec, junk_vec, &perr, &junk, &junk);
   }
   else if (co->constraint_type == dpConstraintSphere)
   {
      double sphere_radius = co->co_radius[0];
      
      /* pass in the position of the point on the constraint object and 
      * the constraint point in the constraint object frame */
      calculateSphereErrors(PERR, sphere_radius, p1, p2,
         junk_vec, junk_vec, junk_vec, junk_vec, &perr, &junk, &junk);
   }
   else if (co->constraint_type == dpConstraintCylinder)
   {
      double cyl_radius = co->co_radius[0];
      
      calculateCylinderErrors(PERR, cyl_radius, p1, p2, 
         junk_vec, junk_vec, junk_vec, junk_vec, &perr, &junk, &junk);
   }
   return perr;
}  

/* calculate the velocity error for the given point on the given constraint object */
double calculate_constraint_velocity_error(dpConstraintObject *co, int point)
{
   int j, constraint_axis, constraint_sign, pt_segment, co_segment;
   double pt_ground[3], pt_coframe[3], pt_cosegframe[3];
   double projpt_ground[3], projpt_coframe[3], projpt_cosegframe[3];
   double norm_ground[3], norm_coframe[3], norm_cosegframe[3];
   double origin_coframe[] = {0.0, 0.0, 0.0}, origin_cosegframe[3], origin_ground[3];
   double vel[3], projpt_vel[3], orig_vel[3];
   double verr, junk, junk_vec[3], p1[3], p2[3], v1[3], v2[3];            
   double w[3], r[3], wxr[3];
  
   constraint_axis = co->constraint_axis;
   constraint_sign = co->constraint_sign;
   co_segment = co->segment;
   
   j = point;
   pt_segment = co->points[j].segment;
   
   /* convert point to ground frame */
   sdpos(pt_segment, co->points[j].offset, pt_ground);
   
   /* convert point to constraint object segment frame */
   convert_point2(GROUND, pt_ground, co_segment, pt_cosegframe);
   
   /* convert point to constraint object frame */
   convert_point_to_constraint_object_frame(co, pt_cosegframe, pt_coframe);
   
   /* determine projected point, normal vector, in constraint object frame */
   determine_projected_point(co, pt_coframe, projpt_coframe, norm_coframe);
   
   /* determine projected point in ground and constraint object segment frame */
   convert_point_from_constraint_object_frame(co, projpt_coframe, projpt_cosegframe);
   sdpos(co_segment, projpt_cosegframe, projpt_ground);
   
   /* determine normal vector in the ground frame, and constraint object segment frame */
   convert_vec_from_constraint_object_frame(co, norm_coframe, norm_cosegframe);
   normalize_vector(norm_cosegframe, norm_cosegframe);
   sdtrans(co_segment, norm_cosegframe, GROUND, norm_ground);
   normalize_vector(norm_ground, norm_ground);
   
   convert_point_from_constraint_object_frame(co, origin_coframe, origin_cosegframe);
   
   /*determine velocities of points */
   sdvel(pt_segment, co->points[j].offset, vel);
   sdvel(co_segment, projpt_cosegframe, projpt_vel);
   sdvel(co_segment, origin_cosegframe, orig_vel);
   
   /* calculate velocity error */
   /* P1 on body1, P2 on body2 - in constraint object frame */
   sdvcopy(projpt_coframe, p1);
   sdvcopy(pt_coframe, p2);
   
   sdvcopy(projpt_vel, v1);
   /* determine the velocity of p2 wrt. the constraint object origin 
    * v2 = velocity of p2(wrt ground) - velocity of co origin (wrt ground) - wxr */
   sdvsub(vel, orig_vel, v2);
  
   sdpos(co_segment, origin_cosegframe, origin_ground);
   sdvsub(pt_ground, origin_ground, r);
   sdangvel(co_segment, w);
   sdtrans(co_segment, w, GROUND, w);
   sdvcross(w, r, wxr);
   sdvsub(v2, wxr, v2);
   
   
   /* convert the velocities to the constraint object frame */
   sdtrans(GROUND, v1, co_segment, v1);
   convert_vec_to_constraint_object_frame(co, v1, v1);
   sdtrans(GROUND, v2, co_segment, v2);
   convert_vec_to_constraint_object_frame(co, v2, v2);
   
   if (co->constraint_type == dpConstraintPlane)
   { 
      sdtrans(GROUND, orig_vel, co_segment, orig_vel);
      convert_vec_to_constraint_object_frame(co, orig_vel, orig_vel);
      calculatePlaneErrors(VERR, norm_coframe, origin_coframe, p1, p2, orig_vel, v1, v2,
         junk_vec, junk_vec, junk_vec, &junk, &verr, &junk);
   }
   else if (co->constraint_type == dpConstraintEllipsoid)
   {
      calculateEllipsoidErrors(VERR, co->co_radius, p1, p2,
         v1, v2, junk_vec, junk_vec, &junk, &verr, &junk);
   }
   else if (co->constraint_type == dpConstraintSphere)
   {
      double sphere_radius = co->co_radius[0];
      calculateSphereErrors(VERR, sphere_radius, p1, p2, v1, v2,
         junk_vec, junk_vec, &junk, &verr, &junk);
   }
   else if (co->constraint_type == dpConstraintCylinder)
   {
      double cyl_radius = co->co_radius[0];
      calculateCylinderErrors(VERR, cyl_radius, p1, p2, 
         v1, v2, junk_vec, junk_vec, &junk, &verr, &junk);
   }
   return verr;
}

/* calculate the acceleration error of the given point on the given constraint object */
double calculate_constraint_acceleration_error(dpConstraintObject *co, int point)
{
   int j, constraint_axis, constraint_sign, pt_segment, co_segment;
   double pt_ground[3], pt_coframe[3], pt_cosegframe[3];
   double projpt_ground[3], projpt_coframe[3], projpt_cosegframe[3];
   double norm_ground[3], norm_coframe[3], norm_cosegframe[3];
   double origin_coframe[] = {0.0, 0.0, 0.0}, origin_cosegframe[3], origin_ground[3];
   double vel[3], projpt_vel[3], orig_vel[3];
   double aerr, junk, p1[3], p2[3], v1[3], v2[3], a1[3], a2[3]; 
   double acc[3], projpt_acc[3], orig_acc[3];
   double w[3], r[3], wxr[3];
   double alpha[3], axr[3], wxwxr[3], vxr[3];
   
   constraint_axis = co->constraint_axis;
   constraint_sign = co->constraint_sign;
   co_segment = co->segment;
   
   j = point;
   pt_segment = co->points[j].segment;
   
   /* convert point to ground frame */
   sdpos(pt_segment, co->points[j].offset, pt_ground);
   
   /* convert point to constraint object segment frame */
   convert_point2(GROUND, pt_ground, co_segment, pt_cosegframe);
   
   /* convert point to constraint object frame */
   convert_point_to_constraint_object_frame(co, pt_cosegframe, pt_coframe);
   
   /* determine projected point, normal vector, in constraint object frame */
   determine_projected_point(co, pt_coframe, projpt_coframe, norm_coframe);
   
   /* determine projected point in ground and constraint object segment frame */
   convert_point_from_constraint_object_frame(co, projpt_coframe, projpt_cosegframe);
   sdpos(co_segment, projpt_cosegframe, projpt_ground);
   
   /* determine normal vector in the ground frame, and constraint object segment frame */
   convert_vec_from_constraint_object_frame(co, norm_coframe, norm_cosegframe);
   normalize_vector(norm_cosegframe, norm_cosegframe);
   sdtrans(co_segment, norm_cosegframe, GROUND, norm_ground);
   normalize_vector(norm_ground, norm_ground);
   
   convert_point_from_constraint_object_frame(co, origin_coframe, origin_cosegframe);
   
   /* determine velocities of points wrt ground */
   sdvel(pt_segment, co->points[j].offset, vel);
   sdvel(co_segment, projpt_cosegframe, projpt_vel);
   sdvel(co_segment, origin_cosegframe, orig_vel);
   
   /* determine accelerations of points wrt ground */
   sdacc(pt_segment, co->points[j].offset, acc);
   sdacc(co_segment, projpt_cosegframe, projpt_acc);
   sdacc(co_segment, origin_cosegframe, orig_acc);         
   
   /* calculate acceleration error */
   /* P1 on body1, P2 on body2 - in constraint object frame */
   sdvcopy(projpt_coframe, p1);
   sdvcopy(pt_coframe, p2);
   
   /* determine velocities wrt. constraint object origin */
   /* the velocity of p2 wrt. the constraint object origin 
    * v2 = velocity of p2(wrt ground) - velocity of co origin (wrt ground) - wxr */
   sdvcopy(projpt_vel, v1);
   sdvsub(vel, orig_vel, v2);
   
   /* determine accelerations wrt constraint object origin */
   /* the acceleration of p2 wrt. the constraint object origin 
    * a2 = acc of p2(wrt ground) - acc of co origin (wrt ground) - wxwxr -alphaxr + 2vxr */
   sdvcopy(projpt_acc, a1);
   sdvsub(acc, orig_acc, a2);
   
      sdangvel(co_segment, w);
      sdtrans(co_segment, w, GROUND, w);
      sdangacc(co_segment, alpha);
      sdtrans(co_segment, alpha, GROUND, alpha);
      
      sdpos(co_segment, origin_cosegframe, origin_ground);
      sdvsub(pt_ground, origin_ground, r);
      
      sdvcross(w, r, wxr);
      sdvsub(v2, wxr, v2);
      
      sdvcross(w, wxr, wxwxr);
      sdvcross(alpha, r, axr);
      sdvcross(v2, w, vxr);
      sdvsub(a2, wxwxr, a2);
      sdvsub(a2, axr, a2);
      sdvadd(a2, vxr, a2);
      sdvadd(a2, vxr, a2);
   
   /* convert to constraint object frame */
   sdtrans(GROUND, v1, co_segment, v1);
   convert_vec_to_constraint_object_frame(co, v1, v1);
   sdtrans(GROUND, a1, co_segment, a1);
   convert_vec_to_constraint_object_frame(co, a1, a1);
   sdtrans(GROUND, v2, co_segment, v2);
   convert_vec_to_constraint_object_frame(co, v2, v2);
   sdtrans(GROUND, a2, co_segment, a2);
   convert_vec_to_constraint_object_frame(co, a2, a2);
   
   if (co->constraint_type == dpConstraintPlane)
   {
      sdtrans(GROUND, orig_vel, co_segment, orig_vel);
      convert_vec_to_constraint_object_frame(co, orig_vel, orig_vel);
      sdtrans(GROUND, orig_acc, co_segment, orig_acc);
      convert_vec_to_constraint_object_frame(co, orig_acc, orig_acc);
      calculatePlaneErrors(AERR, norm_coframe, origin_coframe, p1, p2,
         orig_vel, v1, v2, orig_acc, a1, a2, &junk,
         &junk, &aerr);
   }
   else if (co->constraint_type == dpConstraintEllipsoid)
   {
      calculateEllipsoidErrors(AERR, co->co_radius, p1, p2, v1, v2, a1, a2,
         &junk, &junk, &aerr);
   }
   else if (co->constraint_type == dpConstraintSphere)
   {
      double sphere_radius = co->co_radius[0];
      calculateSphereErrors(AERR, sphere_radius, p1, p2, v1, v2, a1, a2, 
         &junk, &junk, &aerr);
   }
   else if (co->constraint_type == dpConstraintCylinder)
   {
      double cyl_radius = co->co_radius[0];
      calculateCylinderErrors(AERR, cyl_radius, p1, p2, v1, v2, a1, a2,
         &junk, &junk, &aerr);
   }
   return aerr;
}

/* apply the constraint forces to the given point on the given constraint object */
void apply_constraint_forces(dpConstraintObject *co, double multiplier, int j)
{
   int pt_segment, co_segment;
   double frc[3], projpt_frc[3];
   double pt_ground[3], pt_cosegframe[3], pt_coframe[3];
   double projpt_ground[3], projpt_cosegframe[3], projpt_coframe[3];
   double norm_ground[3], norm_cosegframe[3], norm_coframe[3];

   pt_segment = co->points[j].segment;
   co_segment = co->segment;
   
   /* convert point to ground frame */
   sdpos(pt_segment, co->points[j].offset, pt_ground);
   
   /* convert point to constraint object segment frame */
   convert_point2(GROUND, pt_ground, co_segment, pt_cosegframe);
   
   /* convert point to constraint object frame */
   convert_point_to_constraint_object_frame(co, pt_cosegframe, pt_coframe);
   
   /* determine projected point, normal vector, in constraint object frame */
   determine_projected_point(co, pt_coframe, projpt_coframe, norm_coframe);

   /* determine projected point in ground and constraint object segment frame */
   convert_point_from_constraint_object_frame(co, projpt_coframe, projpt_cosegframe);
   sdpos(co_segment, projpt_cosegframe, projpt_ground);
   
   /* determine normal vector in the ground frame, and constraint object segment frame */
   convert_vec_from_constraint_object_frame(co, norm_coframe, norm_cosegframe);
   normalize_vector(norm_cosegframe, norm_cosegframe);
   sdtrans(co_segment, norm_cosegframe, GROUND, norm_ground);
   normalize_vector(norm_ground, norm_ground);
   
   /* determine and apply forces */         
   sdvmul(multiplier, norm_ground, frc);
   sdtrans(GROUND, frc, pt_segment, frc);
   sdpointf(pt_segment, co->points[j].offset, frc);
   
   sdvmul(-1.0, frc, projpt_frc);
   sdtrans(pt_segment, projpt_frc, co_segment, projpt_frc);
   sdpointf(co_segment, projpt_cosegframe, projpt_frc);
}

/* calculate perr, verr, and aerr for a plane
 * all values given in constraint object frame */
static void calculatePlaneErrors(int status, double normal[], 
                                 double p0[], double p1[], double p2[], 
                          double v0[], double v1[], double v2[],
                          double a0[], double a1[], double a2[],
                          double *pe, double *ve, double *ae)
{
   double perr, verr, aerr;
   double temp[] = {1.0, 0.0, 0.0}, n[3], tu[3], tv[3];

   /* determine tangential vectors */
   sdvcross(normal, temp, tu);
   if (VECTOR_MAGNITUDE(tu) == 0.0)
   {
      /* if normal == 1 0 0 try tu = normal X 0 1 0 */
      temp[0] = 0.0;
      temp[1] = 1.0;
      sdvcross(normal, temp, tu);
   }
   sdvcross(normal, tu, tv);
   sdvcross(tv, normal, tu);
   sdvcross(tu, tv, n);

   normalize_vector(tu, tu);
   normalize_vector(tv, tv);
   normalize_vector(n, n);
   
   /********************* Perr **********************/
   perr = DOT_VECTORS(p2, n);

   *pe = perr;
   if (status == PERR)
      return;
   /************************** Verr **************************/
   verr = DOT_VECTORS(v2, n);

   *ve = verr;
   if (status == VERR)
      return;

   /************************** Aerr ****************************************/
   aerr = DOT_VECTORS(a2, n);

   *ae = aerr;
}


/* calculate Perr, Verr and Aerr, for sphere constraint object
 * All values given in the constraint object frame
 */
static void calculateSphereErrors(int status, double r, double p1[], double p2[],
                                  double v1[], double v2[], double a1[], double a2[], 
                           double *pe, double *ve, double *ae)
{
   double U, V, Udot, Vdot, Udotdot, Vdotdot, cosU, cosV, sinU, sinV;
   double p2x, p2y, p2z, v2x, v2y, v2z, a2x, a2y, a2z;
   double perr, verr, aerr, num, den;
   dpBoolean reparameterized = dpNo;

   p2x = p2[0]; p2y = p2[1]; p2z = p2[2];
   v2x = v2[0]; v2y = v2[1]; v2z = v2[2];
   a2x = a2[0]; a2y = a2[1]; a2z = a2[2];

   /********************* Perr **********************/
   /* Solve for V:
    * (P2 - P1) dot Tv = 0
    * -P2x * sinV + P2y * cosV = 0
    */
   V = atan2(p2y, p2x);

   /* Solve for U:
    * (P2 - P1) dot Tu = 0
    * P2x * cosU * cosV + P2y * cosU * sinV - P2z * sinU = 0
    */
   U = atan2((p2x * cos(V) + p2y * sin(V)), p2z);

   while (U < 0.0)
      U = DEG2RAD(360.0) + U;
   while (V < 0.0)
      V = DEG2RAD(360.0) + V;

   /* If the denominator in the velocity term is too small,
    * reparameterize so it is bigger.
    */
   if ((p2x * cos(V) + p2y * sin(V)) < 0.001)
   {
      V = atan2(p2x, p2z);
      U = atan2((p2z * cos(V) + p2x * sin(V)), p2y);
      while (U < 0.0)
         U = DEG2RAD(360.0) + U;
      while (V < 0.0)
         V = DEG2RAD(360.0) + V;

      reparameterized = dpYes;
   }

   cosU = cos(U);
   cosV = cos(V);
   sinU = sin(U);
   sinV = sin(V);

   /* Perr = P2xsinUcosV + P2y sinUsinV + P2zcosU - r */
   if (reparameterized == dpYes)
      perr = p2z * sinU * cosV + p2x * sinU * sinV + p2y * cosU - r;
   else
      perr = p2x * sinU * cosV + p2y * sinU * sinV + p2z * cosU - r;

   *pe = perr;

   if (status == PERR)
      return;

   /************************** Verr **************************/
   /* Solve for Vdot:
    * -V2x * sinV + V2y * cosV - Vdot * (P2x * cosV + P2y * sinV)  = 0
    */
   if (reparameterized == dpYes)
   {
      Vdot = (-v2z * sinV + v2x * cosV) / (p2z * cosV + p2x * sinV);

      /* Solve for Udot:
       * Udot * (-p2xsinUcosV - p2ysinUsinV - p2zcosU) +
       *     Vdot * (-p2xcosUsinV + p2ycosUcosV)  + v2xcosUcosv + v2ycosUsinV - V2zsinU = 0
       */
      num = v2z * cosU * cosV + v2x * cosU * sinV - v2y * sinU;
      num += Vdot * (-1 * p2z * cosU * sinV + p2x * cosU * cosV);
      den = p2z * sinU * cosV + p2x * sinU * sinV + p2y * cosU;
      Udot = num / den;

      /* Verr = V2x * sinU * cosV + V2y * sinU * sinV + V2z * cosU
       *        + Udot * (P2x * cosU * cosV + P2y * cosU * sinV - P2z * sinU)
       *        + Vdot * (-P2x* sinU * sinV + P2y * sinU * cosV)
       */
      verr = v2z * sinU * cosV + v2x * sinU * sinV + v2y * cosU
           + Udot * (p2z * cosU * cosV + p2x * cosU * sinV - p2y * sinU)
           + Vdot * (-1 * p2z * sinU * sinV + p2x * sinU * cosV);
   }
   else
   {
      Vdot = (-v2x * sinV + v2y * cosV) / (p2x * cosV + p2y * sinV);

      /* Solve for Udot:
       * Udot * (-p2xsinUcosV - p2ysinUsinV - p2zcosU) +
       *     Vdot * (-p2xcosUsinV + p2ycosUcosV)  + v2xcosUcosv + v2ycosUsinV - V2zsinU = 0
       */
      num = v2x * cosU * cosV + v2y * cosU * sinV - v2z * sinU;
      num += Vdot * (-1 * p2x * cosU * sinV + p2y * cosU * cosV);
      den = p2x * sinU * cosV + p2y * sinU * sinV + p2z * cosU;
      Udot = num / den;

      /* Verr = V2x * sinU * cosV + V2y * sinU * sinV + V2z * cosU
       *        + Udot * (P2x * cosU * cosV + P2y * cosU * sinV - P2z * sinU)
       *        + Vdot * (-P2x* sinU * sinV + P2y * sinU * cosV)
       */
      verr = v2x * sinU * cosV + v2y * sinU * sinV + v2z * cosU
           + Udot * (p2x * cosU * cosV + p2y * cosU * sinV - p2z * sinU)
           + Vdot * (-1 * p2x * sinU * sinV + p2y * sinU * cosV);
   }

   *ve = verr;

   if (status == VERR)
      return;

   /************************** Aerr ****************************************/
   /* Solve for Vdotdot
    * -A2xsinV + A2ycosV - Vdotdot(P2xcosV + P2y sinV) 
            - 2 Vdot * (V2xcosV + V2ysinV) - Vdot ^2 * (-P2xsinV + P2y cosV) = 0
    */
   if (reparameterized == dpYes)
   {
      num = -a2z * sinV + a2x * cosV;
      num += -2.0 * Vdot * (v2z * cosV + v2x * sinV);
      num += -1.0 * Vdot * Vdot * (-1.0 * p2z * sinV + p2x * cosV);
      den = p2z * cosV + p2x * sinV;
      Vdotdot = num / den;

      /* Solve for Udotdot:
       * A2x cosUcosV + A2ycosUsinV - A2zsinU 
       *   - 2Udot(V2xsinUcosV + V2ysinUsinV + V2zcosU) + 2Vdot(-V2xcosUsinV + V2ycosUcosV)
       *   - Udotdot (P2xsinUcosV + P2ysinUsinV + P2zcosU)
       *   + Vdotdot (-P2xcosUsinV + P2ycosUcosV) 
       *   - Udot^2(P2xcosUcosV + P2ycosUsinV - P2zsinU)
       *   - Vdot^2(P2xcosUcosV + P2ycosUsinV) 
       *   - 2UdotVdot(-P2xsinUsinV + P2ysinUcosV)
       */
      num = a2z * cosU * cosV + a2x * cosU * sinV - a2y * sinU;
      num += -2 * Udot * (v2z * sinU * cosV + v2x * sinU * sinV + v2y * cosU);
      num += 2 * Vdot * (-1 * v2z * cosU * sinV + v2x * cosU * cosV);
      num += Vdotdot * (-1 * p2z * cosU * sinV + p2x * cosU * cosV);
      num += -1 * Udot * Udot * (p2z * cosU * cosV + p2x * cosU * sinV - p2y * sinU);
      num += -1 * Vdot * Vdot * (p2z * cosU * cosV + p2x * cosU * sinV);
      num += -2 * Udot * Vdot * (-1 * p2z * sinU * sinV + p2x * sinU * cosV);
      den = p2z * sinU * cosV + p2x * sinU * sinV + p2y * cosU;
      Udotdot = num / den;
   
      /* Aerr = A2xsinUcosV + a2ysinUsinV + A2zcosU
       *       + 2Udot(V2xcosUcosV + V2ycosUsinV - V2zsinU
       *       + 2Vdot(-V2xsinUsinV + V2ysinUcosV)
       *       - Udot^2(P2xsinUcosV + P2ysinUsinV + P2zcosU)
       *       - Vdot^2(P2xsinUcosV + P2ysinUsinV)
       *       + 2UdotVdot(-P2xcosUsinV + P2ycosUcosV)
       *       + Udotdot(P2xcosUcosV + P2ycosUsinV - P2z sinU)
       *       + Vdotdot(-P2xsinUsinV + P2ysinUcosV)
       */
      aerr = a2z * sinU * cosV + a2x * sinU * sinV + a2y * cosU;
      aerr += 2 * Udot * (v2z * cosU * cosV + v2x * cosU * sinV - v2y * sinU);
      aerr += 2 * Vdot * (-v2z * sinU * sinV + v2x * sinU * cosV);
      aerr += -1 * Udot * Udot * (p2z * sinU * cosV + p2x * sinU * sinV + p2y * cosU);
      aerr += -1 * Vdot * Vdot * (p2z * sinU * cosV + p2x * sinU * sinV);
      aerr += 2 * Udot * Vdot * (-1 * p2z * cosU * sinV + p2x * cosU * cosV);
      aerr += Udotdot * (p2z * cosU * cosV + p2x * cosU * sinV - p2y * sinU);
      aerr += Vdotdot * (-1 * p2z * sinU * sinV + p2x * sinU * cosV);
   }
   else
   {
      num = -a2x * sinV + a2y * cosV;
      num += -2.0 * Vdot * (v2x * cosV + v2y * sinV);
      num += -1.0 * Vdot * Vdot * (-1.0 * p2x * sinV + p2y * cosV);
      den = p2x * cosV + p2y * sinV;
      Vdotdot = num / den;

      /* Solve for Udotdot:
       * A2x cosUcosV + A2ycosUsinV - A2zsinU 
       *   - 2Udot(V2xsinUcosV + V2ysinUsinV + V2zcosU) + 2Vdot(-V2xcosUsinV + V2ycosUcosV)
       *   - Udotdot (P2xsinUcosV + P2ysinUsinV + P2zcosU)
       *   + Vdotdot (-P2xcosUsinV + P2ycosUcosV) 
       *   - Udot^2(P2xcosUcosV + P2ycosUsinV - P2zsinU)
       *   - Vdot^2(P2xcosUcosV + P2ycosUsinV) 
       *   - 2UdotVdot(-P2xsinUsinV + P2ysinUcosV)
       */
      num = a2x * cosU * cosV + a2y * cosU * sinV - a2z * sinU;
      num += -2 * Udot * (v2x * sinU * cosV + v2y * sinU * sinV + v2z * cosU);
      num += 2 * Vdot * (-1 * v2x * cosU * sinV + v2y * cosU * cosV);
      num += Vdotdot * (-1 * p2x * cosU * sinV + p2y * cosU * cosV);
      num += -1 * Udot * Udot * (p2x * cosU * cosV + p2y * cosU * sinV - p2z * sinU);
      num += -1 * Vdot * Vdot * (p2x * cosU * cosV + p2y * cosU * sinV);
      num += -2 * Udot * Vdot * (-1 * p2x * sinU * sinV + p2y * sinU * cosV);
      den = p2x * sinU * cosV + p2y * sinU * sinV + p2z * cosU;
      Udotdot = num / den;
   
      /* Aerr = A2xsinUcosV + a2ysinUsinV + A2zcosU
       *       + 2Udot(V2xcosUcosV + V2ycosUsinV - V2zsinU
       *       + 2Vdot(-V2xsinUsinV + V2ysinUcosV)
       *       - Udot^2(P2xsinUcosV + P2ysinUsinV + P2zcosU)
       *       - Vdot^2(P2xsinUcosV + P2ysinUsinV)
       *       + 2UdotVdot(-P2xcosUsinV + P2ycosUcosV)
       *       + Udotdot(P2xcosUcosV + P2ycosUsinV - P2z sinU)
       *       + Vdotdot(-P2xsinUsinV + P2ysinUcosV)
       */
      aerr = a2x * sinU * cosV + a2y * sinU * sinV + a2z * cosU;
      aerr += 2 * Udot * (v2x * cosU * cosV + v2y * cosU * sinV - v2z * sinU);
      aerr += 2 * Vdot * (-v2x * sinU * sinV + v2y * sinU * cosV);
      aerr += -1 * Udot * Udot * (p2x * sinU * cosV + p2y * sinU * sinV + p2z * cosU);
      aerr += -1 * Vdot * Vdot * (p2x * sinU * cosV + p2y * sinU * sinV);
      aerr += 2 * Udot * Vdot * (-1 * p2x * cosU * sinV + p2y * cosU * cosV);
      aerr += Udotdot * (p2x * cosU * cosV + p2y * cosU * sinV - p2z * sinU);
      aerr += Vdotdot * (-1 * p2x * sinU * sinV + p2y * sinU * cosV);
   }

   *ae = aerr;

   if (status == AERR)
      return;
}

/* calculate Perr, Verr and Aerr, for ellipsoid constraint object
 * All values given in the constraint object frame
 */
static void calculateEllipsoidErrors(int status, double r[], double p1[], double p2[],
                           double v1[], double v2[], double a1[], double a2[], 
                           double *pe, double *ve, double *ae)
{
   double U, V, Udot, Vdot, Udotdot, Vdotdot, cosU, cosV, sinU, sinV;
   double a, b, c, p2x, p2y, p2z, v2x, v2y, v2z, a2x, a2y, a2z;
   double perr, verr, aerr;
   double Tu[3], Tudot[3], Tudotdot[3], Tv[3], Tvdot[3], Tvdotdot[3], n[3], ndot[3], ndotdot[3];
   ellDataStruct info;
   double *vars, *resids;
   int numVars = 2, numResids = 5;
   dpBoolean reparameterized = dpNo;

   vars = (double *)simm_malloc(numVars * sizeof(double));
   resids = (double *)simm_malloc(numResids * sizeof(double));

   a = r[0];
   b = r[1];
   c = r[2];

   p2x = p2[0]; p2y = p2[1]; p2z = p2[2];
   v2x = v2[0]; v2y = v2[1]; v2z = v2[2];
   a2x = a2[0]; a2y = a2[1]; a2z = a2[2];

   info.a = a;
   info.b = b;
   info.c = c;
   sdvset(p2x, p2y, p2z, info.p2);
   sdvset(v2x, v2y, v2z, info.v2);
   sdvset(a2x, a2y, a2z, info.a2);

   /********************* Perr **********************/
      /* assume ellipsoid is spherical to get starting values of U, V */
      vars[0] = atan2(p2y, p2x);
      vars[1] = atan2((p2x * cos(vars[0]) + p2y * sin(vars[0])), p2z);
   while (vars[0] < 0.0)
      vars[0] += DEG2RAD(360.0);
   while (vars[1] < 0.0)
      vars[1] += DEG2RAD(360.0);
   
   /* if the point is approaching the min or max along the z-axis, reparametrize */
   if ((vars[1] > DEG2RAD(150) && vars[1] < DEG2RAD(210)) || (vars[1] < DEG2RAD(30)) || (vars[1] > DEG2RAD(330)))
   {
      vars[0] = atan2(p2z, p2y);
      vars[1] = atan2((p2y * cos(vars[0]) + p2z * sin(vars[0])), p2x);
      while (vars[0] < 0.0)
         vars[0] += DEG2RAD(360.0);
      while (vars[1] < 0.0)
         vars[1] += DEG2RAD(360.0);
      reparameterized = dpYes;
   }

   info.status = PERR;
   info.reparameterized = reparameterized;
   LMsolve(&info, numVars, numResids, vars, resids);

   U = vars[0];
   V = vars[1];

   while (U < 0.0)
      U = DEG2RAD(360.0) - U;
   while (U > DEG2RAD(360.0))
      U -= DEG2RAD(360.0);

   while (V < 0.0)
      V += DEG2RAD(360.0);
   while (V > DEG2RAD(360.0))
      V -= DEG2RAD(360.0);

   info.U = U;
   info.V = V;

   cosU = cos(U);
   sinU = sin(U);
   cosV = cos(V);
   sinV = sin(V);

   sdvcopy(info.p1, p1);
   sdvcopy(info.Tu, Tu);
   sdvcopy(info.Tv, Tv);
   sdvcopy(info.n, n);

   perr = DOT_VECTORS(p2, n) - DOT_VECTORS(p1, n);

   *pe = perr;

   if (status == PERR)
   {
      free(vars);
      free(resids);
      return;
   }
   /************************** Verr **************************/

   /* solve for Udot and Vdot */
   vars[0] = 0.0;
   vars[1] = 0.0;
   info.status = VERR;
   LMsolve(&info, numVars, numResids, vars, resids);
   Udot = vars[0];
   Vdot = vars[1];
   info.Udot = Udot;
   info.Vdot = Vdot;
   sdvcopy(info.v1, v1);
   sdvcopy(info.Tudot, Tudot);
   sdvcopy(info.Tvdot, Tvdot);
   sdvcopy(info.ndot, ndot);

   verr = DOT_VECTORS(v2, n) - DOT_VECTORS(v1, n);
   verr += DOT_VECTORS(p2, ndot) - DOT_VECTORS(p1, ndot);

   *ve = verr;
   
   if (status == VERR)
   {
      free(vars);
      free(resids);
      return;
   }
   /************************** Aerr ****************************************/
   /* solve for Udot and Vdot */
   vars[0] = 0.0;
   vars[1] = 0.0;
   info.status = AERR;

   LMsolve(&info, numVars, numResids, vars, resids);

   Udotdot = vars[0];
   Vdotdot = vars[1];
   sdvcopy(info.a1, a1);
   sdvcopy(info.Tudotdot, Tudotdot);
   sdvcopy(info.Tvdotdot, Tvdotdot);
   sdvcopy(info.ndotdot, ndotdot);

   /* Aerr = (A2 - A1) dot N + 2 * (V2 - V1) dot Ndot + (P2 - P1) dot Ndotdot */
   aerr = DOT_VECTORS(a2, n) - DOT_VECTORS(a1, n);
   aerr += 2.0 * (DOT_VECTORS(v2, ndot) - DOT_VECTORS(v1, ndot));
   aerr += DOT_VECTORS(p2, ndotdot) - DOT_VECTORS(p1, ndotdot);

   *ae = aerr;
   if (status == AERR)
   {
      free(vars);
      free(resids);
      return;
   }
}


/* calculate cylinder perr, verr and aerr 
 * all vectors in constraint object frame */
void calculateCylinderErrors(int status, double r, double p1[], double p2[],
                             double v1[], double v2[], double a1[], double a2[],
                             double *pe, double *ve, double *ae)
{
   double V, Vdot, Vdotdot, cosV, sinV;
   double perr, verr, aerr;
   double p2x, p2y, p2z, v2x, v2y, v2z, a2x, a2y, a2z;

   p2x = p2[0]; p2y = p2[1]; p2z = p2[2];
   v2x = v2[0]; v2y = v2[1]; v2z = v2[2];
   a2x = a2[0]; a2y = a2[1]; a2z = a2[2];

   /********************* Perr **********************/
   /* Solve for theta:
    * (P2 - P1) dot Tv = 0
    * P2x * sinV - P2y * cosV = 0
    */
   V = atan2(p2y, p2x);

   cosV = cos(V);
   sinV = sin(V);

   /* Perr = P2x cosV + P2y sinV - r */
   perr = p2x * cosV + p2y * sinV - r;
   *pe = perr;

   if (status == PERR)
      return;
   /************************** Verr **************************/
   /* Solve for Vdot:
    * V2x * sinV - V2y * cosV + Vdot * (P2x * cosV + P2y * sinV)  = 0
    */
   Vdot = (-v2x * sinV + v2y * cosV) / (p2x * cosV + p2y * sinV);

   /* Verr = V2x * cosV + V2y * sinV
    *        - Vdot * (P2x * sinV - P2y * cosV)
    */
   verr = v2x * cosV + v2y * sinV - Vdot * (p2x * sinV - p2y * cosV);
   *ve = verr;

   if (status == VERR)
      return;

   /************************** Aerr ****************************************/
   /* Solve for Vdotdot
    * -A2xsinV + A2ycosV - Vdotdot(P2xcosV + P2y sinV) 
            - 2 Vdot * (V2xcosV + V2ysinV) + Vdot ^2 * (P2xsinV - P2y cosV) = 0
    */
   Vdotdot = (-a2x * sinV + a2y * cosV - 2 * Vdot * (v2x * cosV + v2y * sinV)
      + Vdot * Vdot * (p2x * sinV - p2y * cosV)) / (p2x * cosV + p2y * sinV);
   
   /* Aerr = A2xcosV + a2ysinV - 2Vdot(V2xsinV - V2ycosV)
    *       - Vdot^2(P2xcosV + P2ysinV) - Vdotdot(P2xsinV - P2ycosV)
    */
   aerr = a2x * cosV + a2y * sinV;
   aerr += -2.0 * Vdot * (v2x * sinV - v2y * cosV);
   aerr += -1.0 * Vdot * Vdot * (p2x * cosV + p2y * sinV);
   aerr += -1.0 * Vdotdot * (p2x * sinV - p2y * cosV);
  
   *ae = aerr;
}

/* find projected point in constraint object frame */
void determine_projected_point(dpConstraintObject *co, double pt[], double projpt[], double norm[])
{
   double distance;
   double pt_segframe[3], projpt_segframe[3], norm_segframe[3];

   if (co->constraint_type == dpConstraintPlane)
   {
      /* convert the point to the segment frame */
      convert_point_from_constraint_object_frame(co, pt, pt_segframe);

      /* determine projected point (pass info in constraint object SEGMENT frame */
      distance = project_point_onto_plane(pt_segframe, &co->plane, projpt_segframe);
      convert_point_to_constraint_object_frame(co, projpt_segframe, projpt);
      
      /* get plane normal in co frame */
      norm_segframe[0] = co->plane.a;
      norm_segframe[1] = co->plane.b;
      norm_segframe[2] = co->plane.c;
      normalize_vector(norm_segframe, norm_segframe);
      convert_vec_to_constraint_object_frame(co, norm_segframe, norm);
   }
   else if (co->constraint_type == dpConstraintEllipsoid)
   {
      double vars[2], resids[5];
      ellDataStruct info;
      distance = calc_distance_to_ellipsoid(pt, co->co_radius, projpt);
      /* does not return the correct normal vector - solve for it using CalcResids */
      
      info.a = co->co_radius[0];
      info.b = co->co_radius[1];
      info.c = co->co_radius[2];
      sdvset(pt[0], pt[1], pt[2], info.p2);

      /* assume ellipsoid is spherical to get starting values of U, V */
      vars[0] = atan2(pt[1], pt[0]);
      vars[1] = atan2((pt[0] * cos(vars[0]) + pt[1] * sin(vars[0])), pt[2]);
      while (vars[0] < 0.0)
         vars[0] += DEG2RAD(360.0);
      while (vars[0] > DEG2RAD(360.0))
         vars[0] -= DEG2RAD(360.0);
      while (vars[1] < 0.0)
         vars[1] += DEG2RAD(360.0);
      while (vars[1] > DEG2RAD(360.0))
         vars[1] -= DEG2RAD(360.0);

      info.status = PERR;
      LMsolve(&info, 2, 5, vars, resids);
      sdvcopy(info.p1, projpt);
      sdvcopy(info.n, norm);
   }
   else if (co->constraint_type == dpConstraintSphere)
   {
      double sphere_radius = co->co_radius[0];
      distance = VECTOR_MAGNITUDE(pt) - sphere_radius;
      sdvcopy(pt, norm);
      normalize_vector(norm, norm);
      sdvmul(sphere_radius, norm, projpt);
   }
   else if (co->constraint_type == dpConstraintCylinder)
   {
      double z_coeff, axis[] = {0.0, 0.0, 1.0}, origin[] = {0.0, 0.0, 0.0};

      double cyl_radius = co->co_radius[0];
      
      /* find projected point on cylinder axis */
      get_point_from_point_line(pt, origin, axis, projpt);
      z_coeff = projpt[2];
      
      /* find projected point on cylinder */
      sdvsub(pt, projpt, norm);
      normalize_vector(norm, norm);
      sdvmul(cyl_radius, norm, projpt);
      projpt[2] += z_coeff;            
   }
}

/* function used to calculate residuals when solving for U, V, Udot, Vdot, UDotdot and Vdotdot */
void CalculateResids(int numResid, int numVar, double vars[], double resids[], int *flag, 
                       void *data)
{
   ellDataStruct *info = (ellDataStruct *)data;
   double p2x, p2y, p2z, v2x, v2y, v2z, a2x, a2y, a2z;
   double U, V, Udot, Vdot, Udotdot, Vdotdot;
   double p1[3], p2[3], v1[3], v2[3], a1[3], a2[3];
   double n[3], ndot[3], ndotdot[3], Tu[3], Tudot[3], Tudotdot[3], Tv[3], Tvdot[3], Tvdotdot[3];
   double a, b, c, resid1, resid2;
   int status;
   double cosU, cosV, sinU, sinV;
   double TuA, TuB, TuC, TuD, TuAdot, TuBdot, TuCdot, TuDdot, TuAdotdot, TuBdotdot, TuCdotdot, TuDdotdot;
   double TvA, TvB, TvC, TvD, TvAdot, TvBdot, TvCdot, TvDdot, TvAdotdot, TvBdotdot, TvCdotdot, TvDdotdot;
   double nA, nB, nC, nD, nAdot, nBdot, nCdot, nDdot, nAdotdot, nBdotdot, nCdotdot, nDdotdot;

   p2x = info->p2[0]; p2y = info->p2[1]; p2z = info->p2[2];
   v2x = info->v2[0]; v2y = info->v2[1]; v2z = info->v2[2];
   a2x = info->a2[0]; a2y = info->a2[1]; a2z = info->a2[2];
   a = info->a;
   b = info->b;
   c = info->c;

   sdvset(p2x, p2y, p2z, p2);
   sdvset(v2x, v2y, v2z, v2);
   sdvset(a2x, a2y, a2z, a2);

   status = info->status;

   if (status == PERR)
   {
      U = vars[0];
      V = vars[1];
   }
   else
   {
      U = info->U;
      V = info->V;
      if (status == VERR)
      {
         Udot = vars[0];
         Vdot = vars[1];
      }
      if (status > VERR)
      {
         Udot = info->Udot;
         Vdot = info->Vdot;
         Udotdot = vars[0];
         Vdotdot = vars[1];
      }
   }

   while (U < 0.0)
      U += DEG2RAD(360.0);
   while (U > DEG2RAD(360.0))
      U -= DEG2RAD(360.0);
   while (V < 0.0)
      V += DEG2RAD(360.0);
   while (V > DEG2RAD(360.0))
      V -= DEG2RAD(360.0);

   cosU = cos(U);
   sinU = sin(U);
   cosV = cos(V);
   sinV = sin(V);

   if (info->reparameterized == dpYes)
   {
      p1[0] = a * cosV;
      p1[1] = b * cosU * sinV;
      p1[2] = c * sinU * sinV;
      sdvcopy(p1, info->p1);

      TuA = 0.0;
      TuB = -b * sinU * sinV;
      TuC = c * cosU * sinV;
      TuD = SQR(b * sinU * sinV) + SQR(c * cosU * sinV);

      Tu[0] = TuA / sqrt(TuD);
      Tu[1] = TuB / sqrt(TuD);
      Tu[2] = TuC / sqrt(TuD);

      TvA = -a * sinV;
      TvB = b * cosU * cosV;
      TvC = c * sinU * cosV;
      TvD = SQR(a * sinV) + SQR(b * cosU * cosV) + SQR(c * sinU * cosV);

      Tv[0] = TvA / sqrt(TvD);
      Tv[1] = TvB / sqrt(TvD);
      Tv[2] = TvC / sqrt(TvD);

      nA = b * c * cosV;
      nB = a * c * cosU * sinV;
      nC = a * b * sinU * sinV;
      nD = SQR(nA) + SQR(nB) + SQR(nC);

      n[0] = nA / sqrt(nD);
      n[1] = nB / sqrt(nD);
      n[2] = nC / sqrt(nD);
   }
   else
   {
      p1[0] = a * cosU * sinV;
      p1[1] = b * sinU * sinV;
      p1[2] = c * cosV;
      sdvcopy(p1, info->p1);

      TuA = -a * sinU * sinV;/// JPL added V term
      TuB = b * cosU * sinV;/// JPL added V term
      TuD = SQR(a * sinU * sinV) + SQR(b * cosU * sinV);/// JPL added V terms
      Tu[0] = TuA / sqrt(TuD);
      Tu[1] = TuB / sqrt(TuD);
      Tu[2] = 0.0;

      TvA = a * cosU * cosV;
      TvB = b * sinU * cosV;
      TvC = -1.0 * c * sinV;
      TvD = SQR(a * cosU * cosV) + SQR(b * sinU * cosV) + SQR(c * sinV);
      Tv[0] = TvA / sqrt(TvD);
      Tv[1] = TvB / sqrt(TvD);
      Tv[2] = TvC / sqrt(TvD);

      nA = b * c * cosU * sinV;
      nB = a * c * sinU * sinV;
      nC = a * b * cosV;
      nD = SQR(nA) + SQR(nB) + SQR(nC);

      n[0] = nA / sqrt(nD);
      n[1] = nB / sqrt(nD);
      n[2] = nC / sqrt(nD);
   }

   sdvcopy(Tu, info->Tu);
   sdvcopy(Tv, info->Tv);
   sdvcopy(n, info->n);

   /************************** solve for U and V resids *********************************/
   /* to solve for U and V, solve:
    * (P2 - P1) dot Tu = 0, and 
    * (P2 - P1) dot Tv = 0
    */
   resid1 = DOT_VECTORS(p2, Tu) - DOT_VECTORS(p1, Tu);
   resid2 = DOT_VECTORS(p2, Tv) - DOT_VECTORS(p1, Tv);

   resids[0] = resid1;
   resids[1] = resid2;

   resids[2] = resids[3] = resids[4] = 0.0;
   //if (fabs(V) > DEG2RAD(180.0))
      //resids[2] = fabs(V) - DEG2RAD(180.0); JPL maybe add back in later???

   if (status == PERR)
      return;

   /*************************** solve for Udot and Vdot resids *****************************/
   /* to solve for Udot and Vdot, solve:
    * (V2 - V1) dot Tu + (P2 - P1) dot TuDot = 0, and
    * (V2 - V1) dot Tv + (P2 - P1) dot TvDot = 0
    */
   if (info->reparameterized == dpYes)
   {
      v1[0] = -a * Vdot * sinV;
      v1[1] = b * (-Udot * sinU * sinV + Vdot * cosU * cosV);
      v1[2] = c * (Udot * cosU * sinV + Vdot * sinU * cosV);

      TuAdot = 0.0;
      TuBdot = -b * (cosU * sinV * Udot + sinU * cosV * Vdot);
      TuCdot = c * (-sinU * sinV * Udot + cosU * cosV * Vdot);
      TuDdot = 2.0 * (b * b - c * c) * cosU * sinU * sinV * sinV * Udot;
      TuDdot += 2.0 * (b * b * sinU * sinU + c * c * cosU * cosU) * sinV * cosV * Vdot;
      Tudot[0] = TuAdot / sqrt(TuD) - 0.5 * TuA * TuDdot / pow(TuD, 1.5);
      Tudot[1] = TuBdot / sqrt(TuD) - 0.5 * TuB * TuDdot / pow(TuD, 1.5);
      Tudot[2] = TuCdot / sqrt(TuD) - 0.5 * TuC * TuDdot / pow(TuD, 1.5);

      TvAdot = -a * cosV * Vdot;
      TvBdot = -b * (sinU * cosV * Udot + cosU * sinV * Vdot);
      TvCdot = c * (cosU * cosV * Udot - sinU * sinV * Vdot);
      TvDdot = 2.0 * (c * c - b * b) * Udot * cosU * sinU * cosV * cosV;
      TvDdot += 2.0 * Vdot * cosV * sinV * (-1.0 * SQR(b * cosU) - SQR(c * sinU) + a * a);   

      Tvdot[0] = TvAdot / sqrt(TvD) - 0.5 * TvA * TvDdot / pow(TvD, 1.5);
      Tvdot[1] = TvBdot / sqrt(TvD) - 0.5 * TvB * TvDdot / pow(TvD, 1.5);
      Tvdot[2] = TvCdot / sqrt(TvD) - 0.5 * TvC * TvDdot / pow(TvD, 1.5);

      nAdot = -b * c * sinV * Vdot;
      nBdot = a * c * (-sinU * sinV * Udot + cosU * cosV * Vdot);
      nCdot = a * b * (cosU * sinV * Udot + sinU * cosV * Vdot);
      nDdot = 2.0 * Udot * cosU * sinU * sinV * sinV * (SQR(a * b) - SQR(a * c));
      nDdot += 2.0 * Vdot * sinV * cosV * (SQR(a * c * cosU) + SQR(a * b * sinU) - SQR(b * c));

      ndot[0] = nAdot / sqrt(nD) - 0.5 * nA * nDdot / pow(nD, 1.5);
      ndot[1] = nBdot / sqrt(nD) - 0.5 * nB * nDdot / pow(nD, 1.5);
      ndot[2] = nCdot / sqrt(nD) - 0.5 * nC * nDdot / pow(nD, 1.5);
   }
   else
   {
      v1[0] = a * (-1.0 * Udot * sinU * sinV + Vdot * cosU * cosV);
      v1[1] = b * (Udot * cosU * sinV + Vdot * sinU * cosV);
      v1[2] = c * (-1.0 * Vdot * sinV);

      TuAdot = -a * cosU * sinV * Udot - a * sinU * cosV * Vdot;/// JPL added V term
      TuBdot = -b * sinU * sinV * Udot + b * cosU * cosV * Vdot;/// JPL added V term
      TuDdot = 2.0 * (a * a - b * b) * cosU * sinU * sinV * sinV * Udot; /// JPL added V terms
      TuDdot += 2.0 * (a * a * sinU * sinU + b * b * cosU * cosU) * sinV * cosV * Vdot; /// JPL added V terms
      Tudot[0] = TuAdot / sqrt(TuD) - 0.5 * TuA * TuDdot / pow(TuD, 1.5);
      Tudot[1] = TuBdot / sqrt(TuD) - 0.5 * TuB * TuDdot / pow(TuD, 1.5);
      Tudot[2] = 0.0;

      TvAdot = -1.0 * a * Udot * sinU * cosV + a * Vdot * cosU * sinV;
      TvBdot = b * Udot * cosU * cosV - b * Vdot * sinU * sinV;
      TvCdot = -1.0 * c * Vdot * cosV;
      TvDdot = 2.0 * (b * b - a * a) * Udot * cosU * sinU * cosV * cosV;
      TvDdot += 2.0 * Vdot * cosV * sinV * (-1.0 * SQR(a * cosU) - SQR(b * sinU) + c * c);   

      Tvdot[0] = TvAdot / sqrt(TvD) - 0.5 * TvA * TvDdot / pow(TvD, 1.5);
      Tvdot[1] = TvBdot / sqrt(TvD) - 0.5 * TvB * TvDdot / pow(TvD, 1.5);
      Tvdot[2] = TvCdot / sqrt(TvD) - 0.5 * TvC * TvDdot / pow(TvD, 1.5);

      nAdot = b * c * (-1.0 * Udot * sinU * sinV + Vdot * cosU * cosV);
      nBdot = a * c * (Udot * cosU * sinV + Vdot * sinU * cosV);
      nCdot = -1.0 * a * b * Vdot * sinV;
      nDdot = 2.0 * Udot * cosU * sinU * sinV * sinV * (SQR(a * c) - SQR(b * c));
      nDdot += 2.0 * Vdot * sinV * cosV * (SQR(b * c * cosU) + SQR(a * c * sinU) - SQR(a * b));

      ndot[0] = nAdot / sqrt(nD) - 0.5 * nA * nDdot / pow(nD, 1.5);
      ndot[1] = nBdot / sqrt(nD) - 0.5 * nB * nDdot / pow(nD, 1.5);
      ndot[2] = nCdot / sqrt(nD) - 0.5 * nC * nDdot / pow(nD, 1.5);
   }

   normalize_vector(Tudot, Tudot);
   normalize_vector(Tvdot, Tvdot);
   normalize_vector(ndot, ndot);
   sdvcopy(v1, info->v1);
   sdvcopy(Tudot, info->Tudot);
   sdvcopy(Tvdot, info->Tvdot);
   sdvcopy(ndot, info->ndot);

   resid1 = DOT_VECTORS(v2, Tu) - DOT_VECTORS(v1, Tu) + DOT_VECTORS(p2, Tudot) - DOT_VECTORS(p1, Tudot);
   resid2 = DOT_VECTORS(v2, Tv) - DOT_VECTORS(v1, Tv) + DOT_VECTORS(p2, Tvdot) - DOT_VECTORS(p1, Tvdot);

   resids[0] = resid1;
   resids[1] = resid2;
   resids[2] = 0.0;
   resids[3] = 0.0;
   resids[4] = 0.0;

   if (status == VERR)
      return;

   /************************** solve for Udotdot and Vdotdot resids *************************/
   /* to solve for Udotdot and Vdotdot, solve:
    * (A2 - A1) dot Tu + (V2 - V1) dot TuDot + (P2 - P1) dot TuDotDot = 0, and
    * (A2 - A1) dot Tv + (V2 - V1) dot TvDot + (P2 - P1) dot TuDotDot = 0
    */
   if (info->reparameterized == dpYes)
   {
      a1[0] = a * (-Vdotdot * sinV - Vdot * Vdot * cosV);
      a1[1] = b * (-1.0 * Udotdot * sinU * sinV + Vdotdot * cosU * cosV);
      a1[1] += b * (-1.0 * Udot * Udot * cosU * sinV - Vdot * Vdot * cosU * sinV - 2.0 * Udot * Vdot * sinU * cosV);
      a1[2] = c * (Udotdot * cosU * sinV + Vdotdot * sinU * cosV);
      a1[2] += c * (-1.0 * Udot * Udot * sinU * sinV - Vdot * Vdot * sinU * sinV + 2.0 * Udot * Vdot * cosU * cosV);

      TuAdotdot = 0.0;
      TuBdotdot = -b * (cosU * sinV * Udotdot + Udot * (cosU * cosV * Vdot - sinU * sinV * Udot));
      TuBdotdot += -b * (sinU * cosV * Vdot + Vdot * (sinU * -sinV * Vdot + cosU * cosV * Udot));
      TuCdotdot = c * (-sinU * sinV * Udotdot + Udot * (-sinU * cosV * Vdot - cosU * sinV * Udot));
      TuCdotdot += c * (cosU * cosV * Vdotdot + Vdot * (cosU * -sinV * Vdot - sinU * cosV * Udot));
      TuDdotdot = 2.0 * (b*b - c*c) * cosU * sinU * (sinV * (sinV * Udotdot + cosV * Udot * Vdot) + cosV * sinV * Udot * Vdot);
      TuDdotdot += 2.0 * (b*b - c*c) * (cosU * cosU * Udot - sinU * sinU * Udot) * sinV * sinV * Udot;
      TuDdotdot += 2.0 * sinV * cosV * Vdot * (2.0 * b * b * (sinU * cosU * Udot) - 2.0 * c * c * (sinU * cosU * Udot));
      TuDdotdot += 2.0 * (sinV * (cosV * Vdotdot - sinV * Vdot * Vdot) + cosV * cosV * Vdot * Vdot) * (b * b * sinU * sinU + c * c * cosU * cosU);
      Tudotdot[0] = TuAdotdot / sqrt(TuD) - TuAdot * TuDdot / pow(TuD, 1.5) -0.5 * TuA * TuDdotdot / pow(TuD, 1.5) + 0.75 * TuA * TuDdot * TuDdot / pow(TuD, 2.5);
      Tudotdot[1] = TuBdotdot / sqrt(TuD) - TuBdot * TuDdot / pow(TuD, 1.5) -0.5 * TuB * TuDdotdot / pow(TuD, 1.5) + 0.75 * TuB * TuDdot * TuDdot / pow(TuD, 2.5);
      Tudotdot[2] = TuCdotdot / sqrt(TuD) - TuCdot * TuDdot / pow(TuD, 1.5) -0.5 * TuC * TuDdotdot / pow(TuD, 1.5) + 0.75 * TuC * TuDdot * TuDdot / pow(TuD, 2.5);

      TvAdotdot = -c * Vdotdot * cosV + c * Vdot * Vdot * sinV;
      TvBdotdot = -b * Udotdot * sinU * cosV - b * Udot * Udot * cosU * cosV;
      TvBdotdot += b * Vdotdot * cosU * sinV + b * Vdot * Vdot * cosU * cosV;
      TvCdotdot = c * Udotdot * cosU * cosV - c * Udot * Udot * sinU * cosV - 2.0 * c * Udot * Vdot * cosU * sinV;
      TvCdotdot += -1.0 * c * Vdotdot * sinU * sinV - c * Vdot * Vdot * sinU * cosV;
      TvDdotdot = 2.0 * (c * c - b * b) * Udotdot * cosU * sinU * cosV * cosV;
      TvDdotdot += 2.0 * (c * c - b * b) * Udot * Udot * cosV * cosV * (SQR(cosU) - SQR(sinU));
      TvDdotdot += -4.0 * (c * c - b * b) * Udot * Vdot * cosU * sinU * cosV * sinV;
      TvDdotdot += 2.0 * Vdotdot * cosV * sinV * (-1.0 * SQR(b * cosU) - SQR(c * sinU) + a * a);
      TvDdotdot += 2.0 * Vdot * Vdot * (SQR(cosV) - SQR(sinV)) * (-1.0 * SQR(b * cosU) - SQR(c * sinU) + a * a);
      TvDdotdot += 4.0 * Udot * Vdot * cosU * sinU * cosV * sinV * (b * b - c * c); 

      Tvdotdot[0] = TvAdotdot / sqrt(TvD) - TvAdot * TvDdot / pow(TvD, 1.5) -0.5 * TvA * TvDdotdot / pow(TvD, 1.5) + 0.75 * TvA * TvDdot * TvDdot / pow(TvD, 2.5);
      Tvdotdot[1] = TvBdotdot / sqrt(TvD) - TvBdot * TvDdot / pow(TvD, 1.5) -0.5 * TvB * TvDdotdot / pow(TvD, 1.5) + 0.75 * TvB * TvDdot * TvDdot / pow(TvD, 2.5);
      Tvdotdot[2] = TvCdotdot / sqrt(TvD) - TvCdot * TvDdot / pow(TvD, 1.5) -0.5 * TvC * TvDdotdot / pow(TvD, 1.5) + 0.75 * TvC * TvDdot * TvDdot / pow(TvD, 2.5);

      nAdotdot = -b * c * (Vdotdot * sinV + Vdot * Vdot * cosV);
      nBdotdot = c * a * (-1.0 * Udotdot * sinU * sinV + Vdotdot * cosU * cosV);
      nBdotdot += c * a * (-1.0 * Udot * Udot * cosU * sinV - Vdot * Vdot * cosU * sinV);
      nBdotdot += c * a * -2.0 * Udot * Vdot * sinU  * cosV;
      nCdotdot = b * a * (Udotdot * cosU * sinV + Vdotdot * sinV * cosU);
      nCdotdot += b * a * (-1.0 * Udot * Udot * sinU * sinV - Vdot * Vdot * sinU * sinV);
      nCdotdot += b * a * 2.0 * Udot * Vdot * cosU * cosV;
      nDdotdot = 2.0 * (SQR(b * a) - SQR(c * a)) * (Udotdot * cosU * sinU * sinV * sinV + Udot * Udot * sinV * sinV * (SQR(cosU) - SQR(sinU)));
      nDdotdot += 8.0 * (SQR(b * a) - SQR(c * a)) * Udot * Vdot * cosV * sinV * cosU * sinU;
      nDdotdot += 2.0 * (SQR(c * a * cosU) + SQR(b * a * sinU) - SQR(b * c)) * (Vdotdot * cosV * sinV + Vdot * Vdot * (SQR(cosV) - SQR(sinV)));

      ndotdot[0] = nAdotdot / sqrt(nD) - nAdot * nDdot / pow(nD, 1.5) -0.5 * nA * nDdotdot / pow(nD, 1.5) + 0.75 * nA * nDdot * nDdot / pow(nD, 2.5);
      ndotdot[1] = nBdotdot / sqrt(nD) - nBdot * nDdot / pow(nD, 1.5) -0.5 * nB * nDdotdot / pow(nD, 1.5) + 0.75 * nB * nDdot * nDdot / pow(nD, 2.5);
      ndotdot[2] = nCdotdot / sqrt(nD) - nCdot * nDdot / pow(nD, 1.5) -0.5 * nC * nDdotdot / pow(nD, 1.5) + 0.75 * nC * nDdot * nDdot / pow(nD, 2.5);
   }
   else
   {
      a1[0] = a * (-1.0 * Udotdot * sinU * sinV + Vdotdot * cosU * cosV);
      a1[0] += a * (-1.0 * Udot * Udot * cosU * sinV - Vdot * Vdot * cosU * sinV - 2.0 * Udot * Vdot * sinU * cosV);
      a1[1] = b * (Udotdot * cosU * sinV + Vdotdot * sinU * cosV);
      a1[1] += b * (-1.0 * Udot * Udot * sinU * sinV - Vdot * Vdot * sinU * sinV + 2.0 * Udot * Vdot * cosU * cosV);
      a1[2] = c * (-1.0 * Vdotdot * sinV - Vdot * Vdot * cosV);

      TuAdotdot = -1.0 * a * (Udotdot * cosU - Udot * Udot * sinU);
      TuBdotdot = -1.0 * b * (Udotdot * sinU + Udot * Udot * cosU);
      TuDdotdot = 2.0 * (a * a - b * b) * (Udotdot * cosU * sinU + Udot * Udot * (SQR(cosU) - SQR(sinU)));
      Tudotdot[0] = TuAdotdot / sqrt(TuD) - TuAdot * TuDdot / pow(TuD, 1.5) -0.5 * TuA * TuDdotdot / pow(TuD, 1.5) + 0.75 * TuA * TuDdot * TuDdot / pow(TuD, 2.5);
      Tudotdot[1] = TuBdotdot / sqrt(TuD) - TuBdot * TuDdot / pow(TuD, 1.5) -0.5 * TuB * TuDdotdot / pow(TuD, 1.5) + 0.75 * TuB * TuDdot * TuDdot / pow(TuD, 2.5);
      Tudotdot[2] = 0.0;

      TvAdotdot = -1.0 * a * Udotdot * sinU * cosV - a * Udot * Udot * cosU * cosV;
      TvAdotdot += a * Vdotdot * cosU * sinV + a * Vdot * Vdot * cosU * cosV;
      TvBdotdot = b * Udotdot * cosU * cosV - b * Udot * Udot * sinU * cosV - 2.0 * b * Udot * Vdot * cosU * sinV;
      TvBdotdot += -1.0 * b * Vdotdot * sinU * sinV - b * Vdot * Vdot * sinU * cosV;
      TvCdotdot = -1.0 * c * Vdotdot * cosV + c * Vdot * Vdot * sinV;
      TvDdotdot = 2.0 * (b * b - a * a) * Udotdot * cosU * sinU * cosV * cosV;
      TvDdotdot += 2.0 * (b * b - a * a) * Udot * Udot * cosV * cosV * (SQR(cosU) - SQR(sinU));
      TvDdotdot += -4.0 * (b * b - a * a) * Udot * Vdot * cosU * sinU * cosV * sinV;
      TvDdotdot += 2.0 * Vdotdot * cosV * sinV * (-1.0 * SQR(a * cosU) - SQR(b * sinU) + c * c);
      TvDdotdot += 2.0 * Vdot * Vdot * (SQR(cosV) - SQR(sinV)) * (-1.0 * SQR(a * cosU) - SQR(b * sinU) + c * c);
      TvDdotdot += 4.0 * Udot * Vdot * cosU * sinU * cosV * sinV * (a * a - b * b); 

      Tvdotdot[0] = TvAdotdot / sqrt(TvD) - TvAdot * TvDdot / pow(TvD, 1.5) -0.5 * TvA * TvDdotdot / pow(TvD, 1.5) + 0.75 * TvA * TvDdot * TvDdot / pow(TvD, 2.5);
      Tvdotdot[1] = TvBdotdot / sqrt(TvD) - TvBdot * TvDdot / pow(TvD, 1.5) -0.5 * TvB * TvDdotdot / pow(TvD, 1.5) + 0.75 * TvB * TvDdot * TvDdot / pow(TvD, 2.5);
      Tvdotdot[2] = TvCdotdot / sqrt(TvD) - TvCdot * TvDdot / pow(TvD, 1.5) -0.5 * TvC * TvDdotdot / pow(TvD, 1.5) + 0.75 * TvC * TvDdot * TvDdot / pow(TvD, 2.5);

      nAdotdot = b * c * (-1.0 * Udotdot * sinU * sinV + Vdotdot * cosU * cosV);
      nAdotdot += b * c * (-1.0 * Udot * Udot * cosU * sinV - Vdot * Vdot * cosU * sinV);
      nAdotdot += b * c * -2.0 * Udot * Vdot * sinU  * cosV;
      nBdotdot = a * c * (Udotdot * cosU * sinV + Vdotdot * sinV * cosU);
      nBdotdot += a * c * (-1.0 * Udot * Udot * sinU * sinV - Vdot * Vdot * sinU * sinV);
      nBdotdot += a * c * 2.0 * Udot * Vdot * cosU * cosV;
      nCdotdot = -1.0 * a * b * (Vdotdot * sinV + Vdot * Vdot * cosV);
      nDdotdot = 2.0 * (SQR(a * c) - SQR(b * c)) * (Udotdot * cosU * sinU * sinV * sinV + Udot * Udot * sinV * sinV * (SQR(cosU) - SQR(sinU)));
      nDdotdot += 8.0 * (SQR(a * c) - SQR(b * c)) * Udot * Vdot * cosV * sinV * cosU * sinU;
      nDdotdot += 2.0 * (SQR(b * c * cosU) + SQR(a * c * sinU) - SQR(a * b)) * (Vdotdot * cosV * sinV + Vdot * Vdot * (SQR(cosV) - SQR(sinV)));

      ndotdot[0] = nAdotdot / sqrt(nD) - nAdot * nDdot / pow(nD, 1.5) -0.5 * nA * nDdotdot / pow(nD, 1.5) + 0.75 * nA * nDdot * nDdot / pow(nD, 2.5);
      ndotdot[1] = nBdotdot / sqrt(nD) - nBdot * nDdot / pow(nD, 1.5) -0.5 * nB * nDdotdot / pow(nD, 1.5) + 0.75 * nB * nDdot * nDdot / pow(nD, 2.5);
      ndotdot[2] = nCdotdot / sqrt(nD) - nCdot * nDdot / pow(nD, 1.5) -0.5 * nC * nDdotdot / pow(nD, 1.5) + 0.75 * nC * nDdot * nDdot / pow(nD, 2.5);
   }

   normalize_vector(Tudotdot, Tudotdot);
   normalize_vector(Tvdotdot, Tvdotdot);
   normalize_vector(ndotdot, ndotdot);

   sdvcopy(a1, info->a1);
   sdvcopy(Tudotdot, info->Tudotdot);
   sdvcopy(Tvdotdot, info->Tvdotdot);
   sdvcopy(ndotdot, info->ndotdot);

   resid1 = DOT_VECTORS(a2, Tu) - DOT_VECTORS(a1, Tu);
   resid1 += DOT_VECTORS(v2, Tudot) - DOT_VECTORS(v1, Tudot);
   resid1 += DOT_VECTORS(p2, Tudotdot) - DOT_VECTORS(p1, Tudotdot);

   resid2 = DOT_VECTORS(a2, Tv) - DOT_VECTORS(a1, Tv);
   resid2 += DOT_VECTORS(v2, Tvdot) - DOT_VECTORS(v1, Tvdot);
   resid2 += DOT_VECTORS(p2, Tvdotdot) - DOT_VECTORS(p1, Tvdotdot);

   resids[0] = resid1;
   resids[1] = resid2;
   resids[2] = 0.0;
   resids[3] = 0.0;
   resids[4] = 0.0;
}


/* LMSOLVE: Set up the required work arrays and variables and call lmdif
 * to solve the least squares problem using the Levenberg-Marquart theory.
 * q: solution vector (initially contains estimate of soln in internal units) (x) 
 * fvec: functions evaluated at output q (final residuals)
 * num_resid: number of functions (m) (nres) 
 * nq: number of variables (n) (ndofinp)
 */
int LMsolve(ellDataStruct *solveInfo, int numVars, int numResid, double vars[], double resid[])
{
   int info;                  /* output flag */
   int num_func_calls;        /* number of calls to func (nfev) */
   int ldfjac = numResid;     /* leading dimension of fjac (nres) */
   double *fjac;              /* m X n array */
   
   /* solution parameters */
   int mode = 1, nprint = 0, max_iter = 5000;
   double ftol = 1e-4, xtol = 1e-4, gtol = 0.0;
   double epsfcn = 0.0, step_factor = 0.2;
   
   /* work arrays */
   int *ipvt;  
   double *diag, *qtf, *wa1, *wa2, *wa3, *wa4;
      
   /* allocate space for necessary arrays */
   ipvt = (int *)simm_malloc(numVars * sizeof(int));
   diag = (double *)simm_malloc(numVars * sizeof(double));
   fjac = (double *)simm_malloc(numVars * numResid * sizeof(double));
   qtf = (double *)simm_malloc(numVars * sizeof(double));               /* wa[ndofinp + 1] */
   wa1 = (double *)simm_malloc(numVars * sizeof(double));               /* wa[2 * ndofinp + 1] */
   wa2 = (double *)simm_malloc(numVars * sizeof(double));               /* wa[3 * ndofinp + 1] */
   wa3 = (double *)simm_malloc(numVars * sizeof(double));               /* wa[4 * ndofinp + 1] */
   wa4 = (double *)simm_malloc(numResid * sizeof(double));           /* wa[5 * ndofinp + 1]*/

   xtol = 1e-8;
   ftol = 1e-8;

   lmdif_C(CalculateResids, numResid, numVars, vars, resid,
       ftol, xtol, gtol, max_iter, epsfcn, diag, mode, step_factor,
       nprint, &info, &num_func_calls, fjac, ldfjac, ipvt, qtf,
       wa1, wa2, wa3, wa4, solveInfo);

   free(ipvt);
   free(diag);
   free(fjac);
   free(qtf);
   free(wa1);
   free(wa2);
   free(wa3);
   free(wa4);

   return info;
}


static void convert_point_to_constraint_object_frame(dpConstraintObject* co, double* in, double* out)
{
   sdvcopy(in, out);
   if (co && out)
   {
      transform_pt(co->to_local_xform, out);
   }
}


static void convert_point_from_constraint_object_frame(dpConstraintObject* co, double* in, double* out)
{
   sdvcopy(in, out);
   if (co && out)
   {
      transform_pt(co->from_local_xform, out);
   }
}


static void convert_vec_to_constraint_object_frame(dpConstraintObject* co, double* in, double* out)
{
   sdvcopy(in, out);
   if (co && out)
   {
      transform_vec(co->to_local_xform, out);
   }
}


static void convert_vec_from_constraint_object_frame(dpConstraintObject* co, double* in, double* out)
{
   sdvcopy(in, out);
   if (co && out)
   {
      transform_vec(co->from_local_xform, out);
   }
}

