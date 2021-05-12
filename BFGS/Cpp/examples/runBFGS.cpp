// Author: Dai-Ni Hsieh (dnhsieh@jhu.edu)
// Date  : 05/20/2020

#include <cstring>
#include "mex.h"
#include "struct.h"

long long assignStructMemory(optdata &, fcndata &, double *, double *);
void      BFGS(double *, double *, double *, optdata &, fcndata &);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
	double *posIni;                    // inputs
	double *posNow, fcnNow, *grdNow;   // outputs

	optdata optObj;
	fcndata fcnObj;

	posIni        = mxGetDoubles(prhs[0]);
	optObj.itrMax =  mxGetScalar(prhs[1]);
	optObj.tolVal =  mxGetScalar(prhs[2]);
	optObj.wolfe1 =  mxGetScalar(prhs[3]);
	optObj.wolfe2 =  mxGetScalar(prhs[4]);
	optObj.vbsFlg =  mxGetScalar(prhs[5]);

	fcnObj.varNum = mxGetNumberOfElements(prhs[0]);

	if ( fcnObj.varNum > 1000000 )
	{
		mexErrMsgIdAndTxt("BFGS:numberOfVariables", 
		                  "The number of variables is over one million. Use LBFGS instead.");
	}

	plhs[0] = mxCreateDoubleMatrix(fcnObj.varNum, 1, mxREAL);
	plhs[2] = mxCreateDoubleMatrix(fcnObj.varNum, 1, mxREAL);
	posNow  = mxGetDoubles(plhs[0]);
	grdNow  = mxGetDoubles(plhs[2]);

	// ---

	long long optMemCnt = (long long) fcnObj.varNum * (fcnObj.varNum + 6);
	long long fcnMemCnt = 0;

	double *optWorkspace = NULL, *fcnWorkspace = NULL;
	optWorkspace = (double *) calloc(optMemCnt, sizeof(double));
	fcnWorkspace = (double *) calloc(fcnMemCnt, sizeof(double));

	if ( optWorkspace == NULL || fcnWorkspace == NULL )
	{
		mexErrMsgIdAndTxt("BFGS:memAllocate", 
		                  "Failed to allocate memory for BFGS.");
	}

	long long asgMemCnt = assignStructMemory(optObj, fcnObj, optWorkspace, fcnWorkspace);
	if ( asgMemCnt != optMemCnt + fcnMemCnt )
	{
		mexErrMsgIdAndTxt("BFGS:memAssign", 
		                  "Assigned memory (%d) mismatched the allocated memory (%d).", 
		                  asgMemCnt, optMemCnt + fcnMemCnt);
	}

	// ---

	memcpy(posNow, posIni, sizeof(double) * fcnObj.varNum);
	BFGS(&fcnNow, grdNow, posNow, optObj, fcnObj);

	plhs[1] = mxCreateDoubleScalar(fcnNow);

	// ---

	free(optWorkspace);
	free(fcnWorkspace);

	return;
}

