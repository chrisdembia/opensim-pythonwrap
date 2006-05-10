/*
Generated 20-Feb-2002 17:54:57 by SD/FAST, Kane's formulation
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
    double vars[23],param[1],resid[1];
{
    int i;
    double pos[24],vel[23];

    for (i = 0; i < 23; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[23],param[25],resid[1];
{

    sdstate(param[24],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[23],param[24],resid[23];
{
    double pos[24],qdotdum[24];

    sdang2st(vars,pos);
    sdstate(param[23],pos,param);
    sduforce(param[23],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[0]);
}

sdstdyfunc(vars,param,resid)
    double vars[46],param[1],resid[23];
{
    double pos[24],qdotdum[24];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[23]);
    sduforce(param[0],pos,&vars[23]);
    sdperr(resid);
    sdverr(&resid[0]);
    sdderiv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[47],dstate[47],param[1];
    int *status;
{

    sdstate(time,state,&state[24]);
    sduforce(time,state,&state[24]);
    sdderiv(dstate,&dstate[24]);
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[47];
    int lock[23];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[1],param[1];
    int i;

    sdgentime(&i);
    if (i != 175441) {
        sdseterr(50,42);
    }
    param[0] = time;
    sdst2ang(state,state);
    *err = 0;
    *fcnt = 0;
    sdposfunc(state,param,perrs);
    *fcnt = *fcnt+1;
    sdang2st(state,state);
}

/* This routine performs initial velocity analysis. */

sdinitvel(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[47];
    int lock[23];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[1],param[25];
    int i;

    sdgentime(&i);
    if (i != 175441) {
        sdseterr(51,42);
    }
    for (i = 0; i < 24; i++) {
        param[i] = state[i];
    }
    param[24] = time;
    *err = 0;
    *fcnt = 0;
    sdvelfunc(&state[24],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

sdstatic(time,state,lock,ctol,tol,maxevals,fcnt,err)
    double time,state[47];
    int lock[23];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[23],param[24],jw[529],dw[4232],rw[368];
    int iw[184],rooterr,i;

    sdgentime(&i);
    if (i != 175441) {
        sdseterr(52,42);
    }
    for (i = 0; i < 23; i++) {
        param[i] = state[24+i];
    }
    param[23] = time;
    sdst2ang(state,state);
    sdroot(sdstatfunc,state,param,23,23,23,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstatfunc(state,param,resid);
    *fcnt = *fcnt+1;
    sdang2st(state,state);
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
    double time,state[47];
    int lock[46];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[23],param[1],vars[46];
    double jw[1058],dw[9522],rw[575];
    int iw[276],rooterr,i;

    sdgentime(&i);
    if (i != 175441) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdst2ang(state,vars);
    for (i = 0; i < 23; i++) {
        vars[23+i] = state[24+i];
    }
    sdroot(sdstdyfunc,vars,param,23,46,23,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstdyfunc(vars,param,resid);
    *fcnt = *fcnt+1;
    sdang2st(vars,state);
    for (i = 0; i < 23; i++) {
        state[24+i] = vars[23+i];
    }
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
    double *time,state[47],dstate[47],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[282],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 175441) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,47,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[47],dstate[47],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[188],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 175441) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,47,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
