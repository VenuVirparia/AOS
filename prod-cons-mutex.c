#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 5

int count = 0, in = 0, out = 0, item = 0;

pthread_mutex_t lock;
int buffer[SIZE];

void *producer() {
  printf("\nProducer\n\n");
  for (int i = 0; i < 10; i++) {
    item++;
    pthread_mutex_lock(&lock);
    while (count == SIZE) {
      pthread_mutex_unlock(&lock);
      pthread_mutex_lock(&lock);
    }
    buffer[in] = item;
    printf("Producer produced: %d at %d\n", item, in);
    in = (in + 1) % SIZE;
    count++;
    pthread_mutex_unlock(&lock);
  }
  printf("\nProducer finished\n\n");
  return NULL;
}

void *consumer() {
  printf("\nConsumer\n\n");
  for (int i = 0; i < 10; i++) {
    pthread_mutex_lock(&lock);
    while (count == 0) {
      pthread_mutex_unlock(&lock);
      pthread_mutex_lock(&lock);
    }
    item = buffer[out];
    printf("Consumer consumed: %d at %d\n", item, out);
    out = (out + 1) % SIZE;
    count--;
    pthread_mutex_unlock(&lock);
  }
  printf("\nConsumer finished\n\n");
  return NULL;
}

int main() {
  // pthread_mutex_t lock;
  pthread_t t1, t2;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&t2, NULL, &producer, NULL);
  pthread_create(&t1, NULL, &consumer, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_mutex_destroy(&lock);
  printf("Ans: %d\n", count);
  return 0;
}
