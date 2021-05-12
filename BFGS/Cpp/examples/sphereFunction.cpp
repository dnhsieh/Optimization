#include "struct.h"

// global minimum  : 0
// global minimizer: (0, 0, ..., 0)

void objgrd(double *fcnVal, double *grdVec, double *posVec, fcndata &fcnObj)
{
	int varNum = fcnObj.varNum;

	*fcnVal = 0.0;

	for ( int varIdx = 0; varIdx < varNum; ++varIdx )
	{
		*fcnVal += posVec[varIdx] * posVec[varIdx];
		grdVec[varIdx] = 2.0 * posVec[varIdx];
	}

	return;
}
