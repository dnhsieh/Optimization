#include "struct.h"

long long assignStructMemory(optdata &optObj, fcndata &fcnObj, double *d_optWorkspace, double *d_fcnWorkspace)
{
	long long memCnt = 0;

	// ---

	int varNum = fcnObj.varNum;
	int memNum = optObj.memNum;

	double *d_nowPtr = d_optWorkspace;

	optObj.d_dspMat = d_nowPtr;
	d_nowPtr += varNum * memNum;
	memCnt += varNum * memNum;

	optObj.d_dgdMat = d_nowPtr;
	d_nowPtr += varNum * memNum;
	memCnt += varNum * memNum;

	optObj.d_dirVec = d_nowPtr;
	d_nowPtr += varNum;
	memCnt += varNum;

	optObj.d_posNxt = d_nowPtr;
	d_nowPtr += varNum;
	memCnt += varNum;

	optObj.d_grdNxt = d_nowPtr;
	d_nowPtr += varNum;
	memCnt += varNum;

	optObj.d_dspVec = d_nowPtr;
	d_nowPtr += varNum;
	memCnt += varNum;

	optObj.d_dgdVec = d_nowPtr;
	memCnt += varNum;

	return memCnt;
}
