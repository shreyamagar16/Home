#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(2); // Child outlives parent

        cout << "CHILD : now an ORPHAN. PID = "
             << getpid()
             << ", new PPID = "
             << getppid()
             << endl;
    }
    else {
        // Parent process
        cout << "PARENT: PID = "
             << getpid()
             << " exiting immediately."
             << endl;
    }

    return 0;
}