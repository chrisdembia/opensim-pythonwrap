/*******************************************************************************

   pipeline/dynsim/src/sdfor.c

   Created by NMBLTS (from model Two-Legged Cycling)

   Time of creation: 11/07/2005 12:58:13 PM

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

static double femoral_tibial_r_tx_data[][2] =
{
{-120.0000000000, -0.0032000000},
{-100.0000000000, 0.0017900000},
{-80.0000000000, 0.0041100000},
{-60.0000000000, 0.0041000000},
{-40.0000000000, 0.0021200000},
{-20.0000000000, -0.0010000000},
{-10.0000000000, -0.0031000000},
{0.0000000000, -0.0052500000}
};

static double femoral_tibial_r_ty_data[][2] =
{
{-120.0000000000, -0.4226000000},
{-70.0000000000, -0.4082000000},
{-30.0000000000, -0.3990000000},
{-20.0000000000, -0.3976000000},
{-10.0000000000, -0.3966000000},
{0.0000000000, -0.3960000000}
};

static double tp_r_tx_data[][2] =
{
{-120.0000000000, 0.0173000000},
{-80.0000000000, 0.0324000000},
{-60.0000000000, 0.0381000000},
{-40.0000000000, 0.0430000000},
{-20.0000000000, 0.0469000000},
{-10.0000000000, 0.0484000000},
{0.0000000000, 0.0496000000}
};

static double tp_r_ty_data[][2] =
{
{-120.0000000000, -0.0219000000},
{-90.0000000000, -0.0202000000},
{-80.0000000000, -0.0200000000},
{-60.0000000000, -0.0204000000},
{-40.0000000000, -0.0211000000},
{-20.0000000000, -0.0219000000},
{-10.0000000000, -0.0223000000},
{0.2860000000, -0.0227000000}
};

static double tp_r_r1_data[][2] =
{
{-120.0000000000, 17.6500000000},
{-114.5900000000, 17.6500000000},
{-83.5100000000, 17.5500000000},
{-30.1600000000, 15.4800000000},
{1.6000000000, -2.1200000000},
{10.0000000000, -16.0400000000}
};

static double femoral_tibial_l_tx_data[][2] =
{
{-120.0000000000, -0.0032000000},
{-100.0000000000, 0.0017900000},
{-80.0000000000, 0.0041100000},
{-60.0000000000, 0.0041000000},
{-40.0000000000, 0.0021200000},
{-20.0000000000, -0.0010000000},
{-10.0000000000, -0.0031000000},
{0.0000000000, -0.0052500000}
};

static double femoral_tibial_l_ty_data[][2] =
{
{-120.0000000000, -0.4226000000},
{-70.0000000000, -0.4082000000},
{-30.0000000000, -0.3990000000},
{-20.0000000000, -0.3976000000},
{-10.0000000000, -0.3966000000},
{0.0000000000, -0.3960000000}
};

static double tp_l_tx_data[][2] =
{
{-120.0000000000, 0.0173000000},
{-80.0000000000, 0.0324000000},
{-60.0000000000, 0.0381000000},
{-40.0000000000, 0.0430000000},
{-20.0000000000, 0.0469000000},
{-10.0000000000, 0.0484000000},
{0.0000000000, 0.0496000000}
};

static double tp_l_ty_data[][2] =
{
{-120.0000000000, -0.0219000000},
{-90.0000000000, -0.0202000000},
{-80.0000000000, -0.0200000000},
{-60.0000000000, -0.0204000000},
{-40.0000000000, -0.0211000000},
{-20.0000000000, -0.0219000000},
{-10.0000000000, -0.0223000000},
{0.2860000000, -0.0227000000}
};

static double tp_l_r1_data[][2] =
{
{-120.0000000000, 17.6500000000},
{-114.5900000000, 17.6500000000},
{-83.5100000000, 17.5500000000},
{-30.1600000000, 15.4800000000},
{1.6000000000, -2.1200000000},
{10.0000000000, -16.0400000000}
};

static dpSplineFunction femoral_tibial_r_tx_func;
static dpSplineFunction femoral_tibial_r_ty_func;
static dpSplineFunction tp_r_tx_func;
static dpSplineFunction tp_r_ty_func;
static dpSplineFunction tp_r_r1_func;
static dpSplineFunction femoral_tibial_l_tx_func;
static dpSplineFunction femoral_tibial_l_ty_func;
static dpSplineFunction tp_l_tx_func;
static dpSplineFunction tp_l_ty_func;
static dpSplineFunction tp_l_r1_func;

static double q_restraint_func1_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func2_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func3_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func4_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func5_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func6_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func7_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func8_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func9_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func10_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func11_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func12_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func13_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func14_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func15_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func16_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func17_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static double q_restraint_func18_data[][2] = {
{0.0000000000, 0.0000000000},
{30.0000000000, 200.0000000000}
};


static dpSplineFunction q_restraint_func[18];



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
   mstrcpy(&sdm->q[crank_angle].name,"crank_angle");
   sdm->q[crank_angle].type = dpUnconstrainedQ;
   sdm->q[crank_angle].joint = bb;
   sdm->q[crank_angle].axis = 0;
   sdm->q[crank_angle].conversion = 57.2957795131;
   sdm->q[crank_angle].initial_value = 273.0000000000;
   sdm->q[crank_angle].initial_velocity = 0.0;
   sdm->q[crank_angle].range_start = -360.0000000000;
   sdm->q[crank_angle].range_end = 1440.0000000000;
   sdm->q[crank_angle].restraint_func = NULL;
   sdm->q[crank_angle].min_restraint_func = &q_restraint_func[0];
   sdm->q[crank_angle].max_restraint_func = &q_restraint_func[1];
   sdm->q[crank_angle].function_active = dpNo;
   sdm->q[crank_angle].constraint_func = NULL;
   sdm->q[crank_angle].constraint_num = -1;
   sdm->q[crank_angle].q_ind = -1;
   sdm->q[crank_angle].output = dpYes;
   sdm->q[crank_angle].pd_stiffness = 0.0000000000;
   sdm->q[crank_angle].torque = 0.0;

   mstrcpy(&sdm->q[fixed1].name,"fixed1");
   sdm->q[fixed1].type = dpFixedQ;
   sdm->q[fixed1].joint = pelvis;
   sdm->q[fixed1].axis = 0;
   sdm->q[fixed1].conversion = 57.2957795131;
   sdm->q[fixed1].initial_value = 0.0000000000;
   sdm->q[fixed1].initial_velocity = 0.0;
   sdm->q[fixed1].range_start = -99999.9;
   sdm->q[fixed1].range_end = 99999.9;
   sdm->q[fixed1].restraint_func = NULL;
   sdm->q[fixed1].min_restraint_func = NULL;
   sdm->q[fixed1].max_restraint_func = NULL;
   sdm->q[fixed1].function_active = dpNo;
   sdm->q[fixed1].constraint_func = NULL;
   sdm->q[fixed1].constraint_num = -1;
   sdm->q[fixed1].q_ind = -1;
   sdm->q[fixed1].output = dpNo;
   sdm->q[fixed1].pd_stiffness = 0.0;
   sdm->q[fixed1].torque = 0.0;

   mstrcpy(&sdm->q[pedal_angle].name,"pedal_angle");
   sdm->q[pedal_angle].type = dpUnconstrainedQ;
   sdm->q[pedal_angle].joint = cp;
   sdm->q[pedal_angle].axis = 0;
   sdm->q[pedal_angle].conversion = 57.2957795131;
   sdm->q[pedal_angle].initial_value = 136.0000000000;
   sdm->q[pedal_angle].initial_velocity = 0.0;
   sdm->q[pedal_angle].range_start = -720.0000000000;
   sdm->q[pedal_angle].range_end = 720.0000000000;
   sdm->q[pedal_angle].restraint_func = NULL;
   sdm->q[pedal_angle].min_restraint_func = &q_restraint_func[2];
   sdm->q[pedal_angle].max_restraint_func = &q_restraint_func[3];
   sdm->q[pedal_angle].function_active = dpNo;
   sdm->q[pedal_angle].constraint_func = NULL;
   sdm->q[pedal_angle].constraint_num = -1;
   sdm->q[pedal_angle].q_ind = -1;
   sdm->q[pedal_angle].output = dpYes;
   sdm->q[pedal_angle].pd_stiffness = 0.0000000000;
   sdm->q[pedal_angle].torque = 0.0;

   mstrcpy(&sdm->q[pedal_angle_l].name,"pedal_angle_l");
   sdm->q[pedal_angle_l].type = dpUnconstrainedQ;
   sdm->q[pedal_angle_l].joint = cp_l;
   sdm->q[pedal_angle_l].axis = 0;
   sdm->q[pedal_angle_l].conversion = 57.2957795131;
   sdm->q[pedal_angle_l].initial_value = 110.0000000000;
   sdm->q[pedal_angle_l].initial_velocity = 0.0;
   sdm->q[pedal_angle_l].range_start = -720.0000000000;
   sdm->q[pedal_angle_l].range_end = 720.0000000000;
   sdm->q[pedal_angle_l].restraint_func = NULL;
   sdm->q[pedal_angle_l].min_restraint_func = &q_restraint_func[4];
   sdm->q[pedal_angle_l].max_restraint_func = &q_restraint_func[5];
   sdm->q[pedal_angle_l].function_active = dpNo;
   sdm->q[pedal_angle_l].constraint_func = NULL;
   sdm->q[pedal_angle_l].constraint_num = -1;
   sdm->q[pedal_angle_l].q_ind = -1;
   sdm->q[pedal_angle_l].output = dpYes;
   sdm->q[pedal_angle_l].pd_stiffness = 0.0000000000;
   sdm->q[pedal_angle_l].torque = 0.0;

   mstrcpy(&sdm->q[fixed4].name,"fixed4");
   sdm->q[fixed4].type = dpFixedQ;
   sdm->q[fixed4].joint = pc;
   sdm->q[fixed4].axis = 0;
   sdm->q[fixed4].conversion = 57.2957795131;
   sdm->q[fixed4].initial_value = 0.0000000000;
   sdm->q[fixed4].initial_velocity = 0.0;
   sdm->q[fixed4].range_start = -99999.9;
   sdm->q[fixed4].range_end = 99999.9;
   sdm->q[fixed4].restraint_func = NULL;
   sdm->q[fixed4].min_restraint_func = NULL;
   sdm->q[fixed4].max_restraint_func = NULL;
   sdm->q[fixed4].function_active = dpNo;
   sdm->q[fixed4].constraint_func = NULL;
   sdm->q[fixed4].constraint_num = -1;
   sdm->q[fixed4].q_ind = -1;
   sdm->q[fixed4].output = dpNo;
   sdm->q[fixed4].pd_stiffness = 0.0;
   sdm->q[fixed4].torque = 0.0;

   mstrcpy(&sdm->q[fixed5].name,"fixed5");
   sdm->q[fixed5].type = dpFixedQ;
   sdm->q[fixed5].joint = pc_l;
   sdm->q[fixed5].axis = 0;
   sdm->q[fixed5].conversion = 57.2957795131;
   sdm->q[fixed5].initial_value = 0.0000000000;
   sdm->q[fixed5].initial_velocity = 0.0;
   sdm->q[fixed5].range_start = -99999.9;
   sdm->q[fixed5].range_end = 99999.9;
   sdm->q[fixed5].restraint_func = NULL;
   sdm->q[fixed5].min_restraint_func = NULL;
   sdm->q[fixed5].max_restraint_func = NULL;
   sdm->q[fixed5].function_active = dpNo;
   sdm->q[fixed5].constraint_func = NULL;
   sdm->q[fixed5].constraint_num = -1;
   sdm->q[fixed5].q_ind = -1;
   sdm->q[fixed5].output = dpNo;
   sdm->q[fixed5].pd_stiffness = 0.0;
   sdm->q[fixed5].torque = 0.0;

   mstrcpy(&sdm->q[hip_flexion_r].name,"hip_flexion_r");
   sdm->q[hip_flexion_r].type = dpUnconstrainedQ;
   sdm->q[hip_flexion_r].joint = hip_r;
   sdm->q[hip_flexion_r].axis = 0;
   sdm->q[hip_flexion_r].conversion = 57.2957795131;
   sdm->q[hip_flexion_r].initial_value = 0.0000000000;
   sdm->q[hip_flexion_r].initial_velocity = 0.0;
   sdm->q[hip_flexion_r].range_start = -11.0000000000;
   sdm->q[hip_flexion_r].range_end = 95.0000000000;
   sdm->q[hip_flexion_r].restraint_func = NULL;
   sdm->q[hip_flexion_r].min_restraint_func = &q_restraint_func[6];
   sdm->q[hip_flexion_r].max_restraint_func = &q_restraint_func[7];
   sdm->q[hip_flexion_r].function_active = dpNo;
   sdm->q[hip_flexion_r].constraint_func = NULL;
   sdm->q[hip_flexion_r].constraint_num = -1;
   sdm->q[hip_flexion_r].q_ind = -1;
   sdm->q[hip_flexion_r].output = dpYes;
   sdm->q[hip_flexion_r].pd_stiffness = 0.0000000000;
   sdm->q[hip_flexion_r].torque = 0.0;

   mstrcpy(&sdm->q[femoral_tibial_r_tx].name,"femoral_tibial_r_tx");
   sdm->q[femoral_tibial_r_tx].type = dpConstrainedQ;
   sdm->q[femoral_tibial_r_tx].joint = femoral_tibial_r;
   sdm->q[femoral_tibial_r_tx].axis = 0;
   sdm->q[femoral_tibial_r_tx].conversion = 1.0000000000;
   sdm->q[femoral_tibial_r_tx].initial_value = -0.0052500000;
   sdm->q[femoral_tibial_r_tx].initial_velocity = 0.0;
   sdm->q[femoral_tibial_r_tx].range_start = -99999.9;
   sdm->q[femoral_tibial_r_tx].range_end = 99999.9;
   sdm->q[femoral_tibial_r_tx].restraint_func = NULL;
   sdm->q[femoral_tibial_r_tx].min_restraint_func = NULL;
   sdm->q[femoral_tibial_r_tx].max_restraint_func = NULL;
   sdm->q[femoral_tibial_r_tx].function_active = dpNo;
   sdm->q[femoral_tibial_r_tx].constraint_func = &femoral_tibial_r_tx_func;
   sdm->q[femoral_tibial_r_tx].constraint_num = femoral_tibial_r_tx_con;
   sdm->q[femoral_tibial_r_tx].q_ind = knee_angle_r;
   sdm->q[femoral_tibial_r_tx].output = dpNo;
   sdm->q[femoral_tibial_r_tx].pd_stiffness = 0.0;
   sdm->q[femoral_tibial_r_tx].torque = 0.0;

   mstrcpy(&sdm->q[femoral_tibial_r_ty].name,"femoral_tibial_r_ty");
   sdm->q[femoral_tibial_r_ty].type = dpConstrainedQ;
   sdm->q[femoral_tibial_r_ty].joint = femoral_tibial_r;
   sdm->q[femoral_tibial_r_ty].axis = 1;
   sdm->q[femoral_tibial_r_ty].conversion = 1.0000000000;
   sdm->q[femoral_tibial_r_ty].initial_value = -0.3960000000;
   sdm->q[femoral_tibial_r_ty].initial_velocity = 0.0;
   sdm->q[femoral_tibial_r_ty].range_start = -99999.9;
   sdm->q[femoral_tibial_r_ty].range_end = 99999.9;
   sdm->q[femoral_tibial_r_ty].restraint_func = NULL;
   sdm->q[femoral_tibial_r_ty].min_restraint_func = NULL;
   sdm->q[femoral_tibial_r_ty].max_restraint_func = NULL;
   sdm->q[femoral_tibial_r_ty].function_active = dpNo;
   sdm->q[femoral_tibial_r_ty].constraint_func = &femoral_tibial_r_ty_func;
   sdm->q[femoral_tibial_r_ty].constraint_num = femoral_tibial_r_ty_con;
   sdm->q[femoral_tibial_r_ty].q_ind = knee_angle_r;
   sdm->q[femoral_tibial_r_ty].output = dpNo;
   sdm->q[femoral_tibial_r_ty].pd_stiffness = 0.0;
   sdm->q[femoral_tibial_r_ty].torque = 0.0;

   mstrcpy(&sdm->q[knee_angle_r].name,"knee_angle_r");
   sdm->q[knee_angle_r].type = dpUnconstrainedQ;
   sdm->q[knee_angle_r].joint = femoral_tibial_r;
   sdm->q[knee_angle_r].axis = 2;
   sdm->q[knee_angle_r].conversion = 57.2957795131;
   sdm->q[knee_angle_r].initial_value = 0.0000000000;
   sdm->q[knee_angle_r].initial_velocity = 0.0;
   sdm->q[knee_angle_r].range_start = -120.0000000000;
   sdm->q[knee_angle_r].range_end = 0.0000000000;
   sdm->q[knee_angle_r].restraint_func = NULL;
   sdm->q[knee_angle_r].min_restraint_func = &q_restraint_func[8];
   sdm->q[knee_angle_r].max_restraint_func = &q_restraint_func[9];
   sdm->q[knee_angle_r].function_active = dpNo;
   sdm->q[knee_angle_r].constraint_func = NULL;
   sdm->q[knee_angle_r].constraint_num = -1;
   sdm->q[knee_angle_r].q_ind = -1;
   sdm->q[knee_angle_r].output = dpYes;
   sdm->q[knee_angle_r].pd_stiffness = 0.0000000000;
   sdm->q[knee_angle_r].torque = 0.0;

   mstrcpy(&sdm->q[tp_r_tx].name,"tp_r_tx");
   sdm->q[tp_r_tx].type = dpConstrainedQ;
   sdm->q[tp_r_tx].joint = tp_r;
   sdm->q[tp_r_tx].axis = 0;
   sdm->q[tp_r_tx].conversion = 1.0000000000;
   sdm->q[tp_r_tx].initial_value = 0.0496000000;
   sdm->q[tp_r_tx].initial_velocity = 0.0;
   sdm->q[tp_r_tx].range_start = -99999.9;
   sdm->q[tp_r_tx].range_end = 99999.9;
   sdm->q[tp_r_tx].restraint_func = NULL;
   sdm->q[tp_r_tx].min_restraint_func = NULL;
   sdm->q[tp_r_tx].max_restraint_func = NULL;
   sdm->q[tp_r_tx].function_active = dpNo;
   sdm->q[tp_r_tx].constraint_func = &tp_r_tx_func;
   sdm->q[tp_r_tx].constraint_num = tp_r_tx_con;
   sdm->q[tp_r_tx].q_ind = knee_angle_r;
   sdm->q[tp_r_tx].output = dpNo;
   sdm->q[tp_r_tx].pd_stiffness = 0.0;
   sdm->q[tp_r_tx].torque = 0.0;

   mstrcpy(&sdm->q[tp_r_ty].name,"tp_r_ty");
   sdm->q[tp_r_ty].type = dpConstrainedQ;
   sdm->q[tp_r_ty].joint = tp_r;
   sdm->q[tp_r_ty].axis = 1;
   sdm->q[tp_r_ty].conversion = 1.0000000000;
   sdm->q[tp_r_ty].initial_value = -0.0226890900;
   sdm->q[tp_r_ty].initial_velocity = 0.0;
   sdm->q[tp_r_ty].range_start = -99999.9;
   sdm->q[tp_r_ty].range_end = 99999.9;
   sdm->q[tp_r_ty].restraint_func = NULL;
   sdm->q[tp_r_ty].min_restraint_func = NULL;
   sdm->q[tp_r_ty].max_restraint_func = NULL;
   sdm->q[tp_r_ty].function_active = dpNo;
   sdm->q[tp_r_ty].constraint_func = &tp_r_ty_func;
   sdm->q[tp_r_ty].constraint_num = tp_r_ty_con;
   sdm->q[tp_r_ty].q_ind = knee_angle_r;
   sdm->q[tp_r_ty].output = dpNo;
   sdm->q[tp_r_ty].pd_stiffness = 0.0;
   sdm->q[tp_r_ty].torque = 0.0;

   mstrcpy(&sdm->q[tp_r_r1].name,"tp_r_r1");
   sdm->q[tp_r_r1].type = dpConstrainedQ;
   sdm->q[tp_r_r1].joint = tp_r;
   sdm->q[tp_r_r1].axis = 2;
   sdm->q[tp_r_r1].conversion = 57.2957795131;
   sdm->q[tp_r_r1].initial_value = -0.0669882444;
   sdm->q[tp_r_r1].initial_velocity = 0.0;
   sdm->q[tp_r_r1].range_start = -99999.9;
   sdm->q[tp_r_r1].range_end = 99999.9;
   sdm->q[tp_r_r1].restraint_func = NULL;
   sdm->q[tp_r_r1].min_restraint_func = NULL;
   sdm->q[tp_r_r1].max_restraint_func = NULL;
   sdm->q[tp_r_r1].function_active = dpNo;
   sdm->q[tp_r_r1].constraint_func = &tp_r_r1_func;
   sdm->q[tp_r_r1].constraint_num = tp_r_r1_con;
   sdm->q[tp_r_r1].q_ind = knee_angle_r;
   sdm->q[tp_r_r1].output = dpNo;
   sdm->q[tp_r_r1].pd_stiffness = 0.0;
   sdm->q[tp_r_r1].torque = 0.0;

   mstrcpy(&sdm->q[ankle_angle_r].name,"ankle_angle_r");
   sdm->q[ankle_angle_r].type = dpUnconstrainedQ;
   sdm->q[ankle_angle_r].joint = ankle_r;
   sdm->q[ankle_angle_r].axis = 0;
   sdm->q[ankle_angle_r].conversion = 57.2957795131;
   sdm->q[ankle_angle_r].initial_value = 0.0000000000;
   sdm->q[ankle_angle_r].initial_velocity = 0.0;
   sdm->q[ankle_angle_r].range_start = -50.0000000000;
   sdm->q[ankle_angle_r].range_end = 30.0000000000;
   sdm->q[ankle_angle_r].restraint_func = NULL;
   sdm->q[ankle_angle_r].min_restraint_func = &q_restraint_func[10];
   sdm->q[ankle_angle_r].max_restraint_func = &q_restraint_func[11];
   sdm->q[ankle_angle_r].function_active = dpNo;
   sdm->q[ankle_angle_r].constraint_func = NULL;
   sdm->q[ankle_angle_r].constraint_num = -1;
   sdm->q[ankle_angle_r].q_ind = -1;
   sdm->q[ankle_angle_r].output = dpYes;
   sdm->q[ankle_angle_r].pd_stiffness = 0.0000000000;
   sdm->q[ankle_angle_r].torque = 0.0;

   mstrcpy(&sdm->q[fixed14].name,"fixed14");
   sdm->q[fixed14].type = dpFixedQ;
   sdm->q[fixed14].joint = subtalar_r;
   sdm->q[fixed14].axis = 0;
   sdm->q[fixed14].conversion = 57.2957795131;
   sdm->q[fixed14].initial_value = 0.0000000000;
   sdm->q[fixed14].initial_velocity = 0.0;
   sdm->q[fixed14].range_start = -99999.9;
   sdm->q[fixed14].range_end = 99999.9;
   sdm->q[fixed14].restraint_func = NULL;
   sdm->q[fixed14].min_restraint_func = NULL;
   sdm->q[fixed14].max_restraint_func = NULL;
   sdm->q[fixed14].function_active = dpNo;
   sdm->q[fixed14].constraint_func = NULL;
   sdm->q[fixed14].constraint_num = -1;
   sdm->q[fixed14].q_ind = -1;
   sdm->q[fixed14].output = dpNo;
   sdm->q[fixed14].pd_stiffness = 0.0;
   sdm->q[fixed14].torque = 0.0;

   mstrcpy(&sdm->q[hip_flexion_l].name,"hip_flexion_l");
   sdm->q[hip_flexion_l].type = dpUnconstrainedQ;
   sdm->q[hip_flexion_l].joint = hip_l;
   sdm->q[hip_flexion_l].axis = 0;
   sdm->q[hip_flexion_l].conversion = 57.2957795131;
   sdm->q[hip_flexion_l].initial_value = 0.0000000000;
   sdm->q[hip_flexion_l].initial_velocity = 0.0;
   sdm->q[hip_flexion_l].range_start = -11.0000000000;
   sdm->q[hip_flexion_l].range_end = 95.0000000000;
   sdm->q[hip_flexion_l].restraint_func = NULL;
   sdm->q[hip_flexion_l].min_restraint_func = &q_restraint_func[12];
   sdm->q[hip_flexion_l].max_restraint_func = &q_restraint_func[13];
   sdm->q[hip_flexion_l].function_active = dpNo;
   sdm->q[hip_flexion_l].constraint_func = NULL;
   sdm->q[hip_flexion_l].constraint_num = -1;
   sdm->q[hip_flexion_l].q_ind = -1;
   sdm->q[hip_flexion_l].output = dpYes;
   sdm->q[hip_flexion_l].pd_stiffness = 0.0000000000;
   sdm->q[hip_flexion_l].torque = 0.0;

   mstrcpy(&sdm->q[femoral_tibial_l_tx].name,"femoral_tibial_l_tx");
   sdm->q[femoral_tibial_l_tx].type = dpConstrainedQ;
   sdm->q[femoral_tibial_l_tx].joint = femoral_tibial_l;
   sdm->q[femoral_tibial_l_tx].axis = 0;
   sdm->q[femoral_tibial_l_tx].conversion = 1.0000000000;
   sdm->q[femoral_tibial_l_tx].initial_value = -0.0052500000;
   sdm->q[femoral_tibial_l_tx].initial_velocity = 0.0;
   sdm->q[femoral_tibial_l_tx].range_start = -99999.9;
   sdm->q[femoral_tibial_l_tx].range_end = 99999.9;
   sdm->q[femoral_tibial_l_tx].restraint_func = NULL;
   sdm->q[femoral_tibial_l_tx].min_restraint_func = NULL;
   sdm->q[femoral_tibial_l_tx].max_restraint_func = NULL;
   sdm->q[femoral_tibial_l_tx].function_active = dpNo;
   sdm->q[femoral_tibial_l_tx].constraint_func = &femoral_tibial_l_tx_func;
   sdm->q[femoral_tibial_l_tx].constraint_num = femoral_tibial_l_tx_con;
   sdm->q[femoral_tibial_l_tx].q_ind = knee_angle_l;
   sdm->q[femoral_tibial_l_tx].output = dpNo;
   sdm->q[femoral_tibial_l_tx].pd_stiffness = 0.0;
   sdm->q[femoral_tibial_l_tx].torque = 0.0;

   mstrcpy(&sdm->q[femoral_tibial_l_ty].name,"femoral_tibial_l_ty");
   sdm->q[femoral_tibial_l_ty].type = dpConstrainedQ;
   sdm->q[femoral_tibial_l_ty].joint = femoral_tibial_l;
   sdm->q[femoral_tibial_l_ty].axis = 1;
   sdm->q[femoral_tibial_l_ty].conversion = 1.0000000000;
   sdm->q[femoral_tibial_l_ty].initial_value = -0.3960000000;
   sdm->q[femoral_tibial_l_ty].initial_velocity = 0.0;
   sdm->q[femoral_tibial_l_ty].range_start = -99999.9;
   sdm->q[femoral_tibial_l_ty].range_end = 99999.9;
   sdm->q[femoral_tibial_l_ty].restraint_func = NULL;
   sdm->q[femoral_tibial_l_ty].min_restraint_func = NULL;
   sdm->q[femoral_tibial_l_ty].max_restraint_func = NULL;
   sdm->q[femoral_tibial_l_ty].function_active = dpNo;
   sdm->q[femoral_tibial_l_ty].constraint_func = &femoral_tibial_l_ty_func;
   sdm->q[femoral_tibial_l_ty].constraint_num = femoral_tibial_l_ty_con;
   sdm->q[femoral_tibial_l_ty].q_ind = knee_angle_l;
   sdm->q[femoral_tibial_l_ty].output = dpNo;
   sdm->q[femoral_tibial_l_ty].pd_stiffness = 0.0;
   sdm->q[femoral_tibial_l_ty].torque = 0.0;

   mstrcpy(&sdm->q[knee_angle_l].name,"knee_angle_l");
   sdm->q[knee_angle_l].type = dpUnconstrainedQ;
   sdm->q[knee_angle_l].joint = femoral_tibial_l;
   sdm->q[knee_angle_l].axis = 2;
   sdm->q[knee_angle_l].conversion = 57.2957795131;
   sdm->q[knee_angle_l].initial_value = 0.0000000000;
   sdm->q[knee_angle_l].initial_velocity = 0.0;
   sdm->q[knee_angle_l].range_start = -120.0000000000;
   sdm->q[knee_angle_l].range_end = 0.0000000000;
   sdm->q[knee_angle_l].restraint_func = NULL;
   sdm->q[knee_angle_l].min_restraint_func = &q_restraint_func[14];
   sdm->q[knee_angle_l].max_restraint_func = &q_restraint_func[15];
   sdm->q[knee_angle_l].function_active = dpNo;
   sdm->q[knee_angle_l].constraint_func = NULL;
   sdm->q[knee_angle_l].constraint_num = -1;
   sdm->q[knee_angle_l].q_ind = -1;
   sdm->q[knee_angle_l].output = dpYes;
   sdm->q[knee_angle_l].pd_stiffness = 0.0000000000;
   sdm->q[knee_angle_l].torque = 0.0;

   mstrcpy(&sdm->q[tp_l_tx].name,"tp_l_tx");
   sdm->q[tp_l_tx].type = dpConstrainedQ;
   sdm->q[tp_l_tx].joint = tp_l;
   sdm->q[tp_l_tx].axis = 0;
   sdm->q[tp_l_tx].conversion = 1.0000000000;
   sdm->q[tp_l_tx].initial_value = 0.0496000000;
   sdm->q[tp_l_tx].initial_velocity = 0.0;
   sdm->q[tp_l_tx].range_start = -99999.9;
   sdm->q[tp_l_tx].range_end = 99999.9;
   sdm->q[tp_l_tx].restraint_func = NULL;
   sdm->q[tp_l_tx].min_restraint_func = NULL;
   sdm->q[tp_l_tx].max_restraint_func = NULL;
   sdm->q[tp_l_tx].function_active = dpNo;
   sdm->q[tp_l_tx].constraint_func = &tp_l_tx_func;
   sdm->q[tp_l_tx].constraint_num = tp_l_tx_con;
   sdm->q[tp_l_tx].q_ind = knee_angle_l;
   sdm->q[tp_l_tx].output = dpNo;
   sdm->q[tp_l_tx].pd_stiffness = 0.0;
   sdm->q[tp_l_tx].torque = 0.0;

   mstrcpy(&sdm->q[tp_l_ty].name,"tp_l_ty");
   sdm->q[tp_l_ty].type = dpConstrainedQ;
   sdm->q[tp_l_ty].joint = tp_l;
   sdm->q[tp_l_ty].axis = 1;
   sdm->q[tp_l_ty].conversion = 1.0000000000;
   sdm->q[tp_l_ty].initial_value = -0.0226890900;
   sdm->q[tp_l_ty].initial_velocity = 0.0;
   sdm->q[tp_l_ty].range_start = -99999.9;
   sdm->q[tp_l_ty].range_end = 99999.9;
   sdm->q[tp_l_ty].restraint_func = NULL;
   sdm->q[tp_l_ty].min_restraint_func = NULL;
   sdm->q[tp_l_ty].max_restraint_func = NULL;
   sdm->q[tp_l_ty].function_active = dpNo;
   sdm->q[tp_l_ty].constraint_func = &tp_l_ty_func;
   sdm->q[tp_l_ty].constraint_num = tp_l_ty_con;
   sdm->q[tp_l_ty].q_ind = knee_angle_l;
   sdm->q[tp_l_ty].output = dpNo;
   sdm->q[tp_l_ty].pd_stiffness = 0.0;
   sdm->q[tp_l_ty].torque = 0.0;

   mstrcpy(&sdm->q[tp_l_r1].name,"tp_l_r1");
   sdm->q[tp_l_r1].type = dpConstrainedQ;
   sdm->q[tp_l_r1].joint = tp_l;
   sdm->q[tp_l_r1].axis = 2;
   sdm->q[tp_l_r1].conversion = 57.2957795131;
   sdm->q[tp_l_r1].initial_value = -0.0669882444;
   sdm->q[tp_l_r1].initial_velocity = 0.0;
   sdm->q[tp_l_r1].range_start = -99999.9;
   sdm->q[tp_l_r1].range_end = 99999.9;
   sdm->q[tp_l_r1].restraint_func = NULL;
   sdm->q[tp_l_r1].min_restraint_func = NULL;
   sdm->q[tp_l_r1].max_restraint_func = NULL;
   sdm->q[tp_l_r1].function_active = dpNo;
   sdm->q[tp_l_r1].constraint_func = &tp_l_r1_func;
   sdm->q[tp_l_r1].constraint_num = tp_l_r1_con;
   sdm->q[tp_l_r1].q_ind = knee_angle_l;
   sdm->q[tp_l_r1].output = dpNo;
   sdm->q[tp_l_r1].pd_stiffness = 0.0;
   sdm->q[tp_l_r1].torque = 0.0;

   mstrcpy(&sdm->q[ankle_angle_l].name,"ankle_angle_l");
   sdm->q[ankle_angle_l].type = dpUnconstrainedQ;
   sdm->q[ankle_angle_l].joint = ankle_l;
   sdm->q[ankle_angle_l].axis = 0;
   sdm->q[ankle_angle_l].conversion = 57.2957795131;
   sdm->q[ankle_angle_l].initial_value = 0.0000000000;
   sdm->q[ankle_angle_l].initial_velocity = 0.0;
   sdm->q[ankle_angle_l].range_start = -50.0000000000;
   sdm->q[ankle_angle_l].range_end = 30.0000000000;
   sdm->q[ankle_angle_l].restraint_func = NULL;
   sdm->q[ankle_angle_l].min_restraint_func = &q_restraint_func[16];
   sdm->q[ankle_angle_l].max_restraint_func = &q_restraint_func[17];
   sdm->q[ankle_angle_l].function_active = dpNo;
   sdm->q[ankle_angle_l].constraint_func = NULL;
   sdm->q[ankle_angle_l].constraint_num = -1;
   sdm->q[ankle_angle_l].q_ind = -1;
   sdm->q[ankle_angle_l].output = dpYes;
   sdm->q[ankle_angle_l].pd_stiffness = 0.0000000000;
   sdm->q[ankle_angle_l].torque = 0.0;

   mstrcpy(&sdm->q[fixed23].name,"fixed23");
   sdm->q[fixed23].type = dpFixedQ;
   sdm->q[fixed23].joint = subtalar_l;
   sdm->q[fixed23].axis = 0;
   sdm->q[fixed23].conversion = 57.2957795131;
   sdm->q[fixed23].initial_value = 0.0000000000;
   sdm->q[fixed23].initial_velocity = 0.0;
   sdm->q[fixed23].range_start = -99999.9;
   sdm->q[fixed23].range_end = 99999.9;
   sdm->q[fixed23].restraint_func = NULL;
   sdm->q[fixed23].min_restraint_func = NULL;
   sdm->q[fixed23].max_restraint_func = NULL;
   sdm->q[fixed23].function_active = dpNo;
   sdm->q[fixed23].constraint_func = NULL;
   sdm->q[fixed23].constraint_num = -1;
   sdm->q[fixed23].q_ind = -1;
   sdm->q[fixed23].output = dpNo;
   sdm->q[fixed23].pd_stiffness = 0.0;
   sdm->q[fixed23].torque = 0.0;

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
   sdm->body_segment[ground+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[ground+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[ground+1].mass_center[2] = 0.0000000000;
   for (i=0; i<3; i++)
      for (j=0; j<3; j++)
         sdm->body_segment[ground+1].inertia[i][j] = 0.0;
   sdm->body_segment[ground+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[crank+1].name,"crank");
   sdm->body_segment[crank+1].output = dpYes;
   sdgetmass(crank, &(sdm->body_segment[crank+1].mass));
   sdgetiner(crank, sdm->body_segment[crank+1].inertia);
   sdm->body_segment[crank+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[crank+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[crank+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[crank+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[pelvis+1].name,"pelvis");
   sdm->body_segment[pelvis+1].output = dpYes;
   sdgetmass(pelvis, &(sdm->body_segment[pelvis+1].mass));
   sdgetiner(pelvis, sdm->body_segment[pelvis+1].inertia);
   sdm->body_segment[pelvis+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[pelvis+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[pelvis+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[pelvis+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[pedal+1].name,"pedal");
   sdm->body_segment[pedal+1].output = dpYes;
   sdgetmass(pedal, &(sdm->body_segment[pedal+1].mass));
   sdgetiner(pedal, sdm->body_segment[pedal+1].inertia);
   sdm->body_segment[pedal+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[pedal+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[pedal+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[pedal+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[pedal_l+1].name,"pedal_l");
   sdm->body_segment[pedal_l+1].output = dpYes;
   sdgetmass(pedal_l, &(sdm->body_segment[pedal_l+1].mass));
   sdgetiner(pedal_l, sdm->body_segment[pedal_l+1].inertia);
   sdm->body_segment[pedal_l+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[pedal_l+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[pedal_l+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[pedal_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_r+1].name,"calcn_r");
   sdm->body_segment[calcn_r+1].output = dpYes;
   sdgetmass(calcn_r, &(sdm->body_segment[calcn_r+1].mass));
   sdgetiner(calcn_r, sdm->body_segment[calcn_r+1].inertia);
   sdm->body_segment[calcn_r+1].mass_center[0] = 0.0500000000;
   sdm->body_segment[calcn_r+1].mass_center[1] = 0.0300000000;
   sdm->body_segment[calcn_r+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[calcn_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_l+1].name,"calcn_l");
   sdm->body_segment[calcn_l+1].output = dpYes;
   sdgetmass(calcn_l, &(sdm->body_segment[calcn_l+1].mass));
   sdgetiner(calcn_l, sdm->body_segment[calcn_l+1].inertia);
   sdm->body_segment[calcn_l+1].mass_center[0] = 0.0500000000;
   sdm->body_segment[calcn_l+1].mass_center[1] = 0.0300000000;
   sdm->body_segment[calcn_l+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[calcn_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[femur_r+1].name,"femur_r");
   sdm->body_segment[femur_r+1].output = dpYes;
   sdgetmass(femur_r, &(sdm->body_segment[femur_r+1].mass));
   sdgetiner(femur_r, sdm->body_segment[femur_r+1].inertia);
   sdm->body_segment[femur_r+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[femur_r+1].mass_center[1] = -0.1700000000;
   sdm->body_segment[femur_r+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[femur_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[tibia_r+1].name,"tibia_r");
   sdm->body_segment[tibia_r+1].output = dpYes;
   sdgetmass(tibia_r, &(sdm->body_segment[tibia_r+1].mass));
   sdgetiner(tibia_r, sdm->body_segment[tibia_r+1].inertia);
   sdm->body_segment[tibia_r+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[tibia_r+1].mass_center[1] = -0.1867000000;
   sdm->body_segment[tibia_r+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[tibia_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[patella_r+1].name,"patella_r");
   sdm->body_segment[patella_r+1].output = dpYes;
   sdgetmass(patella_r, &(sdm->body_segment[patella_r+1].mass));
   sdgetiner(patella_r, sdm->body_segment[patella_r+1].inertia);
   sdm->body_segment[patella_r+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[patella_r+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[patella_r+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[patella_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[talus_r+1].name,"talus_r");
   sdm->body_segment[talus_r+1].output = dpYes;
   sdgetmass(talus_r, &(sdm->body_segment[talus_r+1].mass));
   sdgetiner(talus_r, sdm->body_segment[talus_r+1].inertia);
   sdm->body_segment[talus_r+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[talus_r+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[talus_r+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[talus_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_rp+1].name,"calcn_rp");
   sdm->body_segment[calcn_rp+1].output = dpYes;
   sdgetmass(calcn_rp, &(sdm->body_segment[calcn_rp+1].mass));
   sdgetiner(calcn_rp, sdm->body_segment[calcn_rp+1].inertia);
   sdm->body_segment[calcn_rp+1].mass_center[0] = 0.0500000000;
   sdm->body_segment[calcn_rp+1].mass_center[1] = 0.0300000000;
   sdm->body_segment[calcn_rp+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[calcn_rp+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[femur_l+1].name,"femur_l");
   sdm->body_segment[femur_l+1].output = dpYes;
   sdgetmass(femur_l, &(sdm->body_segment[femur_l+1].mass));
   sdgetiner(femur_l, sdm->body_segment[femur_l+1].inertia);
   sdm->body_segment[femur_l+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[femur_l+1].mass_center[1] = -0.1713000000;
   sdm->body_segment[femur_l+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[femur_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[tibia_l+1].name,"tibia_l");
   sdm->body_segment[tibia_l+1].output = dpYes;
   sdgetmass(tibia_l, &(sdm->body_segment[tibia_l+1].mass));
   sdgetiner(tibia_l, sdm->body_segment[tibia_l+1].inertia);
   sdm->body_segment[tibia_l+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[tibia_l+1].mass_center[1] = -0.1867000000;
   sdm->body_segment[tibia_l+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[tibia_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[patella_l+1].name,"patella_l");
   sdm->body_segment[patella_l+1].output = dpYes;
   sdgetmass(patella_l, &(sdm->body_segment[patella_l+1].mass));
   sdgetiner(patella_l, sdm->body_segment[patella_l+1].inertia);
   sdm->body_segment[patella_l+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[patella_l+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[patella_l+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[patella_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[talus_l+1].name,"talus_l");
   sdm->body_segment[talus_l+1].output = dpYes;
   sdgetmass(talus_l, &(sdm->body_segment[talus_l+1].mass));
   sdgetiner(talus_l, sdm->body_segment[talus_l+1].inertia);
   sdm->body_segment[talus_l+1].mass_center[0] = 0.0000000000;
   sdm->body_segment[talus_l+1].mass_center[1] = 0.0000000000;
   sdm->body_segment[talus_l+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[talus_l+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[calcn_lp+1].name,"calcn_lp");
   sdm->body_segment[calcn_lp+1].output = dpYes;
   sdgetmass(calcn_lp, &(sdm->body_segment[calcn_lp+1].mass));
   sdgetiner(calcn_lp, sdm->body_segment[calcn_lp+1].inertia);
   sdm->body_segment[calcn_lp+1].mass_center[0] = 0.0500000000;
   sdm->body_segment[calcn_lp+1].mass_center[1] = 0.0300000000;
   sdm->body_segment[calcn_lp+1].mass_center[2] = 0.0000000000;
   sdm->body_segment[calcn_lp+1].contactable = dpNo;

   mstrcpy(&sdm->name, "Two-Legged Cycling");

   check_for_sderror("INIT_SEGMENTS");

}


/* INIT_Q_RESTRAINT_FUNCTIONS: this routine initializes the restraint
 * functions which are used to keep the Qs from exceeding their ranges of motion.
 */

