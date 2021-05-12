varNum = 100;
memNum = 10;
iniVec = 3 * ones(varNum, 1);
itrMax = 10000;
tolVal = 1e-6;
wolfe1 = 0;
wolfe2 = 0.5;
vbsFlg = true;

% - - -

tic
[optPos, optObj, optGrd] = LBFGS_rosenbrock(iniVec, memNum, itrMax, tolVal, wolfe1, wolfe2, vbsFlg);
toc

