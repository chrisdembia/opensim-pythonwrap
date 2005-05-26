// utwalking.h

#ifdef UNIX
#define __stdcall
#endif

#ifdef __cplusplus
extern "C" {
#endif

// INITIALIZATION
void __stdcall INTL23(double *x,double *ynode,int *maxiter,int *drvtype,
	double *dx,int *sclflg,int *inf,double *sxo,double *szo);
void intl23_(double *x,double *ynode,int *maxiter,int *drvtype,
	double *dx,int *sclflg,int *inf,double *sxo,double *szo);

// PARAMETERS
void __stdcall SETFOM(int *aMuscle,double *aFOM);
void setfom_(int *aMuscle,double *aFOM);
double __stdcall GETFOM(int *aMuscle);
double getfom_(int *aMuscle);
void __stdcall GETACTUATORLENGTHS(double *aLengths);
void getactuatorlengths_(double *aLengths);
void __stdcall GETACTUATORVELOCITIES(double *aVelocities);
void getactuatorvelocities_(double *aVelocities);

// MUSCLE
void __stdcall MMATVDOT(const int *nmus,double *xt,double *atv,
	double *TCRISE,double *TCFALL,double *atvdot);
void mmatvdot_(const int *nmus,double *xt,double *atv,
	double *TCRISE,double *TCFALL,double *atvdot);
void __stdcall MMFDOT(const int *nmus,double *actlen,double *actsv,double *f,double *atv,
	double *xt,double *fdot,double *edot);
void mmfdot_(const int *nmus,double *actlen,double *actsv,double *f,double *atv,
	double *xt,double *fdot,double *edot);
double __stdcall MUSFRC(const int *mus,double *atv,double *actlen,double *actsv);
double musfrc_(const int *mus,double *atv,double *actlen,double *actsv);
double mmintl_(const int *nmus,double *fom,double *lom,double *lst,double *pennation, double *slow,double *mass);

// APPLYING LOADS
void sforce23_(double *t,double *q,double *u,
	double *sforce,double *spt,double *tqlig);
void __stdcall FORCE23(double *t,double *y,double *q,double *u);
void force23_(double *t,double *y,double *q,double *u);
void spring23_(double *q,double *u,double *sforce,double *spt);

// GRAPHICS
int drawutwalking_(double *t,double *x,double *y,double *sfrc,double *spts);
void __stdcall SETMUSON(int *mus,int *onoff);
void setmuson_(int *mus,int *onoff);


#ifdef __cplusplus
}
#endif