void init_q_restraint_functions(void)
{
   int i, numpts;

   numpts = sizeof(q_restraint_func1_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[0],numpts);
   q_restraint_func[0].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[0].x[i] = q_restraint_func1_data[i][0];
      q_restraint_func[0].y[i] = q_restraint_func1_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[0]);
   numpts = sizeof(q_restraint_func2_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[1],numpts);
   q_restraint_func[1].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[1].x[i] = q_restraint_func2_data[i][0];
      q_restraint_func[1].y[i] = q_restraint_func2_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[1]);
   numpts = sizeof(q_restraint_func3_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[2],numpts);
   q_restraint_func[2].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[2].x[i] = q_restraint_func3_data[i][0];
      q_restraint_func[2].y[i] = q_restraint_func3_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[2]);
   numpts = sizeof(q_restraint_func4_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[3],numpts);
   q_restraint_func[3].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[3].x[i] = q_restraint_func4_data[i][0];
      q_restraint_func[3].y[i] = q_restraint_func4_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[3]);
   numpts = sizeof(q_restraint_func5_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[4],numpts);
   q_restraint_func[4].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[4].x[i] = q_restraint_func5_data[i][0];
      q_restraint_func[4].y[i] = q_restraint_func5_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[4]);
   numpts = sizeof(q_restraint_func6_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[5],numpts);
   q_restraint_func[5].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[5].x[i] = q_restraint_func6_data[i][0];
      q_restraint_func[5].y[i] = q_restraint_func6_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[5]);
   numpts = sizeof(q_restraint_func7_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[6],numpts);
   q_restraint_func[6].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[6].x[i] = q_restraint_func7_data[i][0];
      q_restraint_func[6].y[i] = q_restraint_func7_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[6]);
   numpts = sizeof(q_restraint_func8_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[7],numpts);
   q_restraint_func[7].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[7].x[i] = q_restraint_func8_data[i][0];
      q_restraint_func[7].y[i] = q_restraint_func8_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[7]);
   numpts = sizeof(q_restraint_func9_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[8],numpts);
   q_restraint_func[8].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[8].x[i] = q_restraint_func9_data[i][0];
      q_restraint_func[8].y[i] = q_restraint_func9_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[8]);
   numpts = sizeof(q_restraint_func10_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[9],numpts);
   q_restraint_func[9].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[9].x[i] = q_restraint_func10_data[i][0];
      q_restraint_func[9].y[i] = q_restraint_func10_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[9]);
   numpts = sizeof(q_restraint_func11_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[10],numpts);
   q_restraint_func[10].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[10].x[i] = q_restraint_func11_data[i][0];
      q_restraint_func[10].y[i] = q_restraint_func11_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[10]);
   numpts = sizeof(q_restraint_func12_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[11],numpts);
   q_restraint_func[11].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[11].x[i] = q_restraint_func12_data[i][0];
      q_restraint_func[11].y[i] = q_restraint_func12_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[11]);
   numpts = sizeof(q_restraint_func13_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[12],numpts);
   q_restraint_func[12].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[12].x[i] = q_restraint_func13_data[i][0];
      q_restraint_func[12].y[i] = q_restraint_func13_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[12]);
   numpts = sizeof(q_restraint_func14_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[13],numpts);
   q_restraint_func[13].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[13].x[i] = q_restraint_func14_data[i][0];
      q_restraint_func[13].y[i] = q_restraint_func14_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[13]);
   numpts = sizeof(q_restraint_func15_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[14],numpts);
   q_restraint_func[14].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[14].x[i] = q_restraint_func15_data[i][0];
      q_restraint_func[14].y[i] = q_restraint_func15_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[14]);
   numpts = sizeof(q_restraint_func16_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[15],numpts);
   q_restraint_func[15].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[15].x[i] = q_restraint_func16_data[i][0];
      q_restraint_func[15].y[i] = q_restraint_func16_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[15]);
   numpts = sizeof(q_restraint_func17_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[16],numpts);
   q_restraint_func[16].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[16].x[i] = q_restraint_func17_data[i][0];
      q_restraint_func[16].y[i] = q_restraint_func17_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[16]);
   numpts = sizeof(q_restraint_func18_data)/(sizeof(double)*2);
   (void)malloc_function(&q_restraint_func[17],numpts);
   q_restraint_func[17].numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      q_restraint_func[17].x[i] = q_restraint_func18_data[i][0];
      q_restraint_func[17].y[i] = q_restraint_func18_data[i][1];
   }
   calc_spline_coefficients(&q_restraint_func[17]);
}


