/*
Generated  9-Nov-2004 16:04:24 by SD/FAST, Kane's formulation
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
    double vars[45],param[1],resid[45];
{
    int i;
    double pos[45],vel[45];

    for (i = 0; i < 45; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdumotion(param[0],pos,vel);
    sdperr(resid);
}

sdvelfunc(vars,param,resid)
    double vars[45],param[46],resid[45];
{

    sdstate(param[45],param,vars);
    sdumotion(param[45],param,vars);
    sdverr(resid);
}

sdstatfunc(vars,param,resid)
    double vars[45],param[46],resid[90];
{
    double pos[45],qdotdum[45];

    sdang2st(vars,pos);
    sdstate(param[45],pos,param);
    sdumotion(param[45],pos,param);
    sduforce(param[45],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[45]);
}

sdstdyfunc(vars,param,resid)
    double vars[90],param[1],resid[135];
{
    double pos[45],qdotdum[45];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[45]);
    sdumotion(param[0],pos,&vars[45]);
    sduforce(param[0],pos,&vars[45]);
    sdperr(resid);
    sdverr(&resid[45]);
    sdderiv(qdotdum,&resid[90]);
}

/* This routine is passed to the integrator. */

sdmotfunc(time,state,dstate,param,status)
    double time,state[90],dstate[90],param[1];
    int *status;
{
    double err[45];
    int i;

    sdstate(time,state,&state[45]);
    sdumotion(time,state,&state[45]);
    sduforce(time,state,&state[45]);
    sdderiv(dstate,&dstate[45]);
    *status = 1;
    sdverr(err);
    for (i = 0; i < 45; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    sdperr(err);
    for (i = 0; i < 45; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    *status = 0;
}

/* This routine performs assembly analysis. */

sdassemble(time,state,lock,tol,maxevals,fcnt,err)
    double time,state[90];
    int lock[45];
    double tol;
    int maxevals,*fcnt,*err;
{
    double perrs[45],param[1];
    int i;
    double jw[2025],dw[16200],rw[720];
    int iw[360],rooterr;

    sdgentime(&i);
    if (i != 160357) {
        sdseterr(50,42);
    }
    param[0] = time;
    sdroot(sdposfunc,state,param,45,45,0,lock,tol,tol,maxevals,
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
    double time,state[90];
    int lock[45];
    double tol;
    int maxevals,*fcnt,*err;
{
    double verrs[45],param[46];
    int i;
    double jw[2025],dw[16200],rw[720];
    int iw[360],rooterr;

    sdgentime(&i);
    if (i != 160357) {
        sdseterr(51,42);
    }
    for (i = 0; i < 45; i++) {
        param[i] = state[i];
    }
    param[45] = time;
    sdroot(sdvelfunc,&state[45],param,45,45,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,verrs,fcnt,&rooterr);
    sdvelfunc(&state[45],param,verrs);
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
    double time,state[90];
    int lock[45];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[90],param[46],jw[4050],dw[36450],rw[1035];
    int iw[540],rooterr,i;

    sdgentime(&i);
    if (i != 160357) {
        sdseterr(52,42);
    }
    for (i = 0; i < 45; i++) {
        param[i] = state[45+i];
    }
    param[45] = time;
    sdroot(sdstatfunc,state,param,90,45,45,lock,
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
    double time,state[90];
    int lock[90];
    double ctol,tol;
    int maxevals,*fcnt,*err;
{
    double resid[135],param[1];
    double jw[12150],dw[101250],rw[1755];
    int iw[900],rooterr,i;

    sdgentime(&i);
    if (i != 160357) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdroot(sdstdyfunc,state,param,135,90,45,lock,
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
    double *time,state[90],dstate[90],dt,ctol,tol;
    int *flag,*err;
{
    static double step;
    double work[540],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 160357) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,90,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

sdfmotion(time,state,dstate,dt,ctol,flag,errest,err)
    double *time,state[90],dstate[90],dt,ctol;
    int *flag;
    double *errest;
    int *err;
{
    double work[360],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 160357) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,90,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
