#ifndef STRUCT_H
#define STRUCT_H

#include <cublas_v2.h>

struct optdata
{
	int    memNum;
	int    itrMax;
	double tolVal;
	double wolfe1;
	double wolfe2;
	bool   vbsFlg;

	double *d_dspMat;   // varNum * memNum
	double *d_dgdMat;   // varNum * memNum
	double *d_dirVec;   // varNum
   double *d_posNxt;   // varNum
   double *d_grdNxt;   // varNum
   double *d_dspVec;   // varNum
   double *d_dgdVec;   // varNum
   double *h_recVec;   // memNum
};

struct fcndata
{
	int varNum;

	cublasHandle_t blasHdl;
};

#endif
