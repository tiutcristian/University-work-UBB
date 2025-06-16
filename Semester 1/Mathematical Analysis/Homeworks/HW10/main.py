import numpy as np
import matplotlib.pyplot as plt


def f(x, y, b):
    return 0.5 * (x**2 + b * y**2)


def gradient(x, y, b):
    df_dx = x
    df_dy = b * y
    return np.array([df_dx, df_dy])


def gradient_descent(x_init, y_init, b, num_iterations):
    x_values = [x_init]
    y_values = [y_init]
    for _ in range(num_iterations):
        gradient_at_point = gradient(x_values[-1], y_values[-1], b)
        step_size = (x_values[-1]**2 + b**2 * y_values[-1]**2) / (x_values[-1]**2 + b**3 * y_values[-1]**2)
        next_x = x_values[-1] - step_size * gradient_at_point[0]
        next_y = y_values[-1] - step_size * gradient_at_point[1]
        x_values.append(next_x)
        y_values.append(next_y)
    return x_values, y_values


b_values = [1, 1/2, 1/5, 1/10]
num_iterations = 20
for b in b_values:
    x_values, y_values = gradient_descent(4, 4, b, num_iterations)
    x = np.linspace(-5, 5, 400)
    y = np.linspace(-5, 5, 400)
    X, Y = np.meshgrid(x, y)
    Z = f(X, Y, b)
    plt.contour(X, Y, Z, levels=20)
    plt.plot(x_values, y_values)
    plt.title(f'Gradient descent for b={b}')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.show()
