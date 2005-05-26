/*
Generated  1-May-2002 23:00:14 by SD/FAST, Kane's formulation
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
    double vars[6],param[1],resid[1];
{
    int i;
    double pos[7],vel[6];

    for (i = 0; i < 6; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[6],param[8],resid[1];
{

    sdstate(param[7],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[6],param[7],resid[6];
{
    double pos[7],qdotdum[7];

    sdang2st(vars,pos);
    sdstate(param[6],pos,param);
    sduforce(param[6],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[0]);
}

sdstdyfunc(vars,param,resid)
    double vars[12],param[1],resid[6];
{
    double pos[7],qdotdum[7];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[6]);
    sduforce(param[0],pos,&vars[6]);
    sdperr(resid);
    sdverr(&resid[0]);
    sdderiv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[13],dstate[13],param[1];
    int *status;
{

    sdstate(time,state,&state[7]);
    sduforce(time,state,&state[7]);
    sdderiv(dstate,&dstate[7]);
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[13];
    int lock[6];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[1],param[1];
    int i;

    sdgentime(&i);
    if (i != 230006) {
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
    double time,state[13];
    int lock[6];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[1],param[8];
    int i;

    sdgentime(&i);
    if (i != 230006) {
        sdseterr(51,42);
    }
    for (i = 0; i < 7; i++) {
        param[i] = state[i];
    }
    param[7] = time;
    *err = 0;
    *fcnt = 0;
    sdvelfunc(&state[7],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

sdstatic(time,state,lock,ctol,tol,maxevals,fcnt,err)
    double time,state[13];
    int lock[6];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[6],param[7],jw[36],dw[288],rw[96];
    int iw[48],rooterr,i;

    sdgentime(&i);
    if (i != 230006) {
        sdseterr(52,42);
    }
    for (i = 0; i < 6; i++) {
        param[i] = state[7+i];
    }
    param[6] = time;
    sdst2ang(state,state);
    sdroot(sdstatfunc,state,param,6,6,6,lock,
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
    double time,state[13];
    int lock[12];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[6],param[1],vars[12];
    double jw[72],dw[648],rw[150];
    int iw[72],rooterr,i;

    sdgentime(&i);
    if (i != 230006) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdst2ang(state,vars);
    for (i = 0; i < 6; i++) {
        vars[6+i] = state[7+i];
    }
    sdroot(sdstdyfunc,vars,param,6,12,6,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstdyfunc(vars,param,resid);
    *fcnt = *fcnt+1;
    sdang2st(vars,state);
    for (i = 0; i < 6; i++) {
        state[7+i] = vars[6+i];
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
    double *time,state[13],dstate[13],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[78],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 230006) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,13,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[13],dstate[13],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[52],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 230006) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,13,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
