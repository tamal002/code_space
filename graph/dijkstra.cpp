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

set<int> findReachableNodes(map<int, vector<pair<int, int>>> &graph, int source){
    set<int> reachableNode;
    queue<int> q;
    q.push(source);
    while(!q.empty()){
        int cur = q.front();
        reachableNode.insert(cur);
        q.pop();
        for(auto &i : graph[cur]){
            if(i.second == -1) continue;
            q.push(i.first);
        }
    }
    return reachableNode;
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

// TC => O(V * V * logV + E)
map<int, int> dijkstraShortestPath(map<int, vector<pair<int, int>>> &graph, int source){
    map<int, int> curCost;
    
    // TC => O(V * logv)
    for(auto i : graph){  
        curCost[i.first] = -1;
    }
    
    set<int>  visit;
    
    // TC => ALREADY CONSIDERED.
    set<int> reachableNode = findReachableNodes(graph, source);
    
    //INITIAL STEP
    // TC => O(V logV)
    curCost[source] = 0;
    for(auto i : graph[source]){
        curCost[i.first] = i.second;
    }
    
    // TC => O(logV)
    visit.insert(source);
    
    // REPEATITIVE STEP.
    // LOOP WILL RUN ATMOST V TIMES.
    while(visit.size() < reachableNode.size()){
        
        // TC => O(V logV)
        int curPoint = chooseMinCost(curCost, visit);
        
        // RELAXATION
        // LOOP WILL RUN ATMOST V TIMES.
        // INSIDE THE ATMOST E NUMBER OF RELAXATION CAN BE HAPPENED.
        // TC => O(V * logV + E)
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


/******************** COMPLEXITY ANALYSUS **********************************
 
TIME COMPLEXITY:

1) FOR CONTRUCTION GRAPH => NUMBER OF EDGES = E, NUMBER OF NODES/VERTEX = V. WE'VE USED MAP DATA STRUCTURE TO CONSTRUCT THE GRAPH..
    SO LOOP WILL WILL RUN FOR ALL EDGES [E TIMES], AND INSIDE THE LOOP MAP INSERTION HAPPENS. THE FINAL MAP SIZE WILL BE EQUAL TO THE NUMBER OF TOTAL NODES/VERTEX [V]. SO OVERALL TIME COMPLEXITY WILL BE 
        O(E * logV)
        
2) FOR "findReachableNodes" FUNCTION => THIS IS TYPICAL BFS TRAVERSAL WHERE EACH NODE IS BEING VISITED ONCE AND EACH EDGE IS BEING VISITED ONCE. SO TC WILL BE O(E + V)

3) FOR "chooseMinCost" FUNCTION => HERE "curCost" IS SIZE OF V BECUZ ALL NODES ARE LISTED HERE. FOOR LOOP WILL ITERATE ACCROSS THE ENTIRE "curCost" [V TIMES]. AND INSIDE THE LOOP AN "MAP SEARCHING" HAPPENS WHICH TAHKES [log V] TIMES TO SEARCH BECAUSE ATMOST SIZE OF THE "visit" WILL BE V. SO OVERALL TC WILL BE O(V * logV)

4) FOR "dijkstraShortestPath" FUNCTION => O(V * V * logV + E)

CONCLUSION :: OVERALL TIME COMPLEXITY => O(E logV) + O(E + V) + O(V * logV) + O(V * V * logV + E) ------> O(V * V * logV + E) -----> O(N*N) [MOST PRECISELY TO BE SAID, N = NUMBER OF NODES]

*/