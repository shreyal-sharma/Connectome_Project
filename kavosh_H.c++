#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/subgraph.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef subgraph<Graph> Subgraph;

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

void findMotifs(Graph& graph) {
   
}

int main() {
    string filename = "S1_hemibrain.csv";

    unordered_map<int, set<int>> adjacencyList;
    readCSV(filename, adjacencyList);

    Graph graph;
    buildGraph(graph, adjacencyList);

    
    cout << "Graph: " << endl;
    print_graph(graph);

    
    findMotifs(graph);


int main() {
    string filename = "S1_hemibrain.csv";
    unordered_map<int, vector<int>> adjacencyList;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int node;
        char comma;
        vector<int> neighbors;

        ss >> node >> comma;
        int neighbor;
        while (ss >> neighbor >> comma) {
            neighbors.push_back(neighbor);
        }

        adjacencyList[node] = neighbors;
    }

    file.close();

    int n = adjacencyList.size();
    int k = 5;

    Graph graph(n, k);

    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        const vector<int>& neighbors = entry.second;
        for (int v : neighbors) {
            graph.addEdge(u, v);
        }
    }

    graph.FindSubgraphs();
    graph.ClassifySubgraphs();
    graph.PrintSubgraphStats();

using namespace std;

class Graph {
private:
    int nV;
    int subgraphSize;
    vector<vector<bool>> adjMat;
    unordered_map<int, vector<int>> edges;
    vector<int> degree;
    vector<vector<bool>> nauty_g;

public:
    Graph(int n, int k) : nV(n), subgraphSize(k) {
        adjMat.resize(n, vector<bool>(n, false));
        degree.resize(n, 0);
        nauty_g.resize(k, vector<bool>(k, false));
    }

    void addEdge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
        adjMat[u][v] = true;
        adjMat[v][u] = true;
        degree[u]++;
        degree[v]++;
    }

    bool isConnected(int u, int v) {
        return adjMat[u][v];
    }

    vector<pair<vector<int>, vector<vector<bool>>>> findSubgraphs() {
        vector<pair<vector<int>, vector<vector<bool>>>> result;
        vector<int> vertices(subgraphSize);
        iota(vertices.begin(), vertices.end(), 0);

        do {
            vector<vector<bool>> subgraph(subgraphSize, vector<bool>(subgraphSize, false));
            for (int i = 0; i < subgraphSize; ++i) {
                for (int j = 0; j < subgraphSize; ++j) {
                    subgraph[i][j] = adjMat[vertices[i]][vertices[j]];
                }
            }
            result.emplace_back(vertices, subgraph);
        } while (next_permutation(vertices.begin(), vertices.end()));

        return result;
    }

    string canonicalForm(const vector<vector<bool>>& subgraph) {
        string canonical;
        for (const auto& row : subgraph) {
            bitset<8> bits;
            for (int i = 0; i < subgraphSize; ++i) {
                bits[i] = row[i];
            }
            canonical += bits.to_string();
        }
        return canonical;
    }

    unordered_map<string, int> classifySubgraphs() {
        unordered_map<string, int> motif_count;
        auto subgraphs = findSubgraphs();
        for (const auto& [vertices, subgraph] : subgraphs) {
            string canon_form = canonicalForm(subgraph);
            motif_count[canon_form]++;
        }
        return motif_count;
    }
};
file_path = 'S1_hemibrain.csv'
int main() {
    int n = 5;
    int k = 3;

    Graph graph(n, k);
edges = [
    (0, 1), (0, 2), (0, 3), (0, 4), (1, 2), (1, 5), (2, 3), (2, 6), (3, 4), (3, 7),
    (4, 8), (5, 6), (5, 9), (6, 7), (6, 10), (7, 8), (7, 11), (8, 12), (9, 10), (9, 13),
    (10, 11), (10, 14), (11, 12), (12, 13), (13, 14)
]

    for (auto [u, v] : edges) {
        graph.addEdge(u, v);
    }

    auto motifs = graph.classifySubgraphs();

    for (const auto& [motif, count] : motifs) {
        cout << "Motif: " << motif << " Count: " << count << endl;
    }

    return 0;
}
