from src.Graph import Graph
from src.Services import *


def test_graph_class():
    print("Running tests for Graph class...")
    graph = Graph()
    graph.add_vertex(0)
    graph.add_vertex(1)
    graph.add_vertex(2)
    assert (graph.is_vertex(0))
    assert (not graph.is_vertex(3))
    graph.add_edge(0, 2)
    graph.add_edge(2, 0)
    graph.add_edge(2, 1)
    graph.add_edge(1, 0)
    assert (graph.is_edge(0, 2))
    assert (not graph.is_edge(1, 2))
    assert (graph.parse_nin(0) == {1: None, 2: None})
    assert (graph.parse_nout(2) == {0: None, 1: None})
    assert (list(graph.parse_vertices()) == [0, 1, 2])
    assert graph.get_num_vertices() == 3
    assert graph.get_in_degree(0) == 2
    assert graph.get_in_degree(1) == 1
    assert graph.get_out_degree(2) == 2
    assert graph.get_out_degree(0) == 1
    graph.set_info(1, 0, 10)
    assert graph.get_info(1, 0) == 10
    assert graph.get_info(0, 2) is None
    graph.remove_edge(1, 0)
    assert not graph.is_edge(1, 0)
    graph.remove_vertex(0)
    assert not graph.is_vertex(0)
    print("Tests for Graph class passed!")


def test_copy_graph():
    print("Running tests for copy_graph function...")
    g = Graph()
    g.add_vertex(0)
    g.add_vertex(1)
    g.add_vertex(2)
    g.add_edge(0, 2)
    g.add_edge(2, 0)
    g.add_edge(2, 1)
    g.add_edge(1, 0)
    g.set_info(1, 0, 10)
    g_copy = copy_graph(g)
    assert g.get_num_vertices() == g_copy.get_num_vertices()
    for vertex in g.parse_vertices():
        assert g.get_in_degree(vertex) == g_copy.get_in_degree(vertex)
        assert g.get_out_degree(vertex) == g_copy.get_out_degree(vertex)
        for neighbor, info in g.parse_nout(vertex).items():
            assert g.get_info(vertex, neighbor) == g_copy.get_info(vertex, neighbor)
    print("Tests for copy_graph passed!")
