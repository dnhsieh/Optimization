#ifndef STRUCT_H
#define STRUCT_H

struct optdata
{
	int    itrMax;
	double tolVal;
	double wolfe1;
	double wolfe2;
	bool   vbsFlg;

	double *apHMat;   // varNum * varNum
	double *dirVec;   // varNum
   double *posNxt;   // varNum
   double *grdNxt;   // varNum
   double *dspVec;   // varNum
   double *dgdVec;   // varNum
   double *tmpVec;   // varNum
};

struct fcndata
{
	int varNum;
};

#endif
