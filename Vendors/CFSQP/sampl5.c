/************************************************************/
/*    Sample 5 from CFSQP distribution                      */
/*    Ex. 2 from Coope & Watson, 1985			    */
/*    single nonlinear SI constraint			    */
/************************************************************/

#include "cfsqpusr.h"

void obj();
void cntr();
void grob();
void grcn();

int
main() {
   int nparam,nf,nineq,neq,mode,iprint,miter,neqn,nineqn,
       ncsrl,ncsrn,nfsr,mesh_pts[1],inform;
   double bigbnd,eps,epsneq,udelta;
   double *x,*bl,*bu,*f,*g,*lambda;
   void *cd;

   mode=100;
   iprint=1;
   miter=500;
   bigbnd=1.e10;
   eps=1.e-4;
   epsneq=0.e0;
   udelta=0.e0;
   nparam=2;
   nf=1;
   neqn=0;
   nineqn=nineq=1;
   ncsrn=1;
   ncsrl=0;
   mesh_pts[0]=101;
   neq=nfsr=0;
   bl=(double *)calloc(nparam,sizeof(double));
   bu=(double *)calloc(nparam,sizeof(double));
   x=(double *)calloc(nparam,sizeof(double));
   f=(double *)calloc(nf,sizeof(double));
   g=(double *)calloc(nineq+(mesh_pts[0]-1)*(ncsrl+ncsrn)+neq,
      sizeof(double));
   lambda=(double *)calloc(nineq+(mesh_pts[0]-1)*(ncsrl+ncsrn)+neq+
          nf+nparam,sizeof(double));
   
   bl[0]=bl[1]=-bigbnd;
   bu[0]=bu[1]=bigbnd;

   x[0]=-1.e0;
   x[1]=-2.e0;

   cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
         mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,
         f,g,lambda,obj,cntr,grob,grcn,cd);

   free(bl);
   free(bu);
   free(x);
   free(f);
   free(g);
   free(lambda);
   return 0;
}
   
void
obj(nparam,j,x,fj,cd)
int nparam,j;
double *x,*fj;
void *cd;
{
   *fj=(1.e0/3.e0)*pow(x[0],2.e0)+pow(x[1],2.e0)+0.5e0*x[0];
   return;
}

void
grob(nparam,j,x,gradfj,dummy,cd)
int nparam,j;
double *x,*gradfj;
void (* dummy)(),*cd;
{
   gradfj[0]=(2.e0/3.e0)*x[0]+0.5e0;
   gradfj[1]=2.e0*x[1];
   return;
}

void  
cntr(nparam,j,x,gj,cd)
int nparam,j;
double *x,*gj;
void *cd;
{
   double y;

   y=(j-1)/100.e0;
   *gj=pow((1.e0-pow(y*x[0],2.e0)),2.e0)-x[0]*y*y-pow(x[1],2.e0)
       +x[1];
   return;
}

void
grcn(nparam,j,x,gradgj,dummy,cd)
int nparam,j;
double *x,*gradgj;
void (* dummy)(),*cd;
{
   double y;

   y=(j-1)/100.e0;
   gradgj[0]=-4.e0*(1.e0-pow(y*x[0],2.e0))*y*y*x[0]-y*y;
   gradgj[1]=-2.e0*x[1]+1.e0;
   return;
}   
