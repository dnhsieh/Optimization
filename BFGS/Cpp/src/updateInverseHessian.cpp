// Equation (6.17) in Nocedal
//
// Author: Dai-Ni Hsieh (dnhsieh@jhu.edu)
// Date  : 05/20/2020

#include "blas.h"

void updateInverseHessian(double *HMat, double *sVec, double *yVec, double *HyVec, int varNum)
{
	// s   = x_next - n_now = dspVec
	// y   = (grad f)_next - (grad f)_now = dgdVec
	// rho = 1 / (s^T y)

	ptrdiff_t dotDim = varNum, incNum = 1;

	double    rhoInv = ddot(&dotDim, sVec, &incNum, yVec, &incNum);
	double    rhoVal = 1.0 / rhoInv;

	char      blas_op = 'N';
	ptrdiff_t HRow = varNum, HCol = varNum;
	double    alpVal = 1.0, btaVal = 0.0;
	dgemv(&blas_op, &HRow, &HCol, &alpVal, HMat, &HRow, yVec, &incNum, &btaVal, HyVec, &incNum);

	double yHyVal = ddot(&dotDim, yVec, &incNum, HyVec, &incNum);

	for ( int rowIdx = 0; rowIdx < varNum; ++rowIdx )
	{
		for ( int colIdx = 0; colIdx < varNum; ++colIdx )
		{
			HMat[rowIdx * varNum + colIdx] +=
			   rhoVal * (-sVec[rowIdx] * HyVec[colIdx] - HyVec[rowIdx] * sVec[colIdx]
			             + (rhoVal * yHyVal + 1.0) * sVec[rowIdx] * sVec[colIdx]);
		}
	}

	return;
}
