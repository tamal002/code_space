// DISJOINT_SET IMPLEMENTATION [UNION BY SIZE]

#include <bits/stdc++.h>
using namespace std;

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

int main(){
    DisjointSet ds;
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    ds.makeSet(4);
    ds.makeSet(5);
    ds.makeSet(6);
    ds.makeSet(7);

    ds.union_by_size(1, 2);
    ds.union_by_size(2, 3);
    ds.union_by_size(4, 5);
    ds.union_by_size(6, 7);
    ds.union_by_size(5, 6);

    if(ds.find_ultimate_parent(3) == ds.find_ultimate_parent(7)){
        cout << "same component." << endl;
    }
    else cout << "not in same omponent." << endl;

    ds.union_by_size(3, 7);

    if(ds.find_ultimate_parent(3) == ds.find_ultimate_parent(7)){
        cout << "same component." << endl;
    }
    else cout << "not in same omponent." << endl;

    return 0;


}

