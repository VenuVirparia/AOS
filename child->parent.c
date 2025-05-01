#include<unistd.h> //fork
#include<sys/types.h> //pid_t
#include<stdio.h> //printf
#include<stdlib.h> //exit
#include<sys/wait.h> //wait


int main()
{
  pid_t id;
  id = fork();
  if(id == 0)
  {	
    printf("Child executed: ");
    printf("%d \n",id);
    printf("Process id child %d,%d\n\n\n",getpid(),getppid());
  }
  else if(id > 0)
  {
    wait(NULL);
    printf("Parent executed: ");
    printf("%d \n",id);
    printf("Process id parent %d,%d\n\n\n",getpid(),getppid());
  }
  else if(id == -1)
  {
    printf("error\n");
  }
  exit(0);
}
