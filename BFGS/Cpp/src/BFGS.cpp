// Author: Dai-Ni Hsieh (dnhsieh@jhu.edu)
// Date  : 06/10/2020

#include <cstdio>
#include <cstring>
#include <cmath>
#include "blas.h"
#include "struct.h"

void objgrd(double *, double *, double *, fcndata &);

int  lineSearch(double *, double *, double *, double *, double, double, double, 
                double *, double *, double *, double &, int &, fcndata &);
void updateInverseHessian(double *, double *, double *, double *, int);

void uniformDiag(double *AMat, double fillVal, int varNum)
{
	memset(AMat, 0, sizeof(double) * varNum * varNum);

	for ( int varIdx = 0; varIdx < varNum; ++varIdx )
		AMat[varIdx * varNum + varIdx] = fillVal;

	return;
}

void vectorSubtract(double *v12Vec, double *v1Vec, double *v2Vec, int varNum)
{
	for ( int varIdx = 0; varIdx < varNum; ++varIdx )
		v12Vec[varIdx] = v1Vec[varIdx] - v2Vec[varIdx];

	return;
}

int BFGS(double *fcnNow, double *grdNow, double *posNow, optdata &optObj, fcndata &fcnObj)
{
	int     varNum = fcnObj.varNum;
	int     itrMax = optObj.itrMax;
	double  tolVal = optObj.tolVal;
	double  wolfe1 = optObj.wolfe1;
	double  wolfe2 = optObj.wolfe2;
	bool    vbsFlg = optObj.vbsFlg;

	double *apHMat = optObj.apHMat;
	double *dirVec = optObj.dirVec;
	double *posNxt = optObj.posNxt;
	double *grdNxt = optObj.grdNxt;
	double *dspVec = optObj.dspVec;
	double *dgdVec = optObj.dgdVec;
	double *tmpVec = optObj.tmpVec;
	double  fcnNxt;

	ptrdiff_t dotDim = varNum, incNum = 1;

	objgrd(fcnNow, grdNow, posNow, fcnObj);
	double grdSqu = ddot(&dotDim, grdNow, &incNum, grdNow, &incNum);
	double grdLen = sqrt(grdSqu);

	if ( vbsFlg )
	{
		printf("%5s   %13s  %13s  %13s  %9s\n", "iter", "f", "|grad f|", "step length", "fcn eval");
		char sepStr[65] = {0};
		memset(sepStr, '-', 62);
		printf("%s\n", sepStr);
		printf("%5d:  %13.6e  %13.6e\n", 0, *fcnNow, grdLen);
	}

	uniformDiag(apHMat, 1.0, varNum);

	for ( int itrIdx = 1; itrIdx <= itrMax; ++itrIdx )
	{
		if ( grdLen < tolVal )
			break;

		if ( itrIdx == 2 )
		{
			double dspDgd = ddot(&dotDim, dspVec, &incNum, dgdVec, &incNum);
			double dgdDgd = ddot(&dotDim, dgdVec, &incNum, dgdVec, &incNum);

			uniformDiag(apHMat, dspDgd / dgdDgd, varNum);
		}

		char      blas_op = 'N';
		ptrdiff_t apHRow = varNum, apHCol = varNum;
		double    alpVal = -1.0, btaVal = 0.0;
		dgemv(&blas_op, &apHRow, &apHCol, &alpVal, apHMat, &apHRow, 
		      grdNow, &incNum, &btaVal, dirVec, &incNum);

		double stpLen;
		int    objCnt;
		int    lineErr = lineSearch(posNow, grdNow, dirVec, fcnNow, wolfe1, wolfe2, tolVal,
		                            posNxt, grdNxt, &fcnNxt, stpLen, objCnt, fcnObj);
		if ( lineErr != 0 ) return 1;

		vectorSubtract(dspVec, posNxt, posNow, varNum);
		vectorSubtract(dgdVec, grdNxt, grdNow, varNum);

		if ( itrIdx >= 2 )
			updateInverseHessian(apHMat, dspVec, dgdVec, tmpVec, varNum);

		memcpy(posNow, posNxt, sizeof(double) * varNum);
		memcpy(grdNow, grdNxt, sizeof(double) * varNum);
		*fcnNow = fcnNxt;
		grdSqu  = ddot(&dotDim, grdNow, &incNum, grdNow, &incNum);
		grdLen  = sqrt(grdSqu);

		if ( vbsFlg )
			printf("%5d:  %13.6e  %13.6e  %13.6e  %9d\n", itrIdx, *fcnNow, grdLen, stpLen, objCnt);
	}

	return 0;
}
