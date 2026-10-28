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
    cout << "Key = " << key << endl;
    int shmid = shmget(key, sizeof(shm_buf), 0666 | IPC_CREAT);
    shm_buf *buf = (shm_buf *)shmat(shmid, NULL, 0);
    buf->flag = 0;

    cout << "WRITER ready. Type 'exit' to quit.\n";

    while (true)
    {
        while (buf->flag == 1);
        cout << "Writer> ";
        cin.getline(buf->msg, SIZE);

        buf->flag = 1;

        if (strcmp(buf->msg, "exit") == 0)
            break;
    }

    shmdt(buf);
    return 0;
}