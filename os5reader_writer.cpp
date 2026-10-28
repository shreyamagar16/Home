#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t wrt;
pthread_mutex_t rcmutex;

int readcount = 0;
int shared_data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&rcmutex);
    readcount++;

    if (readcount == 1)
        sem_wait(&wrt);

    int active = readcount;
    pthread_mutex_unlock(&rcmutex);

    cout << "Reader " << id
         << " reads data = " << shared_data
         << " (active readers = " << active << ")" << endl;

    usleep(50000);

    pthread_mutex_lock(&rcmutex);
    readcount--;

    if (readcount == 0)
        sem_post(&wrt);

    pthread_mutex_unlock(&rcmutex);

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&wrt);

    shared_data += 10;
    cout << "Writer " << id
         << " WROTE data = " << shared_data
         << " (exclusive)" << endl;

    usleep(50000);
    sem_post(&wrt);

    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int id[5] = {1, 2, 3, 1, 2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&rcmutex, NULL);

    pthread_create(&r[0], NULL, reader, &id[0]);
    pthread_create(&w[0], NULL, writer, &id[3]);
    pthread_create(&r[1], NULL, reader, &id[1]);
    pthread_create(&r[2], NULL, reader, &id[2]);
    pthread_create(&w[1], NULL, writer, &id[4]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    cout << "Reader-Writer finished; data consistency maintained."
         << endl;

    sem_destroy(&wrt);
    pthread_mutex_destroy(&rcmutex);

    return 0;
}