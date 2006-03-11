/*******************************************************************************

   D:\programfiles\cimtj\rra\900061\dynsim\src\sdfor.c

   Created by SIMM 4.0.1 (from joint file D:\programfiles\gaitdata\FromAllison\SuccessfulCases\900061.jnt)

   Time of creation: 02/06/2006 04:56:06 PM

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
{-120.0000000000,-0.0030226130},
{-100.0000000000,0.0016907742},
{-80.0000000000,0.0038821686},
{-60.0000000000,0.0038727230},
{-40.0000000000,0.0020024811},
{-20.0000000000,-0.0009445666},
{-10.0000000000,-0.0029281564},
{11.3069910000,-0.0049372495},
{19.3313070000,-0.0051337193},
{28.0851060000,-0.0052650141},
{87.1732520000,-0.0051337193},
{120.0000000000,-0.0049589745}
};

static double knee_r_ty_data[][2] =
{
{-120.0000000000,-0.3991738342},
{-70.0000000000,-0.3855720755},
{-30.0000000000,-0.3768820630},
{-20.0000000000,-0.3755596698},
{-10.0000000000,-0.3746151032},
{9.1185410000,-0.3733531623},
{120.0000000000,-0.3740483633}
};

static double tib_pat_r_r3_data[][2] =
{
{-120.0000000000,17.6500000000},
{-114.5900000000,17.6500000000},
{-83.5100000000,17.5500000000},
{-30.1600000000,15.4800000000},
{1.6000000000,-2.1200000000},
{10.0000000000,-16.0400000000}
};

static double tib_pat_r_tx_data[][2] =
{
{-120.0000000000,0.0160495243},
{-80.0000000000,0.0300580686},
{-60.0000000000,0.0353460621},
{-40.0000000000,0.0398918812},
{-20.0000000000,0.0435099820},
{-10.0000000000,0.0449015593},
{0.0000000000,0.0460148211},
{0.0100000000,0.0460148211},
{0.0200000000,0.0460148211},
{5.0000000000,0.0460148211},
{120.0000000000,0.0460148211}
};

static double tib_pat_r_ty_data[][2] =
{
{-120.0000000000,-0.0203170278},
{-90.0000000000,-0.0187399070},
{-80.0000000000,-0.0185543633},
{-60.0000000000,-0.0189254506},
{-40.0000000000,-0.0195748533},
{-20.0000000000,-0.0203170278},
{-10.0000000000,-0.0206881151},
{0.0000000000,-0.0210592024},
{0.0100000000,-0.0210592024},
{0.0200000000,-0.0210592024},
{5.0000000000,-0.0210592024},
{120.0000000000,-0.0210592024}
};

static double knee_l_tx_data[][2] =
{
{-120.0000000000,-0.0030226130},
{-100.0000000000,0.0016907742},
{-80.0000000000,0.0038821686},
{-60.0000000000,0.0038727230},
{-40.0000000000,0.0020024811},
{-20.0000000000,-0.0009445666},
{-10.0000000000,-0.0029281564},
{11.3069910000,-0.0049372495},
{19.3313070000,-0.0051337193},
{28.0851060000,-0.0052650141},
{87.1732520000,-0.0051337193},
{120.0000000000,-0.0049589745}
};

static double knee_l_ty_data[][2] =
{
{-120.0000000000,-0.3991738342},
{-70.0000000000,-0.3855720755},
{-30.0000000000,-0.3768820630},
{-20.0000000000,-0.3755596698},
{-10.0000000000,-0.3746151032},
{9.1185410000,-0.3733531623},
{120.0000000000,-0.3740483633}
};

static double tib_pat_l_r3_data[][2] =
{
{-120.0000000000,17.6500000000},
{-114.5900000000,17.6500000000},
{-83.5100000000,17.5500000000},
{-30.1600000000,15.4800000000},
{1.6000000000,-2.1200000000},
{10.0000000000,-16.0400000000}
};

static double tib_pat_l_tx_data[][2] =
{
{-120.0000000000,0.0160495243},
{-80.0000000000,0.0300580686},
{-60.0000000000,0.0353460621},
{-40.0000000000,0.0398918812},
{-20.0000000000,0.0435099820},
{-10.0000000000,0.0449015593},
{0.0000000000,0.0460148211},
{0.0100000000,0.0460148211},
{0.0200000000,0.0460148211},
{5.0000000000,0.0460148211},
{120.0000000000,0.0460148211}
};

static double tib_pat_l_ty_data[][2] =
{
{-120.0000000000,-0.0203170278},
{-90.0000000000,-0.0187399070},
{-80.0000000000,-0.0185543633},
{-60.0000000000,-0.0189254506},
{-40.0000000000,-0.0195748533},
{-20.0000000000,-0.0203170278},
{-10.0000000000,-0.0206881151},
{0.0000000000,-0.0210592024},
{0.0100000000,-0.0210592024},
{0.0200000000,-0.0210592024},
{5.0000000000,-0.0210592024},
{120.0000000000,-0.0210592024}
};

static dpSplineFunction knee_r_tx_func;
static dpSplineFunction knee_r_ty_func;
static dpSplineFunction tib_pat_r_r3_func;
static dpSplineFunction tib_pat_r_tx_func;
static dpSplineFunction tib_pat_r_ty_func;
static dpSplineFunction knee_l_tx_func;
static dpSplineFunction knee_l_ty_func;
static dpSplineFunction tib_pat_l_r3_func;
static dpSplineFunction tib_pat_l_tx_func;
static dpSplineFunction tib_pat_l_ty_func;


/**************** GLOBAL VARIABLES (used in only a few files) *****************/
extern dpModelStruct* sdm;


/*************** EXTERNED VARIABLES (declared in another file) ****************/



/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/


/* INIT_QS: this routine initializes the array of structures
 * that hold information about the Qs (gencoords).
 */

