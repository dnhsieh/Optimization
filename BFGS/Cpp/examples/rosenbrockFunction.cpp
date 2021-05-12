#include <cstring>
#include "struct.h"

// global minimum  : 0
// global minimizer: (1, 1, ..., 1)

void objgrd(double *fcnVal, double *grdVec, double *posVec, fcndata &fcnObj)
{
	int varNum = fcnObj.varNum;

	*fcnVal = 0.0;
	memset(grdVec, 0, sizeof(double) * varNum);

	for ( int varIdx = 0; varIdx < varNum - 1; ++varIdx )
	{
		double x0 = posVec[varIdx    ];
		double x1 = posVec[varIdx + 1];
		double f0 = x1 - x0 * x0;
		double f1 = 1.0 - x0;
		
		*fcnVal += 100.0 * f0 * f0 + f1 * f1;

		grdVec[varIdx    ] += -400.0 * f0 * x0 - 2.0 * f1;
		grdVec[varIdx + 1] +=  200.0 * f0;
	}

	return;
}
