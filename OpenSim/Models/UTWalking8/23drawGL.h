#include <stdio.h>
#include <gl/gl.h>
#include <gl/device.h>

static float mat1[] = {
  AMBIENT, .5,.6,1.0,
  DIFFUSE, .5,.6,1.0,
  SPECULAR, .5,.6,1.0,
  LMNULL};
static float mat2[] = {
  AMBIENT, 0.9,0.9,0.9,
  DIFFUSE, 1.0,1.0,1.0,
  SPECULAR, .2,.2,.2,
  LMNULL};
static float matR[] = {
  AMBIENT, 0.7,0.2,0.1,
  DIFFUSE, 0.7,0.2,0.1,
  SPECULAR, 1.0,0.0,0.0,
  LMNULL};
static float matG[] = {
  AMBIENT, 0.1,0.9,0.1, 
  DIFFUSE, 0.1,0.9,0.1,
  SPECULAR, 0.1,0.9,0.1,
  LMNULL};
static float matB[] = {
  AMBIENT, 0.1,0.1,0.9, 
  DIFFUSE, 0.1,0.1,0.9,
  SPECULAR, 0.1,0.1,0.9,
  LMNULL};
static float matF1[] = {
  AMBIENT, 0.,0.,1.0,
  DIFFUSE, 0.,0.,1.0,
  SPECULAR, 0.,0.,1.0,
  LMNULL};
static float matF2[] = {
  AMBIENT, 0.1,0.1,0.9, 
  DIFFUSE, 0.1,0.1,0.9,
  SPECULAR, 0.1,0.1,0.9,
  LMNULL};
static float matY[] = {
  AMBIENT, 0.1,0.7,0.7, 
  DIFFUSE, 0.1,0.7,0.7,
  SPECULAR, 0.1,0.7,0.7,
  LMNULL};
static float lt1[] = {
  LCOLOR, 1.,1.,1.,
  POSITION, 0.,1.,1.,0.,
  LMNULL};
static float lm1[] = {
  LOCALVIEWER, 0,
  LMNULL};

typedef struct win_type {
   long id;
   long xorg,yorg;
   long xsiz,ysiz;
} win_type; 

static double origin[3] = {0.0,0.0,0.0};

static Matrix scenerotmtx = {
	{1.0,	0.0,	0.0,	0.0},
	{0.0,	1.0,	0.0,	0.0},
	{0.0,	0.0,	1.0,	0.0},
	{0.0,	0.0,	0.0,	1.0}
};

}; //namespace
static Matrix identitymtx = {
	{1.0,	0.0,	0.0,	0.0},
	{0.0,	1.0,	0.0,	0.0},
	{0.0,	0.0,	1.0,	0.0},
	{0.0,	0.0,	0.0,	1.0}
};
Device mousedev[2];
short mouseval[2];
static int mousex,mousey,oldmousex,oldmousey,viewdirty=1;
//static float transmtx[3] = {-0.2,-0.7,-1.6};  VIDEO ZOOM OF KNEE
//static float transmtx[3] = {-0.0,-0.8,-4.5};  VIDEO
static float transmtx[3] = {-0.0,-1.0,-5.0};
enum {NOTHING,TRANSLATE,ROTATE} orientmode;
void reorient();
void initializeBonePaths();
void showmus(int muson[54],int musbod[54][5],int order[54][5],
            double y[],
            double ro[54][3],double ri[54][3],
            double roe[54][3],double ria[54][3],double rob[54][3],
            double viaang[54],int viadof[54],double cylR[54],double cyl[54][3]);
void loadgfxrot(double location[3],double rotation[3][3],Matrix gfxrot);
int drawmodel(double pcom[3],double floorcom[3],int bodynum[],double ang[],
        double cyl1[54][3],double cyl2[54][3],double cylR[54],
        double btj[10][3],double itj[10][3],double pin[10][3][3]);
int drawsubject(int bodynum[],double ang[],
        double btj[10][3],double itj[10][3],double pin[10][3][3]);
