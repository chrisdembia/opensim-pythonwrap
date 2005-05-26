/*******************************************************************************

   WRAPPING.C

   Authors: Ken Smith
            Peter Loan

   Copyright (c) 1999-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains routines that deal with wrapping
      muscle points. A wrapping point is a muscle point which is
      active (turned on) only for certain joint angles. They are a
      temporary fix for muscles that wrap around bone. Specifically
      these routines determine which wrapping points in a given
      muscle should be turned on, and if one is turned off, what the
      new 'current point' should be, in the muscle editor tool.

   Routines:
      check_wrapping_points     : determines which points in a muscle are active
      check_wrap_objects        : checks for intersection between muscle and wrap object
      wrap_muscle_seg           : wraps a muscle segment over a wrap object
      calc_muscle_length_change : calculates the change in length due to wrapping

*******************************************************************************/

#include "universal.h"

/*************** DEFINES (for this file only) *********************************/

/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/

/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;

/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/
static int wrap_muscle_seg(dpMuscleStruct* ms, dpWrapObject* wo, dpWrapParams* wp, dpMuscleWrapStruct* ws);
static double calc_muscle_length_change (dpMuscleStruct* ms, dpWrapObject* wo, dpWrapParams* wp);
static void check_wrap_objects (dpMuscleStruct* ms);

/* -------------------------------------------------------------------------
   check_wrapping_points - traverse the muscle's list of muscle points,
      updating wrapping points if necessary.
---------------------------------------------------------------------------- */
void check_wrapping_points(dpMuscleStruct* ms, double state[])
{

   int i, j, genc;
   double value;
   OnOffSwitch ptState;

#if 0 /* Always check wrapping because some gencoord values may have changed. */
   if (ms->wrap_calced == yes)
      return;

   ms->wrap_calced = yes;
#endif

   /* Start out with no points, and then set an mp[] point to each point
    * in mp_orig[] that is active.
    */
   ms->num_points = 0;

   for (i = 0; i < *(ms->num_orig_points); i++)
   {
      ptState = on;
      for (j = 0; j < ms->mp_orig[i].numranges; j++)
      {
         genc = ms->mp_orig[i].ranges[j].genc;
         value = state[genc] * sdm->q[genc].conversion;
         if (value < ms->mp_orig[i].ranges[j].start || value > ms->mp_orig[i].ranges[j].end)
         {
            ptState = off;
            break;
         }
      }
      if (ptState == on)
      {
         ms->mp[ms->num_points++] = &ms->mp_orig[i];
      }
   }

   /* The mp[] array now contains a list of all the user-defined points that are active.
    * Now use that list to check for intersection with the wrap objects.
    */
   check_wrap_objects(ms);

} /* check_wrapping_points */

