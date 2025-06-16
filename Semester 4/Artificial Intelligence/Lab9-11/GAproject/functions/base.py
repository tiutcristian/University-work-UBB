from abc import ABC, abstractmethod


class BenchmarkFunction(ABC):
    """Abstract base class for benchmark functions"""

    def __init__(self, name, domain, global_min):
        self.name = name
        self.domain = domain  # [(x_min, x_max), (y_min, y_max)]
        self.global_min = global_min

    @abstractmethod
    def evaluate(self, x, y):
        pass

    def get_domain(self):
        return self.domain