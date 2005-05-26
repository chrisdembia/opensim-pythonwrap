int winfocus = 0;

#define nq 24
#define nu 23

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <gl/gl.h>
#include <device.h>
#include <string.h>
#include <SU/Models/UTWalk8IATaylor/23drawGL.h>
#include <SU/Models/UTWalk8IATaylor/23inputs.h>
#include <interpolate.h>
#include <vector.h>
#include <matrix.h>
#include <gfxlib.h>
#include <cylinder.h>


static int nt;
static int mirror=0;
static double ts[1000],qs[1000][nq],q[nq],u[nu];

static char *meshDir=NULL;
static char walkmodDir[512];
static char hatPth[512];
static char sacrumPth[512];
static char rpelvisPth[512];
static char rfemurPth[512];
static char rpatPth[512];
static char rtibiaPth[512];
static char rfibulaPth[512];
static char rhindfootPth[512];
static char rtoesPth[512];
static char lpelvisPth[512];
static char lfemurPth[512];
static char lpatPth[512];
static char ltibiaPth[512];
static char lfibulaPth[512];
static char lhindfootPth[512];
static char ltoesPth[512];



/*==========================================================================*/
/* DRAW THE WALKING MODEL AND HANDLE ANY EVENT QUEUEING                     */
/*==========================================================================*/
int draw23_(t,y,nst,pcom,btj,itj,pin,sforce,spt,
               muson,musbod,order,ro,ri,roe,ria,rob,viaang,viadof,cylR,cyl,
					xaccum)
    int *nst;
    double *t,y[],pcom[3],btj[10][3],itj[10][3],pin[10][3][3],
            sforce[10][3],spt[10][3];
    int muson[54],musbod[54][5],order[54][5],viadof[54];
    double ro[54][3],ri[54][3],roe[54][3],ria[54][3],rob[54][3],viaang[54];
    double cylR[54],cyl[54][3];
    double *xaccum;

