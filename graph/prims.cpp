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

map<int, vector<pair<int, int>>> primsMinSpanningTree(map<int, vector<pair<int, int>>> &graph){
    
    // REQUIRED CONTAINERS
    set<int> visit;
    map<int, vector<pair<int, int>>> ans;
    set<pair<int, pair<int, int>>> s; 
    
    // FINDING THE MINIMUM WEIGHTED EDGE.
    int start = -1;
    int dest = -1;
    int cost = INT_MAX;
    for(auto &i : graph){
        for(auto &j : i.second){
            if(j.second < cost){
                cost = j.second;
                start = i.first;
                dest = j.first;
            }
        }
    }
    
    ans[cost].push_back({start, dest});
    visit.insert(start);
    visit.insert(dest);
    for(auto &i: graph){
        if(i.first == start || i.first == dest){
            for(auto &j : i.second){
                s.insert({j.second, {i.first, j.first}});
            }
        }
    }
    
    while(!s.empty()){
        auto smallest = *s.begin();
        start = smallest.second.first;
        dest = smallest.second.second;
        cost = smallest.first;
        s.erase(s.begin());
        if(visit.find(dest) != visit.end()) continue;
        else{
            for(auto &i : graph[dest]){
                s.insert({i.second, {dest, i.first}});
            }
            ans[cost].push_back({start, dest});
            visit.insert(dest);
        }
        
    }
    
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
            cout << "edge between " << j.first << " and " << j.second << " => cost : " << i.first << endl;
        }
    }
}

int main()
{
    vector<vector<int>> input = {{1, 6, 10}, {6, 1, 10}, {6, 5, 25}, {5, 6, 25}, {5, 4, 22}, {4, 5, 22}, {4, 7, 18}, {7, 4, 18}, {7, 5, 24}, {5, 7, 24}, {7, 2, 14}, {2, 7, 14}, {1, 2, 28}, {2, 1, 28}, {2, 3, 16}, {3, 2, 16}, {3, 4, 12}, {4, 3, 12}};
    map<int, vector<pair<int, int>>> graph = constructGraph(input);
    map<int, vector<pair<int, int>>> ans = primsMinSpanningTree(graph);
    printList(ans);
    return 0;
}
