%Pascal Distribution

clear all;
clc;
pause(0.5);

p=-1;

while p<0 || p>1
    p=input("What is the probability for succes=");
end

n=input("What is the number of successes");
S=input("What is the number of simulations=");

X=zeros(1,S);

for i=1:S
    % the i-th simulation
    % X(i) will contain the number of failures before the n-th succes
    % during the i-th simulation
    count = 0;
    while count < n %while we have a failure
        if rand >= p
            X(i)=X(i) + 1;
        else
            count = count + 1;
        end
    end
end

U_x=unique(X);
n_X=hist(X,length(U_x));
rel_freq=n_X/S;


plot(0:max(U_x),nbinpdf(0:max(U_x),n,p),'o');
hold on;
plot(U_x, rel_freq, 'x');
hold off;
legend("pascal", "simulation");

