#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define P 1000000007
#define X 263

int hashPol(const string s){
    long long res = 0, x = 1;

    for (char i : s) {
        res += i * x % P;
        x = x * X % P;
    }
    res %= P;
    return res;
}

int main() {
    string pattern, text;
    long long x = 1, patternHash, *windows;
    int search;
    cin >> pattern >> text;

    for (int i = 0; i < pattern.length() - 1; i++){
        x = x * X % P;
    }
    patternHash = hashPol(pattern);
    search = text.length() - pattern.size() + 1;
    windows = new long long[search];

    for (int i = search - 1; i >= 0; i--){
        if (i == search - 1) {
            windows[i] = hashPol(text.substr(i, pattern.size()));
        } else {
            windows[i] = ((windows[i + 1] - text[i + pattern.size()] * x % P) * X % P + text[i] + P) % P;
        }
    }

    for (int i = 0; i < search; i++){
        if (patternHash == windows[i]){
            if (pattern == text.substr(i, pattern.size())) {
                cout << i << " ";
            }
        }
    }

    return 0;
}