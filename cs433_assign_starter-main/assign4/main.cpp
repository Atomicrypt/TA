/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

// global buffer object
Buffer buffer;

pthread_mutex_t _mutex;
sem_t _full;
sem_t _empty;

// Producer thread function
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        
        sem_wait(&_empty);              // Semaphore wait
        pthread_mutex_lock(&_mutex);    // Mutex lock

        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }

        pthread_mutex_unlock(&_mutex);  // Unlock mutex after critical section
        sem_post(&_full);               // Flag semaphore that buffer isn't full
    }
}

// Consumer thread function
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        
        sem_wait(&_full);               // Semaphore wait
        pthread_mutex_lock(&_mutex);    // Mutex lock
        
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }

        pthread_mutex_unlock(&_mutex);  // Unlock mutex after critical section
        sem_post(&_empty);              // Flag semaphore that buffer isn't full
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    srand(time(NULL));
    if (argc != 4) {
        cout << "Expected 3 arguments, received " << argc - 1 << endl;
        return 1;
    }
    int sleepTime;
    int producer;
    int consumer; 
    /* TODO: 2. Initialize buffer and synchronization primitives */
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */
}
