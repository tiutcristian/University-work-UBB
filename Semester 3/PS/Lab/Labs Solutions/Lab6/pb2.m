% a. At the 5% significance level, is there evidence that the variances of the two populations are equal?
    % theta = sigma1^2 - sigma2^2
    % H0: sigma1^2 = sigma2^2
    % H1: sigma1^2 != sigma2^2

    X = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0]; % for Premium
    Y = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2]; % for Regular
    alpha = 0.05;
    tail = 0; % bilateral test
    [H, P, CI, STATS] = vartest2(X, Y, alpha, tail);
    % STATS = struct with fields:
    %     fstat = TS0
    %     df1 = length(X) - 1
    %     df2 = length(Y) - 1
    

    vartype = '';
    if H == 0
        disp('We do not reject H0: The variances of the two populations are equal')
        vartype = 'equal';
    else
        disp('Reject H0: The variances of the two populations are not equal')
        vartype = 'unequal';
    end

% b. Based on the result in part a., at the same significance level, does gas mileage seem to be higher, on average, when premium gasoline is used?
    % theta = µ1 - µ2
    % H0: theta = 0
    % H1: theta > 0 (right-tailed test) ==> tail = 1

    % from reslit in part a we get if sigma1^2 = sigma2^2 so if sigma1 = sigma2
    % based on the result, we choose how we proceed (sigma1 = sigma2 or sigma1 != sigma2)

    tail = 1; % right-tailed test
    % vartype = 'equal'(if sigma1 = sigma2) or 'unequal'(if sigma1 != sigma2)
    [H, P, CI, STATS] = ttest2(X, Y, alpha, tail, vartype);
    if H == 0
        disp('We do not reject H0: Gas mileage does not seem to be higher, on average, when premium gasoline is used')
    else
        disp('Reject H0: Gas mileage seems to be higher, on average, when premium gasoline is used')
    end