#include<unistd.h> //fork
#include<sys/types.h> //pid_t
#include<stdio.h> //printf
#include<stdlib.h> //exit
#include<sys/wait.h> //wait
#include<fcntl.h> //open

int main()
{
  int fd1, fd2;
  char buff[20];
  fd1 = open("file.txt", O_RDONLY);
  if(fd1==-1)
    printf("Error in opening file1\n");
  read(fd1, buff, 20);
  fd2 = open("file2.txt", O_WRONLY | O_CREAT);
  if(fd2==-1)
    printf("Error in opening file2 \n");
  write(fd2, buff, 20);

  lseek(fd2, 0, SEEK_SET);
  read(fd2, buff, 20);
  printf("%s\n", buff);
  close(fd1);
  close(fd2);
  
  return 0;
}
