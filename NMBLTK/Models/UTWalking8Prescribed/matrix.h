
#ifdef __cplusplus
extern "C" {
#endif

int bgcopymtx_(int N,int M,double A[],double C[]);
int bgscalemtx_(int *N,int *M,double A[],double *b,double C[]);
int bgaddmtx_(int N,int M,double A[],double B[],double C[]);
int bgsubtractmtx_(int N,int M,double A[],double B[],double C[]);
int bgcrossvector_(double A[],double B[],double C[]);
int bgtransposemtx_(int *N,int *M,double A[],double B[]);
int bgmultiplymtx_(int N,int P,int M,double A[],double B[],double C[]);
int bgsolvelinear_(int *N,double A[],double X[],double B[]);
int bginvertmtx_(int N,double INP[],double INV[]);
int bgprintmtx_(int N, int M, double *A, char *title);

#ifdef __cplusplus
}
#endif
