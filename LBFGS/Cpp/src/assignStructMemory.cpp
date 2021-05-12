#include "struct.h"

long long assignStructMemory(optdata &optObj, fcndata &fcnObj, double *optWorkspace, double *fcnWorkspace)
{
	long long memCnt = 0;

	// ---

	int varNum = fcnObj.varNum;
	int memNum = optObj.memNum;

	double *nowPtr = optWorkspace;

	optObj.dspMat = nowPtr;
	nowPtr += varNum * memNum;
	memCnt += varNum * memNum;

	optObj.dgdMat = nowPtr;
	nowPtr += varNum * memNum;
	memCnt += varNum * memNum;

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

	optObj.recVec = nowPtr;
	memCnt += memNum;

	return memCnt;
}
