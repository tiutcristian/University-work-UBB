clc;
clear all;
pause(1);

% Given data
X1 = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
X2 = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];

conf_level = input("confidence level = "); % 95-99% conf level
alpha = 1 - conf_level;

% a) Assuming σ1 = σ2, find a 100(1−α)% confidence interval for the difference of the true means.
n1 = length(X1);
n2 = length(X2);
X1_bar = mean(X1);
X2_bar = mean(X2);
sp = sqrt(((n1-1)*var(X1) + (n2-1)*var(X2))/(n1+n2-2));
ti = tinv(1-alpha/2,n1+n2-2);
thetal = X1_bar - X2_bar - ti*sp*sqrt(1/n1 + 1/n2);
thetau = X1_bar - X2_bar + ti*sp*sqrt(1/n1 + 1/n2);
fprintf("The %f confidence interval for the difference of the true means (with σ1 = σ2) is (%f,%f)\n\n", conf_level, thetal, thetau);

% b) Assuming σ1 != σ2, find a 100(1−α)% confidence interval for the difference of the true means.
v1 = s1^2/n1;
v2 = s2^2/n2;
thetal = X1_bar - X2_bar - sqrt(v1 + v2)*ti;
thetau = X1_bar - X2_bar + sqrt(v1 + v2)*ti;
fprintf("The %f confidence interval for the difference of the true means (with σ1 = σ2) is (%f,%f)\n\n", conf_level, thetal, thetau);

% c) Find a 100(1−α)% confidence interval for the ratio of the variances.
fl = finv(1-alpha/2,n1-1,n2-1);
fu = finv(alpha/2,n1-1,n2-1);
thetal = (s1^2/s2^2)/fl;
thetau = (s1^2/s2^2)/fu;
fprintf("The %f confidence interval for the ratio of the variances is (%f,%f)\n\n", conf_level, thetal, thetau);