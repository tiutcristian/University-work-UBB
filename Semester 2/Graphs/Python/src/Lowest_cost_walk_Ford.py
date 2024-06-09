from src.Graph import Graph


def get_walk(prev, start_vertex, end_vertex):
    """
    Get the walk from start_vertex to end_vertex using the previous vertex list.
    :param prev: previous vertex list
    :param start_vertex: start vertex
    :param end_vertex: end vertex
    :return: list of vertices representing the walk
    """
    walk = []
    current_vertex = end_vertex
    while current_vertex != start_vertex:
        walk.append(current_vertex)
        current_vertex = prev[current_vertex]
    walk.append(start_vertex)
    walk.reverse()
    return walk


# Write a program that, given a graph, finds a lowest cost walk between the given vertices,
# or prints a message if there are negative cost cycles accessible from the starting vertex.
# The program will use the Ford's algorithm.
def lowest_cost_walk_Ford(g: Graph, start_vertex, end_vertex):
    """
    Get the lowest cost walk from start_vertex to end_vertex using Ford's algorithm.
    :param g: the graph
    :param start_vertex: start vertex
    :param end_vertex: end vertex
    :return: tuple: (cost: int, walk: list) or (None, []) if there is a negative cost cycle
    """
    dist = {}
    prev = {}
    for x in g.parse_vertices():
        dist[x] = float("inf")
    dist[start_vertex] = 0
    changed = True
    iterations = 0
    while changed and iterations in range(g.get_num_vertices()-1):
        changed = False
        iterations += 1
        for x in g.parse_vertices():
            for y in g.parse_nout(x):
                if dist[y] > dist[x] + g.get_info(x, y):
                    dist[y] = dist[x] + g.get_info(x, y)
                    prev[y] = x
                    changed = True
    if iterations == g.get_num_vertices()-1:
        for x in g.parse_vertices():
            for y in g.parse_nout(x):
                if dist[y] > dist[x] + g.get_info(x, y):
                    return None, []
    if dist[end_vertex] == float("inf"):
        return float("inf"), []
    return dist[end_vertex], get_walk(prev, start_vertex, end_vertex)


def print_lowest_cost_walk_Ford(g: Graph, start_vertex, end_vertex):
    """
    Print the lowest cost walk from start_vertex to end_vertex using Ford's algorithm.
    :param g: graph
    :param start_vertex: start vertex
    :param end_vertex: end vertex
    """
    cost, walk = lowest_cost_walk_Ford(g, start_vertex, end_vertex)
    if cost is None:
        print("Negative cost cycle detected!")
    elif cost == float("inf"):
        print(f"There is no walk from {start_vertex} to {end_vertex}.")
    else:
        print(f"Cost of lowest cost walk from {start_vertex} to {end_vertex} is {cost}:")
        print(f"Walk: {walk}")