{
int i,j;
char command[100];
static int frame=0;
//static int bodynum[10] = {1,2,3,4,5,6,7,8,9,10};
static int bodynum[10] = {1,2,3,4,5,6,7,8,9,10};
static double origin[3] = {0.0,0.0,0.0};
static struct win_type win[1];
double ang[1000];
double floorcom[3];
long dev;
short val;
static double rtd,dtr;
static double cyl1[54][3],cyl2[54][3];
static double lastT=0.0;
Coord vx,vy,vz;
Coord px,py,pz;

/*INITIALIZATIONS */
  if (*t<lastT) mirror++;
  lastT = *t;	
  if(win->id==0) {
	// BONE PATHS
	initializeBonePaths();
	
  /*Window */
    setupwin(win);
  /*Viacylinders */
    for (j=0;j<54;j++) {
      for (i=0;i<3;i++) {
        cyl1[j][i] = cyl[j][i];
        cyl2[j][i] = cyl[j][i];
      }
      cyl1[j][2] = cyl1[j][2] - 0.10;
      cyl2[j][2] = cyl2[j][2] + 0.10;
    }
  /*Constants */
    dtr = pi / 180.0;
    rtd = 1.0 / dtr;
  /*Subject Data */
    /*input23s_("s2.wlk03",&nt,ts,qs); */
    input23a_(&nt,ts,qs);
    for (i=0;i<nu;i++) u[i] = 0.0;
  }
  winset(win->id);
  viewdirty=1;

/*MOUSE POSITION */
  mousedev[0] = MOUSEX;
  mousedev[1] = MOUSEY;

/* Set the angle to the state vector: */
    for (i=3;i<*nst;i++) {
      ang[i] = 10.0 * rtd * y[i];
    }

/* Set the floorcom: */
    floorcom[0] = 0.0;
    floorcom[1] = -pcom[1];
    floorcom[2] = 0.0;


/* Draw the body:  */
   while(viewdirty) {
      czclear(0x000000,getgdesc(GD_ZMAX));

/*
		vx=*xaccum; vy=10.0; vz=10.0;
		px=*xaccum; py=1.0; vz=0.0;
		lookat(vx,vy,vz,px,py,pz,0.0);
*/

      loadmatrix(identitymtx);
      translate(transmtx[0],transmtx[1],transmtx[2]);
      multmatrix(scenerotmtx);

    /*Show the com:
       pushmatrix();
         translate(pcom[0],pcom[1],pcom[2]);
         lmbind(MATERIAL,5);
         showbody("../SEG/com1",0);
         newRGB(20,20,200);
         bgnline();
          v3d(origin);
          v3d(floorcom);
         endline();
       popmatrix(); */

    /*Show the muscles: */
       showmus(muson,musbod,order,y,ro,ri,roe,ria,rob,viaang,viadof,cylR,cyl);

    /*DRAW THE MODEL */
       drawmodel(pcom,floorcom,bodynum,ang,cyl1,cyl2,cylR,btj,itj,pin);
        	
    /*DRAW THE SUBJECT
       interpolate_(t,&nt,nq,ts,&qs[0][0],q);
			q[0] = q[0] + *xaccum;
       if ((mirror%2) == 1) mirror_(q,q);
       for (i=3;i<nq;i++) {
         ang[i] = 10.0*rtd*q[i];
       }
       sdang2st_(q,q);
       sdstate_(t,q,u); 
       pushmatrix();
       drawsubject(bodynum,ang,btj,itj,pin);
       popmatrix(); */

    /*SHOW GROUND FORCE VECTORS: */
      lmbind(MATERIAL,2);
      for (i=0;i<10;i++) {
        lmbind(MATERIAL,4);
        newRGB(50,50,250);
        showvec1(spt[i],sforce[i],100.0);
      }

    /*DRAW A GRID: */
      newRGB(20,60,20);
   	linewidth(1.0);
      grid(4.0,0.2);
      swapbuffers();
 		linewidth(4.0);
 	   if(0) {
	   	sprintf(command,"scrtest /tmp/clay/walk%d.rgb",frame);
	   	system(command);
			frame++;
	   }
		
      viewdirty=0;


      if ((qtest()) && (winfocus != win->id)) {
         dev=qread(&val);
         if (dev == INPUTCHANGE) winfocus = val;
      }


      while((qtest()) && (winfocus == win->id)) {
         switch(dev=qread(&val)) {
            case INPUTCHANGE:
               winfocus = val;
               break;
            case ESCKEY:
               if (!val) return(-1);
            case REDRAW:
               viewdirty = 1;
               break;
            case LEFTMOUSE: case MIDDLEMOUSE:
               if(val) {
                  if(dev==LEFTMOUSE) orientmode=ROTATE;
                  else 		  orientmode=TRANSLATE;
                  getdev(2,mousedev,mouseval);
                  mousex = mouseval[0];
                  mousey = mouseval[1];
                  oldmousex = mousex;
                  oldmousey = mousey;
                  qdevice(MOUSEX); qdevice(MOUSEY);
               }
               else {
                  orientmode = NOTHING;
                  unqdevice(MOUSEX); unqdevice(MOUSEY);
               }
               break;
            case MOUSEX: case MOUSEY:
               if(dev==MOUSEX) { oldmousex = mousex; mousex = val; }
               else	    { oldmousey = mousey; mousey = val; }
               if(orientmode!=NOTHING) {
                  reorient();
                  viewdirty=1;
               }
               break;
         }
      }
   }
return(0);
}







