//Min Chang
//Github: Minyc510

#include "Graph.cpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string edgeString(tuple<string, string, int>); // Useful for printing edges

// int main() {
//   vector<string> nodes = {"A", "B", "C", "D"};
//   Graph graph1;
//   graph1.addNode(1.12314, "A");
//   graph1.addNode(-7.3412, "B");
//   graph1.addNode(420, "C");
//   graph1.addNode(-12423, "D");

//   graph1.addEdge("A","B", 1);
//   graph1.addEdge("B","C", -714234.322323);
//   graph1.addEdge("C","D", 313412341234123);
//   graph1.addEdge("D","A", -3);

//   graph1.saveGraph("Yee");
//   Graph F(string("Yee.txt"));

//   cout << graph1.getInfo();
//   cout << F.getInfo();

//   cout << "\n------------------------------------" << endl;
//   cout << "BFS Algorithm Test:" << endl;

//   string sourceNode = "A";
//   string targetNode = "D";
//   vector<string> path = graph1.BFS(sourceNode, targetNode);

//   cout << "Shortest path from " << sourceNode << "-" << targetNode << ": ";
//   for (const auto& node : path) {
//     cout << node << " ";
//   }
//   cout << endl;

//   cout << "------------------------------------" << endl;
// }


int main() {
    // Test Case 1: Basic Case
    cout << "Test Case 1: Basic Case";
    Graph graph1;
    graph1.addNode(0, "A");
    graph1.addNode(1, "B");
    graph1.addNode(2, "C");
    graph1.addNode(5, "D");
    graph1.addNode(1, "E");
    graph1.addNode(2, "F");
    graph1.addNode(5, "X");

    graph1.addEdge("A", "B", -1);
    graph1.addEdge("B", "C", 2);
    graph1.addEdge("A", "C", 5);
    graph1.addEdge("C", "D", -2);
    graph1.addEdge("E", "A", 0);
    graph1.addEdge("F", "E", 4);

    cout << graph1.getInfo();

    cout << "Dijkstra's Result from A: " << endl;
    auto result1 = graph1.Dijktras("A");
    for (const auto& pair : result1) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "------------------------------------" << endl;

    // Test Case 2: Disconnected Graph
    cout << "Test Case 2: Disconnected Graph";

    cout << "Dijkstra's Result from X: " << endl;
    auto result2 = graph1.Dijktras("X");
    for (const auto& pair : result2) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "------------------------------------" << endl;

    // Test Case 4: Graph with a Single Node
    cout << "Test Case 3: Graph with a Single Node";
    Graph graph3;
    graph3.addNode(0, "N");

    cout << graph3.getInfo();

    cout << "Dijkstra's Result from N: " << endl;
    auto result3 = graph3.Dijktras("N");
    for (const auto& pair : result3) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "------------------------------------" << endl;





    // Separate the graph creation information from the DFS test
    cout << "\n------------------------------------" << endl;
    cout << "DFS Algorithm Test:" << endl;

    // Set the source and target nodes for DFS test
    string sourceNode = "A";
    string targetNode = "D";

    // Test reachableDists to find distances from sourceNode
    cout << "Testing Reachable Dists from " << sourceNode << ":\n";
    vector<pair<string, double>> distances = graph1.reachableDists(sourceNode);

    // Display distances excluding the distance from the source node to itself
    for (const auto& pair : distances) {
        if (pair.first != sourceNode) {
            cout << "Distance from " << sourceNode << " to " << pair.first << ": " << pair.second << "\n";
        }
    }

    // Find the distance from sourceNode to targetNode
    auto targetDistanceIt = find_if(distances.begin(), distances.end(),
                                    [&targetNode](const auto& pair) { return pair.first == targetNode; });

    // Test BFS algorithm to find the shortest path
    vector<string> path = graph1.DFS(sourceNode, targetNode);

    // Display the shortest path from sourceNode to targetNode
    cout << "Shortest path from " << sourceNode << " to " << targetNode << ": ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << endl;

    // End of DFS test
    cout << "------------------------------------" << endl;





    // Separate the graph creation information from the BFS test
    cout << "\n------------------------------------" << endl;
    cout << "BFS Algorithm Test:" << endl;

    // Set the source and target nodes for BFS test
    sourceNode = "A";
    targetNode = "D";

    // Test reachableDists to find distances from sourceNode
    cout << "Testing reachable dists from " << sourceNode << ":\n";
    distances = graph1.reachableDists(sourceNode);

    // Display distances excluding the distance from the source node to itself
    for (const auto& pair : distances) {
        if (pair.first != sourceNode) {
            cout << "Distance from " << sourceNode << " to " << pair.first << ": " << pair.second << "\n";
        }
    }

    // Find the distance from sourceNode to targetNode
    targetDistanceIt = find_if(distances.begin(), distances.end(),
                                    [&targetNode](const auto& pair) { return pair.first == targetNode; });

    // Test BFS algorithm to find the shortest path
    path = graph1.BFS(sourceNode, targetNode);

    // Display the shortest path from sourceNode to targetNode
    cout << "Shortest path from " << sourceNode << " to " << targetNode << ": ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << endl;

    // End of BFS test
    cout << "------------------------------------" << endl;

    
    return 0;
}
