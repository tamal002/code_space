#include <bits/stdc++.h>
using namespace std;

// CONSTRUCT GRAPH
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

map<int, int> dijkstraShortestPath(map<int, vector<pair<int, int>>> &graph, int source)
{
    set<int> visit;
    map<int, int> curCost;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // MIN_HEAP
    pq.push({0, source});
    for (auto &pair : graph)
    {
        if (pair.first == source)
        {
            curCost[pair.first] = 0;
        }
        else
        {
            curCost[pair.first] = INT_MAX;
        }
    }

    while (!pq.empty())
    {
        int curNode = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        if (visit.find(curNode) != visit.end())
            continue;
        else
        {
            visit.insert(curNode);
        }
        for (auto &i : graph[curNode])
        {
            if (i.second == -1)
                continue; // NO OUTGOING EDGE.
            if (cost + i.second < curCost[i.first])
            {
                curCost[i.first] = cost + i.second;
                pq.push({curCost[i.first], i.first});
            }
        }
    }

    return curCost;
}

void printList(map<int, int> &result, int source)
{
    cout << "SOURCE ---> DESTINATION COST:" << endl;
    for (auto i : result)
    {
        if (i.second == INT_MAX)
        {
            cout << source << " --> " << i.first << " : " << "unreachable" << endl;
        }
        else
        {
            cout << source << " --> " << i.first << " : " << i.second << endl;
        }
    }
}

// DRIVER CODE
int main()
{
    vector<vector<int>> input = {{1, 2, 2}, {1, 3, 4}, {2, 3, 1}, {2, 4, 7}, {3, 5, 3}, {4, 6, 1}, {5, 6, 5}, {6, -1, -1}, {5, 4, 2}};
    map<int, vector<pair<int, int>>> graph = constructGraph(input);
    int source = 5;
    map<int, int> result = dijkstraShortestPath(graph, source);
    printList(result, source);
    return 0;
}