/*==========================================================================*/
/* SHOW THE MUSCLE PATHS                                                    */
/*==========================================================================*/
void showmus(int muson[54],int musbod[54][5],int order[54][5],
            double y[],
            double ro[54][3],double ri[54][3],
            double roe[54][3],double ria[54][3],double rob[54][3],
            double viaang[54],int viadof[54],double cylR[54],double cyl[54][3])
{
int i,j;
int active,bod[6],dof;
int R,G,B;
double origin[3] = {0.0,0.0,0.0};
double vec[6][3],location[3],rotation[3][3];
double atv[54],angle;

/*SHOULD STATES BE MIRRORED? */
  for (i=0;i<54;i++) atv[i]=y[101+i];
/*  if ((mirror%2) == 1) {
    printf("mirroring activations ...\n");
    mirrormus_(atv,atv);
  } */

/*SET CONSTANTS */
  G = 60;
  B = 60;

/*TURN ONLY GMAXL,GMAXM, AND ILPSO ON
  for (i=0;i<54;i++) muson[i] = 0;
  muson[16] = 1; */


/*LOOP THROUGH THE MUSCLES ----------------------------*/
  for (i=0;i<54;i++) {

    if (muson[i]) {

    /*SET THE COLOR */
      R = (int)(235.0*atv[i]) + 60.0;
      newRGB(R,G,B);
		/*lmbind(MATERIAL,3); */

    /*GET THE PATH OF THE MUSCLE */
      if (viadof[i] == -1) {
       viacylinder(musbod[i],order[i],ro[i],ri[i],roe[i],ria[i],rob[i],
                   cylR[i],cyl[i],bod,vec,&active);
      } else {
			dof = viadof[i] - 1;
			if(dof>=0) angle=y[dof];
			else       angle=0.0;
       viapoint(musbod[i],order[i],viadof[i],viaang[i],angle,
                                    ro[i],ri[i],roe[i],ria[i],rob[i],bod,vec);
      }

    /*TRANSFORM THE PATH POINTS TO THE GLOBAL FRAME USING SD-FAST */
      for (j=0;(bod[j]>0)&&(j<6);j++) sdpos_(&bod[j],vec[j],vec[j]);

    /*DRAW THE PATH */
      for (j=0;(bod[j+1]>0)&&(j+1<6);j++) {
        rod1(vec[j],vec[j+1],0.03);
      } 
       
       
    }
  }
/*------------------------------------------------------*/


}






