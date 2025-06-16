#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <exception>
#include <iostream>
#include <fstream>

class Graph {
private:
    int n;
    std::unordered_map<int, std::unordered_map<int, int>> inner_edges;
    std::unordered_map<int, std::unordered_map<int, int>> out_edges;

public:
    Graph(int n = 0) {
        
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->inner_edges[i] = {};
            this->out_edges[i] = {};
        }
    }

    void add_vertex(int x) {
        if (is_vertex(x)) {
            throw std::exception("Vertex already exists");
        }
        this->inner_edges[x] = {};
        this->out_edges[x] = {};
        this->n++;
    }

    bool is_vertex(int x) {
        return this->inner_edges.count(x) > 0 && this->out_edges.count(x) > 0;
    }

    void add_edge(int x, int y) {
        if (!is_vertex(x) || !is_vertex(y) || is_edge(x, y)) {
            throw std::exception("Edge cannot be added");
        }
        this->inner_edges[y][x] = -1;
        this->out_edges[x][y] = -1;
    }

    bool is_edge(int x, int y) {
        return is_vertex(x) && is_vertex(y) && this->inner_edges[y].count(x) > 0;
    }

    std::unordered_map<int, int> parse_nout(int x) {
        if (!is_vertex(x)) {
            throw std::exception("Not a vertex");
        }
        return this->out_edges[x];
    }

    std::unordered_map<int, int> parse_nin(int x) {
        if (!is_vertex(x)) {
            throw std::exception("Not a vertex");
        }
        return this->inner_edges[x];
    }

    std::unordered_set<int> parse_vertices() {
        std::unordered_set<int> vertices;
        for (const auto& pair : this->inner_edges) {
            vertices.insert(pair.first);
        }
        return vertices;
    }

    int get_num_vertices() {
        return this->n;
    }

    int get_in_degree(int x) {
        if (!is_vertex(x)) {
            throw std::exception("Not a vertex");
        }
        return this->inner_edges[x].size();
    }

    int get_out_degree(int x) {
        if (!is_vertex(x)) {
            throw std::exception("Not a vertex");
        }
        return this->out_edges[x].size();
    }

    int get_info(int x, int y) {
        if (!is_edge(x, y)) {
            throw std::exception("Not an edge");
        }
        return this->out_edges[x][y];
    }

    void set_info(int x, int y, int info) {
        if (!this->is_edge(x, y)) {
            throw std::exception("Not an edge");
        }
        this->out_edges[x][y] = info;
        this->inner_edges[y][x] = info;
    }

    void remove_edge(int x, int y) {
        if (!this->is_edge(x, y)) {
            throw std::exception("Not an edge");
        }
        this->out_edges[x].erase(y);
        this->inner_edges[y].erase(x);
    }

    void remove_vertex(int x) {
        if (!this->is_vertex(x)) {
            throw std::exception("Not a vertex");
        }
        for (auto it = this->out_edges[x].begin(); it != this->out_edges[x].end(); it++) {
            this->inner_edges[it->first].erase(x);
        }
        for (auto it = this->inner_edges[x].begin(); it != this->inner_edges[x].end(); it++) {
            this->out_edges[it->first].erase(x);
        }
        this->out_edges.erase(x);
        this->inner_edges.erase(x);
    }

    static void testFunc() {
        Graph graph;
        graph.add_vertex(0);
        graph.add_vertex(1);
        graph.add_vertex(2);
        assert(graph.is_vertex(0));
        assert(!graph.is_vertex(3));
        graph.add_edge(0, 2);
        graph.add_edge(2, 0);
        graph.add_edge(2, 1);
        graph.add_edge(1, 0);
        assert(graph.is_edge(0, 2));
        assert(!graph.is_edge(1, 2));

        auto nin0 = graph.parse_nin(0);
        std::unordered_map<int, int> nin0_expected = { {1, -1}, {2, -1} };
        assert(nin0 == nin0_expected);

        auto nout2 = graph.parse_nout(2);
        std::unordered_map<int, int> nout2_expected = { {0, -1}, {1, -1} };
        assert(nout2 == nout2_expected);

        auto vertices = graph.parse_vertices();
        std::unordered_set<int> expected_set = { 0, 1, 2 };
        assert(vertices == expected_set);

        assert(graph.get_num_vertices() == 3);
        assert(graph.get_in_degree(0) == 2);
        assert(graph.get_in_degree(1) == 1);
        assert(graph.get_out_degree(2) == 2);
        assert(graph.get_out_degree(0) == 1);
        graph.set_info(1, 0, 10);
        assert(graph.get_info(1, 0) == 10);
        assert(graph.get_info(0, 2) == -1);
        graph.remove_edge(1, 0);
        assert(!graph.is_edge(1, 0));
        graph.remove_vertex(0);
        assert(!graph.is_vertex(0));
    }
};

