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

int chooseMinCost(map<int, int> &curCost, set <int> &visit){
    int curPoint = -1;
    int minCost = INT_MAX;
    for(auto i : curCost){
        if(i.second != -1 && visit.find(i.first) == visit.end() && i.second < minCost){
            minCost = i.second;
            curPoint = i.first;
        }
    }
    return curPoint;
}

map<int, int> dijkstraShortestPath(map<int, vector<pair<int, int>>> &graph, int source){
    map<int, int> curCost;
    for(auto i : graph){
        curCost[i.first] = -1;
    }
    set<int>  visit;
    
    //INITIAL STEP
    curCost[source] = 0;
    for(auto i : graph[source]){
        curCost[i.first] = i.second;
    }
    
    visit.insert(source);
    
    // REPEATITIVE STEP.
    while(visit.size() < graph.size()){
        int curPoint = chooseMinCost(curCost, visit);
        
        // RELAXATION
        for(auto i : graph[curPoint]){
            if(i.first == -1) continue; // NO OUT-GOING EDGE.
            if(i.second + curCost[curPoint] < curCost[i.first] || curCost[i.first] == -1){
                curCost[i.first] = i.second + curCost[curPoint];
            }
        }
        visit.insert(curPoint);
    }
    
    return curCost;
}




void printList(map<int, int> &result, int source){
    cout << "SOURCE ---> DESTINATION COST:" << endl;
    for(auto i : result){
        cout << source << " --> " << i.first << " : " << i.second << endl;
    }
}

// DRIVER CODE
int main()
{
    vector<vector<int>> input = {{1, 2, 2}, {1, 3, 4}, {2, 3, 1}, {2, 4, 7}, {3, 5, 3}, {4, 6, 1}, {5, 6, 5}, {6, -1, -1}, {5, 4, 2}};
    map<int, vector<pair<int, int>>> graph = constructGraph(input);
    int source = 1;
    map<int, int> result = dijkstraShortestPath(graph, source);
    printList(result, source);
    return 0;
}