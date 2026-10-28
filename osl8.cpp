
#include <iostream>
using namespace std;

const int N = 8;

int requests[N] = {98, 183, 37, 122, 14, 124, 65, 67};

int disk = 200;

int absDiff(int a, int b) {
    return (a > b) ? a - b : b - a;
}

void fcfs(int head) {
    int cur = head, total = 0;

    cout << "\n--- FCFS ---\nSeek order: " << cur;

    for (int i = 0; i < N; i++) {
        total += absDiff(requests[i], cur);
        cur = requests[i];
        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << endl;
}

void sstf(int head) {
    int r[N], done[N] = {0};
    int cur = head, total = 0;

    for (int i = 0; i < N; i++)
        r[i] = requests[i];

    cout << "\n--- SSTF ---\nSeek order: " << cur;

    for (int c = 0; c < N; c++) {
        int idx = -1, best = 999999;

        for (int i = 0; i < N; i++) {
            if (!done[i] && absDiff(r[i], cur) < best) {
                best = absDiff(r[i], cur);
                idx = i;
            }
        }

        done[idx] = 1;
        total += best;
        cur = r[idx];

        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << endl;
}

void sortRequests(int r[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (r[j] > r[j + 1]) {
                int temp = r[j];
                r[j] = r[j + 1];
                r[j + 1] = temp;
            }
        }
    }
}

void scan(int head) {
    int r[N + 2], n = 0;
    int cur = head, total = 0;

    for (int i = 0; i < N; i++)
        r[n++] = requests[i];

    r[n++] = 0;
    r[n++] = disk - 1;

    sortRequests(r, n);

    int pos = 0;
    while (pos < n && r[pos] < head)
        pos++;

    cout << "\n--- SCAN (towards larger end) ---\nSeek order: " << cur;

    for (int i = pos; i < n; i++) {
        if (r[i] == cur)
            continue;

        total += absDiff(r[i], cur);
        cur = r[i];

        cout << " -> " << cur;
    }

    for (int i = pos - 1; i >= 0; i--) {
        total += absDiff(r[i], cur);
        cur = r[i];

        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << endl;
}

void cscan(int head) {
    int r[N + 2], n = 0;
    int cur = head, total = 0;

    for (int i = 0; i < N; i++)
        r[n++] = requests[i];

    r[n++] = 0;
    r[n++] = disk - 1;

    sortRequests(r, n);

    int pos = 0;
    while (pos < n && r[pos] < head)
        pos++;

    cout << "\n--- C-SCAN ---\nSeek order: " << cur;

    for (int i = pos; i < n; i++) {
        if (r[i] == cur)
            continue;

        total += absDiff(r[i], cur);
        cur = r[i];

        cout << " -> " << cur;
    }

    if (cur != 0) {
        total += absDiff(cur, 0);
        cur = 0;
        cout << " -> " << cur;
    }

    for (int i = 0; i < pos; i++) {
        if (r[i] == cur)
            continue;

        total += absDiff(r[i], cur);
        cur = r[i];

        cout << " -> " << cur;
    }

    cout << "\nTotal seek time = " << total << endl;
}

int main() {
    int head = 53;

    cout << "Requests: ";
    for (int i = 0; i < N; i++)
        cout << requests[i] << " ";

    cout << "\nHead start = " << head;
    cout << ", Disk size = " << disk << endl;

    fcfs(head);
    sstf(head);
    scan(head);
    cscan(head);

    return 0;
}
