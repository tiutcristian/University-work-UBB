% RECALL
% Discrete case
% pdf(k) = P(x=k)
% cdf(k) = P(x<=k)

% Continous case
% cdf(k) = P(X<=k) = Integral from -infinity to k of pdf(t)dt
% pdf(x) = P(x=k) = 0

% [abbr of the model] pdf*cdf/inv (where to parameter compute, of the model)

% rand U(0,1) all numbers have the same chance of appearing
% rand N(0,1) numbers in the middle have a higher chance of
% appearing(Gaussian Curve)

% [abr_of_the_model]rnd ( params_of_the_model, size_of_matrix )
unifrnd(0,1,2,3)
unifrnd(-1,1,2,3)
binornd(3,0.5,2,3)


% binostat --> get the functions ...

binostat(10,0.5)

