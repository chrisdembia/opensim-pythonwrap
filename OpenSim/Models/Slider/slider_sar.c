/*
Generated 17-Feb-2003 20:40:45 by SD/FAST, Kane's formulation
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
    double vars[1],param[1],resid[1];
{
    int i;
    double pos[1],vel[1];

    for (i = 0; i < 1; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[1],param[2],resid[1];
{

    sdstate(param[1],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[1],param[2],resid[1];
{
    double pos[1],qdotdum[1];

    sdang2st(vars,pos);
    sdstate(param[1],pos,param);
    sduforce(param[1],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[0]);
}

sdstdyfunc(vars,param,resid)
    double vars[2],param[1],resid[1];
{
    double pos[1],qdotdum[1];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[1]);
    sduforce(param[0],pos,&vars[1]);
    sdperr(resid);
    sdverr(&resid[0]);
    sdderiv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[2],dstate[2],param[1];
    int *status;
{

    sdstate(time,state,&state[1]);
    sduforce(time,state,&state[1]);
    sdderiv(dstate,&dstate[1]);
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[2];
    int lock[1];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[1],param[1];
    int i;

    sdgentime(&i);
    if (i != 204034) {
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
    double time,state[2];
    int lock[1];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[1],param[2];
    int i;

    sdgentime(&i);
    if (i != 204034) {
        sdseterr(51,42);
    }
    for (i = 0; i < 1; i++) {
        param[i] = state[i];
    }
    param[1] = time;
    *err = 0;
    *fcnt = 0;
    sdvelfunc(&state[1],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

sdstatic(time,state,lock,ctol,tol,maxevals,fcnt,err)
    double time,state[2];
    int lock[1];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[1],param[2],jw[1],dw[8],rw[16];
    int iw[8],rooterr,i;

    sdgentime(&i);
    if (i != 204034) {
        sdseterr(52,42);
    }
    for (i = 0; i < 1; i++) {
        param[i] = state[1+i];
    }
    param[1] = time;
    sdroot(sdstatfunc,state,param,1,1,1,lock,
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
    double time,state[2];
    int lock[2];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[1],param[1];
    double jw[2],dw[18],rw[25];
    int iw[12],rooterr,i;

    sdgentime(&i);
    if (i != 204034) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdroot(sdstdyfunc,state,param,1,2,1,lock,
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
    double *time,state[2],dstate[2],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[12],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 204034) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,2,tol,work,&vintgerr,&
      which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[2],dstate[2],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[8],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 204034) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,2,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
