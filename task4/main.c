#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char line_meter[9999];

int main() {
  int len, mas_len = 0;
  char **text;
  text = (char **)malloc(1 * sizeof(char *));
  if (text == NULL) {
    printf("Ошибка, malloc вернул 0");
    return 0;
  }
  for (int i = 0;; i++) {
    fgets(line_meter, 999, stdin);
    if (line_meter[0] == '.') {
      break;
    }
    mas_len += 1;
    text = (char **)realloc(text, i + 1);
    len = strlen(line_meter) + 1; //место для '\0'
    text[i] = (char *)malloc(len * sizeof(char));
    if (text[i] == NULL) {
      printf("Ошибка, malloc вернул 0");
      return 0;
    }
    strcpy(text[i], line_meter);
  }
  for (int i = 0; i < mas_len; i++) {
    for (int j = 0; text[i][j] != '\0'; j++) {
      printf("%c", text[i][j]);
    }
  }
  free(text);
  return 0;
}