#include <iostream>
#include <list>

using namespace std;

struct num{
    int src, dst;
};

void siftDown(int *nums, int ind, int size, list<num> *swaps){
    int minInd = ind, l = ind * 2 + 1, r = ind * 2 + 2;
    if (l < size && nums[l] < nums[minInd]){
        minInd = l;
    }
    if (r < size && nums[r] < nums[minInd]){
        minInd = r;
    }
    if (ind != minInd){
        swap(nums[ind], nums[minInd]);
        swaps->push_front({ind, minInd});
        siftDown(nums, minInd, size, swaps);
    }
}

int main() {
    int n, *arr;
    list<num> swaps;
    cin >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for (int i = n / 2 - 1; i >= 0; i--){
        siftDown(arr, i, n, &swaps);
    }
    cout << swaps.size() << endl;
    while(!swaps.empty()){
        cout << swaps.back().src << ' ' << swaps.back().dst << endl;
        swaps.pop_back();
    }

    return 0;
}