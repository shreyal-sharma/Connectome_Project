#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void addEdge(vector<vector<int>>& adj_list, int u, int v) {
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

string subgraphToString(const unordered_set<int>& subgraph) {
    string result = "{";
    for (int vertex : subgraph) {
        result += to_string(vertex) + ",";
    }
    result.pop_back(); // Remove the last comma
    result += "}";
    return result;
}

void ESUAlgorithm(const vector<vector<int>>& adj_list, int vertex_count, int max_height) {
    vector<int> current_subgraph;
    unordered_set<int> current_set;
    vector<int> neighbors;
    vector<bool> visited(vertex_count, false);
    vector<vector<int>> extensions;

    auto extendSubgraph = [&](int vertex) {
        current_subgraph.push_back(vertex);
        current_set.insert(vertex);
        visited[vertex] = true;
        for (int neighbor : adj_list[vertex]) {
            if (!visited[neighbor] && neighbor > current_subgraph.back()) {
                extensions.push_back({ vertex, neighbor });
            }
        }
    };

    auto contractSubgraph = [&]() {
        int last_vertex = current_subgraph.back();
        current_subgraph.pop_back();
        current_set.erase(last_vertex);
        visited[last_vertex] = false;
    };

    auto generateSubgraphs = [&](int vertex) {
        extendSubgraph(vertex);
        while (!extensions.empty()) {
            int u = extensions.back()[0];
            int v = extensions.back()[1];
            extensions.pop_back();
            extendSubgraph(v);
        }
        if (current_subgraph.size() <= max_height) {
            cout << "Subgraph: " << subgraphToString(current_set) << endl;
        }
        contractSubgraph();
    };

    for (int start_vertex = 0; start_vertex < vertex_count; ++start_vertex) {
        generateSubgraphs(start_vertex);
    }
}

int main() {
    int vertex_count = 15;
    vector<vector<int>> adj_list(vertex_count);

    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 5}, {2, 3}, {2, 6},
        {3, 4}, {3, 7}, {4, 8}, {5, 6}, {5, 9}, {6, 7}, {6, 10}, {7, 8},
        {7, 11}, {8, 12}, {9, 10}, {9, 13}, {10, 11}, {10, 14}, {11, 12},
        {12, 13}, {13, 14}
    };

    for (auto& edge : edges) {
        addEdge(adj_list, edge.first, edge.second);
    }

    int max_height = 3;
    ESUAlgorithm(adj_list, vertex_count, max_height);

    return 0;
}
