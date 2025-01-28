% Plot the graphs of the pdf and the cdf of a random variable X having a Binomial
% distribution of parameters n and p (given by the user).

n = input('n = ');
p = input('p = ');

x = 0:n;
y = binopdf(x, n, p);
z = binocdf(x, n, p);

figure;
subplot(2, 1, 1);
stem(x, y);
title('PDF of X');
xlabel('x');
ylabel('f(x)');
grid on;

subplot(2, 1, 2);
stairs(x, z);
title('CDF of X');
xlabel('x');
ylabel('F(x)');
grid on;
