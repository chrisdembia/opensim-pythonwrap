/*******************************************************************************

   sdfor.c

   Created by NMBLTS (from model 3DGaitModelSimple)

   Time of creation: 01/05/2007 04:53:30 PM

   Description: This file contains the routines needed to perform a forward
      dynamics simulation of an SD/FAST model. The specific routines that it
      contains depend on the SIMM model from which this code was generated.

*******************************************************************************/

#include "universal.h"
#include "model.h"

/*************** DEFINES (for this file only) *********************************/
#define BAUMGARTE_STAB 20

/* Defines for the joints, Qs, and body segments are now found in model.h */



/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/

/* The following spline-function data points are copied directly from the
 * SIMM joints file.
 */

static double knee_r_tx_data[][2] =
{
{-2.0943951000, -0.0033399100},
{-1.7453292500, 0.0018682600},
{-1.3962634000, 0.0042897000},
{-1.0471975500, 0.0042792600},
{-0.6981317000, 0.0022126900},
{-0.3490658500, -0.0010437200},
{-0.1745329300, -0.0032355400},
{0.1973442200, -0.0054555300},
{0.3373949600, -0.0056726300},
{0.4901775700, -0.0058177000},
{1.5214602700, -0.0056726300},
{2.0943951000, -0.0054795400}
};

static double knee_r_ty_data[][2] =
{
{-2.0943951000, -0.4410767700},
{-1.2217304800, -0.4260471800},
{-0.5235987800, -0.4164449400},
{-0.3490658500, -0.4149837300},
{-0.1745329300, -0.4139400100},
{0.1591485600, -0.4125456000},
{2.0943951000, -0.4133137700}
};

static double tib_pat_r_tx_data[][2] =
{
{-2.0943951000, 0.0161849300},
{-1.3962634000, 0.0303116700},
{-1.0471975500, 0.0356442700},
{-0.6981317000, 0.0402284500},
{-0.3490658500, 0.0438770700},
{-0.1745329300, 0.0452803900},
{0.0000000000, 0.0464030500},
{0.0001745300, 0.0464030500},
{0.0003490700, 0.0464030500},
{0.0872664600, 0.0464030500},
{2.0943951000, 0.0464030500}
};

static double tib_pat_r_ty_data[][2] =
{
{-2.0943951000, -0.0204884400},
{-1.5707963300, -0.0188980100},
{-1.3962634000, -0.0187109100},
{-1.0471975500, -0.0190851200},
{-0.6981317000, -0.0197400100},
{-0.3490658500, -0.0204884400},
{-0.1745329300, -0.0208626600},
{0.0000000000, -0.0212368800},
{0.0001745300, -0.0212368800},
{0.0003490700, -0.0212368800},
{0.0872664600, -0.0212368800},
{2.0943951000, -0.0212368800}
};

static double tib_pat_r_r1_data[][2] =
{
{-2.0943951000, 0.3080506100},
{-1.9999727900, 0.3080506100},
{-1.4575244600, 0.3063052800},
{-0.5263913000, 0.2701769700},
{0.0279252700, -0.0370009800},
{0.1745329300, -0.2799508100}
};

static double knee_l_tx_data[][2] =
{
{-2.0943951000, -0.0033399100},
{-1.7453292500, 0.0018682600},
{-1.3962634000, 0.0042897000},
{-1.0471975500, 0.0042792600},
{-0.6981317000, 0.0022126900},
{-0.3490658500, -0.0010437200},
{-0.1745329300, -0.0032355400},
{0.1973442200, -0.0054555300},
{0.3373949600, -0.0056726300},
{0.4901775700, -0.0058177000},
{1.5214602700, -0.0056726300},
{2.0943951000, -0.0054795400}
};

static double knee_l_ty_data[][2] =
{
{-2.0943951000, -0.4410767700},
{-1.2217304800, -0.4260471800},
{-0.5235987800, -0.4164449400},
{-0.3490658500, -0.4149837300},
{-0.1745329300, -0.4139400100},
{0.1591485600, -0.4125456000},
{2.0943951000, -0.4133137700}
};

static double tib_pat_l_tx_data[][2] =
{
{-2.0943951000, 0.0161849300},
{-1.3962634000, 0.0303116700},
{-1.0471975500, 0.0356442700},
{-0.6981317000, 0.0402284500},
{-0.3490658500, 0.0438770700},
{-0.1745329300, 0.0452803900},
{0.0000000000, 0.0464030500},
{0.0001745300, 0.0464030500},
{0.0003490700, 0.0464030500},
{0.0872664600, 0.0464030500},
{2.0943951000, 0.0464030500}
};

static double tib_pat_l_ty_data[][2] =
{
{-2.0943951000, -0.0204884400},
{-1.5707963300, -0.0188980100},
{-1.3962634000, -0.0187109100},
{-1.0471975500, -0.0190851200},
{-0.6981317000, -0.0197400100},
{-0.3490658500, -0.0204884400},
{-0.1745329300, -0.0208626600},
{0.0000000000, -0.0212368800},
{0.0001745300, -0.0212368800},
{0.0003490700, -0.0212368800},
{0.0872664600, -0.0212368800},
{2.0943951000, -0.0212368800}
};

static double tib_pat_l_r1_data[][2] =
{
{-2.0943951000, 0.3080506100},
{-1.9999727900, 0.3080506100},
{-1.4575244600, 0.3063052800},
{-0.5263913000, 0.2701769700},
{0.0279252700, -0.0370009800},
{0.1745329300, -0.2799508100}
};

static dpSplineFunction knee_r_tx_func;
static dpSplineFunction knee_r_ty_func;
static dpSplineFunction tib_pat_r_tx_func;
static dpSplineFunction tib_pat_r_ty_func;
static dpSplineFunction tib_pat_r_r1_func;
static dpSplineFunction knee_l_tx_func;
static dpSplineFunction knee_l_ty_func;
static dpSplineFunction tib_pat_l_tx_func;
static dpSplineFunction tib_pat_l_ty_func;
static dpSplineFunction tib_pat_l_r1_func;


/**************** GLOBAL VARIABLES (used in only a few files) *****************/
extern dpModelStruct sdm;


/*************** EXTERNED VARIABLES (declared in another file) ****************/



/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/


/* INIT_QS: this routine initializes the array of structures
 * that hold information about the Qs (gencoords).
 */

