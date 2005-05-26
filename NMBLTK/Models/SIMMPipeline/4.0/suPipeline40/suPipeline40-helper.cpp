//////////////////////////////////
//
//  suPipeline40-helper
//
//  ripped from pipeline and modified
//
//
#include <cassert>
#include <stdexcept>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdarg>
#include <climits>
#include "./suPipeline40.h"
#include "./suPipeline40-helper.h"


extern "C" void set_up_kin_out_file ( FILE **fp, char filename[] );


//////////////////
// global pipeline data
// DP_MainShutdown responsible for cleanup
//
extern "C" {
   char buffer[1 + CHARBUFFER];
   char current_dir[1 + CHARBUFFER];
   dpSimulationParameters params;
   dpModelStruct *sdm;
   SystemInfo  si;
   MotionData* kinetics_data;
   extern dpBoolean verbose;
}



////////////////////
// DP_Data - non-global pipeline data
//

DP_Data::DP_Data()
{
   memset( static_cast<void *>( this ), 0, sizeof( *this ) );
}

DP_Data::~DP_Data()
{
   free( muscle_file );
   free( kinetics_file );
   free( output_motion_file );
   free( y );
   free( dy );
   if(kin_out!=NULL) fclose( kin_out );
}





/////////////////
// modified pipeline functions copied from main.c
//
//

// Name:  wants_to_quit
// Desc:  answer the question "does bozo want to quit?"

static bool wants_to_quit( )
{
   fprintf( stdout, "Continue simulation? " );
   fflush( stdout );
   int c = getc( stdin );

   if ( toupper(c) == 'N' ) {
      fprintf( stdout, "stopping simulation\n" );
      return true;
   }

   return false;
}



// Name:  sim_message
// Desc:  prints a string and possibly throws an exception

extern "C" int sim_message( ErrorAction action, const char* format, ... )
{  
   va_list argptr;
   va_start( argptr, format );

   int rv = vfprintf( stdout, format, argptr );
   fprintf( stdout, "\n" );
   
   if ( action == exit_program )
      throw std::runtime_error( "sim_message: called with action==exit_program" );

   if ( action == recover && wants_to_quit() )
      throw std::runtime_error( "sim_message: user chose to stop simulation" );

   return rv;
}



// Name:  init_model
// Desc:  populate globals  (copied from main.c)

static void init_model()
{
   params.startTime = 0.0;
   params.endTime = 1.0;
   params.stepSize = 0.01;
   params.outputOptions.contactForces = dpYes;
   params.outputOptions.jointTorques = dpNo;
   params.outputOptions.jointReactionForces = dpNo;
   params.outputOptions.jointReactionTorques = dpNo;
   params.outputOptions.massCenterPositions = dpNo;
   params.outputOptions.massCenterVelocities = dpNo;
   params.outputOptions.muscleMomentArms = dpNo;
   params.outputOptions.muscleJointTorques = dpNo;
   params.outputOptions.totalMuscleJointTorques = dpNo;
   params.outputOptions.muscleActivations = dpYes;
   params.outputOptions.muscleLengths = dpNo;
   params.outputOptions.muscleForces = dpYes;
   params.outputOptions.systemEnergy = dpNo;
   params.outputOptions.numSpringForces = 10;
   params.outputOptions.normalization = dpNoNormalization;

   int info[50];
   sdinfo(info);
   sdm = (dpModelStruct*)simm_malloc(sizeof(dpModelStruct));
   sdm->num_body_segments = info[1] + 1;    /* include ground */
   sdm->nq = info[2] + info[7];
   sdm->nu = info[2];
   sdm->num_closed_loops = info[4];
   sdm->num_joints = info[1] + info[4]; /* nbod + nloop */
   sdm->num_constraints = info[3];
   sdm->num_user_constraints = info[10];
   sdm->num_springs = 0;
   sdm->num_spring_floors = 0;
   sdm->num_force_mattes = 0;
   sdm->spring_array_size = ARRAY_INCREMENT;
   sdm->spring_floor_array_size = ARRAY_INCREMENT;
   sdm->force_matte_array_size = ARRAY_INCREMENT;

   init_qs();
   init_segments();
   init_joints();
   init_wrap_objects();
   init_constraint_objects();

}



// Name:  DP_MainStartup
// Desc:  kitchen sink startup code, modified to use dpd instead of local variables
//        (copied from main.c)

