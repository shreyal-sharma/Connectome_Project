#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <boost/graph/adjacency_list.hpp>
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

    return 0;
}
