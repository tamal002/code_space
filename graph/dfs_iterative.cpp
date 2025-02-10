#include <bits/stdc++.h>

using namespace std;

// CONSTRUCTING THE GRAPH ACCORDING TO OUR GIVEN AS 2D ARRAY INPUT.
unordered_map<int, list<int>> constructGraph(vector<vector<int>> &input) {
  unordered_map<int, list<int>> graph;
  for (int i = 0; i < input.size(); i++) {
    graph[input[i][0]].push_back(input[i][1]);
  }
  return graph;
}

vector < int > dfs(unordered_map < int, list < int >> & graph, int startNode) {

    // CHECKING IF THE GRAPH IS EMPTY OR NOT.
    if (graph.empty()) {
        cout << "Graph is empty." << endl;
        return {};
    }

    // CHECKING IF THE PASSED START NODE IS VALID NODE / ISOLATED NODE OR NOT.
    if (graph.find(startNode) == graph.end() || graph[startNode].front() == -1) {
        cout << "Error : passed invalid starting node." << endl;
        return {};
    }

    stack < int > st;
    unordered_set < int > visitedList; // TO STORE THE VISITED NODES.
    vector < int > ans; // TO STORE THE TRAVERSAL ORDER.

    // FIRST OF ALL PUSHING THE FIRST NODE INTO THE STACK AND MARKING IT AS VISITED.
    st.push(startNode);
    visitedList.insert(startNode);

    while (!st.empty()) {
        int current = st.top();
        st.pop();
        ans.push_back(current);

        // PUSHING AND MARKING VISITED ALL THE NEIGHBOURS OF CURRENT NODE.
        for (auto i: graph[current]) {
            if (visitedList.find(i) == visitedList.end()) {
                st.push(i);
                visitedList.insert(i);
            }
        }
    }

    return ans;
}

int main() {
  // INPUT GRAPH : {SOURCE NODE, DESTINATION NODE} , UNDIRECTED.
  vector<vector<int>> input = {
    {0,1}, {1, 0}, {1, 4}, {1, 2}, {4, 1}, {4, 3},  {2, 3}, {2, 1},  {2, 5},
      {2, 7}, {2, 8}, {3, 4}, {3, 10}, {3, 9}, {3, 2},  {10, 3},
      {9, 3}, {5, 2}, {5, 6}, {5, 7},  {5, 8}, {6, 5},  {7, 5},
      {7, 2}, {7, 8}, {8, 2}, {8, 5},  {8, 7}, {11, -1}};

  unordered_map<int, list<int>> graph = constructGraph(input);

  // EXPLICITLY PASSING START NODE.
  vector<int> ans = dfs(graph, 1);

  if (ans.size() == 0) {
    cout << "Nothing to traverse." << endl;
  } else {
    cout << "DFS traversal : ";
    for (int i : ans) {
      cout << i << " ";
    }
  }

  return 0;
}