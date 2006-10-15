/*******************************************************************************

  model.h

  10/05/2006 12:35:35 PM

*******************************************************************************/

/*********** Joints ************/
#define          ground_pelvis  0
#define                  hip_r  1
#define                 knee_r  2
#define              tib_pat_r  3
#define                ankle_r  4
#define             subtalar_r  5
#define                  mtp_r  6
#define                  hip_l  7
#define                 knee_l  8
#define              tib_pat_l  9
#define                ankle_l 10
#define             subtalar_l 11
#define                  mtp_l 12
#define                   back 13

/************* Qs **************/
#define              pelvis_tz  0   /* = sdindx(ground_pelvis,0) */
#define              pelvis_tx  1   /* = sdindx(ground_pelvis,1) */
#define              pelvis_ty  2   /* = sdindx(ground_pelvis,2) */
#define            pelvis_tilt  3   /* = sdindx(ground_pelvis,3) */
#define            pelvis_list  4   /* = sdindx(ground_pelvis,4) */
#define        pelvis_rotation  5   /* = sdindx(ground_pelvis,5) */
#define          hip_flexion_r  6   /* = sdindx(hip_r,0) */
#define        hip_adduction_r  7   /* = sdindx(hip_r,1) */
#define         hip_rotation_r  8   /* = sdindx(hip_r,2) */
#define              knee_r_tx  9   /* = sdindx(knee_r,0) */
#define              knee_r_ty 10   /* = sdindx(knee_r,1) */
#define           knee_angle_r 11   /* = sdindx(knee_r,2) */
#define           tib_pat_r_tx 12   /* = sdindx(tib_pat_r,0) */
#define           tib_pat_r_ty 13   /* = sdindx(tib_pat_r,1) */
#define           tib_pat_r_r1 14   /* = sdindx(tib_pat_r,2) */
#define          ankle_angle_r 15   /* = sdindx(ankle_r,0) */
#define       subtalar_angle_r 16   /* = sdindx(subtalar_r,0) */
#define            mtp_angle_r 17   /* = sdindx(mtp_r,0) */
#define          hip_flexion_l 18   /* = sdindx(hip_l,0) */
#define        hip_adduction_l 19   /* = sdindx(hip_l,1) */
#define         hip_rotation_l 20   /* = sdindx(hip_l,2) */
#define              knee_l_tx 21   /* = sdindx(knee_l,0) */
#define              knee_l_ty 22   /* = sdindx(knee_l,1) */
#define           knee_angle_l 23   /* = sdindx(knee_l,2) */
#define           tib_pat_l_tx 24   /* = sdindx(tib_pat_l,0) */
#define           tib_pat_l_ty 25   /* = sdindx(tib_pat_l,1) */
#define           tib_pat_l_r1 26   /* = sdindx(tib_pat_l,2) */
#define          ankle_angle_l 27   /* = sdindx(ankle_l,0) */
#define       subtalar_angle_l 28   /* = sdindx(subtalar_l,0) */
#define            mtp_angle_l 29   /* = sdindx(mtp_l,0) */
#define       lumbar_extension 30   /* = sdindx(back,0) */
#define         lumbar_bending 31   /* = sdindx(back,1) */
#define        lumbar_rotation 32   /* = sdindx(back,2) */

/******* Constrained Qs ********/
#define          knee_r_tx_con  0
#define          knee_r_ty_con  1
#define       tib_pat_r_tx_con  2
#define       tib_pat_r_ty_con  3
#define       tib_pat_r_r1_con  4
#define          knee_l_tx_con  5
#define          knee_l_ty_con  6
#define       tib_pat_l_tx_con  7
#define       tib_pat_l_ty_con  8
#define       tib_pat_l_r1_con  9

/******** Body Segments ********/
#define                 ground -1
#define                 pelvis  0
#define                femur_r  1
#define                tibia_r  2
#define              patella_r  3
#define                talus_r  4
#define                calcn_r  5
#define                 toes_r  6
#define                femur_l  7
#define                tibia_l  8
#define              patella_l  9
#define                talus_l 10
#define                calcn_l 11
#define                 toes_l 12
#define                  torso 13
