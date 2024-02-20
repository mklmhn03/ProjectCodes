#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

bool dfs(int current, int destination, vector<vector<int>>& adjacency_list, vector<bool>& visited) {
    if (current == destination) return true;

    visited[current] = true;

    for (int neighbor : adjacency_list[current]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, destination, adjacency_list, visited)) {
                return true;
            }
        }
    }

    return false;
}

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    vector<vector<int>> adjacency_list(n);

    for (const vector<int>& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    vector<bool> visited(n, false);

    return dfs(source, destination, adjacency_list, visited);
}

int main() {
    // Test Case 1: Valid Path Exists
    {
        int n = 3;
        vector<vector<int>> edges = {{0,1},{1,2},{2,0}};
        int source = 0;
        int destination = 2;
        assert(validPath(n, edges, source, destination) == true);
    }

    // Test Case 2: No Path Exists
    {
        int n = 6;
        vector<vector<int>> edges = {{0,1},{0,2},{3,5},{5,4},{4,3}};
        int source = 0;
        int destination = 5;
        assert(validPath(n, edges, source, destination) == false);
    }

    // Test Case 3: Source and Destination are the same
    {
        int n = 4;
        vector<vector<int>> edges = {{0,1},{1,2},{2,3},{3,0}};
        int source = 2;
        int destination = 2;
        assert(validPath(n, edges, source, destination) == true);
    }

    // Test Case 4: Single Vertex Graph
    {
        int n = 1;
        vector<vector<int>> edges = {};
        int source = 0;
        int destination = 0;
        assert(validPath(n, edges, source, destination) == true);
    }

    // Test Case 5: Large Graph (Edge Case)
    {
        int n = 2 * 105;
        vector<vector<int>> edges = {};
        int source = 0;
        int destination = n - 1;
        assert(validPath(n, edges, source, destination) == false);
    }

    cout << "All test cases passed!" << endl;

    return 0;
}