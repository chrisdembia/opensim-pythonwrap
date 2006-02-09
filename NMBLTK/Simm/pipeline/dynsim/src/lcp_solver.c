/*******************************************************************************

   LCP_SOLVER.C

   Author: Krystyne Blaikie

   Copyright (c) 2000-2004 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains functions used to find contact forces and
      impulses at all contact points between bodies in the system. Problems
      are formulated as LCP's and solved using the method described by Baraff
      (Fast Contact Force Computation for Rigid Bodies.  SIGGRAPH 1994).
	
   Routines:
      compute_contact_forces: compute accelerations and forces at all cont points
      create_A_matrix:        creates matrix with masses and contact geometries
      body_in_contact:        checks if body is in contact node
      solve_LCP:              main routine for Baraff's LCP algorithm
      has_neg_members:        checks if a contact has negative elements
      drive_to_zero:          used by LCP code
      fdirection:             used by LCP code
      maxstep:                used by LCP code

*******************************************************************************/	
#include "universal.h"

#if CONTACT_DETECTION

/******************************** DEFINES *************************************/
#define TINY		2e-10		/*1e-10*/
#define MAXDIST	1e10	/* infinity */


/*************************** EXTERNAL VARIABLES *******************************/
extern dpModelStruct* sdm;

/********************** STATIC FUNCTION PROTOTYPES ****************************/
static void create_A_matrix(double *A[], dpContactInfo list[], int n);
static dpBoolean body_in_contact(int body, dpContactInfo cont, double pt[3], double norm[3]);
static void solve_LCP(double *A[], double f[], double a[], int n);
static int has_neg_members(double vec[], int n, double thresh, int *which);
static void drive_to_zero(double *A[], double a[], double f[], int C_set[], 
	                       int NC_set[], int d, int n);
static void fdirection(double *A[], int C_set[], double delta_f[], int d, int n);
static int maxstep(double f[], double delta_f[], double delta_a[], double a[],
	                int C_set[], int NC_set[], int d, int n, double *s);

void compute_contact_forces(int compute_impact)
{
   int i, j, n, *index;
   double *f, *a, **A;
   dpContactInfo *list;

   /* allocate space for a list of all contact points to use when
    * solving for forces and a list of the indices for each element
    * in the list
    */
   n = sdm->num_bilat_contacts + sdm->num_contacts;
   index = (int *) simm_malloc(n * sizeof(int));
   list = (dpContactInfo *)simm_malloc(n * sizeof(dpContactInfo));
	
   /* copy bilateral contacts into list */
   for (i = 0; i < sdm->num_bilat_contacts; i++)
   {
      index[i] = -2;
      copy_cnode(sdm->bilat_contacts[i], &list[i]);
      list[i].acc = 0.0;
   }

   n = sdm->num_bilat_contacts;

   /* copy contacts into list, store the index of the point
	 * if computing RESTING CONTACT forces - only use resting contact points.
	 * if computing IMPACT forces - use impact and resting contact points.
    * Never use SEPARATING contacts since no force is applied to them
    */
   for (i = 0; i < sdm->num_contacts; i++)
   {		
      if ((compute_impact && 
         (sdm->contacts[i].contact_type != dpSeparatingContact)) ||
         (!compute_impact && 
         (sdm->contacts[i].contact_type == dpRestingContact)))
      {
         index[n] = i;
         copy_cnode(sdm->contacts[i], &list[n]);
         n++;
      }
   }

   if (n <= sdm->num_bilat_contacts)
      goto cleanup2;

   /* dynamically allocate necessary arrays */
   f = (double *)simm_malloc(n * sizeof(double));
   a = (double *)simm_malloc(n * sizeof(double));
   A = (double **)simm_malloc(n * sizeof(double *));

   for (i = 0; i < n; i++)
      A[i] = (double *)simm_malloc(n * sizeof(double));
		
   for (i = 0; i < n; i++)
   {
      f[i] = 0.0;
      a[i] = list[i].acc;
      for (j = 0; j < n; j++)
         A[i][j] = 0.0;
   }

   create_A_matrix(A, list, n);

   /* solve the linear complementarity problem:  new_acc = A*f + initial_acc
	 * return with the calculated forces and accelerations in f and a
    */
   solve_LCP(A, f, a, n);

   /* copy force information back into contact list */
   for (i = 0; i < n; i++)
   {
      if (index[i] >= 0)
      {
         sdm->contacts[index[i]].acc = a[i];
         sdvmul(f[i], sdm->contacts[index[i]].outward_norm, 
            sdm->contacts[index[i]].cont_frc);
      }
      else
      {
         sdm->bilat_contacts[i].acc = a[i];
         sdvmul(f[i], sdm->bilat_contacts[i].outward_norm, sdm->bilat_contacts[i].cont_frc);
      }
   }

cleanup1:
   free(a);
   free(f);
   for (i = 0; i < n; i++)
      free(A[i]);
   free(A);

cleanup2:
   free(list);
   free(index);
	
   check_for_sderror("COMPUTE CONTACT FORCES");
}


