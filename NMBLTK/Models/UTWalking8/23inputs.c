#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nq 24
#define nu 23
#define nb 10
#define na 30
#define nm 30 

/*=============================================================*/
int input23s_(char *file,int *n,double t[],double q[][nq])
/*=============================================================*/
{
const char path[] = "./";
const double dtr = 0.01745329252;
FILE *fp;
int i,j,end;
char ds[100],infile[60];
double dd;
double m[1000][3][3];

/* JOINT ANGLES */
/*--------------*/
  strcpy(infile,path);
  strcat(infile,file);
  strcat(infile,".jang");
  fp = fopen(infile,"r");
  fscanf(fp,"%s",ds);
  for (i=0;i<nb;i++) fscanf(fp,"%s",ds);
  for (i=0;i<na;i++) fscanf(fp,"%s",ds);
  for (end=i=0;end!=EOF;i++) {
    if ((end=fscanf(fp,"%lf",&t[i])) == EOF) continue;
    fscanf(fp,"%lf %lf %lf",&q[i][3],&q[i][4],&q[i][5]); /* pelvis xyz */ 
    fscanf(fp,"%lf %lf %lf",&q[i][6],&q[i][7],&q[i][8]); /* hat xyz */ 
    fscanf(fp,"%lf %lf %lf",&q[i][9],&q[i][10],&q[i][11]); /* rhip xyz */ 
    fscanf(fp,"%lf %lf %lf",&q[i][12],&dd,&dd); /* rknee */ 
    fscanf(fp,"%lf %lf %lf",&q[i][13],&q[i][14],&dd); /* rank */ 
    fscanf(fp,"%lf %lf %lf",&q[i][15],&dd,&dd); /* rtoe */ 
    fscanf(fp,"%lf %lf %lf",&q[i][16],&q[i][17],&q[i][18]); /* lhip xyz */ 
    fscanf(fp,"%lf %lf %lf",&q[i][19],&dd,&dd); /* lknee */ 
    fscanf(fp,"%lf %lf %lf",&q[i][20],&q[i][21],&dd); /* lank */ 
    fscanf(fp,"%lf %lf %lf",&q[i][22],&dd,&dd); /* ltoe */ 
    for (j=3;j<nu;j++) q[i][j] *= dtr;
  }
  fclose(fp);
  *n = i - 1;

/* JOINT MARKERS */
/*---------------*/
  strcpy(infile,path);
  strcat(infile,file);
  strcat(infile,".mrks");
  fp = fopen(infile,"r");
  fscanf(fp,"%s",ds);
  for (i=0;i<nb;i++) fscanf(fp,"%s",ds);
  for (i=0;i<nm;i++) fscanf(fp,"%s",ds);
  for (i=0;i<nm*3;i++) fscanf(fp,"%s",ds);
  for (i=0;i<*n;i++) {
    fscanf(fp,"%lf",&dd);  /* time */
    fscanf(fp,"%lf %lf %lf",&m[i][0][0],&m[i][0][1],&m[i][0][2]);
    fscanf(fp,"%lf %lf %lf",&m[i][1][0],&m[i][1][1],&m[i][1][2]);
    fscanf(fp,"%lf %lf %lf",&m[i][2][0],&m[i][2][1],&m[i][2][2]);
    for (j=0;j<(3*(nm-3));j++) fscanf(fp,"%lf",&dd); 
  }
  fclose(fp);


/* ASSIGN PELVIS TRANSLATION */
/*---------------------------*/
  for (i=0;i<*n;i++) {
    q[i][0] = (m[i][0][0] + m[i][1][0] + m[i][2][0])/3.0;
    q[i][1] = (m[i][0][1] + m[i][1][1] + m[i][2][1])/3.0;
    q[i][2] = (m[i][0][2] + m[i][1][2] + m[i][2][2])/3.0 - 0.7;
  }

/* ZERO THE X POSITION OF THE PELVIS */
/*-----------------------------------*/
	dd = q[0][0];
   for (i=0;i<*n;i++) q[i][0] = q[i][0] - dd; 

/* TAKE SOME HEIGHT OF OFF THE Y POSITON */
/*---------------------------------------*/
   dd = 0.05;
   for (i=0;i<*n;i++) q[i][1] -= dd;

/* ZERO THE TIME ARRAY */
/*---------------------*/
   dd = t[0];
   for (i=0;i<*n;i++) t[i] -= dd; 


  return(0);
}
/*=============================================================*/



/*=============================================================*/
int input23a_(int *n,double t[],double q[][nq])
/*=============================================================*/
{
const char path[] = "./";
const double dtr = 0.01745329252;
FILE *fp;
int i,j,end;
char ds[100],infile[60];
double dd,norm;
double m[1000][3][3];

/* printf("\n\ninput23a_: reading in subject data...\n\n"); */

/* JOINT ANGLES */
/*--------------*/
  strcpy(infile,path);
  strcat(infile,"subave");
  strcat(infile,".jang");
  fp = fopen(infile,"r");
  for(end=i=0;end!=EOF;i++) {
    if((end=fscanf(fp,"%lf",&t[i])) == EOF) continue;
    for(j=0;j<nu;j++) fscanf(fp,"%lf",&q[i][j]);
    for(j=3;j<nu;j++) q[i][j] *= dtr;
/*
    q[i][0] = q[i][0] - 1.0;
    q[i][2] = q[i][0] + 0.75;
*/
  }
  fclose(fp);
  *n = i-1;

/* SCALE TIME TO SAME AS MODEL */
/*-----------------------------*/
/*	printf("subject tfinal = %lf\n",t[*n-1]); */
	norm = 0.56 / t[*n-1];
	for(i=0;i<*n;i++) t[i] *= norm;


  return(0);
}
/*=============================================================*/






/*=============================================================*/
/* mirror the generalized coordinates									*/
/*=============================================================*/
int mirror_(double qo[nq],double qn[nq])
{
	int i;
	double qd[nq];

	qd[0] =  qo[0];
	qd[1] =  qo[1];
	qd[2] =  qo[2];

	qd[3] = -qo[3];
	qd[4] = -qo[4];
	qd[5] =  qo[5];

	qd[6] =  qo[6];
	qd[7] = -qo[7];
	qd[8] = -qo[8];

	qd[9] =  qo[16];
	qd[10] =  qo[17];
	qd[11] =  qo[18];
	qd[12] =  qo[19];
	qd[13] =  qo[20];
	qd[14] =  qo[21];
	qd[15] =  qo[22];

	qd[16] =  qo[9];
	qd[17] =  qo[10];
	qd[18] =  qo[11];
	qd[19] =  qo[12];
	qd[20] =  qo[13];
	qd[21] =  qo[14];
	qd[22] =  qo[15];

	qd[23] =  qo[23];

	
	for (i=0;i<nq;i++) qn[i]=qd[i];

	return(0);
}





/*=============================================================*/
/* mirror activations or muscle forces									*/
/*=============================================================*/
int mirrormus_(double ain[54],double aout[54])
{
  int i;
  double adum[54];

  for (i=0;i<54;i++) adum[i] = ain[i];
  for (i=0;i<27;i++) {
    aout[i] = adum[i+27]; 
    aout[i+27] = adum[i];
  }

  return(0);
}
