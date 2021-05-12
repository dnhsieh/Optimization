function HMat = updateInverseHessian(HMat, sVec, yVec)
%Equation (6.17) in Nocedal
%
% Author: Dai-Ni Hsieh (dnhsieh@jhu.edu)
% Date  : 05/20/2020

% s   = x_next - x_now = dspVec
% y   = (grad f)_next - (grad f)_now = dgdVec
% rho = 1 / (s^T y)

rhoVal = 1 / (sVec' * yVec);

HyVec  = HMat  * yVec;
yHyVal = yVec' * HyVec;

HMat = HMat + rhoVal * ( (-sVec * HyVec' - HyVec * sVec') ...
                        + (rhoVal * yHyVal + 1) * (sVec * sVec'));
