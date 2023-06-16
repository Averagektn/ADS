#include <iostream>

using namespace std;

void heapify(pair<long, int>* arr, int size, int ind) {
    int minInd = ind, left = 2 * ind + 1, right = 2 * ind + 2;
    if (left < size && arr[left] < arr[minInd]) {
        minInd = left;
    }
    if (right < size && arr[right] < arr[minInd]) {
        minInd = right;
    }
    if (minInd != ind) {
        swap(arr[ind], arr[minInd]);
        heapify(arr, size, minInd);
    }
}

int main() {
    int n, m;
    long time;
    pair<long, int> *prs;

    cin >> n >> m;
    prs = new pair<long, int>[n];
    for (int i = 0; i < n; i++) {
        prs[i] = {0, i};
    }
    for (int i = 0; i < m; i++) {
        cin >> time;
        cout << prs[0].second << " " << prs[0].first << endl;
        prs[0].first += time;
        heapify(prs, n, 0);
    }
    return 0;
}