#include <iostream>
#include <stack>

using namespace std;

struct node{
    int num, max;
};

int main() {
    stack<node> left, right;
    int n, m, *arr, maxNum = 0;

    cin >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cin >> m;

    for (int i = 0; i < m; i++){
        if (arr[i] > maxNum)
            maxNum = arr[i];
        left.push({arr[i], maxNum});
    }

    for (int i = m; i < n; i++){
        if (left.empty() || right.empty()){
            maxNum = left.empty() ? right.top().max : left.top().max;
        } else {
            maxNum = max(left.top().max, right.top().max);
        }

        cout << maxNum << ' ';

        if (right.empty()){
            while (!left.empty()){
                int elem = left.top().num;
                if (right.empty())
                    right.push({elem, elem});
                else
                    right.push({elem, max(elem, right.top().max)});
                left.pop();
            }
        }
        right.pop();
        maxNum = left.empty() ? arr[i] : max(left.top().max, arr[i]);
        left.push({arr[i], maxNum});
    }
    if(left.empty())
        cout << right.top().max;
    else if (right.empty())
        cout << left.top().max;
    else
        cout << max(left.top().max, right.top().max);


    return 0;
}