clear all;
clc;
pause(0.5);

n = 3;
p = 0.5;

% a)
k=0:3;
fx=binopdf(k,n,p);
m=[k;fx]

% b)
kreal=0:0.01:3;
px=binocdf(kreal,n,p);
% plot(kreal, px);
% title("Cumulative distribution function");
% legend("CDF");

% c)
fprintf("c)\n\tP(X=0)=%.3f\n", binopdf(0,n,p));
fprintf("\tP(X!=1)=%.3f\n", 1 - binopdf(1,n,p));

% d)
fprintf("d)\n\tP(X<=2)=%.3f\n", binocdf(2,n,p));
fprintf("\tP(X<2)=%.3f\n", binocdf(2,n,p)-binopdf(2,n,p));

% e)
fprintf("e)\n\tP(X>=1)=%.3f\n", 1-(binocdf(1,n,p)-binopdf(1,n,p)));
fprintf("\tP(X>1)=%.3f\n", 1-binocdf(1,n,p));

% f)
