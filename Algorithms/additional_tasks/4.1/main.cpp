#include <iostream>
#include <vector>

using namespace std;

int find_set(const int *parent, int v) {
    while (v != parent[v]) {
        v = parent[v];
    }
    return v;
}

int union_sets(int *par, int *rng, int *rec, int d, int s, int max) {
    d = find_set(par, d);
    s = find_set(par, s);
    if (d != s) {
        if (rng[d] < rng[s]) {
            swap(d, s);
        }
        rec[d] += rec[s];
        rec[s] = 0;
        if (max < rec[d]) {
            max = rec[d];
        }
        par[s] = d;
        if (rng[d] == rng[s]) {
            rng[d]++;
        }
    }
    return max;
}

int main() {
    int *parent, *rang, *records, maximum = 0, n, m, dest, src;

    cin >> n >> m;
    parent = new int[n];
    rang = new int[n];
    records = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> records[i];
        if (maximum < records[i])
            maximum = records[i];
        parent[i] = i;
        rang[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> dest >> src;
        maximum = union_sets(parent, rang, records, dest - 1, src - 1, maximum);
        cout << maximum << endl;
    }

    return 0;
}