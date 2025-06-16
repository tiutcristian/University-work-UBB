% To reach the maximum efficiency in performing an assembling operation in a manufacturing plant, 
% new employees are required to take a 1-month training course. A new method was suggested, 
% and the manager wants to compare the new method with the standard one, 
% by looking at the lengths of time required for employees to assemble a certain device. 
% They are given below (and assumed approximately normally distributed):

% Standard method:  46 37 39 48 47 44 35 31 44 37
% New method:       35 33 31 35 34 30 27 32 31 31

% a. At the 5% significance level, do the population variances seem to differ?
% b. Find a 95% confidence interval for the difference of the average assembling times.

% Data
standard = [46 37 39 48 47 44 35 31 44 37];
new = [35 33 31 35 34 30 27 32 31 31];

% a. 
alpha = 0.05;
[h, p, ci, stats] = vartest2(standard, new, alpha);
if h == 0
    fprintf('The population variances seem to be equal.\n');
else
    fprintf('The population variances seem to differ.\n');
end

% b.
alpha = 0.05;
[h, p, ci, stats] = ttest2(standard, new, alpha, 'both', 'unequal');
fprintf('The 95%% confidence interval for the difference of the average assembling times is (%f, %f).\n', ci(1), ci(2));