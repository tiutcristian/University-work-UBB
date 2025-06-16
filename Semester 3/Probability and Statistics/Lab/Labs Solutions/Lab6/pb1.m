% a)
% H0: µ = 8.5 (null hypothesis should always be with equality)
% H1: µ < 8.5 (in this case the standard is not met) (left-tailed test)

X = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
sigma = 5; % standard deviation
M = 8.5; % tested value
tail = -1; % tail = {-1(left-t), 0(bilateral), 1(right-t)}
alpha = input("a) alpha = "); % alpha - input from user

[H, p, ci, Zval] = ztest(X, M, sigma, alpha, tail); % because standard deviation is known
% h = {1 (if reject H0), 0 (otherwise)}
% p = P-value
% ci = a 100(1-alpha)% confidence interval
% zval = TS0

% for alpha = 0.05 --> reject (H = 1)
% for alpha = 0.01 --> don't reject (H = 0)

if H == 1
    disp("The standard is not met.")
else
    disp("The standard is met.")
end

ttalpha = norminv(alpha, 0, 1); % critical value (quantile)



% b)
% Without the assumption on σ, does the data suggest that, on average, the number
% of files stored exceeds 5.5? (same significance level)

% H0: µ = 5.5
% H1: µ > 5.5 (right-tailed test)
% sigma is unknown ==> t-test
M = 5.5;
tail = 1;
% alpha = input("b) alpha = ");
[H, p, ci, stats] = ttest(X, M, alpha, tail) % because standard deviation is not known
% stats = {
%   tstat, (TS0)
%   df, (degrees of freedom) = n - 1
%   sd, (standard deviation) ~ sigma
%   ci
% }

% for alpha = 0.05 --> reject (H = 1)
% for alpha = 0.01 --> don't reject (H = 0)

if H == 1
    disp("The number of files stored exceeds 5.5.")
else
    disp("The number of files stored does not exceed 5.5.")
end

n = length(X);
ttalpha = tinv(1-alpha, n); % critical value (quantile)