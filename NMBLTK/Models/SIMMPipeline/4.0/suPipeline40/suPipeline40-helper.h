#ifndef SU_PIPELINE_40_HELPER_H
#define SU_PIPELINE_40_HELPER_H
//////
//
// suPipeline40-helper
//
// ripped from pipeline and modified
//
//



////////////
// pipeline includes

extern "C" {
#  include "./dp/basic.h"
#  include "./dp/dp.h"
#  include "./dp/structs.h"
#  include "./dp/functions.h"
#  include "./dp/model_d.h"
}


///////////
// pipeline globals
//
extern "C" {
   extern char buffer[1 + CHARBUFFER];
   extern char current_dir[1 + CHARBUFFER];
   extern dpSimulationParameters params;
   extern dpModelStruct *sdm;
   extern SystemInfo si;
   extern MotionData* kinetics_data;
   extern dpBoolean verbose;
}




//////////
// DP_Data
//  non-global pipeline data
//
//  malloc/free used for all member data
//
struct DP_Data {
   char *muscle_file;
   char *kinetics_file;
   char *output_motion_file;
   char *output_kinetics_file;
   int dim;
   double *y;
   double *dy;
   double t;
   FILE *kin_out;

   DP_Data(); // zero out the struct
   ~DP_Data(); // free dynamic resources
private:
   DP_Data( const DP_Data & );
   DP_Data & operator = ( const DP_Data & );
};



/////////////
// modified pipeline functions
//
extern "C" int sim_message( ErrorAction action, const char* format, ... );
extern "C" void DP_MainStartup( DP_Data *dpd, const char *workpath, const char *paramfile );

extern "C" void DP_MainShutdown();



#endif
