% Nickel powders are used in coatings used to shield electronic equipment. 
% A random sample is selected, and the sizes of nickel particles in each coating are recorded (they are assumed to be approximately normally distributed):
% 3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96
% a. Find a 95% confidence interval for the average size of nickel particles.
% b. At the 1% significance level, on average, do these nickel particles seem to be smaller than 3?

% Given data
nickel = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

% a. Find a 95% confidence interval for the average size of nickel particles.
alpha = 0.05;
n = length(nickel);
x_bar = mean(nickel);
s = std(nickel);
z = abs(norminv(alpha/2));
CI = [x_bar - z * s/sqrt(n), x_bar + z * s/sqrt(n)]

% b. At the 1% significance level, on average, do these nickel particles seem to be smaller than 3?
% H0: mu = 3
% H1: mu < 3
alpha = 0.01;
M = 3;
tail = -1;
[H, p, ci, Zval] = ztest(nickel, M, s, alpha, tail);
if H == 0
    fprintf('Null hypothesis is not rejected. The nickel particles do not seem to be smaller than 3 on average.\n');
else
    fprintf('Null hypothesis is rejected. The nickel particles seem to be smaller than 3 on average.\n');
end