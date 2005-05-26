/*******************************************************************************

   SPHERE_WRAP.C

   Authors: Peter Loan
            Ken Smith
            Craig Robinson
            Frans van der Helm.

   Copyright (c) 1994-2004 MusculoGraphics, Inc, a division of Motion Analysis Corp.
   All rights reserved.

   Description: code for wrapping muscle over a sphere

*******************************************************************************/

#include <universal.h>

/*************** DEFINES (for this file only) *********************************/
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




/* to calculate the closest 3d point to given 3d line.
 * the line is defined as vector(vec) and a point(pt)
 * the line has not been normalized to a unit vector
 * the value hypo*(cosalpha) of a rt triangle is found out
 * to get the closest point
 */
static void get_point_from_point_line2(double point[], double pt[], double vec[],
			                              double closest_pt[], double* t)
{

   double v1[3], v2[3];
   double mag, mag2;

   v1[0] = point[0] - pt[0];
   v1[1] = point[1] - pt[1];
   v1[2] = point[2] - pt[2];

   v2[0] = vec[0];
   v2[1] = vec[1];
   v2[2] = vec[2];

   mag = normalize_vector(v1,v1);
   mag2 = normalize_vector(v2,v2);
   *t = DOT_VECTORS(v1,v2) * mag;

   closest_pt[0] = pt[0] + *t * v2[0];
   closest_pt[1] = pt[1] + *t * v2[1];
   closest_pt[2] = pt[2] + *t * v2[2];
   
   *t = *t / mag2;
}



/* Description: Calculates the tangential point r1 of the curved line
 * element k, with origin p1 and insertion p2 around a spherical bony
 * contour with center m and radius r. p_flag == TRUE if there is a 
 * tangent, FALSE if there is no intersection of a straight line
 * between p1 and p2.
 */
