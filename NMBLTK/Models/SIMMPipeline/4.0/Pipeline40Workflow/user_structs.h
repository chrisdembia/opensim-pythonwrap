/*******************************************************************************

   USER_STRUCTS.H

   Author: Darryl Thelen

   Description: This file contains definitions of custom structures that
   supplement the Dynamics Pipeline code

*******************************************************************************/

#ifndef USER_STRUCTS_H
#define USER_STRUCTS_H


#include <SU/Models/SIMMPipeline/4.0/suPipeline40/dp/universal.h>



typedef struct
{
   dpBoolean extForces;
   dpBoolean extTorques;
   dpBoolean muscleExcitations;
   dpBoolean fiberLengths;
   dpBoolean markerKinematics;
} dtOutputOptions;



STRUCT {
   int refSegment;          /* reference body segment in which current torque vector is described */
   int applSegment;              /* body segment to which torque is applied */
   int outputSegment;             /* body segment to which external torque is referenced to in output motion file */
   double appl_point[3];            /* pnt of application of force (local coords) */
   double force_vec[3];             /* force vector */
} ForceVecStruct;                   /* contains one external force */


STRUCT {
   int refSegment;          /* reference body segment in which current torque vector is described */
   int applSegment;              /* body segment to which torque is applied */
   int outputSegment;             /* body segment to which external torque is referenced to in output motion file */
   double torque_vec[3];             /* torque vector */
} TorqueVecStruct;                       /* contains one external torque vector */


#endif /* USER_STRUCTS_H */