/*==========================================================================*/
/* RETURN THE PATH OF A MUSCLE WHICH CROSSES A VIACYLINDER                  */
/*==========================================================================*/
int viacylinder(int musbod[5],int order[5],
                double ro[3],double ri[3],double roe[3],
                double ria[3],double rob[3],
                double cylR,double cyl[3],
                int bod[6],double vec[6][3],int *active)
{
int i,j,k;
int status;
int bodtmp[6],cylbod;
double location[3],rotation[3][3];
Matrix gfxrot;
double vectmp[6][3];
double ovec[3],ivec[3],Pcyl[3],Scyl[3],qcyl[3],tcyl[3];
double Pq[1],qt[1],tS[1],L[1];
static double origin[3] = {0.0,0.0,0.0};

/*ARRANGE THE PATH POINTS IN ORDER */
  cylbod = musbod[2];
  bod[0] = musbod[0];
  bod[1] = musbod[4];
  bod[2] = musbod[3];
  bod[3] = musbod[1];
  bod[4] = 0;
  bod[5] = 0;
  assignd(ro,3,vec[0]);
  assignd(ria,3,vec[1]);
  assignd(rob,3,vec[2]);
  assignd(ri,3,vec[3]);

/*REMOVE INACTIVE VIAPOINTS */
  for (i=0;i<6;i++) bodtmp[i] = 0;
  for (j=0,k=0;k<6;j++,k++) {
    while ((bod[k]==0)&&(k<6)) k++;
    if (k>5) k=5;
    bodtmp[j] = bod[k];
    assignd(vec[k],3,vectmp[j]);
  }


/*FIND THE VIACYLINDER POINTS */
/*----------------------------*/
/*ASSUME THAT THE VIACYLINDER IS BETWEEN THE ORIGIN FRAME AND THE NEXT 
  INSERTION FRAME.  NOTE THE CYLINDER IS IN THE 'roe' FRAME. */
/*TRANSFORM THE ORIGIN AND THE NEXT POINT INTO THE CYLINDER FRAME */
  sdtransform_(&bodtmp[0],vectmp[0],&cylbod,ovec);
  sdtransform_(&bodtmp[1],vectmp[1],&cylbod,ivec);
  for (i=0;i<3;i++) {
    Pcyl[i] = ovec[i] - cyl[i];
    Scyl[i] = ivec[i] - cyl[i];
  }
/*GET THE POINTS CONTACTING THE CYLINDER (q,t) */
  status = scylinder_(&cylR,Pcyl,qcyl,tcyl,Scyl,Pq,qt,tS,L,active);



/*IF THE VIACYLINDER IS ACTIVE */
  if (*active == 1) {
  /*DRAW THE PATH ALONG THE CIACYLINDER */
    pushmatrix();
    /*transform to cylinder body frame */
      sdpos_(&cylbod,origin,location);
      sdorient_(&cylbod,rotation);
      loadgfxrot(location,rotation,gfxrot);
      multmatrix(gfxrot);
    /*transform to the cylinder frame */
      translate(cyl[0],cyl[1],cyl[2]);
    /*draw an arc */
      cylarc(cylR,qcyl,tcyl,0.03);
    popmatrix();
  /*TRANSFORM THE VIACYLINDER POINTS BACK TO THE roe FRAME */
    for (i=0;i<3;i++) {
      qcyl[i] = qcyl[i] + cyl[i];
      tcyl[i] = tcyl[i] + cyl[i];
    }
  /*ARRANGE THE POINTS IN VEC AND BOD */
    bod[0] = bodtmp[0];
    bod[1] = musbod[2];
    bod[2] = musbod[2];
    bod[3] = bodtmp[1];
    bod[4] = bodtmp[2];
    bod[5] = bodtmp[3];
    assignd(vectmp[0],3,vec[0]);
    assignd(qcyl,3,vec[1]);
    assignd(tcyl,3,vec[2]);
    assignd(vectmp[1],3,vec[3]);
    assignd(vectmp[2],3,vec[4]);
    assignd(vectmp[3],3,vec[5]);
  }


/*IF THE VIACYLINDER IS NOT ACTIVE, REASSIGN THE POINTS TO vec AND bod */
  if (*active == 0) {
    for (j=0;j<5;j++) {
      bod[j] = bodtmp[j];
      assignd(vectmp[j],3,vec[j]);
    } 
  }


  return(0);
}






/*==========================================================================*/
/* RETURN THE PATH OF A MUSCLE WHICH PASSES THROUGH VIA POINTS              */
/*==========================================================================*/
int viapoint( int musbod[5],int order[5],int viadof,double viaang, double angle,
              double ro[3],double ri[3],
              double roe[3],double ria[3],double rob[3],
              int bod[6],double vec[6][3] )
{
int j,k;
int bodtmp[6];
double vectmp[6][3];

/*ASSIGN THE ORDER OF THE POINTS */
  for (j=0;j<5;j++) {
    bod[order[j]] = musbod[j];
    bodtmp[j] = 0.0;
  }

/*IDENTIFY INACTIVE SOMETIMES VIAPOINTS */
  if ((viadof==0) || (angle<viaang)) {  
    bod[order[2]] = 0;
  }

/*ASSIGN THE PATH TO vec[][] */
  assignd(ro,3,vec[order[0]]);
  assignd(ri,3,vec[order[1]]);
  assignd(roe,3,vec[order[2]]);
  assignd(rob,3,vec[order[3]]);
  assignd(ria,3,vec[order[4]]);

/*REMOVE INACTIVE VIAPOINTS */
  for (j=0,k=0;k<5;j++,k++) {
    if (bod[j]==0) k++;  
    if (k>4) k=4;
    bodtmp[j] = bod[k];
    assignd(vec[k],3,vectmp[j]); 
  } 

/*REASSIGN THE POINTS TO vec AND bod */
  for (j=0;j<5;j++) {
    bod[j] = bodtmp[j];
    assignd(vectmp[j],3,vec[j]);
  } 

  return(0);
}









