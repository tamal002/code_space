// KRUSKAL ALGORITHM

#include <bits/stdc++.h>
using namespace std;

// DisjointSet IMPLEMENTATION [UNION BY SIZE].
class DisjointSet{
    private:
    unordered_map<int, int> size, parent;

    public:

    void makeSet(int x){
        size[x] = 1;
        parent[x] = x;
    }

    int find_ultimate_parent(int node){
        if(node == parent[node]) return node;
        return parent[node] = find_ultimate_parent(parent[node]); // PATH COMPRESSING
    }

    void union_by_size(int u, int v){
        int ulp_u = find_ultimate_parent(u);
        int ulp_v = find_ultimate_parent(v);

        if(ulp_u == ulp_v) return;
        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

// GRAPH CONSTRUCTION.
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

// KRUSKAL ALGORITHM IMPLEMENTATION.
map<int, vector<pair<int, int>>> kruskal(map<int, vector<pair<int, int>>> &graph){
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> edges;
    DisjointSet ds;
    for(auto &i : graph){
        ds.makeSet(i.first);
        for(auto j : i.second){
            edges.push({j.second, {i.first, j.first}});
        }
    }
    
    map<int, vector<pair<int, int>>> ans;
    while(!edges.empty()){
        int u = edges.top().second.first;
        int v = edges.top().second.second;
        int cost = edges.top().first;
        edges.pop();
        if(ds.find_ultimate_parent(u) != ds.find_ultimate_parent(v)){
            ans[u].push_back({v, cost});
            ds.union_by_size(u, v);
        }
    }
    
    return ans;
    
}

void printList(map<int, vector<pair<int, int>>> &graph)
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
    vector<vector<int>> input = {{1, 6, 10}, {6, 1, 10}, {6, 5, 25}, {5, 6, 25}, {5, 4, 22}, {4, 5, 22}, {4, 7, 18}, {7, 4, 18}, {7, 5, 24}, {5, 7, 24}, {7, 2, 14}, {2, 7, 14}, {1, 2, 28}, {2, 1, 28}, {2, 3, 16}, {3, 2, 16}, {3, 4, 12}, {4, 3, 12}};
    map<int, vector<pair<int, int>>> graph = constructGraph(input);
    map<int, vector<pair<int, int>>> ans =  kruskal(graph);
    printList(ans);
    return 0;
}