void DP_MainStartup(DP_Data *dpd,const char *workpath,const char *paramfile)
{
   const double BAUMGARTE_STAB = 20.0;

   sim_message(none, "\nDynamics Pipeline (3.1.1) Simulation.\n");


   // populate sdm

   init_model();


  // copy workpath into current_dir
   {
      assert( PATH_MAX < CHARBUFFER );
      size_t len = strlen( workpath );

      if ( CHARBUFFER < len )
         throw std::logic_error( "main_startup: workpath too long" );

      strncpy( current_dir, workpath, 1 + len );
   }

   
   // this line can be eliminated by stipulating a small change to read_param_file formal parameter list
   std::vector<char> tmp_paramfile( &paramfile[0], &paramfile[ 1+strlen(paramfile) ] );

   ReturnCode rc = read_parameters_file(
      &tmp_paramfile[0],
      sdm, 
      &dpd->muscle_file,
      &dpd->kinetics_file, 
      &dpd->output_motion_file, 
      &dpd->output_kinetics_file
      );

   if ( rc == code_bad ) {
      sim_message(
         recover,
         "Unable to load input parameters: %s%s not found.\n",
         current_dir,
         paramfile
         );
   }

   init_joint_functions();
   init_q_restraint_functions();

   if ( dpd->muscle_file ) {
      if ( read_muscle_file( sdm, dpd->muscle_file ) == code_bad)  {

            sim_message(
               exit_program,
               "Error reading muscle file %s.", 
               dpd->muscle_file
               );
      }
   }
   else  {
      sdm->num_muscles = 0;
      sim_message( none, "Running simulation without a muscle file." );
   }

   
   int num_muscle_states = count_muscle_states( sdm );
   sdm->neq = sdm->nu + sdm->nq + num_muscle_states;

   dpd->dim = sdm->neq;
   dpd->y = (double*)simm_malloc(sdm->neq * sizeof(double));
   dpd->dy =(double*)simm_malloc(sdm->neq * sizeof(double));
   
	
   if ( dpd->kinetics_file )
      set_up_kinetics_input( dpd->kinetics_file, &kinetics_data );

   set_initial_conditions(&dpd->t, dpd->y, dpd->dy);
   
   init_motion();

   sdinit();
   check_for_sderror( "SDINIT" );
	
   assemble_model( dpd->t, dpd->y );

   /* enable constraint stabilization */
   sdstab( 2.0 * BAUMGARTE_STAB, BAUMGARTE_STAB * BAUMGARTE_STAB );
   sdstate( dpd->t, dpd->y, &dpd->y[sdm->nq] );

   init_muscle_states( sdm, dpd->y );

   sim_message(
      none,
      "\nSystem assembled (%d bodies, %d Qs, %d Us, %d muscles, %d muscle states).\n",
      sdm->num_body_segments, 
      sdm->nq, 
      sdm->nu, 
      sdm->num_muscles, 
      num_muscle_states
      );
	
   if ( verbose == dpYes )
      print_body_info();
   
   if ( dpd->output_motion_file )
   {
      create_output_motion( "sd_motion" );
      open_output_motion_file( dpd->output_motion_file );
   }

   if ( dpd->output_kinetics_file )
      set_up_kin_out_file( &dpd->kin_out, dpd->output_kinetics_file );

   check_for_sderror( "MAIN" );

   if ( verbose == dpYes )
   {
      //start_time = get_time_now();
      print_state(dpd->y,dpd->dy);

   }
}

// Name:  DP_MainShutdown
// Desc:  destroy globals

void DP_MainShutdown()
{
   // TODO: destroy globals: params, sdm, kinetics_data

   // pipeline does not do this b/c it is designed to run once to completion
}
/*
void print_state_2_file(double y[], double dy[], dpModelStruct* sdmp)
{
   int i, pres;
   FILE *fo;

   fo = fopen("statesFromSuPipeline.txt", "w");

   for (i = 0; i < sdm->nu; i++)
   {
      fprintf(fo, "y[%2d] = %-15.15s= %12.5f %12.5f", i, sdm->q[i].name, 
         sdm->q[i].conversion * y[i], sdm->q[i].conversion * y[i+ sdm->nq]);
      fprintf(fo, " %12.5f", dy[i + sdm->nq]);
      if (sdm->q[i].type == dpFixedQ)
         fprintf(fo, " %s", "FIXED");
      else if (sdm->q[i].type == dpUnconstrainedQ)
         fprintf(fo, " %s", "FREE");
      else if (sdm->q[i].type == dpPrescribedQ)
         fprintf(fo, " %s", "PRESCRIBED");
      else if (sdm->q[i].type == dpConstrainedQ)
         fprintf(fo, " %s", "CONSTRAINED");
      sdgetpres(sdm->q[i].joint, sdm->q[i].axis, &pres);
      if (pres == 0)
         fprintf(fo, "(0)\n");
      else
         fprintf(fo, "(1)\n");
   }
	for(i=0;i<sdm->neq;i++) {
		fprintf(fo, "y[%d]=\t%lf\n",i,y[i]);
	}
	for (i=0; i < sdm->num_muscles; i++){
		fprintf(fo, "%s, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", 
			sdm->muscles[i].name,
			sdm->muscles[i].muscle_tendon_length,
			sdm->muscles[i].fiber_length,
			sdm->muscles[i].tendon_length,
			sdm->muscles[i].muscle_tendon_vel,
			sdm->muscles[i].fiber_velocity,
			sdm->muscles[i].tendon_velocity,
			sdm->muscles[i].force,
			sdm->muscles[i].applied_power,
			sdm->muscles[i].excitation_level);
	}

   fprintf(fo, "********************************************************************************");
   fclose(fo);
}
*/