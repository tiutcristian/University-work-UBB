import numpy as np

from .encoding.encoding import get_encoder


class GA:
    """
    Genetic Algorithm class for optimizing a given fitness function.
    """

    def __init__(self, fitness_func, x_bounds, y_bounds, config):
        self.fitness_func = fitness_func
        self.config = config
        self.population_size = self.config["population_size"]
        self.mutation_rate = self.config["mutation_rate"]
        self.crossover_rate = self.config["crossover_rate"]
        self.generations = self.config["generations"]
        self.tournament_size = self.config.get("tournament_size", 3)
        self.encoder = get_encoder(x_bounds, y_bounds, config)
        self.population = self.encoder.initialize_population()
        self.best_solution = None
        self.best_fitness = np.inf
        self.best_fitnesses_history = []  # best fitness per generation

    def tournament_selection(self, fitnesses):
        selected_indices = np.random.choice(len(self.population), self.tournament_size, replace=False)
        tournament_fitnesses = [fitnesses[i] for i in selected_indices]
        winner_idx = selected_indices[np.argmin(tournament_fitnesses)]  # minimize fitness
        return self.population[winner_idx]

    def run(self):
        for gen in range(self.generations):
            decoded_pop = self.encoder.decode_population(self.population)
            fitnesses = np.array([self.fitness_func(ind) for ind in decoded_pop])

            min_idx = np.argmin(fitnesses)
            if fitnesses[min_idx] < self.best_fitness:
                self.best_fitness = fitnesses[min_idx]
                self.best_solution = decoded_pop[min_idx]
            self.best_fitnesses_history.append(self.best_fitness)

            new_population = []
            while len(new_population) < self.population_size:
                p1 = self.tournament_selection(fitnesses)
                p2 = self.tournament_selection(fitnesses)

                c1_enc, c2_enc = self.encoder.crossover(p1, p2, self.crossover_rate)
                c1_mut = self.encoder.mutate(c1_enc, self.mutation_rate)
                c2_mut = self.encoder.mutate(c2_enc, self.mutation_rate)

                new_population.extend([c1_mut, c2_mut])

            self.population = np.array(new_population[:self.population_size])

        return self.best_solution, self.best_fitness, self.best_fitnesses_history