% A study is conducted to compare heat loss in glass pipes, versus steel pipes of the same size. 
% Various liquids at identical starting temperatures are run through segments of each type 
% and the heat loss (in °) is measured. These data result (normality of the two populations is assumed):
% Steel: 4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4
% Glass: 2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4

% a. At the 5% significance level, do the population variances seem to differ?
% b. At the same significance level, does it seem that on average, steel pipes lose more heat than glass pipes?

% a.
% H0: the population variances are equal
% H1: the population variances are not equal
alpha = 0.05;
steel = [4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4];
glass = [2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4];

[h, p, ci, stats] = vartest2(steel, glass, alpha);
if h == 0
    disp('The population variances are equal');
else
    disp('The population variances are not equal');
end

% b.
% H0: steel pipes lose the same amount of heat as glass pipes
% H1: steel pipes lose more heat than glass pipes
[h, p, ci, stats] = ttest2(steel, glass, alpha, 'right');
if h == 0
    disp('Steel pipes lose the same amount of heat as glass pipes');
else
    disp('Steel pipes lose more heat than glass pipes');
end