int calc_line_intersect_sphere(double p1[], double p2[], double m[],
			       double r, double *rlen, double r1[],
			       double r2[],
			       double** wrap_pts, int *num_wrap_pts,
			       int wrap_axis, int wrap_sign, dpMuscleWrapStruct* mwrap,
			       int *p_flag,
			       dpWrapObject* wo)
{
   double l1, l2, disc, a, b, c, a1, a2, j1, j2, j3, j4, r1r2,
 	ri[3], p2m[3], p1m[3], mp[3], r1n[3], r2n[3],
	p1p2[3], np2[3], hp2[3], r1m[3], r2m[3], y[3], z[3], n[3],
	ra[3][3], rrx[3][3], aa[3][3], r1a[3], r2a[3],
	r1b[3], r2b[3], r1am[3], r2am[3], r1bm[3], r2bm[3],
        mat[4][4], axis[4], vec[4], rotvec[4], angle, dangle, *r11, *r22;

   int i, maxit, index, return_code = E_WRAPPED;
   dpBoolean far_side_wrap = dpNo;

#if VISUAL_WRAPPING_DEBUG
   wo->num_debug_glyphs = 0;
   enable_debug_shapes(yes);
#endif

   maxit = 50;
   *p_flag = TRUE;

   *num_wrap_pts = 0;
   *wrap_pts = NULL;

   MAKE_3DVECTOR21(p1, m, p1m);
   MAKE_3DVECTOR21(p2, m, p2m);
   MAKE_3DVECTOR21(p1, p2, ri);
   MAKE_3DVECTOR21(m, p2, mp);
   MAKE_3DVECTOR21(p1,p2,p1p2);

   /* check that neither point is inside the radius of the sphere */
   if (VECTOR_MAGNITUDE(p1m) < r || VECTOR_MAGNITUDE(p2m) < r)
      return E_INSIDE_RADIUS;

   a = DOT_VECTORS(ri, ri);
   b = -2.0 * DOT_VECTORS(mp, ri);
   c = DOT_VECTORS(mp, mp) - r * r;
   disc = b * b - 4.0 * a * c;

   /* check if there is an intersection of p1p2 and the sphere */
   if (disc < 0.0) 
   {
      *p_flag = FALSE;
      *rlen = 0.0;
      return E_NO_WRAP;
   }

   l1 = (-b + sqrt(disc)) / (2.0 * a);
   l2 = (-b - sqrt(disc)) / (2.0 * a);

   /* check if the intersection is between p1 and p2 */
   if ( ! (0.0 < l1 && l1 < 1.0) || ! (0.0 < l2 && l2 < 1.0))	
   {
      *p_flag = FALSE;
      *rlen = 0.0;
      return E_NO_WRAP;
   }

   if (l1 < l2) 
   {
      *p_flag = FALSE;
      *rlen = 0.0;
      return E_NO_WRAP;
   }

   normalize_vector(p1p2, p1p2);
   normalize_vector(p2m, np2);

   cross_vectors(p1p2, np2, hp2);

   /* if the muscle line passes too close to the center of the sphere
    * then give up
    */
   if (VECTOR_MAGNITUDE(hp2) < 0.00001) 
   {
      /* no wait!  don't give up!  Instead use the previous r1 & r2:
       * -- added KMS 9/9/99
       */
      for (i = 0; i < 3; i++)
      {
         r1[i] = mwrap->r1[i];
         r2[i] = mwrap->r2[i];
      }
      goto calc_path;
   }

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(wo, 1.0, p1, p2, 2, "p1", "p2", yellow);
   add_debug_line(wo, 1.0, p2, m, 2, "", "", pink);
   normalize_vector(hp2, n);
   n[XX] *= r * 1.2;
   n[YY] *= r * 1.2;
   n[ZZ] *= r * 1.2;
   add_debug_line(wo, 1.0, m, n, 2, "", "n", green);
#endif

   /* calc tangent point candidates r1a, r1b */
   normalize_vector(hp2, n);
   MAKE_3DVECTOR21(m, p1, y);
   normalize_vector(y, y);
   cross_vectors(n, y, z);
   
#if VISUAL_WRAPPING_DEBUG
   add_debug_line(wo, 1.0, m, y, 2, "", "y", yellow);
   add_debug_line(wo, 1.0, m, z, 2, "", "z", pink);
#endif

   for (i = 0; i < 3; i++)
   {
      ra[i][0] = n[i];
      ra[i][1] = y[i];
      ra[i][2] = z[i];
   }

   a1 = asin(r / VECTOR_MAGNITUDE(p1m));

   make_3x3_xrot_matrix(a1, rrx);
   mult_3x3matrices(ra, rrx, aa);

   for (i = 0; i < 3; i++)
      r1a[i] = p1[i] + aa[i][1] * VECTOR_MAGNITUDE(p1m) * cos(a1);

   make_3x3_xrot_matrix(-a1, rrx);
   mult_3x3matrices(ra, rrx, aa);

   for (i = 0; i < 3; i++)
      r1b[i] = p1[i] + aa[i][1] * VECTOR_MAGNITUDE(p1m) * cos(a1);

   /* calc tangent point candidates r2a, r2b */
   MAKE_3DVECTOR21(m, p2, y);
   normalize_vector(y, y);
   cross_vectors(n, y, z);

   for (i = 0; i < 3; i++)
   {
      ra[i][0] = n[i];
      ra[i][1] = y[i];
      ra[i][2] = z[i];
   }

   a2 = asin(r / VECTOR_MAGNITUDE(p2m));
   
   make_3x3_xrot_matrix(a2, rrx);
   mult_3x3matrices(ra, rrx, aa);

   for (i = 0; i < 3; i++)
      r2a[i] = p2[i] + aa[i][1] * VECTOR_MAGNITUDE(p2m) * cos(a2);

   make_3x3_xrot_matrix(-a2, rrx);
   mult_3x3matrices(ra, rrx, aa);

   for (i = 0; i < 3; i++)
      r2b[i] = p2[i] + aa[i][1] * VECTOR_MAGNITUDE(p2m) * cos(a2);

#if VISUAL_WRAPPING_DEBUG
   add_debug_line(wo, 1.0, m, r1a, 2, "", "r1a", white);
   add_debug_line(wo, 1.0, m, r1b, 2, "", "r1b", white);
   add_debug_line(wo, 1.0, m, r2a, 2, "", "r2a", white);
   add_debug_line(wo, 1.0, m, r2b, 2, "", "r2b", white);
#endif

   /* determine wrapping tangent points r1 & r2:
    */
   MAKE_3DVECTOR21(r1a, m, r1am);
   MAKE_3DVECTOR21(r1b, m, r1bm);
   MAKE_3DVECTOR21(r2a, m, r2am);
   MAKE_3DVECTOR21(r2b, m, r2bm);
   
   normalize_vector(r1am, r1am);
   normalize_vector(r1bm, r1bm);
   normalize_vector(r2am, r2am);
   normalize_vector(r2bm, r2bm);
   
   {
      /* check which of the tangential points results in the shortest distance */
      j1 = DOT_VECTORS(r1am, r2am);
      j2 = DOT_VECTORS(r1am, r2bm);
      j3 = DOT_VECTORS(r1bm, r2am);
      j4 = DOT_VECTORS(r1bm, r2bm);
       
      if (j1 > j2 && j1 > j3 && j1 > j4)
      {
         COPY_1X3VECTOR(r1a, r1);
         COPY_1X3VECTOR(r2a, r2);
         r11 = r1b;
         r22 = r2b;
      }
      else if (j2 > j3 && j2 > j4)
      {
         COPY_1X3VECTOR(r1a, r1);
         COPY_1X3VECTOR(r2b, r2);
         r11 = r1b;
         r22 = r2a;
      }
      else if (j3 > j4)
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

   if (wrap_sign != 0)
   {
      if (DSIGN(p1[wrap_axis]) == wrap_sign || DSIGN(p2[wrap_axis]) == wrap_sign)
      {
         double tt, mm[3], r_squared = SQR(r);
         
         /* If either muscle point is on the constrained side, then check for intersection
          * of the muscle line and the cylinder. If there is an intersection, then
          * you've found a mandatory wrap. If not, then if one point is not on the constrained
          * side and the closest point on the line is not on the constrained side, you've
          * found a potential wrap. Otherwise, there is no wrap.
          */
         get_point_from_point_line2(m, p1, p1p2, mm, &tt);
         
         tt = -tt; /* because p1p2 is actually p2->p1 */
         
         if (distancesqr_between_vertices(m, mm) < r_squared && tt > 0.0 && tt < 1.0)
         {
            return_code = E_MANDATORY_WRAP;
         }
         else
         {
            if (DSIGN(p1[wrap_axis]) != DSIGN(p2[wrap_axis]) && DSIGN(mm[wrap_axis]) != wrap_sign)
            {
               return_code = E_WRAPPED;
            }
            else
            {
               return E_NO_WRAP;
            }
         }
      }
      
      if (DSIGN(p1[wrap_axis]) != wrap_sign || DSIGN(p2[wrap_axis]) != wrap_sign)
      {
         double wrapaxis[3], sum_musc[3], sum_r[3];
         
         for (i = 0; i < 3; i++)
            wrapaxis[i] = (i == wrap_axis) ? (double) wrap_sign : 0.0;

         /* determine best constrained r1 & r2 tangent points:
          */
         for (i = 0; i < 3; i++)
            sum_musc[i] = (m[i] - p1[i]) + (m[i] - p2[i]);
         
         normalize_vector(sum_musc, sum_musc);
         
         if (DOT_VECTORS(r1am, sum_musc) > DOT_VECTORS(r1bm, sum_musc))
         {
            COPY_1X3VECTOR(r1a, r1);
            r11 = r1b;
         }
         else
         {
            COPY_1X3VECTOR(r1b, r1);
            r11 = r1a;
         }
         
         if (DOT_VECTORS(r2am, sum_musc) > DOT_VECTORS(r2bm, sum_musc))
         {
            COPY_1X3VECTOR(r2a, r2);
            r22 = r2b;
         }
         else
         {
            COPY_1X3VECTOR(r2b, r2);
            r22 = r2a;
         }
         
         /* flip if necessary:
          */
         for (i = 0; i < 3; i++)
            sum_musc[i] = (r1[i] - p1[i]) + (r2[i] - p2[i]);
         
         normalize_vector(sum_musc, sum_musc);
         
         if (DOT_VECTORS(sum_musc, wrapaxis) < 0.0)
         {
            COPY_1X3VECTOR(r11, r1);
            COPY_1X3VECTOR(r22, r2);
         }
         
         /* determine if the resulting tangent points create a far
          * side wrap:
          */
         for (i = 0; i < 3; i++)
         {
            sum_musc[i] = (r1[i] - p1[i]) + (r2[i] - p2[i]);
            
            sum_r[i] = (r1[i] - m[i]) + (r2[i] - m[i]);
         }
         
         if (DOT_VECTORS(sum_r, sum_musc) < 0.0)
            far_side_wrap = dpYes;
      }
   }

 calc_path:
   MAKE_3DVECTOR21(r1, m, r1m);
   MAKE_3DVECTOR21(r2, m, r2m);

   normalize_vector(r1m, r1n);
   normalize_vector(r2m, r2n);

   angle = acos(DOT_VECTORS(r1n, r2n));
   
   if (far_side_wrap)
      angle = -(2 * M_PI - angle);
   
   r1r2 = r * angle;
   *rlen = r1r2;

   cross_vectors(r1n,r2n,axis);
   normalize_vector(axis,axis);
   axis[3] = 1.0;

   *num_wrap_pts = 101;
   *wrap_pts = (double*)simm_malloc((*num_wrap_pts)*3*sizeof(double));

   (*wrap_pts)[0] = r1[0];
   (*wrap_pts)[1] = r1[1];
   (*wrap_pts)[2] = r1[2];

   (*wrap_pts)[((*num_wrap_pts)-1)*3] = r2[0];
   (*wrap_pts)[((*num_wrap_pts)-1)*3+1] = r2[1];
   (*wrap_pts)[((*num_wrap_pts)-1)*3+2] = r2[2];

   vec[0] = r1m[0];
   vec[1] = r1m[1];
   vec[2] = r1m[2];
   vec[3] = 1.0;

   for (i = 0; i < *num_wrap_pts - 2; i++)
   {
      index = (i+1) * 3;
      dangle = angle * (i+1) / (*num_wrap_pts - 1);
      
      make_4x4dircos_matrix(dangle * RTOD, axis, mat);
      mult_4x4matrix_by_vector(mat, vec, rotvec);
      
      (*wrap_pts)[index]   = m[0] + rotvec[0];
      (*wrap_pts)[index+1] = m[1] + rotvec[1];
      (*wrap_pts)[index+2] = m[2] + rotvec[2];
   }
   
   for (i = 0; i < 3; i++)
   {
      mwrap->r1[i] = r1[i];
      mwrap->r2[i] = r2[i];
   }

   return return_code;
}

