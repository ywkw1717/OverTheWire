#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  char s[80];

  if (argc == 1) {
    printf("Usage: %s argument\n", argv[0]);
    exit(1);
  }

  strcpy(s, argv[1]);

  printf("%s", s);

  return 0;
}
