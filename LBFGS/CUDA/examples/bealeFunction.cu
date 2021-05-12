#include "struct.h"

// global minimum  : 0
// global minimizer: (3, 0.5)

__global__ void objgrdKernel(double *d_fcnVal, double *d_grdVec, double *d_posVec, int varNum)
{
	double xVal = d_posVec[0];
	double yVal = d_posVec[1];

	double f1Val = 1.5   + xVal * (-1.0 + yVal              );
	double f2Val = 2.25  + xVal * (-1.0 + yVal * yVal       );
	double f3Val = 2.625 + xVal * (-1.0 + yVal * yVal * yVal);

	*d_fcnVal = f1Val * f1Val + f2Val * f2Val + f3Val * f3Val;

	d_grdVec[0] =  2 * f1Val * (-1.0 + yVal              )
	             + 2 * f2Val * (-1.0 + yVal * yVal       )
	             + 2 * f3Val * (-1.0 + yVal * yVal * yVal);

	d_grdVec[1] =  2 * f1Val *       xVal
	             + 2 * f2Val * 2.0 * xVal * yVal
	             + 2 * f3Val * 3.0 * xVal * yVal * yVal;

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