/* INIT_JOINT_FUNCTIONS: this routine initializes the constraint functions
 * for the joints which have user-defined constraints.
 */

void init_joint_functions(void)
{

   int i, numpts;

   numpts = sizeof(femoral_tibial_r_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&femoral_tibial_r_tx_func,numpts);
   femoral_tibial_r_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      femoral_tibial_r_tx_func.x[i] = femoral_tibial_r_tx_data[i][0];
      femoral_tibial_r_tx_func.y[i] = femoral_tibial_r_tx_data[i][1];
   }
   calc_spline_coefficients(&femoral_tibial_r_tx_func);

   numpts = sizeof(femoral_tibial_r_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&femoral_tibial_r_ty_func,numpts);
   femoral_tibial_r_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      femoral_tibial_r_ty_func.x[i] = femoral_tibial_r_ty_data[i][0];
      femoral_tibial_r_ty_func.y[i] = femoral_tibial_r_ty_data[i][1];
   }
   calc_spline_coefficients(&femoral_tibial_r_ty_func);

   numpts = sizeof(tp_r_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&tp_r_tx_func,numpts);
   tp_r_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tp_r_tx_func.x[i] = tp_r_tx_data[i][0];
      tp_r_tx_func.y[i] = tp_r_tx_data[i][1];
   }
   calc_spline_coefficients(&tp_r_tx_func);

   numpts = sizeof(tp_r_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&tp_r_ty_func,numpts);
   tp_r_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tp_r_ty_func.x[i] = tp_r_ty_data[i][0];
      tp_r_ty_func.y[i] = tp_r_ty_data[i][1];
   }
   calc_spline_coefficients(&tp_r_ty_func);

   numpts = sizeof(tp_r_r1_data)/(sizeof(double)*2);
   (void)malloc_function(&tp_r_r1_func,numpts);
   tp_r_r1_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tp_r_r1_func.x[i] = tp_r_r1_data[i][0];
      tp_r_r1_func.y[i] = tp_r_r1_data[i][1];
   }
   calc_spline_coefficients(&tp_r_r1_func);

   numpts = sizeof(femoral_tibial_l_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&femoral_tibial_l_tx_func,numpts);
   femoral_tibial_l_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      femoral_tibial_l_tx_func.x[i] = femoral_tibial_l_tx_data[i][0];
      femoral_tibial_l_tx_func.y[i] = femoral_tibial_l_tx_data[i][1];
   }
   calc_spline_coefficients(&femoral_tibial_l_tx_func);

   numpts = sizeof(femoral_tibial_l_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&femoral_tibial_l_ty_func,numpts);
   femoral_tibial_l_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      femoral_tibial_l_ty_func.x[i] = femoral_tibial_l_ty_data[i][0];
      femoral_tibial_l_ty_func.y[i] = femoral_tibial_l_ty_data[i][1];
   }
   calc_spline_coefficients(&femoral_tibial_l_ty_func);

   numpts = sizeof(tp_l_tx_data)/(sizeof(double)*2);
   (void)malloc_function(&tp_l_tx_func,numpts);
   tp_l_tx_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tp_l_tx_func.x[i] = tp_l_tx_data[i][0];
      tp_l_tx_func.y[i] = tp_l_tx_data[i][1];
   }
   calc_spline_coefficients(&tp_l_tx_func);

   numpts = sizeof(tp_l_ty_data)/(sizeof(double)*2);
   (void)malloc_function(&tp_l_ty_func,numpts);
   tp_l_ty_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tp_l_ty_func.x[i] = tp_l_ty_data[i][0];
      tp_l_ty_func.y[i] = tp_l_ty_data[i][1];
   }
   calc_spline_coefficients(&tp_l_ty_func);

   numpts = sizeof(tp_l_r1_data)/(sizeof(double)*2);
   (void)malloc_function(&tp_l_r1_func,numpts);
   tp_l_r1_func.numpoints = numpts;
   for (i=0; i<numpts; i++)
   {
      tp_l_r1_func.x[i] = tp_l_r1_data[i][0];
      tp_l_r1_func.y[i] = tp_l_r1_data[i][1];
   }
   calc_spline_coefficients(&tp_l_r1_func);

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

