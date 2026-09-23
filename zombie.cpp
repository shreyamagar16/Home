#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        cout << "CHILD : PID = "
             << getpid()
             << " exiting now -> becomes ZOMBIE."
             << endl;
    }
    else {
        // Parent process
        cout << "PARENT: PID = "
             << getpid()
             << " sleeping, NOT calling wait()."
             << endl;

        cout << "Run 'ps -el | grep defunct' in another terminal to see the zombie."
             << endl;

        sleep(2);
    }

    return 0;
}