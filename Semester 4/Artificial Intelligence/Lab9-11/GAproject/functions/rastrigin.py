import numpy as np

from functions.base import BenchmarkFunction


class RastriginFunction(BenchmarkFunction):
    def __init__(self):
        domain = [(-5.12, 5.12), (-5.12, 5.12)]
        global_min = 0.0
        super().__init__("Rastrigin", domain, global_min)

    def evaluate(self, x, y):
        return 20 + (x ** 2 - 10 * np.cos(2 * np.pi * x)) + (y ** 2 - 10 * np.cos(2 * np.pi * y))

    def bounds(self):
        return self.domain