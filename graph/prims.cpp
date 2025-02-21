#include <bits/stdc++.h>
using namespace std;

// CONTRUC THE GRAPH FIRST.
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


map<int, vector<pair<int, int>>> primsMinSpanningTree(map<int, vector<pair<int, int>>> &graph, int startNode){
    
    // CHECKING IF THE START_NODE IS ISOLATED OR NOT.
    for(auto &i : graph[startNode]){
        if(i.first == -1){
            cout << "INVALID START NODE." << endl;
            return {};
        }
    }
    
    //CHECKING IF THE NODE IS ACTUALLY PRESENT IN GRAPH OR NOT.
    if(graph.find(startNode) == graph.end()){
        cout << "INVALID START NODE." << endl;
        return {};
    }
    
    
    // REQUIRED CONTAINERS.
    set<int> visit;
    map<int, vector<pair<int, int>>> ans;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq; //[MIN_HEAP]
    int minCost = 0;
    
    pq.push({0, {startNode, -1}});
    
    while(!pq.empty()){
        int start = pq.top().second.first;
        int dest = pq.top().second.second;
        int cost = pq.top().first;
        
        pq.pop();
        
        if(dest == -1){
            visit.insert(start);
        
            // PUSHING ALL THE EDGES ASSOCIATED WITH startNode
            for(auto &i : graph[start]){
                pq.push({i.second, {start, i.first}});
            }
        }
        else if(visit.find(dest) != visit.end()) continue;
        else{
            for(auto &i : graph[dest]){
                pq.push({i.second, {dest, i.first}});
            }
            ans[start].push_back({dest, cost});
            minCost += cost;
            visit.insert(dest);
        }
    }
    
    
    cout << "TOTAL MINIMUM COST : " << minCost << endl;
    
    return ans;
    
}


void printList(map<int, vector<pair<int, int>>> &ans){
    if(ans.size() == 0){
        cout << "NOTHING TO PRINT." << endl;
        return;
    }
    
    cout << "TAKEN EDGES." << endl;
    for(auto &i : ans){
        for(auto &j : i.second){
            cout << "edge between " << i.first << " and " << j.first << " => cost : " << j.second << endl;
        }
    }
}

int main()
{
    vector<vector<int>> input = {{1, 6, 10}, {6, 1, 10}, {6, 5, 25}, {5, 6, 25}, {5, 4, 22}, {4, 5, 22}, {4, 7, 18}, {7, 4, 18}, {7, 5, 24}, {5, 7, 24}, {7, 2, 14}, {2, 7, 14}, {1, 2, 28}, {2, 1, 28}, {2, 3, 16}, {3, 2, 16}, {3, 4, 12}, {4, 3, 12}};
    map<int, vector<pair<int, int>>> graph = constructGraph(input);
    map<int, vector<pair<int, int>>> ans = primsMinSpanningTree(graph, 5);
    printList(ans);
    return 0;
}
