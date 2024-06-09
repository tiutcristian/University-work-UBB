from src.Graph import Graph
# Given an undirected graph, find a Hamiltonian cycle (if it exists).


def create_cost_matrix(g: Graph):
    n = g.get_num_vertices()
    cost_matrix = [[2] * n for _ in range(n)]

    for i in range(n):
        for j in g.parse_nout(i):
            cost_matrix[i][j] = 1
            cost_matrix[j][i] = 1

    return cost_matrix


def get_hamiltonian_cycle(g: Graph):
    n = g.get_num_vertices()
    cost_matrix = create_cost_matrix(g)

    # Use dynamic programming to store the minimum cost of visiting all sets of vertices
    dp = [[float('inf')] * n for _ in range(1 << n)]
    parent = [[-1] * n for _ in range(1 << n)]
    dp[1][0] = 0

    for mask in range(1 << n):
        for u in range(n):
            if mask & (1 << u):
                for v in range(n):
                    if mask & (1 << v) == 0:
                        new_mask = mask | (1 << v)
                        new_cost = dp[mask][u] + cost_matrix[u][v]
                        if new_cost < dp[new_mask][v]:
                            dp[new_mask][v] = new_cost
                            parent[new_mask][v] = u

    # Find the minimum cost to complete the cycle
    min_cost = float('inf')
    last_vertex = -1
    for v in range(n):
        cost = dp[(1 << n) - 1][v] + cost_matrix[v][0]
        if cost < min_cost:
            min_cost = cost
            last_vertex = v

    # If the minimum cost is exactly the number of vertices, we found a Hamiltonian cycle
    if min_cost == n:
        # Reconstruct the path
        path = [0] * n
        mask = (1 << n) - 1
        current_vertex = last_vertex
        for i in range(n - 1, -1, -1):
            path[i] = current_vertex
            current_vertex = parent[mask][current_vertex]
            mask ^= (1 << path[i])
        path.append(0)  # Complete the cycle by returning to the starting vertex
        return path
    return None


def print_hamiltonian_cycle(g: Graph):
    cycle = get_hamiltonian_cycle(g)
    if cycle is None:
        print("No hamiltonian cycle")
    else:
        print("Hamiltonian cycle: ", cycle)
