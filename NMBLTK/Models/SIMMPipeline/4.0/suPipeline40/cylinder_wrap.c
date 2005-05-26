/*******************************************************************************

   CYLINDER_WRAP.C

   Author: Ken Smith
           Frans van der Helm
           Peter Loan

   Copyright (c) 1998-2004 MusculoGraphics, Inc, a division of Motion Analysis Corp.
   All rights reserved.

   Description: code for wrapping muscle over a cylinder. The "spiral" algorithm
     is currently being used; the "planar" algorithm is commented out.

*******************************************************************************/
#include "universal.h"


/*************** DEFINES (for this file only) *********************************/
#define NUM_WRAP_SEGS     100
#define MAX_ITERATIONS    100
#define TANGENCY_THRESHOLD (0.1 * DTOR) /* find tangency to within 1 degree */

#define E_INSIDE_RADIUS	  -1
#define E_NO_WRAP 0
#define E_WRAPPED 1
#define E_MANDATORY_WRAP 2


/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
#if VISUAL_WRAPPING_DEBUG
static const float red[] = { 1, 0, 0 }, green[] = { 0, 1, 0 }, blue[] = { 0, 0, 1 };
static const float cyan[] = { 0, 1, 1 }, magenta[] = { 1, 0, 1 }, yellow[] = { 1, 1, 0 };
static const float white[] = { 1, 1, 1 }, pink[] = { 1, 0.5, 0.5 };
#endif


/*************** EXTERNED VARIABLES (declared in another file) ****************/


/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/
static int _spiral_wrap_cylinder (
	double		p1[3],	  /* input:  muscle point 1 */
	double		p2[3],	  /* input:  muscle point 2 */
   double		p0[3],     /* input:  point on cylinder axis */
	double		dn[3],     /* input:  direction vector of cyl axis */
	double		r,         /* input:  cylinder radius */
	double		len,       /* input:  cylinder length */
	double*		rlen,		  /* output: length of surface wrap */
	double		r1[],		  /* output: wrap tangent point 1 */
	double		r2[],		  /* output: wrap tangent point 2 */
	double**	wrap_pts,	  /* output: intermediate surface wrap pts */
	int*		num_wrap_pts, /* output: number of intermediate pts */
	int		wrap_axis,	  /* input:  constraint axis */
	int		wrap_sign,	  /* input:  constraint direction */
	dpMuscleWrapStruct* mwrap, /* in/out: muscle wrap structure */
	int*		p_flag,		  /* output: did wrapping occur? */
	dpWrapObject*	wo);       /* input:  pointer to cylinder wrap object */

static void _make_spiral_path (
	double		p1[3],		/* input:  muscle point 1		*/
	double		p2[3],		/* input:  muscle point 2		*/
        double		p0[3],          /* input:  point on cylinder axis       */
	double		dn[3],          /* input:  direction vector of cyl axis */
	double		r,              /* input:  cylinder radius              */
	double		r1[],		/* input:  wrap tangent point 1		*/
	double		r2[],		/* input:  wrap tangent point 2		*/
	dpBoolean	far_side_wrap,	/* input:  is it a far side wrap?	*/
	double*		rlen,		/* output: length of surface wrap	*/
	double**	wrap_pts,	/* output: intermediate surface wrap pts*/
	int*		num_wrap_pts,	/* output: number of intermediate pts	*/
	dpWrapObject*	wo);

static void _calc_spiral_wrap_point (
	const double	r1a[3],
	const double	axial_vec[3],
	double		m[4][4],
	const double	axis[3],
	double		r,
	double		sense,
	double		t,
	double		theta,
	double		wrap_pt[3]);

static dpBoolean _adjust_tangent_point (
	double		p1[3],		/* input:  muscle point 1		*/
	double		dn[3],          /* input:  direction vector of cyl axis */
	double		r1[],		/* input/output:  wrap tangent point 1	*/
	double		w1[]);		/* input:  wrap point 1			*/

static dpBoolean _ray_plane_intersetion (
   double vs[3],  /* input:  plane normal vector */
   double vs4,    /* input:  plane offset */
   double rp[3],  /* input:  ray origin */
   double vv[3],  /* input:  ray vector */
   double r[3]);  /* output: ray-plane intersection */

#if 0
static int _planar_wrap_cylinder (
	double		p11[3],		/* input:  muscle point 1		*/
	double		p22[3],		/* input:  muscle point 2		*/
        double		p0[3],          /* input:  point on cylinder axis       */
	double		dn[3],          /* input:  direction vector of cyl axis */
	double		r,              /* input:  cylinder radius              */
	double*		rlen,		/* output: length of surface wrap	*/
	double		r1[],		/* output: wrap tangent point 1		*/
	double		r2[],		/* output: wrap tangent point 2		*/
	double**	wrap_pts,	/* output: intermediate surface wrap pts*/
	int*		num_wrap_pts,	/* output: number of intermediate pts	*/
	int		wrap_axis,	/* input:  constraint axis		*/
	int		wrap_sign,	/* input:  constraint direction		*/
	dpMuscleWrapStruct* mwrap, /* in/out: muscle wrap structure	*/
	int*		p_flag,		/* output: did wrapping occur?		*/
	dpWrapObject*	wo);


static double polang(double v1[3], double v2[3], double v3[3]);

static void dcyl(const double p0[3], const double dn[3], double r,
	         const double r1[3], const double r2[3],
	         const double c0[3], const double wrap_axis[3],
	         double* rlen, double** wrap_pts, int* num_wrap_pts);
#endif

/* -------------------------------------------------------------------------
   calc_line_intersect_cylinder - 
---------------------------------------------------------------------------- */
int calc_line_intersect_cylinder (
	double		p11[3],		/* input:  muscle point 1 */
	double		p22[3],		/* input:  muscle point 2 */
   double		p0[3],      /* input:  point on cylinder axis */
	double		dn[3],      /* input:  direction vector of cyl axis */
	double		r,          /* input:  cylinder radius */
	double		len,        /* input:  cylinder length */
	double*		rlen,		   /* output: length of surface wrap */
	double		r1[],		   /* output: wrap tangent point 1 */
	double		r2[],		   /* output: wrap tangent point 2 */
	double**	wrap_pts,	   /* output: intermediate surface wrap pts */
	int*		num_wrap_pts,	/* output: number of intermediate pts */
	int		wrap_axis,	   /* input:  constraint axis */
	int		wrap_sign,	   /* input:  constraint direction */
	dpMuscleWrapStruct* mwrap, /* in/out: muscle wrap structure */
	int*		p_flag,		   /* output: did wrapping occur? */
	dpWrapObject*	wo)         /* input:  pointer to the cylinder wrap object */
{
#if 0
   if (wo->wrap_algorithm == 0)
#endif
      return _spiral_wrap_cylinder(p11, p22, p0, dn, r, len, rlen, r1, r2, wrap_pts, num_wrap_pts,
                                   wrap_axis, wrap_sign, mwrap, p_flag, wo);
#if 0
   // planar wrapping no longer supported
   else
      return _planar_wrap_cylinder(p11, p22, p0, dn, r, rlen, r1, r2, wrap_pts, num_wrap_pts,
                                   wrap_axis, wrap_sign, mwrap, p_flag, wo);
#endif
}

#if 0
  #pragma mark -
  #pragma mark SPIRAL WRAPPING CODE
