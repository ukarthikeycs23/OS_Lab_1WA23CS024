#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 3


int buffer = 0; 
sem_t mutex; 
sem_t full; 
sem_t empty; 

// Producer function
void* producer(void* arg) {
    int producer_id = *((int*)arg);
    
    
    int item = rand() % 100 + 1; // Random item (between 1 and 100)
    
    // Wait for empty space and acquire mutex lock
    sem_wait(&empty); // Wait if buffer is full
    sem_wait(&mutex); // Critical section
    
    // Add item to buffer
    buffer += item;
    printf("Producer %d produced %d\n", producer_id, item);
    printf("Buffer: %d\n", buffer);
    
    // Release mutex and signal full
    sem_post(&mutex);
    sem_post(&full); // Signal that buffer has one more item
    
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int consumer_id = *((int*)arg);
    
    // Simulate consuming an item
    int item;
    
    // Wait for full buffer and acquire mutex lock
    sem_wait(&full); // Wait if buffer is empty
    sem_wait(&mutex); // Critical section
    
    // Remove item from buffer
    item = buffer;
    buffer = 0;
    printf("Consumer %d consumed %d\n", consumer_id, item);
    printf("Buffer: %d\n", buffer);
    
    // Release mutex and signal empty
    sem_post(&mutex);
    sem_post(&empty); // Signal that buffer has one more empty slot
    
    return NULL;
}

int main() {
    int num_producers, num_consumers;
    printf("Enter the number of Producers: ");
    scanf("%d", &num_producers);
    printf("Enter the number of Consumers: ");
    scanf("%d", &num_consumers);
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1); 
    sem_init(&full, 0, 0);   
    sem_init(&empty, 0, MAX_BUFFER_SIZE); 
    
    // Create producer and consumer threads
    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];
    
    // Start producer threads
    for (int i = 0; i < num_producers; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1; // Producer ID starting from 1
        pthread_create(&producers[i], NULL, producer, id);
    }
    
    // Start consumer threads
    for (int i = 0; i < num_consumers; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1; // Consumer ID starting from 1
        pthread_create(&consumers[i], NULL, consumer, id);
    }
    
    // Join producer threads
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }
    
    // Join consumer threads
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    
    return 0;
}
