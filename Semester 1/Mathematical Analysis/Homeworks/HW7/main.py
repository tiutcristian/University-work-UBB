"""
The integral from -inf to inf can be rewritten as the limit as a goes to infinity of the integral from -a to a.
Therefore we take the interval [-a,a] and divide it into n intervals and take the left ...
"""


import math
import numpy as np


def f(x: float):
    return math.e ** (-x ** 2)


# MAIN
print(f"sqrt(pi) = {math.sqrt(math.pi)}\n")

a = 10000

for a in [10, 100, 1000]:
    n = 10*a
    ls = np.linspace(-a, a, n+1)
    final_sum = 0
    for x in ls[:-1]:
        final_sum += f(x)
    final_sum *= 2*a/n
    print(f"a = {a}:\n    riemann_sum = {final_sum}")
