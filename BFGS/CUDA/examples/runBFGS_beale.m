varNum   = 2;
d_iniVec = zeros(varNum, 1, 'gpuArray');
itrMax   = 1000;
tolVal   = 1e-6;
wolfe1   = 0;
wolfe2   = 0.5;
vbsFlg   = true;

% - - -

tic
[d_optPos, h_optObj, d_optGrd] = BFGS_beale(d_iniVec, itrMax, tolVal, wolfe1, wolfe2, vbsFlg);
toc

