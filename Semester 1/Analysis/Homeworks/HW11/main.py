import numpy as np
import matplotlib.pyplot as plt


def f(x, y, a1, a2):
    return a1 * x ** 2 + a2 * y ** 2


def gradient(x, y, a1, a2):
    return 2 * a1 * x, 2 * a2 * y


A_values = {
    "minimum": (1, 2),
    "maximum": (-1, -2),
    "saddle point": (1, -2)
}

# generate 3D graphs
for it in A_values:
    key = it
    a1 = A_values[it][0]
    a2 = A_values[it][1]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x = np.linspace(-2, 2, 100)
    y = np.linspace(-2, 2, 100)
    x, y = np.meshgrid(x, y)
    z = f(x, y, a1, a2)

    ax.plot_surface(x, y, z, cmap='viridis')

    ax.set_title(key.title())
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')

    plt.show()

# generate 2D graphs
for it in A_values:
    key = it
    a1 = A_values[it][0]
    a2 = A_values[it][1]

    x = np.linspace(-2, 2, 100)
    y = np.linspace(-2, 2, 100)
    x, y = np.meshgrid(x, y)
    z = f(x, y, a1, a2)

    plt.contour(x, y, z, levels=3)

    random_points = [
        (-1.5, -1),
        (1.5, 1.25),
        (-0.75, 1.25)
    ]
    function_values = [f(point[0], point[1], a1, a2) for point in random_points]
    gradients = [gradient(point[0], point[1], a1, a2) for point in random_points]

    for i in range(len(random_points)):
        plt.scatter(random_points[i][0], random_points[i][1], color='red')
        plt.quiver(random_points[i][0], random_points[i][1], gradients[i][0], gradients[i][1], scale=30, color='blue')

    plt.title(key.title())
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.show()
