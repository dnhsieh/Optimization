varNum   = 2;
memNum   = 1000;
d_iniVec = zeros(varNum, 1, 'gpuArray');
itrMax   = 1000;
tolVal   = 1e-6;
wolfe1   = 0;
wolfe2   = 0.5;
vbsFlg   = true;

% - - -

tic
[d_optPos, h_optObj, d_optGrd] = LBFGS_beale(d_iniVec, memNum, itrMax, tolVal, wolfe1, wolfe2, vbsFlg);
toc

