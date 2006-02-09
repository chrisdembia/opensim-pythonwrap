/*******************************************************************************

   READTOOLS.C

   Author: Peter Loan
           Krystyne Blaikie

   Copyright (c) 1996-2005 MusculoGraphics, a division of Motion Analysis Corp.
   All rights reserved.

   Description: This file contains tools for reading ascii text from
      input files, and for extracting numbers and strings from the text.

   Routines:
      get_muscle_file_name      : reads the muscle file name from the parameters file
      read_parameters_file      : reads the parameters file for the stand-alone app
      read_dllparameters_file   : reads the parameters file for the DLL app
      preprocess_file           : runs acpp on a file, then opens it
      read_string               : reads a string from a file
      read_line                 : reads a possibly empty line from a file
      read_nonempty_line        : reads a non-empty line of chars from a file
		read_til_tokens           : reads from a file until certain tokens are found
      clean_string              : removes leading and trailing white space
      read_muscle_groups        : reads a set of muscle group names from a file
      read_muscle_attachment_points : reads muscle attachment points from a file
      read_double_array         : reads an array of x-y pairs from a file
      string_contains_closing_paren : checks to see if string has closing paren
      get_xy_pair_from_string   : reads x-y pair from a file, e.g. (0.00,0.00)
      parse_string              : extracts variable w/specified type from string
      enter_segment             : enters a segment name into a model's database
      enter_gencoord            : enters a gencoord name into a model's database
      load_kinetics_data        : does set up for reading kinetics data
      read_kinetics_file        : reads kinetics data from a .ktx file
      read_motion_file          : reads kinetics data from a .mot file
      verify_kinetics_data      : checks kinetics data from .ktx file for completeness
      verify_motion_data        : checks kinetics data from .mot file for completeness
      name_is_gencoord          : checks if a string is a gencoord or gc deriv
      name_is_body_segment      : checks is a string is a body segment name
      string_hss_suffix         : compares one string to the end of another
      simm_malloc               : wrapper routine for malloc
      simm_calloc               : wrapper routine for calloc
      simm_realloc              : wrapper routine for realloc
      convert_string            : converts special chars in a string to '_'
      is_absolute_path          : determines whether filename is an absolute path
      read_spring               : reads a spring element from parameters file
      read_spring_floor         : reads a spring floor element from parameters file
      append_if_necessary       : appends a DIR_SEP_CHAR to a file name if necessary

*******************************************************************************/

#include "universal.h"


/*************** DEFINES (for this file only) *********************************/
typedef enum {POS_X = 0, POS_Y, POS_Z, VEC_X, VEC_Y, VEC_Z} FTcomponent;


/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/
static char* velocity_suffix = "_vel";
static char* acceleration_suffix = "_acc";
static char* force_suffix = "_force";
static char* torque_suffix = "_torque";
static char* linear_text = "_lin";
static char* natural_cubic_text = "_spl";
static char* gcv_text = "_gcv";
static char* px_suffix = "_force_px";
static char* py_suffix = "_force_py";
static char* pz_suffix = "_force_pz";
static char* vx_suffix = "_force_vx";
static char* vy_suffix = "_force_vy";
static char* vz_suffix = "_force_vz";
static char* ax_suffix = "_torque_x";
static char* ay_suffix = "_torque_y";
static char* az_suffix = "_torque_z";


/**************** GLOBAL VARIABLES (used in only a few files) *****************/
char buffer[CHARBUFFER];
char buffer2[CHARBUFFER];
char *bone_path = NULL;


/*************** EXTERNED VARIABLES (declared in another file) ****************/
extern dpModelStruct* sdm;								/* defined in sdfor.c */
extern dpBoolean verbose;
#ifndef INVERSE
extern dpSimulationParameters params;
#endif

/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/
static ReturnCode verify_kinetics_data(dpModelStruct* sdm, MotionData* data);
static void map_motion_force(dpModelStruct* sdm, MotionData* data, int segNum, FTcomponent comp,
                             dpSplineType splineType, double cutoffFrequency, int column);
static void map_motion_torque(dpModelStruct* sdm, MotionData* data, int segNum, FTcomponent comp,
                              dpSplineType splineType, double cutoffFrequency, int column);
static ReturnCode verify_motion_data(dpModelStruct* sdm, MotionData* data);
static int name_is_gencoord(char name[], dpModelStruct* sdm, char suffix[],
                            dpSplineType* splineType, double* cutoffFrequency);
static int name_is_body_segment(char name[], dpModelStruct* sdm, char suffix[],
                                dpSplineType* splineType, double* cutoffFrequency);
static int name_is_muscle(char name[], dpModelStruct* sdm, char suffix[],
                          dpSplineType* splineType, double* cutoffFrequency);
static dpBoolean string_has_suffix(char str1[], char suffix[]);
static dpBoolean string_contains_closing_paren(char str_buffer[]);
static ReturnCode read_spring_floor(FILE** fp);
static ReturnCode read_spring(FILE** fp);
static ReturnCode read_force_matte(FILE** fp);


ReturnCode get_muscle_file_name(char params_file[], char** muscle_file)
{
   char* filename;
   FILE* fp;   

   if ((fp = fopen(params_file, "r")) == NULL)
      return code_bad;

   while (1)
   {
      if (fscanf(fp, "%s", buffer) != 1)
         break;

      if (buffer[0] == '#')
      {
         read_line(&fp, buffer);
         continue;
      }

      if (STRINGS_ARE_EQUAL(buffer, "muscle_file") && muscle_file)
      {
         read_line(&fp, buffer);
         filename = clean_string(buffer);
         if (filename == NULL || strlen(filename) < 1)
            sim_message(exit_program, "Error reading muscle_file name in %s.", params_file);
         else
            mstrcpy(muscle_file, filename);
      }
   }

   fclose(fp);

   return code_fine;
}