/* -------------------------------------------------------------------------
   check_wrap_objects - check the muscle for intersection with its associated
      wrap object.  Currently a muscle can wrap over only one wrap object.
      If this is a multi-segment muscle, then choose the "best" muscle segment
      to wrap over the wrap object.
---------------------------------------------------------------------------- */
static void check_wrap_objects(dpMuscleStruct* ms)
{
   int i, j, k, kk, pt1, pt2, maxIterations;
   int start, end, wrapStart, wrapEnd, numActiveWraps;
   double min_length_change, last_length;
   dpWrapParams best_wrap = {-1, -1, NULL};
   dpMusclePoint *smp, *emp, *fmp, *lmp;
   dpMuscleWrapStruct* ws;
   dpWrapObject* wo;
   int *result, *order;

   for (i = 0, numActiveWraps = 0; i < ms->numWrapStructs; i++)
      if (ms->wrapStruct[i]->wrap_object->active == dpYes)
         numActiveWraps++;

   if (numActiveWraps == 0)
      return;

   result = (int*)simm_malloc(ms->numWrapStructs * sizeof(int));
   order = (int*)simm_malloc(ms->numWrapStructs * sizeof(int));

   /* Set the initial order to be the order they are listed in the muscle. */
   for (i = 0; i < ms->numWrapStructs; i++)
      order[i] = i;

   /* If there is only one active wrap object, calculate the wrapping only once.
    * If there are two or more objects, perform up to 8 iterations where
    * the result from one wrap object is used as the starting point for
    * the next wrap.
    */
   if (numActiveWraps < 2)
      maxIterations = 1;
   else
      maxIterations = 8;

   for (kk = 0, last_length = DBL_MAX; kk < maxIterations; kk++)
   {
      for (i = 0; i < ms->numWrapStructs; i++)
      {
         result[i] = 0;
         ws = ms->wrapStruct[order[i]];
         wo = ws->wrap_object;
         best_wrap.wrap_pts = NULL;
         min_length_change = DBL_MAX;

         if (wo->active == dpYes)
         {
            /* First remove this object's wrapping points from the current muscle path
             */
            for (j = 0; j < ms->num_points; j++)
            {
               if (ms->mp[j] == &ws->mp_wrap[0])
               {
                  for (k = j; k < ms->num_points - 2; k++)
                  {
                     ms->mp[k] = ms->mp[k+2];
                  }
                  ms->num_points -= 2;
                  break;
               }
            }

            /* startPoint and endPoint in wrapStruct represent the user-defined
             * starting and ending points in the array of muscle points that should
             * be considered for wrapping. These indices take into account via points,
             * whether or not they are active. Thus they are indices into mp_orig[],
             * not mp[] (also, mp[] may contain wrapping points from previous wrap
             * objects, which would mess up the starting and ending indices). But the
             * goal is to find starting and ending indices in mp[] to consider for
             * wrapping over this wrap object. Here is how that is done:
             */

            /* 1. startPoint and endPoint are 1-based, so subtract 1 from them to get
             * indices into mp_orig[]. -1 (or any value less than 1) means use the first
             * (or last) point.
             */
            if (ws->startPoint < 1)
               wrapStart = 0;
            else
               wrapStart = ws->startPoint - 1;

            if (ws->endPoint < 1)
               wrapEnd = *ms->num_orig_points - 1;
            else
               wrapEnd = ws->endPoint - 1;

            /* 2. Store pointers to the user-defined starting and ending muscle points,
             * and the first and last points in mp_orig[].
             */
            smp = &ms->mp_orig[wrapStart];
            emp = &ms->mp_orig[wrapEnd];
            fmp = &ms->mp_orig[0];
            lmp = &ms->mp_orig[*ms->num_orig_points - 1];

            /* 3. Now scan forward from wrapStart (in the mp[] array) to find the first
             * point in mp_orig[] that is active. As you scan forward, skip over
             * mp_wrap[] points (this is what the fmp and lmp bounds are for). This code
             * assumes that mp_orig[] is a continuous block in memory.
             */
            for (j = 0; j < ms->num_points; j++)
            {
               if (ms->mp[j] >= smp && ms->mp[j] >= fmp && ms->mp[j] <= lmp)
               {
                  start = j;
                  break;
               }
            }

            /* 4. Now scan backwards from wrapEnd (in the mp[] array) to find the last
             * point in mp_orig[] that is active. As you scan backwards, skip over
             * mp_wrap[] points (this is what the fmp and lmp bounds are for). This code
             * assumes that mp_orig[] is a continuous block in memory.
             */
            for (j = ms->num_points - 1; j >= 0; j--)
            {
               if (ms->mp[j] <= emp && ms->mp[j] >= fmp && ms->mp[j] <= lmp)
               {
                  end = j;
                  break;
               }
            }

            /* You now have indices into mp[] (which is a list of all currently active points,
             * including wrap points) that represent the used-defined range of points to consider
             * for wrapping over this wrap object. Check each muscle segment in this range, choosing
             * the best wrap as the one that changes the muscle segment length the least:
             */
            for (pt1 = start; pt1 < end; pt1++)
            {
               pt2 = pt1 + 1;

               /* As long as the two points are not auto wrap points on the
                * same wrap object, check them for wrapping.
                */
               if (ms->mp[pt1]->is_auto_wrap_point == dpNo || ms->mp[pt1]->num_wrap_pts > 0 ||
                  ms->mp[pt2]->is_auto_wrap_point == dpNo || ms->mp[pt2]->num_wrap_pts == 0)
               {
                  dpWrapParams wp = { -1, -1, NULL };

                  wp.start = pt1;
                  wp.end   = pt2;

                  result[i] = wrap_muscle_seg(ms, wo, &wp, ws);
                  if (result[i] == E_MANDATORY_WRAP)
                  {
                     /* E_MANDATORY_WRAP means the muscle line actually intersected
                      * the wrap object. In this case, you *must* choose this segment
                      * as the "best" one for wrapping. If the muscle has more than
                      * one segment that intersects the object, the first one is taken
                      * as the mandatory wrap (this is considered an ill-conditioned case).
                      */
                     FREE_IFNOTNULL(best_wrap.wrap_pts);
                     best_wrap = wp;
                     break;
                  }
                  else if (result[i] == E_WRAPPED)
                  {
                     /* E_WRAPPED means the muscle segment was wrapped over the object,
                      * but you should consider the other segments as well to see if one
                      * wraps with a smaller length change.
                      */
                     double muscle_length_change = calc_muscle_length_change(ms, wo, &wp);

                     if (muscle_length_change < min_length_change)
                     {
                        FREE_IFNOTNULL(best_wrap.wrap_pts);
                        best_wrap = wp;
                        min_length_change = muscle_length_change;
                     }
                     else
                     {
                        FREE_IFNOTNULL(wp.wrap_pts);
                     }
                  }
                  else
                  {
                  }
               }
            }

            /* deallocate previous wrapping points if necessary: */
            FREE_IFNOTNULL(ws->mp_wrap[1].wrap_pts);

            if (best_wrap.wrap_pts == NULL)
            {
               if (ws)
               {
                  for (j = 0; j < 3; j++)
                  {
                     ws->c[j]  = MINMDOUBLE;
                     ws->r1[j] = MINMDOUBLE;
                     ws->r2[j] = MINMDOUBLE;
                  }
               }
            }
            else
            {
               /* if wrapping did occur, copy wrap information into the MuscleStruct */
               ws->mp_wrap[0].wrap_pts = NULL;
               ws->mp_wrap[0].num_wrap_pts = 0;

               ws->mp_wrap[1].wrap_pts = best_wrap.wrap_pts;
               ws->mp_wrap[1].num_wrap_pts = best_wrap.num_wrap_pts;

               ws->mp_wrap[0].segment = wo->segment;
               ws->mp_wrap[1].segment = wo->segment;
               ws->mp_wrap[0].is_auto_wrap_point = dpYes;
               ws->mp_wrap[1].is_auto_wrap_point = dpYes;
               ws->mp_wrap[0].wrap_distance = 0.0;
               ws->mp_wrap[1].wrap_distance = best_wrap.wrap_path_length;

               for (j = 0; j < 3; j++)
               {
                  ws->mp_wrap[0].point[j] = best_wrap.r1[j];
                  ws->mp_wrap[1].point[j] = best_wrap.r2[j];
               }

               /* Now insert the two new wrapping points into the mp[] array.
                * mp[] is already be large enough to hold the two points.
                */
               for (j = ms->num_points + 1; j > best_wrap.end + 1; j--)
                  ms->mp[j] = ms->mp[j-2];

               ms->mp[best_wrap.end] = &ws->mp_wrap[0];
               ms->mp[best_wrap.end+1] = &ws->mp_wrap[1];

               ms->num_points += 2;
            }
         }
      }
      calc_muscle_tendon_length(ms);

      if (DABS(ms->muscle_tendon_length - last_length) < 0.0001)
      {
         break;
      }
      else
      {
         last_length = ms->muscle_tendon_length;
      }

      if (kk == 0 && ms->numWrapStructs > 1)
      {
         /* If the first wrap was a no wrap, and the second was a no wrap
          * because a point was inside the object, switch the order of
          * the first two objects and try again.
          */
         if (result[0] == E_NO_WRAP && result[1] == E_INSIDE_RADIUS)
         {
            order[0] = 1;
            order[1] = 0;

            // remove wrap object 0 from the list of muscle points
            ws = ms->wrapStruct[0];
            for (j = 0; j < ms->num_points; j++)
            {
               if (ms->mp[j] == &ws->mp_wrap[0])
               {
                  for (k = j; k < ms->num_points - 2; k++)
                  {
                     ms->mp[k] = ms->mp[k+2];
                  }
                  ms->num_points -= 2;
                  break;
               }
            }
         }
      }
   }

   FREE_IFNOTNULL(result);
   FREE_IFNOTNULL(order);

} /* check_wrap_objects */


