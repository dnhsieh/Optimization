objgrdHdl = @(x) bealeFunction(x);

varNum = 2;
memNum = 2;
iniVec = zeros(varNum, 1);
itrMax = 1000;
tolVal = 1e-6;

% - - -

addpath('../src');

options.MaxIterations       = itrMax;
options.OptimalityTolerance = tolVal;
options.Columns             = memNum;
options.Verbose             = true;

tic
[optPos, optObj, optGrd] = LBFGS(objgrdHdl, iniVec, options);
toc

rmpath('../src');
