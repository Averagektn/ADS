#include <iostream>
#include <queue>

using namespace std;

struct packet{
    int arrival, duration;
};

int main()
{
    int size, n, currTime = 0;
    packet *packets;
    queue<int> time;

    cin >> size >> n;
    cout << endl;

    packets = new packet[n];
    for (int i = 0; i < n; i++){
        cin >> packets[i].arrival >> packets[i].duration;
    }

    for (int i = 0; i < n; i++) {

        while (!time.empty() && time.front() <= packets[i].arrival)
            time.pop();

        if (currTime < packets[i].arrival) {
            cout << packets[i].arrival << endl;
            currTime = packets[i].arrival + packets[i].duration;
            time.push(currTime);
        } else if (time.size() < size) {
            cout << currTime << endl;
            currTime += packets[i].duration;
            time.push(currTime);
        } else {
            cout << -1 << endl;
        }
    }

    return 0;
}
