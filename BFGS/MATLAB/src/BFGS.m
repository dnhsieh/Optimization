function [posNow, objNow, grdNow, pathMat] = BFGS(objgrdHdl, posNow, options)
%
% Author: Dai-Ni Hsieh (dnhsieh@jhu.edu)
% Date  : 06/10/2020

if nargin == 2, options.Verbose = false; end
options = setOptions(options);

wolfe1 = options.Wolfe1;
wolfe2 = options.Wolfe2;
itrMax = options.MaxIterations;
tolVal = options.OptimalityTolerance;

posNow = posNow(:);
varNum = length(posNow);

[objNow, grdNow] = objgrdHdl(posNow);
grdLen = norm(grdNow);

if options.Verbose
	fprintf('%5s   %13s  %13s  %13s  %9s\n', 'iter', 'f', '|grad f|', 'step length', 'fcn eval');
	fprintf('%s\n', repmat('-', 1, 62));
	fprintf('%5d:  %13.6e  %13.6e\n', 0, objNow, grdLen);
end

pathMat = [[posNow; grdNow], zeros(2 * varNum, itrMax)];
apHMat = eye(varNum);

for itrIdx = 1 : itrMax

	if grdLen < tolVal
		break;
	end

	if itrIdx == 2
		apHMat = (dspVec' * dgdVec) / (dgdVec' * dgdVec) * eye(varNum);
	end

	dirVec = -apHMat * grdNow;
	[objNxt, posNxt, grdNxt, stpLen, objCnt, sucFlg] = ...
	   lineSearch(objgrdHdl, objNow, posNow, grdNow, dirVec, wolfe1, wolfe2, tolVal);

	if ~sucFlg
		return;
	end

	dspVec = posNxt - posNow;
	dgdVec = grdNxt - grdNow;
	if itrIdx >= 2
		apHMat = updateInverseHessian(apHMat, dspVec, dgdVec);
	end

	posNow = posNxt;
	grdNow = grdNxt;
	objNow = objNxt;

	grdLen = norm(grdNow);

	pathMat(:, itrIdx + 1) = [posNow; grdNow];

	if options.Verbose
		fprintf('%5d:  %13.6e  %13.6e  %13.6e  %9d\n', itrIdx, objNow, grdLen, stpLen, objCnt);
	end

end

pathMat(:, (itrIdx + 1) : end) = [];


% ---------------------------------------------------------------------------- %
%                                 Subfunctions                                 %
% ---------------------------------------------------------------------------- %

function options = setOptions(options)

if ~isfield(options, 'Wolfe1')
	options.Wolfe1 = 0;
end

if ~isfield(options, 'Wolfe2')
	options.Wolfe2 = 0.5;
end

if ~isfield(options, 'MaxIterations')
	options.MaxIterations = 1000;
end

if ~isfield(options, 'OptimalityTolerance')
	options.OptimalityTolerance = 1e-6;
end

if ~isfield(options, 'Verbose')
	options.Verbose = false;
end
