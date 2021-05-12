#ifndef STRUCT_H
#define STRUCT_H

struct optdata
{
	int    memNum;
	int    itrMax;
	double tolVal;
	double wolfe1;
	double wolfe2;
	bool   vbsFlg;

	double *dspMat;   // varNum * memNum
	double *dgdMat;   // varNum * memNum
	double *dirVec;   // varNum
   double *posNxt;   // varNum
   double *grdNxt;   // varNum
   double *dspVec;   // varNum
   double *dgdVec;   // varNum
   double *recVec;   // memNum
};

struct fcndata
{
	int varNum;
};

#endif
