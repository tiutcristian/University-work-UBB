clc;
clear all;
pause(1);

S=input("number of simulations=");
n=input("no. of trials=");
p=input("prob. of success=");

U=rand(n,S);
X=sum(U<p);

U_X=unique(X);
n_X=hist(X,length(U_X));
rel_freq=n_X/S;

plot(U_X, rel_freq, 'x');
hold on;
plot(0:n, binopdf(0:n, n, p), 'o');
hold off;

title("Bino");
legend("simulation","theoretical");