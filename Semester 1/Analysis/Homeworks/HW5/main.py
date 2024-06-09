# convex function: f(x)=x^2 => f'(x) = 2*x
# Libraries that could help: numpy, matplotlib.
# results can be numerical or graphical
# pictures with the code and the results

"""
(a) Take a convex f and show that for small η the method converges to the minimum off.
(b) Show that by increasing η the method can converge faster (in fewer steps).
(c) Show that taking η too large might lead to the divergence of the method.
(d) Take a non-convex f and show that the method can get stuck in a local minimum.
"""

"""
import matplotlib.pyplot as plt

x1 = 3  # first element of the (x_n) sequence
no_of_elements = 1000
eta_values = [0.0005, 0.001, 0.002]

for eta in eta_values:
    tmp = [x1]
    for i in range(1, no_of_elements):
        x = tmp[i-1]
        tmp.append(x - eta*(4 * x**3 - 8*x))
    plt.plot(range(1, no_of_elements+1), tmp)
    plt.title(f"Plot for eta = {eta}")
    plt.xlabel("Index")
    plt.ylabel("Value")
    plt.show()
"""


import matplotlib.pyplot as plt
import math


def W(x: float) -> float:
    a = 1  # a initialized with 1
    b = 1  # b initialized with 1
    s = 0  # sum initialized with 0
    n = 100  # number of terms

    for i in range(n):
        s += a * math.cos(b * math.pi * x)
        a /= 3
        b *= 3
    return s


indexes = []
crt = 1/1000
for i in range(1500):
    indexes.append(crt)
    crt += 1/1000


ImW = []
for x in indexes:
    ImW.append(W(x))

plt.plot(indexes, ImW)
plt.title("Weierstrass function plot")
plt.xlabel("x")
plt.ylabel("W(x)")
plt.show()

