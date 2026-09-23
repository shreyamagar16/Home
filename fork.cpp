#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        cout << "CHILD : PID = " << getpid()
             << ", PPID = " << getppid()
             << " -> prints ODD numbers" << endl;

        for (int i = 1; i <= 10; i += 2) {
            cout << " Child (odd) : " << i << endl;
        }
    }
    else {
        // Parent process
        cout << "PARENT: PID = " << getpid()
             << ", PPID = " << getppid()
             << " -> prints EVEN numbers" << endl;

        for (int i = 2; i <= 10; i += 2) {
            cout << " Parent (even): " << i << endl;
        }

        wait(NULL); // Wait for child, reap it

        cout << "PARENT: Child reaped successfully (no zombie left)." << endl;
    }

    return 0;
}