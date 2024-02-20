#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

int numHops(unordered_map<string, vector<string>>& aList, string v1, string v2);
int main() {
unordered_map<string, vector<string>> adjList{ {"A", {"C", "E"}},
{"C", {"A",
"I"}},
{"I", {"C",
"H", "B","D"}},
{"H",
{"I"}},
{"D", {"I",
"B", "G"}},
{"B", {"E",
"F", "G", "D", "I"}},
{"G", {"B",
"D"}},
{"F",
{"B"}},
{"E", {"A",
"B"}}
};
cout << "Number of hops between cities D and A is " << numHops(adjList, "D",
"A") << endl; // Should be 3
cout << "Number of hops between cities A and B is " << numHops(adjList, "A",
"B") << endl; // Should be 2
cout << "Number of hops between cities H and E is " << numHops(adjList, "H",
"E") << endl; // Should be 3
return 0;
}


int numHops(unordered_map<string, vector<string>>& aList, string v1, string v2) {
    if (v1 == v2) return 0;

    unordered_set<string> visited;
    queue<string> frontier;
    int hops = 0;

    frontier.push(v1);
    visited.insert(v1);

    while (!frontier.empty()) {
        int frontierSize = frontier.size();

        for (int i = 0; i < frontierSize; i++) {
            string currentCity = frontier.front();
            frontier.pop();

            for (const string& neighbor : aList[currentCity]) {
                if (neighbor == v2) return ++hops;
                if (visited.find(neighbor) == visited.end()) {
                    frontier.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }

        hops++;
    }

    return -1;
}

