#include "struct.h"

// global minimum  : 0
// global minimizer: (3, 0.5)

void objgrd(double *fcnVal, double *grdVec, double *posVec, fcndata &fcnObj)
{
	double xVal = posVec[0];
	double yVal = posVec[1];

	double f1Val = 1.5   + xVal * (-1.0 + yVal              );
	double f2Val = 2.25  + xVal * (-1.0 + yVal * yVal       );
	double f3Val = 2.625 + xVal * (-1.0 + yVal * yVal * yVal);

	*fcnVal = f1Val * f1Val + f2Val * f2Val + f3Val * f3Val;

	grdVec[0] =  2 * f1Val * (-1.0 + yVal              )
	           + 2 * f2Val * (-1.0 + yVal * yVal       )
	           + 2 * f3Val * (-1.0 + yVal * yVal * yVal);

	grdVec[1] =  2 * f1Val *       xVal
	           + 2 * f2Val * 2.0 * xVal * yVal
	           + 2 * f3Val * 3.0 * xVal * yVal * yVal;

	return;
}