#endif
extern dpWrapObject *gWo;
/* -------------------------------------------------------------------------
   _spiral_wrap_cylinder - 
---------------------------------------------------------------------------- */
static int _spiral_wrap_cylinder (
	double		p1[3],	  /* input:  muscle point 1 */
	double		p2[3],	  /* input:  muscle point 2 */
   double		p0[3],     /* input:  point on cylinder axis */
	double		dn[3],     /* input:  direction vector of cyl axis */
	double		r,         /* input:  cylinder radius */
	double		len,       /* input:  cylinder length */
	double*		rlen,		  /* output: length of surface wrap */
	double		r1[],		  /* output: wrap tangent point 1 */
	double		r2[],		  /* output: wrap tangent point 2 */
	double**	wrap_pts,	  /* output: intermediate surface wrap pts */
	int*		num_wrap_pts, /* output: number of intermediate pts */
	int		wrap_axis,	  /* input:  constraint axis */
	int		wrap_sign,	  /* input:  constraint direction */
	dpMuscleWrapStruct* mwrap, /* in/out: muscle wrap structure */
	int*		p_flag,		  /* output: did wrapping occur? */
	dpWrapObject*	wo)        /* input:  pointer to cylinder wrap object */
{
   double dist, pp[3], vv[3], uu[3], r1a[3], r1b[3], r2a[3], r2b[3],
          r1am[3], r1bm[3], r2am[3], r2bm[3], p11_dist, p22_dist, t, t1, t2, apex[3],
          dot1, dot2, dot3, dot4, plane_normal[3], d, sum_musc[3], sin_theta,
          p11[3], p22[3], *r11, *r22, r1p[3], r2p[3], alpha, beta, r_squared = SQR(r);
   
   double dist1, dist2, axispt[3], vert1[3], vert2[3], mpt[3], apex1[3], apex2[3], l1[3], l2[3];

   double near12[3], t12, mag12,
          near00[3], t00, mag00, p00[3];
   
   int i, return_code = E_WRAPPED;
   
   dpBoolean r1_inter, r2_inter;
   
   dpBoolean constrained   = (dpBoolean) (wrap_sign != 0);
   dpBoolean far_side_wrap = dpNo, long_wrap = dpNo;

#if VISUAL_WRAPPING_DEBUG
   gWo = wo;
   wo->num_debug_glyphs = 0;
   enable_debug_shapes(yes);
#endif

   *p_flag       = FALSE;
   *rlen         = 0.0;
   *num_wrap_pts = 0;
   *wrap_pts     = NULL;
   
   /* abort if p1 or p2 is inside the cylinder. */
   if (get_distsqr_point_line(p1, p0, dn) < r_squared ||
       get_distsqr_point_line(p2, p0, dn) < r_squared)
   {
      return E_INSIDE_RADIUS;
   }
         
   /* Find the closest intersection between the muscle line and the axis of the
    * cylinder. This intersection is used in several places further down in the
    * code to check for various wrapping conditions.
    */
   for (i = 0; i < 3; i++)
      p00[i] = p0[i] + dn[i];

   intersect_lines_scaled(p1, p2, p0, p00, near12, &t12, &mag12, near00, &t00, &mag00);

   /* abort if the cylinder is unconstrained and p1p2 misses the cylinder.
    * Use the return values from the above call to intersect_lines_scaled()
    * to perform the check.
    */
   if ( ! constrained)
   {
      if (distancesqr_between_vertices(near12, near00) < r_squared && t12 > 0.0 && t12 < mag12)
      {
         return_code = E_MANDATORY_WRAP;
      }
      else
      {
         return E_NO_WRAP;
      }
   }

   /* find points p11 & p22 on the cylinder axis closest p1 & p2: */
   get_point_from_point_line(p1, p0, dn, p11);
   get_point_from_point_line(p2, p0, dn, p22);
   
   /* find preliminary tangent point candidates r1a & r1b: */
   MAKE_3DVECTOR(p11, p1, vv);
   
   p11_dist = normalize_vector(vv, vv);
   
   sin_theta = r / p11_dist;
   
   dist = r * sin_theta;
   
   for (i = 0; i < 3; i++)
      pp[i] = p11[i] + dist * vv[i];

   dist = sqrt(r_squared - SQR(dist));

   cross_vectors(dn, vv, uu);
   
   for (i = 0; i < 3; i++)
   {
      r1a[i] = pp[i] + dist * uu[i];
      r1b[i] = pp[i] - dist * uu[i];
   }

   /* find preliminary tangent point candidates r2a & r2b: */
   MAKE_3DVECTOR(p22, p2, vv);
   
   p22_dist = normalize_vector(vv, vv);
   
   sin_theta = r / p22_dist;
   
   dist = r * sin_theta;
   
   for (i = 0; i < 3; i++)
      pp[i] = p22[i] + dist * vv[i];

   dist = sqrt(r_squared - SQR(dist));

   cross_vectors(dn, vv, uu);
   
   for (i = 0; i < 3; i++)
   {
      r2a[i] = pp[i] + dist * uu[i];
      r2b[i] = pp[i] - dist * uu[i];
   }
   
#if VISUAL_WRAPPING_DEBUG
   {
      double tmp1[3], tmp2[3];

      COPY_1X3VECTOR(p1, tmp1);
      COPY_1X3VECTOR(p11, tmp2);
      //transform_pt(wo->from_local_xform, tmp1);
      //transform_pt(wo->from_local_xform, tmp2);
      add_debug_line(gWo, 1.0, tmp1, tmp2, 1, "", "p11", white);

      COPY_1X3VECTOR(p2, tmp1);
      COPY_1X3VECTOR(p22, tmp2);
      //transform_pt(wo->from_local_xform, tmp1);
      //transform_pt(wo->from_local_xform, tmp2);
      add_debug_line(gWo, 1.0, tmp1, tmp2, 1, "", "p22", white);

      COPY_1X3VECTOR(p11, tmp1);
      COPY_1X3VECTOR(r1a, tmp2);
      //transform_pt(wo->from_local_xform, tmp1);
      //transform_pt(wo->from_local_xform, tmp2);
      add_debug_line(gWo, 1.0, tmp1, tmp2, 1, "", "r1a", white);

      COPY_1X3VECTOR(r1b, tmp2);
      //transform_pt(wo->from_local_xform, tmp2);
      add_debug_line(gWo, 1.0, tmp1, tmp2, 1, "", "r1b", white);

      COPY_1X3VECTOR(p22, tmp1);
      COPY_1X3VECTOR(r2a, tmp2);
      //transform_pt(wo->from_local_xform, tmp1);
      //transform_pt(wo->from_local_xform, tmp2);
      add_debug_line(gWo, 1.0, tmp1, tmp2, 1, "", "r2a", white);

      COPY_1X3VECTOR(r2b, tmp2);
      //transform_pt(wo->from_local_xform, tmp2);
      add_debug_line(gWo, 1.0, tmp1, tmp2, 1, "", "r2b", white);
   }
   /*
   add_debug_line(gWo, 1.0, p11, p1, 1, "p11", "", pink);
   add_debug_line(gWo, 1.0, p22, p2, 1, "p22", "", pink);

   add_debug_line(gWo, 1.0, p11, r1a, 1, "", "r1a", white);
   add_debug_line(gWo, 1.0, p11, r1b, 1, "", "r1b", white);

   add_debug_line(gWo, 1.0, p22, r2a, 1, "", "r2a", white);
   add_debug_line(gWo, 1.0, p22, r2b, 1, "", "r2b", white);
   */
#endif

   /* choose the best preliminary tangent points r1 & r2 from the 4 candidates. */
   if (constrained)
   {
      double sum_r[3];

      if (DSIGN(p1[wrap_axis]) == wrap_sign || DSIGN(p2[wrap_axis]) == wrap_sign)
      {
         /* If either muscle point is on the constrained side, then check for intersection
          * of the muscle line and the cylinder. If there is an intersection, then
          * you've found a mandatory wrap. If not, then if one point is not on the constrained
          * side and the closest point on the line is not on the constrained side, you've
          * found a potential wrap. Otherwise, there is no wrap.
          * Use the return values from the previous call to intersect_lines_scaled()
          * to perform these checks.
          */
         if (distancesqr_between_vertices(near12, near00) < r_squared && t12 > 0.0 && t12 < mag12)
         {
            return_code = E_MANDATORY_WRAP;
         }
         else
         {
            if (DSIGN(p1[wrap_axis]) != DSIGN(p2[wrap_axis]) && DSIGN(near12[wrap_axis]) != wrap_sign)
            {
               return_code = E_WRAPPED;
            }
            else
            {
               return E_NO_WRAP;
            }
         }
      }

      MAKE_3DVECTOR(p11, r1a, r1am);
      MAKE_3DVECTOR(p11, r1b, r1bm);
      MAKE_3DVECTOR(p22, r2a, r2am);
      MAKE_3DVECTOR(p22, r2b, r2bm);

      alpha = compute_angle_between_vectors(r1am, r2bm);
      beta = compute_angle_between_vectors(r1bm, r2am);

      /* check to see which of the four tangent points should be chosen by seeing which
       * ones are on the 'active' portion of the cylinder. If r1a and r1b are both on or
       * both off the active portion, then use r2a and r2b to decide.
       */
      if (DSIGN(r1a[wrap_axis]) == wrap_sign && DSIGN(r1b[wrap_axis]) == wrap_sign)
      {
         if (DSIGN(r2a[wrap_axis]) == wrap_sign)
         {
            COPY_1X3VECTOR(r1b, r1);
            COPY_1X3VECTOR(r2a, r2);
            if (alpha > beta)
               far_side_wrap = dpNo;
            else
               far_side_wrap = dpYes;
         }
         else
         {
            COPY_1X3VECTOR(r1a, r1);
            COPY_1X3VECTOR(r2b, r2);
            if (alpha > beta)
               far_side_wrap = dpYes;
            else
               far_side_wrap = dpNo;
         }
      }
      else if (DSIGN(r1a[wrap_axis]) == wrap_sign && DSIGN(r1b[wrap_axis]) != wrap_sign)
      {
         COPY_1X3VECTOR(r1a, r1);
         COPY_1X3VECTOR(r2b, r2);
         if (alpha > beta)
            far_side_wrap = dpYes;
         else
            far_side_wrap = dpNo;
      }
      else if (DSIGN(r1a[wrap_axis]) != wrap_sign && DSIGN(r1b[wrap_axis]) == wrap_sign)
      {
         COPY_1X3VECTOR(r1b, r1);
         COPY_1X3VECTOR(r2a, r2);
         if (alpha > beta)
            far_side_wrap = dpNo;
         else
            far_side_wrap = dpYes;
      }
      else if (DSIGN(r1a[wrap_axis]) != wrap_sign && DSIGN(r1b[wrap_axis]) != wrap_sign)
      {
         if (DSIGN(r2a[wrap_axis]) == wrap_sign)
         {
            COPY_1X3VECTOR(r1b, r1);
            COPY_1X3VECTOR(r2a, r2);
            if (alpha > beta)
               far_side_wrap = dpNo;
            else
               far_side_wrap = dpYes;
         }
         else if (DSIGN(r2b[wrap_axis]) == wrap_sign)
         {
            COPY_1X3VECTOR(r1a, r1);
            COPY_1X3VECTOR(r2b, r2);
            if (alpha > beta)
               far_side_wrap = dpYes;
            else
               far_side_wrap = dpNo;
         }
         else // none of the four tangent points is on the active portion
         {
            if (alpha > beta)
            {
               COPY_1X3VECTOR(r1a, r1);
               COPY_1X3VECTOR(r2b, r2);
               far_side_wrap = dpYes;
            }
            else
            {
               COPY_1X3VECTOR(r1b, r1);
               COPY_1X3VECTOR(r2a, r2);
               far_side_wrap = dpYes;
            }
         }
      }
      /* determine if the resulting tangent points create a short wrap
       * (less than half the cylinder) or a long wrap.
       */
      for (i = 0; i < 3; i++)
      {
         sum_musc[i] = (r1[i] - p1[i]) + (r2[i] - p2[i]);
         sum_r[i] = (r1[i] - p11[i]) + (r2[i] - p22[i]);
      }
      
      if (DOT_VECTORS(sum_r, sum_musc) < 0.0)
         long_wrap = dpYes;
   }
   else
   {
      MAKE_3DVECTOR(p11, r1a, r1am);
      MAKE_3DVECTOR(p11, r1b, r1bm);
      MAKE_3DVECTOR(p22, r2a, r2am);
      MAKE_3DVECTOR(p22, r2b, r2bm);

      normalize_vector(r1am, r1am);
      normalize_vector(r1bm, r1bm);
      normalize_vector(r2am, r2am);
      normalize_vector(r2bm, r2bm);

      dot1 = DOT_VECTORS(r1am, r2am);
      dot2 = DOT_VECTORS(r1am, r2bm);
      dot3 = DOT_VECTORS(r1bm, r2am);
      dot4 = DOT_VECTORS(r1bm, r2bm);

      if (dot1 > dot2 && dot1 > dot3 && dot1 > dot4)
      {
         COPY_1X3VECTOR(r1a, r1);
         COPY_1X3VECTOR(r2a, r2);
         r11 = r1b;
         r22 = r2b;
      }
      else if (dot2 > dot3 && dot2 > dot4)
      {
         COPY_1X3VECTOR(r1a, r1);
         COPY_1X3VECTOR(r2b, r2);
         r11 = r1b;
         r22 = r2a;
      }
      else if (dot3 > dot4)
      {
         COPY_1X3VECTOR(r1b, r1);
         COPY_1X3VECTOR(r2a, r2);
         r11 = r1a;
         r22 = r2b;
      }
      else
      {
         COPY_1X3VECTOR(r1b, r1);
         COPY_1X3VECTOR(r2b, r2);
         r11 = r1a;
         r22 = r2a;
      }
   }

   /* bisect angle between r1 & r2 vectors to find the apex edge of the
    * cylinder:
    */
   MAKE_3DVECTOR(p11, r1, uu);
   MAKE_3DVECTOR(p22, r2, vv);

   for (i = 0; i < 3; i++)
      vv[i] = uu[i] + vv[i];
   
#if VISUAL_WRAPPING_DEBUG
   add_debug_line(gWo, 1.0, origin, vv, 2, "", "vv", cyan);
#endif
   normalize_vector(vv, vv);

#if 0
   if (far_side_wrap /*&& DOT_VECTORS(vv, sum_musc) < 0.0*/)
      t = -1.0;
   else
      t = 1.0;

   for (i = 0; i < 3; i++)
      apex[i] = p11[i] + t * r * vv[i];

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(gWo, 1.0, origin, apex, 2, "", "apex0", blue);
#endif
#endif

   // find the apex point by using a ratio of the lengths of the
   // p1-p11 and p2-p22 segments:
   t = p11_dist / (p11_dist + p22_dist);

   // find point along muscle line according to calculated t value
   for (i = 0; i < 3; i++)
      mpt[i] = p1[i] + t * (p2[i] - p1[i]);

   // find closest point on cylinder axis to mpt
   get_point_from_point_line(mpt, p0, dn, axispt);

   // find normal of plane through p1, p2, axispt
   MAKE_3DVECTOR(axispt, p1, l1);
   MAKE_3DVECTOR(axispt, p2, l2);

   normalize_vector(l1, l1);
   normalize_vector(l2, l2);

   cross_vectors(l1, l2, plane_normal);
   normalize_vector(plane_normal, plane_normal);

   // cross plane normal and cylinder axis (each way) to
   // get vectors pointing from axispt towards mpt and
   // away from mpt (you can't tell which is which yet).
   cross_vectors(dn, plane_normal, vert1);
   normalize_vector(vert1, vert1);
   cross_vectors(plane_normal, dn, vert2);
   normalize_vector(vert2, vert2);

   // now find two potential apex points, one along each vector
   for (i = 0; i < 3; i++)
   {
      apex1[i] = axispt[i] + r * vert1[i];
      apex2[i] = axispt[i] + r * vert2[i];
   }

   // Now use the distance from these points to mpt to
   // pick the right one.
   dist1 = distancesqr_between_vertices(mpt, apex1);
   dist2 = distancesqr_between_vertices(mpt, apex2);
   if (far_side_wrap)
   {
      if (dist1 < dist2)
      {
         for (i = 0; i < 3; i++)
            apex[i] = apex2[i];
      }
      else
      {
         for (i = 0; i < 3; i++)
            apex[i] = apex1[i];
      }
   }
   else
   {
      if (dist1 < dist2)
      {
         for (i = 0; i < 3; i++)
            apex[i] = apex1[i];
      }
      else
      {
         for (i = 0; i < 3; i++)
            apex[i] = apex2[i];
      }
   }

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(gWo, 1.0, axispt, apex, 2, "", "apx", cyan);
#endif

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(gWo, 1.0, p1, apex, 2, "p1", "", yellow);
   add_debug_line(gWo, 1.0, p2, apex, 2, "p2", "", yellow);
#endif

   /* determine how far to slide the preliminary r1/r2 along their
    * "edge of tangency" with the cylinder by intersecting the p1-ax
    * line with the plane formed by p1, p2, and apex:
    */
   MAKE_3DVECTOR(apex, p1, uu);
   MAKE_3DVECTOR(apex, p2, vv);
   
   normalize_vector(uu, uu);
   normalize_vector(vv, vv);
   
   cross_vectors(uu, vv, plane_normal);
   normalize_vector(plane_normal, plane_normal);
   
   d = - p1[0] * plane_normal[0] - p1[1] * plane_normal[1] - p1[2] * plane_normal[2];
   
   for (i = 0; i < 3; i++)
   {
      r1a[i] = r1[i] - 10.0 * dn[i];
      r2a[i] = r2[i] - 10.0 * dn[i];
      
      r1b[i] = r1[i] + 10.0 * dn[i];
      r2b[i] = r2[i] + 10.0 * dn[i];
   }
   
   r1_inter = intersect_line_plane01(r1a, r1b, plane_normal, d, r1p, &t1);
   r2_inter = intersect_line_plane01(r2a, r2b, plane_normal, d, r2p, &t2);

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(gWo, 1.0, r1, r1p, 2, "", "r1p", white);
   add_debug_line(gWo, 1.0, r2, r2p, 2, "", "r2p", white);
#endif

   if (r1_inter)
   {
      get_point_from_point_line(r1p, p11, p22, r1a);

      if (distancesqr_between_vertices(r1a, p22) < distancesqr_between_vertices(p11, p22))
         for (i = 0; i < 3; i++)
            r1[i] = r1p[i];
   }

   if (r2_inter)
   {
      get_point_from_point_line(r2p, p11, p22, r2a);

      if (distancesqr_between_vertices(r2a, p11) < distancesqr_between_vertices(p22, p11))
         for (i = 0; i < 3; i++)
            r2[i] = r2p[i];
   }

   /* Now that you have r1 and r2, check to see if they are beyond the
    * [display] length of the cylinder. If both are, there should be
    * no wrapping. Since the axis of the cylinder is the Z axis, and
    * the cylinder is centered on Z=0, check the Z components of r1 and r2
    * to see if they are within len/2.0 of zero.
    */
   if ((r1[ZZ] < -len/2.0 || r1[ZZ] > len/2.0) && (r2[ZZ] < -len/2.0 || r2[ZZ] > len/2.0))
      return E_NO_WRAP;

    // make the path and calculate the muscle length:
   _make_spiral_path(p1, p2, p0, dn, r, r1, r2, long_wrap, rlen, wrap_pts, num_wrap_pts, wo);

   *p_flag = TRUE;

   return return_code;

} /* _spiral_wrap_cylinder */