/*==========================================================================*/
/* LOAD THE GRAPHICS TRANSFORMATION MATRIX                                  */
/*==========================================================================*/
void loadgfxrot(double location[3],double rotation[3][3],Matrix gfxrot)
{
int i,j;

  for (i=0;i<3;i++) {
    for (j=0;j<3;j++) {
      gfxrot[i][j] = (float)rotation[j][i];
    }
  }
  for (j=0;j<3;j++) {
    gfxrot[3][j] = (float)location[j];
  }
  for (i=0;i<3;i++) {
    gfxrot[i][3] = 0.0;
  }
  gfxrot[3][3] = 1.0;

}






/*==========================================================================*/
/* INITIALIZE A GRAPHICS WINDOW AND SET MODES FOR HIGH PERFORMANCE	    */
/*==========================================================================*/
int setupwin(struct win_type *win) {
   long scrnx,scrny;
   float aspect;

   scrnx = getgdesc(GD_XPMAX);
   scrny = getgdesc(GD_YPMAX);

/*
   win->xsiz = (long) (400);
   win->ysiz = (long) (1024);
*/
   win->xsiz = (long) (0.98*scrnx);
   win->ysiz = (long) (0.85*scrny);
   win->xorg = (long) (scrnx - win->xsiz);
   win->yorg = (long) (scrny - win->ysiz);
   aspect = (float)win->xsiz / (float)win->ysiz;

   foreground();
/*
   prefposition(scrnx-win->xsiz,scrnx,scrny-win->ysiz,scrny);
*/
   prefposition(20,win->xsiz+20,120,win->ysiz+120);
   win->id = winopen("Jump 54");
   /* printf("Jump 54 window id = %d \n",win->id); */

   RGBmode();
   doublebuffer(); 
   gconfig();
   lsetdepth(getgdesc(GD_ZMIN),getgdesc(GD_ZMAX));
   zbuffer(TRUE);
   nmode(NAUTO);
   mmode(MVIEWING);
   perspective(300,aspect,1.0,21.0);
   loadmatrix(identitymtx);
   drawmode(NORMALDRAW);
   shademodel(GOURAUD);

   zfunction(ZF_LEQUAL);
   czclear(0x000000,getgdesc(GD_ZMAX));
   swapbuffers(); 

   qdevice(INPUTCHANGE);
   qdevice(LEFTMOUSE);
   qdevice(MIDDLEMOUSE);
   qdevice(RIGHTMOUSE);
   qdevice(ESCKEY);

/* DEFINE LIGHTING CHARACTERISTICS */
   lmdef(DEFMATERIAL,1,4,mat1);
   lmdef(DEFMATERIAL,2,4,mat2);
   lmdef(DEFMATERIAL,3,4,matR);
   lmdef(DEFMATERIAL,4,4,matG);
   lmdef(DEFMATERIAL,5,4,matB);
   lmdef(DEFLIGHT,1,3,lt1);
   lmdef(DEFLMODEL,1,2,lm1);

/* BIND THE LIGHTING CHARACTERISTICS */
   lmbind(LIGHT0,1);
   lmbind(LMODEL,1); 

/* SET LINE WIDTH */
   linewidth(4.0);


   return(0);
}




/*==========================================================================*/
/* ADJUST CURRENT VIEWING ORIENTATION BASED ON MOUSE MOVEMENTS	            */
/*==========================================================================*/
void reorient() {
   long dx=mousex-oldmousex,dy=mousey-oldmousey;
   if(orientmode==ROTATE) {
      pushmatrix();
      loadmatrix(identitymtx);
      if(getbutton(ZKEY)) { rotate(dy,'z'); }
      else                { rotate(dx,'y'); rotate(-dy,'x'); }
      multmatrix(scenerotmtx);
      getmatrix(scenerotmtx);
      popmatrix();
   } else
   if(orientmode==TRANSLATE) {
      if(getbutton(ZKEY))   transmtx[2] += 0.01*(float)dy;
      else                { transmtx[0] += 0.01*(float)dx;
                            transmtx[1] += 0.01*(float)dy;
      }
   }
}




