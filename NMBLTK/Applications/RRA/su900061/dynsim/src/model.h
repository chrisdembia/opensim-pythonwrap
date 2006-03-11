/*******************************************************************************

   D:\programfiles\cimtj\rra\900061\dynsim\src\model.h

   Created by SIMM 4.0.1 (from joint file D:\programfiles\gaitdata\FromAllison\SuccessfulCases\900061.jnt)

   Time of creation: 02/06/2006 04:56:06 PM

*******************************************************************************/

/*********** Joints ************/
#define        ground_calcn_rp  0
#define        ground_calcn_lp  1
#define          ground_pelvis  2
#define                  hip_r  3
#define                 knee_r  4
#define              tib_pat_r  5
#define                ankle_r  6
#define             subtalar_r  7
#define                  mtp_r  8
#define                  hip_l  9
#define                 knee_l 10
#define              tib_pat_l 11
#define                ankle_l 12
#define             subtalar_l 13
#define                  mtp_l 14
#define                   back 15

/************* Qs **************/
#define             calcn_r_tx  0   /* = sdindx(ground_calcn_rp,0) */
#define             calcn_r_ty  1   /* = sdindx(ground_calcn_rp,1) */
#define             calcn_r_tz  2   /* = sdindx(ground_calcn_rp,2) */
#define             calcn_r_r1  3   /* = sdindx(ground_calcn_rp,3) */
#define             calcn_r_r2  4   /* = sdindx(ground_calcn_rp,4) */
#define             calcn_r_r3  5   /* = sdindx(ground_calcn_rp,5) */
#define             calcn_l_tx  6   /* = sdindx(ground_calcn_lp,0) */
#define             calcn_l_ty  7   /* = sdindx(ground_calcn_lp,1) */
#define             calcn_l_tz  8   /* = sdindx(ground_calcn_lp,2) */
#define             calcn_l_r1  9   /* = sdindx(ground_calcn_lp,3) */
#define             calcn_l_r2 10   /* = sdindx(ground_calcn_lp,4) */
#define             calcn_l_r3 11   /* = sdindx(ground_calcn_lp,5) */
#define              pelvis_tz 12   /* = sdindx(ground_pelvis,0) */
#define              pelvis_tx 13   /* = sdindx(ground_pelvis,1) */
#define              pelvis_ty 14   /* = sdindx(ground_pelvis,2) */
#define            pelvis_tilt 15   /* = sdindx(ground_pelvis,3) */
#define            pelvis_list 16   /* = sdindx(ground_pelvis,4) */
#define        pelvis_rotation 17   /* = sdindx(ground_pelvis,5) */
#define          hip_flexion_r 18   /* = sdindx(hip_r,0) */
#define        hip_adduction_r 19   /* = sdindx(hip_r,1) */
#define         hip_rotation_r 20   /* = sdindx(hip_r,2) */
#define              knee_r_tx 21   /* = sdindx(knee_r,0) */
#define              knee_r_ty 22   /* = sdindx(knee_r,1) */
#define           knee_angle_r 23   /* = sdindx(knee_r,2) */
#define           tib_pat_r_tx 24   /* = sdindx(tib_pat_r,0) */
#define           tib_pat_r_ty 25   /* = sdindx(tib_pat_r,1) */
#define           tib_pat_r_r3 26   /* = sdindx(tib_pat_r,2) */
#define          ankle_angle_r 27   /* = sdindx(ankle_r,0) */
#define       subtalar_angle_r 28   /* = sdindx(subtalar_r,0) */
#define            mtp_angle_r 29   /* = sdindx(mtp_r,0) */
#define          hip_flexion_l 30   /* = sdindx(hip_l,0) */
#define        hip_adduction_l 31   /* = sdindx(hip_l,1) */
#define         hip_rotation_l 32   /* = sdindx(hip_l,2) */
#define              knee_l_tx 33   /* = sdindx(knee_l,0) */
#define              knee_l_ty 34   /* = sdindx(knee_l,1) */
#define           knee_angle_l 35   /* = sdindx(knee_l,2) */
#define           tib_pat_l_tx 36   /* = sdindx(tib_pat_l,0) */
#define           tib_pat_l_ty 37   /* = sdindx(tib_pat_l,1) */
#define           tib_pat_l_r3 38   /* = sdindx(tib_pat_l,2) */
#define          ankle_angle_l 39   /* = sdindx(ankle_l,0) */
#define       subtalar_angle_l 40   /* = sdindx(subtalar_l,0) */
#define            mtp_angle_l 41   /* = sdindx(mtp_l,0) */
#define       lumbar_extension 42   /* = sdindx(back,0) */
#define         lumbar_bending 43   /* = sdindx(back,1) */
#define        lumbar_rotation 44   /* = sdindx(back,2) */

/******* Constrained Qs ********/
#define          knee_r_tx_con  0
#define          knee_r_ty_con  1
#define       tib_pat_r_tx_con  2
#define       tib_pat_r_ty_con  3
#define       tib_pat_r_r3_con  4
#define          knee_l_tx_con  5
#define          knee_l_ty_con  6
#define       tib_pat_l_tx_con  7
#define       tib_pat_l_ty_con  8
#define       tib_pat_l_r3_con  9

/******** Body Segments ********/
#define                 ground -1
#define               calcn_rp  0
#define               calcn_lp  1
#define                 pelvis  2
#define                femur_r  3
#define                tibia_r  4
#define              patella_r  5
#define                talus_r  6
#define                calcn_r  7
#define                 toes_r  8
#define                femur_l  9
#define                tibia_l 10
#define              patella_l 11
#define                talus_l 12
#define                calcn_l 13
#define                 toes_l 14
#define                  torso 15