/* -------------------------------------------------------------------------
   wrap_muscle_seg - 
---------------------------------------------------------------------------- */
static int wrap_muscle_seg(dpMuscleStruct* ms, dpWrapObject* wo, dpWrapParams* wp, dpMuscleWrapStruct* ws)
{

   static double origin[] = {0,0,0}, axis[] = {0,0,1};
   int i, p_flag, return_code;
   double pt1[4], pt2[4], npt1[4], npt2[4], tpt1[4], tpt2[4];

   for (i = 0; i < 3; i++)
   {
      pt1[i] = ms->mp[wp->start]->point[i];
      pt2[i] = ms->mp[wp->end]->point[i];
   }

   convert_point(pt1,ms->mp[wp->start]->segment,wo->segment);
   convert_point(pt2,ms->mp[wp->end]->segment,wo->segment);

   pt1[3] = pt2[3] = 1.0;
   mult_4x4matrix_by_vector(wo->to_local_xform,pt1,npt1);
   mult_4x4matrix_by_vector(wo->to_local_xform,pt2,npt2);

   if (wo->wrap_type == dpWrapSphere)
   {
       return_code = calc_line_intersect_sphere(npt1, npt2,
                                                origin, wo->radius[0],
                                                &wp->wrap_path_length,
                                                tpt1, tpt2,
                                                &wp->wrap_pts, &wp->num_wrap_pts,
                                                wo->wrap_axis, wo->wrap_sign,
                                                ws, &p_flag, NULL);
   }
   else if (wo->wrap_type == dpWrapEllipsoid)
   {
       return_code = calc_line_intersect_ellipsoid(npt1, npt2,
                                                   origin, wo->radius,
                                                   &wp->wrap_path_length,
                                                   tpt1, tpt2,
                                                   &wp->wrap_pts, &wp->num_wrap_pts,
                                                   wo->wrap_axis, wo->wrap_sign,
                                                   ws, &p_flag, NULL);
   }
   else if (wo->wrap_type == dpWrapCylinder)
   {
       return_code = calc_line_intersect_cylinder(npt1, npt2,
                                                  origin, axis, wo->radius[0],
                                                  wo->height,
                                                  &wp->wrap_path_length,
                                                  tpt1, tpt2,
                                                  &wp->wrap_pts, &wp->num_wrap_pts,
                                                  wo->wrap_axis, wo->wrap_sign,
                                                  ws, &p_flag, NULL);
   }
   else if (wo->wrap_type == dpWrapTorus)
   {
       return_code = calc_line_intersect_torus(npt1, npt2,
                                               origin, wo->radius,
                                               &wp->wrap_path_length,
                                               tpt1, tpt2,
                                               &wp->wrap_pts, &wp->num_wrap_pts,
                                               wo->wrap_axis, wo->wrap_sign,
                                               ws, &p_flag, NULL);
   }
   else
   {
       return_code = E_NO_WRAP;
       p_flag = 0;
   }

   if (p_flag == 1 && return_code > 0)
   {
      tpt1[3] = tpt2[3] = 1.0;
      mult_4x4matrix_by_vector(wo->from_local_xform,tpt1,wp->r1);
      mult_4x4matrix_by_vector(wo->from_local_xform,tpt2,wp->r2);
   }

   return return_code;

} /* wrap_muscle_seg */