/* -------------------------------------------------------------------------
   _make_spiral_path - this routine calculates wrapping points along a
      spiral path from r1 to r2.
   
   IMPORTANT:  if necessary this routine will slide r1 and r2 axially along
      the cylinder's surface to acheive tangency to within 1 degree at r1
      and r2.
---------------------------------------------------------------------------- */

static void _make_spiral_path (
	double		p1[3],		/* input:  muscle point 1		*/
	double		p2[3],		/* input:  muscle point 2		*/
        double		p0[3],          /* input:  point on cylinder axis       */
	double		dn[3],          /* input:  direction vector of cyl axis */
	double		r,              /* input:  cylinder radius              */
	double		r1[],		/* input:  wrap tangent point 1		*/
	double		r2[],		/* input:  wrap tangent point 2		*/
	dpBoolean	far_side_wrap,	/* input:  is it a far side wrap?	*/
	double*		rlen,		/* output: length of surface wrap	*/
	double**	wrap_pts,	/* output: intermediate surface wrap pts*/
	int*		num_wrap_pts,	/* output: number of intermediate pts	*/
	dpWrapObject*	wo)
{

   double r1a[3], r2a[3], uu[3], vv[3], ax[3], x,y, axial_vec[3], axial_dist, theta, *wrap_pt;
   
   double sense = far_side_wrap ? -1.0 : 1.0;
   
   double m[4][4];
   
   int i, iterations = 0;

restart_spiral_wrap:

   /* determine the axial vector: */

   get_point_from_point_line(r1, p0, dn, r1a);
   get_point_from_point_line(r2, p0, dn, r2a);

   MAKE_3DVECTOR(r1a, r2a, axial_vec);
   
   axial_dist = VECTOR_MAGNITUDE(axial_vec);
   
   /* determine the radial angle: */
   MAKE_3DVECTOR(r1a, r1, uu);
   MAKE_3DVECTOR(r2a, r2, vv);
   
#if VISUAL_WRAPPING_DEBUG && 0
   {
      /* use this debug code to understand how iterating to tangency at r1 & r2
       * works:
       */
      static float clr[MAX_ITERATIONS][3];
      
      if (iterations == 0)
      {
         for (i = 0; i < MAX_ITERATIONS; i++)
         {
            clr[i][0] = 1.0;
            clr[i][1] = (float) i / MAX_ITERATIONS;
            clr[i][2] = (i == 0) ? 1.0 : (float) i / MAX_ITERATIONS;
         }
      }
      add_debug_line(wo, 1.0, r1a, r1, 1, "", "", yellow);
      add_debug_line(wo, 1.0, r2a, r2, 1, "", "", yellow);
   }
#endif
   
   for (i = 0; i < 3; i++)
   {
      uu[i] /= r;
      vv[i] /= r;
   }

   theta = compute_angle_between_vectors(uu,vv);

   if (far_side_wrap)
      theta = 2.0 * M_PI - theta;
   
   /* use pythagorus to calculate the length of the spiral path (imaging
    * a right triangle wrapping around the surface of a cylinder):
    */
   x = r * theta;
   y = axial_dist;
   
   *rlen = sqrt(SQR(x) + SQR(y));
   
   /* build path segments:
    */
   *num_wrap_pts = NUM_WRAP_SEGS + 1;
   
   if (*wrap_pts == NULL)
      *wrap_pts = (double*) simm_malloc(*num_wrap_pts * 3 * sizeof(double));

   cross_vectors(uu, vv, ax);
   normalize_vector(ax, ax);
   
   cross_vectors(ax, uu, vv);
   
   m[0][XX] = ax[XX]; m[0][YY] = ax[YY]; m[0][ZZ] = ax[ZZ]; m[0][WW] = 0.0;
   m[1][XX] = uu[XX]; m[1][YY] = uu[YY]; m[1][ZZ] = uu[ZZ]; m[1][WW] = 0.0;
   m[2][XX] = vv[XX]; m[2][YY] = vv[YY]; m[2][ZZ] = vv[ZZ]; m[2][WW] = 0.0;
   m[3][XX] = 0.0;    m[3][YY] = 0.0;    m[3][ZZ] = 0.0;    m[3][WW] = 1.0;
   
   for (i = 0, wrap_pt = *wrap_pts; i < *num_wrap_pts; i++, wrap_pt += 3)
   {
      double t = (double) i / NUM_WRAP_SEGS;
      
      _calc_spiral_wrap_point(r1a, axial_vec, m, ax, r, sense, t, theta, wrap_pt);

      /* adjust r1/r2 tangent points if necessary to acheive tangency with
       * the spiral path:
       */
      if (i == 1 && iterations < MAX_ITERATIONS)
      {
         dpBoolean did_adjust_r2 = dpNo,
                  did_adjust_r1 = _adjust_tangent_point(p1, dn, r1, wrap_pt);

         double temp_wrap_pt[3];
         
         _calc_spiral_wrap_point(r1a, axial_vec, m, ax, r, sense, 1.0 - t, theta, temp_wrap_pt);

         did_adjust_r2 = _adjust_tangent_point(p2, dn, r2, temp_wrap_pt);

         if (did_adjust_r1 || did_adjust_r2)
         {
            iterations++;
            
            goto restart_spiral_wrap;
         }
      }
   }
#if 0
   if (iterations > 0)
      fprintf(stderr, "%2d iterations (%s:%d).\n", iterations, __FILE__, __LINE__);
#endif
} /* _make_spiral_path */

