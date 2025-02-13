#include <bits/stdc++.h>
using namespace std;

struct  Node
{
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// ADDING NODES LEVEL WISE.
Node* addNode(Node* root, int value){
    if(root == nullptr){
        root = new Node(value);
        return root;
    }
    queue <Node*> q;
    q.push(root);
    Node* current = q.front();
    while(current -> left != nullptr && current -> right != nullptr){
        q.pop();
        q.push(current -> left);
        q.push(current -> right);
        current = q.front();
    }
    if(current -> left == nullptr) current -> left = new Node(value);
    else current -> right = new Node(value);
    return root;
}
 
void dfs_root_to_leaf_rec(vector<int> ans, Node* root){
    // BASE CASE.
    if(root == nullptr || root -> data == -1){
        return;
    }

    ans.push_back(root -> data);
    if(root -> left == nullptr && root -> right == nullptr){
        for(int i : ans){
            cout << i << " ";
        }
        cout << endl;
    }
    else{
        dfs_root_to_leaf_rec(ans, root -> left);
        dfs_root_to_leaf_rec(ans, root -> right);
    }
    ans.pop_back();
}

void printTree(Node* root){
    if(root == nullptr){
        cout << "Tree is empty." << endl;
        return;
    }
    vector<int> ans;
    dfs_root_to_leaf_rec(ans, root);
}

int main(){
    Node* root = nullptr;

    printTree(root);

    // ADDING NODES.[-1 --> null]
    root = addNode(root, 1);
    root = addNode(root, 2);
    root = addNode(root, 3);
    root = addNode(root, -1);
    root = addNode(root, 5);
    root = addNode(root, 6);
    root = addNode(root, 7);

    //PRINTING THE TREE FROMT ROOT TO EVERY LEAF.
    printTree(root);

    return 0;
}