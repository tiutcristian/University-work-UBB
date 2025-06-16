import random

from src.Graph import Graph


def copy_graph(g):
    """Creates a copy of a graph
    :param g: the graph to be copied
    :return: a copy of the graph"""
    new_graph = Graph()
    for vertex in g.parse_vertices():
        new_graph.add_vertex(vertex)
    for vertex in g.parse_vertices():
        for neighbor, info in g.parse_nout(vertex).items():
            new_graph.add_edge(vertex, neighbor)
            new_graph.set_info(vertex, neighbor, info)
    return new_graph


def read_from_file(filename: str):
    """Reads a graph from a text file
    :param filename: the name of the file
    :return: a graph"""
    f = open(filename, "r")
    num_vertices, num_edges = map(int, f.readline().split())
    g = Graph(num_vertices)
    for _ in range(num_edges):
        source, destination, cost = map(int, f.readline().split())
        g.add_edge(source, destination)
        g.set_info(source, destination, cost)
    f.close()
    return g


def write_to_file(g: Graph, filename: str):
    """Writes a graph to a text file
    :param g: the graph
    :param filename: the name of the file"""
    with open(filename, "w") as f:
        for vertex in g.parse_vertices():
            for neighbor, info in g.parse_nout(vertex).items():
                f.write(f"{vertex} {neighbor} {info}\n")


def write_graph(g: Graph):
    """Writes a graph to the console
    :param g: the graph"""
    for vertex in g.parse_vertices():
        for neighbor, info in g.parse_nout(vertex).items():
            print(f"{vertex} {neighbor} {info}")


def create_random_directed_graph(n, m):
    """Creates a random directed graph with n vertices and m edges
    :param n: the number of vertices
    :param m: the number of edges
    :return: a random graph"""
    g = Graph(n)
    nr_attempts = 0
    while m > 0:
        nr_attempts += 1
        x = random.randrange(n)
        y = random.randrange(n)
        if x != y:
            try:
                g.add_edge(x, y)
                m -= 1
            except ValueError:
                pass
    print(f"nr_attempts = {nr_attempts}")
    return g


def create_random_undirected_graph(n, m):
    """Creates a random undirected graph with n vertices and m edges
    :param n: the number of vertices
    :param m: the number of edges
    :return: a random graph"""
    g = Graph(n)
    while m > 0:
        x = random.randrange(n)
        y = random.randrange(n)
        if x != y:
            try:
                g.add_edge(x, y)
                g.add_edge(y, x)
                m -= 1
            except ValueError:
                pass
    return g
