from src.Graph import Graph


def dfs(g: Graph, node, visited, component):
    """
    Perform a depth-first search on the graph.
    :param g: graph
    :param node: node to start the search from
    :param visited: list where visited[i] is True if node i was visited
    :param component: list of nodes in the connected component
    """
    visited[node] = True
    component.append(node)
    for neighbor in g.parse_nout(node):
        if not visited[neighbor]:
            dfs(g, neighbor, visited, component)


def connected_components(g: Graph):
    """
    Get the connected components of the graph.
    :param g: graph
    :return: list of connected components
    """
    visited = {node: False for node in g.parse_vertices()}
    components = []
    for node in g.parse_vertices():
        if not visited[node]:
            component = []
            dfs(g, node, visited, component)
            components.append(component)
    return components


def print_connected_components(g: Graph):
    """
    Print the connected components of the graph.
    :param g: graph
    """
    components = connected_components(g)
    for component in components:
        print(component)
