#include <iostream>
#include <cstring>

#define MAX_SIZE 10000000

using namespace std;

char my_map[MAX_SIZE][20];

int main() {
    int n, num;
    string request;
    char name[20];

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> request;
        if (request == "add") {
            cin >> num >> name;
            strcpy(my_map[num], name);
        } else if (request == "del") {
            cin >> num;
            my_map[num][0] = '\0';
        } else {
            cin >> num;
            if (!my_map[num][0])
                cout << "not found\n";
            else
                cout << my_map[num] << "\n";
        }
    }
    return 0;
}