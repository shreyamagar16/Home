#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;
#define SIZE 1024

struct shm_buf
{
    int flag;
    char msg[SIZE];
};

int main()
{
    key_t key = ftok("chatfile", 65);
    int shmid = shmget(key, sizeof(shm_buf), 0666 | IPC_CREAT);
    shm_buf *buf = (shm_buf *)shmat(shmid, NULL, 0);
    cout << "READER ready.\n";

    while (true)
    {
        while (buf->flag == 0);

        if (strcmp(buf->msg, "exit") == 0)
        {
            cout << "Chat ended.\n";
            break;
        }

        cout << "Reader received: " << buf->msg << endl;
        buf->flag = 0;
    }

    shmdt(buf);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}