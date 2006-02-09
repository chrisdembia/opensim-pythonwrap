/*******************************************************************************

   TORUS_WRAP.C

   Author: Peter Loan

   Copyright (c) 2002-2004 MusculoGraphics, Inc, a division of Motion Analysis Corp.
   All rights reserved.

   Description: code for wrapping muscle through a torus. This is done by
     putting a hemi-cylinder at the appropriate position w.r.t. the torus,
     and wrapping the muscle over the cylinder (because true torus wrapping
     is too difficult).

*******************************************************************************/

#include "universal.h"

/*************** DEFINES (for this file only) *********************************/
#define E_INSIDE_RADIUS	  -1
#define E_NO_WRAP 0
#define E_WRAPPED 1
#define E_MANDATORY_WRAP 2
#define _UNFACTOR \
   for (i = 0; i < 3; i++) \
   { \
      p1[i] /= factor; \
      p2[i] /= factor; \
      m[i]  /= factor; \
      a[i]  /= factor; \
      r1[i] /= factor; \
      r2[i] /= factor; \
   }

typedef struct
{
   double p1[3], p2[3], r;
} CircleCallback;



/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
static const float red[] = { 1, 0, 0 }, green[] = { 0, 1, 0 }, blue[] = { 0, 0, 1 };
static const float cyan[] = { 0, 1, 1 }, magenta[] = { 1, 0, 1 }, yellow[] = { 1, 1, 0 };
static const float white[] = { 1, 1, 1 }, pink[] = { 1, 0.5, 0.5 };
static const float* fan_color = white;
static double factor, sv[3], c1[3];


/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/
void lmdif_C(void (*fcn)(int, int, double[], double[], int *, void *),
             int m, int n, double x[], double fvec[], double ftol, double xtol,
             double gtol, int maxfev, double epsfcn, double diag[], int mode,
             double factor, int nprint, int *info, int *nfev, double fjac[],
             int ldfjac, int ipvt[], double qtf[], double wa1[], double wa2[],
             double wa3[], double wa4[], void *ptr);



void calcCircleResids(int numResid, int numQs, double q[], double resid[], int *flag2, void *ptr)
{
   double mag, nx, ny, nz, u;
   double c2, c3, c4, c5, c6;
   CircleCallback *cb = ptr;

   u = q[0];

   mag = sqrt((cb->p2[0]-cb->p1[0])*(cb->p2[0]-cb->p1[0]) + (cb->p2[1]-cb->p1[1])*(cb->p2[1]-cb->p1[1]) +
      (cb->p2[2]-cb->p1[2])*(cb->p2[2]-cb->p1[2]));

   nx = (cb->p2[0]-cb->p1[0]) / mag;
   ny = (cb->p2[1]-cb->p1[1]) / mag;
   nz = (cb->p2[2]-cb->p1[2]) / mag;

   c2 = 2.0 * (cb->p1[0]*nx + cb->p1[1]*ny + cb->p1[2]*nz);
   c3 = cb->p1[0]*nx + cb->p1[1]*ny;
   c4 = nx*nx + ny*ny;
   c5 = cb->p1[0]*cb->p1[0] + cb->p1[1]*cb->p1[1];
   c6 = sqrt (u * u * c4 + 2.0 * c3 * u + c5);

   resid[0] = c2 + 2.0 * u - 2.0 * cb->r * (2.0 * c4 * u + 2.0 * c3) / sqrt (u * u * c4 + 2.0 * c3 * u + c5);
}

dpWrapObject *gWo;

/* This function finds the closest point on an origin-centered circle on the Z=0 plane
 * to the line between p1 and p2. It uses lmdif_C()
 */
