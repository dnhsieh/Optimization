varNum = 2;
memNum = 1000;
iniVec = zeros(varNum, 1);
itrMax = 1000;
tolVal = 1e-6;
wolfe1 = 0;
wolfe2 = 0.5;
vbsFlg = true;

% - - -

tic
[optPos, optObj, optGrd] = LBFGS_beale(iniVec, memNum, itrMax, tolVal, wolfe1, wolfe2, vbsFlg);
toc

