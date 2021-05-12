#ifndef STRUCT_H
#define STRUCT_H

#include <cublas_v2.h>

struct optdata
{
	int    itrMax;
	double tolVal;
	double wolfe1;
	double wolfe2;
	bool   vbsFlg;

	double *d_apHMat;   // varNum * varNum
	double *d_dirVec;   // varNum
   double *d_posNxt;   // varNum
   double *d_grdNxt;   // varNum
   double *d_dspVec;   // varNum
   double *d_dgdVec;   // varNum
   double *d_tmpVec;   // varNum
};

struct fcndata
{
	int varNum;

	cublasHandle_t blasHdl;
};

#endif