/*======================================================================*/
/* INITIALIZE THE BONE PATHS                                            */
/*======================================================================*/
void initializeBonePaths()
{
	// ENVIRONMENT
   meshDir = getenv("MESHES");
	if(meshDir==NULL) {
		strcpy(walkmodDir,".");
	} else {
		strcpy(walkmodDir,meshDir);
	}
	strcat(walkmodDir,"/WALKMOD/");

	// INDIVIDUAL BONES AND SEGMENTS
	sprintf(hatPth,"%s/hat",walkmodDir);
	sprintf(sacrumPth,"%s/sacrum",walkmodDir);
	sprintf(rpelvisPth,"%s/rpelvis",walkmodDir);
	sprintf(rfemurPth,"%s/rfemur",walkmodDir);
	sprintf(rpatPth,"%s/rpat",walkmodDir);
	sprintf(rtibiaPth,"%s/rtibia",walkmodDir);
	sprintf(rfibulaPth,"%s/rfibula",walkmodDir);
	sprintf(rhindfootPth,"%s/rhindfoot.10",walkmodDir);
	sprintf(rtoesPth,"%s/rtoes.10",walkmodDir);
	sprintf(lpelvisPth,"%s/lpelvis",walkmodDir);
	sprintf(lfemurPth,"%s/lfemur",walkmodDir);
	sprintf(lpatPth,"%s/lpat",walkmodDir);
	sprintf(ltibiaPth,"%s/ltibia",walkmodDir);
	sprintf(lfibulaPth,"%s/lfibula",walkmodDir);
	sprintf(lhindfootPth,"%s/lhindfoot.10",walkmodDir);
	sprintf(ltoesPth,"%s/ltoes.10",walkmodDir);
}



