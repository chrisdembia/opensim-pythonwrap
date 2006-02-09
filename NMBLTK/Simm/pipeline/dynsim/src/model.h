/*******************************************************************************

  pipeline/dynsim/src/model.h

  11/07/2005 12:58:13 PM

*******************************************************************************/

/*********** Joints ************/
#define                     bb  0
#define                 pelvis  1
#define                     cp  2
#define                   cp_l  3
#define                     pc  4
#define                   pc_l  5
#define                  hip_r  6
#define       femoral_tibial_r  7
#define                   tp_r  8
#define                ankle_r  9
#define             subtalar_r 10
#define                  hip_l 11
#define       femoral_tibial_l 12
#define                   tp_l 13
#define                ankle_l 14
#define             subtalar_l 15

/************* Qs **************/
#define            crank_angle  0   /* = sdindx(bb,0) */
#define                 fixed1  1   /* = sdindx(pelvis,0) */
#define            pedal_angle  2   /* = sdindx(cp,0) */
#define          pedal_angle_l  3   /* = sdindx(cp_l,0) */
#define                 fixed4  4   /* = sdindx(pc,0) */
#define                 fixed5  5   /* = sdindx(pc_l,0) */
#define          hip_flexion_r  6   /* = sdindx(hip_r,0) */
#define    femoral_tibial_r_tx  7   /* = sdindx(femoral_tibial_r,0) */
#define    femoral_tibial_r_ty  8   /* = sdindx(femoral_tibial_r,1) */
#define           knee_angle_r  9   /* = sdindx(femoral_tibial_r,2) */
#define                tp_r_tx 10   /* = sdindx(tp_r,0) */
#define                tp_r_ty 11   /* = sdindx(tp_r,1) */
#define                tp_r_r1 12   /* = sdindx(tp_r,2) */
#define          ankle_angle_r 13   /* = sdindx(ankle_r,0) */
#define                fixed14 14   /* = sdindx(subtalar_r,0) */
#define          hip_flexion_l 15   /* = sdindx(hip_l,0) */
#define    femoral_tibial_l_tx 16   /* = sdindx(femoral_tibial_l,0) */
#define    femoral_tibial_l_ty 17   /* = sdindx(femoral_tibial_l,1) */
#define           knee_angle_l 18   /* = sdindx(femoral_tibial_l,2) */
#define                tp_l_tx 19   /* = sdindx(tp_l,0) */
#define                tp_l_ty 20   /* = sdindx(tp_l,1) */
#define                tp_l_r1 21   /* = sdindx(tp_l,2) */
#define          ankle_angle_l 22   /* = sdindx(ankle_l,0) */
#define                fixed23 23   /* = sdindx(subtalar_l,0) */

/******* Constrained Qs ********/
#define femoral_tibial_r_tx_con  0
#define femoral_tibial_r_ty_con  1
#define            tp_r_tx_con  2
#define            tp_r_ty_con  3
#define            tp_r_r1_con  4
#define femoral_tibial_l_tx_con  5
#define femoral_tibial_l_ty_con  6
#define            tp_l_tx_con  7
#define            tp_l_ty_con  8
#define            tp_l_r1_con  9

/******** Body Segments ********/
#define                 ground -1
#define                  crank  0
#define                 pelvis  1
#define                  pedal  2
#define                pedal_l  3
#define                calcn_r  4
#define                calcn_l  5
#define                femur_r  6
#define                tibia_r  7
#define              patella_r  8
#define                talus_r  9
#define               calcn_rp 10
#define                femur_l 11
#define                tibia_l 12
#define              patella_l 13
#define                talus_l 14
#define               calcn_lp 15
