#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

class UndirectedGraph {
public:
    UndirectedGraph() {
        num_vertices = 0;
    }

    void add_edge(int u, int v) {
        if (edge_map.find(u) == edge_map.end()) {
            edge_map[u] = {};
        }
        edge_map[u].insert(v);

        if (edge_map.find(v) == edge_map.end()) {
            edge_map[v] = {};
        }
        edge_map[v].insert(u);

        num_vertices = max(num_vertices, max(u, v) + 1);
    }

    vector<int> get_vertices() {
        vector<int> vertices;
        for (auto it = edge_map.begin(); it != edge_map.end(); ++it) {
            vertices.push_back(it->first);
        }
        return vertices;
    }

    set<int> get_neighbors(int vertex) {
        if (edge_map.find(vertex) == edge_map.end()) {
            return {};
        }
        return edge_map[vertex];
    }

    map<set<int>, int> classify_subgraphs() {
        map<set<int>, int> motifs;

        for (auto it = edge_map.begin(); it != edge_map.end(); ++it) {
            int u = it->first;
            for (auto v : it->second) {
                if (v <= u) {
                    continue;
                }
                set<int> subgraph = {u, v};
                for (auto neighbor : edge_map[u]) {
                    if (neighbor != v && edge_map[v].count(neighbor) > 0) {
                        subgraph.insert(neighbor);
                    }
                }
                set<int> sorted_subgraph;
                for (auto node : subgraph) {
                    sorted_subgraph.insert(node);
                }
                motifs[sorted_subgraph]++;
            }
        }
        return motifs;
    }

    void export_dot_file(string filename) {
        ofstream file(filename);
        file << "graph G {\n";

        for (auto it = edge_map.begin(); it != edge_map.end(); ++it) {
            int u = it->first;
            for (auto v : it->second) {
                if (v > u) {
                    file << u << " -- " << v << ";\n";
                }
            }
        }

        file << "}\n";
        file.close();
    }

private:
    map<int, set<int>> edge_map;
    int num_vertices;
};

int main() {
    UndirectedGraph graph;

    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 5}, {2, 3}, {2, 6}, {3, 4}, {3, 7},
        {4, 8}, {5, 6}, {5, 9}, {6, 7}, {6, 10}, {7, 8}, {7, 11}, {8, 12}, {9, 10}, {9, 13},
        {10, 11}, {10, 14}, {11, 12}, {12, 13}, {13, 14}
    };

    for (auto& edge : edges) {
        graph.add_edge(edge.first, edge.second);
    }

    graph.export_dot_file("graph.dot");

    auto motifs = graph.classify_subgraphs();
    for (auto& motif : motifs) {
        cout << "Motif: {";
        for (auto& node : motif.first) {
            cout << node << ", ";
        }
        cout << "} Count: " << motif.second << endl;
    }

    return 0;
}
