#include "struct.h"

long long assignStructMemory(optdata &optObj, fcndata &fcnObj, double *optWorkspace, double *fcnWorkspace)
{
	long long memCnt = 0;

	// ---

	int varNum = fcnObj.varNum;

	double *nowPtr = optWorkspace;

	optObj.apHMat = nowPtr;
	nowPtr += varNum * varNum;
	memCnt += varNum * varNum;

	optObj.dirVec = nowPtr;
	nowPtr += varNum;
	memCnt += varNum;

	optObj.posNxt = nowPtr;
	nowPtr += varNum;
	memCnt += varNum;

	optObj.grdNxt = nowPtr;
	nowPtr += varNum;
	memCnt += varNum;

	optObj.dspVec = nowPtr;
	nowPtr += varNum;
	memCnt += varNum;

	optObj.dgdVec = nowPtr;
	nowPtr += varNum;
	memCnt += varNum;

	optObj.tmpVec = nowPtr;
	memCnt += varNum;

	return memCnt;
}
