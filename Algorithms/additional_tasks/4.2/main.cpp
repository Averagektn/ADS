#include <iostream>

using namespace std;

int find_set(const int *par, int v) {
    while (v != par[v]){
        v = par[v];
    }
    return v;
}

void union_sets(int *rng, int *par, int a, int b) {
    a = find_set(par, a);
    b = find_set(par, b);
    if (a != b) {
        if (rng[a] < rng[b])
            swap(a, b);
        par[b] = a;
        if (rng[a] == rng[b])
            rng[a]++;
    }
}

int main() {
    int n, e, d, a, b, *parent, *rang;;
    bool flag = true;

    cin >> n >> e >> d;
    parent = new int[n];
    rang = new int[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rang[i] = 0;
    }

    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        union_sets(rang, parent, a - 1, b - 1);
    }

    for (int i = 0; i < d; i++) {
        cin >> a >> b;
        if (find_set(parent, a - 1) == find_set(parent, b - 1))
            flag = false;
    }

    if (flag){
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}