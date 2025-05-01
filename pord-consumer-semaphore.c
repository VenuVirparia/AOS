#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_TO_PRODUCE 4

int buffer[BUFFER_SIZE];
int in = 0;  
int out = 0;


sem_t empty;  
sem_t full;   
sem_t mutex;  

void *producer(void *arg) {
    int id = *(int*)arg;

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        int item = id * 10 + i;

        sem_wait(&empty);  
        sem_wait(&mutex); 

        buffer[in] = item;
        printf("Producer %d: Inserted item %d at position %d\n\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);  
        sem_post(&full);   

        sleep(1);  
     
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = *(int*)arg;

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        sem_wait(&full);   
        sem_wait(&mutex);  

        int item = buffer[out];
        printf("Consumer %d: Removed item %d from position %d\n\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;
      
        sem_post(&mutex);  
        sem_post(&empty); 

        sleep(2);  
    }
    return NULL;
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);  
    sem_init(&full, 0, 0);             
    sem_init(&mutex, 0, 1);            

    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int ids[4] = {0, 1, 0, 1};  

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, &ids[i]);
    }


    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, &ids[i+2]);
    }

   for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
