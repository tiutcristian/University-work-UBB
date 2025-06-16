import matplotlib.pyplot as plt
import numpy as np

from functions.base import BenchmarkFunction


def plot_surface(func: BenchmarkFunction, bounds, title="Function"):
    x = np.linspace(bounds[0], bounds[1], 100)
    y = np.linspace(bounds[0], bounds[1], 100)
    X, Y = np.meshgrid(x, y)
    Z = func.evaluate(X, Y)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X, Y, Z, cmap='viridis')
    ax.set_title(title)
    plt.show()

def plot_contour(func, bounds, title="Function"):
    x = np.linspace(bounds[0], bounds[1], 100)
    y = np.linspace(bounds[0], bounds[1], 100)
    X, Y = np.meshgrid(x, y)
    Z = func.evaluate(X, Y)

    plt.contourf(X, Y, Z, levels=50, cmap='viridis')
    plt.colorbar()
    plt.title(title)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()