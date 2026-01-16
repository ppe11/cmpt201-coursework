#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter programs to run.\n> ");
    fflush(stdout);

    ssize_t nread = getline(&line, &len, stdin);
    if (nread == -1) {
      break;
    }

    if (line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }

    pid_t pid = fork();

    if (pid == 0) {
      execl(line, line, (char *)NULL);
      perror("Exec failure");
      exit(1);
    } else if (pid > 0) {
      waitpid(pid, NULL, 0);
    }
  }

  free(line);
  return 0;
}