/* -------------------------------------------------------------------------
   _calc_spiral_wrap_point - calculate a point along the spiral wrap path.
---------------------------------------------------------------------------- */
static void _calc_spiral_wrap_point (
	const double	r1a[3],
	const double	axial_vec[3],
	double		m[4][4],
	const double	axis[3],
	double		r,
	double		sense,
	double		t,
	double		theta,
	double		wrap_pt[3])
{
   double n[4][4];
   int i;
   
   copy_4x4matrix(m, n);
   
   rotate_matrix_axis_angle(n, axis, sense * t * theta);

   for (i = 0; i < 3; i++)
   {
      double radial_componant = r * n[1][i];
      
      double axial_componant = t * axial_vec[i];
      
      wrap_pt[i] = r1a[i] + radial_componant + axial_componant;
   }
} /* _calc_spiral_wrap_point */

/* -------------------------------------------------------------------------
   _adjust_tangent_point - detect whether the specified tangent point 'r1'
      needs to be adjusted or not.  If so, slide it in the appropriate
      direction and return yes, otherwise return no.
---------------------------------------------------------------------------- */
static dpBoolean _adjust_tangent_point (
	double		p1[3],		/* input:  muscle point 1		*/
	double		dn[3],          /* input:  direction vector of cyl axis */
	double		r1[],		/* input/output:  wrap tangent point 1	*/
	double		w1[])		/* input:  wrap point 1			*/
{

   double pr_vec[3], rw_vec[3], alpha, omega;
   int i;
   dpBoolean did_adust = dpNo;

   MAKE_3DVECTOR(p1, r1, pr_vec);
   MAKE_3DVECTOR(r1, w1, rw_vec);

   normalize_vector(pr_vec, pr_vec);
   normalize_vector(rw_vec, rw_vec);

   alpha = acos(DOT_VECTORS(pr_vec, dn));
   omega = acos(DOT_VECTORS(rw_vec, dn));

   if (fabs(alpha - omega) > TANGENCY_THRESHOLD)
   {
      double p1a[3], w1a[3], p1w1_int[3], p1w1_t, p1aw1a_int[3], p1aw1a_t;
      double save[3];

      get_point_from_point_line(p1, r1, dn, p1a);
      get_point_from_point_line(w1, r1, dn, w1a);

#if VISUAL_WRAPPING_DEBUG & 0
      add_debug_line(gWo, 1.0, p1, r1, 1, "", "", magenta);
      add_debug_line(gWo, 1.0, r1, w1, 1, "", "", green);
      add_debug_line(gWo, 1.0, p1, w1, 1, "", "", yellow);
      add_debug_line(gWo, 1.0, p1a, w1a, 1, "", "", red);
#endif

      intersect_lines(p1, w1, p1a, w1a,
		      p1w1_int, &p1w1_t, p1aw1a_int, &p1aw1a_t);

      for (i = 0; i < 3; i++)
      {
         save[i] = r1[i];
         r1[i] += 1.5 * (p1aw1a_int[i] - r1[i]);
      }

#if VISUAL_WRAPPING_DEBUG & 0
      add_debug_line(gWo, 1.0, save, r1, 1, "", "", blue);
#endif

      did_adust = dpYes;
   }
   return did_adust;

} /* _adjust_tangent_point */

