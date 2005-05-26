/***********************************************************/
/*    Sample 3 from CFSQP distribution			   */
/*    Problem 71 from Hock/Schittkowski, 1981              */
/***********************************************************/

#include "cfsqpusr.h"

void obj71();
void cntr71();
void grob71();
void grcn71();

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
   eps=1.e-7;
   epsneq=7.e-6;
   udelta=0.e0;
   nparam=4;
   nf=1;
   neqn=1;
   nineqn=1;
   nineq=1;
   neq=1;
   ncsrl=ncsrn=nfsr=mesh_pts[0]=0;
   bl=(double *)calloc(nparam,sizeof(double));
   bu=(double *)calloc(nparam,sizeof(double));
   x=(double *)calloc(nparam,sizeof(double));
   f=(double *)calloc(nf,sizeof(double));
   g=(double *)calloc(nineq+neq,sizeof(double));
   lambda=(double *)calloc(nineq+neq+nf+nparam,sizeof(double));
   
   bl[0]=bl[1]=bl[2]=bl[3]=1.e0;
   bu[0]=bu[1]=bu[2]=bu[3]=5.e0;


   x[0]=1.e0;
   x[1]=5.e0;
   x[2]=5.e0;
   x[3]=1.e0;

   cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
         mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,
         f,g,lambda,obj71,cntr71,grob71,grcn71,cd);

   free(bl);
   free(bu);
   free(x);
   free(f);
   free(g);
   free(lambda);
   return 0;
}
   
void  
obj71(nparam,j,x,fj,cd)
int nparam,j;
double *x,*fj;
void *cd;
{
   *fj=x[0]*x[3]*(x[0]+x[1]+x[2])+x[2];
   return;
}

void
grob71(nparam,j,x,gradfj,dummy,cd)
int nparam,j;
double *x,*gradfj;
void (* dummy)(),*cd;
{
   gradfj[0]=x[3]*(x[0]+x[1]+x[2])+x[0]*x[3];
   gradfj[1]=x[0]*x[3];
   gradfj[2]=x[0]*x[3]+1.e0;
   gradfj[3]=x[0]*(x[0]+x[1]+x[2]);
   return;
}

void  
cntr71(nparam,j,x,gj,cd)
int nparam,j;
double *x,*gj;
void *cd;
{
   switch (j) {
      case 1:
	 *gj=25.e0-x[0]*x[1]*x[2]*x[3];
	 break;
      case 2:
	 *gj=x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]-40.e0;
	 break;
   }
   return;
}

void
grcn71(nparam,j,x,gradgj,dummy,cd)
int nparam,j;
double *x,*gradgj;
void (* dummy)(),*cd;
{
   switch (j) {
      case 1:
	 gradgj[0]=-x[1]*x[2]*x[3];
	 gradgj[1]=-x[0]*x[2]*x[3];
	 gradgj[2]=-x[0]*x[1]*x[3];
	 gradgj[3]=-x[0]*x[1]*x[2];
	 break;
      case 2:
	 gradgj[0]=2.e0*x[0];
	 gradgj[1]=2.e0*x[1];
	 gradgj[2]=2.e0*x[2];
	 gradgj[3]=2.e0*x[3];
	 break;
   }
   return;
}   
