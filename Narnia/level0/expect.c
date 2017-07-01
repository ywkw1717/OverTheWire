/*
    This program is my expectation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int str = 0x41414141;
  char *c1 =  "Correct val's value from 0x41414141 -> 0xdeadbeef!";
  char *c2 = "Here is your chance: ";
  char *buf;

  scanf("%24s", buf);

  printf("buf: %s\n", buf);
  printf("val: 0x%08x\n", str);

  if(!strcmp(str, 0xdeadbeef)) {
    system("/bin/sh");
  }
  else {
    printf("WAY OFF!!!!\n");
    exit(1);
  }

  return 0;
}