int findClosestPoint(double radius, double p1[], double p2[], double* xc, double* yc, double* zc,
                     int wrap_sign, int wrap_axis)
{
   int info;                  /* output flag */
   int num_func_calls;        /* number of calls to func (nfev) */
   int ldfjac = 1;            /* leading dimension of fjac (nres) */
   int numResid = 1;
   int numQs = 1;
   double q[2], resid[2], fjac[2];            /* m X n array */
   CircleCallback cb;
   dpBoolean constrained = (dpBoolean) (wrap_sign != 0);
   /* solution parameters */
   int mode = 1, nprint = 0, max_iter = 500;
   double ftol = 1e-4, xtol = 1e-4, gtol = 0.0;
   double epsfcn = 0.0, step_factor = 0.2;
   /* work arrays */
   int ipvt[2];  
   double diag[2], qtf[2], wa1[2], wa2[2], wa3[2], wa4[2];
   /* Circle variables */
   double u, mag, nx, ny, nz, x, y, z, a1[3], a2[3], distance1, distance2, betterPt = 0;

   cb.p1[0] = p1[0];
   cb.p1[1] = p1[1];
   cb.p1[2] = p1[2];
   cb.p2[0] = p2[0];
   cb.p2[1] = p2[1];
   cb.p2[2] = p2[2];
   cb.r = radius;

   q[0] = 0.0;

   lmdif_C(calcCircleResids, numResid, numQs, q, resid,
           ftol, xtol, gtol, max_iter, epsfcn, diag, mode, step_factor,
           nprint, &info, &num_func_calls, fjac, ldfjac, ipvt, qtf,
           wa1, wa2, wa3, wa4, (void*)&cb);

   u = q[0];

   mag = sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));

   nx = (p2[0]-p1[0]) / mag;
   ny = (p2[1]-p1[1]) / mag;
   nz = (p2[2]-p1[2]) / mag;

   x = p1[0] + u * nx;
   y = p1[1] + u * ny;
   z = p1[2] + u * nz;

   /* Store the result from the first pass. */
   a1[0] = x;
   a1[1] = y;
   a1[2] = z;

   distance1 = sqrt(x*x + y*y + z*z + radius*radius - 2.0 * radius * sqrt(x*x + y*y));

   /* Perform the second pass, switching the order of the two points. */
   cb.p1[0] = p2[0];
   cb.p1[1] = p2[1];
   cb.p1[2] = p2[2];
   cb.p2[0] = p1[0];
   cb.p2[1] = p1[1];
   cb.p2[2] = p1[2];
   cb.r = radius;

   q[0] = 0.0;

   lmdif_C(calcCircleResids, numResid, numQs, q, resid,
           ftol, xtol, gtol, max_iter, epsfcn, diag, mode, step_factor,
           nprint, &info, &num_func_calls, fjac, ldfjac, ipvt, qtf,
           wa1, wa2, wa3, wa4, (void*)&cb);

   u = q[0];

   mag = sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));

   nx = (p1[0]-p2[0]) / mag;
   ny = (p1[1]-p2[1]) / mag;
   nz = (p1[2]-p2[2]) / mag;

   x = p2[0] + u * nx;
   y = p2[1] + u * ny;
   z = p2[2] + u * nz;

   /* Store the result from the second pass. */
   a2[0] = x;
   a2[1] = y;
   a2[2] = z;

   distance2 = sqrt(x*x + y*y + z*z + radius*radius - 2.0 * radius * sqrt(x*x + y*y));

   /* Now choose the better result from the two passes. If the circle is not
    * constrained, then just choose the one with the shortest distance. If the
    * circle is constrained, then choose the one that is on the correct half of
    * the circle. If both are on the correct half, choose the closest.
    */
   if (constrained)
   {
      if (DSIGN(a1[wrap_axis]) == wrap_sign && DSIGN(a2[wrap_axis]) == wrap_sign)
      {
         if (distance1 < distance2)
            betterPt = 0;
         else
            betterPt = 1;
      }
      else if (DSIGN(a1[wrap_axis]) == wrap_sign)
      {
         betterPt = 0;
      }
      else if (DSIGN(a2[wrap_axis]) == wrap_sign)
      {
         betterPt = 1;
      }
      else
      {
         /* no wrapping should occur */
         return 0;
      }
   }
   else
   {
      if (distance1 < distance2)
         betterPt = 0;
      else
         betterPt = 1;
   }

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(gWo, 1.0, a1, a2, 2, "a1", "a2", yellow);
#endif

   /* a1 and a2 represent the points on the line that are closest to the circle.
    * What you need to find and return is the corresponding point on the circle.
    */
   if (betterPt == 0)
   {
      mag = (sqrt(a1[0]*a1[0] + a1[1]*a1[1]));
      *xc = a1[0] * radius / mag;
      *yc = a1[1] * radius / mag;
      *zc = 0.0;
   }
   else
   {
      mag = (sqrt(a2[0]*a2[0] + a2[1]*a2[1]));
      *xc = a2[0] * radius / mag;
      *yc = a2[1] * radius / mag;
      *zc = 0.0;
   }

   return 1;
}


