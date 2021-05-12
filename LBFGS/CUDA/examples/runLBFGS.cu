// Author: Dai-Ni Hsieh (dnhsieh@jhu.edu)
// Date  : 05/20/2020

#include "mex.h"
#include "gpu/mxGPUArray.h"
#include <cublas_v2.h>
#include "struct.h"

long long assignStructMemory(optdata &, fcndata &, double *, double *);
void      LBFGS(double *, double *, double *, optdata &, fcndata &);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
	mxInitGPU();

	mxGPUArray const *posIni;
	mxGPUArray       *posNow, *grdNow;

	optdata optObj;
	fcndata fcnObj;

	posIni        = mxGPUCreateFromMxArray(prhs[0]);
	optObj.memNum =            mxGetScalar(prhs[1]);
	optObj.itrMax =            mxGetScalar(prhs[2]);
	optObj.tolVal =            mxGetScalar(prhs[3]);
	optObj.wolfe1 =            mxGetScalar(prhs[4]);
	optObj.wolfe2 =            mxGetScalar(prhs[5]);
	optObj.vbsFlg =            mxGetScalar(prhs[6]);

	fcnObj.varNum = mxGPUGetNumberOfElements(posIni);

	mwSize const ndim = 1;
	mwSize const dims[1] = {(mwSize) fcnObj.varNum};
	posNow = mxGPUCreateGPUArray(ndim, dims, mxDOUBLE_CLASS, mxREAL, MX_GPU_DO_NOT_INITIALIZE);
	grdNow = mxGPUCreateGPUArray(ndim, dims, mxDOUBLE_CLASS, mxREAL, MX_GPU_DO_NOT_INITIALIZE);

	// ---

	// inputs
	double *d_posIni = (double *) mxGPUGetDataReadOnly(posIni);

	// outputs
	double *d_posNow = (double *) mxGPUGetData(posNow);
	double  h_fcnNow;
	double *d_grdNow = (double *) mxGPUGetData(grdNow);

	// ---

	long long optMemCnt = (long long) fcnObj.varNum * (5 + 2 * optObj.memNum);
	long long fcnMemCnt = 0;

	double *d_optWorkspace = NULL, *d_fcnWorkspace = NULL;
	cudaError_t optMemErr = cudaMalloc((void **) &d_optWorkspace, sizeof(double) * optMemCnt);
	cudaError_t fcnMemErr = cudaMalloc((void **) &d_fcnWorkspace, sizeof(double) * fcnMemCnt);

	if ( optMemErr != cudaSuccess || fcnMemErr != cudaSuccess )
	{
		mexErrMsgIdAndTxt("LBFGS:memAllocate", 
		                  "Failed to allocate memory for LBFGS.");
	}

	long long asgMemCnt = assignStructMemory(optObj, fcnObj, d_optWorkspace, d_fcnWorkspace);
	if ( asgMemCnt != optMemCnt + fcnMemCnt )
	{
		mexErrMsgIdAndTxt("LBFGS:memAssign", 
		                  "Assigned memory (%d) mismatched the allocated memory (%d).", 
		                  asgMemCnt, optMemCnt + fcnMemCnt);
	}

	optObj.h_recVec = (double *) calloc(optObj.memNum, sizeof(double));

	cublasCreate(&(fcnObj.blasHdl));

	// ---

	cudaMemcpy(d_posNow, d_posIni, sizeof(double) * fcnObj.varNum, cudaMemcpyDeviceToDevice);
	LBFGS(&h_fcnNow, d_grdNow, d_posNow, optObj, fcnObj);

	plhs[0] = mxGPUCreateMxArrayOnGPU(  posNow);
	plhs[1] =    mxCreateDoubleScalar(h_fcnNow);
	plhs[2] = mxGPUCreateMxArrayOnGPU(  grdNow);

	// ---

	mxGPUDestroyGPUArray(posIni);
	mxGPUDestroyGPUArray(posNow);
	mxGPUDestroyGPUArray(grdNow);

	free(optObj.h_recVec);
	cudaFree(d_optWorkspace);
	cudaFree(d_fcnWorkspace);

	cublasDestroy(fcnObj.blasHdl);

	return;
}

