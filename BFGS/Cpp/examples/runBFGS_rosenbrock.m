varNum = 100;
iniVec = 3 * ones(varNum, 1);
itrMax = 1000;
tolVal = 1e-6;
wolfe1 = 0;
wolfe2 = 0.5;
vbsFlg = true;

% - - -

tic
[optPos, optObj, optGrd] = BFGS_rosenbrock(iniVec, itrMax, tolVal, wolfe1, wolfe2, vbsFlg);
toc

