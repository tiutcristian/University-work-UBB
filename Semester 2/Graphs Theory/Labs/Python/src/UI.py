from src.Services import *
from src.Test_functions import *
from src.Connected_components import print_connected_components
from src.Lowest_cost_walk_Ford import print_lowest_cost_walk_Ford
from src.Topological_sorting_pred_counters import print_topo_sort
from src.Hamiltonian_cycle import print_hamiltonian_cycle


def run_tests():
    test_graph_class()
    test_copy_graph()
    print("All tests passed!")


def run_read_write_graph():
    while True:
        print("Choose a file to read from: ")
        print("1. graph1k.txt")
        print("2. graph10k.txt")
        print("3. graph100k.txt")
        print("4. graph1m.txt")
        print("0. Exit")
        option = int(input("Option: ").strip())
        filename = ""
        if option == 0:
            print("Exiting...")
            break
        elif option == 1:
            filename = "graph1k.txt"
            print("Graph 1k: ")
        elif option == 2:
            filename = "graph10k.txt"
            print("Graph 10k: ")
        elif option == 3:
            filename = "graph100k.txt"
            print("Graph 100k: ")
        elif option == 4:
            filename = "graph1m.txt"
            print("Graph 1m: ")
        g = read_from_file(filename)
        write_graph(g)


# noinspection DuplicatedCode
def run_connected_components():
    # illustration
    # https://ubbcluj-my.sharepoint.com/:w:/g/personal/cristian_tiut_stud_ubbcluj_ro/EQYR9gb3pWtAu2_P4FsLwNIBxXT5Ih2Im16lq9Jv4_Vm9g?e=IIIkR1

    # create graph
    g = Graph()

    # add 6 vertices
    g.add_vertex(0)
    g.add_vertex(1)
    g.add_vertex(2)
    g.add_vertex(3)
    g.add_vertex(4)
    g.add_vertex(5)

    # add bidirectional edges
    g.add_edge(0, 1)
    g.add_edge(1, 0)
    g.add_edge(0, 5)
    g.add_edge(5, 0)
    g.add_edge(3, 2)
    g.add_edge(2, 3)

    # create random undirected graph
    # g = create_random_undirected_graph(100, 100)

    # print connected components
    print_connected_components(g)


# noinspection DuplicatedCode
def run_lowest_cost_walk_Ford():
    # illustration
    # https://ubbcluj-my.sharepoint.com/:w:/g/personal/cristian_tiut_stud_ubbcluj_ro/EXrc2-xzL8xCrr0I7QUZRM0BrQnCFjAnadz0JPY2eRZjEA?e=k9wMw5
    print("Running lowest cost walk Ford...")
    g = Graph()
    g.add_vertex(0)
    g.add_vertex(1)
    g.add_vertex(2)
    g.add_vertex(3)
    g.add_vertex(4)
    g.add_vertex(5)

    g.add_edge(0, 1)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(2, 4)
    g.add_edge(4, 3)
    g.add_edge(3, 5)
    g.add_edge(5, 2)

    g.set_info(0, 1, 3)
    g.set_info(1, 2, -1)
    g.set_info(2, 3, -7)
    g.set_info(2, 4, -1)
    g.set_info(4, 3, 9)
    g.set_info(3, 5, 4)
    g.set_info(5, 2, 5)

    print("Hardcoded graph created (see illustration).")
    while True:
        print("Read data? (y/n)")
        option = input().strip()
        if option == "n":
            print("Exiting...")
            break
        print("Enter the start vertex: ")
        start_vertex = int(input().strip())
        print("Enter the end vertex: ")
        end_vertex = int(input().strip())
        print_lowest_cost_walk_Ford(g, start_vertex, end_vertex)


def run_topological_sort():
    # illustration
    # https://ubbcluj-my.sharepoint.com/:w:/g/personal/cristian_tiut_stud_ubbcluj_ro/EaDIGwHvWFZAqN1K7VnydA0BlPKm-TlQC_WFMqAr77Q_Ag?e=xafbHc
    print("Running topological sort...")
    activities = {
        'A': 3,
        'B': 2,
        'C': 1,
        'D': 4,
        'E': 6
    }
    prerequisites = {
        'A': [],
        'B': ['A'],
        'C': ['A'],
        'D': ['B', 'C'],
        'E': ['D']
    }
    print_topo_sort(activities, prerequisites)


def run_hamiltonian_cycle():
    # illustration
    # https://ubbcluj-my.sharepoint.com/:w:/r/personal/cristian_tiut_stud_ubbcluj_ro/_layouts/15/Doc.aspx?sourcedoc=%7Bb670f61e-d6a8-49bf-8b65-a35675832094%7D&action=editnew&wdOrigin=OFFICE-METAOS.FILEBROWSER.FILES-FOLDER
    print("Running hamiltonian cycle...")
    g = Graph()
    g.add_vertex(0)
    g.add_vertex(1)
    g.add_vertex(2)
    g.add_vertex(3)
    g.add_vertex(4)
    g.add_vertex(5)

    g.add_edge(0, 2)
    g.add_edge(0, 3)
    g.add_edge(0, 4)
    g.add_edge(0, 5)
    g.add_edge(1, 2)
    g.add_edge(1, 4)
    g.add_edge(1, 5)
    g.add_edge(2, 0)
    g.add_edge(2, 1)
    g.add_edge(2, 3)
    g.add_edge(2, 4)
    g.add_edge(3, 0)
    g.add_edge(3, 2)
    g.add_edge(4, 0)
    g.add_edge(4, 1)
    g.add_edge(4, 2)
    g.add_edge(4, 5)
    g.add_edge(5, 0)
    g.add_edge(5, 1)
    g.add_edge(5, 4)

    print("Hardcoded graph created (see illustration).")
    print_hamiltonian_cycle(g)