Graph copy_graph(Graph& g) {
    Graph new_graph;
    for (int vertex : g.parse_vertices())
        new_graph.add_vertex(vertex);
    
    for (int vertex : g.parse_vertices()) {
        auto nout = g.parse_nout(vertex);
        for (auto sth : nout) {
			new_graph.add_edge(vertex, sth.first);
			new_graph.set_info(vertex, sth.first, sth.second);
		}
    }
    return new_graph;
}

void test_copy_graph() {
    Graph g;
    g.add_vertex(0);
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_edge(0, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 1);
    g.add_edge(1, 0);
    g.set_info(1, 0, 10);
    Graph g_copy = copy_graph(g);
    assert(g.get_num_vertices() == g_copy.get_num_vertices());
    for (int vertex : g.parse_vertices()) {
        assert(g.get_in_degree(vertex) == g_copy.get_in_degree(vertex));
        assert(g.get_out_degree(vertex) == g_copy.get_out_degree(vertex));

        for (auto sth : g.parse_nout(vertex)) {
            assert(g.get_info(vertex, sth.first) == g_copy.get_info(vertex, sth.first));
        }
    }
}

Graph read_from_file(const std::string& filename) {
    std::ifstream f(filename);
    int num_vertices, num_edges;
    f >> num_vertices >> num_edges;
    Graph g(num_vertices);
    for (int i = 0; i < num_edges; i++) {
        int source, destination, cost;
        f >> source >> destination >> cost;
        g.add_edge(source, destination);
        g.set_info(source, destination, cost);
    }
    f.close();
    return g;
}

void write_to_file(Graph& g, const std::string& filename) {
    std::ofstream f(filename);
    for (int vertex : g.parse_vertices()) {
        for (auto sth : g.parse_nout(vertex)) {
            f << vertex << " " << sth.first << " " << sth.second << "\n";
        }
    }
    f.close();
}

void write_graph(Graph& g) {
    for (int vertex : g.parse_vertices()) {
        for (auto sth : g.parse_nout(vertex)) {
            std::cout << vertex << " " << sth.first << " " << sth.second << "\n";
        }
    }
}

Graph create_random_graph(int n, int m) {
    Graph g(n);
    int nr_attempts = 0;
    while (m > 0) {
        nr_attempts++;
        int x = rand() % n;
        int y = rand() % n;
        if (x != y) {
            try {
                g.add_edge(x, y);
                m--;
            }
            catch (const std::exception&) {
            }
        }
    }
    std::cout << "nr_attempts = " << nr_attempts << "\n";
    return g;
}

void runTests() 
{
	Graph::testFunc();
    test_copy_graph();
    std::cout << "All tests passed\n\n";
}

void run_ui() {
    while (true) {
        std::cout << "Choose a file to read from: " << std::endl;
        std::cout << "1. graph1k.txt" << std::endl;
        std::cout << "2. graph10k.txt" << std::endl;
        std::cout << "3. graph100k.txt" << std::endl;
        std::cout << "4. graph1m.txt" << std::endl;
        std::cout << "0. Exit" << std::endl;

        
        int optionInt;
        std::cin >> optionInt;
        std::string filename = "";
        if (optionInt == 0) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        else if (optionInt == 1) {
            filename = "graph1k.txt";
            std::cout << "Graph 1k: " << std::endl;
        }
        else if (optionInt == 2) {
            filename = "graph10k.txt";
            std::cout << "Graph 10k: " << std::endl;
        }
        else if (optionInt == 3) {
            filename = "graph100k.txt";
            std::cout << "Graph 100k: " << std::endl;
        }
        else if (optionInt == 4) {
            filename = "graph1m.txt";
            std::cout << "Graph 1m: " << std::endl;
        }

        Graph g = read_from_file(filename);
        write_graph(g);
    }
}

int main() 
{
    runTests();
    run_ui();
	return 0;
}