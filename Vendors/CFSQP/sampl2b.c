/***********************************************************/
/*    Sample 2b from CFSQP distribution			   */
/*    Example 6 from Madsen, 1978                          */
/***********************************************************/

#include "cfsqpusr.h"

void objmad();
void cnmad();

int 
main() {
   int nparam,nf,nineq,neq,mode,iprint,miter,neqn,nineqn,
       ncsrl,ncsrn,nfsr,mesh_pts[1],inform;
   double bigbnd,eps,epsneq,udelta;
   double *x,*bl,*bu,*f,*g,*lambda;
   double *cd;

   mode=111;
   iprint=1;
   miter=500;
   bigbnd=1.e10;
   eps=1.e-8;
   epsneq=0.e0;
   udelta=0.e0;
   nparam=6;
   nf=1;
   nfsr=1;
   mesh_pts[0]=163;
   neqn=0;
   nineqn=0;
   nineq=7;
   neq=0;
   ncsrl=ncsrn=0;
   bl=(double *)calloc(nparam,sizeof(double));
   bu=(double *)calloc(nparam,sizeof(double));
   x=(double *)calloc(nparam,sizeof(double));
   f=(double *)calloc(mesh_pts[0],sizeof(double));
   g=(double *)calloc(nineq+neq,sizeof(double));
   lambda=(double *)calloc(nineq+neq+mesh_pts[0]+nparam,
          sizeof(double));
   
   bl[0]=bl[1]=bl[2]=bl[3]=bl[4]=bl[5]=-bigbnd;
   bu[0]=bu[1]=bu[2]=bu[3]=bu[4]=bu[5]=bigbnd;

   x[0]=0.5e0;
   x[1]=1.e0;
   x[2]=1.5e0;
   x[3]=2.e0;
   x[4]=2.5e0;
   x[5]=3.e0;

   cd=(double *)calloc(2,sizeof(double));
   cd[0]=3.14159265358979e0;
   cd[1]=0.425e0;

   cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
         mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,
         f,g,lambda,objmad,cnmad,grobfd,grcnfd,cd);

   free(bl);
   free(bu);
   free(x);
   free(f);
   free(g);
   free(lambda);
   free(cd);
   return 0;
}
   
void
objmad(nparam,j,x,fj,cd)
int nparam,j;
double *x,*fj;
double *cd;
{
   double pi,theta;
   int i;

   pi=cd[0];
   theta=pi*(8.5e0+j*0.5e0)/180.e0;
   *fj=0.e0;
   for (i=0; i<=5; i++)
      *fj=*fj+cos(2.e0*pi*x[i]*sin(theta));
   *fj=2.e0*(*fj+cos(2.e0*pi*3.5e0*sin(theta)))/15.e0
      +1.e0/15.e0;
   return; 
}

void  
cnmad(nparam,j,x,gj,cd)
int nparam,j;
double *x,*gj;
double *cd;
{
   double ss;

   ss=cd[1];
   switch (j) {
      case 1:
	 *gj=ss-x[0];
	 break;
      case 2:
	 *gj=ss+x[0]-x[1];
	 break;
      case 3:
	 *gj=ss+x[1]-x[2];
	 break;
      case 4:
	 *gj=ss+x[2]-x[3];
	 break;
      case 5:
	 *gj=ss+x[3]-x[4];
	 break;
      case 6:
	 *gj=ss+x[4]-x[5];
	 break;
      case 7:
	 *gj=ss+x[5]-3.5e0;
	 break;
   }
   return;
}