/* -------------------------------------------------------------------------
   calc_line_intersect_torus - calculate an optimal wrapping path about
      the specified torus.
---------------------------------------------------------------------------- */
int calc_line_intersect_torus (
	double		p1[3],		/* input:  muscle point 1		*/
	double		p2[3],		/* input:  muscle point 2		*/
	double		m[3],		/* input:  torus origin (0,0,0)	*/
	double		a[3],		/* input:  torus xy[z] radii		*/
	double*		rlen,		/* output: length of surface wrap	*/
	double		r1[],		/* output: wrap tangent point 1		*/
	double		r2[],		/* output: wrap tangent point 2		*/
	double**	wrap_pts,	/* output: intermediate surface wrap pts*/
	int*		num_wrap_pts,	/* output: number of intermediate pts	*/
	int		wrap_axis,	/* input:  constraint axis		*/
	int		wrap_sign,	/* input:  constraint direction		*/
	dpMuscleWrapStruct* mwrap, /* in/out: muscle wrap structure	*/
	int*		p_flag,		/* output: did wrapping occur?		*/
	dpWrapObject*	wo)
{
   int i;
   
   double x, y, z;
   dpBoolean constrained   = (dpBoolean) (wrap_sign != 0);
   
   dpBoolean far_side_wrap = dpNo;
      
   *p_flag       = TRUE;
   *num_wrap_pts = 0;
   *wrap_pts     = NULL;
   
#if VISUAL_WRAPPING_DEBUG
   enable_debug_shapes(yes);
   gWo = wo;
   wo->num_debug_glyphs = 0;
#endif
#if 0
   /* Only wrap this muscle segment if the points are on either side of the torus. */
   if (DSIGN(p1[ZZ]) == DSIGN(p2[ZZ]))
      return E_NO_WRAP;
#endif
#if 0
   /* If the torus is constrained, intersect the muscle line with the Z=0 plane
    * to see if wrapping needs to occur. t is the value of the parameter of the
    * 3D line from p1 to p2 when Z = 0. You don't need to bother with this check
    * if the torus is unconstrained because in that case you always want to find
    * the instantaneous cylinder and try to wrap over it.
    */
   if (constrained)
   {
      t = p1[2] / (p1[2] - p2[2]);
      pt[0] = p1[0] + t * (p2[0] - p1[0]);
      pt[1] = p1[1] + t * (p2[1] - p1[1]);

      if (DSIGN(pt[wrap_axis]) != wrap_sign)
         return E_NO_WRAP;
   }
#endif

   if (findClosestPoint(a[1], p1, p2, &x, &y, &z, wrap_sign, wrap_axis) == 0)
      return E_NO_WRAP;

   /* Now put a cylinder at (x, y, z) and call the cylinder wrap code. */
   {
      int error_code;
      dpWrapObject cyl;
      double pt1[4], pt2[4], npt1[4], npt2[4], tpt1[4], tpt2[4];
      double origin[3], axis[3], Xaxis[3], Yaxis[3], Zaxis[3], delta[3];

      for (i = 0; i < 3; i++)
      {
         pt1[i] = p1[i];
         pt2[i] = p2[i];
      }
      pt1[3] = pt2[3] = 1.0;
#if VISUAL_WRAPPING_DEBUG && ! WRAP_LIB
         add_debug_line(wo, 1.0, pt1, pt2, 2, "", "p1p2", red);
#endif
      origin[0] = 0.0;
      origin[1] = 0.0;
      origin[2] = -5000.0;
      axis[0] = 0.0;
      axis[1] = 0.0;
      axis[2] = 1.0;

      cyl.wrap_type = dpWrapCylinder;
      cyl.wrap_algorithm = 0;
      cyl.height = 10000.0;
      cyl.radius[0] = a[0];
      cyl.wrap_axis = XX;
      cyl.wrap_sign = 1;

      // fill in proper transform
      Xaxis[0] = -x;
      Xaxis[1] = -y;
      Xaxis[2] = -z;
      normalize_vector(Xaxis, Xaxis);
      Yaxis[0] = 0.0;
      Yaxis[1] = 0.0;
      Yaxis[2] = -1.0;
      cross_vectors(Xaxis, Yaxis, Zaxis);
      MAKE_IDENTITY_MATRIX(cyl.to_local_xform);
      for (i = 0; i < 3; i++)
      {
         cyl.to_local_xform[i][0] = Xaxis[i];
         cyl.to_local_xform[i][1] = Yaxis[i];
         cyl.to_local_xform[i][2] = Zaxis[i];
      }
      delta[0] = -x; delta[1] = -y; delta[2] = -z;
      transform_pt(cyl.to_local_xform, delta);
      translate_matrix(cyl.to_local_xform, delta);
      invert_4x4transform(cyl.to_local_xform, cyl.from_local_xform);

      mult_4x4matrix_by_vector(cyl.to_local_xform,pt1,npt1);
      mult_4x4matrix_by_vector(cyl.to_local_xform,pt2,npt2);

      error_code = calc_line_intersect_cylinder(npt1, npt2,
                                                origin, axis, cyl.radius[0],
                                                cyl.height, rlen, tpt1, tpt2,
                                                wrap_pts, num_wrap_pts,
                                                cyl.wrap_axis, cyl.wrap_sign,
                                                mwrap, p_flag, &cyl);
      if (*p_flag == TRUE && error_code > 0)
      {
         tpt1[3] = tpt2[3] = 1.0;
         mult_4x4matrix_by_vector(cyl.from_local_xform,tpt1,r1);
         mult_4x4matrix_by_vector(cyl.from_local_xform,tpt2,r2);
      }

      return E_WRAPPED;
   }

   return E_WRAPPED;

} /* calc_line_intersect_ellipsoid */

