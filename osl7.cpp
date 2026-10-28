
#include <iostream>
using namespace std;

int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3,
               0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

const int RS = sizeof(pages) / sizeof(pages[0]);
const int FR = 3;

void show(int f[]) {
    cout << " Frames: ";
    for (int i = 0; i < FR; i++) {
        if (f[i] == -1)
            cout << "- ";
        else
            cout << f[i] << " ";
    }
    cout << endl;
}

void fifo() {
    int f[FR], ptr = 0, faults = 0;

    for (int i = 0; i < FR; i++)
        f[i] = -1;

    cout << "\n===== FIFO =====\n";

    for (int i = 0; i < RS; i++) {
        bool hit = false;

        for (int j = 0; j < FR; j++) {
            if (f[j] == pages[i])
                hit = true;
        }

        if (!hit) {
            f[ptr] = pages[i];
            ptr = (ptr + 1) % FR;
            faults++;
            cout << "Page " << pages[i] << " -> FAULT";
        } else {
            cout << "Page " << pages[i] << " -> HIT";
        }

        show(f);
    }

    cout << "Total Page Faults (FIFO) = " << faults << endl;
}

void lru() {
    int f[FR], last[FR], faults = 0;

    for (int i = 0; i < FR; i++) {
        f[i] = -1;
        last[i] = -1;
    }

    cout << "\n===== LRU =====\n";

    for (int i = 0; i < RS; i++) {
        int hit = -1;

        for (int j = 0; j < FR; j++) {
            if (f[j] == pages[i])
                hit = j;
        }

        if (hit == -1) {
            int lru = 0;

            for (int j = 1; j < FR; j++) {
                if (last[j] < last[lru])
                    lru = j;
            }

            f[lru] = pages[i];
            last[lru] = i;
            faults++;

            cout << "Page " << pages[i] << " -> FAULT";
        } else {
            last[hit] = i;
            cout << "Page " << pages[i] << " -> HIT";
        }

        show(f);
    }

    cout << "Total Page Faults (LRU) = " << faults << endl;
}

void optimal() {
    int f[FR], faults = 0;

    for (int i = 0; i < FR; i++)
        f[i] = -1;

    cout << "\n===== Optimal =====\n";

    for (int i = 0; i < RS; i++) {
        bool hit = false;

        for (int j = 0; j < FR; j++) {
            if (f[j] == pages[i])
                hit = true;
        }

        if (!hit) {
            int idx = -1;
            int farthest = -1;

            for (int j = 0; j < FR; j++) {
                if (f[j] == -1) {
                    idx = j;
                    break;
                }

                int k;
                for (k = i + 1; k < RS; k++) {
                    if (pages[k] == f[j])
                        break;
                }

                if (k > farthest) {
                    farthest = k;
                    idx = j;
                }
            }

            f[idx] = pages[i];
            faults++;

            cout << "Page " << pages[i] << " -> FAULT";
        } else {
            cout << "Page " << pages[i] << " -> HIT";
        }

        show(f);
    }

    cout << "Total Page Faults (Optimal) = " << faults << endl;
}

int main() {
    cout << "Reference string: ";

    for (int i = 0; i < RS; i++)
        cout << pages[i] << " ";

    cout << "\nNumber of frames = " << FR << endl;

    fifo();
    lru();
    optimal();

    return 0;
}
