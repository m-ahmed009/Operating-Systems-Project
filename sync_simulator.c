#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
sem_t semaphore;
int monitor_condition = 0;
pthread_mutex_t monitor_lock;
pthread_cond_t monitor_cond;

void critical_section(int thread_id) {
    printf("Thread %d entering critical section\n", thread_id);
    sleep(1); // Simulate some work in the critical section
    printf("Thread %d leaving critical section\n", thread_id);
}

void *mutex_thread(void *arg) {
    int thread_id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    critical_section(thread_id);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *semaphore_thread(void *arg) {
    int thread_id = *((int *)arg);
    sem_wait(&semaphore);
    critical_section(thread_id);
    sem_post(&semaphore);
    return NULL;
}


void *monitor_thread(void *arg) {
    int thread_id = *((int *)arg);
    
    pthread_mutex_lock(&monitor_lock);
    while (monitor_condition != 0) {
        pthread_cond_wait(&monitor_cond, &monitor_lock);
    }
    monitor_condition = 1;  
    pthread_mutex_unlock(&monitor_lock);
    
    critical_section(thread_id);
    
    pthread_mutex_lock(&monitor_lock);
    monitor_condition = 0;
    pthread_cond_signal(&monitor_cond);
    pthread_mutex_unlock(&monitor_lock);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Initialize semaphore with value 1
    sem_init(&semaphore, 0, 1);

    // Initialize monitor lock and condition variable
    pthread_mutex_init(&monitor_lock, NULL);
    pthread_cond_init(&monitor_cond, NULL);

    // Create and run threads for each synchronization technique
    printf("Running Mutex Example:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, mutex_thread, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nRunning Semaphore Example:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, semaphore_thread, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nRunning Monitor Example:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, monitor_thread, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);
    pthread_mutex_destroy(&monitor_lock);
    pthread_cond_destroy(&monitor_cond);

    return 0;
}
