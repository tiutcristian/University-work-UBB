import numpy as np

def tournament_selection(pop, fitnesses, k=3):
    selected = []
    for _ in range(len(pop)):
        indices = np.random.choice(len(pop), k)
        best_idx = indices[np.argmin(fitnesses[indices])]
        selected.append(pop[best_idx])
    return np.array(selected)