/* -------------------------------------------------------------------------
   _ray_plane_intersetion - 
---------------------------------------------------------------------------- */
static dpBoolean _ray_plane_intersetion (
   double vs[3],  /* input:  plane normal vector */
   double vs4,    /* input:  plane offset */
   double rp[3],  /* input:  ray origin */
   double vv[3],  /* input:  ray vector */
   double r[3])   /* output: ray-plane intersection */
{
   double numerator   = vs[0] * rp[0] + vs[1] * rp[1] + vs[2] * rp[2] + vs4;
   double denominator = vs[0] * vv[0] + vs[1] * vv[1] + vs[2] * vv[2];
   double t;
   int i;
   
   if (EQUAL_WITHIN_ERROR(0.0,denominator))
   {
      if (EQUAL_WITHIN_ERROR(0.0,numerator))
      {
         /* line is contained within the plane */
         for (i = 0; i < 3; i++)
            r[i] = rp[i];
         
         return dpYes;
      }
      /* line is parallel to the plane */
      return dpNo;
   }
   
   t = - numerator / denominator;
   
   for (i = 0; i < 3; i++)
      r[i] = rp[i] + t * vv[i];
   
   return (dpBoolean) (t >= 0.0);
}

#if 0
  #pragma mark -
  #pragma mark FRANS' PLANAR CYLINDER WRAPPING CODE
#endif

