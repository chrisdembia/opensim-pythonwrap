/*
Generated 20-Nov-2002 10:26:07 by SD/FAST, Kane's formulation
(sdfast B.2.6 #70405) on machine ID 690ee52e
Copyright (c) 1990-1996 Symbolic Dynamics, Inc.
Copyright (c) 1990-1996 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
#include <math.h>

/* These routines are passed to sdroot. */

sdposfunc(vars,param,resid)
    double vars[2],param[1],resid[1];
{
    int i;
    double pos[2],vel[2];

    for (i = 0; i < 2; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[2],param[3],resid[1];
{

    sdstate(param[2],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[2],param[3],resid[2];
{
    double pos[2],qdotdum[2];

    sdang2st(vars,pos);
    sdstate(param[2],pos,param);
    sduforce(param[2],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[0]);
}

sdstdyfunc(vars,param,resid)
    double vars[4],param[1],resid[2];
{
    double pos[2],qdotdum[2];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[2]);
    sduforce(param[0],pos,&vars[2]);
    sdperr(resid);
    sdverr(&resid[0]);
    sdderiv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[4],dstate[4],param[1];
    int *status;
{

    sdstate(time,state,&state[2]);
    sduforce(time,state,&state[2]);
    sdderiv(dstate,&dstate[2]);
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[4];
    int lock[2];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[1],param[1];
    int i;

    sdgentime(&i);
    if (i != 102553) {
        sdseterr(50,42);
    }
    param[0] = time;
    *err = 0;
    *fcnt = 0;
    sdposfunc(state,param,perrs);
    *fcnt = *fcnt+1;
}

/* This routine performs initial velocity analysis. */

sdinitvel(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[4];
    int lock[2];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[1],param[3];
    int i;

    sdgentime(&i);
    if (i != 102553) {
        sdseterr(51,42);
    }
    for (i = 0; i < 2; i++) {
        param[i] = state[i];
    }
    param[2] = time;
    *err = 0;
    *fcnt = 0;
    sdvelfunc(&state[2],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

sdstatic(time,state,lock,ctol,tol,maxevals,fcnt,err)
    double time,state[4];
    int lock[2];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[2],param[3],jw[4],dw[32],rw[32];
    int iw[16],rooterr,i;

    sdgentime(&i);
    if (i != 102553) {
        sdseterr(52,42);
    }
    for (i = 0; i < 2; i++) {
        param[i] = state[2+i];
    }
    param[2] = time;
    sdroot(sdstatfunc,state,param,2,2,2,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstatfunc(state,param,resid);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs steady motion analysis. */

sdsteady(time,state,lock,ctol,tol,maxevals,fcnt,err)
    double time,state[4];
    int lock[4];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[2],param[1];
    double jw[8],dw[72],rw[50];
    int iw[24],rooterr,i;

    sdgentime(&i);
    if (i != 102553) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdroot(sdstdyfunc,state,param,2,4,2,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstdyfunc(state,param,resid);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs state integration. */

sdmotion(time,state,dstate,dt,ctol,tol,flag,err)
    double *time,state[4],dstate[4],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[24],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 102553) {
        sdseterr(54,42);
    }
    param[0] = ctol;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        step = dt;
        *flag = 0;
    }
    if (step <= 0.) {
        step = dt;
    }
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,4,tol,work,&vintgerr,&
      which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[4],dstate[4],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[16],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 102553) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,4,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
