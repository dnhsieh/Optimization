srcDir     = '../src';
structDir  = '../src';
matlabFlag = '-R2018a';

mex(matlabFlag, ['-I', structDir], [srcDir, '/*.cpp'], 'runLBFGS.cpp', ...
    'bealeFunction.cpp', '-lmwblas', '-output', 'LBFGS_beale');

mex(matlabFlag, ['-I', structDir], [srcDir, '/*.cpp'], 'runLBFGS.cpp', ...
    'rosenbrockFunction.cpp', '-lmwblas', '-output', 'LBFGS_rosenbrock');
