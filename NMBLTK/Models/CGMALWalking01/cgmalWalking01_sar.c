/*
Generated 18-Jun-2003 17:59:45 by SD/FAST, Kane's formulation
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
    double vars[9],param[1],resid[1];
{
    int i;
    double pos[9],vel[9];

    for (i = 0; i < 9; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[9],param[10],resid[1];
{

    sdstate(param[9],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[9],param[10],resid[9];
{
    double pos[9],qdotdum[9];

    sdang2st(vars,pos);
    sdstate(param[9],pos,param);
    sduforce(param[9],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[0]);
}

sdstdyfunc(vars,param,resid)
    double vars[18],param[1],resid[9];
{
    double pos[9],qdotdum[9];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[9]);
    sduforce(param[0],pos,&vars[9]);
    sdperr(resid);
    sdverr(&resid[0]);
    sdderiv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[18],dstate[18],param[1];
    int *status;
{

    sdstate(time,state,&state[9]);
    sduforce(time,state,&state[9]);
    sdderiv(dstate,&dstate[9]);
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[18];
    int lock[9];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[1],param[1];
    int i;

    sdgentime(&i);
    if (i != 175922) {
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
    double time,state[18];
    int lock[9];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[1],param[10];
    int i;

    sdgentime(&i);
    if (i != 175922) {
        sdseterr(51,42);
    }
    for (i = 0; i < 9; i++) {
        param[i] = state[i];
    }
    param[9] = time;
    *err = 0;
    *fcnt = 0;
    sdvelfunc(&state[9],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

sdstatic(time,state,lock,ctol,tol,maxevals,fcnt,err)
    double time,state[18];
    int lock[9];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[9],param[10],jw[81],dw[648],rw[144];
    int iw[72],rooterr,i;

    sdgentime(&i);
    if (i != 175922) {
        sdseterr(52,42);
    }
    for (i = 0; i < 9; i++) {
        param[i] = state[9+i];
    }
    param[9] = time;
    sdroot(sdstatfunc,state,param,9,9,9,lock,
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
    double time,state[18];
    int lock[18];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[9],param[1];
    double jw[162],dw[1458],rw[225];
    int iw[108],rooterr,i;

    sdgentime(&i);
    if (i != 175922) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdroot(sdstdyfunc,state,param,9,18,9,lock,
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
    double *time,state[18],dstate[18],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[108],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 175922) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,18,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[18],dstate[18],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[72],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 175922) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,18,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
