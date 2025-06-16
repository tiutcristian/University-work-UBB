clc;
clear all;
pause(1);

S=input("number of simulations=");
p=input("prob. of success=");

X=zeros(1,S);

for i=1:S
    % the i-th simulation
    nofailures=0;
    while rand>=p
        nofailures=nofailures+1;
    end
    X(i)=nofailures;
end

U_X=unique(X);
n_X=hist(X,length(U_X));
rel_freq=n_X/S;

plot(U_X, rel_freq, 'x');
hold on;
plot(0:max(U_X), geopdf(0:max(U_X), p), 'o');
hold off;

title("Geo");
legend("simulation","theoretical");