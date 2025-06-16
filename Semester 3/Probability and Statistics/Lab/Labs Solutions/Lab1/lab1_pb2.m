% For x ∈[0, 3], graph on the same set of axes the functions x5/10, x sin x and cos x,
% in diﬀerent colors and linestyles. Display a title and a legend on your graph. Then
% plot them on diﬀerent pictures, but in the same window.

x=0:0.01:3;

y1=x.^5/10;
y2=x.*sin(x);
y3=cos(x);

% Same set of axes
plot(x, y1, 'r--')
hold on;
plot(x, y2, 'm')
plot(x, y3, 'b:')
hold off;

title('Graph of x^5/10, x sin x and cos x')
legend('x^5/10', 'x sin x', 'cos x')

% Different pictures, same window
figure
plot(x, y1, 'r--')
title('Graph of x^5/10')

figure
plot(x, y2, 'm')
title('Graph of x sin x')

figure
plot(x, y3, 'b:')
title('Graph of cos x')