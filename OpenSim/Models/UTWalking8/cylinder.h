#ifndef _cylinder_h_
#define _cylinder_h_

#ifdef __cplusplus
extern "C" {
#endif


int path_inside_radius_(double P[2],double S[2],double R);
double distance_between_(double P[3],double S[3]);
int scylinder_(double *R,double P[3],double q[3],double t[3],double S[3],
               double *Pq,double *qt,double *tS,double *L,int *active);
int dcylinder_(double U[3],double Ru,double V[3],double Rv,double M[9],
              double P[3],double q[3],double Q[3],double T[3],double t[3],
              double S[3],
              double *Pq,double *qQ,double *QT,double *Tt,double *tS,
              double *L,int *active);


#ifdef __cplusplus
}
#endif