void init_qs(void)
{

   int i;

   sdm.q = (dpQStruct*)simm_malloc(sdm.nq*sizeof(dpQStruct));
   mstrcpy(&sdm.q[pelvis_tz].name,"pelvis_tz");
   sdm.q[pelvis_tz].type = dpUnconstrainedQ;
   sdm.q[pelvis_tz].joint = ground_pelvis;
   sdm.q[pelvis_tz].axis = 0;
   sdm.q[pelvis_tz].initial_value = 0.0000000000;
   sdm.q[pelvis_tz].initial_velocity = 0.0;
   sdm.q[pelvis_tz].range_start = -3.0000000000;
   sdm.q[pelvis_tz].range_end = 3.0000000000;
   sdm.q[pelvis_tz].restraint_func = NULL;
   sdm.q[pelvis_tz].min_restraint_func = NULL;
   sdm.q[pelvis_tz].max_restraint_func = NULL;
   sdm.q[pelvis_tz].function_active = dpNo;
   sdm.q[pelvis_tz].constraint_func = NULL;
   sdm.q[pelvis_tz].constraint_num = -1;
   sdm.q[pelvis_tz].q_ind = -1;
   sdm.q[pelvis_tz].output = dpYes;
   sdm.q[pelvis_tz].pd_stiffness = 0.0;
   sdm.q[pelvis_tz].torque = 0.0;

   mstrcpy(&sdm.q[pelvis_tx].name,"pelvis_tx");
   sdm.q[pelvis_tx].type = dpUnconstrainedQ;
   sdm.q[pelvis_tx].joint = ground_pelvis;
   sdm.q[pelvis_tx].axis = 1;
   sdm.q[pelvis_tx].initial_value = 0.1200000000;
   sdm.q[pelvis_tx].initial_velocity = 0.0;
   sdm.q[pelvis_tx].range_start = -5.0000000000;
   sdm.q[pelvis_tx].range_end = 5.0000000000;
   sdm.q[pelvis_tx].restraint_func = NULL;
   sdm.q[pelvis_tx].min_restraint_func = NULL;
   sdm.q[pelvis_tx].max_restraint_func = NULL;
   sdm.q[pelvis_tx].function_active = dpNo;
   sdm.q[pelvis_tx].constraint_func = NULL;
   sdm.q[pelvis_tx].constraint_num = -1;
   sdm.q[pelvis_tx].q_ind = -1;
   sdm.q[pelvis_tx].output = dpYes;
   sdm.q[pelvis_tx].pd_stiffness = 0.0;
   sdm.q[pelvis_tx].torque = 0.0;

   mstrcpy(&sdm.q[pelvis_ty].name,"pelvis_ty");
   sdm.q[pelvis_ty].type = dpUnconstrainedQ;
   sdm.q[pelvis_ty].joint = ground_pelvis;
   sdm.q[pelvis_ty].axis = 2;
   sdm.q[pelvis_ty].initial_value = 0.9300000000;
   sdm.q[pelvis_ty].initial_velocity = 0.0;
   sdm.q[pelvis_ty].range_start = -1.0000000000;
   sdm.q[pelvis_ty].range_end = 2.0000000000;
   sdm.q[pelvis_ty].restraint_func = NULL;
   sdm.q[pelvis_ty].min_restraint_func = NULL;
   sdm.q[pelvis_ty].max_restraint_func = NULL;
   sdm.q[pelvis_ty].function_active = dpNo;
   sdm.q[pelvis_ty].constraint_func = NULL;
   sdm.q[pelvis_ty].constraint_num = -1;
   sdm.q[pelvis_ty].q_ind = -1;
   sdm.q[pelvis_ty].output = dpYes;
   sdm.q[pelvis_ty].pd_stiffness = 0.0;
   sdm.q[pelvis_ty].torque = 0.0;

   mstrcpy(&sdm.q[pelvis_tilt].name,"pelvis_tilt");
   sdm.q[pelvis_tilt].type = dpUnconstrainedQ;
   sdm.q[pelvis_tilt].joint = ground_pelvis;
   sdm.q[pelvis_tilt].axis = 3;
   sdm.q[pelvis_tilt].initial_value = 0.0000000000;
   sdm.q[pelvis_tilt].initial_velocity = 0.0;
   sdm.q[pelvis_tilt].range_start = -1.5707963300;
   sdm.q[pelvis_tilt].range_end = 1.5707963300;
   sdm.q[pelvis_tilt].restraint_func = NULL;
   sdm.q[pelvis_tilt].min_restraint_func = NULL;
   sdm.q[pelvis_tilt].max_restraint_func = NULL;
   sdm.q[pelvis_tilt].function_active = dpNo;
   sdm.q[pelvis_tilt].constraint_func = NULL;
   sdm.q[pelvis_tilt].constraint_num = -1;
   sdm.q[pelvis_tilt].q_ind = -1;
   sdm.q[pelvis_tilt].output = dpYes;
   sdm.q[pelvis_tilt].pd_stiffness = 0.0;
   sdm.q[pelvis_tilt].torque = 0.0;

   mstrcpy(&sdm.q[pelvis_list].name,"pelvis_list");
   sdm.q[pelvis_list].type = dpUnconstrainedQ;
   sdm.q[pelvis_list].joint = ground_pelvis;
   sdm.q[pelvis_list].axis = 4;
   sdm.q[pelvis_list].initial_value = 0.0000000000;
   sdm.q[pelvis_list].initial_velocity = 0.0;
   sdm.q[pelvis_list].range_start = -1.5707963300;
   sdm.q[pelvis_list].range_end = 1.5707963300;
   sdm.q[pelvis_list].restraint_func = NULL;
   sdm.q[pelvis_list].min_restraint_func = NULL;
   sdm.q[pelvis_list].max_restraint_func = NULL;
   sdm.q[pelvis_list].function_active = dpNo;
   sdm.q[pelvis_list].constraint_func = NULL;
   sdm.q[pelvis_list].constraint_num = -1;
   sdm.q[pelvis_list].q_ind = -1;
   sdm.q[pelvis_list].output = dpYes;
   sdm.q[pelvis_list].pd_stiffness = 0.0;
   sdm.q[pelvis_list].torque = 0.0;

   mstrcpy(&sdm.q[pelvis_rotation].name,"pelvis_rotation");
   sdm.q[pelvis_rotation].type = dpUnconstrainedQ;
   sdm.q[pelvis_rotation].joint = ground_pelvis;
   sdm.q[pelvis_rotation].axis = 5;
   sdm.q[pelvis_rotation].initial_value = 0.0000000000;
   sdm.q[pelvis_rotation].initial_velocity = 0.0;
   sdm.q[pelvis_rotation].range_start = -1.5707963300;
   sdm.q[pelvis_rotation].range_end = 1.5707963300;
   sdm.q[pelvis_rotation].restraint_func = NULL;
   sdm.q[pelvis_rotation].min_restraint_func = NULL;
   sdm.q[pelvis_rotation].max_restraint_func = NULL;
   sdm.q[pelvis_rotation].function_active = dpNo;
   sdm.q[pelvis_rotation].constraint_func = NULL;
   sdm.q[pelvis_rotation].constraint_num = -1;
   sdm.q[pelvis_rotation].q_ind = -1;
   sdm.q[pelvis_rotation].output = dpYes;
   sdm.q[pelvis_rotation].pd_stiffness = 0.0;
   sdm.q[pelvis_rotation].torque = 0.0;

   mstrcpy(&sdm.q[hip_flexion_r].name,"hip_flexion_r");
   sdm.q[hip_flexion_r].type = dpUnconstrainedQ;
   sdm.q[hip_flexion_r].joint = hip_r;
   sdm.q[hip_flexion_r].axis = 0;
   sdm.q[hip_flexion_r].initial_value = 0.0000000000;
   sdm.q[hip_flexion_r].initial_velocity = 0.0;
   sdm.q[hip_flexion_r].range_start = -2.0943951000;
   sdm.q[hip_flexion_r].range_end = 2.0943951000;
   sdm.q[hip_flexion_r].restraint_func = NULL;
   sdm.q[hip_flexion_r].min_restraint_func = NULL;
   sdm.q[hip_flexion_r].max_restraint_func = NULL;
   sdm.q[hip_flexion_r].function_active = dpNo;
   sdm.q[hip_flexion_r].constraint_func = NULL;
   sdm.q[hip_flexion_r].constraint_num = -1;
   sdm.q[hip_flexion_r].q_ind = -1;
   sdm.q[hip_flexion_r].output = dpYes;
   sdm.q[hip_flexion_r].pd_stiffness = 0.0;
   sdm.q[hip_flexion_r].torque = 0.0;

   mstrcpy(&sdm.q[hip_adduction_r].name,"hip_adduction_r");
   sdm.q[hip_adduction_r].type = dpUnconstrainedQ;
   sdm.q[hip_adduction_r].joint = hip_r;
   sdm.q[hip_adduction_r].axis = 1;
   sdm.q[hip_adduction_r].initial_value = 0.0000000000;
   sdm.q[hip_adduction_r].initial_velocity = 0.0;
   sdm.q[hip_adduction_r].range_start = -2.0943951000;
   sdm.q[hip_adduction_r].range_end = 2.0943951000;
   sdm.q[hip_adduction_r].restraint_func = NULL;
   sdm.q[hip_adduction_r].min_restraint_func = NULL;
   sdm.q[hip_adduction_r].max_restraint_func = NULL;
   sdm.q[hip_adduction_r].function_active = dpNo;
   sdm.q[hip_adduction_r].constraint_func = NULL;
   sdm.q[hip_adduction_r].constraint_num = -1;
   sdm.q[hip_adduction_r].q_ind = -1;
   sdm.q[hip_adduction_r].output = dpYes;
   sdm.q[hip_adduction_r].pd_stiffness = 0.0;
   sdm.q[hip_adduction_r].torque = 0.0;

   mstrcpy(&sdm.q[hip_rotation_r].name,"hip_rotation_r");
   sdm.q[hip_rotation_r].type = dpUnconstrainedQ;
   sdm.q[hip_rotation_r].joint = hip_r;
   sdm.q[hip_rotation_r].axis = 2;
   sdm.q[hip_rotation_r].initial_value = 0.0000000000;
   sdm.q[hip_rotation_r].initial_velocity = 0.0;
   sdm.q[hip_rotation_r].range_start = -2.0943951000;
   sdm.q[hip_rotation_r].range_end = 2.0943951000;
   sdm.q[hip_rotation_r].restraint_func = NULL;
   sdm.q[hip_rotation_r].min_restraint_func = NULL;
   sdm.q[hip_rotation_r].max_restraint_func = NULL;
   sdm.q[hip_rotation_r].function_active = dpNo;
   sdm.q[hip_rotation_r].constraint_func = NULL;
   sdm.q[hip_rotation_r].constraint_num = -1;
   sdm.q[hip_rotation_r].q_ind = -1;
   sdm.q[hip_rotation_r].output = dpYes;
   sdm.q[hip_rotation_r].pd_stiffness = 0.0;
   sdm.q[hip_rotation_r].torque = 0.0;

   mstrcpy(&sdm.q[knee_r_tx].name,"knee_r_tx");
   sdm.q[knee_r_tx].type = dpConstrainedQ;
   sdm.q[knee_r_tx].joint = knee_r;
   sdm.q[knee_r_tx].axis = 0;
   sdm.q[knee_r_tx].initial_value = -0.0046965961;
   sdm.q[knee_r_tx].initial_velocity = 0.0;
   sdm.q[knee_r_tx].range_start = -99999.9;
   sdm.q[knee_r_tx].range_end = 99999.9;
   sdm.q[knee_r_tx].restraint_func = NULL;
   sdm.q[knee_r_tx].min_restraint_func = NULL;
   sdm.q[knee_r_tx].max_restraint_func = NULL;
   sdm.q[knee_r_tx].function_active = dpNo;
   sdm.q[knee_r_tx].constraint_func = &knee_r_tx_func;
   sdm.q[knee_r_tx].constraint_num = knee_r_tx_con;
   sdm.q[knee_r_tx].q_ind = knee_angle_r;
   sdm.q[knee_r_tx].output = dpNo;
   sdm.q[knee_r_tx].pd_stiffness = 0.0;
   sdm.q[knee_r_tx].torque = 0.0;

   mstrcpy(&sdm.q[knee_r_ty].name,"knee_r_ty");
   sdm.q[knee_r_ty].type = dpConstrainedQ;
   sdm.q[knee_r_ty].joint = knee_r;
   sdm.q[knee_r_ty].axis = 1;
   sdm.q[knee_r_ty].initial_value = -0.4131266349;
   sdm.q[knee_r_ty].initial_velocity = 0.0;
   sdm.q[knee_r_ty].range_start = -99999.9;
   sdm.q[knee_r_ty].range_end = 99999.9;
   sdm.q[knee_r_ty].restraint_func = NULL;
   sdm.q[knee_r_ty].min_restraint_func = NULL;
   sdm.q[knee_r_ty].max_restraint_func = NULL;
   sdm.q[knee_r_ty].function_active = dpNo;
   sdm.q[knee_r_ty].constraint_func = &knee_r_ty_func;
   sdm.q[knee_r_ty].constraint_num = knee_r_ty_con;
   sdm.q[knee_r_ty].q_ind = knee_angle_r;
   sdm.q[knee_r_ty].output = dpNo;
   sdm.q[knee_r_ty].pd_stiffness = 0.0;
   sdm.q[knee_r_ty].torque = 0.0;

   mstrcpy(&sdm.q[knee_angle_r].name,"knee_angle_r");
   sdm.q[knee_angle_r].type = dpUnconstrainedQ;
   sdm.q[knee_angle_r].joint = knee_r;
   sdm.q[knee_angle_r].axis = 2;
   sdm.q[knee_angle_r].initial_value = 0.0000000000;
   sdm.q[knee_angle_r].initial_velocity = 0.0;
   sdm.q[knee_angle_r].range_start = -2.0943951000;
   sdm.q[knee_angle_r].range_end = 0.1745329300;
   sdm.q[knee_angle_r].restraint_func = NULL;
   sdm.q[knee_angle_r].min_restraint_func = NULL;
   sdm.q[knee_angle_r].max_restraint_func = NULL;
   sdm.q[knee_angle_r].function_active = dpNo;
   sdm.q[knee_angle_r].constraint_func = NULL;
   sdm.q[knee_angle_r].constraint_num = -1;
   sdm.q[knee_angle_r].q_ind = -1;
   sdm.q[knee_angle_r].output = dpYes;
   sdm.q[knee_angle_r].pd_stiffness = 0.0;
   sdm.q[knee_angle_r].torque = 0.0;

   mstrcpy(&sdm.q[tib_pat_r_tx].name,"tib_pat_r_tx");
   sdm.q[tib_pat_r_tx].type = dpConstrainedQ;
   sdm.q[tib_pat_r_tx].joint = tib_pat_r;
   sdm.q[tib_pat_r_tx].axis = 0;
   sdm.q[tib_pat_r_tx].initial_value = 0.0464030500;
   sdm.q[tib_pat_r_tx].initial_velocity = 0.0;
   sdm.q[tib_pat_r_tx].range_start = -99999.9;
   sdm.q[tib_pat_r_tx].range_end = 99999.9;
   sdm.q[tib_pat_r_tx].restraint_func = NULL;
   sdm.q[tib_pat_r_tx].min_restraint_func = NULL;
   sdm.q[tib_pat_r_tx].max_restraint_func = NULL;
   sdm.q[tib_pat_r_tx].function_active = dpNo;
   sdm.q[tib_pat_r_tx].constraint_func = &tib_pat_r_tx_func;
   sdm.q[tib_pat_r_tx].constraint_num = tib_pat_r_tx_con;
   sdm.q[tib_pat_r_tx].q_ind = knee_angle_r;
   sdm.q[tib_pat_r_tx].output = dpNo;
   sdm.q[tib_pat_r_tx].pd_stiffness = 0.0;
   sdm.q[tib_pat_r_tx].torque = 0.0;

   mstrcpy(&sdm.q[tib_pat_r_ty].name,"tib_pat_r_ty");
   sdm.q[tib_pat_r_ty].type = dpConstrainedQ;
   sdm.q[tib_pat_r_ty].joint = tib_pat_r;
   sdm.q[tib_pat_r_ty].axis = 1;
   sdm.q[tib_pat_r_ty].initial_value = -0.0212368800;
   sdm.q[tib_pat_r_ty].initial_velocity = 0.0;
   sdm.q[tib_pat_r_ty].range_start = -99999.9;
   sdm.q[tib_pat_r_ty].range_end = 99999.9;
   sdm.q[tib_pat_r_ty].restraint_func = NULL;
   sdm.q[tib_pat_r_ty].min_restraint_func = NULL;
   sdm.q[tib_pat_r_ty].max_restraint_func = NULL;
   sdm.q[tib_pat_r_ty].function_active = dpNo;
   sdm.q[tib_pat_r_ty].constraint_func = &tib_pat_r_ty_func;
   sdm.q[tib_pat_r_ty].constraint_num = tib_pat_r_ty_con;
   sdm.q[tib_pat_r_ty].q_ind = knee_angle_r;
   sdm.q[tib_pat_r_ty].output = dpNo;
   sdm.q[tib_pat_r_ty].pd_stiffness = 0.0;
   sdm.q[tib_pat_r_ty].torque = 0.0;

   mstrcpy(&sdm.q[tib_pat_r_r1].name,"tib_pat_r_r1");
   sdm.q[tib_pat_r_r1].type = dpConstrainedQ;
   sdm.q[tib_pat_r_r1].joint = tib_pat_r;
   sdm.q[tib_pat_r_r1].axis = 2;
   sdm.q[tib_pat_r_r1].initial_value = -0.0011691637;
   sdm.q[tib_pat_r_r1].initial_velocity = 0.0;
   sdm.q[tib_pat_r_r1].range_start = -99999.9;
   sdm.q[tib_pat_r_r1].range_end = 99999.9;
   sdm.q[tib_pat_r_r1].restraint_func = NULL;
   sdm.q[tib_pat_r_r1].min_restraint_func = NULL;
   sdm.q[tib_pat_r_r1].max_restraint_func = NULL;
   sdm.q[tib_pat_r_r1].function_active = dpNo;
   sdm.q[tib_pat_r_r1].constraint_func = &tib_pat_r_r1_func;
   sdm.q[tib_pat_r_r1].constraint_num = tib_pat_r_r1_con;
   sdm.q[tib_pat_r_r1].q_ind = knee_angle_r;
   sdm.q[tib_pat_r_r1].output = dpNo;
   sdm.q[tib_pat_r_r1].pd_stiffness = 0.0;
   sdm.q[tib_pat_r_r1].torque = 0.0;

   mstrcpy(&sdm.q[ankle_angle_r].name,"ankle_angle_r");
   sdm.q[ankle_angle_r].type = dpUnconstrainedQ;
   sdm.q[ankle_angle_r].joint = ankle_r;
   sdm.q[ankle_angle_r].axis = 0;
   sdm.q[ankle_angle_r].initial_value = 0.0000000000;
   sdm.q[ankle_angle_r].initial_velocity = 0.0;
   sdm.q[ankle_angle_r].range_start = -1.5707963300;
   sdm.q[ankle_angle_r].range_end = 1.5707963300;
   sdm.q[ankle_angle_r].restraint_func = NULL;
   sdm.q[ankle_angle_r].min_restraint_func = NULL;
   sdm.q[ankle_angle_r].max_restraint_func = NULL;
   sdm.q[ankle_angle_r].function_active = dpNo;
   sdm.q[ankle_angle_r].constraint_func = NULL;
   sdm.q[ankle_angle_r].constraint_num = -1;
   sdm.q[ankle_angle_r].q_ind = -1;
   sdm.q[ankle_angle_r].output = dpYes;
   sdm.q[ankle_angle_r].pd_stiffness = 0.0;
   sdm.q[ankle_angle_r].torque = 0.0;

   mstrcpy(&sdm.q[subtalar_angle_r].name,"subtalar_angle_r");
   sdm.q[subtalar_angle_r].type = dpFixedQ;
   sdm.q[subtalar_angle_r].joint = subtalar_r;
   sdm.q[subtalar_angle_r].axis = 0;
   sdm.q[subtalar_angle_r].initial_value = 0.0000000000;
   sdm.q[subtalar_angle_r].initial_velocity = 0.0;
   sdm.q[subtalar_angle_r].range_start = -1.5707963300;
   sdm.q[subtalar_angle_r].range_end = 1.5707963300;
   sdm.q[subtalar_angle_r].restraint_func = NULL;
   sdm.q[subtalar_angle_r].min_restraint_func = NULL;
   sdm.q[subtalar_angle_r].max_restraint_func = NULL;
   sdm.q[subtalar_angle_r].function_active = dpNo;
   sdm.q[subtalar_angle_r].constraint_func = NULL;
   sdm.q[subtalar_angle_r].constraint_num = -1;
   sdm.q[subtalar_angle_r].q_ind = -1;
   sdm.q[subtalar_angle_r].output = dpYes;
   sdm.q[subtalar_angle_r].pd_stiffness = 0.0;
   sdm.q[subtalar_angle_r].torque = 0.0;

   mstrcpy(&sdm.q[mtp_angle_r].name,"mtp_angle_r");
   sdm.q[mtp_angle_r].type = dpFixedQ;
   sdm.q[mtp_angle_r].joint = mtp_r;
   sdm.q[mtp_angle_r].axis = 0;
   sdm.q[mtp_angle_r].initial_value = 0.0000000000;
   sdm.q[mtp_angle_r].initial_velocity = 0.0;
   sdm.q[mtp_angle_r].range_start = -1.5707963300;
   sdm.q[mtp_angle_r].range_end = 1.5707963300;
   sdm.q[mtp_angle_r].restraint_func = NULL;
   sdm.q[mtp_angle_r].min_restraint_func = NULL;
   sdm.q[mtp_angle_r].max_restraint_func = NULL;
   sdm.q[mtp_angle_r].function_active = dpNo;
   sdm.q[mtp_angle_r].constraint_func = NULL;
   sdm.q[mtp_angle_r].constraint_num = -1;
   sdm.q[mtp_angle_r].q_ind = -1;
   sdm.q[mtp_angle_r].output = dpYes;
   sdm.q[mtp_angle_r].pd_stiffness = 0.0;
   sdm.q[mtp_angle_r].torque = 0.0;

   mstrcpy(&sdm.q[hip_flexion_l].name,"hip_flexion_l");
   sdm.q[hip_flexion_l].type = dpUnconstrainedQ;
   sdm.q[hip_flexion_l].joint = hip_l;
   sdm.q[hip_flexion_l].axis = 0;
   sdm.q[hip_flexion_l].initial_value = 0.0000000000;
   sdm.q[hip_flexion_l].initial_velocity = 0.0;
   sdm.q[hip_flexion_l].range_start = -2.0943951000;
   sdm.q[hip_flexion_l].range_end = 2.0943951000;
   sdm.q[hip_flexion_l].restraint_func = NULL;
   sdm.q[hip_flexion_l].min_restraint_func = NULL;
   sdm.q[hip_flexion_l].max_restraint_func = NULL;
   sdm.q[hip_flexion_l].function_active = dpNo;
   sdm.q[hip_flexion_l].constraint_func = NULL;
   sdm.q[hip_flexion_l].constraint_num = -1;
   sdm.q[hip_flexion_l].q_ind = -1;
   sdm.q[hip_flexion_l].output = dpYes;
   sdm.q[hip_flexion_l].pd_stiffness = 0.0;
   sdm.q[hip_flexion_l].torque = 0.0;

   mstrcpy(&sdm.q[hip_adduction_l].name,"hip_adduction_l");
   sdm.q[hip_adduction_l].type = dpUnconstrainedQ;
   sdm.q[hip_adduction_l].joint = hip_l;
   sdm.q[hip_adduction_l].axis = 1;
   sdm.q[hip_adduction_l].initial_value = 0.0000000000;
   sdm.q[hip_adduction_l].initial_velocity = 0.0;
   sdm.q[hip_adduction_l].range_start = -2.0943951000;
   sdm.q[hip_adduction_l].range_end = 2.0943951000;
   sdm.q[hip_adduction_l].restraint_func = NULL;
   sdm.q[hip_adduction_l].min_restraint_func = NULL;
   sdm.q[hip_adduction_l].max_restraint_func = NULL;
   sdm.q[hip_adduction_l].function_active = dpNo;
   sdm.q[hip_adduction_l].constraint_func = NULL;
   sdm.q[hip_adduction_l].constraint_num = -1;
   sdm.q[hip_adduction_l].q_ind = -1;
   sdm.q[hip_adduction_l].output = dpYes;
   sdm.q[hip_adduction_l].pd_stiffness = 0.0;
   sdm.q[hip_adduction_l].torque = 0.0;

   mstrcpy(&sdm.q[hip_rotation_l].name,"hip_rotation_l");
   sdm.q[hip_rotation_l].type = dpUnconstrainedQ;
   sdm.q[hip_rotation_l].joint = hip_l;
   sdm.q[hip_rotation_l].axis = 2;
   sdm.q[hip_rotation_l].initial_value = 0.0000000000;
   sdm.q[hip_rotation_l].initial_velocity = 0.0;
   sdm.q[hip_rotation_l].range_start = -2.0943951000;
   sdm.q[hip_rotation_l].range_end = 2.0943951000;
   sdm.q[hip_rotation_l].restraint_func = NULL;
   sdm.q[hip_rotation_l].min_restraint_func = NULL;
   sdm.q[hip_rotation_l].max_restraint_func = NULL;
   sdm.q[hip_rotation_l].function_active = dpNo;
   sdm.q[hip_rotation_l].constraint_func = NULL;
   sdm.q[hip_rotation_l].constraint_num = -1;
   sdm.q[hip_rotation_l].q_ind = -1;
   sdm.q[hip_rotation_l].output = dpYes;
   sdm.q[hip_rotation_l].pd_stiffness = 0.0;
   sdm.q[hip_rotation_l].torque = 0.0;

   mstrcpy(&sdm.q[knee_l_tx].name,"knee_l_tx");
   sdm.q[knee_l_tx].type = dpConstrainedQ;
   sdm.q[knee_l_tx].joint = knee_l;
   sdm.q[knee_l_tx].axis = 0;
   sdm.q[knee_l_tx].initial_value = -0.0046965961;
   sdm.q[knee_l_tx].initial_velocity = 0.0;
   sdm.q[knee_l_tx].range_start = -99999.9;
   sdm.q[knee_l_tx].range_end = 99999.9;
   sdm.q[knee_l_tx].restraint_func = NULL;
   sdm.q[knee_l_tx].min_restraint_func = NULL;
   sdm.q[knee_l_tx].max_restraint_func = NULL;
   sdm.q[knee_l_tx].function_active = dpNo;
   sdm.q[knee_l_tx].constraint_func = &knee_l_tx_func;
   sdm.q[knee_l_tx].constraint_num = knee_l_tx_con;
   sdm.q[knee_l_tx].q_ind = knee_angle_l;
   sdm.q[knee_l_tx].output = dpNo;
   sdm.q[knee_l_tx].pd_stiffness = 0.0;
   sdm.q[knee_l_tx].torque = 0.0;

   mstrcpy(&sdm.q[knee_l_ty].name,"knee_l_ty");
   sdm.q[knee_l_ty].type = dpConstrainedQ;
   sdm.q[knee_l_ty].joint = knee_l;
   sdm.q[knee_l_ty].axis = 1;
   sdm.q[knee_l_ty].initial_value = -0.4131266349;
   sdm.q[knee_l_ty].initial_velocity = 0.0;
   sdm.q[knee_l_ty].range_start = -99999.9;
   sdm.q[knee_l_ty].range_end = 99999.9;
   sdm.q[knee_l_ty].restraint_func = NULL;
   sdm.q[knee_l_ty].min_restraint_func = NULL;
   sdm.q[knee_l_ty].max_restraint_func = NULL;
   sdm.q[knee_l_ty].function_active = dpNo;
   sdm.q[knee_l_ty].constraint_func = &knee_l_ty_func;
   sdm.q[knee_l_ty].constraint_num = knee_l_ty_con;
   sdm.q[knee_l_ty].q_ind = knee_angle_l;
   sdm.q[knee_l_ty].output = dpNo;
   sdm.q[knee_l_ty].pd_stiffness = 0.0;
   sdm.q[knee_l_ty].torque = 0.0;

   mstrcpy(&sdm.q[knee_angle_l].name,"knee_angle_l");
   sdm.q[knee_angle_l].type = dpUnconstrainedQ;
   sdm.q[knee_angle_l].joint = knee_l;
   sdm.q[knee_angle_l].axis = 2;
   sdm.q[knee_angle_l].initial_value = 0.0000000000;
   sdm.q[knee_angle_l].initial_velocity = 0.0;
   sdm.q[knee_angle_l].range_start = -2.0943951000;
   sdm.q[knee_angle_l].range_end = 0.1745329300;
   sdm.q[knee_angle_l].restraint_func = NULL;
   sdm.q[knee_angle_l].min_restraint_func = NULL;
   sdm.q[knee_angle_l].max_restraint_func = NULL;
   sdm.q[knee_angle_l].function_active = dpNo;
   sdm.q[knee_angle_l].constraint_func = NULL;
   sdm.q[knee_angle_l].constraint_num = -1;
   sdm.q[knee_angle_l].q_ind = -1;
   sdm.q[knee_angle_l].output = dpYes;
   sdm.q[knee_angle_l].pd_stiffness = 0.0;
   sdm.q[knee_angle_l].torque = 0.0;

   mstrcpy(&sdm.q[tib_pat_l_tx].name,"tib_pat_l_tx");
   sdm.q[tib_pat_l_tx].type = dpConstrainedQ;
   sdm.q[tib_pat_l_tx].joint = tib_pat_l;
   sdm.q[tib_pat_l_tx].axis = 0;
   sdm.q[tib_pat_l_tx].initial_value = 0.0464030500;
   sdm.q[tib_pat_l_tx].initial_velocity = 0.0;
   sdm.q[tib_pat_l_tx].range_start = -99999.9;
   sdm.q[tib_pat_l_tx].range_end = 99999.9;
   sdm.q[tib_pat_l_tx].restraint_func = NULL;
   sdm.q[tib_pat_l_tx].min_restraint_func = NULL;
   sdm.q[tib_pat_l_tx].max_restraint_func = NULL;
   sdm.q[tib_pat_l_tx].function_active = dpNo;
   sdm.q[tib_pat_l_tx].constraint_func = &tib_pat_l_tx_func;
   sdm.q[tib_pat_l_tx].constraint_num = tib_pat_l_tx_con;
   sdm.q[tib_pat_l_tx].q_ind = knee_angle_l;
   sdm.q[tib_pat_l_tx].output = dpNo;
   sdm.q[tib_pat_l_tx].pd_stiffness = 0.0;
   sdm.q[tib_pat_l_tx].torque = 0.0;

   mstrcpy(&sdm.q[tib_pat_l_ty].name,"tib_pat_l_ty");
   sdm.q[tib_pat_l_ty].type = dpConstrainedQ;
   sdm.q[tib_pat_l_ty].joint = tib_pat_l;
   sdm.q[tib_pat_l_ty].axis = 1;
   sdm.q[tib_pat_l_ty].initial_value = -0.0212368800;
   sdm.q[tib_pat_l_ty].initial_velocity = 0.0;
   sdm.q[tib_pat_l_ty].range_start = -99999.9;
   sdm.q[tib_pat_l_ty].range_end = 99999.9;
   sdm.q[tib_pat_l_ty].restraint_func = NULL;
   sdm.q[tib_pat_l_ty].min_restraint_func = NULL;
   sdm.q[tib_pat_l_ty].max_restraint_func = NULL;
   sdm.q[tib_pat_l_ty].function_active = dpNo;
   sdm.q[tib_pat_l_ty].constraint_func = &tib_pat_l_ty_func;
   sdm.q[tib_pat_l_ty].constraint_num = tib_pat_l_ty_con;
   sdm.q[tib_pat_l_ty].q_ind = knee_angle_l;
   sdm.q[tib_pat_l_ty].output = dpNo;
   sdm.q[tib_pat_l_ty].pd_stiffness = 0.0;
   sdm.q[tib_pat_l_ty].torque = 0.0;

   mstrcpy(&sdm.q[tib_pat_l_r1].name,"tib_pat_l_r1");
   sdm.q[tib_pat_l_r1].type = dpConstrainedQ;
   sdm.q[tib_pat_l_r1].joint = tib_pat_l;
   sdm.q[tib_pat_l_r1].axis = 2;
   sdm.q[tib_pat_l_r1].initial_value = -0.0011691637;
   sdm.q[tib_pat_l_r1].initial_velocity = 0.0;
   sdm.q[tib_pat_l_r1].range_start = -99999.9;
   sdm.q[tib_pat_l_r1].range_end = 99999.9;
   sdm.q[tib_pat_l_r1].restraint_func = NULL;
   sdm.q[tib_pat_l_r1].min_restraint_func = NULL;
   sdm.q[tib_pat_l_r1].max_restraint_func = NULL;
   sdm.q[tib_pat_l_r1].function_active = dpNo;
   sdm.q[tib_pat_l_r1].constraint_func = &tib_pat_l_r1_func;
   sdm.q[tib_pat_l_r1].constraint_num = tib_pat_l_r1_con;
   sdm.q[tib_pat_l_r1].q_ind = knee_angle_l;
   sdm.q[tib_pat_l_r1].output = dpNo;
   sdm.q[tib_pat_l_r1].pd_stiffness = 0.0;
   sdm.q[tib_pat_l_r1].torque = 0.0;

   mstrcpy(&sdm.q[ankle_angle_l].name,"ankle_angle_l");
   sdm.q[ankle_angle_l].type = dpUnconstrainedQ;
   sdm.q[ankle_angle_l].joint = ankle_l;
   sdm.q[ankle_angle_l].axis = 0;
   sdm.q[ankle_angle_l].initial_value = 0.0000000000;
   sdm.q[ankle_angle_l].initial_velocity = 0.0;
   sdm.q[ankle_angle_l].range_start = -1.0471975500;
   sdm.q[ankle_angle_l].range_end = 1.0471975500;
   sdm.q[ankle_angle_l].restraint_func = NULL;
   sdm.q[ankle_angle_l].min_restraint_func = NULL;
   sdm.q[ankle_angle_l].max_restraint_func = NULL;
   sdm.q[ankle_angle_l].function_active = dpNo;
   sdm.q[ankle_angle_l].constraint_func = NULL;
   sdm.q[ankle_angle_l].constraint_num = -1;
   sdm.q[ankle_angle_l].q_ind = -1;
   sdm.q[ankle_angle_l].output = dpYes;
   sdm.q[ankle_angle_l].pd_stiffness = 0.0;
   sdm.q[ankle_angle_l].torque = 0.0;

   mstrcpy(&sdm.q[subtalar_angle_l].name,"subtalar_angle_l");
   sdm.q[subtalar_angle_l].type = dpFixedQ;
   sdm.q[subtalar_angle_l].joint = subtalar_l;
   sdm.q[subtalar_angle_l].axis = 0;
   sdm.q[subtalar_angle_l].initial_value = 0.0000000000;
   sdm.q[subtalar_angle_l].initial_velocity = 0.0;
   sdm.q[subtalar_angle_l].range_start = -1.5707963300;
   sdm.q[subtalar_angle_l].range_end = 1.5707963300;
   sdm.q[subtalar_angle_l].restraint_func = NULL;
   sdm.q[subtalar_angle_l].min_restraint_func = NULL;
   sdm.q[subtalar_angle_l].max_restraint_func = NULL;
   sdm.q[subtalar_angle_l].function_active = dpNo;
   sdm.q[subtalar_angle_l].constraint_func = NULL;
   sdm.q[subtalar_angle_l].constraint_num = -1;
   sdm.q[subtalar_angle_l].q_ind = -1;
   sdm.q[subtalar_angle_l].output = dpYes;
   sdm.q[subtalar_angle_l].pd_stiffness = 0.0;
   sdm.q[subtalar_angle_l].torque = 0.0;

   mstrcpy(&sdm.q[mtp_angle_l].name,"mtp_angle_l");
   sdm.q[mtp_angle_l].type = dpFixedQ;
   sdm.q[mtp_angle_l].joint = mtp_l;
   sdm.q[mtp_angle_l].axis = 0;
   sdm.q[mtp_angle_l].initial_value = 0.0000000000;
   sdm.q[mtp_angle_l].initial_velocity = 0.0;
   sdm.q[mtp_angle_l].range_start = -1.0471975500;
   sdm.q[mtp_angle_l].range_end = 1.0471975500;
   sdm.q[mtp_angle_l].restraint_func = NULL;
   sdm.q[mtp_angle_l].min_restraint_func = NULL;
   sdm.q[mtp_angle_l].max_restraint_func = NULL;
   sdm.q[mtp_angle_l].function_active = dpNo;
   sdm.q[mtp_angle_l].constraint_func = NULL;
   sdm.q[mtp_angle_l].constraint_num = -1;
   sdm.q[mtp_angle_l].q_ind = -1;
   sdm.q[mtp_angle_l].output = dpYes;
   sdm.q[mtp_angle_l].pd_stiffness = 0.0;
   sdm.q[mtp_angle_l].torque = 0.0;

   mstrcpy(&sdm.q[lumbar_extension].name,"lumbar_extension");
   sdm.q[lumbar_extension].type = dpUnconstrainedQ;
   sdm.q[lumbar_extension].joint = back;
   sdm.q[lumbar_extension].axis = 0;
   sdm.q[lumbar_extension].initial_value = 0.0000000000;
   sdm.q[lumbar_extension].initial_velocity = 0.0;
   sdm.q[lumbar_extension].range_start = -1.5707963300;
   sdm.q[lumbar_extension].range_end = 1.5707963300;
   sdm.q[lumbar_extension].restraint_func = NULL;
   sdm.q[lumbar_extension].min_restraint_func = NULL;
   sdm.q[lumbar_extension].max_restraint_func = NULL;
   sdm.q[lumbar_extension].function_active = dpNo;
   sdm.q[lumbar_extension].constraint_func = NULL;
   sdm.q[lumbar_extension].constraint_num = -1;
   sdm.q[lumbar_extension].q_ind = -1;
   sdm.q[lumbar_extension].output = dpYes;
   sdm.q[lumbar_extension].pd_stiffness = 0.0;
   sdm.q[lumbar_extension].torque = 0.0;

   mstrcpy(&sdm.q[lumbar_bending].name,"lumbar_bending");
   sdm.q[lumbar_bending].type = dpUnconstrainedQ;
   sdm.q[lumbar_bending].joint = back;
   sdm.q[lumbar_bending].axis = 1;
   sdm.q[lumbar_bending].initial_value = 0.0000000000;
   sdm.q[lumbar_bending].initial_velocity = 0.0;
   sdm.q[lumbar_bending].range_start = -1.5707963300;
   sdm.q[lumbar_bending].range_end = 1.5707963300;
   sdm.q[lumbar_bending].restraint_func = NULL;
   sdm.q[lumbar_bending].min_restraint_func = NULL;
   sdm.q[lumbar_bending].max_restraint_func = NULL;
   sdm.q[lumbar_bending].function_active = dpNo;
   sdm.q[lumbar_bending].constraint_func = NULL;
   sdm.q[lumbar_bending].constraint_num = -1;
   sdm.q[lumbar_bending].q_ind = -1;
   sdm.q[lumbar_bending].output = dpYes;
   sdm.q[lumbar_bending].pd_stiffness = 0.0;
   sdm.q[lumbar_bending].torque = 0.0;

   mstrcpy(&sdm.q[lumbar_rotation].name,"lumbar_rotation");
   sdm.q[lumbar_rotation].type = dpUnconstrainedQ;
   sdm.q[lumbar_rotation].joint = back;
   sdm.q[lumbar_rotation].axis = 2;
   sdm.q[lumbar_rotation].initial_value = 0.0000000000;
   sdm.q[lumbar_rotation].initial_velocity = 0.0;
   sdm.q[lumbar_rotation].range_start = -1.5707963300;
   sdm.q[lumbar_rotation].range_end = 1.5707963300;
   sdm.q[lumbar_rotation].restraint_func = NULL;
   sdm.q[lumbar_rotation].min_restraint_func = NULL;
   sdm.q[lumbar_rotation].max_restraint_func = NULL;
   sdm.q[lumbar_rotation].function_active = dpNo;
   sdm.q[lumbar_rotation].constraint_func = NULL;
   sdm.q[lumbar_rotation].constraint_num = -1;
   sdm.q[lumbar_rotation].q_ind = -1;
   sdm.q[lumbar_rotation].output = dpYes;
   sdm.q[lumbar_rotation].pd_stiffness = 0.0;
   sdm.q[lumbar_rotation].torque = 0.0;

   for (i=0, sdm.num_gencoords=0; i<sdm.nq; i++)
      if (sdm.q[i].type == dpUnconstrainedQ)
         sdm.num_gencoords++;

   check_for_sderror("INIT_QS");
}


