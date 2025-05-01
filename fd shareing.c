#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
  int fd;
  char* buff[10];
  //fd=open("file.txt",O_RDWR);

  int id = fork();
  fd=open("file.txt",O_RDWR);
  if(id == 0)
  {	
    printf("Child\n");
    read(fd,buff,10);
    write(1,buff,5);
    printf("\n\n");
    printf("Child %d\n",fd);
  }
  else if(id > 0)
  {
    printf("Parent\n");
    read(fd,buff,10);
    write(1,buff,5);
    printf("\n\n");
    printf("Parent %d\n",fd);
  }
  else
  {
    printf("Error\n");
  }
  close(fd);
  return 0;
}
