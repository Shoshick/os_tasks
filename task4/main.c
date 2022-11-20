#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_BUF
#define MAX_BUF 999 // USED ​​IN FUNCTION fgets()
#endif
char line_meter[MAX_BUF];


void freeing_memory(int text, int lines_number)
{
  for (int i = 0; i < lines_number; i++)
    free(text[i]);
  free(text);
}

int main() {
  int len, lines_number = 0;
  char **text;
  text = (char **)malloc(1 * sizeof(char *));
  if (text == NULL) {
    printf("Ошибка, malloc вернул NULL");
    freeing_memory(text, lines_number);
    return 1;
  }
  for (int i = 0;; i++) {
    fgets(line_meter, MAX_BUF, stdin);
    if (line_meter[0] == '.') {
      break;
    }
    lines_number += 1;
    text = (char **)realloc(text, i + 1);
    len = strlen(line_meter) + 1; //место для '\0'
    text[i] = (char *)malloc(len * sizeof(char));
    if (text[i] == NULL) {
      printf("Ошибка, malloc вернул NULL");
      freeing_memory(text, lines_number);
      return 1;
    }
    strcpy(text[i], line_meter);
  }
  for (int i = 0; i < lines_number; i++) {
      printf("%s", text[i]);
    }
  freeing_memory(text, lines_number);
  return 0;
}