void init_qs(void)
{

   int i;

   sdm->q = (dpQStruct*)simm_malloc(sdm->nq*sizeof(dpQStruct));
   mstrcpy(&sdm->q[calcn_r_tx].name,"calcn_r_tx");
   sdm->q[calcn_r_tx].type = dpUnconstrainedQ;
   sdm->q[calcn_r_tx].joint = ground_calcn_rp;
   sdm->q[calcn_r_tx].axis = 0;
   sdm->q[calcn_r_tx].conversion = 1.0000000000;
   sdm->q[calcn_r_tx].initial_value = 0.0000000000;
   sdm->q[calcn_r_tx].initial_velocity = 0.0;
   sdm->q[calcn_r_tx].range_start = -5.0000000000;
   sdm->q[calcn_r_tx].range_end = 5.0000000000;
   sdm->q[calcn_r_tx].restraint_func = NULL;
   sdm->q[calcn_r_tx].min_restraint_func = NULL;
   sdm->q[calcn_r_tx].max_restraint_func = NULL;
   sdm->q[calcn_r_tx].function_active = dpNo;
   sdm->q[calcn_r_tx].constraint_func = NULL;
   sdm->q[calcn_r_tx].constraint_num = -1;
   sdm->q[calcn_r_tx].q_ind = -1;
   sdm->q[calcn_r_tx].output = dpYes;
   sdm->q[calcn_r_tx].torque = 0.0;

   mstrcpy(&sdm->q[calcn_r_ty].name,"calcn_r_ty");
   sdm->q[calcn_r_ty].type = dpUnconstrainedQ;
   sdm->q[calcn_r_ty].joint = ground_calcn_rp;
   sdm->q[calcn_r_ty].axis = 1;
   sdm->q[calcn_r_ty].conversion = 1.0000000000;
   sdm->q[calcn_r_ty].initial_value = 0.0100000000;
   sdm->q[calcn_r_ty].initial_velocity = 0.0;
   sdm->q[calcn_r_ty].range_start = -1.0000000000;
   sdm->q[calcn_r_ty].range_end = 2.0000000000;
   sdm->q[calcn_r_ty].restraint_func = NULL;
   sdm->q[calcn_r_ty].min_restraint_func = NULL;
   sdm->q[calcn_r_ty].max_restraint_func = NULL;
   sdm->q[calcn_r_ty].function_active = dpNo;
   sdm->q[calcn_r_ty].constraint_func = NULL;
   sdm->q[calcn_r_ty].constraint_num = -1;
   sdm->q[calcn_r_ty].q_ind = -1;
   sdm->q[calcn_r_ty].output = dpYes;
   sdm->q[calcn_r_ty].torque = 0.0;

   mstrcpy(&sdm->q[calcn_r_tz].name,"calcn_r_tz");
   sdm->q[calcn_r_tz].type = dpUnconstrainedQ;
   sdm->q[calcn_r_tz].joint = ground_calcn_rp;
   sdm->q[calcn_r_tz].axis = 2;
   sdm->q[calcn_r_tz].conversion = 1.0000000000;
   sdm->q[calcn_r_tz].initial_value = 0.0914200000;
   sdm->q[calcn_r_tz].initial_velocity = 0.0;
   sdm->q[calcn_r_tz].range_start = -3.0000000000;
   sdm->q[calcn_r_tz].range_end = 3.0000000000;
   sdm->q[calcn_r_tz].restraint_func = NULL;
   sdm->q[calcn_r_tz].min_restraint_func = NULL;
   sdm->q[calcn_r_tz].max_restraint_func = NULL;
   sdm->q[calcn_r_tz].function_active = dpNo;
   sdm->q[calcn_r_tz].constraint_func = NULL;
   sdm->q[calcn_r_tz].constraint_num = -1;
   sdm->q[calcn_r_tz].q_ind = -1;
   sdm->q[calcn_r_tz].output = dpYes;
   sdm->q[calcn_r_tz].torque = 0.0;

   mstrcpy(&sdm->q[calcn_r_r1].name,"calcn_r_r1");
   sdm->q[calcn_r_r1].type = dpUnconstrainedQ;
   sdm->q[calcn_r_r1].joint = ground_calcn_rp;
   sdm->q[calcn_r_r1].axis = 3;
   sdm->q[calcn_r_r1].conversion = 57.2957795131;
   sdm->q[calcn_r_r1].initial_value = 0.0000000000;
   sdm->q[calcn_r_r1].initial_velocity = 0.0;
   sdm->q[calcn_r_r1].range_start = -360.0000000000;
   sdm->q[calcn_r_r1].range_end = 360.0000000000;
   sdm->q[calcn_r_r1].restraint_func = NULL;
   sdm->q[calcn_r_r1].min_restraint_func = NULL;
   sdm->q[calcn_r_r1].max_restraint_func = NULL;
   sdm->q[calcn_r_r1].function_active = dpNo;
   sdm->q[calcn_r_r1].constraint_func = NULL;
   sdm->q[calcn_r_r1].constraint_num = -1;
   sdm->q[calcn_r_r1].q_ind = -1;
   sdm->q[calcn_r_r1].output = dpYes;
   sdm->q[calcn_r_r1].torque = 0.0;

   mstrcpy(&sdm->q[calcn_r_r2].name,"calcn_r_r2");
   sdm->q[calcn_r_r2].type = dpUnconstrainedQ;
   sdm->q[calcn_r_r2].joint = ground_calcn_rp;
   sdm->q[calcn_r_r2].axis = 4;
   sdm->q[calcn_r_r2].conversion = 57.2957795131;
   sdm->q[calcn_r_r2].initial_value = 0.0000000000;
   sdm->q[calcn_r_r2].initial_velocity = 0.0;
   sdm->q[calcn_r_r2].range_start = -360.0000000000;
   sdm->q[calcn_r_r2].range_end = 360.0000000000;
   sdm->q[calcn_r_r2].restraint_func = NULL;
   sdm->q[calcn_r_r2].min_restraint_func = NULL;
   sdm->q[calcn_r_r2].max_restraint_func = NULL;
   sdm->q[calcn_r_r2].function_active = dpNo;
   sdm->q[calcn_r_r2].constraint_func = NULL;
   sdm->q[calcn_r_r2].constraint_num = -1;
   sdm->q[calcn_r_r2].q_ind = -1;
   sdm->q[calcn_r_r2].output = dpYes;
   sdm->q[calcn_r_r2].torque = 0.0;

   mstrcpy(&sdm->q[calcn_r_r3].name,"calcn_r_r3");
   sdm->q[calcn_r_r3].type = dpUnconstrainedQ;
   sdm->q[calcn_r_r3].joint = ground_calcn_rp;
   sdm->q[calcn_r_r3].axis = 5;
   sdm->q[calcn_r_r3].conversion = 57.2957795131;
   sdm->q[calcn_r_r3].initial_value = 0.0000000000;
   sdm->q[calcn_r_r3].initial_velocity = 0.0;
   sdm->q[calcn_r_r3].range_start = -360.0000000000;
   sdm->q[calcn_r_r3].range_end = 360.0000000000;
   sdm->q[calcn_r_r3].restraint_func = NULL;
   sdm->q[calcn_r_r3].min_restraint_func = NULL;
   sdm->q[calcn_r_r3].max_restraint_func = NULL;
   sdm->q[calcn_r_r3].function_active = dpNo;
   sdm->q[calcn_r_r3].constraint_func = NULL;
   sdm->q[calcn_r_r3].constraint_num = -1;
   sdm->q[calcn_r_r3].q_ind = -1;
   sdm->q[calcn_r_r3].output = dpYes;
   sdm->q[calcn_r_r3].torque = 0.0;

   mstrcpy(&sdm->q[calcn_l_tx].name,"calcn_l_tx");
   sdm->q[calcn_l_tx].type = dpUnconstrainedQ;
   sdm->q[calcn_l_tx].joint = ground_calcn_lp;
   sdm->q[calcn_l_tx].axis = 0;
   sdm->q[calcn_l_tx].conversion = 1.0000000000;
   sdm->q[calcn_l_tx].initial_value = 0.0000000000;
   sdm->q[calcn_l_tx].initial_velocity = 0.0;
   sdm->q[calcn_l_tx].range_start = -5.0000000000;
   sdm->q[calcn_l_tx].range_end = 5.0000000000;
   sdm->q[calcn_l_tx].restraint_func = NULL;
   sdm->q[calcn_l_tx].min_restraint_func = NULL;
   sdm->q[calcn_l_tx].max_restraint_func = NULL;
   sdm->q[calcn_l_tx].function_active = dpNo;
   sdm->q[calcn_l_tx].constraint_func = NULL;
   sdm->q[calcn_l_tx].constraint_num = -1;
   sdm->q[calcn_l_tx].q_ind = -1;
   sdm->q[calcn_l_tx].output = dpYes;
   sdm->q[calcn_l_tx].torque = 0.0;

   mstrcpy(&sdm->q[calcn_l_ty].name,"calcn_l_ty");
   sdm->q[calcn_l_ty].type = dpUnconstrainedQ;
   sdm->q[calcn_l_ty].joint = ground_calcn_lp;
   sdm->q[calcn_l_ty].axis = 1;
   sdm->q[calcn_l_ty].conversion = 1.0000000000;
   sdm->q[calcn_l_ty].initial_value = 0.0100000000;
   sdm->q[calcn_l_ty].initial_velocity = 0.0;
   sdm->q[calcn_l_ty].range_start = -1.0000000000;
   sdm->q[calcn_l_ty].range_end = 2.0000000000;
   sdm->q[calcn_l_ty].restraint_func = NULL;
   sdm->q[calcn_l_ty].min_restraint_func = NULL;
   sdm->q[calcn_l_ty].max_restraint_func = NULL;
   sdm->q[calcn_l_ty].function_active = dpNo;
   sdm->q[calcn_l_ty].constraint_func = NULL;
   sdm->q[calcn_l_ty].constraint_num = -1;
   sdm->q[calcn_l_ty].q_ind = -1;
   sdm->q[calcn_l_ty].output = dpYes;
   sdm->q[calcn_l_ty].torque = 0.0;

   mstrcpy(&sdm->q[calcn_l_tz].name,"calcn_l_tz");
   sdm->q[calcn_l_tz].type = dpUnconstrainedQ;
   sdm->q[calcn_l_tz].joint = ground_calcn_lp;
   sdm->q[calcn_l_tz].axis = 2;
   sdm->q[calcn_l_tz].conversion = 1.0000000000;
   sdm->q[calcn_l_tz].initial_value = -0.0914200000;
   sdm->q[calcn_l_tz].initial_velocity = 0.0;
   sdm->q[calcn_l_tz].range_start = -3.0000000000;
   sdm->q[calcn_l_tz].range_end = 3.0000000000;
   sdm->q[calcn_l_tz].restraint_func = NULL;
   sdm->q[calcn_l_tz].min_restraint_func = NULL;
   sdm->q[calcn_l_tz].max_restraint_func = NULL;
   sdm->q[calcn_l_tz].function_active = dpNo;
   sdm->q[calcn_l_tz].constraint_func = NULL;
   sdm->q[calcn_l_tz].constraint_num = -1;
   sdm->q[calcn_l_tz].q_ind = -1;
   sdm->q[calcn_l_tz].output = dpYes;
   sdm->q[calcn_l_tz].torque = 0.0;

   mstrcpy(&sdm->q[calcn_l_r1].name,"calcn_l_r1");
   sdm->q[calcn_l_r1].type = dpUnconstrainedQ;
   sdm->q[calcn_l_r1].joint = ground_calcn_lp;
   sdm->q[calcn_l_r1].axis = 3;
   sdm->q[calcn_l_r1].conversion = 57.2957795131;
   sdm->q[calcn_l_r1].initial_value = 0.0000000000;
   sdm->q[calcn_l_r1].initial_velocity = 0.0;
   sdm->q[calcn_l_r1].range_start = -360.0000000000;
   sdm->q[calcn_l_r1].range_end = 360.0000000000;
   sdm->q[calcn_l_r1].restraint_func = NULL;
   sdm->q[calcn_l_r1].min_restraint_func = NULL;
   sdm->q[calcn_l_r1].max_restraint_func = NULL;
   sdm->q[calcn_l_r1].function_active = dpNo;
   sdm->q[calcn_l_r1].constraint_func = NULL;
   sdm->q[calcn_l_r1].constraint_num = -1;
   sdm->q[calcn_l_r1].q_ind = -1;
   sdm->q[calcn_l_r1].output = dpYes;
   sdm->q[calcn_l_r1].torque = 0.0;

   mstrcpy(&sdm->q[calcn_l_r2].name,"calcn_l_r2");
   sdm->q[calcn_l_r2].type = dpUnconstrainedQ;
   sdm->q[calcn_l_r2].joint = ground_calcn_lp;
   sdm->q[calcn_l_r2].axis = 4;
   sdm->q[calcn_l_r2].conversion = 57.2957795131;
   sdm->q[calcn_l_r2].initial_value = 0.0000000000;
   sdm->q[calcn_l_r2].initial_velocity = 0.0;
   sdm->q[calcn_l_r2].range_start = -360.0000000000;
   sdm->q[calcn_l_r2].range_end = 360.0000000000;
   sdm->q[calcn_l_r2].restraint_func = NULL;
   sdm->q[calcn_l_r2].min_restraint_func = NULL;
   sdm->q[calcn_l_r2].max_restraint_func = NULL;
   sdm->q[calcn_l_r2].function_active = dpNo;
   sdm->q[calcn_l_r2].constraint_func = NULL;
   sdm->q[calcn_l_r2].constraint_num = -1;
   sdm->q[calcn_l_r2].q_ind = -1;
   sdm->q[calcn_l_r2].output = dpYes;
   sdm->q[calcn_l_r2].torque = 0.0;

   mstrcpy(&sdm->q[calcn_l_r3].name,"calcn_l_r3");
   sdm->q[calcn_l_r3].type = dpUnconstrainedQ;
   sdm->q[calcn_l_r3].joint = ground_calcn_lp;
   sdm->q[calcn_l_r3].axis = 5;
   sdm->q[calcn_l_r3].conversion = 57.2957795131;
   sdm->q[calcn_l_r3].initial_value = 0.0000000000;
   sdm->q[calcn_l_r3].initial_velocity = 0.0;
   sdm->q[calcn_l_r3].range_start = -360.0000000000;
   sdm->q[calcn_l_r3].range_end = 360.0000000000;
   sdm->q[calcn_l_r3].restraint_func = NULL;
   sdm->q[calcn_l_r3].min_restraint_func = NULL;
   sdm->q[calcn_l_r3].max_restraint_func = NULL;
   sdm->q[calcn_l_r3].function_active = dpNo;
   sdm->q[calcn_l_r3].constraint_func = NULL;
   sdm->q[calcn_l_r3].constraint_num = -1;
   sdm->q[calcn_l_r3].q_ind = -1;
   sdm->q[calcn_l_r3].output = dpYes;
   sdm->q[calcn_l_r3].torque = 0.0;

   mstrcpy(&sdm->q[pelvis_tz].name,"pelvis_tz");
   sdm->q[pelvis_tz].type = dpUnconstrainedQ;
   sdm->q[pelvis_tz].joint = ground_pelvis;
   sdm->q[pelvis_tz].axis = 0;
   sdm->q[pelvis_tz].conversion = 1.0000000000;
   sdm->q[pelvis_tz].initial_value = 0.0000000000;
   sdm->q[pelvis_tz].initial_velocity = 0.0;
   sdm->q[pelvis_tz].range_start = -3.0000000000;
   sdm->q[pelvis_tz].range_end = 3.0000000000;
   sdm->q[pelvis_tz].restraint_func = NULL;
   sdm->q[pelvis_tz].min_restraint_func = NULL;
   sdm->q[pelvis_tz].max_restraint_func = NULL;
   sdm->q[pelvis_tz].function_active = dpNo;
   sdm->q[pelvis_tz].constraint_func = NULL;
   sdm->q[pelvis_tz].constraint_num = -1;
   sdm->q[pelvis_tz].q_ind = -1;
   sdm->q[pelvis_tz].output = dpYes;
   sdm->q[pelvis_tz].torque = 0.0;

   mstrcpy(&sdm->q[pelvis_tx].name,"pelvis_tx");
   sdm->q[pelvis_tx].type = dpUnconstrainedQ;
   sdm->q[pelvis_tx].joint = ground_pelvis;
   sdm->q[pelvis_tx].axis = 1;
   sdm->q[pelvis_tx].conversion = 1.0000000000;
   sdm->q[pelvis_tx].initial_value = 0.1200000000;
   sdm->q[pelvis_tx].initial_velocity = 0.0;
   sdm->q[pelvis_tx].range_start = -5.0000000000;
   sdm->q[pelvis_tx].range_end = 5.0000000000;
   sdm->q[pelvis_tx].restraint_func = NULL;
   sdm->q[pelvis_tx].min_restraint_func = NULL;
   sdm->q[pelvis_tx].max_restraint_func = NULL;
   sdm->q[pelvis_tx].function_active = dpNo;
   sdm->q[pelvis_tx].constraint_func = NULL;
   sdm->q[pelvis_tx].constraint_num = -1;
   sdm->q[pelvis_tx].q_ind = -1;
   sdm->q[pelvis_tx].output = dpYes;
   sdm->q[pelvis_tx].torque = 0.0;

   mstrcpy(&sdm->q[pelvis_ty].name,"pelvis_ty");
   sdm->q[pelvis_ty].type = dpUnconstrainedQ;
   sdm->q[pelvis_ty].joint = ground_pelvis;
   sdm->q[pelvis_ty].axis = 2;
   sdm->q[pelvis_ty].conversion = 1.0000000000;
   sdm->q[pelvis_ty].initial_value = 0.9300000000;
   sdm->q[pelvis_ty].initial_velocity = 0.0;
   sdm->q[pelvis_ty].range_start = -1.0000000000;
   sdm->q[pelvis_ty].range_end = 2.0000000000;
   sdm->q[pelvis_ty].restraint_func = NULL;
   sdm->q[pelvis_ty].min_restraint_func = NULL;
   sdm->q[pelvis_ty].max_restraint_func = NULL;
   sdm->q[pelvis_ty].function_active = dpNo;
   sdm->q[pelvis_ty].constraint_func = NULL;
   sdm->q[pelvis_ty].constraint_num = -1;
   sdm->q[pelvis_ty].q_ind = -1;
   sdm->q[pelvis_ty].output = dpYes;
   sdm->q[pelvis_ty].torque = 0.0;

   mstrcpy(&sdm->q[pelvis_tilt].name,"pelvis_tilt");
   sdm->q[pelvis_tilt].type = dpUnconstrainedQ;
   sdm->q[pelvis_tilt].joint = ground_pelvis;
   sdm->q[pelvis_tilt].axis = 3;
   sdm->q[pelvis_tilt].conversion = 57.2957795131;
   sdm->q[pelvis_tilt].initial_value = 0.0000000000;
   sdm->q[pelvis_tilt].initial_velocity = 0.0;
   sdm->q[pelvis_tilt].range_start = -90.0000000000;
   sdm->q[pelvis_tilt].range_end = 90.0000000000;
   sdm->q[pelvis_tilt].restraint_func = NULL;
   sdm->q[pelvis_tilt].min_restraint_func = NULL;
   sdm->q[pelvis_tilt].max_restraint_func = NULL;
   sdm->q[pelvis_tilt].function_active = dpNo;
   sdm->q[pelvis_tilt].constraint_func = NULL;
   sdm->q[pelvis_tilt].constraint_num = -1;
   sdm->q[pelvis_tilt].q_ind = -1;
   sdm->q[pelvis_tilt].output = dpYes;
   sdm->q[pelvis_tilt].torque = 0.0;

   mstrcpy(&sdm->q[pelvis_list].name,"pelvis_list");
   sdm->q[pelvis_list].type = dpUnconstrainedQ;
   sdm->q[pelvis_list].joint = ground_pelvis;
   sdm->q[pelvis_list].axis = 4;
   sdm->q[pelvis_list].conversion = 57.2957795131;
   sdm->q[pelvis_list].initial_value = 0.0000000000;
   sdm->q[pelvis_list].initial_velocity = 0.0;
   sdm->q[pelvis_list].range_start = -90.0000000000;
   sdm->q[pelvis_list].range_end = 90.0000000000;
   sdm->q[pelvis_list].restraint_func = NULL;
   sdm->q[pelvis_list].min_restraint_func = NULL;
   sdm->q[pelvis_list].max_restraint_func = NULL;
   sdm->q[pelvis_list].function_active = dpNo;
   sdm->q[pelvis_list].constraint_func = NULL;
   sdm->q[pelvis_list].constraint_num = -1;
   sdm->q[pelvis_list].q_ind = -1;
   sdm->q[pelvis_list].output = dpYes;
   sdm->q[pelvis_list].torque = 0.0;

   mstrcpy(&sdm->q[pelvis_rotation].name,"pelvis_rotation");
   sdm->q[pelvis_rotation].type = dpUnconstrainedQ;
   sdm->q[pelvis_rotation].joint = ground_pelvis;
   sdm->q[pelvis_rotation].axis = 5;
   sdm->q[pelvis_rotation].conversion = 57.2957795131;
   sdm->q[pelvis_rotation].initial_value = 0.0000000000;
   sdm->q[pelvis_rotation].initial_velocity = 0.0;
   sdm->q[pelvis_rotation].range_start = -90.0000000000;
   sdm->q[pelvis_rotation].range_end = 90.0000000000;
   sdm->q[pelvis_rotation].restraint_func = NULL;
   sdm->q[pelvis_rotation].min_restraint_func = NULL;
   sdm->q[pelvis_rotation].max_restraint_func = NULL;
   sdm->q[pelvis_rotation].function_active = dpNo;
   sdm->q[pelvis_rotation].constraint_func = NULL;
   sdm->q[pelvis_rotation].constraint_num = -1;
   sdm->q[pelvis_rotation].q_ind = -1;
   sdm->q[pelvis_rotation].output = dpYes;
   sdm->q[pelvis_rotation].torque = 0.0;

   mstrcpy(&sdm->q[hip_flexion_r].name,"hip_flexion_r");
   sdm->q[hip_flexion_r].type = dpUnconstrainedQ;
   sdm->q[hip_flexion_r].joint = hip_r;
   sdm->q[hip_flexion_r].axis = 0;
   sdm->q[hip_flexion_r].conversion = 57.2957795131;
   sdm->q[hip_flexion_r].initial_value = 0.0000000000;
   sdm->q[hip_flexion_r].initial_velocity = 0.0;
   sdm->q[hip_flexion_r].range_start = -120.0000000000;
   sdm->q[hip_flexion_r].range_end = 120.0000000000;
   sdm->q[hip_flexion_r].restraint_func = NULL;
   sdm->q[hip_flexion_r].min_restraint_func = NULL;
   sdm->q[hip_flexion_r].max_restraint_func = NULL;
   sdm->q[hip_flexion_r].function_active = dpNo;
   sdm->q[hip_flexion_r].constraint_func = NULL;
   sdm->q[hip_flexion_r].constraint_num = -1;
   sdm->q[hip_flexion_r].q_ind = -1;
   sdm->q[hip_flexion_r].output = dpYes;
   sdm->q[hip_flexion_r].torque = 0.0;

   mstrcpy(&sdm->q[hip_adduction_r].name,"hip_adduction_r");
   sdm->q[hip_adduction_r].type = dpUnconstrainedQ;
   sdm->q[hip_adduction_r].joint = hip_r;
   sdm->q[hip_adduction_r].axis = 1;
   sdm->q[hip_adduction_r].conversion = 57.2957795131;
   sdm->q[hip_adduction_r].initial_value = 0.0000000000;
   sdm->q[hip_adduction_r].initial_velocity = 0.0;
   sdm->q[hip_adduction_r].range_start = -120.0000000000;
   sdm->q[hip_adduction_r].range_end = 120.0000000000;
   sdm->q[hip_adduction_r].restraint_func = NULL;
   sdm->q[hip_adduction_r].min_restraint_func = NULL;
   sdm->q[hip_adduction_r].max_restraint_func = NULL;
   sdm->q[hip_adduction_r].function_active = dpNo;
   sdm->q[hip_adduction_r].constraint_func = NULL;
   sdm->q[hip_adduction_r].constraint_num = -1;
   sdm->q[hip_adduction_r].q_ind = -1;
   sdm->q[hip_adduction_r].output = dpYes;
   sdm->q[hip_adduction_r].torque = 0.0;

   mstrcpy(&sdm->q[hip_rotation_r].name,"hip_rotation_r");
   sdm->q[hip_rotation_r].type = dpUnconstrainedQ;
   sdm->q[hip_rotation_r].joint = hip_r;
   sdm->q[hip_rotation_r].axis = 2;
   sdm->q[hip_rotation_r].conversion = 57.2957795131;
   sdm->q[hip_rotation_r].initial_value = 0.0000000000;
   sdm->q[hip_rotation_r].initial_velocity = 0.0;
   sdm->q[hip_rotation_r].range_start = -120.0000000000;
   sdm->q[hip_rotation_r].range_end = 120.0000000000;
   sdm->q[hip_rotation_r].restraint_func = NULL;
   sdm->q[hip_rotation_r].min_restraint_func = NULL;
   sdm->q[hip_rotation_r].max_restraint_func = NULL;
   sdm->q[hip_rotation_r].function_active = dpNo;
   sdm->q[hip_rotation_r].constraint_func = NULL;
   sdm->q[hip_rotation_r].constraint_num = -1;
   sdm->q[hip_rotation_r].q_ind = -1;
   sdm->q[hip_rotation_r].output = dpYes;
   sdm->q[hip_rotation_r].torque = 0.0;

   mstrcpy(&sdm->q[knee_r_tx].name,"knee_r_tx");
   sdm->q[knee_r_tx].type = dpConstrainedQ;
   sdm->q[knee_r_tx].joint = knee_r;
   sdm->q[knee_r_tx].axis = 0;
   sdm->q[knee_r_tx].conversion = 1.0000000000;
   sdm->q[knee_r_tx].initial_value = -0.0042504136;
   sdm->q[knee_r_tx].initial_velocity = 0.0;
   sdm->q[knee_r_tx].range_start = -99999.9;
   sdm->q[knee_r_tx].range_end = 99999.9;
   sdm->q[knee_r_tx].restraint_func = NULL;
   sdm->q[knee_r_tx].min_restraint_func = NULL;
   sdm->q[knee_r_tx].max_restraint_func = NULL;
   sdm->q[knee_r_tx].function_active = dpNo;
   sdm->q[knee_r_tx].constraint_func = &knee_r_tx_func;
   sdm->q[knee_r_tx].constraint_num = knee_r_tx_con;
   sdm->q[knee_r_tx].q_ind = knee_angle_r;
   sdm->q[knee_r_tx].output = dpNo;
   sdm->q[knee_r_tx].torque = 0.0;

   mstrcpy(&sdm->q[knee_r_ty].name,"knee_r_ty");
   sdm->q[knee_r_ty].type = dpConstrainedQ;
   sdm->q[knee_r_ty].joint = knee_r;
   sdm->q[knee_r_ty].axis = 1;
   sdm->q[knee_r_ty].conversion = 1.0000000000;
   sdm->q[knee_r_ty].initial_value = -0.3738789988;
   sdm->q[knee_r_ty].initial_velocity = 0.0;
   sdm->q[knee_r_ty].range_start = -99999.9;
   sdm->q[knee_r_ty].range_end = 99999.9;
   sdm->q[knee_r_ty].restraint_func = NULL;
   sdm->q[knee_r_ty].min_restraint_func = NULL;
   sdm->q[knee_r_ty].max_restraint_func = NULL;
   sdm->q[knee_r_ty].function_active = dpNo;
   sdm->q[knee_r_ty].constraint_func = &knee_r_ty_func;
   sdm->q[knee_r_ty].constraint_num = knee_r_ty_con;
   sdm->q[knee_r_ty].q_ind = knee_angle_r;
   sdm->q[knee_r_ty].output = dpNo;
   sdm->q[knee_r_ty].torque = 0.0;

   mstrcpy(&sdm->q[knee_angle_r].name,"knee_angle_r");
   sdm->q[knee_angle_r].type = dpUnconstrainedQ;
   sdm->q[knee_angle_r].joint = knee_r;
   sdm->q[knee_angle_r].axis = 2;
   sdm->q[knee_angle_r].conversion = 57.2957795131;
   sdm->q[knee_angle_r].initial_value = 0.0000000000;
   sdm->q[knee_angle_r].initial_velocity = 0.0;
   sdm->q[knee_angle_r].range_start = -120.0000000000;
   sdm->q[knee_angle_r].range_end = 10.0000000000;
   sdm->q[knee_angle_r].restraint_func = NULL;
   sdm->q[knee_angle_r].min_restraint_func = NULL;
   sdm->q[knee_angle_r].max_restraint_func = NULL;
   sdm->q[knee_angle_r].function_active = dpNo;
   sdm->q[knee_angle_r].constraint_func = NULL;
   sdm->q[knee_angle_r].constraint_num = -1;
   sdm->q[knee_angle_r].q_ind = -1;
   sdm->q[knee_angle_r].output = dpYes;
   sdm->q[knee_angle_r].torque = 0.0;

   mstrcpy(&sdm->q[tib_pat_r_tx].name,"tib_pat_r_tx");
   sdm->q[tib_pat_r_tx].type = dpConstrainedQ;
   sdm->q[tib_pat_r_tx].joint = tib_pat_r;
   sdm->q[tib_pat_r_tx].axis = 0;
   sdm->q[tib_pat_r_tx].conversion = 1.0000000000;
   sdm->q[tib_pat_r_tx].initial_value = 0.0460148211;
   sdm->q[tib_pat_r_tx].initial_velocity = 0.0;
   sdm->q[tib_pat_r_tx].range_start = -99999.9;
   sdm->q[tib_pat_r_tx].range_end = 99999.9;
   sdm->q[tib_pat_r_tx].restraint_func = NULL;
   sdm->q[tib_pat_r_tx].min_restraint_func = NULL;
   sdm->q[tib_pat_r_tx].max_restraint_func = NULL;
   sdm->q[tib_pat_r_tx].function_active = dpNo;
   sdm->q[tib_pat_r_tx].constraint_func = &tib_pat_r_tx_func;
   sdm->q[tib_pat_r_tx].constraint_num = tib_pat_r_tx_con;
   sdm->q[tib_pat_r_tx].q_ind = knee_angle_r;
   sdm->q[tib_pat_r_tx].output = dpNo;
   sdm->q[tib_pat_r_tx].torque = 0.0;

   mstrcpy(&sdm->q[tib_pat_r_ty].name,"tib_pat_r_ty");
   sdm->q[tib_pat_r_ty].type = dpConstrainedQ;
   sdm->q[tib_pat_r_ty].joint = tib_pat_r;
   sdm->q[tib_pat_r_ty].axis = 1;
   sdm->q[tib_pat_r_ty].conversion = 1.0000000000;
   sdm->q[tib_pat_r_ty].initial_value = -0.0210592024;
   sdm->q[tib_pat_r_ty].initial_velocity = 0.0;
   sdm->q[tib_pat_r_ty].range_start = -99999.9;
   sdm->q[tib_pat_r_ty].range_end = 99999.9;
   sdm->q[tib_pat_r_ty].restraint_func = NULL;
   sdm->q[tib_pat_r_ty].min_restraint_func = NULL;
   sdm->q[tib_pat_r_ty].max_restraint_func = NULL;
   sdm->q[tib_pat_r_ty].function_active = dpNo;
   sdm->q[tib_pat_r_ty].constraint_func = &tib_pat_r_ty_func;
   sdm->q[tib_pat_r_ty].constraint_num = tib_pat_r_ty_con;
   sdm->q[tib_pat_r_ty].q_ind = knee_angle_r;
   sdm->q[tib_pat_r_ty].output = dpNo;
   sdm->q[tib_pat_r_ty].torque = 0.0;

   mstrcpy(&sdm->q[tib_pat_r_r3].name,"tib_pat_r_r3");
   sdm->q[tib_pat_r_r3].type = dpConstrainedQ;
   sdm->q[tib_pat_r_r3].joint = tib_pat_r;
   sdm->q[tib_pat_r_r3].axis = 2;
   sdm->q[tib_pat_r_r3].conversion = 57.2957795131;
   sdm->q[tib_pat_r_r3].initial_value = -0.0669882444;
   sdm->q[tib_pat_r_r3].initial_velocity = 0.0;
   sdm->q[tib_pat_r_r3].range_start = -99999.9;
   sdm->q[tib_pat_r_r3].range_end = 99999.9;
   sdm->q[tib_pat_r_r3].restraint_func = NULL;
   sdm->q[tib_pat_r_r3].min_restraint_func = NULL;
   sdm->q[tib_pat_r_r3].max_restraint_func = NULL;
   sdm->q[tib_pat_r_r3].function_active = dpNo;
   sdm->q[tib_pat_r_r3].constraint_func = &tib_pat_r_r3_func;
   sdm->q[tib_pat_r_r3].constraint_num = tib_pat_r_r3_con;
   sdm->q[tib_pat_r_r3].q_ind = knee_angle_r;
   sdm->q[tib_pat_r_r3].output = dpNo;
   sdm->q[tib_pat_r_r3].torque = 0.0;

   mstrcpy(&sdm->q[ankle_angle_r].name,"ankle_angle_r");
   sdm->q[ankle_angle_r].type = dpUnconstrainedQ;
   sdm->q[ankle_angle_r].joint = ankle_r;
   sdm->q[ankle_angle_r].axis = 0;
   sdm->q[ankle_angle_r].conversion = 57.2957795131;
   sdm->q[ankle_angle_r].initial_value = 0.0000000000;
   sdm->q[ankle_angle_r].initial_velocity = 0.0;
   sdm->q[ankle_angle_r].range_start = -90.0000000000;
   sdm->q[ankle_angle_r].range_end = 90.0000000000;
   sdm->q[ankle_angle_r].restraint_func = NULL;
   sdm->q[ankle_angle_r].min_restraint_func = NULL;
   sdm->q[ankle_angle_r].max_restraint_func = NULL;
   sdm->q[ankle_angle_r].function_active = dpNo;
   sdm->q[ankle_angle_r].constraint_func = NULL;
   sdm->q[ankle_angle_r].constraint_num = -1;
   sdm->q[ankle_angle_r].q_ind = -1;
   sdm->q[ankle_angle_r].output = dpYes;
   sdm->q[ankle_angle_r].torque = 0.0;

   mstrcpy(&sdm->q[subtalar_angle_r].name,"subtalar_angle_r");
   sdm->q[subtalar_angle_r].type = dpUnconstrainedQ;
   sdm->q[subtalar_angle_r].joint = subtalar_r;
   sdm->q[subtalar_angle_r].axis = 0;
   sdm->q[subtalar_angle_r].conversion = 57.2957795131;
   sdm->q[subtalar_angle_r].initial_value = 0.0000000000;
   sdm->q[subtalar_angle_r].initial_velocity = 0.0;
   sdm->q[subtalar_angle_r].range_start = -90.0000000000;
   sdm->q[subtalar_angle_r].range_end = 90.0000000000;
   sdm->q[subtalar_angle_r].restraint_func = NULL;
   sdm->q[subtalar_angle_r].min_restraint_func = NULL;
   sdm->q[subtalar_angle_r].max_restraint_func = NULL;
   sdm->q[subtalar_angle_r].function_active = dpNo;
   sdm->q[subtalar_angle_r].constraint_func = NULL;
   sdm->q[subtalar_angle_r].constraint_num = -1;
   sdm->q[subtalar_angle_r].q_ind = -1;
   sdm->q[subtalar_angle_r].output = dpYes;
   sdm->q[subtalar_angle_r].torque = 0.0;

   mstrcpy(&sdm->q[mtp_angle_r].name,"mtp_angle_r");
   sdm->q[mtp_angle_r].type = dpUnconstrainedQ;
   sdm->q[mtp_angle_r].joint = mtp_r;
   sdm->q[mtp_angle_r].axis = 0;
   sdm->q[mtp_angle_r].conversion = 57.2957795131;
   sdm->q[mtp_angle_r].initial_value = 0.0000000000;
   sdm->q[mtp_angle_r].initial_velocity = 0.0;
   sdm->q[mtp_angle_r].range_start = -90.0000000000;
   sdm->q[mtp_angle_r].range_end = 90.0000000000;
   sdm->q[mtp_angle_r].restraint_func = NULL;
   sdm->q[mtp_angle_r].min_restraint_func = NULL;
   sdm->q[mtp_angle_r].max_restraint_func = NULL;
   sdm->q[mtp_angle_r].function_active = dpNo;
   sdm->q[mtp_angle_r].constraint_func = NULL;
   sdm->q[mtp_angle_r].constraint_num = -1;
   sdm->q[mtp_angle_r].q_ind = -1;
   sdm->q[mtp_angle_r].output = dpYes;
   sdm->q[mtp_angle_r].torque = 0.0;

   mstrcpy(&sdm->q[hip_flexion_l].name,"hip_flexion_l");
   sdm->q[hip_flexion_l].type = dpUnconstrainedQ;
   sdm->q[hip_flexion_l].joint = hip_l;
   sdm->q[hip_flexion_l].axis = 0;
   sdm->q[hip_flexion_l].conversion = 57.2957795131;
   sdm->q[hip_flexion_l].initial_value = 0.0000000000;
   sdm->q[hip_flexion_l].initial_velocity = 0.0;
   sdm->q[hip_flexion_l].range_start = -120.0000000000;
   sdm->q[hip_flexion_l].range_end = 120.0000000000;
   sdm->q[hip_flexion_l].restraint_func = NULL;
   sdm->q[hip_flexion_l].min_restraint_func = NULL;
   sdm->q[hip_flexion_l].max_restraint_func = NULL;
   sdm->q[hip_flexion_l].function_active = dpNo;
   sdm->q[hip_flexion_l].constraint_func = NULL;
   sdm->q[hip_flexion_l].constraint_num = -1;
   sdm->q[hip_flexion_l].q_ind = -1;
   sdm->q[hip_flexion_l].output = dpYes;
   sdm->q[hip_flexion_l].torque = 0.0;

   mstrcpy(&sdm->q[hip_adduction_l].name,"hip_adduction_l");
   sdm->q[hip_adduction_l].type = dpUnconstrainedQ;
   sdm->q[hip_adduction_l].joint = hip_l;
   sdm->q[hip_adduction_l].axis = 1;
   sdm->q[hip_adduction_l].conversion = 57.2957795131;
   sdm->q[hip_adduction_l].initial_value = 0.0000000000;
   sdm->q[hip_adduction_l].initial_velocity = 0.0;
   sdm->q[hip_adduction_l].range_start = -120.0000000000;
   sdm->q[hip_adduction_l].range_end = 120.0000000000;
   sdm->q[hip_adduction_l].restraint_func = NULL;
   sdm->q[hip_adduction_l].min_restraint_func = NULL;
   sdm->q[hip_adduction_l].max_restraint_func = NULL;
   sdm->q[hip_adduction_l].function_active = dpNo;
   sdm->q[hip_adduction_l].constraint_func = NULL;
   sdm->q[hip_adduction_l].constraint_num = -1;
   sdm->q[hip_adduction_l].q_ind = -1;
   sdm->q[hip_adduction_l].output = dpYes;
   sdm->q[hip_adduction_l].torque = 0.0;

   mstrcpy(&sdm->q[hip_rotation_l].name,"hip_rotation_l");
   sdm->q[hip_rotation_l].type = dpUnconstrainedQ;
   sdm->q[hip_rotation_l].joint = hip_l;
   sdm->q[hip_rotation_l].axis = 2;
   sdm->q[hip_rotation_l].conversion = 57.2957795131;
   sdm->q[hip_rotation_l].initial_value = 0.0000000000;
   sdm->q[hip_rotation_l].initial_velocity = 0.0;
   sdm->q[hip_rotation_l].range_start = -120.0000000000;
   sdm->q[hip_rotation_l].range_end = 120.0000000000;
   sdm->q[hip_rotation_l].restraint_func = NULL;
   sdm->q[hip_rotation_l].min_restraint_func = NULL;
   sdm->q[hip_rotation_l].max_restraint_func = NULL;
   sdm->q[hip_rotation_l].function_active = dpNo;
   sdm->q[hip_rotation_l].constraint_func = NULL;
   sdm->q[hip_rotation_l].constraint_num = -1;
   sdm->q[hip_rotation_l].q_ind = -1;
   sdm->q[hip_rotation_l].output = dpYes;
   sdm->q[hip_rotation_l].torque = 0.0;

   mstrcpy(&sdm->q[knee_l_tx].name,"knee_l_tx");
   sdm->q[knee_l_tx].type = dpConstrainedQ;
   sdm->q[knee_l_tx].joint = knee_l;
   sdm->q[knee_l_tx].axis = 0;
   sdm->q[knee_l_tx].conversion = 1.0000000000;
   sdm->q[knee_l_tx].initial_value = -0.0042504136;
   sdm->q[knee_l_tx].initial_velocity = 0.0;
   sdm->q[knee_l_tx].range_start = -99999.9;
   sdm->q[knee_l_tx].range_end = 99999.9;
   sdm->q[knee_l_tx].restraint_func = NULL;
   sdm->q[knee_l_tx].min_restraint_func = NULL;
   sdm->q[knee_l_tx].max_restraint_func = NULL;
   sdm->q[knee_l_tx].function_active = dpNo;
   sdm->q[knee_l_tx].constraint_func = &knee_l_tx_func;
   sdm->q[knee_l_tx].constraint_num = knee_l_tx_con;
   sdm->q[knee_l_tx].q_ind = knee_angle_l;
   sdm->q[knee_l_tx].output = dpNo;
   sdm->q[knee_l_tx].torque = 0.0;

   mstrcpy(&sdm->q[knee_l_ty].name,"knee_l_ty");
   sdm->q[knee_l_ty].type = dpConstrainedQ;
   sdm->q[knee_l_ty].joint = knee_l;
   sdm->q[knee_l_ty].axis = 1;
   sdm->q[knee_l_ty].conversion = 1.0000000000;
   sdm->q[knee_l_ty].initial_value = -0.3738789988;
   sdm->q[knee_l_ty].initial_velocity = 0.0;
   sdm->q[knee_l_ty].range_start = -99999.9;
   sdm->q[knee_l_ty].range_end = 99999.9;
   sdm->q[knee_l_ty].restraint_func = NULL;
   sdm->q[knee_l_ty].min_restraint_func = NULL;
   sdm->q[knee_l_ty].max_restraint_func = NULL;
   sdm->q[knee_l_ty].function_active = dpNo;
   sdm->q[knee_l_ty].constraint_func = &knee_l_ty_func;
   sdm->q[knee_l_ty].constraint_num = knee_l_ty_con;
   sdm->q[knee_l_ty].q_ind = knee_angle_l;
   sdm->q[knee_l_ty].output = dpNo;
   sdm->q[knee_l_ty].torque = 0.0;

   mstrcpy(&sdm->q[knee_angle_l].name,"knee_angle_l");
   sdm->q[knee_angle_l].type = dpUnconstrainedQ;
   sdm->q[knee_angle_l].joint = knee_l;
   sdm->q[knee_angle_l].axis = 2;
   sdm->q[knee_angle_l].conversion = 57.2957795131;
   sdm->q[knee_angle_l].initial_value = 0.0000000000;
   sdm->q[knee_angle_l].initial_velocity = 0.0;
   sdm->q[knee_angle_l].range_start = -120.0000000000;
   sdm->q[knee_angle_l].range_end = 10.0000000000;
   sdm->q[knee_angle_l].restraint_func = NULL;
   sdm->q[knee_angle_l].min_restraint_func = NULL;
   sdm->q[knee_angle_l].max_restraint_func = NULL;
   sdm->q[knee_angle_l].function_active = dpNo;
   sdm->q[knee_angle_l].constraint_func = NULL;
   sdm->q[knee_angle_l].constraint_num = -1;
   sdm->q[knee_angle_l].q_ind = -1;
   sdm->q[knee_angle_l].output = dpYes;
   sdm->q[knee_angle_l].torque = 0.0;

   mstrcpy(&sdm->q[tib_pat_l_tx].name,"tib_pat_l_tx");
   sdm->q[tib_pat_l_tx].type = dpConstrainedQ;
   sdm->q[tib_pat_l_tx].joint = tib_pat_l;
   sdm->q[tib_pat_l_tx].axis = 0;
   sdm->q[tib_pat_l_tx].conversion = 1.0000000000;
   sdm->q[tib_pat_l_tx].initial_value = 0.0460148211;
   sdm->q[tib_pat_l_tx].initial_velocity = 0.0;
   sdm->q[tib_pat_l_tx].range_start = -99999.9;
   sdm->q[tib_pat_l_tx].range_end = 99999.9;
   sdm->q[tib_pat_l_tx].restraint_func = NULL;
   sdm->q[tib_pat_l_tx].min_restraint_func = NULL;
   sdm->q[tib_pat_l_tx].max_restraint_func = NULL;
   sdm->q[tib_pat_l_tx].function_active = dpNo;
   sdm->q[tib_pat_l_tx].constraint_func = &tib_pat_l_tx_func;
   sdm->q[tib_pat_l_tx].constraint_num = tib_pat_l_tx_con;
   sdm->q[tib_pat_l_tx].q_ind = knee_angle_l;
   sdm->q[tib_pat_l_tx].output = dpNo;
   sdm->q[tib_pat_l_tx].torque = 0.0;

   mstrcpy(&sdm->q[tib_pat_l_ty].name,"tib_pat_l_ty");
   sdm->q[tib_pat_l_ty].type = dpConstrainedQ;
   sdm->q[tib_pat_l_ty].joint = tib_pat_l;
   sdm->q[tib_pat_l_ty].axis = 1;
   sdm->q[tib_pat_l_ty].conversion = 1.0000000000;
   sdm->q[tib_pat_l_ty].initial_value = -0.0210592024;
   sdm->q[tib_pat_l_ty].initial_velocity = 0.0;
   sdm->q[tib_pat_l_ty].range_start = -99999.9;
   sdm->q[tib_pat_l_ty].range_end = 99999.9;
   sdm->q[tib_pat_l_ty].restraint_func = NULL;
   sdm->q[tib_pat_l_ty].min_restraint_func = NULL;
   sdm->q[tib_pat_l_ty].max_restraint_func = NULL;
   sdm->q[tib_pat_l_ty].function_active = dpNo;
   sdm->q[tib_pat_l_ty].constraint_func = &tib_pat_l_ty_func;
   sdm->q[tib_pat_l_ty].constraint_num = tib_pat_l_ty_con;
   sdm->q[tib_pat_l_ty].q_ind = knee_angle_l;
   sdm->q[tib_pat_l_ty].output = dpNo;
   sdm->q[tib_pat_l_ty].torque = 0.0;

   mstrcpy(&sdm->q[tib_pat_l_r3].name,"tib_pat_l_r3");
   sdm->q[tib_pat_l_r3].type = dpConstrainedQ;
   sdm->q[tib_pat_l_r3].joint = tib_pat_l;
   sdm->q[tib_pat_l_r3].axis = 2;
   sdm->q[tib_pat_l_r3].conversion = 57.2957795131;
   sdm->q[tib_pat_l_r3].initial_value = -0.0669882444;
   sdm->q[tib_pat_l_r3].initial_velocity = 0.0;
   sdm->q[tib_pat_l_r3].range_start = -99999.9;
   sdm->q[tib_pat_l_r3].range_end = 99999.9;
   sdm->q[tib_pat_l_r3].restraint_func = NULL;
   sdm->q[tib_pat_l_r3].min_restraint_func = NULL;
   sdm->q[tib_pat_l_r3].max_restraint_func = NULL;
   sdm->q[tib_pat_l_r3].function_active = dpNo;
   sdm->q[tib_pat_l_r3].constraint_func = &tib_pat_l_r3_func;
   sdm->q[tib_pat_l_r3].constraint_num = tib_pat_l_r3_con;
   sdm->q[tib_pat_l_r3].q_ind = knee_angle_l;
   sdm->q[tib_pat_l_r3].output = dpNo;
   sdm->q[tib_pat_l_r3].torque = 0.0;

   mstrcpy(&sdm->q[ankle_angle_l].name,"ankle_angle_l");
   sdm->q[ankle_angle_l].type = dpUnconstrainedQ;
   sdm->q[ankle_angle_l].joint = ankle_l;
   sdm->q[ankle_angle_l].axis = 0;
   sdm->q[ankle_angle_l].conversion = 57.2957795131;
   sdm->q[ankle_angle_l].initial_value = 0.0000000000;
   sdm->q[ankle_angle_l].initial_velocity = 0.0;
   sdm->q[ankle_angle_l].range_start = -60.0000000000;
   sdm->q[ankle_angle_l].range_end = 60.0000000000;
   sdm->q[ankle_angle_l].restraint_func = NULL;
   sdm->q[ankle_angle_l].min_restraint_func = NULL;
   sdm->q[ankle_angle_l].max_restraint_func = NULL;
   sdm->q[ankle_angle_l].function_active = dpNo;
   sdm->q[ankle_angle_l].constraint_func = NULL;
   sdm->q[ankle_angle_l].constraint_num = -1;
   sdm->q[ankle_angle_l].q_ind = -1;
   sdm->q[ankle_angle_l].output = dpYes;
   sdm->q[ankle_angle_l].torque = 0.0;

   mstrcpy(&sdm->q[subtalar_angle_l].name,"subtalar_angle_l");
   sdm->q[subtalar_angle_l].type = dpUnconstrainedQ;
   sdm->q[subtalar_angle_l].joint = subtalar_l;
   sdm->q[subtalar_angle_l].axis = 0;
   sdm->q[subtalar_angle_l].conversion = 57.2957795131;
   sdm->q[subtalar_angle_l].initial_value = 0.0000000000;
   sdm->q[subtalar_angle_l].initial_velocity = 0.0;
   sdm->q[subtalar_angle_l].range_start = -90.0000000000;
   sdm->q[subtalar_angle_l].range_end = 90.0000000000;
   sdm->q[subtalar_angle_l].restraint_func = NULL;
   sdm->q[subtalar_angle_l].min_restraint_func = NULL;
   sdm->q[subtalar_angle_l].max_restraint_func = NULL;
   sdm->q[subtalar_angle_l].function_active = dpNo;
   sdm->q[subtalar_angle_l].constraint_func = NULL;
   sdm->q[subtalar_angle_l].constraint_num = -1;
   sdm->q[subtalar_angle_l].q_ind = -1;
   sdm->q[subtalar_angle_l].output = dpYes;
   sdm->q[subtalar_angle_l].torque = 0.0;

   mstrcpy(&sdm->q[mtp_angle_l].name,"mtp_angle_l");
   sdm->q[mtp_angle_l].type = dpUnconstrainedQ;
   sdm->q[mtp_angle_l].joint = mtp_l;
   sdm->q[mtp_angle_l].axis = 0;
   sdm->q[mtp_angle_l].conversion = 57.2957795131;
   sdm->q[mtp_angle_l].initial_value = 0.0000000000;
   sdm->q[mtp_angle_l].initial_velocity = 0.0;
   sdm->q[mtp_angle_l].range_start = -60.0000000000;
   sdm->q[mtp_angle_l].range_end = 60.0000000000;
   sdm->q[mtp_angle_l].restraint_func = NULL;
   sdm->q[mtp_angle_l].min_restraint_func = NULL;
   sdm->q[mtp_angle_l].max_restraint_func = NULL;
   sdm->q[mtp_angle_l].function_active = dpNo;
   sdm->q[mtp_angle_l].constraint_func = NULL;
   sdm->q[mtp_angle_l].constraint_num = -1;
   sdm->q[mtp_angle_l].q_ind = -1;
   sdm->q[mtp_angle_l].output = dpYes;
   sdm->q[mtp_angle_l].torque = 0.0;

   mstrcpy(&sdm->q[lumbar_extension].name,"lumbar_extension");
   sdm->q[lumbar_extension].type = dpUnconstrainedQ;
   sdm->q[lumbar_extension].joint = back;
   sdm->q[lumbar_extension].axis = 0;
   sdm->q[lumbar_extension].conversion = 57.2957795131;
   sdm->q[lumbar_extension].initial_value = 0.0000000000;
   sdm->q[lumbar_extension].initial_velocity = 0.0;
   sdm->q[lumbar_extension].range_start = -90.0000000000;
   sdm->q[lumbar_extension].range_end = 90.0000000000;
   sdm->q[lumbar_extension].restraint_func = NULL;
   sdm->q[lumbar_extension].min_restraint_func = NULL;
   sdm->q[lumbar_extension].max_restraint_func = NULL;
   sdm->q[lumbar_extension].function_active = dpNo;
   sdm->q[lumbar_extension].constraint_func = NULL;
   sdm->q[lumbar_extension].constraint_num = -1;
   sdm->q[lumbar_extension].q_ind = -1;
   sdm->q[lumbar_extension].output = dpYes;
   sdm->q[lumbar_extension].torque = 0.0;

   mstrcpy(&sdm->q[lumbar_bending].name,"lumbar_bending");
   sdm->q[lumbar_bending].type = dpUnconstrainedQ;
   sdm->q[lumbar_bending].joint = back;
   sdm->q[lumbar_bending].axis = 1;
   sdm->q[lumbar_bending].conversion = 57.2957795131;
   sdm->q[lumbar_bending].initial_value = 0.0000000000;
   sdm->q[lumbar_bending].initial_velocity = 0.0;
   sdm->q[lumbar_bending].range_start = -90.0000000000;
   sdm->q[lumbar_bending].range_end = 90.0000000000;
   sdm->q[lumbar_bending].restraint_func = NULL;
   sdm->q[lumbar_bending].min_restraint_func = NULL;
   sdm->q[lumbar_bending].max_restraint_func = NULL;
   sdm->q[lumbar_bending].function_active = dpNo;
   sdm->q[lumbar_bending].constraint_func = NULL;
   sdm->q[lumbar_bending].constraint_num = -1;
   sdm->q[lumbar_bending].q_ind = -1;
   sdm->q[lumbar_bending].output = dpYes;
   sdm->q[lumbar_bending].torque = 0.0;

   mstrcpy(&sdm->q[lumbar_rotation].name,"lumbar_rotation");
   sdm->q[lumbar_rotation].type = dpUnconstrainedQ;
   sdm->q[lumbar_rotation].joint = back;
   sdm->q[lumbar_rotation].axis = 2;
   sdm->q[lumbar_rotation].conversion = 57.2957795131;
   sdm->q[lumbar_rotation].initial_value = 0.0000000000;
   sdm->q[lumbar_rotation].initial_velocity = 0.0;
   sdm->q[lumbar_rotation].range_start = -90.0000000000;
   sdm->q[lumbar_rotation].range_end = 90.0000000000;
   sdm->q[lumbar_rotation].restraint_func = NULL;
   sdm->q[lumbar_rotation].min_restraint_func = NULL;
   sdm->q[lumbar_rotation].max_restraint_func = NULL;
   sdm->q[lumbar_rotation].function_active = dpNo;
   sdm->q[lumbar_rotation].constraint_func = NULL;
   sdm->q[lumbar_rotation].constraint_num = -1;
   sdm->q[lumbar_rotation].q_ind = -1;
   sdm->q[lumbar_rotation].output = dpYes;
   sdm->q[lumbar_rotation].torque = 0.0;

   for (i=0, sdm->num_gencoords=0; i<sdm->nq; i++)
      if (sdm->q[i].type == dpUnconstrainedQ)
         sdm->num_gencoords++;

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
 * into the sdm->body_segment[] array because they start at -1.
 */

void init_segments(void)
{

   int i, j;
   sdm->body_segment = (dpBodyStruct*)simm_malloc(sdm->num_body_segments*sizeof(dpBodyStruct));

   mstrcpy(&sdm->body_segment[ground+1].name,"ground");
   sdm->body_segment[ground+1].output = dpNo;
   sdm->body_segment[ground+1].mass = 0.0;
   sdm->body_segment[ground+1].mass_center[0] = 0.000000;
   sdm->body_segment[ground+1].mass_center[1] = 0.000000;
   sdm->body_segment[ground+1].mass_center[2] = 0.000000;
   for (i=0; i<3; i++)
      for (j=0; j<3; j++)
         sdm->body_segment[ground+1].inertia[i][j] = 0.0;
   sdm->body_segment[ground+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_rp+1].name,"calcn_rp");
   sdm->body_segment[calcn_rp+1].output = dpYes;
   sdgetmass(calcn_rp, &(sdm->body_segment[calcn_rp+1].mass));
   sdgetiner(calcn_rp, sdm->body_segment[calcn_rp+1].inertia);
   sdm->body_segment[calcn_rp+1].mass_center[0] = 0.093869;
   sdm->body_segment[calcn_rp+1].mass_center[1] = 0.028161;
   sdm->body_segment[calcn_rp+1].mass_center[2] = 0.000000;
   sdm->body_segment[calcn_rp+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_lp+1].name,"calcn_lp");
   sdm->body_segment[calcn_lp+1].output = dpYes;
   sdgetmass(calcn_lp, &(sdm->body_segment[calcn_lp+1].mass));
   sdgetiner(calcn_lp, sdm->body_segment[calcn_lp+1].inertia);
   sdm->body_segment[calcn_lp+1].mass_center[0] = 0.093869;
   sdm->body_segment[calcn_lp+1].mass_center[1] = 0.028161;
   sdm->body_segment[calcn_lp+1].mass_center[2] = 0.000000;
   sdm->body_segment[calcn_lp+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[pelvis+1].name,"pelvis");
   sdm->body_segment[pelvis+1].output = dpYes;
   sdgetmass(pelvis, &(sdm->body_segment[pelvis+1].mass));
   sdgetiner(pelvis, sdm->body_segment[pelvis+1].inertia);
   sdm->body_segment[pelvis+1].mass_center[0] = -0.065773;
   sdm->body_segment[pelvis+1].mass_center[1] = 0.000000;
   sdm->body_segment[pelvis+1].mass_center[2] = 0.000000;
   sdm->body_segment[pelvis+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[femur_r+1].name,"femur_r");
   sdm->body_segment[femur_r+1].output = dpYes;
   sdgetmass(femur_r, &(sdm->body_segment[femur_r+1].mass));
   sdgetiner(femur_r, sdm->body_segment[femur_r+1].inertia);
   sdm->body_segment[femur_r+1].mass_center[0] = 0.000000;
   sdm->body_segment[femur_r+1].mass_center[1] = -0.160576;
   sdm->body_segment[femur_r+1].mass_center[2] = 0.000000;
   sdm->body_segment[femur_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[tibia_r+1].name,"tibia_r");
   sdm->body_segment[tibia_r+1].output = dpYes;
   sdgetmass(tibia_r, &(sdm->body_segment[tibia_r+1].mass));
   sdgetiner(tibia_r, sdm->body_segment[tibia_r+1].inertia);
   sdm->body_segment[tibia_r+1].mass_center[0] = 0.000000;
   sdm->body_segment[tibia_r+1].mass_center[1] = -0.173205;
   sdm->body_segment[tibia_r+1].mass_center[2] = 0.000000;
   sdm->body_segment[tibia_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[patella_r+1].name,"patella_r");
   sdm->body_segment[patella_r+1].output = dpYes;
   sdgetmass(patella_r, &(sdm->body_segment[patella_r+1].mass));
   sdgetiner(patella_r, sdm->body_segment[patella_r+1].inertia);
   sdm->body_segment[patella_r+1].mass_center[0] = 0.000000;
   sdm->body_segment[patella_r+1].mass_center[1] = 0.000000;
   sdm->body_segment[patella_r+1].mass_center[2] = 0.000000;
   sdm->body_segment[patella_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[talus_r+1].name,"talus_r");
   sdm->body_segment[talus_r+1].output = dpYes;
   sdgetmass(talus_r, &(sdm->body_segment[talus_r+1].mass));
   sdgetiner(talus_r, sdm->body_segment[talus_r+1].inertia);
   sdm->body_segment[talus_r+1].mass_center[0] = 0.000000;
   sdm->body_segment[talus_r+1].mass_center[1] = 0.000000;
   sdm->body_segment[talus_r+1].mass_center[2] = 0.000000;
   sdm->body_segment[talus_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_r+1].name,"calcn_r");
   sdm->body_segment[calcn_r+1].output = dpYes;
   sdgetmass(calcn_r, &(sdm->body_segment[calcn_r+1].mass));
   sdgetiner(calcn_r, sdm->body_segment[calcn_r+1].inertia);
   sdm->body_segment[calcn_r+1].mass_center[0] = 0.093869;
   sdm->body_segment[calcn_r+1].mass_center[1] = 0.028161;
   sdm->body_segment[calcn_r+1].mass_center[2] = 0.000000;
   sdm->body_segment[calcn_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[toes_r+1].name,"toes_r");
   sdm->body_segment[toes_r+1].output = dpYes;
   sdgetmass(toes_r, &(sdm->body_segment[toes_r+1].mass));
   sdgetiner(toes_r, sdm->body_segment[toes_r+1].inertia);
   sdm->body_segment[toes_r+1].mass_center[0] = 0.032479;
   sdm->body_segment[toes_r+1].mass_center[1] = 0.005632;
   sdm->body_segment[toes_r+1].mass_center[2] = -0.016427;
   sdm->body_segment[toes_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[femur_l+1].name,"femur_l");
   sdm->body_segment[femur_l+1].output = dpYes;
   sdgetmass(femur_l, &(sdm->body_segment[femur_l+1].mass));
   sdgetiner(femur_l, sdm->body_segment[femur_l+1].inertia);
   sdm->body_segment[femur_l+1].mass_center[0] = 0.000000;
   sdm->body_segment[femur_l+1].mass_center[1] = -0.160576;
   sdm->body_segment[femur_l+1].mass_center[2] = 0.000000;
   sdm->body_segment[femur_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[tibia_l+1].name,"tibia_l");
   sdm->body_segment[tibia_l+1].output = dpYes;
   sdgetmass(tibia_l, &(sdm->body_segment[tibia_l+1].mass));
   sdgetiner(tibia_l, sdm->body_segment[tibia_l+1].inertia);
   sdm->body_segment[tibia_l+1].mass_center[0] = 0.000000;
   sdm->body_segment[tibia_l+1].mass_center[1] = -0.173205;
   sdm->body_segment[tibia_l+1].mass_center[2] = 0.000000;
   sdm->body_segment[tibia_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[patella_l+1].name,"patella_l");
   sdm->body_segment[patella_l+1].output = dpYes;
   sdgetmass(patella_l, &(sdm->body_segment[patella_l+1].mass));
   sdgetiner(patella_l, sdm->body_segment[patella_l+1].inertia);
   sdm->body_segment[patella_l+1].mass_center[0] = 0.000000;
   sdm->body_segment[patella_l+1].mass_center[1] = 0.000000;
   sdm->body_segment[patella_l+1].mass_center[2] = 0.000000;
   sdm->body_segment[patella_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[talus_l+1].name,"talus_l");
   sdm->body_segment[talus_l+1].output = dpYes;
   sdgetmass(talus_l, &(sdm->body_segment[talus_l+1].mass));
   sdgetiner(talus_l, sdm->body_segment[talus_l+1].inertia);
   sdm->body_segment[talus_l+1].mass_center[0] = 0.000000;
   sdm->body_segment[talus_l+1].mass_center[1] = 0.000000;
   sdm->body_segment[talus_l+1].mass_center[2] = 0.000000;
   sdm->body_segment[talus_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_l+1].name,"calcn_l");
   sdm->body_segment[calcn_l+1].output = dpYes;
   sdgetmass(calcn_l, &(sdm->body_segment[calcn_l+1].mass));
   sdgetiner(calcn_l, sdm->body_segment[calcn_l+1].inertia);
   sdm->body_segment[calcn_l+1].mass_center[0] = 0.093869;
   sdm->body_segment[calcn_l+1].mass_center[1] = 0.028161;
   sdm->body_segment[calcn_l+1].mass_center[2] = 0.000000;
   sdm->body_segment[calcn_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[toes_l+1].name,"toes_l");
   sdm->body_segment[toes_l+1].output = dpYes;
   sdgetmass(toes_l, &(sdm->body_segment[toes_l+1].mass));
   sdgetiner(toes_l, sdm->body_segment[toes_l+1].inertia);
   sdm->body_segment[toes_l+1].mass_center[0] = 0.032479;
   sdm->body_segment[toes_l+1].mass_center[1] = 0.005632;
   sdm->body_segment[toes_l+1].mass_center[2] = 0.016427;
   sdm->body_segment[toes_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[torso+1].name,"torso");
   sdm->body_segment[torso+1].output = dpYes;
   sdgetmass(torso, &(sdm->body_segment[torso+1].mass));
   sdgetiner(torso, sdm->body_segment[torso+1].inertia);
   sdm->body_segment[torso+1].mass_center[0] = -0.025486;
   sdm->body_segment[torso+1].mass_center[1] = 0.271854;
   sdm->body_segment[torso+1].mass_center[2] = 0.000000;
   sdm->body_segment[torso+1].contactable = dpNo;

   mstrcpy(&sdm->name, "900061");

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

   numpts = sizeof(tib_pat_r_r3_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_r_r3_func,numpts);
   tib_pat_r_r3_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_r_r3_func.x[i] = tib_pat_r_r3_data[i][0];
      tib_pat_r_r3_func.y[i] = tib_pat_r_r3_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_r_r3_func);

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

   numpts = sizeof(tib_pat_l_r3_data)/(sizeof(double)*2);
   (void)malloc_function(&tib_pat_l_r3_func,numpts);
   tib_pat_l_r3_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tib_pat_l_r3_func.x[i] = tib_pat_l_r3_data[i][0];
      tib_pat_l_r3_func.y[i] = tib_pat_l_r3_data[i][1];
   }
   calc_spline_coefficients(&tib_pat_l_r3_func);

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

}


void init_wrap_objects(void)
{

   /* There are no wrap objects in this model. */

  sdm->num_wrap_objects = 0;
  sdm->wrap_object = NULL;

}

void init_constraint_objects(void)
{

   /* There are no constraint objects in this model. */

  sdm->num_constraint_objects = 0;
  sdm->constraint_object = NULL;
}

