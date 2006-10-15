/*
Generated  5-Oct-2006 12:36:48 by SD/FAST, Kane's formulation
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
    double vars[33],param[1],resid[33];
{
    int i;
    double pos[33],vel[33];

    for (i = 0; i < 33; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdumotion(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[33],param[34],resid[33];
{

    sdstate(param[33],param,vars);
    sdumotion(param[33],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[33],param[34],resid[66];
{
    double pos[33],qdotdum[33];

    sdang2st(vars,pos);
    sdstate(param[33],pos,param);
    sdumotion(param[33],pos,param);
    sduforce(param[33],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[33]);
}

sdstdyfunc(vars,param,resid)
    double vars[66],param[1],resid[99];
{
    double pos[33],qdotdum[33];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[33]);
    sdumotion(param[0],pos,&vars[33]);
    sduforce(param[0],pos,&vars[33]);
    sdperr(resid);
    sdverr(&resid[33]);
    sdderiv(qdotdum,&resid[66]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[66],dstate[66],param[1];
    int *status;
{
    double err[33];
    int i;

    sdstate(time,state,&state[33]);
    sdumotion(time,state,&state[33]);
    sduforce(time,state,&state[33]);
    sdderiv(dstate,&dstate[33]);
    *status = 1;
    sdverr(err);
    for (i = 0; i < 33; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    sdperr(err);
    for (i = 0; i < 33; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[66];
    int lock[33];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[33],param[1];
    int i;
    double jw[1089],dw[8712],rw[528];
    int iw[264],rooterr;

    sdgentime(&i);
    if (i != 123625) {
        sdseterr(50,42);
    }
    param[0] = time;
    sdroot(sdposfunc,state,param,33,33,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,perrs,fcnt,&rooterr);
    sdposfunc(state,param,perrs);
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

/* This routine performs initial velocity analysis. */

sdinitvel(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[66];
    int lock[33];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[33],param[34];
    int i;
    double jw[1089],dw[8712],rw[528];
    int iw[264],rooterr;

    sdgentime(&i);
    if (i != 123625) {
        sdseterr(51,42);
    }
    for (i = 0; i < 33; i++) {
        param[i] = state[i];
    }
    param[33] = time;
    sdroot(sdvelfunc,&state[33],param,33,33,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,verrs,fcnt,&rooterr);
    sdvelfunc(&state[33],param,verrs);
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

/* This routine performs static analysis. */

sdstatic(time,state,lock,ctol,tol,maxevals,fcnt,err)
    double time,state[66];
    int lock[33];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[66],param[34],jw[2178],dw[19602],rw[759];
    int iw[396],rooterr,i;

    sdgentime(&i);
    if (i != 123625) {
        sdseterr(52,42);
    }
    for (i = 0; i < 33; i++) {
        param[i] = state[33+i];
    }
    param[33] = time;
    sdroot(sdstatfunc,state,param,66,33,33,lock,
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
    double time,state[66];
    int lock[66];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[99],param[1];
    double jw[6534],dw[54450],rw[1287];
    int iw[660],rooterr,i;

    sdgentime(&i);
    if (i != 123625) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdroot(sdstdyfunc,state,param,99,66,33,lock,
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
    double *time,state[66],dstate[66],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[396],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 123625) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,66,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[66],dstate[66],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[264],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 123625) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,66,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
