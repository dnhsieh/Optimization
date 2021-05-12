// Author: Dai-Ni Hsieh (dnhsieh@jhu.edu)
// Date  : 05/20/2020

#include <cstring>
#include "mex.h"
#include "struct.h"

long long assignStructMemory(optdata &, fcndata &, double *, double *);
void      LBFGS(double *, double *, double *, optdata &, fcndata &);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
	double *posIni;                    // inputs
	double *posNow, fcnNow, *grdNow;   // outputs

	optdata optObj;
	fcndata fcnObj;

	posIni        = mxGetDoubles(prhs[0]);
	optObj.memNum =  mxGetScalar(prhs[1]);
	optObj.itrMax =  mxGetScalar(prhs[2]);
	optObj.tolVal =  mxGetScalar(prhs[3]);
	optObj.wolfe1 =  mxGetScalar(prhs[4]);
	optObj.wolfe2 =  mxGetScalar(prhs[5]);
	optObj.vbsFlg =  mxGetScalar(prhs[6]);

	fcnObj.varNum = mxGetNumberOfElements(prhs[0]);

	plhs[0] = mxCreateDoubleMatrix(fcnObj.varNum, 1, mxREAL);
	plhs[2] = mxCreateDoubleMatrix(fcnObj.varNum, 1, mxREAL);
	posNow  = mxGetDoubles(plhs[0]);
	grdNow  = mxGetDoubles(plhs[2]);

	// ---

	long long optMemCnt = (long long) fcnObj.varNum * (5 + 2 * optObj.memNum) + optObj.memNum;
	long long fcnMemCnt = 0;

	double *optWorkspace = NULL, *fcnWorkspace = NULL;
	optWorkspace = (double *) calloc(optMemCnt, sizeof(double));
	fcnWorkspace = (double *) calloc(fcnMemCnt, sizeof(double));

	if ( optWorkspace == NULL || fcnWorkspace == NULL )
	{
		mexErrMsgIdAndTxt("LBFGS:memAllocate", 
		                  "Failed to allocate memory for LBFGS.");
	}

	long long asgMemCnt = assignStructMemory(optObj, fcnObj, optWorkspace, fcnWorkspace);
	if ( asgMemCnt != optMemCnt + fcnMemCnt )
	{
		mexErrMsgIdAndTxt("LBFGS:memAssign", 
		                  "Assigned memory (%d) mismatched the allocated memory (%d).", 
		                  asgMemCnt, optMemCnt + fcnMemCnt);
	}

	// ---

	memcpy(posNow, posIni, sizeof(double) * fcnObj.varNum);
	LBFGS(&fcnNow, grdNow, posNow, optObj, fcnObj);

	plhs[1] = mxCreateDoubleScalar(fcnNow);

	// ---

	free(optWorkspace);
	free(fcnWorkspace);

	return;
}

