

/*==============================================================================*/
/*==============================================================================*/
/*==============================================================================*/
/*===                                                                       ====*/
/*=== GENERAL MATHEMATICAL MATRIX OPERATION ROUTINES DESIGNED TO ACCOMODATE ====*/
/*===             HIGH EFFICIENCY COMPUTATION OF MATRIX EQUATIONS.           ===*/
/*===                                                                       ====*/
/*===                               written by:                             ====*/
/*===                                                                       ====*/
/*===                              Brian Garner                             ====*/
/*===                               March 1995                              ====*/
/*===                                                                       ====*/
/*==============================================================================*/
/*==============================================================================*/
/*==============================================================================*/
/*== COPY A(NxM) INTO C(NxM) (A AND C CAN OVERLAP BUT SHOULDN'T)					==*/
/*== SCALE A(NxM) BY b AND PUT RESULT IN C(NxM) (A AND C CAN OVERLAP)			==*/
/*== ADD A(NxM) TO B(NxM) AND PUT RESULT IN C(NxM) (A,B,C CAN OVERLAP)			==*/
/*== SUBTRACT B(NxM) FROM A(NxM) AND PUT RESULT IN C(NxM) (A,B,C CAN OVERLAP)	==*/
/*== CROSS A(3x3) BY B(3x3) AND PUT RESULT IN C(3x3) (A,B,C CAN OVERLAP)		==*/
/*== TRANSPOSE A(NxM) INTO B(MxN) (A AND B CAN OVERLAP)								==*/
/*== MULTIPLY A(NxP) BY B(PxM) AND PUT RESULT IN C(NxM) (A,B,C CAN OVERLAP)	==*/
/*== SOLVE THE SYSTEM OF LINEAR EQUATIONS:  A(NxN)*X(Nx1)=B(Nx1)              ==*/
/*== INVERT INP MATRIX AND PUT IT INTO INV (INP AND INV CAN OVERLAP)				==*/
/*== PRINT MATRIX A(NxM) WITH title                                           ==*/
/*==============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

#define ISZERO(A) ( ((A)<1.0e-15) && ((A)>-1.0e-15) )


/*==============================================================================*/
/*======== COPY A(NxM) INTO C(NxM) (A AND C CAN OVERLAP BUT SHOULDN'T) =========*/
/*==============================================================================*/
int bgcopymtx_(int N,int M,double A[],double C[]) {
	if(A==C) return(0);
	memcpy(C,A,N*M*sizeof(double));
	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*====== SCALE A(NxM) BY b AND PUT RESULT IN C(NxM) (A AND C CAN OVERLAP) ======*/
/*==============================================================================*/
int bgscalemtx_(int *N,int *M,double A[],double *b,double C[]) {
	register double *Aij=A,*Cij=C;
	register int i,n;
	for(i=0,n=*N**M;i<n;i++) *(Cij++) = *(Aij++)**b;
	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*===== ADD A(NxM) TO B(NxM) AND PUT RESULT IN C(NxM) (A,B,C CAN OVERLAP) ======*/
/*==============================================================================*/
int bgaddmtx_(int N,int M,double A[],double B[],double C[]) {
	register double *Aij=A,*Bij=B,*Cij=C;
	register int i,n;
	for(i=0,n=N*M;i<n;i++) *(Cij++) = *(Aij++) + *(Bij++);
	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*== SUBTRACT A(NxM) FROM B(NxM) AND PUT RESULT IN C(NxM) (A,B,C CAN OVERLAP) ==*/
/*==============================================================================*/
int bgsubtractmtx_(int N,int M,double A[],double B[],double C[]) {
	register double *Aij=A,*Bij=B,*Cij=C;
	register int i,n;
	for(i=0,n=N*M;i<n;i++) *(Cij++) = *(Aij++) - *(Bij++);
	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*==== CROSS A(3x3) BY B(3x3) AND PUT RESULT IN C(3x3) (A,B,C CAN OVERLAP) =====*/
/*==============================================================================*/
int bgcrossvector_(double A[],double B[],double C[]) {
	register double x,y;
	x    = A[1]*B[2] - B[1]*A[2];
	y    = A[2]*B[0] - B[2]*A[0];
	C[2] = A[0]*B[1] - B[0]*A[1];		C[0] = x;		C[1] = y;
	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*======= MAINTAIN MEMORY ALLOCATION FOR VARIOUS OPERATIONS THAT NEED IT =======*/
/*==============================================================================*/
static double *MTX=NULL,**Mtx=NULL,**Inv=NULL;
static int mtxsize=0;
static int ptrsize=0;
/*==============================================================================*/
void bgAllocateMtx(int size) {
	if(mtxsize>0) free(MTX);	mtxsize=size;
	MTX=(double *) malloc(size*sizeof(double));
	if(MTX==NULL) { fprintf(stderr,"\nOut of memory.\n\n"); exit(0); }
	return;
}
/*==============================================================================*/
void bgAllocatePtr(int size) {
	if(ptrsize>0) { free(Mtx); free(Inv); }	ptrsize=size;
	Mtx=(double **) malloc(size*sizeof(double *));
	Inv=(double **) malloc(size*sizeof(double *));
	if(Inv==NULL) { fprintf(stderr,"\nOut of memory.\n\n"); exit(0); }
	return;
}
/*==============================================================================*/




/*==============================================================================*/
/*============== TRANSPOSE A(NxM) INTO B(MxN) (A AND B CAN OVERLAP) ============*/
/*==============================================================================*/
int bgtransposemtx_(int *N,int *M,double A[],double B[]) {
	register double *Aij,*Bji;
	register int i,j;
	if(A==B) {
		if(mtxsize<*N**M) bgAllocateMtx(*N**M);
		for(i=0,Aij=A;i<*N;i++) { Bji = MTX+i; for(j=0;j<*M;j++,Bji+=*N) *Bji = *(Aij++); }
		memcpy(B,MTX,*N**M*sizeof(double));
	} else {
		for(i=0,Aij=A;i<*N;i++) { Bji = B+i; for(j=0;j<*M;j++,Bji+=*N) *Bji = *(Aij++); }
	}
	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*=== MULTIPLY A(NxP) BY B(PxM) AND PUT RESULT IN C(NxM) (A,B,C CAN OVERLAP) ===*/
/*==============================================================================*/
int bgmultiplymtx_(int N,int P,int M,double A[],double B[],double C[]) {
	register double *Aik,*Bkj,*Rij,d;
	register int i,j,k;
	if((A==C)||(B==C)) {
		if(mtxsize<N*M) bgAllocateMtx(N*M);
		for(i=0,Rij=MTX;i<N;i++) for(j=0;j<M;j++,Rij++) {
			Aik = A+i*P;	Bkj = B+j;
			for(k=0,d=0.0;k<P;k++,Bkj+=M) d += *(Aik++) * *Bkj;
			*Rij = d;
		}
		memcpy(C,MTX,N*M*sizeof(double));
	} else {
		for(i=0,Rij=C;i<N;i++) for(j=0;j<M;j++,Rij++) {
			Aik = A+i*P;	Bkj = B+j;
			for(k=0,d=0.0;k<P;k++,Bkj+=M) d += *(Aik++) * *Bkj;
			*Rij = d;
		}
	}
	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*======== SOLVE THE SYSTEM OF LINEAR EQUATIONS:  A(NxN)*X(Nx1)=B(Nx1) =========*/
/*==============================================================================*/
int bgsolvelinear_(int *N,double A[],double X[],double B[]) {
	register double **Mr,*Mrj,*Mij,*Xr,*Br,d;
	register int r,i,j,n;

	/*====================================================================*/
	/*======= ALLOCATE STORAGE FOR DUPLICATE OF A AND ROW POINTERS =======*/
	/*====================================================================*/
	if(mtxsize<*N*(*N+1)) bgAllocateMtx(*N*(*N+1)); if(ptrsize<*N) bgAllocatePtr(*N);
	/*====================================================================*/

	/*====================================================================*/
	/*== COPY A INTO MTX(NxN), B INT MTX(N+1), AND LOAD POINTER VECTOR ===*/
	/*====================================================================*/
	for(r=0,Mrj=MTX,Mij=A,Br=B;r<*N;r++) {
		for(j=0;j<*N;j++) *(Mrj++) = *(Mij++);	*(Mrj++) = *(Br++); }
	for(r=0,Mr=Mtx;r<*N;r++) *(Mr++)=MTX+r*(*N+1);
	/*====================================================================*/

	/*====================================================================*/
	/*======= REDUCE MTX TO UPPER TRIANGULAR USING ROW OPS ON MTX ========*/
	/*====================================================================*/
	for(r=0,n=*N-1;r<n;r++) {
		if(ISZERO(*(Mrj=Mtx[r]+r))) {	/*==== SWAP ROWS ====*/
			for(i=r+1;i<*N;i++) if(!ISZERO(*(Mtx[i]+r))) break;
			if(i==*N) return(-1);	/*=== NON-INVERTIBLE ===*/
			Mrj=Mtx[r];	Mtx[r]=Mtx[i];	Mtx[i]=Mrj;	Mrj=Mtx[r]+r;
		}
		for(i=r+1;i<*N;i++) {
			if(ISZERO(*(Mij=Mtx[i]+r))) continue;	Mrj=Mtx[r]+r;
			d = (*Mij)/(*Mrj);	*(Mij++)=0.0;	Mrj++;
			for(j=r+1;j<=*N;j++) *(Mij++) -= *(Mrj++)*d;
		}
	}
	/*====================================================================*/

	if(ISZERO(*(Mrj=Mtx[r]+r))) return(-1);	/*=== NON-INVERTIBLE ===*/

	/*====================================================================*/
	/*========= BACK PROPAGATE SOLUTION THROUGH TRIANGULAR MATRIX ========*/
	/*====================================================================*/
	n=*N-1;	Xr=X+n;	*Xr = *((Mrj=Mtx[n])+*N) / *(Mrj+n);
	for(r=n-1,Xr--,Mr=Mtx+r;r>=0;r--,Mr--) {
		d = *(*Mr+*N);
		for(j=r+1,Mrj= *Mr+j;j<*N;j++) d -= *(Mrj++)*X[j];
		*(Xr--) = d / *(*Mr+r);
	}
	/*====================================================================*/

	return(0);
}
/*==============================================================================*/




/*==============================================================================*/
/*====== INVERT INP MATRIX AND PUT IT INTO INV (INP AND INV CAN OVERLAP) =======*/
/*==============================================================================*/
int bginvertmtx_(int N,double INP[],double INV[]) {
	register double **Mr,**Ir,*Mrj,*Irj,*Mij,*Iij,d;
	register int r,i,j,n;

	/*====================================================================*/
	/*====== ALLOCATE STORAGE FOR DUPLICATE OF INP AND ROW POINTERS ======*/
	/*====================================================================*/
	if(mtxsize<N*N) bgAllocateMtx(N*N); if(ptrsize<N) bgAllocatePtr(N);
	/*====================================================================*/

	/*====================================================================*/
	/*======== COPY INP INTO MTX AND LOAD IDENTITY MATRIX INTO INV =======*/
	/*====================================================================*/
	n=N*N*sizeof(double);	memcpy(MTX,INP,n);	memset(INV,0,n);
	for(r=0,Mr=Mtx,Ir=Inv;r<N;r++,Mr++,Ir++) { i=r*N; *Mr=MTX+i; *Ir=INV+i; }
	for(r=0,Irj=INV,n=N+1;r<N;r++,Irj+=n) *Irj=1.0;
	/*====================================================================*/

	/*====================================================================*/
	/*=== REDUCE MTX TO UPPER TRIANGULAR USING ROW OPS ON MTX AND INV ====*/
	/*====================================================================*/
	for(r=0,n=N-1;r<n;r++) {
		if(ISZERO(*(Mrj=Mtx[r]+r))) 	/*==== SWAP ROWS ====*/{
			for(i=r+1;i<N;i++) if(!ISZERO(*(Mtx[i]+r))) break;
			if(i==N) return(-1);	/*=== NON-INVERTIBLE ===*/
			Mrj=Mtx[r];	Mtx[r]=Mtx[i];	Mtx[i]=Mrj;	Mrj=Mtx[r]+r;
			for(j=0,Irj=Inv[r],Iij=Inv[i];j<N;j++) {
					d= *Irj;  *(Irj++) = *Iij;	*(Iij++) = d; }
		}
		for(i=r+1;i<N;i++) {
			if(ISZERO(*(Mij=Mtx[i]+r))) continue;	Mrj=Mtx[r]+r;
			d = (*Mij)/(*Mrj);	*(Mij++)=0.0;	Mrj++;
			for(j=r+1;j<N;j++) *(Mij++) -= *(Mrj++)*d;
			Irj=Inv[r];	Iij=Inv[i];
			for(j=0;j<N;j++) *(Iij++) -= *(Irj++)*d;
		}
	}
	/*====================================================================*/


	/*====================================================================*/
	/*================= NORMALIZE LAST ROW OF MTX AND INV ================*/
	/*====================================================================*/
	if(ISZERO(*(Mrj=Mtx[r]+r))) return(-1);	/*=== NON-INVERTIBLE ===*/
	d = 1.0 / *Mrj;	*Mrj=1.0;
	for(j=0,Irj=Inv[r];j<N;j++) *(Irj++) *= d;
	/*====================================================================*/

	/*====================================================================*/
	/*======== DIAGONALIZE MTX USING ROW OPERATIONS ON MTX AND INV =======*/
	/*====================================================================*/
	for(r=N-1;r>0;) {
		for(i=r-1;i>=0;i--) {
			if(ISZERO(*(Mij=Mtx[i]+r))) continue;
			d = *Mij;	*Mij=0.0;
			for(j=0,Iij=Inv[i],Irj=Inv[r];j<N;j++) *(Iij++) -= *(Irj++)*d;
		}
		r--;
		d = 1.0 / *(Mrj=Mtx[r]+r);	*Mrj=1.0;
		for(j=0,Irj=Inv[r];j<N;j++) *(Irj++) *= d;
	}
	/*====================================================================*/

	return(0);
}
/*==============================================================================*/







/*==============================================================================*/
/*========================= PRINT MATRIX A(NxM) WITH title =====================*/
/*==============================================================================*/
int bgprintmtx_(int N, int M, double *A, char *title) {
	int i,j,l;	l=strlen(title);
	if(l<10) printf("%s",title);
	else { printf("%s\n",title); l=10; }
	for(i=0;i<N;i++) {
		if((i>0)&&(i<N-1))	for(j=0;j<l;j++) printf(" ");
		else if(i>0) 			for(j=0;j<l;j++) printf("_");
		for (j=0;j<M;j++) {
			if(j>0) printf("    ");
			printf("%.3lf",*(A + i*M + j));
		}
		printf("\n");
	}
	return(0);
}
/*==============================================================================*/

