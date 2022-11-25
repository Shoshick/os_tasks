#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_BUF
#define MAX_BUF 999 // USED ​​IN FUNCTION fgets()
#endif

void free_memory(char **text, int size) {
  for (int i = 0; i < size; i++) {
    free(text[i]);
  }
  free(text);
}

int main() {
  int len, lines_number = 0;
  char **text;
  text = (char **)malloc(1 * sizeof(char *));
  if (text == NULL) {
    perror("Error allocating memory");
    free_memory(text, lines_number);
    return 1;
  }
  for (int i = 0;; i++) {
    char buffer[MAX_BUF];
    fgets(buffer, MAX_BUF, stdin);
    if (buffer[0] == '.') {
      break;
    }
    lines_number += 1;
    text = (char **)realloc(text, (i + 1) * sizeof(char));
    len = strlen(buffer) + 1; //место для '\0'
    text[i] = (char *)malloc(len * sizeof(char));
    if (text[i] == NULL) {
      perror("Error allocating memory");
      free_memory(text, lines_number);
      return 1;
    }
    strcpy(text[i], buffer);
  }
  for (int i = 0; i < lines_number; i++) {
    printf("%s", text[i]);
  }
  free_memory(text, lines_number);
  return 0;
}