#include <bits/stdc++.h>
using namespace std;

map<int, vector<pair<int, int>>> constructGraph(vector<vector<int>> &input)
{
    if (input.size() == 0)
    {
        cout << "invalid input" << endl;
        return {};
    }
    map<int, vector<pair<int, int>>> graph;
    for (int i = 0; i < input.size(); i++)
    {
        graph[input[i][0]].push_back({input[i][1], input[i][2]});
    }
    return graph;
}

void printGraph(map<int, vector<pair<int, int>>> &graph)
{
    for (auto i : graph)
    {
        cout << i.first << ": ";
        for (auto j : i.second)
        {
            if(j.first == -1){
                cout << "No path avialable" << endl;
            }
            else{
                cout << j.first << " cost: " << j.second << ",   ";
            }
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> input = {{1, 2, 2}, {1, 3, 4}, {2, 3, 1}, {2, 4, 7}, {3, 5, 3}, {4, 6, 1}, {5, 6, 5}, {6, -1, -1}, {5, 4, 2}};
    map<int, vector<pair<int, int>>> graph = constructGraph(input);
    printGraph(graph);
    return 0;
}