ReturnCode read_parameters_file(char params_file[], dpModelStruct* sdm,
				                    char** kinetics_file, char** output_motion_file,
                                char** output_kinetics_file)
{
   int i, j, k;
   double mass, inertia[3][3];
   char* filename;
   FILE* fp;   

   if ((fp = fopen(params_file,"r")) == NULL)
      return code_bad;

#if CONTACT_DETECTION
   init_object_info();
#endif

   while (1)
   {
      if (fscanf(fp, "%s", buffer) != 1)
         break;

      if (buffer[0] == '#')
      {
         read_line(&fp, buffer);
         continue;
      }

      if (STRINGS_ARE_EQUAL(buffer,"verbose"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            verbose = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            verbose = dpNo;
         else
            sim_message(exit_program, "Error reading verbose mode (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"kinetics_file") && kinetics_file)
      {
         read_line(&fp, buffer);
         filename = clean_string(buffer);
         if (filename == NULL || strlen(filename) < 1)
            sim_message(exit_program, "Error reading kinetics_file name in %s.", params_file);
         else
            mstrcpy(kinetics_file,filename);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_motion_file") && output_motion_file)
      {
         read_line(&fp, buffer);
         filename = clean_string(buffer);
         if (filename == NULL || strlen(filename) < 1)
            sim_message(exit_program, "Error reading output_motion_file name in %s.", params_file);
         else
            mstrcpy(output_motion_file,filename);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_kinetics_file") && output_kinetics_file)
      {
         read_line(&fp, buffer);
         filename = clean_string(buffer);
         if (filename == NULL || strlen(filename) < 1)
            sim_message(exit_program, "Error reading output_kinetics_file name in %s.", params_file);
         else
            mstrcpy(output_kinetics_file,filename);
      }
      else if (STRINGS_ARE_EQUAL(buffer, "muscle_file"))
      {
         /* muscle_file is read from the parameters file by a different
          * function (get_muscle_file_name(), called earlier). So here just
          * skip over the muscle file name.
          */
         read_line(&fp, buffer);
      }
      else if (STRINGS_ARE_EQUAL(buffer, "bone_path"))
      {
         read_line(&fp, buffer);
         filename = clean_string(buffer);
         if (filename == NULL || strlen(filename) < 1)
            sim_message(exit_program, "Error reading bone_path name in %s.", params_file);
         else
            mstrcpy(&bone_path,filename);
      }
#ifndef INVERSE
      else if (STRINGS_ARE_EQUAL(buffer,"spring"))
      {
         read_spring(&fp);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"spring_floor"))
      {
         read_spring_floor(&fp);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"force_matte"))
      {
         read_force_matte(&fp);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"start_time"))
      {
         if (fscanf(fp,"%lf", &params.startTime) != 1)
            sim_message(exit_program, "Error reading start_time from file %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"end_time"))
      {
         if (fscanf(fp,"%lf", &params.endTime) != 1)
            sim_message(exit_program, "Error reading end_time from file %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"step_size"))
      {
         if (fscanf(fp,"%lf", &params.stepSize) != 1)
            sim_message(exit_program, "Error reading step_size from file %s.", params_file);
      }
		else if (STRINGS_ARE_EQUAL(buffer,"output_gencoord_values"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.gencoordValues = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.gencoordValues = dpNo;
         else
            sim_message(exit_program, "Error reading output_gencoord_values (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_muscle_activations"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.muscleActivations = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.muscleActivations = dpNo;
         else
            sim_message(exit_program, "Error reading output_muscle_activations (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_muscle_lengths"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.muscleLengths = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.muscleLengths = dpNo;
         else
            sim_message(exit_program, "Error reading output_muscle_lengths (true/yes or false/no) in %s.", params_file);
      }
	  else if (STRINGS_ARE_EQUAL(buffer,"output_muscle_fiber_lengths"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.muscleFiberLengths = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.muscleFiberLengths = dpNo;
         else
            sim_message(exit_program, "Error reading output_muscle_fiber_lengths (true/yes or false/no) in %s.", params_file);
      }
	  else if (STRINGS_ARE_EQUAL(buffer,"output_muscle_fiber_velocities"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.muscleFiberVelocities = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.muscleFiberVelocities = dpNo;
         else
            sim_message(exit_program, "Error reading output_muscle_fiber_velocities (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_muscle_forces"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.muscleForces = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.muscleForces = dpNo;
         else
            sim_message(exit_program, "Error reading output_muscle_forces (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_muscles"))
      {
         sim_message(none, "Parameter output_muscles is no longer supported.");
         sim_message(none, "Please use one or more of the following instead:");
         sim_message(none, "   output_muscle_activations");
         sim_message(none, "   output_muscle_lengths");
         sim_message(none, "   output_muscle_forces");
         sim_message(none, "   output_muscle_moment_arms");
         sim_message(none, "   output_muscle_joint_torques");
         sim_message(exit_program, "   output_total_muscle_joint_torques");
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_contact_forces"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.contactForces = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.contactForces = dpNo;
         else
            sim_message(exit_program, "Error reading output_contact_forces (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_joint_torques"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
			{
            params.outputOptions.jointTorques = dpYes;
				params.outputOptions.traditionalInverse = dpYes;
			}
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
			{
				// can't set it to dpNo because output_corrected_joint_torques may have already set it to yes
            //params.outputOptions.jointTorques = dpNo;
			}
         else
            sim_message(exit_program, "Error reading output_joint_torques (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_corrected_joint_torques"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
			{
            params.outputOptions.jointTorques = dpYes;
				params.outputOptions.traditionalInverse = dpNo;
			}
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
			{
				// can't set it to dpNo because output_joint_torques may have already set it to yes
            //params.outputOptions.jointTorques = dpNo;
			}
         else
            sim_message(exit_program, "Error reading output_corrected_joint_torques (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_optimized_muscle_activations"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.optimizedMuscleActivations = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.optimizedMuscleActivations = dpNo;
         else
            sim_message(exit_program, "Error reading output_optimized_muscle_activations (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_muscle_moment_arms"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.muscleMomentArms = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.muscleMomentArms = dpNo;
         else
            sim_message(exit_program, "Error reading output_muscle_moment_arms (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_muscle_joint_torques"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.muscleJointTorques = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.muscleJointTorques = dpNo;
         else
            sim_message(exit_program, "Error reading output_muscle_joint_torques (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_total_muscle_joint_torques"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.totalMuscleJointTorques = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.totalMuscleJointTorques = dpNo;
         else
            sim_message(exit_program, "Error reading output_total_muscle_joint_torques (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_joint_reaction_forces"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.jointReactionForces = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.jointReactionForces = dpNo;
         else
            sim_message(exit_program, "Error reading output_joint_reaction_forces (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_joint_reaction_torques"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.jointReactionTorques = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.jointReactionTorques = dpNo;
         else
            sim_message(exit_program, "Error reading output_joint_reaction_torques (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_mass_center_positions"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.massCenterPositions = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.massCenterPositions = dpNo;
         else
            sim_message(exit_program, "Error reading output_mass_center_positions (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_mass_center_velocities"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.massCenterVelocities = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.massCenterVelocities = dpNo;
         else
            sim_message(exit_program, "Error reading output_mass_center_velocities (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"output_system_energy"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.systemEnergy = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.systemEnergy = dpNo;
         else
            sim_message(exit_program, "Error reading output_system_energy (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer, "output_spring_forces"))
      {
         fscanf(fp,"%s", buffer);
         if (STRINGS_ARE_EQUAL(buffer,"true") || STRINGS_ARE_EQUAL(buffer,"yes"))
            params.outputOptions.springForces = dpYes;
         else if (STRINGS_ARE_EQUAL(buffer,"false") || STRINGS_ARE_EQUAL(buffer,"no"))
            params.outputOptions.springForces = dpNo;
         else
            sim_message(exit_program, "Error reading output_spring_forces (true/yes or false/no) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer, "num_output_spring_forces"))
      {
         if (fscanf(fp,"%d", &params.outputOptions.numSpringForces) != 1)
            sim_message(exit_program, "Error reading num_output_spring_forces (integer) in %s.", params_file);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"object"))
      {
#if CONTACT_DETECTION
         read_object(&fp);
#else
         sim_message(none, "Error reading \"object\" in %s.", params_file);
         sim_message(none, "   You must set CONTACT_DETECTION=1 in your project settings");
         sim_message(exit_program, "   in order to use contact detection.");
#endif
      }
      else if (STRINGS_ARE_EQUAL(buffer,"begin_group"))
      {
#if CONTACT_DETECTION
         read_object_group(&fp);
#else
         sim_message(none, "Error reading \"begin_group\" in %s.", params_file);
         sim_message(none, "   You must set CONTACT_DETECTION=1 in your project settings");
         sim_message(exit_program, "   in order to use contact detection.");
#endif
      }
      else if (STRINGS_ARE_EQUAL(buffer,"contact_pair"))
      {
#if CONTACT_DETECTION
         read_contact_pair(&fp);
#else
         sim_message(none, "Error reading \"contact_pair\" in %s.", params_file);
         sim_message(none, "   You must set CONTACT_DETECTION=1 in your project settings");
         sim_message(exit_program, "   in order to use contact detection.");
#endif
      }
#endif
      else
      {
         /* see if the name is a segment */
         for (i=0; i<sdm->num_body_segments; i++)
         {
            if (STRINGS_ARE_EQUAL(buffer,sdm->body_segment[i].name))
            {
               fscanf(fp,"%s", buffer2);
               if (STRINGS_ARE_EQUAL(buffer2,"mass"))
               {
                  if (fscanf(fp,"%lf", &mass) != 1)
                  {
                     sim_message(recover, "Error reading mass for %s in %s.", buffer, params_file);
                  }
                  else
                  {
                     sdmass(i-1,mass);
                     if (check_for_sderror("READ_PARAMETERS_FILE") == 19)
                     {
                        sim_message(recover, "READ_PARAMETERS_FILE: trying to set a non-? parameter.");
                        sim_message(none, "Mass of %s will remain at %lf.", buffer, sdm->body_segment[i].mass);
                     }
                     else
                        sdm->body_segment[i].mass = mass;
                  }
                  break;
               }
               else if (STRINGS_ARE_EQUAL(buffer2,"inertia"))
               {
                  if (fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf", &inertia[0][0],
                     &inertia[0][1], &inertia[0][2], &inertia[1][0], &inertia[1][1],
                     &inertia[1][2], &inertia[2][0], &inertia[2][1], &inertia[2][2]) != 9)
                  {
                     sim_message(recover, "Error reading 3x3 inertia tensor for %s in %s.", buffer, params_file);
                  }
                  else
                  {
                     sdiner(i-1,inertia);
                     if (check_for_sderror("READ_PARAMETERS_FILE") == 19)
                     {
                        sim_message(recover, "READ_PARAMETERS_FILE: trying to set a non-? parameter.");
                        sim_message(none, "Inertia of %s will remain at:", buffer);
                        print_3x3matrix(sdm->body_segment[i].inertia,NULL,stderr);
                     }
                     else
                     {
                        for (j=0; j<3; j++)
                           for (k=0; k<3; k++)
                              sdm->body_segment[i].inertia[j][k] = inertia[j][k];
                     }
                  }
                  break;
               }
               else
               {
                  sim_message(recover, "Unknown string (%s) found after segment name %s in %s.",
                     buffer, buffer2, params_file);
               }
            }
         }
         /* if it's not a segment, see if it is a Q */
         if (i == sdm->num_body_segments)
         {
            for (i=0; i<sdm->nq; i++)
            {
               if (STRINGS_ARE_EQUAL(buffer,sdm->q[i].name))
               {
                  if (fscanf(fp,"%lf %lf", &sdm->q[i].initial_value, &sdm->q[i].initial_velocity) != 2)
                     sim_message(recover, "Error reading initial value and velocity for %s in %s.", buffer, params_file);
                     break;
               }
            }

            /* If it's not a Q, see if it's a muscle name. */
            if (i == sdm->nq)
            {
               for (i = 0; i < sdm->num_muscles; i++)
               {
                  if (STRINGS_ARE_EQUAL(buffer, sdm->muscles[i].name))
                  {
                     char* buffer_ptr;
                     double value = 0.0;
                     ReturnCode rc;
                     dpMuscleStruct* ms = &sdm->muscles[i];

                     read_line(&fp, buffer);

                     /* Read as many doubles as you can from the line, storing them in
                      * the muscle's stateParams array. You don't know how many there should
                      * be because this depends on the particular muscle model.
                      */
                     for (buffer_ptr = buffer; NOT_EQUAL_WITHIN_ERROR(value, ERROR_DOUBLE); )
                     {
                        buffer_ptr = parse_string(buffer_ptr, type_double, (void*)&value);
                        if (NOT_EQUAL_WITHIN_ERROR(value, ERROR_DOUBLE))
                        {
                           if (ms->numStateParams == 0)
                           {
                              ms->stateParams = (double*)simm_malloc(sizeof(double));
                           }
                           else
                           {
                              ms->stateParams = (double*)simm_realloc(ms->stateParams, (ms->numStateParams + 1) * sizeof(double), &rc);
                              if (rc == code_bad)
                                 sim_message(exit_program, "Ran out of memory while reading state vector for %s in %s.", buffer, params_file);
                           }
                           ms->stateParams[ms->numStateParams++] = value;
                        }
                     }
                     break;
                  }
               }
               if (i == sdm->num_muscles)
                  sim_message(exit_program, "Unknown string (%s) found in %s.", buffer, params_file);
            }
         }
      }
   }

   fclose(fp);

#if CONTACT_DETECTION
   check_object_info();
#endif
#ifndef INVERSE
   check_spring_info();
#endif
   return code_fine;
}


ReturnCode read_dllparameters_file(char params_file[], dpModelStruct* sdm)
{
   int i, j, k;
   double mass, inertia[3][3];
   char* filename;
   FILE* fp;   

   if ((fp = fopen(params_file,"r")) == NULL)
      return code_bad;

   while (1)
   {
      if (fscanf(fp, "%s", buffer) != 1)
         break;

      if (buffer[0] == '#')
      {
         read_line(&fp, buffer);
         continue;
      }

      /* See if the string is the name of a Q. */
      for (i = 0; i < sdm->nq; i++)
      {
         if (STRINGS_ARE_EQUAL(buffer, sdm->q[i].name))
         {
            if (fscanf(fp, "%lf %lf", &sdm->q[i].initial_value, &sdm->q[i].initial_velocity) != 2)
               sim_message(recover, "Error reading initial value and velocity for %s in %s.", buffer, params_file);
            break;
         }
      }

      /* If it's not a Q, see if it's a muscle name. */
      if (i == sdm->nq)
      {
         for (i = 0; i < sdm->num_muscles; i++)
         {
            if (STRINGS_ARE_EQUAL(buffer, sdm->muscles[i].name))
            {
               char* buffer_ptr;
               double value = 0.0;
               ReturnCode rc;
               dpMuscleStruct* ms = &sdm->muscles[i];

               read_line(&fp, buffer);

               /* Read as many doubles as you can from the line, storing them in
                * the muscle's stateParams array. You don't know how many there should
                * be because this depends on the particular muscle model.
                */
               for (buffer_ptr = buffer; NOT_EQUAL_WITHIN_ERROR(value, ERROR_DOUBLE); )
               {
                  buffer_ptr = parse_string(buffer_ptr, type_double, (void*)&value);
                  if (NOT_EQUAL_WITHIN_ERROR(value, ERROR_DOUBLE))
                  {
                     if (ms->numStateParams == 0)
                     {
                        ms->stateParams = (double*)simm_malloc(sizeof(double));
                     }
                     else
                     {
                        ms->stateParams = (double*)simm_realloc(ms->stateParams, (ms->numStateParams + 1) * sizeof(double), &rc);
                        if (rc == code_bad)
                           sim_message(exit_program, "Ran out of memory while reading state vector for %s in %s.", buffer, params_file);
                     }
                     ms->stateParams[ms->numStateParams++] = value;
                  }
               }
               break;
            }
         }
         if (i == sdm->num_muscles)
            sim_message(exit_program, "Unknown string (%s) found in %s.", buffer, params_file);
      }
   }

   fclose(fp);

   return code_fine;
}


/* PREPROCESS_FILE: this routine runs the a C preprocessor on the specified
 * input file, putting the output in the specified output file. It then
 * opens the processed file and returns a pointer to a FILE structure for it.
 * NOTE: the original (Unix) version of preprocess_file() for the pipeline
 * called the ANSI system() routine to execute the C preprocessor.
 * Unfortunately, not all Win32 compilers support system(), nor do they all
 * provide command-line compilers.  So we avoid the problem by call a
 * C preprocessor linked directly into our executable (acpp.lib).
 */

static void acpp(char in_file[], const char out_file[], char option_string[])

{

   int argc = 0;
   char** argv;
   char* remaining_options = option_string;
   char option[CHARBUFFER];

   /* room for 50 arguments should be enough */
   argv = (char**) malloc(50 * sizeof(char*));
   mstrcpy(&argv[argc++], "acpp");

   while (1)
   {
      remaining_options = parse_string(remaining_options, type_string, option);

      if (option == NULL || STRING_IS_NULL(option))
	 break;

      mstrcpy(&argv[argc++], option);
   }

   mstrcpy(&argv[argc++], (char*) in_file);
   mstrcpy(&argv[argc++], (char*) out_file);

   remove(out_file); /* required to work-around CodeWarrior bug */

   if (acpp_main(argc,argv) != 0)
      fprintf(stderr, "Error running acpp on input file: %s.", in_file);

   while (argc > 0)
      free(argv[--argc]);

   free(argv);

}


FILE* preprocess_file(char infile[], char outfile[])
{

   FILE* fp = fopen(infile,"r");

   if (fp == NULL)
      return (NULL);

   fclose(fp);

   acpp(infile, outfile, "-P");

#ifndef WIN32
   chmod(outfile,438);
#endif

   return fopen(outfile, "r");

}



/* READ_STRING: this routine reads a character string from a file. It skips over
 * any white space at the beginning, and returns EOF if it hit the end of
 * the file before completing the string.
 */

int read_string(FILE** fp, char str_buffer[])
{

   int c;

   /* Scan thru white space until you find the first character in the string */

   while (1)
   {
      c = getc(*fp);
      if (c == EOF)
         return (EOF);
      *str_buffer = c;
      if (CHAR_IS_NOT_WHITE_SPACE(*str_buffer))
         break;
   }
   str_buffer++;

   /* Now read characters until you find white space or EOF */

   while (1)
   {
      c = getc(*fp);
      if (c == EOF)
         return (EOF);
      *str_buffer = c;
      if (CHAR_IS_WHITE_SPACE(*str_buffer))
         break;
      str_buffer++;
   }

   /* Null-terminate the string */

   *str_buffer = STRING_TERMINATOR;

   /* You found a valid string without hitting EOF, so return a value that you
    * know will never equal EOF, no matter how EOF is defined.
    */

   return (EOF+1);

}



/* READ_LINE: reads a line (possibly empty) from a file */

int read_line(FILE** fp, char str_buffer[])
{

   int c;

   /* Read characters until you hit a carriage return or EOF */

   while (1)
   {
      c = getc(*fp);
      if (c == EOF)
         return (EOF);
      *str_buffer = c;
      if (*str_buffer == CARRIAGE_RETURN)
         break;
      str_buffer++;
   }

   /* Null-terminate the string */

   *str_buffer = STRING_TERMINATOR;

   /* You found a valid line without hitting EOF, so return a value that you
    * know will never equal EOF, no matter how EOF is defined.
    */

   return (EOF+1);

}



/* READ_NONEMPTY_LINE: Reads the first non-empty line from a file. */

int read_nonempty_line(FILE** fp, char str_buffer[])
{

   int c;

   /* Scan thru the white space until you find the first character */

   while (1)
   {
      c = getc(*fp);
      if (c == EOF)
         return (EOF);
      *str_buffer = c;
      if (*str_buffer != SPACE && *str_buffer != TAB)
         break;
   }
   str_buffer++;

   /* Now read characters until you find a carriage return or EOF */

   while (1)
   {
      c = getc(*fp);
      if (c == EOF)
         return (EOF);
      *str_buffer = c;
      if (*str_buffer == CARRIAGE_RETURN)
         break;
      str_buffer++;
   }

   *str_buffer = STRING_TERMINATOR;

   /* You found a valid line without hitting EOF, so return a value that you
    * know will never equal EOF, no matter how EOF is defined.
    */

   return (EOF+1);

}


/* READ_TIL_TOKENS: Read characters from 'file' into 'buf' until one of the
 * characters specified in 'delimiters' is encountered.  Put the delimiting
 * character back into 'file'.
 */

int read_til_tokens(FILE** file, char buf[], const char delimiters[])
{
   char* p = buf;

   while (1)
   {
      char c = fgetc(*file);

      if (feof(*file) || ferror(*file))
         break;
      else
      {
         if (strchr(delimiters, c))
         {
            ungetc(c, *file);
            break;
         }
         else
            *p++ = c;
      }
   }
   *p = '\0';

   /* remove trailing whitespace if necessary */
   while (p > buf && isspace(p[-1]))
       *(--p) = '\0';

   /* Return 1 if the string is not empty. */
   if (p > buf)
      return 1;
   else
      return 0;
}


/* CLEAN_STRING: clears leading and trailing white space from a string */

char* clean_string(char buf[])
{
   char* ptr;

   if (strlen(buf) < 1)
      return NULL;

   /* Remove trailing white space */
   ptr = &buf[strlen(buf)-1];
   while (CHAR_IS_WHITE_SPACE(*ptr))
      ptr--;
   *(ptr+1) = STRING_TERMINATOR;

   /* Remove leading white space */
   ptr = buf;
   while (CHAR_IS_WHITE_SPACE(*ptr))
      ptr++;

   return ptr;
}


/* READ_DOUBLE_ARRAY: this routine reads an array of pairs-of-doubles
 * (e.g. "(2.30, -0.05)"), as in the definition of a function. It keeps
 * reading until it encounters the ending string (e.g. "endfunction")
 * which is passed in. This routine is not trivial because it allows
 * spaces to be placed liberally in the string that it extracts the
 * doubles from (e.g. "( 2.30 , -0.05 )").
 */

ReturnCode read_double_array(FILE **fp, char ending[], char name[],
			                    dpSplineFunction* func)
{
   int new_size;

   func->numpoints = 0;

   while (1)
   {
      if (read_string(fp,buffer) == EOF)
      {
         sim_message(abort_action, "Unexpected EOF reading function %s.", name);
         return code_bad;
      }

      if (STRINGS_ARE_EQUAL(buffer,ending))
         break;

      /* If the string just read is not the ending string (e.g. "endfunction"),
       * then it must be part or all of an x-y pair "(x,y)". It cannot be more
       * than one x-y pair because there must be a space between each x-y pair.
       * Since there can be spaces within an x-y pair, you now want to continue
       * reading strings from the file until you encounter a closing parenthesis.
       */

      /* Before parsing this next string, first make sure that there is enough
       * space in the function structure for the next x-y pair.
       */

      if (func->numpoints == func->coefficient_array_size)
      {
         new_size = func->coefficient_array_size + SPLINE_ARRAY_INCREMENT;
         if (realloc_function(func,new_size) == code_bad)
            return (code_bad);
      }

      while (1)
      {
         if (string_contains_closing_paren(buffer) == dpYes)
            break;

         if (read_string(fp,&buffer[strlen(buffer)]) == EOF)
         {
            sim_message(abort_action, "Unexpected EOF reading function %s.", name);
            return code_bad;
         }
      }

      if (get_xypair_from_string(buffer,&func->x[func->numpoints],
         &func->y[func->numpoints]) == code_bad)
      {
         sim_message(abort_action, "Error reading x-y pair in function %s.", name);
         return code_bad;
      }
      
      (func->numpoints)++;
   }

   if (func->numpoints < 2)
   {
      sim_message(abort_action, "Function %s contains fewer than 2 points.", name);
      return code_bad;
   }

   return code_fine;
}



/* STRING_CONTAINS_CLOSING_PAREN: this routine scans a string to see if
 * it contains a closing parenthesis.
 */

static dpBoolean string_contains_closing_paren(char str_buffer[])
{

   while (*str_buffer != STRING_TERMINATOR)
   {
      if (*(str_buffer++) == ')')
         return dpYes;
   }

   return dpNo;

}



/* GET_XYPAIR_FROM_STRING: this routine parses a string to extract a pair
 * of doubles from it. The string should be of the form: "(x, y)".
 */

ReturnCode get_xypair_from_string(char str_buffer[], double* x, double* y)
{

   char junk;
   char* buffer_ptr;

   *x = *y = ERROR_DOUBLE;

   buffer_ptr = parse_string(str_buffer,type_char,(void*)&junk); /* open paren */
   buffer_ptr = parse_string(buffer_ptr,type_double,(void*)x);   /* x coord */
   buffer_ptr = parse_string(buffer_ptr,type_char,(void*)&junk); /* comma */
   buffer_ptr = parse_string(buffer_ptr,type_double,(void*)y);   /* y coord */
   buffer_ptr = parse_string(buffer_ptr,type_char,(void*)&junk); /* close paren*/

   if (*x == ERROR_DOUBLE || *y == ERROR_DOUBLE)
      return (code_bad);

   return (code_fine);

}



/* PARSE_STRING: this routine scans a string and extracts a variable from
 * it. The type of variable that it extracts is specified in one of the
 * arguments. It returns the unused portion of the string so that more
 * variables can be extracted from it.
 */

char* parse_string(char str_buffer[], VariableType var_type, void* dest_var)
{
   char tmp_buffer[CHARBUFFER], *buffer_ptr;

   if (str_buffer == NULL)
      return NULL;

   buffer_ptr = tmp_buffer;

   while (CHAR_IS_WHITE_SPACE(*str_buffer))
      str_buffer++;

   if (var_type == type_char)
   {
      *((char*)dest_var) = *str_buffer;
      return str_buffer + 1;
   }

   if (var_type == type_string)
   {
      if (STRING_IS_NULL(str_buffer))
         *((char*)dest_var) = STRING_TERMINATOR;
      else
         sscanf(str_buffer,"%s", (char*)dest_var);
      return str_buffer + strlen((char*)dest_var);
   }

   if (var_type == type_double)
   {
      *((double*)dest_var) = ERROR_DOUBLE;
      if (STRING_IS_NOT_NULL(str_buffer))
      {
         while (*str_buffer == '-' || *str_buffer == '.' || (*str_buffer >= '0' && *str_buffer <= '9'))
            *(buffer_ptr++) = *(str_buffer++);
         *buffer_ptr = STRING_TERMINATOR;
         if (sscanf(tmp_buffer,"%lf",(double*)dest_var) != 1)
            *((double*)dest_var) = ERROR_DOUBLE;
      }
      return str_buffer;
   }

   if (var_type == type_int)
   {
      *((int*)dest_var) = ERROR_INT;
      if (STRING_IS_NOT_NULL(str_buffer))
      {
         while (*str_buffer == '-' || (*str_buffer >= '0' && *str_buffer <= '9'))
            *(buffer_ptr++) = *(str_buffer++);
         *buffer_ptr = STRING_TERMINATOR;
         sscanf(tmp_buffer,"%d",(int*)dest_var);
      }
      return str_buffer;
   }

   sim_message(none, "Unknown variable type (%d) passed to parse_string().", (int)var_type);

   return str_buffer;
}



/* ENTER_SEGMENT: this routine takes the name of a body segment and enters it
 * into the model's array of segment names. It returns the index of the array
 * entry where the name is stored (minus 1 since SD/FAST body numbers start at -1).
 * It is used when reading muscle attachment points. When a segment name is read
 * from a muscle file, you want to find out which SD/FAST body segment number the
 * name corresponds to. If the name is not in the SDModel structure, it is an error
 * since all of the body segments have already been defined. Before checking the
 * name, remove any special characters from it since this has been done to the
 * array of valid segment names (because they have to compile as #defines).
 */

int enter_segment(dpModelStruct* sdm, char segment_name[])
{

   int i;

   /* Because body segment numbers in SD/FAST start at -1 (ground),
    * this routine returns segment array indices minus one, so that
    * it also numbers segments starting at -1.
    */

   convert_string(segment_name);

   for (i=0; i<sdm->num_body_segments; i++)
      if (STRINGS_ARE_EQUAL(segment_name,sdm->body_segment[i].name))
         return (i-1);

   return (-2);

}



/* ENTER_GENCOORD: this routine takes the name of a generalized coordinate
 * and enters it into the model's array of gencoord (q) names. It returns the
 * index of the array entry where the name is stored. It is used when reading
 * muscles which have wrapping points that are functions of a generalized
 * coordinate. If the gencoord name found in the muscle file (and passed into
 * this routine) is not in the SDModel structure, it is an error since all of
 * the model's gencoords have already been defined. Before checking the name,
 * remove any special characters from it since this has been done to the array
 * of valid gencoord names (because they have to compile as #defines).
 */

int enter_gencoord(dpModelStruct* sdm, char gencoord_name[])
{

   int i;

   convert_string(gencoord_name);

   for (i=0; i<sdm->nq; i++)
      if (STRINGS_ARE_EQUAL(gencoord_name,sdm->q[i].name))
         return (i);

   return (-1);

}



/* LOAD_KINETICS_DATA: this routine reads a file of kinetics data. This file can
 * contain positions, velocities, and accelerations of Qs (gencoords), as well as
 * external forces and torques applied to the body segments. Thus it can be used
 * in a forward or inverse simulation.
 */

ReturnCode load_kinetics_data(dpModelStruct* sdm, MotionData* data, char filename[])
{
   const char *suffix = get_suffix(filename);

   data->num_frames = data->current_frame = 0;
   data->num_elements = data->num_otherdata = 0;
   data->num_forces = data->num_torques = data->num_musc_excitations = 0;
   data->time_index = -1;
   data->range_start = data->range_end = data->step_size = 0.0;
   data->q_data = NULL;
   data->event_color[0] = 1.0;
   data->event_color[1] = 0.0;
   data->event_color[2] = 1.0;
   data->enforce_constraints = 1;

   if (suffix == NULL || STRINGS_ARE_EQUAL(suffix, "mot"))
   {
      return read_motion_file(sdm, data, filename);
   }
   else if (STRINGS_ARE_EQUAL(suffix, "ktx"))
   {
      mstrcpy(&data->name, "input_data");
      return read_kinetics_file(sdm, data, filename);
   }
   else
   {
      sim_message(none, "Unrecognized suffix on input file %s (must be .ktx or .mot).", filename);
      return code_bad;
   }
}


ReturnCode read_kinetics_file(dpModelStruct* sdm, MotionData* data, char filename[])
{
   int i, j, num_read, num_columns;
   dpSplineType splineType;
   double cutoffFrequency;
   dpBoolean read_frames = dpNo, read_elements = dpNo, read_otherdata = dpNo;

   if ((data->fp = preprocess_file(filename, get_temp_file_name(".kinetics"))) == NULL)

   {
      sim_message(none, "Unable to open kinetics file %s.", filename);
      return code_bad;
   }

   while (1)
   {
      if (read_string(&data->fp,buffer) == EOF)
      {
         sim_message(abort_action, "Premature EOF found in kinetics file.");
         return code_bad;
      }

      if (buffer[0] == '#')
      {
         read_nonempty_line(&data->fp,buffer);
         continue;
      }

      if (STRINGS_ARE_EQUAL(buffer,"frames") || STRINGS_ARE_EQUAL(buffer,"numframes"))
      {
         if (fscanf(data->fp,"%d", &data->num_frames) != 1)
         {
            sim_message(abort_action, "Error reading number of frames from kinetics file.");
            return code_bad;
         }
         else
            read_frames = dpYes;
      }
      else if (STRINGS_ARE_EQUAL(buffer,"elements") || STRINGS_ARE_EQUAL(buffer,"numelements"))
      {
         if (fscanf(data->fp,"%d", &data->num_elements) != 1)
         {
            sim_message(abort_action, "Error reading number of elements from kinetics file.");
            return code_bad;
         }
         else
            read_elements = dpYes;
      }
      else if (STRINGS_ARE_EQUAL(buffer,"otherdata"))
      {
         if (fscanf(data->fp,"%d", &data->num_otherdata) != 1)
         {
            sim_message(abort_action, "Error reading number of otherdata from kinetics file.");
            return code_bad;
         }
         else
            read_otherdata = dpYes;
      }
      else if (STRINGS_ARE_EQUAL(buffer, "enforce_constraints"))
      {
         if (read_string(&data->fp, buffer) == EOF)
         {
            sim_message(abort_action, "Error reading enforce_constraints from kinetics file (must be: yes/no/on/off/true/false).");
            return code_bad;
         }

         if (STRINGS_ARE_EQUAL(buffer, "no") || STRINGS_ARE_EQUAL(buffer, "off")
            || STRINGS_ARE_EQUAL(buffer, "false"))
            data->enforce_constraints = 0;
         else if (STRINGS_ARE_EQUAL(buffer, "yes") || STRINGS_ARE_EQUAL(buffer, "on")
            ||STRINGS_ARE_EQUAL(buffer, "true"))
            data->enforce_constraints = 1;
      }
      else
      {
         sim_message(recover, "Unrecognized string \"%s\" found in kinetics file.", buffer);
      }
      
      if (read_frames == dpYes && read_elements == dpYes && read_otherdata == dpYes)
         break;
   }

   data->elementnames = (char**)simm_calloc(data->num_elements, sizeof(char*));
   if (data->elementnames == NULL)
      return code_bad;

   for (num_read=0, i=0; i<data->num_elements; i++)
   {
      num_read += fscanf(data->fp,"%s", buffer);
      mstrcpy(&data->elementnames[i],buffer);
   }

   if (num_read < data->num_elements)
   {
      sim_message(abort_action, "Error reading names of data elements. Only %d of %d read.",
         num_read, data->num_elements);
      return code_bad;
   }

   for (num_columns = 0, i=0; i<data->num_elements; i++)
   {
      if (name_is_body_segment(data->elementnames[i], sdm, force_suffix, &splineType, &cutoffFrequency) != -2)
         num_columns += 6;
      else if (name_is_body_segment(data->elementnames[i], sdm, torque_suffix, &splineType, &cutoffFrequency) != -2)
         num_columns += 3;
      else
         num_columns++;
   }

   data->motiondata = (double**)simm_calloc(num_columns, sizeof(double*));
   if (data->motiondata == NULL)
   {
      return code_bad;
   }

   for (i=0; i<num_columns; i++)
   {
      data->motiondata[i] = (double*)simm_calloc(data->num_frames, sizeof(double));
      if (data->motiondata[i] == NULL)
      {
         return code_bad;
      }
   }

   for (i=0; i<data->num_frames; i++)
   {
      num_read = 0;
      for (j=0; j<num_columns; j++)
         num_read += fscanf(data->fp,"%lg", &data->motiondata[j][i]);
      if (num_read < num_columns)
      {
         data->num_frames = i;
         sim_message(recover, "Error reading kinetics file %s:\n  Only %d frames found.", filename, data->num_frames);
         break;
      }
   }

   (void)fclose(data->fp);
   (void)unlink(get_temp_file_name(".kinetics"));

   sim_message(none, "Read %d frames of data from kinetics file %s.", data->num_frames, filename);

   return verify_kinetics_data(sdm, data);
}


ReturnCode read_motion_file(dpModelStruct* sdm, MotionData* data, char filename[])
{
   int i, j, num_read;
   dpSplineType splineType;
   double cutoffFrequency;
   ReturnCode rc;

   if ((data->fp = preprocess_file(filename, get_temp_file_name(".motion"))) == NULL)
   {
      sim_message(none, "Unable to open motion file %s.", filename);
      return code_bad;
   }

   while (1)
   {
      if (read_string(&data->fp,buffer) == EOF)
      {
         sim_message(abort_action, "Premature EOF found in motion file.");
         return code_bad;
      }

      if (buffer[0] == '#')
      {
         read_nonempty_line(&data->fp,buffer);
         continue;
      }

      if (STRINGS_ARE_EQUAL(buffer, "endheader"))
         break;

      else if (STRINGS_ARE_EQUAL(buffer,"name"))
      {
         read_line(&data->fp, buffer);
         mstrcpy(&data->name, buffer);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"wrap"))
      {
      }
      else if (STRINGS_ARE_EQUAL(buffer, "enforce_loops"))
      {
         /* Ignore this command since loops are always enforced by SD/FAST. */
         read_string(&data->fp, buffer);
      }
      else if (STRINGS_ARE_EQUAL(buffer, "enforce_constraints"))
      {
         if (read_string(&data->fp, buffer) == EOF)
         {
            sim_message(abort_action, "Error reading enforce_constraints from motion file (must be: yes/no/on/off/true/false).");
            return code_bad;
         }

         if (STRINGS_ARE_EQUAL(buffer, "no") || STRINGS_ARE_EQUAL(buffer, "off")
            || STRINGS_ARE_EQUAL(buffer, "false"))
            data->enforce_constraints = 0;
         else if (STRINGS_ARE_EQUAL(buffer, "yes") || STRINGS_ARE_EQUAL(buffer, "on")
            ||STRINGS_ARE_EQUAL(buffer, "true"))
            data->enforce_constraints = 1;
      }
      else if (STRINGS_ARE_EQUAL(buffer,"datacolumns"))
      {
         if (fscanf(data->fp,"%d", &data->num_elements) != 1)
         {
            sim_message(abort_action, "Error reading number of data columns from motion file.");
            return code_bad;
         }
      }
      else if (STRINGS_ARE_EQUAL(buffer,"keys"))
      {
         read_line(&data->fp, buffer);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"datarows"))
      {
         if (fscanf(data->fp,"%d", &data->num_frames) != 1)
         {
            sim_message(abort_action, "Error reading number of frames from motion file.");
            return code_bad;
         }
      }
      else if (STRINGS_ARE_EQUAL(buffer,"range"))
      {
         fscanf(data->fp,"%*lg %*lg");
      }
      else if (STRINGS_ARE_EQUAL(buffer, "units"))
      {
         read_line(&data->fp, buffer);
      }
      else if (STRINGS_ARE_EQUAL(buffer,"cursor"))
      {
         fscanf(data->fp,"%*f %*f %*f");
      }
      else if (STRINGS_ARE_EQUAL(buffer,"event"))
      {
         if (data->event)
            data->event = (dpMotionEvent*)simm_realloc(data->event, (data->num_events + 1) * sizeof(dpMotionEvent), &rc);
         else
            data->event = (dpMotionEvent*)simm_malloc((data->num_events + 1) * sizeof(dpMotionEvent));

         if (!data->event)
         {
            sim_message(recover, "Unable to malloc space to hold motion event.");
         }
         else if (fscanf(data->fp, "%lg", &data->event[data->num_events].xCoord) != 1)
         {
            sim_message(recover, "Error reading event time in motion %s.", data->name);
         }
         else if (read_nonempty_line(&data->fp, buffer) == EOF)
         {
            sim_message(recover, "Error reading event name in motion %s.", data->name);
         }
         else
         {
            mstrcpy(&data->event[data->num_events].name, buffer);
            data->num_events++;
         }
      }
      else if (STRINGS_ARE_EQUAL(buffer,"event_color"))
      {
         if (fscanf(data->fp, "%f %f %f", &data->event_color[0],
             &data->event_color[1], &data->event_color[2]) != 3)
         {
            sim_message(none, "Error reading event_color for motion %s.", data->name);
         }
         else
         {
            /* Support for 'old style' colors (range: 0 to 255). If any of the
             * color components is greater than 1.0, assume that it's an old
             * style color definition.
             */
            if (data->event_color[0] > 1.0 || data->event_color[1] > 1.0 || data->event_color[2] > 1.0)
            {
               data->event_color[0] /= 255.0;
               data->event_color[1] /= 255.0;
               data->event_color[2] /= 255.0;
            }
            for (i = 0; i < 3; i++)
            {
               if (data->event_color[i] < 0.0)
                  data->event_color[i] = 0.0;
            }
         }
      }
      else if (STRINGS_ARE_EQUAL(buffer,"calc_derivatives"))
      {
         fscanf(data->fp,"%*lg");
      }
      else if (STRINGS_ARE_EQUAL(buffer,"accept_realtime_motion"))
      {
      }
      else if (STRINGS_ARE_EQUAL(buffer,"sliding_time_scale"))
      {
      }
      else
      {
         sim_message(recover, "Unrecognized string \"%s\" found in motion file.", buffer);
      }
   }

   data->elementnames = (char**)simm_calloc(data->num_elements, sizeof(char*));
   if (data->elementnames == NULL)
   {
      sim_message(exit_program, "Unable to allocate enough memory to read motion file.");
   }

   for (num_read=0, i=0; i<data->num_elements; i++)
   {
      num_read += fscanf(data->fp,"%s", buffer);
      mstrcpy(&data->elementnames[i],buffer);
   }

   if (num_read < data->num_elements)
   {
      sim_message(recover, "Error reading names of data columns. Only %d of %d read.", num_read, data->num_elements);
      return code_bad;
   }

   data->motiondata = (double**)simm_calloc(data->num_elements, sizeof(double*));
   if (data->motiondata == NULL)
   {
      sim_message(exit_program, "Unable to allocate enough memory to read motion file.");
   }

   for (i=0; i<data->num_elements; i++)
   {
      data->motiondata[i] = (double*)simm_calloc(data->num_frames, sizeof(double));
      if (data->motiondata[i] == NULL)
      {
         sim_message(exit_program, "Unable to allocate enough memory to read motion file.");
      }
   }

   for (i=0; i<data->num_frames; i++)
   {
      num_read = 0;
      for (j=0; j<data->num_elements; j++)
         num_read += fscanf(data->fp,"%lg", &data->motiondata[j][i]);
      if (num_read < data->num_elements)
      {
         data->num_frames = i;
         sim_message(recover, "Error reading motion file %s:\n  Only %d frames found.", filename, data->num_frames);
         break;
      }
   }

   (void)fclose(data->fp);
   (void)unlink(get_temp_file_name(".motion"));

   sim_message(none, "Read %d frames of data from motion file %s.", data->num_frames, filename);

   return verify_motion_data(sdm, data);
}


/* VERIFY_KINETICS_DATA: this routine checks the validity of the kinetics data.
 * It checks the column names in the file to make sure they match the model's
 * gencoords (for positions, velocities, and accelerations), and body segments
 * (for forces and torques). Then it stores the data appropriately in the
 * MotionData structure.
 */

static ReturnCode verify_kinetics_data(dpModelStruct* sdm, MotionData* data)
{

   int i, gc, seg, column, num_otherdata;
   dpSplineType splineType;
   double cutoffFrequency;
   ForceStruct* fs;
   TorqueStruct* ts;

   /* The size of these arrays is fixed at the number of gencoords in the model. */
   data->q_data = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));
   data->u_data = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));
   data->udot_data = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));
   data->q_torques = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));

   /* These arrays are initially allocated to their maximum possible size, and then
    * they are re-alloced later.
    */
   data->forces = (ForceStruct**)simm_calloc(data->num_elements, sizeof(ForceStruct*));
   data->torques = (TorqueStruct**)simm_calloc(data->num_elements, sizeof(TorqueStruct*));

   for (column = 0, num_otherdata = 0, i = 0; i<data->num_elements; i++)
   {
      splineType = dpStepFunction;

      if ((gc = name_is_gencoord(data->elementnames[i], sdm, NULL, &splineType, &cutoffFrequency)) != -1)
      {
         data->q_data[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->q_data[gc], data->motiondata[column], data->num_frames, splineType, cutoffFrequency);
         column++;
      }
      else if ((gc = name_is_gencoord(data->elementnames[i], sdm, velocity_suffix, &splineType, &cutoffFrequency)) != -1)
      {
         data->u_data[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->u_data[gc], data->motiondata[column], data->num_frames, splineType, cutoffFrequency);
         column++;
      }
      else if ((gc = name_is_gencoord(data->elementnames[i], sdm, acceleration_suffix, &splineType, &cutoffFrequency)) != -1)
      {
         data->udot_data[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->udot_data[gc], data->motiondata[column], data->num_frames, splineType, cutoffFrequency);
         column++;
      }
      else if ((gc = name_is_gencoord(data->elementnames[i], sdm, torque_suffix, &splineType, &cutoffFrequency)) != -1)
      {
         data->q_torques[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->q_torques[gc], data->motiondata[column], data->num_frames, splineType, cutoffFrequency);
         column++;
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, force_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         data->forces[data->num_forces] = (ForceStruct*)simm_malloc(sizeof(ForceStruct));
         fs = data->forces[data->num_forces++];
         fs->segment = seg;
         init_spline_func(&fs->appl_point[XX], data->motiondata[column], data->num_frames, splineType, cutoffFrequency);
         init_spline_func(&fs->appl_point[YY], data->motiondata[column+1], data->num_frames, splineType, cutoffFrequency);
         init_spline_func(&fs->appl_point[ZZ], data->motiondata[column+2], data->num_frames, splineType, cutoffFrequency);
         init_spline_func(&fs->force_vec[XX], data->motiondata[column+3], data->num_frames, splineType, cutoffFrequency);
         init_spline_func(&fs->force_vec[YY], data->motiondata[column+4], data->num_frames, splineType, cutoffFrequency);
         init_spline_func(&fs->force_vec[ZZ], data->motiondata[column+5], data->num_frames, splineType, cutoffFrequency);
         column += 6;
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, torque_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         data->torques[data->num_torques] = (TorqueStruct*)simm_malloc(sizeof(TorqueStruct));
         ts = data->torques[data->num_torques++];
         ts->segment = seg;
         init_spline_func(&ts->torque_vec[XX], data->motiondata[column], data->num_frames, splineType, cutoffFrequency);
         init_spline_func(&ts->torque_vec[YY], data->motiondata[column+1], data->num_frames, splineType, cutoffFrequency);
         init_spline_func(&ts->torque_vec[ZZ], data->motiondata[column+2], data->num_frames, splineType, cutoffFrequency);
         column += 3;
      }
      else if (STRINGS_ARE_EQUAL(data->elementnames[i], "time"))
      {
         data->time_index = i;
         column++;
      }
      else
      {
         num_otherdata++;
         column++;
      }
   }

   /* Realloc these arrays, now that their actual size is known. */
   data->forces = (ForceStruct**)realloc(data->forces, data->num_forces * sizeof(ForceStruct*));
   data->torques = (TorqueStruct**)realloc(data->torques, data->num_torques * sizeof(TorqueStruct*));

   if (setup_spline_structs(sdm, data) == code_bad)
      return code_bad;

   if (num_otherdata > 0)
   {
      sim_message(none, "  %d column%sof data in kinetics file %s classified as 'otherdata'", num_otherdata,
         num_otherdata > 1 ? "s " : " ", num_otherdata > 1 ? "were" : "was");
      sim_message(none, "  and will be ignored.");
   }

   sim_message(none, "Verified data in kinetics file.");

   return code_fine;
}


static void map_motion_force(dpModelStruct* sdm, MotionData* data, int segNum, FTcomponent comp,
                             dpSplineType splineType, double cutoffFrequency, int column)
{
   int i;
   ForceStruct *fs;

   /* Scan the force structs, looking for one which matches the segment, but which does not
    * have the 'comp' component defined. If you find one, use the column of data to initialize
    * that component. If you don't, make a new force struct and define that component.
    */
   for (i = 0; i < data->num_forces; i++)
   {
      if (comp <= POS_Z && data->forces[i]->segment == segNum &&
          data->forces[i]->appl_point[comp].defined == dpNo)
      {
         init_spline_func(&data->forces[i]->appl_point[comp], data->motiondata[column], data->num_frames,
                          splineType, cutoffFrequency);
         return;
      }
      else if (comp > POS_Z && data->forces[i]->segment == segNum &&
               data->forces[i]->force_vec[comp - 3].defined == dpNo)
      {
         init_spline_func(&data->forces[i]->force_vec[comp - 3], data->motiondata[column], data->num_frames,
                          splineType, cutoffFrequency);
         return;
      }
   }

   /* You didn't find a slot for this component, so start a new ForceStruct. */
   data->forces[data->num_forces] = (ForceStruct*)simm_malloc(sizeof(ForceStruct));
   fs = data->forces[data->num_forces++];
   fs->segment = segNum;
   for (i = 0; i < 3; i++)
   {
      fs->appl_point[i].defined = dpNo;
      fs->force_vec[i].defined = dpNo;
   }
   if (comp <= POS_Z)
      init_spline_func(&fs->appl_point[comp], data->motiondata[column], data->num_frames,
                       splineType, cutoffFrequency);
   else
      init_spline_func(&fs->force_vec[comp - 3], data->motiondata[column], data->num_frames,
                       splineType, cutoffFrequency);
}


static void map_motion_torque(dpModelStruct* sdm, MotionData* data, int segNum, FTcomponent comp,
                              dpSplineType splineType, double cutoffFrequency, int column)
{
   int i;
   TorqueStruct *ts;

   /* Scan the torque structs, looking for one which matches the segment, but which does not
    * have the 'comp' component defined. If you find one, use the column of data to initialize
    * that component. If you don't, make a new torque struct and define that component.
    */
   for (i = 0; i < data->num_torques; i++)
   {
      if (data->torques[i]->segment == segNum && data->torques[i]->torque_vec[comp].defined == dpNo)
      {
         init_spline_func(&data->torques[i]->torque_vec[comp], data->motiondata[column], data->num_frames,
                          splineType, cutoffFrequency);
         return;
      }
   }

   /* You didn't find a slot for this component, so start a new TorqueStruct. */
   data->torques[data->num_torques] = (TorqueStruct*)simm_malloc(sizeof(TorqueStruct));
   ts = data->torques[data->num_torques++];
   ts->segment = segNum;
   for (i = 0; i < 3; i++)
      ts->torque_vec[i].defined = dpNo;
   init_spline_func(&ts->torque_vec[comp], data->motiondata[column], data->num_frames,
                    splineType, cutoffFrequency);
}


/* MAP_MUSCLE_EXCITATION: this function takes a column of 
 */
static map_muscle_excitation(dpModelStruct* sdm, MotionData* data, int muscNum,
                             dpSplineType splineType, double cutoffFrequency, int column)
{
   int i;
   dpSplineFunction* sf;
   dpMuscleStruct* ms = &sdm->muscles[muscNum];

   /* Free the existing excitation data, if any. This would be the excitation
    * data specified in the muscle file.
    */
   if (ms->excitation)
   {
      free_function(ms->excitation);
      FREE_IFNOTNULL(ms->excitation);
   }

   /* Put this data in the next unused musc_excitation slot. */
   sf = data->musc_excitations[data->num_musc_excitations] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
   data->num_musc_excitations++;

   init_spline_func(sf, data->motiondata[column], data->num_frames, splineType, cutoffFrequency);

   /* Now point the muscle's excitation function to this one. */
   ms->excitation = sf;
}


/* VERIFY_MOTION_DATA: this routine checks the validity of the kinetics data.
 * It checks the column names in the file to make sure they match the model's
 * gencoords (for positions, velocities, and accelerations), body segments (for
 * forces and torques), and muscles (for excitations). Then it stores the data
 * appropriately in the MotionData structure.
 */

static ReturnCode verify_motion_data(dpModelStruct* sdm, MotionData* data)
{

   int i, gc, seg, musc, num_otherdata;
   dpSplineType splineType;
   double cutoffFrequency;
   ForceStruct* fs;
   TorqueStruct* ts;

   /* The size of these arrays is fixed at the number of gencoords in the model. */
   data->q_data = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));
   data->u_data = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));
   data->udot_data = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));
   data->q_torques = (dpSplineFunction**)simm_calloc(sdm->nq, sizeof(dpSplineFunction*));

   /* These arrays are initially allocated to their maximum possible size, and then
    * they are re-alloced later.
    */
   data->musc_excitations = (dpSplineFunction**)simm_calloc(sdm->num_muscles, sizeof(dpSplineFunction*));
   data->forces = (ForceStruct**)simm_calloc(data->num_elements, sizeof(ForceStruct*));
   data->torques = (TorqueStruct**)simm_calloc(data->num_elements, sizeof(TorqueStruct*));

   for (num_otherdata = 0, i = 0; i<data->num_elements; i++)
   {
      splineType = dpStepFunction;

      if ((gc = name_is_gencoord(data->elementnames[i], sdm, NULL, &splineType, &cutoffFrequency)) != -1)
      {
         data->q_data[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->q_data[gc], data->motiondata[i], data->num_frames, splineType, cutoffFrequency);
      }
      else if ((gc = name_is_gencoord(data->elementnames[i], sdm, velocity_suffix, &splineType, &cutoffFrequency)) != -1)
      {
         data->u_data[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->u_data[gc], data->motiondata[i], data->num_frames, splineType, cutoffFrequency);
      }
      else if ((gc = name_is_gencoord(data->elementnames[i], sdm, acceleration_suffix, &splineType, &cutoffFrequency)) != -1)
      {
         data->udot_data[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->udot_data[gc], data->motiondata[i], data->num_frames, splineType, cutoffFrequency);
      }
      else if ((gc = name_is_gencoord(data->elementnames[i], sdm, torque_suffix, &splineType, &cutoffFrequency)) != -1)
      {
         data->q_torques[gc] = (dpSplineFunction*)simm_malloc(sizeof(dpSplineFunction));
         init_spline_func(data->q_torques[gc], data->motiondata[i], data->num_frames, splineType, cutoffFrequency);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, px_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_force(sdm, data, seg, POS_X, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, py_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_force(sdm, data, seg, POS_Y, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, pz_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_force(sdm, data, seg, POS_Z, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, vx_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_force(sdm, data, seg, VEC_X, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, vy_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_force(sdm, data, seg, VEC_Y, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, vz_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_force(sdm, data, seg, VEC_Z, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, ax_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_torque(sdm, data, seg, POS_X, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, ay_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_torque(sdm, data, seg, POS_Y, splineType, cutoffFrequency, i);
      }
      else if ((seg = name_is_body_segment(data->elementnames[i], sdm, az_suffix, &splineType, &cutoffFrequency)) != -2)
      {
         map_motion_torque(sdm, data, seg, POS_Z, splineType, cutoffFrequency, i);
      }
      else if ((musc = name_is_muscle(data->elementnames[i], sdm, NULL, &splineType, &cutoffFrequency)) != -1)
      {
         map_muscle_excitation(sdm, data, musc, splineType, cutoffFrequency, i);
      }
      else if (STRINGS_ARE_EQUAL(data->elementnames[i], "time"))
      {
         data->time_index = i;
      }
      else
      {
         num_otherdata++;
      }
   }

   /* Realloc these arrays, now that their actual size is known. */
   data->forces = (ForceStruct**)realloc(data->forces, data->num_forces * sizeof(ForceStruct*));
   data->torques = (TorqueStruct**)realloc(data->torques, data->num_torques * sizeof(TorqueStruct*));
   data->musc_excitations = (dpSplineFunction**)realloc(data->musc_excitations,
                                                      data->num_musc_excitations * sizeof(dpSplineFunction*));

   if (setup_spline_structs(sdm, data) == code_bad)
      return code_bad;

   if (num_otherdata > 0)
   {
      sim_message(none, "  %d column%sof data in motion file %s classified as 'otherdata'", num_otherdata,
         num_otherdata > 1 ? "s " : " ", num_otherdata > 1 ? "were" : "was");
      sim_message(none, "  and will be ignored.");
   }

   sim_message(none, "Verified data in motion file.");

   return code_fine;
}


/* NAME_IS_GENCOORD: this routine checks to see if a string is the name
 * of one of the model's gencoords, with an optional suffix and also
 * possibly the extra suffix "_lin", "_spl", or "_gcv" (possibly followed a cutoff
 * frequency). It returns the index of the gencoord if there is a match.
 */

static int name_is_gencoord(char name[], dpModelStruct* sdm, char suffix[],
                            dpSplineType* splineType, double* cutoffFrequency)
{
   int i, len, lenQ, Qnum, index, maxLen;
   char* ptr;

   len = strlen(name);

   /* First check to see if the string begins with the name of a Q.
    * To handle models which have overlapping gencoord names, like
    * "q1" and "q10", check for a match with all gencoords, and take
    * the longest match.
    */
   for (i = 0, index = -1, maxLen = -1; i < sdm->nq; i++)
   {
      lenQ = strlen(sdm->q[i].name);
      if (len >= lenQ)
      {
         if (!strncmp(name, sdm->q[i].name, lenQ))
         {
            if (lenQ > maxLen)
            {
               index = i;
               maxLen = lenQ;
            }
         }
      }
   }

   if (index == -1)
      return -1;

   /* You've found a matching Q name, so move ptr past the Q name and
    * get ready to check the suffixes.
    */
   Qnum = index;
   ptr = &name[maxLen];
   len -= maxLen;

   /* If a suffix was passed in, check to see if the name ends in that suffix.
    * If it does, remove the suffix and continue on. If it does not, return -1
    * because the suffix is not optional.
    */
   if (suffix)
   {
      int suffix_len = strlen(suffix);

      if (len >= suffix_len)
      {
         if (!strncmp(ptr, suffix, suffix_len))
         {
            ptr += suffix_len;
            len -= suffix_len;
         }
         else
         {
            return -1;
         }
      }
      else
      {
         return -1;
      }
   }

   /* If splineType and cutoffFrequency are not NULL, check to see if the name ends in
    * natural_cubic_text or gcv_text (followed by an optional cutoff frequency). If it
    * does, set *splineType to the appropriate type. If no spline label is found, set
    * the type to step_func.
    */
   if (splineType && cutoffFrequency)
   {
      int matched_spl = 0, matched_lin = 0;
		int lin_len = strlen(linear_text);
      int spl_len = strlen(natural_cubic_text);
      int gcv_len = strlen(gcv_text);

      *splineType = dpStepFunction;
      *cutoffFrequency = -1.0; // by default there is no smoothing

		if (len >= lin_len)
		{
         if (!strncmp(ptr, linear_text, lin_len))
         {
            *splineType = dpLinear;
            ptr += lin_len;
            len -= lin_len;
            matched_lin = 1;
         }
		}

      if (!matched_lin && len >= spl_len)
      {
         if (!strncmp(ptr, natural_cubic_text, spl_len))
         {
            *splineType = dpNaturalCubic;
            ptr += spl_len;
            len -= spl_len;
            matched_spl = 1;
         }
      }

      if (!matched_lin && !matched_spl && len >= gcv_len)
      {
         if (!strncmp(ptr, gcv_text, gcv_len))
         {
            ptr += gcv_len;
            len -= gcv_len;
            *splineType = dpGCVSpline;
            if (len > 0)
            {
               char* intPtr = buffer;

               /* Move over the underscore and look for an integer. */
               if (*(ptr++) != '_')
               {
                  return -1;
               }
               else
               {
                  len--; /* for the underscore character */
                  while (*ptr >= '0' && *ptr <= '9')
                  {
                     *(intPtr++) = *(ptr++);
                     len--;
                  }
                  *intPtr = STRING_TERMINATOR;
                  *cutoffFrequency = atof(buffer);
               }
            }
         }
      }
   }

   /* If there are extra characters after the suffixes, return an error. */
   if (len > 0)
      return -1;

   return Qnum;
}


/* NAME_IS_BODY_SEGMENT: this routine checks to see if a string is the name
 * of one of the model's body segments, with an optional suffix and also possibly
 * the extra suffix "_spl" or "_gcv" (possibly followed by a cutoff frequency).
 * Since the C version of SD/FAST uses -1 as the number of the ground segment,
 * -2 means there was no match.
 */

static int name_is_body_segment(char name[], dpModelStruct* sdm, char suffix[],
                                dpSplineType* splineType, double* cutoffFrequency)
{
   int i, len, lenS, Snum, index, maxLen;
   char* ptr;

   len = strlen(name);

   /* First check to see if the string begins with the name of a body segment.
    * To handle models which have overlapping segment names, like
    * "body1" and "body10", check for a match with all segments, and take
    * the longest match.
    */
   for (i = 0, index = -1, maxLen = -1; i < sdm->num_body_segments; i++)
   {
      lenS = strlen(sdm->body_segment[i].name);
      if (len >= lenS)
      {
         if (!strncmp(name, sdm->body_segment[i].name, lenS))
         {
            if (lenS > maxLen)
            {
               index = i;
               maxLen = lenS;
            }
         }
      }
   }

   if (index == -1)
      return -2;

   /* You've found a matching segment name, so move ptr past the segment name and
    * get ready to check the suffixes.
    */
   Snum = index - 1;
   ptr = &name[maxLen];
   len -= maxLen;

   /* If a suffix was passed in, check to see if the name ends in that suffix.
    * If it does, remove the suffix and continue on. If it does not, return -2
    * because the suffix is not optional.
    */
   if (suffix)
   {
      int suffix_len = strlen(suffix);

      if (len >= suffix_len)
      {
         if (!strncmp(ptr, suffix, suffix_len))
         {
            ptr += suffix_len;
            len -= suffix_len;
         }
         else
         {
            return -2;
         }
      }
      else
      {
         return -2;
      }
   }

   /* If splineType and cutoffFrequency are not NULL, check to see if the name ends in
    * natural_cubic_text or gcv_text (followed by an optional cutoff frequency). If it
    * does, set *splineType to the appropriate type. If no spline label is found, set
    * the type to step_func.
    */
   if (splineType && cutoffFrequency)
   {
      int matched_spl = 0, matched_lin = 0;
		int lin_len = strlen(linear_text);
      int spl_len = strlen(natural_cubic_text);
      int gcv_len = strlen(gcv_text);

      *splineType = dpStepFunction;
      *cutoffFrequency = -1.0; // by default there is no smoothing

      if (len >= lin_len)
      {
         if (!strncmp(ptr, linear_text, lin_len))
         {
            *splineType = dpLinear;
            ptr += lin_len;
            len -= lin_len;
            matched_lin = 1;
         }
      }

      if (!matched_lin && len >= spl_len)
      {
         if (!strncmp(ptr, natural_cubic_text, spl_len))
         {
            *splineType = dpNaturalCubic;
            ptr += spl_len;
            len -= spl_len;
            matched_spl = 1;
         }
      }

      if (!matched_lin && !matched_spl && len >= gcv_len)
      {
         if (!strncmp(ptr, gcv_text, gcv_len))
         {
            ptr += gcv_len;
            len -= gcv_len;
            *splineType = dpGCVSpline;
            if (len > 0)
            {
               char* intPtr = buffer;

               /* Move over the underscore and look for an integer. */
               if (*(ptr++) != '_')
               {
                  return -2;
               }
               else
               {
                  len--; /* for the underscore character */
                  while (*ptr >= '0' && *ptr <= '9')
                  {
                     *(intPtr++) = *(ptr++);
                     len--;
                  }
                  *intPtr = STRING_TERMINATOR;
                  *cutoffFrequency = atof(buffer);
               }
            }
         }
      }
   }

   /* If there are extra characters after the suffixes, return an error. */
   if (len > 0)
      return -2;

   return Snum;
}


/* NAME_IS_MUSCLE: this routine checks to see if a string is the name
 * of one of the model's muscles, with an optional suffix and also
 * possibly the extra suffix "_spl" or "_gcv" (possibly followed a cutoff
 * frequency). It returns the index of the muscle if there is a match.
 */

static int name_is_muscle(char name[], dpModelStruct* sdm, char suffix[],
                          dpSplineType* splineType, double* cutoffFrequency)
{
   int i, len, lenM, Mnum, index, maxLen;
   char* ptr;

   len = strlen(name);

   /* First check to see if the string begins with the name of a muscle.
    * To handle models which have overlapping muscle names, like
    * "trap1" and "trap10", check for a match with all muscles, and take
    * the longest match.
    */
   for (i = 0, index = -1, maxLen = -1; i < sdm->num_muscles; i++)
   {
      lenM = strlen(sdm->muscles[i].name);
      if (len >= lenM)
      {
         if (!strncmp(name, sdm->muscles[i].name, lenM))
         {
            if (lenM > maxLen)
            {
               index = i;
               maxLen = lenM;
            }
         }
      }
   }

   if (index == -1)
      return -1;

   /* You've found a matching muscle name, so move ptr past the name and
    * get ready to check the suffixes.
    */
   Mnum = index;
   ptr = &name[maxLen];
   len -= maxLen;

   /* If a suffix was passed in, check to see if the name ends in that suffix.
    * If it does, remove the suffix and continue on. If it does not, return -1
    * because the suffix is not optional.
    */
   if (suffix)
   {
      int suffix_len = strlen(suffix);

      if (len >= suffix_len)
      {
         if (!strncmp(ptr, suffix, suffix_len))
         {
            ptr += suffix_len;
            len -= suffix_len;
         }
         else
         {
            return -1;
         }
      }
      else
      {
         return -1;
      }
   }

   /* If splineType and cutoffFrequency are not NULL, check to see if the name ends in
    * natural_cubic_text or gcv_text (followed by an optional cutoff frequency). If it
    * does, set *splineType to the appropriate type. If no spline label is found, set
    * the type to step_func.
    */
   if (splineType && cutoffFrequency)
   {
      int matched_spl = 0, matched_lin = 0;
		int lin_len = strlen(linear_text);
      int spl_len = strlen(natural_cubic_text);
      int gcv_len = strlen(gcv_text);

      *splineType = dpStepFunction;
      *cutoffFrequency = -1.0; // by default there is no smoothing

      if (len >= lin_len)
      {
         if (!strncmp(ptr, linear_text, lin_len))
         {
            *splineType = dpLinear;
            ptr += lin_len;
            len -= lin_len;
            matched_lin = 1;
         }
      }

      if (!matched_lin && len >= spl_len)
      {
         if (!strncmp(ptr, natural_cubic_text, spl_len))
         {
            *splineType = dpNaturalCubic;
            ptr += spl_len;
            len -= spl_len;
            matched_spl = 1;
         }
      }

      if (!matched_lin && !matched_spl && len >= gcv_len)
      {
         if (!strncmp(ptr, gcv_text, gcv_len))
         {
            ptr += gcv_len;
            len -= gcv_len;
            *splineType = dpGCVSpline;
            if (len > 0)
            {
               char* intPtr = buffer;

               /* Move over the underscore and look for an integer. */
               if (*(ptr++) != '_')
               {
                  return -1;
               }
               else
               {
                  len--; /* for the underscore character */
                  while (*ptr >= '0' && *ptr <= '9')
                  {
                     *(intPtr++) = *(ptr++);
                     len--;
                  }
                  *intPtr = STRING_TERMINATOR;
                  *cutoffFrequency = atof(buffer);
               }
            }
         }
      }
   }

   /* If there are extra characters after the suffixes, return an error. */
   if (len > 0)
      return -1;

   return Mnum;
}


/* STRING_HAS_SUFFIX: this function checks if str1 ends in suffix. */

static dpBoolean string_has_suffix(char str1[], char suffix[])
{

   int len, suffix_len;

   len = strlen(str1);
   suffix_len = strlen(suffix);

   if (len >= suffix_len)
   {
      if (strncmp(&str1[len - suffix_len], suffix, suffix_len) == 0)
         return dpYes;
   }

   return dpNo;
}



/* SIMM_MALLOC: this is a wrapper routine for malloc. It checks the size
 * you want to malloc, then calls malloc. If there is an error, it prints
 * an error message then returns NULL.
 */

void* simm_malloc(unsigned mem_size)
{
   void* ptr;

   /* To make sure you don't try to malloc 0 bytes (which is a problem
    * with some compilers because malloc returns NULL when you try it).
    * This is not the most elegant solution, but it works in the case
    * in which simm_malloc() is accidentally called with size 0.
    */
   if (mem_size <= 0)
      mem_size = sizeof(int);

   ptr = malloc(mem_size);

   if (ptr == NULL)
      sim_message(exit_program, "Ran out of memory. Unable to malloc %d bytes.", (int)mem_size);

   return ptr;
}



/* SIMM_CALLOC: this is a wrapper routine for calloc. It checks the size
 * you want to calloc, then calls calloc. If there is an error, it prints
 * an error message then returns NULL.
 */

void* simm_calloc(unsigned num_elements, unsigned elem_size)
{
   void* ptr;

   /* To make sure you don't try to malloc 0 bytes (which is a problem
    * with some compilers because malloc returns NULL when you try it).
    * This is not the most elegant solution, but it works in the case
    * in which simm_calloc() is accidentally called with size or num_elements 0.
    */
   if (num_elements*elem_size <= 0)
   {
      num_elements = 1;
      elem_size = sizeof(int);
   }

   ptr = calloc(num_elements,elem_size);

   if (ptr == NULL)
      sim_message(exit_program, "Ran out of memory. Unable to calloc %d bytes.", (int)(num_elements*elem_size));

   return ptr;
}



/* SIMM_REALLOC: this is a wrapper routine for realloc. It checks the size
 * you want to realloc to, then calls realloc. If there is an error, it prints
 * an error message then returns NULL.
 */

void* simm_realloc(void* ptr, unsigned mem_size, ReturnCode* rc)
{
   void* new_ptr;

   /* To make sure you don't try to malloc 0 bytes (which is a problem
    * with some compilers because malloc returns NULL when you try it).
    * This is not the most elegant solution, but it works in the case
    * in which simm_calloc() is accidentally called with size 0.
    */
   if (mem_size <= 0)
      mem_size = sizeof(int);

   new_ptr = realloc(ptr,mem_size);

   if (new_ptr == NULL)
   {
      sim_message(none, "Ran out of memory. Unable to realloc %d bytes.", (int)mem_size);
      *rc = code_bad;
      return ptr;
   }

   *rc = code_fine;
   return new_ptr;
}



/* CONVERT_STRING: this routine scans a string and converts all special
 * characters into underscores. A special character is any character
 * other than a letter or number. The resulting string is one token,
 * and can therefore be used as a variable name in SIMM-written C code.
 */

void convert_string(char str[])
{

   int i, len;

   len = strlen(str);

   for (i=0; i<len; i++)
   {
      if (str[i] >= 97 && str[i] <= 122)  /* lowercase letters */
         continue;
      if (str[i] >= 65 && str[i] <= 90)   /* uppercase letters */
         continue;
      if (str[i] >= 48 && str[i] <= 57)   /* numbers */
         continue;
      str[i] = '_';
   }

}


FILE* simm_fopen(const char* name, const char* mode)
{
#ifdef WIN32
   if (mode && mode[0] == 'w')
      remove(name);
#endif
   
   return fopen(name, mode);
}


#ifdef WIN32
   #include "windows.h"
#endif

char* get_temp_file_name(const char* baseFileName)
{

   static char sTempFileNameBuffer[512];

#ifdef WIN32
   static char sTempFilePath[256];
   static int  sTempFilePathInited = 0;

   if ( ! sTempFilePathInited)
   {
      GetTempPath(sizeof(sTempFilePath), sTempFilePath);
      sTempFilePathInited = 1;
   }

   if (baseFileName && baseFileName[0] == '.' && baseFileName[1] != '\0')
      baseFileName++;

#else
   static char sTempFilePath[] = "/tmp/";
#endif

   strcpy(sTempFileNameBuffer, sTempFilePath);

   if (baseFileName)
      strcat(sTempFileNameBuffer, baseFileName);

   return sTempFileNameBuffer;

}

dpBoolean is_absolute_path(char *path)
{
   if ((path[1] == ':') && (path[2] == DIR_SEP_CHAR))
      return dpYes;
   return dpNo;
}

/* Read a spring element from the parameters file and store it in an
 * array in the model struct */
static ReturnCode read_spring(FILE** fp)
{
   int segnum, index = 0;
   int num_params = 7;
   double pt[3]; 
   double friction, param_a, param_b, param_c, param_d, param_e, param_f;
   ReturnCode rc = code_fine;

   /* read segment name and get SD/FAST index */
   if (fscanf(*fp, "%s", buffer) != 1)
   {
      sim_message(exit_program, "Error reading segment name for spring.");
      return code_bad;
   }
   segnum = enter_segment(sdm,buffer);

   /* check that segment is valid */
	if (segnum  == -2)
		sim_message(exit_program, "Unknown segment name (%s) in spring definition.", buffer);

   /* read the coordinates of the spring attachement point
    * points are defined from segment origin */
   if (fscanf(*fp, "%lf %lf %lf", &pt[0], &pt[1], &pt[2]) != 3)
   {
      sim_message(exit_program, "Error reading spring points.");
      return code_bad;
   }

   /* read name of spring floor (plane) spring is attached to */
   if (fscanf(*fp, "%s ", buffer) != 1)
   {
      sim_message(exit_program, "Error reading spring floor name for spring.");
      return code_bad;
   }

   /* read spring parameters - friction and 6 other parameters */
   if (fscanf(*fp, "%lf %lf %lf %lf %lf %lf %lf", &friction, &param_a,
      &param_b, &param_c, &param_d, &param_e, &param_f) != num_params)
   {
      sim_message(exit_program, "Error reading parameters for spring %d.", sdm->num_springs + 1);
      return code_bad;
   }

	/* If you make it to here, then the spring was successfully read
	 * and the segment name matched one in the model, so add the spring to
	 * the list.  Reallocate space if the array is already full.
	 */
   if (sdm->spring_array_size == 0)
      sdm->spring_array_size += ARRAY_INCREMENT;
   if (sdm->num_springs == 0)
   {
		sdm->spring = (dpSpringStruct*)simm_malloc(sdm->spring_array_size *
         sizeof(dpSpringStruct));
   }
	else if (sdm->num_springs == sdm->spring_array_size)
   {
      sdm->spring_array_size += ARRAY_INCREMENT;
		sdm->spring = (dpSpringStruct *)simm_realloc(sdm->spring,
				(sdm->spring_array_size)*sizeof(dpSpringStruct), &rc);
      if (rc == code_bad)
         return code_bad;
   }

   /* point read in is with respect to SIMM origin, store it with
    * respect to body mass center */
   index = sdm->num_springs;
   sdvsub(pt, sdm->body_segment[segnum + 1].mass_center, sdm->spring[index].point);
   mstrcpy(&sdm->spring[index].floor_name, buffer);
   sdm->spring[index].segment = segnum;
 	sdm->spring[index].friction = friction;
 	sdm->spring[index].param_a = param_a;
 	sdm->spring[index].param_b = param_b;
 	sdm->spring[index].param_c = param_c;
 	sdm->spring[index].param_d = param_d;
 	sdm->spring[index].param_e = param_e;
 	sdm->spring[index].param_f = param_f;
   sdm->spring[index].force[0] = 0.0;
   sdm->spring[index].force[1] = 0.0;
   sdm->spring[index].force[2] = 0.0;

   sdm->num_springs++;
   return code_fine;

}

/* read a spring floor element from the parameters file and store it in
 * the array in the model struct */
static ReturnCode read_spring_floor(FILE** fp)
{
   int segnum;
   ReturnCode rc;
   dpPolyhedronStruct ph;
   char floor_name[CHARBUFFER], filename[CHARBUFFER], seg_name[CHARBUFFER];

   /* read floor name, file name, and segment name */
	if (fscanf(*fp,"%s %s %s", floor_name, filename, seg_name) != 3)
		sim_message(exit_program, "Error reading spring_floor definition.");

   /* check that the floor is attached to a valid segment */
   strcpy(buffer, seg_name);
   segnum = enter_segment(sdm, buffer);
	if (segnum == -2)
		sim_message(exit_program, "Unknown segment name (%s) in spring_floor definition.", seg_name);

   /* read the bone file */
   ph.body_segment = segnum;
	if (read_polyhedron(&ph, filename) == code_bad)
		sim_message(exit_program, "Could not read spring_floor.");

   mstrcpy(&ph.name, floor_name);
   
	/* If you make it to here, then the polyhedron was successfully loaded,
	 * and the segment name matched one in the model, so add the floor to
	 * the list, and store the polyhedron.  Reallocate space for the array
    * if it is already full.
	 */
   if (sdm->spring_floor_array_size == 0)
      sdm->spring_floor_array_size += ARRAY_INCREMENT;

   if (sdm->num_spring_floors == 0)
   {
		sdm->spring_floor = (dpSpringFloor*)simm_malloc(sdm->spring_floor_array_size *
         sizeof(dpSpringFloor));
   }
	else if (sdm->num_spring_floors == sdm->spring_floor_array_size)
   {
      sdm->spring_floor_array_size += ARRAY_INCREMENT;
		sdm->spring_floor = (dpSpringFloor*)simm_realloc(sdm->spring_floor,
				(sdm->spring_floor_array_size) * sizeof(dpSpringFloor), &rc);
      if (rc == code_bad)
      {
         sim_message(abort_action, "Ran out of memory. Unable to create spring floor.");
         return code_bad;
      }
   }

   /* now that you have allocated space for the floor, fill in the info */
   mstrcpy(&sdm->spring_floor[sdm->num_spring_floors].name, floor_name);
   sdm->spring_floor[sdm->num_spring_floors].segment = segnum;
   sdm->spring_floor[sdm->num_spring_floors].ph = 
      (dpPolyhedronStruct*)simm_malloc(sizeof(dpPolyhedronStruct));
   copy_polyhedron(&ph, sdm->spring_floor[sdm->num_spring_floors].ph);

   sdm->num_spring_floors++;

   return code_fine;
}


/* read a force matte element from the parameters file and store it in
 * the array in the model struct */
static ReturnCode read_force_matte(FILE** fp)
{
   int segnum, count;
   ReturnCode rc;
   dpPolyhedronStruct ph;
   char *clean_name, matte_name[CHARBUFFER], filename[CHARBUFFER], seg_name[CHARBUFFER];

	/* Read the three elements of a force matte definition. There must be
	 * a tab after the filename because the name can contain spaces.
	 */
   count = fscanf(*fp, "%s", matte_name);
   count += read_til_tokens(fp, filename, "\t\r\n");
   clean_name = clean_string(filename);
   read_line(fp, buffer);
   count += sscanf(buffer, "%s", seg_name);

	if (count != 3)
		sim_message(exit_program, "Error reading force_matte definition (make sure a tab follows the filename).");

   /* check that the matte is attached to a valid segment */
   strcpy(buffer, seg_name);
   segnum = enter_segment(sdm, buffer);
	if (segnum == -2)
		sim_message(exit_program, "Unknown segment name (%s) in force_matte definition.", seg_name);

   /* read the bone file */
   ph.body_segment = segnum;
	if (read_polyhedron(&ph, clean_name) == code_bad)
		sim_message(exit_program, "Could not read force_matte.");

   mstrcpy(&ph.name, matte_name);
   
	/* If you make it to here, then the polyhedron was successfully loaded,
	 * and the segment name matched one in the model, so add the matte to
	 * the list, and store the polyhedron.  Reallocate space for the array
    * if it is already full.
	 */
   if (sdm->force_matte_array_size == 0)
      sdm->force_matte_array_size += ARRAY_INCREMENT;

   if (sdm->num_force_mattes == 0)
   {
		sdm->force_matte = (dpForceMatte*)simm_malloc(sdm->force_matte_array_size *
         sizeof(dpForceMatte));
   }
	else if (sdm->num_force_mattes == sdm->force_matte_array_size)
   {
      sdm->force_matte_array_size += ARRAY_INCREMENT;
		sdm->force_matte = (dpForceMatte*)simm_realloc(sdm->force_matte,
				(sdm->force_matte_array_size) * sizeof(dpForceMatte), &rc);
      if (rc == code_bad)
      {
         sim_message(abort_action, "Ran out of memory. Unable to create force matte.");
         return code_bad;
      }
   }

   /* now that you have allocated space for the matte, fill in the info */
   mstrcpy(&sdm->force_matte[sdm->num_force_mattes].name, matte_name);
   sdm->force_matte[sdm->num_force_mattes].segment = segnum;
   sdm->force_matte[sdm->num_force_mattes].ph = 
      (dpPolyhedronStruct*)simm_malloc(sizeof(dpPolyhedronStruct));
   copy_polyhedron(&ph, sdm->force_matte[sdm->num_force_mattes].ph);

   sdm->num_force_mattes++;

   return code_fine;
}


void append_if_necessary (char str[], char c)
{
   int n = strlen(str);
   
   if (str[n-1] != c)
   {
      str[n] = c;
      str[n+1] = '\0';
   }
}


const char* get_suffix(const char str[])
{
   int cp = 0;

   cp = strlen(str) - 1;

   while (cp >= 0 && str[cp] != '.')
      cp--;

   if (cp == 0)
      return (NULL);

   return &str[cp+1];
}

const char* get_function_suffix(dpSplineFunction* func)
{
	if (func->type == dpNaturalCubic)
		return natural_cubic_text;
	if (func->type == dpGCVSpline)
		return gcv_text;
	if (func->type == dpLinear)
		return linear_text;
	return "";
}
