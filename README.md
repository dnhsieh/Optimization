## Optimization

MATLAB, C++, and CUDA code for BFGS and LBFGS  

In each `examples` folder (e.g., BFGS/CUDA/examples), there are two examples: `rosenbrockFunction.*` and `bealeFunction.*` which implment the computation of the objective function and gradient. The files `runBFGS.*` and `runLBFGS.*` show how to call `BFGS.*` and `LBFGS.*`. Both C++ and CUDA code need to be compiled. The file `compile.m` in the `examples` folder can be used (with `libDir` modified) to compile the two examples and run tests `runBFGS_*.m` and `runLBFGS_*.m` in MATLAB.
