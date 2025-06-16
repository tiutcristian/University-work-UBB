% 10. A food store owner receives 1-liter water bottles from two suppliers. 
% After some complaints from customers, he wants to check the accuracy of the weights of 1-liter water bottles. 
% He finds the following weights (the two populations are approximately normally distributed):
% Supplier A:   1021 980 1017  988 1005  998 1014 985  995 1004 1030 1015 995 1023
% Supplier B:   1070 970  993 1013 1006 1002 1014 997 1002 1010  975

% a. At the 5% significance level, do the population variances seem to differ?
% b. At the same significance level, on average, does Supplier A seem to be more reliable?

% Given data
A = [1021 980 1017 988 1005 998 1014 985 995 1004 1030 1015 995 1023];
B = [1070 970 993 1013 1006 1002 1014 997 1002 1010 975];

% a. At the 5% significance level, do the population variances seem to differ?
alpha = 0.05;
tail = 0;
[H, P, CI, STATS] = vartest2(A, B, alpha, tail);
if H == 0
    disp('We do not reject H0: The population variances do not seem to differ')
else
    disp('Reject H0: The population variances seem to differ')
end

% b. At the same significance level, on average, does Supplier A seem to be more reliable?
tail = 1;
[H, P, CI, STATS] = ttest2(A, B, alpha, tail);
if H == 0
    disp('We do not reject H0: Supplier A does not seem to be more reliable')
else
    disp('Reject H0: Supplier A seems to be more reliable')
end