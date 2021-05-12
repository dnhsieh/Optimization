srcDir     = '../src';
structDir  = '../src';
matlabFlag = '-R2018a';

mex(matlabFlag, ['-I', structDir], [srcDir, '/*.cpp'], 'runBFGS.cpp', ...
    'bealeFunction.cpp', '-lmwblas', '-output', 'BFGS_beale');

mex(matlabFlag, ['-I', structDir], [srcDir, '/*.cpp'], 'runBFGS.cpp', ...
    'rosenbrockFunction.cpp', '-lmwblas', '-output', 'BFGS_rosenbrock');
