#include <iostream>

using namespace std;

struct node{
    int value, left, right;
};

bool inorder(const node *arr, int ind, int left, int right){
    if (ind == -1){
        return true;
    }
    if (!inorder(arr, arr[ind].left, left, arr[ind].value)){
        return false;
    }
    if (left >= arr[ind].value || arr[ind].value >= right) {
        return false;
    }
    if (!inorder(arr, arr[ind].right, arr[ind].value, right)){
        return false;
    }

    return true;
}

int main() {
    node *tree;
    int n;

    cin >> n;
    tree = new node[n];
    for (int i = 0; i < n; i++){
        cin >> tree[i].value >> tree[i].left >> tree[i].right;
    }

    if (n < 1 || inorder(tree, 0, INT32_MIN, INT32_MAX)){
        cout << "CORRECT";
    } else {
        cout << "INCORRECT";
    }

    return 0;
}