clear all;
clc;
pause(0.5);

n=input("number of trials = ");
p=input("prob. of success = ");

%pdf
k=0:n;
px=binopdf(k,n,p);

%cdf
kreal=0:0.01:n;
fx=binocdf(kreal,n,p);

%plot
plot(k, px, '*');
hold on;
plot(kreal,fx);
hold off;
title("The binomial model");
legend("pdf", "cdf");
