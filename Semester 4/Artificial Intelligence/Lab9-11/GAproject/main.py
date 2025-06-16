import pandas as pd
import numpy as np

from config import CONFIG
from functions.ackley import AckleyFunction
from functions.rastrigin import RastriginFunction
from ga.GA import GA
from utils.functions_plotting import plot_contour, plot_surface


def run_ga(fun, config):
    def fitness_func(ind):
        x, y = ind
        return fun.evaluate(x, y)
    bounds = fun.bounds()
    ga = GA(fitness_func, bounds[0], bounds[1], config)
    best_solution, best_fitness, fitness_history = ga.run()
    return best_solution, best_fitness, fitness_history

configs = [
    {
        "encoding": "binary",
        "crossover_method": "1point",
    },
    {
        "encoding": "binary",
        "crossover_method": "2point",
    },
    {
        "encoding": "real",
        "crossover_method": "arithmetic",
    },
    {
        "encoding": "real",
        "crossover_method": "blx",
    }
]

NUM_RUNS = 30

def get_updated_config(config):
    updated_config = CONFIG.copy()
    updated_config.update(config)
    return updated_config

def plot_functions():
    # Plotting the Ackley function
    plot_contour(AckleyFunction(), [-32, 32], "Ackley Contour")
    plot_surface(AckleyFunction(), [-32, 32], "Ackley Surface")

    # Plotting the Rastrigin function
    plot_contour(RastriginFunction(), [-5, 5], "Rastrigin Contour")
    plot_surface(RastriginFunction(), [-5, 5], "Rastrigin Surface")

if __name__ == "__main__":
    # plot_functions()

    results = []

    for config in configs:
        updated_config = get_updated_config(config)

        for i in range(NUM_RUNS):
            print(f"Running Ackley function with config: {updated_config}, run {i + 1}/{NUM_RUNS}")
            np.random.seed(CONFIG["seeds"][i % len(CONFIG["seeds"])])
            ackley_result = run_ga(AckleyFunction(), updated_config)
            results.append({
                "function": "Ackley",
                "encoding": updated_config["encoding"],
                "crossover_method": updated_config["crossover_method"],
                "run": i,
                "best_solution": ackley_result[0],
                "best_fitness": ackley_result[1],
                "fitness_history": ackley_result[2]
            })

        for i in range(NUM_RUNS):
            print(f"Running Rastrigin function with config: {updated_config}, run {i + 1}/{NUM_RUNS}")
            np.random.seed(CONFIG["seeds"][i % len(CONFIG["seeds"])])
            rastrigin_result = run_ga(RastriginFunction(), updated_config)
            results.append({
                "function": "Rastrigin",
                "encoding": updated_config["encoding"],
                "crossover_method": updated_config["crossover_method"],
                "run": i,
                "best_solution": rastrigin_result[0],
                "best_fitness": rastrigin_result[1],
                "fitness_history": rastrigin_result[2]
            })

    df_results = pd.DataFrame(results)

    # Summarize performance
    df_summary = df_results.groupby(["function", "encoding", "crossover_method"]).agg(
        best=("best_fitness", "min"),
        mean=("best_fitness", "mean"),
        std=("best_fitness", "std"),
        median=("best_fitness", "median"),
    ).reset_index()

    print("\nSummary of Results:")
    print(df_summary.to_string(index=False))