/* create A matrix reflecting the masses and contact geometries of the system */
static void create_A_matrix(double *A[], dpContactInfo list[], int n)
{
   int body, r, c;
   double inertia[3][3], inv_inertia[3][3], inv_mass;
   double pt_c[3], pt_r[3], norm_c[3], norm_r[3];
   double r_cross_n[3], alpha[3];
   double ang_acc[3], lin_acc[3], total_acc[3], component_in_r_dir;

	/* go through all the bodies, if the body occurs in contact r and contact c
	 * the contact force at c contributes to the acceleration at r
	 */
	for (body = 0; body < sdm->num_body_segments; body++)
	{
		copy_3x3matrix(sdm->body_segment[body].inertia, inertia);
		if (zero_3x3matrix(inertia) == dpYes)
			make_3x3matrix(inv_inertia, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		else 
			invert_3x3matrix(inertia, inv_inertia);

		if (sdm->body_segment[body].mass == 0.0) 
			inv_mass = 0.0;
		else
			inv_mass = 1.0/sdm->body_segment[body].mass;

		for (r = 0; r < n; r++)
		{
			for (c = 0; c < n; c++)
			{
				/* the cth contact force can only contribute to the rth normal
				 * separation acceleration if the rth and cth
				 * contacts involve the same body.
             */
				if ((body_in_contact(body, list[c], pt_c, norm_c) == dpYes) && 
					(body_in_contact(body, list[r], pt_r, norm_r) == dpYes))
				{
					sdvcross(pt_c, norm_c, r_cross_n);
               mult_3x3matrix_by_vector(inv_inertia, r_cross_n, alpha);
					sdvcross(alpha, pt_r, ang_acc);
					sdvmul(inv_mass, norm_c, lin_acc);
					sdvadd(lin_acc, ang_acc, total_acc);
					component_in_r_dir = DOT_VECTORS(total_acc, norm_r);
					A[r][c] += component_in_r_dir;
				}
			}
		}
	} /* end for all bodies */
	check_for_sderror("CREATE A MATRIX");
}


/* check whether a given SIMM body index is in the given contact node.  If yes,
 * return the contact point from the body mass center and the normal at the 
 * contact point in the body frame */
static dpBoolean body_in_contact(int body, dpContactInfo cont, double pt[3], double norm[3])
{
	if (body == (cont.body1 + 1))
	{
		sdvcopy(cont.pt1, pt);
		sdvcopy(cont.norm1, norm);
		return dpYes;
	}
	else if (body == (cont.body2 + 1))
	{
		sdvcopy(cont.pt2, pt);
		sdvcopy(cont.norm2, norm);
		return dpYes;
	}
	else
		return dpNo;
}

/* From Baraff - 1994 */
static void solve_LCP(double *A[], double f[], double a[], int n)
{
   int i, d, *C_set, *NC_set, count = 0;
   double threshold = TINY;
	
   /* dynamically allocate arrays */
   C_set = (int *)simm_malloc(n * sizeof(int));
   NC_set = (int *)simm_malloc(n * sizeof(int));

   /* initialize C_set and NC_set to empty */
   for (i = 0; i < n; i++)
      C_set[i] = NC_set[i] = NO;

	/* put bilateral contacts (the first num_bilat_contacts contacts) into C set.
	 * Don't care if their forces become -ve as long as their accelerations
	 * remain 0.0
    */
   for (i = 0; i < sdm->num_bilat_contacts; i++)
      C_set[i] = YES;

	/* keep computing forces until all a's are positive or zero */
   while (has_neg_members(a, n, threshold, &d) && count++ < 500)
   {
      drive_to_zero(A, a, f, C_set, NC_set, d, n);
   }

   /* free space used by dynamically-allocated arrays */
   free(C_set);
   free(NC_set);
}

static int has_neg_members(double vec[], int n, double thresh, int *which)
{
   int i;

   for (i = sdm->num_bilat_contacts; i < n; i++)
   {
      if (vec[i] < -thresh)
      {
         *which = i;
         return YES;
      }
   }
   return NO;
} /* end has_neg_members */


static void drive_to_zero(double *A[], double a[], double f[], int C_set[], 
	int NC_set[], int d, int n)
{
   int r, c, j, count = 0;
   double *delta_f, *delta_a, s, total;

   delta_a = (double *)simm_malloc(n * sizeof(double));
   delta_f = (double *)simm_malloc(n * sizeof(double));

start:

   count++;

   fdirection(A, C_set, delta_f, d, n);

   /* compute delta_a = A * delta_f */
   for (r = 0; r < n; r++)
   {
      total = 0;
      for (c = 0; c < n; c++)
         total += A[r][c] * delta_f[c];
      delta_a[r] = total;
   }

   j = maxstep(f, delta_f, delta_a, a, C_set, NC_set, d, n, &s);

   if (s == MAXDIST)
   {
      sim_message(none, "WARNING in drive_to_zero(): s->infinity.");
      sim_message(none, "SOLUTION CANNOT BE FOUND. TERMINATING.");
      print_contact_list(sdm->contacts, sdm->num_contacts);
      print_contact_list(sdm->bilat_contacts, sdm->num_bilat_contacts); 
      show_array("a", a, 0, n);
      show_array("f", f, 0, n);
      sim_message(exit_program, "lcp_solver.");
   }

   for (r = 0; r < n; r++)
   {
      f[r] += s * delta_f[r];
      a[r] += s * delta_a[r];
   }

   if (count > 50)
   {
      C_set[d] = YES;
      C_set[j] = YES;
      NC_set[j] = NO;
		a[d] = 0.0;
      free(delta_f);
      free(delta_a);
      return;
   }

   if (C_set[j] == YES)
   {
      C_set[j] = NO;
      NC_set[j] = YES;
      goto start;
   }
   else if (NC_set[j] == YES)
   {
      NC_set[j] = NO;
      C_set[j] = YES;
      goto start;
   }
   else
   {
      C_set[j] = YES;
      free(delta_f);
      free(delta_a);
      return;
   }
} /* end drive_to_zero */


static void fdirection(double *A[], int C_set[], double delta_f[], int d, int n)
{
   int r, c, row_ind = 0, col_ind = 0, C_size = 0, *indx;
   double *v_1, **A_11, d2;

   for (r = 0; r < n; r++)
   {
      /* set delta_f = 0 */
      delta_f[r] = 0.;

      /* determine size of Acc */
      if (C_set[r] == YES)
         C_size++;
   }
   delta_f[d] = 1.;

   indx = (int *)simm_malloc(C_size * sizeof(int));
   v_1 = (double *)simm_malloc(C_size * sizeof(double));
   A_11 = (double **)simm_malloc(C_size * sizeof(double *));
   for (r = 0; r < C_size; r++)
      A_11[r] = (double *)simm_malloc(C_size * sizeof(double));

   for (r = 0; r < n; r++)
   {
      if (C_set[r] == YES)
      {
         for (c = 0; c < n; c++)
         {
            if (C_set[c] == YES)
            {
               A_11[row_ind][col_ind] = A[r][c];
               col_ind++;
            }
         }
         v_1[row_ind] = -1 * A[r][d];
         row_ind++;
         col_ind = 0;
      }
   }

   if (C_size > 0)
   { 
      ludcmp(A_11, C_size, indx, &d2);
      lubksb(A_11, C_size, indx, v_1);

      /* transfer solution (in v_1) into delta_f */
      row_ind = 0;
      for (r = 0; r < n; r++)
      {
         if (C_set[r] == YES)
         {
            delta_f[r] = v_1[row_ind];
            row_ind++;
         }
      }
   }
   free(v_1);
   free(indx);
   for (r = 0; r < C_size; r++) free(A_11[r]);
   free(A_11);
}

static int maxstep(double f[], double delta_f[], double delta_a[], double a[],
	int C_set[], int NC_set[], int d, int n, double *s)
{
   int i, j = -1;
   double s_prime;

   *s = MAXDIST;

   if (delta_a[d] > 0.0)
   {
      j = d;
      *s = -1 * a[d]/delta_a[d];
   }

   /* ignore i's related to bilateral contacts */
   for (i = sdm->num_bilat_contacts; i < n; i++)
   {
      if ((C_set[i] == YES) && (delta_f[i] < -TINY))
      {
         s_prime = -1 * f[i] / delta_f[i];
         if (s_prime < (*s - TINY))
         {
            *s = s_prime;
            j = i;
         }
      }

      if ((NC_set[i] == YES) && (delta_a[i] < -TINY))
      {
         s_prime = -1 * a[i] / delta_a[i];
         if (s_prime < (*s - TINY))
         {
            *s = s_prime;
            j = i;
         }
      }
   } /* end for all contacts */

   return j;
}


#endif /* CONTACT_DETECTION */
