
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define BUF 5
#define ITEMS 10

int buffer[BUF], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t buf_mutex;

void* producer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&buf_mutex);

        buffer[in] = i;
        cout << "Produced item " << i
             << " at slot " << in << endl;
        in = (in + 1) % BUF;

        pthread_mutex_unlock(&buf_mutex);
        sem_post(&full);
        usleep(50000);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&buf_mutex);

        int item = buffer[out];
        cout << "Consumed item " << item
             << " from slot " << out << endl;
        out = (out + 1) % BUF;

        pthread_mutex_unlock(&buf_mutex);
        sem_post(&empty);
        usleep(90000);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, BUF);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&buf_mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&buf_mutex);

    cout << "Producer-Consumer finished without overflow/underflow."
         << endl;

    return 0;
}
