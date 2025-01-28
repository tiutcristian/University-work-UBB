clc;
clear all;
pause(1);

X = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];

% Find confidence interval for the average number of files stored, knowing:

% a) sigma = 5
conf_level = input("a) confidence level (0.95 - 0.99) = "); % 95-99% conf level
alpha = 1 - conf_level;
m=mean(X);
sigma = 5;
n = length(X);
z1=norminv(1-alpha/2, 0, 1);
z2=norminv(alpha/2, 0, 1);
thetaL = m-sigma/sqrt(n) * z1;
thetaU = m-sigma/sqrt(n) * z2;
fprintf("the %f CI for the average member files is (%f,%f)\n\n", 100*conf_level, thetaL, thetaU);

% b) sigma unknown
conf_level = input("b) confidence level (0.95 - 0.99) = "); % 95-99% conf level
alpha = 1 - conf_level;
m=mean(X);
s = std(X);
n = length(X);
t1=tinv(1-alpha/2, n-1);
t2=tinv(alpha/2, n-1);
thetaL = m-s/sqrt(n) * t1;
thetaU = m-s/sqrt(n) * t2;
fprintf("the %f CI for the average member files is (%f,%f)\n\n", 100*conf_level, thetaL, thetaU);

% c) confidence intervals for the variance and for the standard deviation
% knowing files stored ~ normally distributed
conf_level = input("c) confidence level (0.95 - 0.99) = "); % 95-99% conf level
alpha = 1 - conf_level;
m=mean(X);
s = std(X);
n = length(X);
chi1=chi2inv(1-alpha/2, n-1);
chi2=chi2inv(alpha/2, n-1);
thetaL = (n-1)*s^2/chi1;
thetaU = (n-1)*s^2/chi2;
fprintf("the %f CI for the variance of member files is (%f,%f)\n", 100*conf_level, thetaL, thetaU);
fprintf("the %f CI for the standard deviation of member files is (%f,%f)\n\n", 100*conf_level, sqrt(thetaL), sqrt(thetaU));