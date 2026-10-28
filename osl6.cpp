#include <iostream>
using namespace std;

void allocate(int b[], int nb, int p[], int np, int choice) {
    int block[100], alloc[100];

    for (int i = 0; i < nb; i++)
        block[i] = b[i];

    for (int i = 0; i < np; i++)
        alloc[i] = -1;

    for (int i = 0; i < np; i++) {
        int pos = -1;

        for (int j = 0; j < nb; j++) {
            if (block[j] >= p[i]) {
                if (choice == 1) {
                    pos = j;
                    break;
                }
                if (choice == 2 && (pos == -1 || block[j] < block[pos]))
                    pos = j;
                if (choice == 3 && (pos == -1 || block[j] > block[pos]))
                    pos = j;
            }
        }

        if (pos != -1) {
            alloc[i] = pos;
            block[pos] -= p[i];
        }
    }

    if (choice == 1)
        cout << "\n--- First Fit ---\n";
    else if (choice == 2)
        cout << "\n--- Best Fit ---\n";
    else
        cout << "\n--- Worst Fit ---\n";

    cout << "Process\tSize\tBlock\n";

    for (int i = 0; i < np; i++) {
        cout << "P" << i + 1 << "\t" << p[i] << "\t";

        if (alloc[i] != -1)
            cout << "B" << alloc[i] + 1;
        else
            cout << "Not Allocated";

        cout << "\n";
    }
}

int main() {
    int b[100], p[100];
    int nb, np, choice;

    cout << "Enter number of memory blocks (1-100): ";
    cin >> nb;

    if (nb < 1 || nb > 100) {
        cout << "Invalid number of blocks!\n";
        return 1;
    }

    for (int i = 0; i < nb; i++) {
        cout << "Enter size of block B" << i + 1 << ": ";
        cin >> b[i];

        if (b[i] <= 0) {
            cout << "Block size must be positive!\n";
            return 1;
        }
    }

    cout << "\nEnter number of processes (1-100): ";
    cin >> np;

    if (np < 1 || np > 100) {
        cout << "Invalid number of processes!\n";
        return 1;
    }

    for (int i = 0; i < np; i++) {
        cout << "Enter size of process P" << i + 1 << ": ";
        cin >> p[i];

        if (p[i] <= 0) {
            cout << "Process size must be positive!\n";
            return 1;
        }
    }

    do {
        cout << "\n===== Memory Allocation Menu =====\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Run All Strategies\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                allocate(b, nb, p, np, 1);
                break;

            case 2:
                allocate(b, nb, p, np, 2);
                break;

            case 3:
                allocate(b, nb, p, np, 3);
                break;

            case 4:
                allocate(b, nb, p, np, 1);
                allocate(b, nb, p, np, 2);
                allocate(b, nb, p, np, 3);
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            case 6:
            cout << "Display remaining blocks.\n";

            for (int i = 0; i < nb; i++)
                cout << "B" << i + 1 << ": " << b[i] << endl;

            break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}