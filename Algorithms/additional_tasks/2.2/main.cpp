#include <iostream>
using namespace std;

void count(int src[], int i, int height[]) {
    if (height[i])
        return;
    if (src[i] == -1) {
        height[i] = 1;
        return;
    }
    if (height[src[i]] == 0)
        count(src, src[i], height);
    height[i] = height[src[i]] + 1;
}


int findHeight(int src[], int n) {
    int height[n], res;

    for (int i = 0; i < n; i++)
        height[i] = 0;

    for (int i = 0; i < n; i++)
        count(src, i, height);

    res = height[0];
    for (int i = 1; i < n; i++)
        if (res < height[i])
            res = height[i];
    return res;
}

int main()
{
    int *arr, size;

    cin >> size;
    arr = new int[size];

    for (int i = 0; i < size; i++){
        cin >> arr[i];
    }

    cout << findHeight(arr, size);
    return 0;
}
