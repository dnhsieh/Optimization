#include "struct.h"

// global minimum  : 0
// global minimizer: (1, 1, ..., 1)

__global__ void objgrdKernel(double *d_fcnVal, double *d_grdVec, double *d_posVec, int varNum)
{
	*d_fcnVal = 0.0;
	for ( int varIdx = 0; varIdx < varNum - 1; ++varIdx )
	{
		double x0 = d_posVec[varIdx    ];
		double x1 = d_posVec[varIdx + 1];
		double f0 = x1 - x0 * x0;
		double f1 = 1.0 - x0;
		
		*d_fcnVal += 100.0 * f0 * f0 + f1 * f1;

		d_grdVec[varIdx    ] += -400.0 * f0 * x0 - 2.0 * f1;
		d_grdVec[varIdx + 1] +=  200.0 * f0;
	}

	return;
}

void objgrd(double *h_fcnVal, double *d_grdVec, double *d_posVec, fcndata &fcnObj)
{
	int varNum = fcnObj.varNum;

	cudaMemset(d_grdVec, 0, sizeof(double) * varNum);

	// bad implementation, but enough for the purpose of illustration
	double *d_fcnVal;
	cudaMalloc((void **) &d_fcnVal, sizeof(double));
	objgrdKernel <<<1, 1>>> (d_fcnVal, d_grdVec, d_posVec, varNum);

	cudaMemcpy(h_fcnVal, d_fcnVal, sizeof(double), cudaMemcpyDeviceToHost);

	cudaFree(d_fcnVal);

	return;
}
