#include <iostream>

using namespace std;

struct node{
    int value, left, right;
};

void preorder(const node *arr, int ind){
    if (ind == -1){
        return;
    }
    cout << arr[ind].value << ' ';
    preorder(arr, arr[ind].left);
    preorder(arr, arr[ind].right);
}

void inorder(const node *arr, int ind){
    if (ind == -1){
        return;
    }
    inorder(arr, arr[ind].left);
    cout << arr[ind].value << ' ';
    inorder(arr, arr[ind].right);
}

void postorder(const node *arr, int ind){
    if (ind == -1){
        return;
    }
    postorder(arr, arr[ind].left);
    postorder(arr, arr[ind].right);
    cout << arr[ind].value << ' ';
}

int main() {
    node *tree;
    int n;

    cin >> n;
    tree = new node[n];
    for (int i = 0; i < n; i++){
        cin >> tree[i].value >> tree[i].left >> tree[i].right;
    }

    inorder(tree, 0);
    cout << endl;
    preorder(tree, 0);
    cout << endl;
    postorder(tree, 0);

    return 0;
}