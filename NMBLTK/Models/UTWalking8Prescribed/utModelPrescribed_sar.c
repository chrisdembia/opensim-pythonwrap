/*
Generated 08-Oct-2005 16:46:31 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
#include <math.h>

/* These routines are passed to sdroot. */

void sdposfunc(double vars[23],
    double param[1],
    double resid[17])
{
    int i;
    double pos[24],vel[23];

    for (i = 0; i < 23; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdumotion(param[0],pos,vel);
    sdperr(resid);
}

void sdvelfunc(double vars[23],
    double param[25],
    double resid[17])
{

    sdstate(param[24],param,vars);
    sdumotion(param[24],param,vars);
    sdverr(resid);
}

void sdstatfunc(double vars[23],
    double param[24],
    double resid[40])
{
    double pos[24],qdotdum[24];

    sdang2st(vars,pos);
    sdstate(param[23],pos,param);
    sdumotion(param[23],pos,param);
    sduforce(param[23],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[17]);
}

void sdstdyfunc(double vars[46],
    double param[1],
    double resid[57])
{
    double pos[24],qdotdum[24];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[23]);
    sdumotion(param[0],pos,&vars[23]);
    sduforce(param[0],pos,&vars[23]);
    sdperr(resid);
    sdverr(&resid[17]);
    sdderiv(qdotdum,&resid[34]);
}

/* This routine is passed to the integrator. */

void sdmotfunc(double time,
    double state[47],
    double dstate[47],
    double param[1],
    int *status)
{
    double err[17];
    int i;

    sdstate(time,state,&state[24]);
    sdumotion(time,state,&state[24]);
    sduforce(time,state,&state[24]);
    sdderiv(dstate,&dstate[24]);
    *status = 1;
    sdverr(err);
    for (i = 0; i < 17; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    sdperr(err);
    for (i = 0; i < 17; i++) {
        if (fabs(err[i]) > param[0]) {
            return;
        }
    }
    *status = 0;
}

/* This routine performs assembly analysis. */

void sdassemble(double time,
    double state[47],
    int lock[23],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double perrs[17],param[1];
    int i;
    double jw[391],dw[3200],rw[326];
    int iw[160],rooterr;

    sdgentime(&i);
    if (i != 164614) {
        sdseterr(50,42);
    }
    param[0] = time;
    sdst2ang(state,state);
    sdroot(sdposfunc,state,param,17,23,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,perrs,fcnt,&rooterr);
    sdposfunc(state,param,perrs);
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

/* This routine performs initial velocity analysis. */

void sdinitvel(double time,
    double state[47],
    int lock[23],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double verrs[17],param[25];
    int i;
    double jw[391],dw[3200],rw[326];
    int iw[160],rooterr;

    sdgentime(&i);
    if (i != 164614) {
        sdseterr(51,42);
    }
    for (i = 0; i < 24; i++) {
        param[i] = state[i];
    }
    param[24] = time;
    sdroot(sdvelfunc,&state[24],param,17,23,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,verrs,fcnt,&rooterr);
    sdvelfunc(&state[24],param,verrs);
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

void sdstatic(double time,
    double state[47],
    int lock[23],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[40],param[24],jw[920],dw[7938],rw[487];
    int iw[252],rooterr,i;

    sdgentime(&i);
    if (i != 164614) {
        sdseterr(52,42);
    }
    for (i = 0; i < 23; i++) {
        param[i] = state[24+i];
    }
    param[23] = time;
    sdst2ang(state,state);
    sdroot(sdstatfunc,state,param,40,23,23,lock,
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

void sdsteady(double time,
    double state[47],
    int lock[46],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[57],param[1],vars[46];
    double jw[2622],dw[21218],rw[813];
    int iw[412],rooterr,i;

    sdgentime(&i);
    if (i != 164614) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdst2ang(state,vars);
    for (i = 0; i < 23; i++) {
        vars[23+i] = state[24+i];
    }
    sdroot(sdstdyfunc,vars,param,57,46,23,lock,
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

void sdmotion(double *time,
    double state[47],
    double dstate[47],
    double dt,
    double ctol,
    double tol,
    int *flag,
    int *err)
{
    static double step;
    double work[282],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 164614) {
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

void sdfmotion(double *time,
    double state[47],
    double dstate[47],
    double dt,
    double ctol,
    int *flag,
    double *errest,
    int *err)
{
    double work[188],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 164614) {
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
