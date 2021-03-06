libDir    = '/usr/local/cuda/lib64';
structDir = '../src';

% ---

files = ...
{
'../src/LBFGS.cu', ...
'../src/assignStructMemory.cu', ...
'../src/getDirection.cu', ...
'../src/lineSearch.cu', ...
'runLBFGS.cu', ...
'bealeFunction.cu', ...
};

mexcuda(['-L', libDir], ['-I', structDir], files, '-lcublas', '-output', 'LBFGS_beale');

% ---

files = ...
{
'../src/LBFGS.cu', ...
'../src/assignStructMemory.cu', ...
'../src/getDirection.cu', ...
'../src/lineSearch.cu', ...
'runLBFGS.cu', ...
'rosenbrockFunction.cu', ...
};

mexcuda(['-L', libDir], ['-I', structDir], files, '-lcublas', '-output', 'LBFGS_rosenbrock');
