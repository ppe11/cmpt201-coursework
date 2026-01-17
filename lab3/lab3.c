#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

void free_history(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    free(history[i]);
  }
}

void print_history(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    printf("%s", history[i]);
  }
}

int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  int count = 0;

  while (1) {
    char *line = NULL;
    size_t len = 0;

    printf("Enter input: ");
    ssize_t nread = getline(&line, &len, stdin);

    if (nread == -1) {
      free(line);
      break; // EOF or Ctrl+D
    }

    if (strcmp(line, "print\n") == 0) {
      print_history(history, count);
    }

    if (count < HISTORY_SIZE) {
      history[count++] = line;
    } else {
      free(history[0]);
      for (int i = 1; i < HISTORY_SIZE; i++) {
        history[i - 1] = history[i];
      }
      history[HISTORY_SIZE - 1] = line;
    }
  }

  free_history(history, count);
  return 0;
}
