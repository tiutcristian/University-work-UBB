clc;
clear all;

p=-1;
while p>0.05 | p<0
    p=input("prob of success (p<=0.05)=")
end

for n=30:5:100
    lamda=n*p;

    k=0:n;
    px=binopdf(k,n,p);
    plot(k,px,"x");
    hold on;

    kreal=0:n;
    poissonpx=poisspdf(kreal,lamda);
    plot(kreal,poissonpx);
    hold off;

    title("The approximation of the Binomial Distrib. Model with the Normal Distrib. Model")
    legend("bino", "norm");

    pause(0.5);
end