/* -------------------------------------------------------------------------
   calc_muscle_length_change - given the output of a successful muscle wrap
      over a wrap object, determine the percent change in length of the
      muscle segment incurred by wrapping.
---------------------------------------------------------------------------- */
static double calc_muscle_length_change (dpMuscleStruct* ms, dpWrapObject* wo, dpWrapParams* wp)
{
   int i;

   double p1[3], p2[3], straight_length, wrap_length = 0.0;

   for (i = 0; i < 3; i++)
   {
      p1[i] = ms->mp[wp->start]->point[i];
      p2[i] = ms->mp[wp->end]->point[i];
   }
   convert_point(p1,ms->mp[wp->start]->segment,wo->segment);
   convert_point(p2,ms->mp[wp->end]->segment,wo->segment);

   straight_length = sqrt(distancesqr_between_vertices(p1, p2));

   wrap_length += sqrt(distancesqr_between_vertices(p1, wp->r1));
   wrap_length += wp->wrap_path_length;
   wrap_length += sqrt(distancesqr_between_vertices(wp->r2, p2));

   return wrap_length / straight_length;
}


dpWrapObject* get_wrap_object(char name[])
{

   int i;

   for (i = 0; i < sdm->num_wrap_objects; i++)
      if (STRINGS_ARE_EQUAL(name, sdm->wrap_object[i].name))
         return (&sdm->wrap_object[i]);

   return NULL;

}


dpWrapObject* get_muscle_wrap_object(dpMuscleStruct* ms, dpMusclePoint* mpt)
{
   if (ms)
   {
      int i;

      /* Go through the array of wrap structs for this muscle. If the mpt pointer
       * points to one of the two wrap points in the wrap struct, then you've found
       * the wrap struct that matches mpt. Return the pointer to the wrap object.
       */
      for (i = 0; i < ms->numWrapStructs; i++)
         if (mpt == &ms->wrapStruct[i]->mp_wrap[0] || mpt == &ms->wrapStruct[i]->mp_wrap[1])
            return ms->wrapStruct[i]->wrap_object;
   }

   return NULL;
}


dpBoolean onSameWrapObject(dpMuscleStruct* ms, int pt1, int pt2)
{

   if (sdm->num_wrap_objects > 0)
   {
      if (ms->mp[pt1]->is_auto_wrap_point == dpYes && ms->mp[pt2]->is_auto_wrap_point == dpYes)
      {
         dpWrapObject *wo1, *wo2;

         wo1 = get_muscle_wrap_object(ms, ms->mp[pt1]);
         wo2 = get_muscle_wrap_object(ms, ms->mp[pt2]);

         if (wo1 && wo2 && wo1 == wo2)
            return dpYes;
      }
   }

   return dpNo;
}
