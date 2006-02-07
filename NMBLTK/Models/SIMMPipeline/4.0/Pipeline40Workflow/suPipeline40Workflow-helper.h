// Clay Anderson added the following two lines to integrate Darryl Thelen's changes
// to the pipeline.
struct DP_Data;
extern "C" void init_gaitsim(dpModelStruct* sdm, MotionData* data,double t,double *y);
extern "C" void DP_MainStartup_Workflow(DP_Data *dpd,const char *workpath,const char *paramfile);
extern "C" void computeConstrainedCoords(dpModelStruct* sdm,double* y);
