#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

void readCSV(const string& filename, unordered_map<int, set<int>>& adjacencyList) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int node;
        char comma;
        set<int> neighbors;

        ss >> node >> comma;
        int neighbor;
        while (ss >> neighbor >> comma) {
            neighbors.insert(neighbor);
        }

        adjacencyList[node] = neighbors;
    }

    file.close();
}

void buildGraph(Graph& graph, const unordered_map<int, set<int>>& adjacencyList) {
    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        const set<int>& neighbors = entry.second;
        for (int v : neighbors) {
            add_edge(u, v, graph);
        }
    }
}

void printMotifs(const unordered_map<string, int>& motifs) {
    for (const auto& [motif, count] : motifs) {
        cout << "Motif: " << motif << " Count: " << count << endl;
    }
}

void kavosh(const Graph& graph) {
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    typedef graph_traits<Graph>::vertices_size_type VertSize;
    typedef vector<vector<int>> Mat;

    unordered_map<string, int> motif_count;
    VertSize n = num_vertices(graph);

    for (VertSize i = 0; i < n; ++i) {
        for (VertSize j = i + 1; j < n; ++j) {
            for (VertSize k = j + 1; k < n; ++k) {
                Mat subgraph(3, vector<int>(3, 0));

                if (edge(i, j, graph).second && edge(j, k, graph).second && edge(k, i, graph).second) {
                    subgraph[0][1] = subgraph[1][0] = 1;
                }

                if (edge(i, j, graph).second && edge(j, k, graph).second && !edge(k, i, graph).second) {
                    subgraph[0][1] = subgraph[1][0] = subgraph[0][2] = subgraph[1][2] = 1;
                }

                if (edge(i, j, graph).second && !edge(j, k, graph).second && !edge(k, i, graph).second) {
                    subgraph[0][1] = subgraph[1][0] = subgraph[0][2] = 1;
                }

                if (!edge(i, j, graph).second && edge(j, k, graph).second && edge(k, i, graph).second) {
                    subgraph[0][1] = subgraph[1][0] = subgraph[1][2] = 1;
                }

                if (subgraph[0][1] == 1 && subgraph[1][0] == 1 && subgraph[1][2] == 1) {
                    subgraph[0][1] = subgraph[1][0] = subgraph[0][2] = subgraph[2][0] = 1;
                }

                if (subgraph[0][1] == 1 && subgraph[1][0] == 1 && subgraph[0][2] == 1) {
                    subgraph[0][1] = subgraph[1][0] = subgraph[1][2] = subgraph[2][1] = 1;
                }

                if (subgraph[0][1] == 1 && subgraph[1][0] == 1 && subgraph[0][2] == 1 && subgraph[1][2] == 1) {
                    subgraph[0][1] = subgraph[1][0] = subgraph[0][2] = subgraph[1][2] = subgraph[2][1] = subgraph[2][0] = 1;
                }

                string canon_form;
                for (int x = 0; x < 3; ++x) {
                    for (int y = 0; y < 3; ++y) {
                        canon_form += to_string(subgraph[x][y]);
                    }
                }

                motif_count[canon_form]++;
            }
        }
    }

    printMotifs(motif_count);
}

int main() {
    string filename = "S1_hemibrain.csv";

    unordered_map<int, set<int>> adjacencyList;
    readCSV(filename, adjacencyList);

    Graph graph;
    buildGraph(graph, adjacencyList);

    cout << "Graph: " << endl;
    print_graph(graph);

    cout << "\nMotifs found by Kavosh algorithm:\n";
    kavosh(graph);

    return 0;
}
