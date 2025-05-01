#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int C[2];
  int P[2];
  char buff[30];
  char response[30];

  if (pipe(C) < 0 || pipe(P) < 0) {
    perror("Pipe creation failed");
    exit(1);
  }

  int pid = fork();

  if (pid == 0) {
    close(C[0]);
    close(P[1]);

    write(C[1], "file.txt", 9);
    close(C[1]);

    read(P[0], buff, sizeof(buff) - 1);
    buff[sizeof(buff) - 1] = '\0';
    close(P[0]);

    printf("Inside Client: Server Response: %s\n", buff);
  } else if (pid > 0) {
    close(P[0]);
    close(C[1]);

    read(C[0], buff, sizeof(buff) - 1);
    buff[sizeof(buff) - 1] = '\0';
    close(C[0]);

    int fd = open(buff, O_RDONLY);
    if (fd == -1) {
      write(P[1], "error", 6);
    } else {
      size_t n = read(fd, response, sizeof(response) - 1);
      response[n] = '\0';
      close(fd);

      write(P[1], response, n + 1);
    }
    close(P[1]);

    wait(NULL);
  } else {
    perror("Fork failed");
    exit(1);
  }

  return 0;
}
