#include <iostream>
#include <string>
#include <list>

using namespace std;

#define P 1000000007
#define X 263

int hashPol(string s, int size){
    long long res = 0, x = 1;

    for (int i = 0; i < s.size(); i++)
    {
        res += s[i] * x % P;
        x = x * X % P;
    }
    res %= P;
    res %= size;
    return res;
}

bool find(list<string> src, const string& s) {
    list<string> tmp = src;
    while (!tmp.empty()) {
        if (tmp.front() == s) {
            return true;
        }
        tmp.pop_front();
    }
    return false;
}

int main() {
    string str, command;
    int m, n, h, ind;
    list<string> *cell, curr;

    cin >> m >> n;
    cell = new list<string>[m];

    for (int i = 0; i < n; i++) {
        cin >> command;
        if (command != "check") {
            cin >> str;
            h = hashPol(str, m);

            if (command == "add") {
                if (!find(cell[h], str)) {
                    cell[h].push_front(str);
                }
            } else if (command == "del") {
                if (find(cell[h], str)) {
                    cell[h].remove(str);
                }
            } else if (command == "find") {
                if (find(cell[h], str)) {
                    cout << "yes" << endl;
                } else {
                    cout << "no" << endl;
                }
            }
        } else if (command == "check") {
            cin >> ind;
            curr = cell[ind];
            while (!curr.empty()) {
                cout << curr.front() << " ";
                curr.pop_front();
            }
            cout << endl;
        }
    }

    return 0;
}