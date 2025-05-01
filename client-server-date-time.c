#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

int main() {
  int C[2]; // client to server
  int P[2]; // server to client
  char request[30];
  char response[100];

  pipe(C);
  pipe(P);

  int pid = fork();

  if (pid == 0) { // Client
    close(C[0]);
    close(P[1]);

    while (1) {
      write(C[1], "request time", 13);
      read(P[0], response, sizeof(response));
      printf("Client received: %s\n", response);
      sleep(5);
    }
  } else if (pid > 0) { // Server
    close(C[1]);
    close(P[0]);

    while (1) {
      read(C[0], request, sizeof(request));
      time_t now = time(NULL);
      char *dt = ctime(&now);
      write(P[1], dt, strlen(dt) + 1);
    }
  } else {
    perror("fork failed");
    exit(1);
  }

  return 0;
}
