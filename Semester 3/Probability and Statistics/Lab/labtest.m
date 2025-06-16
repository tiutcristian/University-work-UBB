clc;
clear all;
pause(1);

supa = [1021 980 1017 988 1005 998 1014 985 995 1004 1030 1015 995 1023];
supb = [1070 970 993 1013 1006 1002 1014 997 1002 1010 975];

% a)
% H0: population variances are equal
% H1: population variances differ
alpha = 0.05;
tail = 0;
[H, P, CI, STATS] = vartest2(supa, supb, alpha, tail);

% statistical answer: We do not reject H0
% real answer: The population variances do not seem to differ
if H == 0
    fprintf('We do not reject H0: The population variances do not seem to differ\n')
else
    fprintf('Reject H0: The population variances seem to differ\n')
end

% used test: bilateral test

% Rejection region:
fprintf('Rejection region: (-inf,%f) U (%f,inf)\n', CI(1), CI(2));

% P-value:
fprintf('P-value: %f\n', P);

% observed value
fprintf('Observed value: TS0 = %f\n\n\n', STATS.fstat);


% b. find a 95% Cconfidence interval for the difference of the average weights
% from a) we know that the population variances are equal
lena = length(supa);
lenb = length(supb);
supa_bar = mean(supa);
supb_bar = mean(supb);
sp = sqrt(((lena-1)*var(supa) + (lenb-1)*var(supb))/(lena+lenb-2));
ti = tinv(1-alpha/2,lena+lenb-2);
thetal = supa_bar - supb_bar - ti*sp*sqrt(1/lena + 1/lenb);
thetau = supa_bar - supb_bar + ti*sp*sqrt(1/lena + 1/lenb);
fprintf("b) The 95%% confidence interval for the difference of the average weights is (%f,%f)\n\n", thetal, thetau);