import numpy as np

from config import CONFIG


class RealEncoder:
    def __init__(self, x_bounds, y_bounds, config):
        self.x_bounds = x_bounds
        self.y_bounds = y_bounds
        self.config = config
        self.blx_alpha = self.config["blx_alpha"]
        self.size = self.config["population_size"]

    def initialize_population(self):
        return np.random.uniform(
            [self.x_bounds[0], self.y_bounds[0]],
            [self.x_bounds[1], self.y_bounds[1]],
            (self.size, 2)
        )

    def mutate(self, individual, mutation_rate):
        """
        Mutate a real-valued individual with Gaussian noise.
        :param individual: individual to mutate
        :param mutation_rate: probability of mutation for each gene
        :return: mutated individual
        """
        mutant = individual.copy()
        if np.random.rand() < mutation_rate:
            mutant[0] += np.random.normal(0, 0.1)
            mutant[0] = np.clip(mutant[0], *self.x_bounds)
        if np.random.rand() < mutation_rate:
            mutant[1] += np.random.normal(0, 0.1)
            mutant[1] = np.clip(mutant[1], *self.y_bounds)
        return mutant

    def crossover(self, p1, p2, crossover_rate):
        """
        Perform crossover between two real-valued parents.
        :param p1: first parent
        :param p2:
        :param crossover_rate: probability of crossover
        :return: two offspring
        """
        if np.random.rand() > crossover_rate:
            return p1.copy(), p2.copy()
        if self.config["crossover_method"] == "arithmetic":
            return self.arithmetic_crossover(p1, p2)
        return self.blx_alpha_crossover(p1, p2)

    def arithmetic_crossover(self, p1, p2):
        """
        Perform arithmetic crossover between two real-valued parents.
        :param p1: first parent
        :param p2: second parent
        :return: two offspring
        """
        alpha = np.random.rand()
        c1 = alpha * p1 + (1 - alpha) * p2
        c2 = alpha * p2 + (1 - alpha) * p1
        return c1, c2

    def blx_alpha_crossover(self, p1, p2):
        """
        Perform BLX-alpha crossover between two real-valued parents.
        :param p1: first parent
        :param p2: second parent
        :return: two offspring
        """
        diff = np.abs(p1 - p2)
        low = np.minimum(p1, p2) - self.blx_alpha * diff
        high = np.maximum(p1, p2) + self.blx_alpha * diff
        c1 = np.random.uniform(low, high)
        c2 = np.random.uniform(low, high)
        return c1, c2

    def decode_population(self, population):
        """
        Decode a population of real-valued individuals to tuples.
        :param population: array of individuals
        :return: list of tuples representing decoded individuals
        """
        return [tuple(ind) for ind in population]