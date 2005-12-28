/*
Generated 27-Dec-2005 16:51:39 by SD/FAST, Kane's formulation
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

void sdposfunc(double vars[33],
    double param[1],
    double resid[27])
{
    int i;
    double pos[34],vel[33];

    for (i = 0; i < 33; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdumotion(param[0],pos,vel);
    sdperr(resid);
}

void sdvelfunc(double vars[33],
    double param[35],
    double resid[27])
{

    sdstate(param[34],param,vars);
    sdumotion(param[34],param,vars);
    sdverr(resid);
}

void sdstatfunc(double vars[33],
    double param[34],
    double resid[60])
{
    double pos[34],qdotdum[34];

    sdang2st(vars,pos);
    sdstate(param[33],pos,param);
    sdumotion(param[33],pos,param);
    sduforce(param[33],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[27]);
}

void sdstdyfunc(double vars[66],
    double param[1],
    double resid[87])
{
    double pos[34],qdotdum[34];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[33]);
    sdumotion(param[0],pos,&vars[33]);
    sduforce(param[0],pos,&vars[33]);
    sdperr(resid);
    sdverr(&resid[27]);
    sdderiv(qdotdum,&resid[54]);
}

/* This routine is passed to the integrator. */

void sdmotfunc(double time,
    double state[67],
    double dstate[67],
    double param[1],
    int *status)
{
    double err[27];
    int i;

    sdstate(time,state,&state[34]);
    sdumotion(time,state,&state[34]);
    sduforce(time,state,&state[34]);
    sdderiv(dstate,&dstate[34]);
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

void sdassemble(double time,
    double state[67],
    int lock[33],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double perrs[27],param[1];
    int i;
    double jw[891],dw[7200],rw[486];
    int iw[240],rooterr;

    sdgentime(&i);
    if (i != 165119) {
        sdseterr(50,42);
    }
    param[0] = time;
    sdst2ang(state,state);
    sdroot(sdposfunc,state,param,27,33,0,lock,tol,tol,maxevals,
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
    double state[67],
    int lock[33],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double verrs[27],param[35];
    int i;
    double jw[891],dw[7200],rw[486];
    int iw[240],rooterr;

    sdgentime(&i);
    if (i != 165119) {
        sdseterr(51,42);
    }
    for (i = 0; i < 34; i++) {
        param[i] = state[i];
    }
    param[34] = time;
    sdroot(sdvelfunc,&state[34],param,27,33,0,lock,tol,tol,maxevals,
      jw,dw,rw,iw,verrs,fcnt,&rooterr);
    sdvelfunc(&state[34],param,verrs);
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
    double state[67],
    int lock[33],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[60],param[34],jw[1980],dw[17298],rw[717];
    int iw[372],rooterr,i;

    sdgentime(&i);
    if (i != 165119) {
        sdseterr(52,42);
    }
    for (i = 0; i < 33; i++) {
        param[i] = state[34+i];
    }
    param[33] = time;
    sdst2ang(state,state);
    sdroot(sdstatfunc,state,param,60,33,33,lock,
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
    double state[67],
    int lock[66],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[87],param[1],vars[66];
    double jw[5742],dw[46818],rw[1203];
    int iw[612],rooterr,i;

    sdgentime(&i);
    if (i != 165119) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdst2ang(state,vars);
    for (i = 0; i < 33; i++) {
        vars[33+i] = state[34+i];
    }
    sdroot(sdstdyfunc,vars,param,87,66,33,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstdyfunc(vars,param,resid);
    *fcnt = *fcnt+1;
    sdang2st(vars,state);
    for (i = 0; i < 33; i++) {
        state[34+i] = vars[33+i];
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
    double state[67],
    double dstate[67],
    double dt,
    double ctol,
    double tol,
    int *flag,
    int *err)
{
    static double step;
    double work[402],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 165119) {
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
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,67,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

void sdfmotion(double *time,
    double state[67],
    double dstate[67],
    double dt,
    double ctol,
    int *flag,
    double *errest,
    int *err)
{
    double work[268],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 165119) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,67,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}
