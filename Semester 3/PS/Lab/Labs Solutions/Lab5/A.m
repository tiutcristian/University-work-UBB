clc;
clear all;
pause(1);

X = [20 20 21 22 22 22 23*ones(1,6) 24*ones(1,5) 25*ones(1,9) 26 26 27 27];
Y = [75 75 75 76 76 77 77 78*ones(1,5) 79*ones(1,8) 80*ones(1,8) 81 82];

% means
fprintf("mean(X) = %.4f\n", mean(X));
fprintf("mean(Y) = %.4f\n", mean(Y));

% variances
VarX=var(X,1);
VarY=var(Y,1);
fprintf("var(X) = %.4f\n", VarX);
fprintf("var(Y) = %.4f\n", VarY);

% standard deviations
fprintf("std(X) = %.4f\n", sqrt(VarX));
fprintf("std(Y) = %.4f\n", sqrt(VarY));

% covariance
CovXY = cov(X,Y);
fprintf("Cov(X,Y) = %.4f\n", CovXY(1,2));

% correlation coefficient
CorrXY = corrcoef(X,Y);
fprintf("Corr(X,Y) = %.4f\n", CorrXY(1,2));