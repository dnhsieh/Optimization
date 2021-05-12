objgrdHdl = @(x) rosenbrockFunction(x);

varNum = 100;
iniVec = 3 * ones(varNum, 1);
itrMax = 1000;
tolVal = 1e-6;

% - - -

addpath('../src');

options.MaxIterations       = itrMax;
options.OptimalityTolerance = tolVal;
options.Verbose             = true;

tic
[optPos, optObj, optGrd, hisMat] = BFGS(objgrdHdl, iniVec, options);
toc

rmpath('../src');