/* INIT_SEGMENTS: this routine should be called before
 * read_muscles() because it does two things that need to
 * be done before you read in the muscles. First, it assigns
 * numbers to the body segments in your model. These body
 * numbers should match the numbers in the "_info" file
 * that SD/FAST makes. Thus when you read in the muscle
 * attachment points, the segment name listed for each point
 * is converted into an SD/FAST body segment number.
 * Second, this routine records the positions of the mass
 * centers of each body segment. These are the coordinates of
 * the mass centers with respect to the origins of the SIMM
 * bone file. When you read in a muscle attachment point, the
 * mass center coordinates are subtracted from it, so that the
 * muscle point is now w.r.t. the mass center of the body
 * segment, as SD/FAST expects.
 * Note that you cannot use the #defined segment numbers as indices
 * into the sdm.body_segment[] array because they start at -1.
 */

void init_segments(void)
{

   int i, j;
   sdm.body_segment = (dpBodyStruct*)simm_malloc(sdm.num_body_segments*sizeof(dpBodyStruct));

   mstrcpy(&sdm.body_segment[ground+1].name,"ground");
   sdm.body_segment[ground+1].output = dpNo;
   sdm.body_segment[ground+1].mass = 0.0;
   sdm.body_segment[ground+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[ground+1].mass_center[1] = 0.0000000000;
   sdm.body_segment[ground+1].mass_center[2] = 0.0000000000;
   for (i=0; i<3; i++)
      for (j=0; j<3; j++)
         sdm.body_segment[ground+1].inertia[i][j] = 0.0;
   sdm.body_segment[ground+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[pelvis+1].name,"pelvis");
   sdm.body_segment[pelvis+1].output = dpYes;
   sdgetmass(pelvis, &(sdm.body_segment[pelvis+1].mass));
   sdgetiner(pelvis, sdm.body_segment[pelvis+1].inertia);
   sdm.body_segment[pelvis+1].mass_center[0] = -0.0657970100;
   sdm.body_segment[pelvis+1].mass_center[1] = 0.0000000000;
   sdm.body_segment[pelvis+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[pelvis+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[femur_r+1].name,"femur_r");
   sdm.body_segment[femur_r+1].output = dpYes;
   sdgetmass(femur_r, &(sdm.body_segment[femur_r+1].mass));
   sdgetiner(femur_r, sdm.body_segment[femur_r+1].inertia);
   sdm.body_segment[femur_r+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[femur_r+1].mass_center[1] = -0.1774326800;
   sdm.body_segment[femur_r+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[femur_r+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[tibia_r+1].name,"tibia_r");
   sdm.body_segment[tibia_r+1].output = dpYes;
   sdgetmass(tibia_r, &(sdm.body_segment[tibia_r+1].mass));
   sdgetiner(tibia_r, sdm.body_segment[tibia_r+1].inertia);
   sdm.body_segment[tibia_r+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[tibia_r+1].mass_center[1] = -0.1746663000;
   sdm.body_segment[tibia_r+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[tibia_r+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[patella_r+1].name,"patella_r");
   sdm.body_segment[patella_r+1].output = dpYes;
   sdgetmass(patella_r, &(sdm.body_segment[patella_r+1].mass));
   sdgetiner(patella_r, sdm.body_segment[patella_r+1].inertia);
   sdm.body_segment[patella_r+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[patella_r+1].mass_center[1] = 0.0000000000;
   sdm.body_segment[patella_r+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[patella_r+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[talus_r+1].name,"talus_r");
   sdm.body_segment[talus_r+1].output = dpYes;
   sdgetmass(talus_r, &(sdm.body_segment[talus_r+1].mass));
   sdgetiner(talus_r, sdm.body_segment[talus_r+1].inertia);
   sdm.body_segment[talus_r+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[talus_r+1].mass_center[1] = 0.0000000000;
   sdm.body_segment[talus_r+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[talus_r+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[calcn_r+1].name,"calcn_r");
   sdm.body_segment[calcn_r+1].output = dpYes;
   sdgetmass(calcn_r, &(sdm.body_segment[calcn_r+1].mass));
   sdgetiner(calcn_r, sdm.body_segment[calcn_r+1].inertia);
   sdm.body_segment[calcn_r+1].mass_center[0] = 0.1040361100;
   sdm.body_segment[calcn_r+1].mass_center[1] = 0.0312108300;
   sdm.body_segment[calcn_r+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[calcn_r+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[toes_r+1].name,"toes_r");
   sdm.body_segment[toes_r+1].output = dpYes;
   sdgetmass(toes_r, &(sdm.body_segment[toes_r+1].mass));
   sdgetiner(toes_r, sdm.body_segment[toes_r+1].inertia);
   sdm.body_segment[toes_r+1].mass_center[0] = 0.0359964900;
   sdm.body_segment[toes_r+1].mass_center[1] = 0.0062421700;
   sdm.body_segment[toes_r+1].mass_center[2] = -0.0182063200;
   sdm.body_segment[toes_r+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[femur_l+1].name,"femur_l");
   sdm.body_segment[femur_l+1].output = dpYes;
   sdgetmass(femur_l, &(sdm.body_segment[femur_l+1].mass));
   sdgetiner(femur_l, sdm.body_segment[femur_l+1].inertia);
   sdm.body_segment[femur_l+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[femur_l+1].mass_center[1] = -0.1774326800;
   sdm.body_segment[femur_l+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[femur_l+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[tibia_l+1].name,"tibia_l");
   sdm.body_segment[tibia_l+1].output = dpYes;
   sdgetmass(tibia_l, &(sdm.body_segment[tibia_l+1].mass));
   sdgetiner(tibia_l, sdm.body_segment[tibia_l+1].inertia);
   sdm.body_segment[tibia_l+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[tibia_l+1].mass_center[1] = -0.1746663000;
   sdm.body_segment[tibia_l+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[tibia_l+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[patella_l+1].name,"patella_l");
   sdm.body_segment[patella_l+1].output = dpYes;
   sdgetmass(patella_l, &(sdm.body_segment[patella_l+1].mass));
   sdgetiner(patella_l, sdm.body_segment[patella_l+1].inertia);
   sdm.body_segment[patella_l+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[patella_l+1].mass_center[1] = 0.0000000000;
   sdm.body_segment[patella_l+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[patella_l+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[talus_l+1].name,"talus_l");
   sdm.body_segment[talus_l+1].output = dpYes;
   sdgetmass(talus_l, &(sdm.body_segment[talus_l+1].mass));
   sdgetiner(talus_l, sdm.body_segment[talus_l+1].inertia);
   sdm.body_segment[talus_l+1].mass_center[0] = 0.0000000000;
   sdm.body_segment[talus_l+1].mass_center[1] = 0.0000000000;
   sdm.body_segment[talus_l+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[talus_l+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[calcn_l+1].name,"calcn_l");
   sdm.body_segment[calcn_l+1].output = dpYes;
   sdgetmass(calcn_l, &(sdm.body_segment[calcn_l+1].mass));
   sdgetiner(calcn_l, sdm.body_segment[calcn_l+1].inertia);
   sdm.body_segment[calcn_l+1].mass_center[0] = 0.1040361100;
   sdm.body_segment[calcn_l+1].mass_center[1] = 0.0312108300;
   sdm.body_segment[calcn_l+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[calcn_l+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[toes_l+1].name,"toes_l");
   sdm.body_segment[toes_l+1].output = dpYes;
   sdgetmass(toes_l, &(sdm.body_segment[toes_l+1].mass));
   sdgetiner(toes_l, sdm.body_segment[toes_l+1].inertia);
   sdm.body_segment[toes_l+1].mass_center[0] = 0.0359964900;
   sdm.body_segment[toes_l+1].mass_center[1] = 0.0062421700;
   sdm.body_segment[toes_l+1].mass_center[2] = 0.0182063200;
   sdm.body_segment[toes_l+1].contactable = dpNo;

   mstrcpy(&sdm.body_segment[torso+1].name,"torso");
   sdm.body_segment[torso+1].output = dpYes;
   sdgetmass(torso, &(sdm.body_segment[torso+1].mass));
   sdgetiner(torso, sdm.body_segment[torso+1].inertia);
   sdm.body_segment[torso+1].mass_center[0] = -0.0285960600;
   sdm.body_segment[torso+1].mass_center[1] = 0.3050245900;
   sdm.body_segment[torso+1].mass_center[2] = 0.0000000000;
   sdm.body_segment[torso+1].contactable = dpNo;

   mstrcpy(&sdm.name, "3DGaitModelSimple");

   check_for_sderror("INIT_SEGMENTS");

}


/* INIT_Q_RESTRAINT_FUNCTIONS: this routine initializes the restraint
 * functions which are used to keep the Qs from exceeding their ranges of motion.
 */

void init_q_restraint_functions(void)
{
   int i, numpts;

   /* There are no user-defined restraints in this model */

}


/* INIT_JOINT_FUNCTIONS: this routine initializes the constraint functions
 * for the joints which have user-defined constraints.
 */

void init_joint_functions(void)
{

   int i, numpts;

   numpts = sizeof(knee_r_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&knee_r_tx_func,numpts);
   knee_r_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      knee_r_tx_func.x[i] = knee_r_tx_data[i][0];
      knee_r_tx_func.y[i] = knee_r_tx_data[i][1];
   }
   calc_spline_coefficients(&knee_r_tx_func);

   numpts = sizeof(knee_r_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&knee_r_ty_func,numpts);
   knee_r_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      knee_r_ty_func.x[i] = knee_r_ty_data[i][0];
      knee_r_ty_func.y[i] = knee_r_ty_data[i][1];
   }
   calc_spline_coefficients(&knee_r_ty_func);

   numpts = sizeof(tib_pat_r_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_r_tx_func,numpts);
   tib_pat_r_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_r_tx_func.x[i] = tib_pat_r_tx_data[i][0];
      tib_pat_r_tx_func.y[i] = tib_pat_r_tx_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_r_tx_func);

   numpts = sizeof(tib_pat_r_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_r_ty_func,numpts);
   tib_pat_r_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_r_ty_func.x[i] = tib_pat_r_ty_data[i][0];
      tib_pat_r_ty_func.y[i] = tib_pat_r_ty_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_r_ty_func);

   numpts = sizeof(tib_pat_r_r1_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_r_r1_func,numpts);
   tib_pat_r_r1_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_r_r1_func.x[i] = tib_pat_r_r1_data[i][0];
      tib_pat_r_r1_func.y[i] = tib_pat_r_r1_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_r_r1_func);

   numpts = sizeof(knee_l_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&knee_l_tx_func,numpts);
   knee_l_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      knee_l_tx_func.x[i] = knee_l_tx_data[i][0];
      knee_l_tx_func.y[i] = knee_l_tx_data[i][1];
   }
   calc_spline_coefficients(&knee_l_tx_func);

   numpts = sizeof(knee_l_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&knee_l_ty_func,numpts);
   knee_l_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      knee_l_ty_func.x[i] = knee_l_ty_data[i][0];
      knee_l_ty_func.y[i] = knee_l_ty_data[i][1];
   }
   calc_spline_coefficients(&knee_l_ty_func);

   numpts = sizeof(tib_pat_l_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_l_tx_func,numpts);
   tib_pat_l_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_l_tx_func.x[i] = tib_pat_l_tx_data[i][0];
      tib_pat_l_tx_func.y[i] = tib_pat_l_tx_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_l_tx_func);

   numpts = sizeof(tib_pat_l_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_l_ty_func,numpts);
   tib_pat_l_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_l_ty_func.x[i] = tib_pat_l_ty_data[i][0];
      tib_pat_l_ty_func.y[i] = tib_pat_l_ty_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_l_ty_func);

   numpts = sizeof(tib_pat_l_r1_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_l_r1_func,numpts);
   tib_pat_l_r1_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_l_r1_func.x[i] = tib_pat_l_r1_data[i][0];
      tib_pat_l_r1_func.y[i] = tib_pat_l_r1_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_l_r1_func);

}


void init_wrap_objects(void)
{

   /* There are no wrap objects in this model. */

  sdm.num_wrap_objects = 0;
  sdm.wrap_object = NULL;

}

void init_constraint_objects(void)
{

   /* There are no constraint objects in this model. */

  sdm.num_constraint_objects = 0;
  sdm.constraint_object = NULL;
}

