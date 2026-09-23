#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <number>" << endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        cout << "Child process: PID = " << getpid() << endl;

        execl("./factorial", "factorial", argv[1], (char *)NULL);

        // Executes only if execl fails
        perror("exec failed");
        exit(1);
    }
    else
    {
        // Parent process
        cout << "Parent process: PID = " << getpid() << endl;

        wait(NULL);
        cout << "Child process completed." << endl;
    }

    return 0;
}