/*======================================================================*/
/* DRAW THE SUBJECT                                                     */
/*======================================================================*/
int drawsubject(int bodynum[],double ang[],
	double btj[10][3],double itj[10][3],double pin[10][3][3])
{
double location[3],rotation[3][3];
Matrix gfxrot;

    /*BODY 1 : pelvis */
       sdpos_(&bodynum[0],origin,location);
       sdorient_(&bodynum[0],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(sacrumPth,1);
        showbone(rpelvisPth,2);
        showbone(lpelvisPth,3);
        lmbind(MATERIAL,3);
        /* DRAW GMAX VIAPOINTS
        pushmatrix();
         translate(-0.0633,-0.0252,0.1002);
         showbody("../SEG/com3",12);
        popmatrix();
        pushmatrix();
         translate(-0.0822,-0.1024,0.0503);
         showbody("../SEG/com3",12);
        popmatrix(); */
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(itj[1],pin[1][0],1.0);
        pushmatrix();
         translate(itj[1][0],itj[1][1],itj[1][2]);
         rotate(ang[6],'z');
         lmbind(MATERIAL,1);
         newRGB(50,50,250);
         showvec1(origin,pin[1][1],1.0);
        popmatrix();
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(itj[2],pin[2][0],1.0);
        pushmatrix();
         translate(itj[2][0],itj[2][1],itj[2][2]);
         rotate(ang[9],'z');
         lmbind(MATERIAL,1);
         newRGB(50,50,250);
         showvec1(origin,pin[2][1],1.0);
        popmatrix();
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(itj[6],pin[6][0],1.0);
        pushmatrix();
         translate(itj[6][0],itj[6][1],itj[6][2]);
         rotate(ang[16],'z');
         lmbind(MATERIAL,1);
         newRGB(50,50,250);
         showvec1(origin,pin[6][1],1.0);
        popmatrix();
       popmatrix();

    /*BODY 2 : hat */
       sdpos_(&bodynum[1],origin,location);
       sdorient_(&bodynum[1],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(hatPth,2);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[1],pin[1][2],1.0);
       popmatrix();

    /*BODY 3 : rfemur */
       sdpos_(&bodynum[2],origin,location);
       sdorient_(&bodynum[2],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(rfemurPth,4);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[2],pin[2][2],1.0);
       popmatrix();

    /*BODY 4 : rtibia */
       sdpos_(&bodynum[3],origin,location);
       sdorient_(&bodynum[3],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(rtibiaPth,5);
        showbone(rfibulaPth,6);
        showbone(rpatPth,7);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[3],pin[3][0],1.0);
        showvec1(itj[4],pin[4][0],1.0);
       popmatrix();

    /*BODY 5 : rhindfoot */
       sdpos_(&bodynum[4],origin,location);
       sdorient_(&bodynum[4],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(rhindfootPth,5);
        lmbind(MATERIAL,3);
        newRGB(250,250,250);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[4],pin[4][1],1.0);
       popmatrix();

    /*BODY 6 : rtoes */
       sdpos_(&bodynum[5],origin,location);
       sdorient_(&bodynum[5],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(rtoesPth,6);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[5],pin[5][0],1.0);
       popmatrix();

    /*BODY 7 : lfemur */
       sdpos_(&bodynum[6],origin,location);
       sdorient_(&bodynum[6],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(lfemurPth,8);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[6],pin[6][2],1.0);
       popmatrix();

    /*BODY 8 : ltibia */
       sdpos_(&bodynum[7],origin,location);
       sdorient_(&bodynum[7],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(ltibiaPth,9);
        showbone(lfibulaPth,10);
        showbone(lpatPth,11);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[7],pin[7][0],1.0);
        showvec1(itj[8],pin[8][0],1.0);
       popmatrix();

    /*BODY 9 : lhindfoot */
       sdpos_(&bodynum[8],origin,location);
       sdorient_(&bodynum[8],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(lhindfootPth,9);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[8],pin[8][1],1.0);
       popmatrix();

    /*BODY 10 : ltoes */
       sdpos_(&bodynum[9],origin,location);
       sdorient_(&bodynum[9],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(ltoesPth,10);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[9],pin[9][0],1.0);
       popmatrix();

  return(0);
}









/*======================================================================*/
/* DRAW THE MODEL                                                       */
/*======================================================================*/
int drawmodel(double pcom[3],double floorcom[3],int bodynum[],double ang[],
	double cyl1[54][3],double cyl2[54][3],double cylR[54],
	double btj[10][3],double itj[10][3],double pin[10][3][3])
{
int status;
double location[3],rotation[3][3];
Matrix gfxrot;

    /*Show the com:
       pushmatrix();
         translate(pcom[0],pcom[1],pcom[2]);
         lmbind(MATERIAL,5);
         showbody("../SEG/com1",0);
         newRGB(20,20,200);
         bgnline();
          v3d(origin);
          v3d(floorcom);
         endline();
       popmatrix();
	*/

    /*BODY 1 : pelvis */
       sdpos_(&bodynum[0],origin,location);
       sdorient_(&bodynum[0],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(sacrumPth,1);
        showbone(rpelvisPth,2);
        showbone(lpelvisPth,3);
        lmbind(MATERIAL,3);
        /* DRAW GMAX VIAPOINTS
        pushmatrix();
         translate(-0.0633,-0.0252,0.1002);
         showbody("../SEG/com3",12);
        popmatrix();
        pushmatrix();
         translate(-0.0822,-0.1024,0.0503);
         showbody("../SEG/com3",12);
        popmatrix(); */
        lmbind(MATERIAL,1);
        status = rod1(cyl1[16],cyl2[16],2.0*cylR[16]);
        /* status = rod1(cyl1[15],cyl2[15],2.0*cylR[15]);
        status = rod1(cyl1[21],cyl2[21],2.0*cylR[21]); */
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(itj[1],pin[1][0],1.0);
        pushmatrix();
         translate(itj[1][0],itj[1][1],itj[1][2]);
         rotate(ang[6],'z');
         lmbind(MATERIAL,1);
         newRGB(50,50,250);
         showvec1(origin,pin[1][1],1.0);
        popmatrix();
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(itj[2],pin[2][0],1.0);
        pushmatrix();
         translate(itj[2][0],itj[2][1],itj[2][2]);
         rotate(ang[9],'z');
         lmbind(MATERIAL,1);
         newRGB(50,50,250);
         showvec1(origin,pin[2][1],1.0);
        popmatrix();
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(itj[6],pin[6][0],1.0);
        pushmatrix();
         translate(itj[6][0],itj[6][1],itj[6][2]);
         rotate(ang[16],'z');
         lmbind(MATERIAL,1);
         newRGB(50,50,250);
         showvec1(origin,pin[6][1],1.0);
        popmatrix();
       popmatrix();

    /*BODY 2 : hat */
       sdpos_(&bodynum[1],origin,location);
       sdorient_(&bodynum[1],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(hatPth,2);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[1],pin[1][2],1.0);
       popmatrix();

    /*BODY 3 : rfemur */
       sdpos_(&bodynum[2],origin,location);
       sdorient_(&bodynum[2],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(rfemurPth,4);
        lmbind(MATERIAL,1);
        status = rod1(cyl1[11],cyl2[11],2.0*cylR[11]);
        newRGB(50,50,250);
        showvec1(btj[2],pin[2][2],1.0);
       popmatrix();

    /*BODY 4 : rtibia */
       sdpos_(&bodynum[3],origin,location);
       sdorient_(&bodynum[3],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(rfibulaPth,6);
        showbone(rtibiaPth,5);
        showbone(rpatPth,7);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[3],pin[3][0],1.0);
        showvec1(itj[4],pin[4][0],1.0);
       popmatrix();

    /*BODY 5 : rhindfoot */
       sdpos_(&bodynum[4],origin,location);
       sdorient_(&bodynum[4],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(rhindfootPth,5);
        lmbind(MATERIAL,3);
        newRGB(250,250,250);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[4],pin[4][1],1.0);
       popmatrix();

    /*BODY 6 : rtoes */
       sdpos_(&bodynum[5],origin,location);
       sdorient_(&bodynum[5],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(rtoesPth,6);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[5],pin[5][0],1.0);
       popmatrix();

    /*BODY 7 : lfemur */
       sdpos_(&bodynum[6],origin,location);
       sdorient_(&bodynum[6],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(lfemurPth,8);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[6],pin[6][2],1.0);
       popmatrix();

    /*BODY 8 : ltibia */
       sdpos_(&bodynum[7],origin,location);
       sdorient_(&bodynum[7],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,2);
        showbone(ltibiaPth,9);
        showbone(lfibulaPth,10);
        showbone(lpatPth,11);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[7],pin[7][0],1.0);
        showvec1(itj[8],pin[8][0],1.0);
       popmatrix();

    /*BODY 9 : lhindfoot */
       sdpos_(&bodynum[8],origin,location);
       sdorient_(&bodynum[8],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(lhindfootPth,9);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[8],pin[8][1],1.0);
       popmatrix();

    /*BODY 10 : ltoes */
       sdpos_(&bodynum[9],origin,location);
       sdorient_(&bodynum[9],rotation);
       loadgfxrot(location,rotation,gfxrot);
       pushmatrix();
        multmatrix(gfxrot);
        lmbind(MATERIAL,5);
        //showbody("../SEG/com2",11);
        lmbind(MATERIAL,1);
        showbody(ltoesPth,10);
        lmbind(MATERIAL,1);
        newRGB(50,50,250);
        showvec1(btj[9],pin[9][0],1.0);
       popmatrix();

  return(0);
}
