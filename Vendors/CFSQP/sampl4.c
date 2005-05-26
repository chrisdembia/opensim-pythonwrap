/***********************************************************/
/*    Sample 4 from CFSQP Distribution                     */
/*    TP374 from Schittkowski, 1991                        */
/*    single linear SI constraint			   */
/***********************************************************/

#include "cfsqpusr.h"

#define r 100

void obj();
void cntr();
void grob();

int
main() {
   int nparam,nf,nineq,neq,mode,iprint,miter,neqn,nineqn,
       ncsrl,ncsrn,nfsr,mesh_pts[3],numc,inform;
   double bigbnd,eps,epsneq,udelta;
   double *x,*bl,*bu,*f,*g,*lambda;
   void *cd;

   mode=100;
   iprint=1;
   miter=500;
   bigbnd=1.e10;
   eps=1.e-7;
   epsneq=0.e0;
   udelta=0.e0;
   nparam=10;
   nf=1;
   neqn=0;
   nineqn=nineq=ncsrn=3;
   ncsrl=0;
   mesh_pts[0]=mesh_pts[1]=r;
   mesh_pts[2]=3*r/2;
   neq=nfsr=0;
   numc=(int )(3.5*r);
   bl=(double *)calloc(nparam,sizeof(double));
   bu=(double *)calloc(nparam,sizeof(double));
   x=(double *)calloc(nparam,sizeof(double));
   f=(double *)calloc(nf,sizeof(double));
   g=(double *)calloc(numc,sizeof(double));
   lambda=(double *)calloc(numc+nf+nparam,sizeof(double));
   
   bl[0]=bl[1]=bl[2]=bl[3]=bl[4]=bl[5]=bl[6]=bl[7]=bl[8]=bl[9]=-bigbnd;
   bu[0]=bu[1]=bu[2]=bu[3]=bu[4]=bu[5]=bu[6]=bu[7]=bu[8]=bu[9]=bigbnd;

   x[0]=x[1]=x[2]=x[3]=x[4]=x[5]=x[6]=x[7]=x[8]=0.1e0;
   x[9]=1.e0;

   cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
         mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,
         f,g,lambda,obj,cntr,grob,grcnfd,cd);

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
   *fj=x[9];
   return;
}

void
grob(nparam,j,x,gradfj,dummy,cd)
int nparam,j;
double *x,*gradfj;
void (* dummy)(),*cd;
{
   gradfj[0]=0.e0;
   gradfj[1]=0.e0;
   gradfj[2]=0.e0;
   gradfj[3]=0.e0;
   gradfj[4]=0.e0;
   gradfj[5]=0.e0;
   gradfj[6]=0.e0;
   gradfj[7]=0.e0;
   gradfj[8]=0.e0;
   gradfj[9]=1.e0;
   return;
}

void  
cntr(nparam,j,x,gj,cd)
int nparam,j;
double *x,*gj;
void *cd;
{
   double t,z,s1,s2;
   int k;

   s1=s2=0.e0;
   if (j<=r) t=3.14159265e0*(j-1)*0.025e0;
   else {
      if (j<=2*r) t=3.14159265e0*(j-1-r)*0.025e0;
      else t=3.14159265e0*(1.2e0+(j-1-2*r)*0.2e0)*0.25e0;
   }
   for (k=1; k<=9; k++) {
      s1=s1+x[k-1]*cos(k*t);
      s2=s2+x[k-1]*sin(k*t);
   }
   z=s1*s1 + s2*s2;
   if (j<=r) *gj=(1.e0-x[9])*(1.e0-x[9])-z;
   else {
      if (j<=2*r) *gj=z-(1.e0+x[9])*(1.e0+x[9]);
      else *gj=z-x[9]*x[9];
   }
   return;
}
