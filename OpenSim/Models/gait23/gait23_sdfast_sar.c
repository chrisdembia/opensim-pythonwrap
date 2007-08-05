/*
Generated 31-Jul-2007 11:59:44 by SD/FAST, Kane's formulation
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
    double vars[27],param[1],resid[27];
{
    int i;
    double pos[27],vel[27];

    for (i = 0; i < 27; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdumotion(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[27],param[28],resid[27];
{

    sdstate(param[27],param,vars);
    sdumotion(param[27],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[27],param[28],resid[54];
{
    double pos[27],qdotdum[27];

    sdang2st(vars,pos);
    sdstate(param[27],pos,param);
    sdumotion(param[27],pos,param);
    sduforce(param[27],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[27]);
}

sdstdyfunc(vars,param,resid)
    double vars[54],param[1],resid[81];
{
    double pos[27],qdotdum[27];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[27]);
    sdumotion(param[0],pos,&vars[27]);
    sduforce(param[0],pos,&vars[27]);
    sdperr(resid);
    sdverr(&resid[27]);
    sdderiv(qdotdum,&resid[54]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[54],dstate[54],param[1];
    int *status;
{
    double err[27];
    int i;

    sdstate(time,state,&state[27]);
    sdumotion(time,state,&state[27]);
    sduforce(time,state,&state[27]);
    sdderiv(dstate,&dstate[27]);
    *status = 1;
    sdverr(err);
    for (i = 0; i < 27; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    sdperr(err);
    for (i = 0; i < 27; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[54];
    int lock[27];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[27],param[1];
    int i;
    double jw[729],dw[5832],rw[432];
    int iw[216],rooterr;

    sdgentime(&i);
    if (i != 115928) {
        sdseterr(50,42);
    }
    param[0] = time;
    sdroot(sdposfunc,state,param,27,27,0,lock,tol,tol,maxevals,
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
    double time,state[54];
    int lock[27];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[27],param[28];
    int i;
    double jw[729],dw[5832],rw[432];
    int iw[216],rooterr;

    sdgentime(&i);
    if (i != 115928) {
        sdseterr(51,42);
    }
    for (i = 0; i < 27; i++) {
        param[i] = state[i];
    }
    param[27] = time;
    sdroot(sdvelfunc,&state[27],param,27,27,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,verrs,fcnt,&rooterr);
    sdvelfunc(&state[27],param,verrs);
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
    double time,state[54];
    int lock[27];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[54],param[28],jw[1458],dw[13122],rw[621];
    int iw[324],rooterr,i;

    sdgentime(&i);
    if (i != 115928) {
        sdseterr(52,42);
    }
    for (i = 0; i < 27; i++) {
        param[i] = state[27+i];
    }
    param[27] = time;
    sdroot(sdstatfunc,state,param,54,27,27,lock,
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
    double time,state[54];
    int lock[54];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[81],param[1];
    double jw[4374],dw[36450],rw[1053];
    int iw[540],rooterr,i;

    sdgentime(&i);
    if (i != 115928) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdroot(sdstdyfunc,state,param,81,54,27,lock,
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
    double *time,state[54],dstate[54],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[324],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 115928) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,54,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[54],dstate[54],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[216],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 115928) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,54,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
