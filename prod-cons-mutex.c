#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int count = 0;
pthread_mutex_t lock;

void *consumer()
{	int i;
  printf("C Thread started\n\n");
  for(i=0;i<10;i++)
  {	
    pthread_mutex_lock(&lock);
    printf("C Thread: %d\n",count);
    count--;
    pthread_mutex_unlock(&lock);
  }
  printf("C Thread ended\n\n");
}
void *producer()
{	int i;
  printf("P Thread started\n\n");
  for(i=0;i<10;i++)
  {	
    pthread_mutex_lock(&lock);
    count++;
    printf("P Thread: %d\n",count);
    pthread_mutex_unlock(&lock);
  }
  printf("P Thread ended\n\n");
}

int main()
{
  pthread_t t1,t2;
  pthread_mutex_init(&lock,NULL);
  pthread_create(&t2,NULL,&producer,NULL);
  pthread_create(&t1,NULL,&consumer,NULL);

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_mutex_destroy(&lock);
  printf("Ans: %d\n",count);
  return 0;
}
