function [fcnVal, grdVec] = rosenbrockFunction(posVec)

% minimum  : 0
% minimizer: (1, 1, ..., 1)

posNxtVec = posVec(2 :  end     );
posNowVec = posVec(1 : (end - 1));

fcnVal = sum(100 * (posNxtVec - posNowVec.^2).^2 + (1 - posNowVec).^2);

grdVec = zeros(size(posVec));
grdVec(1 : (end - 1)) = 200 * (posNxtVec - posNowVec.^2) .* (-2 * posNowVec) - 2 * (1 - posNowVec);
grdVec(2 :  end     ) = grdVec(2 : end) + 200 * (posNxtVec - posNowVec.^2);
