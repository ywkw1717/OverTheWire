#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vuln(char *str) {
  memset(0, 0, 128);
  printf("goodfunction() = %p\n", 0x80486e0);
  printf("hackedfunction() = %p\n\n", 0x8048706);

  printf("before : ptrf() = %p (%p)\n", 0x80486e0, 0x80486e0);
  puts("I guess you want to come to the hackedfunction...");
  sleep(2);

  snprintf(........);
}

int goodfunction();

int hackedfunction();

int main(int argc, char *argv[]) {
  if(argc <= 1) {
    fprintf(stderr, "Usage: %s <buffer>\n", argv[0]);
    exit(1);
  }

  exit(vuln(argv[1]));
}
