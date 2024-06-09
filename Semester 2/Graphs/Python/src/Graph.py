import random


class Graph:
    def __init__(self, n=0):
        """Constructs a graph with n vertices numbered from 0 to n-1 and no edges"""
        self.__n = n
        self.__inner_edges = {}
        self.__out_edges = {}
        for i in range(n):
            self.__inner_edges[i] = {}
            self.__out_edges[i] = {}

    def add_vertex(self, x):
        """
        Inserts the vertex into the graph.
        Precondition: x is of a type that can be used as a key in a dictionary (immutable and hashable)
        If the vertex is already in the graph, raises ValueError."""
        if self.is_vertex(x):
            raise ValueError("Vertex already exists")
        self.__inner_edges[x] = {}
        self.__out_edges[x] = {}

    def is_vertex(self, x):
        """Checks if the vertex is in the graph."""
        return x in self.__inner_edges and x in self.__out_edges

    def add_edge(self, x, y):
        """Adds an edge from vertex x to vertex y.
            Precondition: x and y are valid vertices of the graph.
            If the edge already exists or x or y are not vertices, raises ValueError."""
        if not self.is_vertex(x) or not self.is_vertex(y) or self.is_edge(x, y):
            raise ValueError("Edge cannot be added")
        self.__inner_edges[y][x] = None
        self.__out_edges[x][y] = None

    def is_edge(self, x, y):
        """Returns True if there is an edge from x to y in the graph, and False otherwise.
            Precondition: x and y are valid vertices of the graph."""
        return self.is_vertex(x) and self.is_vertex(y) and x in self.__inner_edges[y]

    def parse_nout(self, x):
        """Returns something iterable that contains all the outbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
            If x is not a vertex, raises ValueError.
        """
        if not self.is_vertex(x):
            raise ValueError("Not a vertex")
        return dict(self.__out_edges[x])

    def parse_nin(self, x):
        """Returns something iterable that contains all the inbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
            If x is not a vertex, raises ValueError.
        """
        if not self.is_vertex(x):
            raise ValueError("Not a vertex")
        return dict(self.__inner_edges[x])

    def parse_vertices(self):
        """Return something iterable that contains all the vertices of the graph"""
        for x in self.__inner_edges.keys():
            yield x

    def get_num_vertices(self):
        """Returns number of vertices"""
        return len(self.__inner_edges)

    def get_in_degree(self, x):
        """Returns number of inbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
            If x is not a vertex, raises ValueError."""
        if not self.is_vertex(x):
            raise ValueError("Not a vertex")
        return len(self.__inner_edges[x])

    def get_out_degree(self, x):
        """Returns number of outbound neighbors of vertex x
            Precondition: x is a valid vertex of the graph.
            If x is not a vertex, raises ValueError."""
        if not self.is_vertex(x):
            raise ValueError("Not a vertex")
        return len(self.__out_edges[x])

    def get_info(self, x, y):
        """Returns the information of the edge from vertex x to vertex y

            Preconditions:
                - x and y are valid vertices of the graph
                - there is an edge from x to y.
            :raises ValueError:
                If x or y are not vertices
                If there is no edge from x to y"""
        if not self.is_edge(x, y):
            raise ValueError("Not an edge")
        return self.__out_edges[x][y]

    def set_info(self, x, y, info):
        """Sets the information of the edge from vertex x to vertex y
            :raises ValueError: if x or y are not vertices of if there is no edge from x to y.
        """
        if not self.is_edge(x, y):
            raise ValueError("Not an edge")
        self.__out_edges[x][y] = info
        self.__inner_edges[y][x] = info

    def remove_edge(self, x, y):
        """Removes an edge between vertex x and vertex y
        :raises ValueError: if x or y are not vertices or if there is no edge between x and y."""
        if not self.is_edge(x, y):
            raise ValueError("Not an edge")
        del self.__out_edges[x][y]
        del self.__inner_edges[y][x]

    def remove_vertex(self, x):
        """Removes a vertex from the graph
        :raises ValueError: if x is not a vertex."""
        if not self.is_vertex(x):
            raise ValueError("Not a vertex")
        for y in self.__out_edges[x].keys():
            del self.__inner_edges[y][x]
        for y in self.__inner_edges[x].keys():
            del self.__out_edges[y][x]
        del self.__out_edges[x]
        del self.__inner_edges[x]
