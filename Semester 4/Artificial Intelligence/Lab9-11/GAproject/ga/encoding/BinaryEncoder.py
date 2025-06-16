import numpy as np

from config import CONFIG


def decode(bits, bounds):
    """
    Decode a binary string into a real number within specified bounds.
    :param bits: binary string represented as a list of bits (0s and 1s)
    :param bounds: tuple of (min, max) bounds for the decoded value
    :return: decoded real number within the specified bounds
    """
    integer = int("".join(str(b) for b in bits), 2)
    max_val = 2 ** len(bits) - 1
    return bounds[0] + (bounds[1] - bounds[0]) * integer / max_val


class BinaryEncoder:
    """
    Binary Encoding for Genetic Algorithms.
    """
    def __init__(self, x_bounds, y_bounds, config):
        self.config = config
        self.size = self.config["population_size"]
        self.length = self.config["binary_length"]
        self.x_bounds = x_bounds
        self.y_bounds = y_bounds
        self.crossover_method = self.config["crossover_method"]

    def initialize_population(self):
        """
        Initialize a population of binary strings.
        Returns: a numpy array of shape (population_size, length * 2)
        """
        return np.random.randint(0, 2, (self.size, self.length * 2))

    def crossover(self, p1, p2, crossover_rate):
        """
        Perform crossover between two binary strings based on the crossover rate.
        :param p1: first parent binary string
        :param p2: second parent binary string
        :param crossover_rate: probability of performing crossover
        :return: two offspring binary strings
        """
        if np.random.rand() > crossover_rate:
            return p1.copy(), p2.copy()
        if self.crossover_method == "1point":
            return self.one_point_crossover(p1, p2)
        return self.two_point_crossover(p1, p2)

    def one_point_crossover(self, p1, p2):
        """
        Perform one-point crossover between two binary strings.
        :param p1: first parent binary string
        :param p2: second parent binary string
        :return: two offspring binary strings
        """
        point = np.random.randint(1, len(p1))
        c1 = np.concatenate([p1[:point], p2[point:]])
        c2 = np.concatenate([p2[:point], p1[point:]])
        return c1, c2

    def two_point_crossover(self, p1, p2):
        """
        Perform two-point crossover between two binary strings.
        :param p1: first parent binary string
        :param p2: second parent binary string
        :return: two offspring binary strings
        """
        points = sorted(np.random.choice(range(1, len(p1)), 2, replace=False))
        c1 = np.concatenate([p1[:points[0]], p2[points[0]:points[1]], p1[points[1]:]])
        c2 = np.concatenate([p2[:points[0]], p1[points[0]:points[1]], p2[points[1]:]])
        return c1, c2

    def mutate(self, individual, mutation_rate):
        """
        Mutate a binary string by flipping bits with a given mutation rate.
        :param individual: binary string represented as a list of bits (0s and 1s)
        :param mutation_rate: probability of flipping each bit
        :return: mutated binary string
        """
        mutant = individual.copy()
        for i in range(len(mutant)):
            if np.random.rand() < mutation_rate:
                mutant[i] ^= 1  # bit flip
        return mutant

    def decode_population(self, population):
        """
        Decode a population of binary strings into (x, y) coordinates based on the bounds.
        :param population: list of binary strings, each of length 2 * self.length
        :return: list of tuples, each containing (x, y) coordinates
        """
        decoded = []
        for individual in population:
            x_bits = individual[:self.length]
            y_bits = individual[self.length:]
            x = decode(x_bits, self.x_bounds)
            y = decode(y_bits, self.y_bounds)
            decoded.append((x, y))
        return decoded