#if 0
/* -------------------------------------------------------------------------
   _planar_wrap_cylinder - 
---------------------------------------------------------------------------- */
static int _planar_wrap_cylinder (
	double		p11[3],	  /* input:  muscle point 1 */
	double		p22[3],	  /* input:  muscle point 2 */
   double		p0[3],     /* input:  point on cylinder axis */
	double		dn[3],     /* input:  direction vector of cyl axis */
	double		r,         /* input:  cylinder radius */
	double*		rlen,		  /* output: length of surface wrap */
	double		r1[],		  /* output: wrap tangent point 1 */
	double		r2[],		  /* output: wrap tangent point 2 */
	double**	wrap_pts,	  /* output: intermediate surface wrap pts */
	int*		num_wrap_pts, /* output: number of intermediate pts */
	int		wrap_axis,	  /* input:  constraint axis */
	int		wrap_sign,	  /* input:  constraint direction */
	dpMuscleWrapStruct* mwrap, /* in/out: muscle wrap structure */
	int*		p_flag,		  /* output: did wrapping occur? */
	dpWrapObject*	wo)        /* input:  pointer to cylinder wrap object */
{
   double dp1, dp2, p1p2[3], p2p1[3], rc1[3], ai[3][3], aii[3][3], p2p0[3], al[3],
          c0[3], c1[3], pc[3], pn[3], rc[3], c0p2[3], vs[3], vs4,
          a, p1p0[3], m[3], lax, vv[3], p2p[3], p1m[3], p2pm[3], hv[3],
          ev1[3], ev2[3], ev3[3], ev4[3], f1p2p, f1hp2p, r1p[3], r2p[3], cosa, sina,
          p1[3], p2[3], wrapaxis[3], wrap_direction[3];
   
   int i, j, posdir;
   dpBoolean p1p2Flip = no;

#if VISUAL_WRAPPING_DEBUG
   gWo = wo;
   wo->num_debug_glyphs = 0;
   enable_debug_shapes(yes);
#endif
   
   for (i = 0; i < 3; i++)
   {
      p1[i] = p11[i];
      p2[i] = p22[i];
   }
   
   *p_flag = TRUE;
   *num_wrap_pts = 0;
   *wrap_pts = NULL;
   
   normalize_vector(dn, dn);
   
   /* first check if p1 and p2 are inside the cylinder */
   dp1 = sqrt(SQR((p1[0] - p0[0]) * dn[1] - (p1[1] - p0[1]) * dn[0]) +
	      SQR((p1[1] - p0[1]) * dn[2] - (p1[2] - p0[2]) * dn[1]) +
	      SQR((p1[2] - p0[2]) * dn[0] - (p1[0] - p0[0]) * dn[2]));

   dp2 = sqrt(SQR((p2[0] - p0[0]) * dn[1] - (p2[1] - p0[1]) * dn[0]) +
	      SQR((p2[1] - p0[1]) * dn[2] - (p2[2] - p0[2]) * dn[1]) +
	      SQR((p2[2] - p0[2]) * dn[0] - (p2[0] - p0[0]) * dn[2]));
   
   if ((dp1 - r) < 0.0 || (dp2 - r) < 0.0)
   {
      *p_flag = FALSE;
      *rlen = 0.0;
      return E_SOME_ERROR;
   }

   /* Calculate smallest distance between lines p1p2 and central axis of the cylinder.
    *
    * p0 + l(0) * d - l(1) * rc1 - l(2) * p1p2 = p2
    *
    * (line-pieces connected between p0 and p2)
    * hence:
    *
    * [d -p1p2 - rc1] * [l(0) l(1) l(2)]' = p2 - p0
    *
    * c0 is point on central axis and line perpendicular to p1p2 and d
    * pc is point on p1p2 and line perpendicular to p1p2 and d
    * c1 is point on the line perpendicular to p1p2 and d
    *
    * vs is normal vector to plane through p1, p2 and c1, vs4 is the offset of the plane
    * It is assumed that r1 and r2 are in the same plane (not strictly true but very
    * close)
    */
 
 calc_wrap_plane:
   
   MAKE_3DVECTOR21(p1, p2, p1p2);
   MAKE_3DVECTOR21(p2, p1, p2p1);
   cross_vectors(p2p1, dn, rc1);
   normalize_vector(rc1, rc1);
   
   for (i = 0; i < 3; i++)
   {
      ai[i][0] = dn[i];
      ai[i][1] = -p1p2[i];
      ai[i][2] = -rc1[i];
   }
   
   invert_3x3matrix(ai, aii);
   
   MAKE_3DVECTOR21(p2, p0, p2p0);
   
   for (i = 0; i < 3; i++)
   {
      al[i] = 0.0;
      
      for (j = 0; j < 3; j++)
         al[i] += aii[i][j] * p2p0[j];
   }
   
   for (i = 0; i < 3; i++)
   {
      c0[i] = p0[i] + al[0] * dn[i];
      pc[i] = p2[i] + al[1] * p1p2[i];
   }
   
   MAKE_3DVECTOR21(pc, c0, rc);
   normalize_vector(rc, rc);
   
   /* --- BEGIN: KENNY'S NEW CONSTRAINT CODE (9/2/99)
    */
   if (wrap_sign != 0)
   {
      /* if we are constrained to a hemi-cylinder, then build the 'wrapaxis':
       */
      for (i = 0; i < 3; i++)
         wrapaxis[i] = (i == wrap_axis) ? (double) wrap_sign : 0.0;
      
      /* make sure we are wrapping in the direction of 'wrapaxis' by flipping
       * p1 & p2 and staring over if necessary:
       */
      if (DOT_VECTORS(wrapaxis, rc1) < 0.0)
      {
         for (i = 0; i < 3; i++)
         {
            p1[i] = p22[i];
            p2[i] = p11[i];
         }
         p1p2Flip = yes;
         goto calc_wrap_plane;
      }
#if VISUAL_WRAPPING_DEBUG && 1
      for (i = 0; i < 3; i++)
         wrapaxis[i] *= 0.8 * r;
      
      add_debug_line(wo, 1.0, p0, wrapaxis, 3, "", "", yellow);

      for (i = 0; i < 3; i++)
         wrapaxis[i] /= 0.8 * r;
#endif
   }
   else if (DOT_VECTORS(rc1, rc) < 0.0)
   {
      /* if we are not constrained to a hemi-cylinder AND a far side wrap
       * is detected, then flip p1 & p2 to maintain a near side wrap:
       */
      for (i = 0; i < 3; i++)
      {
         p1[i] = p22[i];
         p2[i] = p11[i];
      }
      p1p2Flip = yes;
      goto calc_wrap_plane;
   }
   /* --- END: KENNY'S NEW CONSTRAINT CODE (9/2/99)
    */
   
   /* if the line p1-p2 passes at the same side as rc1 is pointing (shortest route), 
    * it is checked if the line p1-p2 actually cuts through the cylinder.
    * if it is the longest route, the tangential points must be calculated anyway.
    */
   if (DOT_VECTORS(rc1, rc) > 0.0)
   {
      double aa, bb, cc, dd, ee, ff, b, c, disc, l1, l2, sqrt_disc;
      
      /* r1 = p2 + l1 * (p1-p2) and on cylinder
       * r2 = p2 + l2 * (p1-p2) and on cylinder
       */
      aa = p1p2[0] * dn[1] - p1p2[1] * dn[0];
      bb = (p2[0] - p0[0]) * dn[1] - (p2[1] - p0[1]) * dn[0];
      cc = p1p2[1] * dn[2] - p1p2[2] * dn[1];
      dd = (p2[1] - p0[1]) * dn[2] - (p2[2] - p0[2]) * dn[1];
      ee = p1p2[2] * dn[0] - p1p2[0] * dn[2];
      ff = (p2[2] - p0[2]) * dn[0] - (p2[0] - p0[0]) * dn[2];
      
      a = SQR(aa) + SQR(cc) + SQR(ee);
      b = 2.0 * (aa * bb + cc * dd + ee * ff);
      c = SQR(bb) + SQR(dd) + SQR(ff) - SQR(r);
      
      disc = SQR(b) - 4.0 * a * c;
      
      if (disc < 0.0)
      {
         *p_flag = FALSE;
         *rlen = VECTOR_MAGNITUDE(p1p2);
         return E_SOME_ERROR;
      }
      
      sqrt_disc = sqrt(disc);
      
      l1 = (-b + sqrt_disc) / (2.0 * a);
      l2 = (-b - sqrt_disc) / (2.0 * a);
      
      if ( ! (0.0 <= l1 && l1 <= 1.0) || ! (0.0 <= l2 && l2 <= 1.0))
      {
         *p_flag = FALSE;
         *rlen = VECTOR_MAGNITUDE(p1p2);
         return E_SOME_ERROR;
      }
   }
   
   cross_vectors(p2p1, dn, rc1);
   normalize_vector(rc1, rc1);
   
   normalize_vector(p2p1, pn);
   cross_vectors(pn, rc1, vs);

#if VISUAL_WRAPPING_DEBUG && 1
   for (i = 0; i < 3; i++)
      c1[i] = c0[i] + 1.2 * r * rc1[i];
      
   add_debug_line(wo, 1.0, p1, p2, 2, "p1", "p2", yellow);
   add_debug_line(wo, 1.0, c0, c1, 2, "", "rc1", pink);
   add_debug_line(wo, 1.0, c0, pc, 3, "c0", "pc", white);
   add_debug_point (wo, 1.0, p0, 0.0005, "p0", red);
#endif

   for (i = 0; i < 3; i++)
      c1[i] = c0[i] + 2.0 * r * rc1[i];
      
   vs4 = - DOT_VECTORS(vs, c1);

   /* comments in a foreign language here */
   MAKE_3DVECTOR21(p2, p0, p2p0);
   
   a = DOT_VECTORS(vs, p2p0) / DOT_VECTORS(vs, dn);
   
   for (i = 0; i < 3; i++)
      c0[i] = p0[i] + a * dn[i];
   
   MAKE_3DVECTOR21(c0, p2, c0p2);
   a = DOT_VECTORS(pn, c0p2);
   
   for (i = 0; i < 3; i++)
      pc[i] = a * pn[i] + p2[i];
   
   MAKE_3DVECTOR21(pc, c0, rc);

   if (DOT_VECTORS(rc1, rc) > 0.0 && VECTOR_MAGNITUDE(rc) >= r)
   {
      *p_flag = FALSE;
      *rlen = VECTOR_MAGNITUDE(p2p1);
      return E_SOME_ERROR;
   }
   
   /* project p1 ... */
   MAKE_3DVECTOR21(p1, p0, p1p0);
   a = DOT_VECTORS(dn, p1p0);
   
   for (i = 0; i < 3; i++)
      m[i] = p0[i] + a * dn[i];
   
   /* comments in a foreign language here */
   lax = DOT_VECTORS(dn, p2p1);
   
   for (i = 0; i < 3; i++)
   {
      vv[i] = lax * dn[i];
      p2p[i] = p2[i] - vv[i];
   }
   
   /* comments in a foreign language here */
   MAKE_3DVECTOR21(p1, m, p1m);
   MAKE_3DVECTOR21(p2p, m, p2pm);
   MAKE_3DVECTOR21(p2p, p1, hv);

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(wo, 1.0, c0, pc, 3, "c0", "pc", white);
   add_debug_line(wo, 1.0, p1, m, 2, "", "", pink);
   add_debug_line(wo, 1.0, p2p, m, 2, "", "m", magenta);
   add_debug_line(wo, 1.0, p2p, p1, 2, "p2\'", "", yellow);
   
   simm_printf(no, "rc < r (%s), dot(p2\'p1, p1m) > 0 (%s), dot(p2\'p1, p2\'m) < 0 (%s)\n",
      VECTOR_MAGNITUDE(rc) < r ? "*" : " ",
      DOT_VECTORS(hv, p1m) > 0.0 ? "*" : " ",
      DOT_VECTORS(hv, p2pm) < 0.0 ? "*" : " ");
#endif
   
   if (VECTOR_MAGNITUDE(rc) < r && (DOT_VECTORS(hv, p1m) > 0.0 || DOT_VECTORS(hv, p2pm) < 0.0))
   {
      *p_flag = FALSE;
      *rlen = VECTOR_MAGNITUDE(p2p1);
      return E_SOME_ERROR;
   }
   
   /* comments in a foreign language here */
   normalize_vector(p1m, ev1);
   cross_vectors(dn, ev1, ev2);
   
   f1p2p = polang(ev1, ev2, p2pm);
   f1hp2p = polang(ev1, ev2, rc1);
   
   /* comments in a foreign language here */
   posdir = f1hp2p < f1p2p;
   
   a = VECTOR_MAGNITUDE(p1m);
   
   if (a <= r)
   {
      for (i = 0; i < 3; i++)
         r1p[i] = p1[i];
   }
   else
   {
      /* comments in a foreign language here */
      cosa = r / a;
      sina = sqrt(1.0 - SQR(cosa));
      
      for (i = 0; i < 3; i++)
         hv[i] = m[i] + cosa * r * ev1[i];
      
      if (posdir)
         for (i = 0; i < 3; i++)
            r1p[i] = hv[i] + sina * r * ev2[i];
      else
         for (i = 0; i < 3; i++)
            r1p[i] = hv[i] - sina * r * ev2[i];
   }
   
   /* comments in a foreign language here */
   a = VECTOR_MAGNITUDE(p2pm);
   
   if (a <= r)
   {
      for (i = 0; i < 3; i++)
         r2p[i] = p2p[i];
   }
   else
   {
      normalize_vector(p2pm, ev3);
      cosa = r / a;
      sina = sqrt(1.0 - SQR(cosa));
      cross_vectors(dn, ev3, ev4);
      
      for (i = 0; i < 3; i++)
         hv[i] = m[i] + cosa * r * ev3[i];
      
      if (posdir)
         for (i = 0; i < 3; i++)
            r2p[i] = hv[i] - sina * r * ev4[i];
      else
         for (i = 0; i < 3; i++)
            r2p[i] = hv[i] + sina * r * ev4[i];
   }

#if VISUAL_WRAPPING_DEBUG && 1
   add_debug_line(wo, 1.0, r1p, m, 2, "r1p", "m", magenta);
   add_debug_line(wo, 1.0, r2p, m, 2, "r2p", "", magenta);
#endif

   /* determine r1 & r2 given r1p, r2p, and vv:
    */
   if (p1p2Flip)
   {
      _ray_plane_intersetion(vs, vs4, r1p, vv, r2);
      _ray_plane_intersetion(vs, vs4, r2p, vv, r1);
   }
   else
   {
      _ray_plane_intersetion(vs, vs4, r1p, vv, r1);
      _ray_plane_intersetion(vs, vs4, r2p, vv, r2);
   }
   
#if VISUAL_WRAPPING_DEBUG && 1
   {
      double _rc1[3], _rc2[3], _vsx[3], _vsy[3], _vsz[3];
      
      MAKE_3DVECTOR21(r1, c0, _rc1);
      MAKE_3DVECTOR21(r2, c0, _rc2);
      normalize_vector(_rc1, _rc1);
      normalize_vector(_rc2, _rc2);
      
      for (i = 0; i < 3; i++)
         _vsx[i] = _rc1[i];
      
      cross_vectors(_rc1, _rc2, _vsz);
      normalize_vector(_vsz, _vsz);
      cross_vectors(_vsz, _vsx, _vsy);
      
      for (i = 0; i < 3; i++)
      {
         _vsx[i] = c0[i] + 0.04 * _vsx[i];
         _vsy[i] = c0[i] + 0.04 * _vsy[i];
         _vsz[i] = c0[i] + 0.04 * _vsz[i];
      }
      add_debug_line(wo, 1.0, c0, _vsx, 2, "", "xx", magenta);
      add_debug_line(wo, 1.0, c0, _vsy, 2, "", "yy", magenta);
      add_debug_line(wo, 1.0, c0, _vsz, 2, "", "zz", magenta);
   }
#endif

   /* compute wrap direction if necessary */
   if (wrap_sign != 0)
   {
      /* if wrapping is constrained to a hemi-cylinder, then compute the
       * desired direction of the wrap path by adding the p1r1 and p2r2
       * vectors together:   -- KMS 9/2/99
       */
      double p1r1[3], p2r2[3];
      
      MAKE_3DVECTOR21(r1, p1, p1r1);
      MAKE_3DVECTOR21(r2, p2, p2r2);
      normalize_vector(p1r1, p1r1);
      normalize_vector(p2r2, p2r2);
      
      for (i = 0; i < 3; i++)
         wrap_direction[i] = p1r1[i] + p2r2[i];
      
      normalize_vector(wrap_direction, wrap_direction);
      
#if VISUAL_WRAPPING_DEBUG
      add_debug_line(wo, 1.0, c0, wrap_direction, 3, "", "", pink);
      
      simm_printf(no, "dot: %.4f\n", DOT_VECTORS(wrap_direction, wrapaxis));
#endif
      
      if (DOT_VECTORS(wrap_direction, wrapaxis) < -0.5)
      {
         /* avoid for situation in which the overall wrap direction is
          * opposite the user-specified wrap axis:   -- KMS 9/2/99
          */
         *p_flag = FALSE;
         *rlen = VECTOR_MAGNITUDE(p2p1);
         return E_SOME_ERROR;
      }
   }
   
   /* compute wrap path line segments */
   dcyl(p0, dn, r, r1, r2, c0, wrap_sign == 0 ? NULL : wrap_direction,
        rlen, wrap_pts, num_wrap_pts);
   
   /* store the center point and tangent points for next time */
   for (i = 0; i < 3; i++)
   {
      mwrap->c[i]  = c1[i];
      mwrap->r1[i] = r1[i];
      mwrap->r2[i] = r2[i];
   }
   
   return E_NO_ERROR;

} /* _planar_wrap_cylinder */

