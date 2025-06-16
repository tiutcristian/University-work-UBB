import numpy as np
from .base import BenchmarkFunction


class AckleyFunction(BenchmarkFunction):
    def __init__(self):
        domain = [(-5, 5), (-5, 5)]
        global_min = 0.0
        super().__init__("Ackley", domain, global_min)

    def evaluate(self, x, y):
        term1 = -20 * np.exp(-0.2 * np.sqrt(0.5 * (x ** 2 + y ** 2)))
        term2 = -np.exp(0.5 * (np.cos(2 * np.pi * x) + np.cos(2 * np.pi * y)))
        return term1 + term2 + 20 + np.e

    def bounds(self):
        return self.domain