//server.c
#include<stdio.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

int main()
{
  int shm_fd;
  void* ptr;
  char* buff[25];
  const char* name = "OS";
  shm_fd = shm_open(name,O_CREAT | O_RDWR,0777);
  ftruncate(shm_fd, 25);
  ptr = mmap(0,25,PROT_WRITE,MAP_SHARED,shm_fd,0);
  time_t t = time(&t);
  sprintf(ptr,"%s",ctime(&t));
  printf("\nData written into shared memory\n");
  return 0;
}



//client.c

#include<stdio.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

int main()
{
  int shm_fd;
  void* ptr;
  char* buff[25];
  shm_fd = shm_open("OS",O_RDONLY,0777);
  ftruncate(shm_fd, 25);
  ptr = mmap(0,25,PROT_READ,MAP_SHARED,shm_fd,0);
  read(shm_fd,buff,25);
  write(1, buff, 25);

  shm_unlink("OS");
  return 0;
}



//steps
//gcc server.c -lrt -o ser
//gcc client.c -lrt -o cli
// ./ser
// ./cli