/* -------------------------------------------------------------------------
   polang - 
   
   THIS IS THE COMMENT FROM FRANS' CODE:
     ev1 and ev2 should be orthonormal
     polang gives the angle in radians from ev1 in the direction of ev2
     until the length of p.
---------------------------------------------------------------------------- */
static double polang (double ev1[3], double ev2[3], double p[3])
{
   double q[3], cosa, sina, hk;
   
   normalize_vector(p, q);
   cosa = DOT_VECTORS(q, ev1);
   sina = DOT_VECTORS(q, ev2);
   
   if (fabs(sina) < fabs(cosa))
   {
      hk = asin(sina);
      
      if (cosa < 0.0)
         hk = M_PI - hk;
      
      if (hk < 0.0)
         hk += 2 * M_PI;
   }
   else
   {
      hk = acos(cosa);
      
      if (sina < 0.0)
         hk = 2 * M_PI - hk;
   }
   return hk;
}

/* -------------------------------------------------------------------------
   dcyl - find wrapping line segments along cylindrical surface.
---------------------------------------------------------------------------- */
static void dcyl (
        const double	p0[3],          /* input:  point on cylinder axis       */
	const double	dn[3],          /* input:  direction vector of cyl axis */
	double		r,              /* input:  cylinder radius              */
	const double	r1[3],		/* input:  tangent point 1		*/
	const double	r2[3],		/* input:  tangent point 2		*/
	const double	c0[3],		/* input:  special pt. on cylinder axis	*/
	const double    wrapaxis[3],	/* input:  optional constraint axis	*/
	double*		rlen,		/* output: length of wrap path		*/
	double**	wrap_pts,	/* output: intermediate surface wrap pts*/
	int*		num_wrap_pts)	/* output: number of intermediate pts	*/
{
   double rc1[3], rc2[3], phi0, dphi, vsx[3], vsy[3], vsz[3], r0[3][3], ux[3],
          rphi[3][3], s[100][3], p[3], q[3], dv[3];
   
   int i,j,k,l;
   
   MAKE_3DVECTOR21(r1, c0, rc1);
   MAKE_3DVECTOR21(r2, c0, rc2);
   normalize_vector(rc1, rc1);
   normalize_vector(rc2, rc2);
   
   for (i = 0; i < 3; i++)
      vsx[i] = rc1[i];

   cross_vectors(rc1, rc2, vsz);
   normalize_vector(vsz, vsz);
   cross_vectors(vsz, vsx, vsy);

   /* compute phi0, the wrap angle, and then optionally flip phi0 to wrap
    * around the far side if necessary:   -- KMS 9/7/99
    */
   phi0 = acos(DOT_VECTORS(rc1, rc2));
   
   if (wrapaxis && DOT_VECTORS(vsy, wrapaxis) < 0.0)
      phi0 = -(2 * M_PI - phi0);      /* flip phi to wrap over the far side */

   dphi = phi0 / 100.0;
   
   for (i = 0; i < 3; i++)
   {
      r0[i][0] = vsx[i];
      r0[i][1] = vsy[i];
      r0[i][2] = vsz[i];
   }

   clear_vector(ux, 3);

   ux[0] = 1.0;

   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
	 rphi[i][j] = 0.0;

   rphi[2][2] = 1.0;

   for (i = 0; i < 100; i++)
   {
      double aa, bb, cc, dd, ee, ff, a, b, c, disc, mu;
      
      double ri[3], phi = (i+1) * dphi;
      
      rphi[0][0] = cos(phi);
      rphi[0][1] = -sin(phi);
      rphi[1][0] = sin(phi);
      rphi[1][1] = cos(phi);

      for (j = 0; j < 3; j++)
      {
	 double t[3];
	 
	 ri[j] = 0.0;
	 
	 for (k = 0; k < 3; k++)
	 {
	    t[k] = 0.0;
	    
	    for (l = 0; l < 3; l++)
	       t[k] += rphi[k][l] * ux[l];
	    
	    ri[j] += r0[j][k] * t[k];
	 }
      }

      aa = ri[0] * dn[1] - ri[1] * dn[0];
      bb = (c0[0] - p0[0]) * dn[1] - (c0[1] - p0[1]) * dn[0];
      cc = ri[1] * dn[2] - ri[2] * dn[1];
      dd = (c0[1] - p0[1]) * dn[2] - (c0[2] - p0[2]) * dn[1];
      ee = ri[2] * dn[0] - ri[0] * dn[2];
      ff = (c0[2] - p0[2]) * dn[0] - (c0[0] - p0[0]) * dn[2];
      
      a = SQR(aa) + SQR(cc) + SQR(ee);
      b = 2.0 * (aa * bb + cc * dd + ee * ff);
      c = SQR(bb) + SQR(dd) + SQR(ff) - SQR(r);
      disc = SQR(b) - 4.0 * a * c;
      
      mu = (-b + sqrt(disc)) / (2.0 * a);
	    
      for (j = 0; j < 3; j++)
	 s[i][j] = c0[j] + mu * ri[j];
   }

   *num_wrap_pts = 101;
   *wrap_pts = (double*) simm_malloc(*num_wrap_pts * 3 * sizeof(double));

   (*wrap_pts)[0] = r1[0];
   (*wrap_pts)[1] = r1[1];
   (*wrap_pts)[2] = r1[2];

   (*wrap_pts)[(*num_wrap_pts - 1) * 3    ] = r2[0];
   (*wrap_pts)[(*num_wrap_pts - 1) * 3 + 1] = r2[1];
   (*wrap_pts)[(*num_wrap_pts - 1) * 3 + 2] = r2[2];

   for (i = 0; i < *num_wrap_pts - 2; i++)
   {
      int index = (i+1) * 3;
      
      (*wrap_pts)[index    ] = s[i][0];
      (*wrap_pts)[index + 1] = s[i][1];
      (*wrap_pts)[index + 2] = s[i][2];
   }

   *rlen = 0.0;

   p[0] = s[0][0];
   p[1] = s[0][1];
   p[2] = s[0][2];

   MAKE_3DVECTOR21(p, r1, dv);

   *rlen += VECTOR_MAGNITUDE(dv);

   for (i = 0; i < 99; i++)
   {
      p[0] = s[i][0];
      p[1] = s[i][1];
      p[2] = s[i][2];

      q[0] = s[i+1][0];
      q[1] = s[i+1][1];
      q[2] = s[i+1][2];

      MAKE_3DVECTOR21(q, p, dv); 

      *rlen += VECTOR_MAGNITUDE(dv);
   }
   
} /* dcyl */
#endif
