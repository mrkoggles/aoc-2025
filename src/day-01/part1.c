#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 15
#define DIAL_LEN 100

int main(int argc, char **argv) {

  char line[MAX_LINE];
  char *b = line;
  size_t bSize = MAX_LINE;

  int dial[DIAL_LEN];
  int *d = &dial[50];

  int count;
  while (getline(&b, &bSize, stdin) > 1) {

    char *p = line;
    int direction = *p++ == 'L' ? -1 : 1;
    int spin = atoi(p);

    printf("Direction: %d; Spin: %d\n", direction, spin);

    int overflow = d - &dial[0] + (direction * (spin % DIAL_LEN));
    int n = (DIAL_LEN + overflow) % DIAL_LEN;
    d = &dial[0] + n;

    printf("Dial now at: %ld\n", d - &dial[0]);

    if (d == &dial[0]) // if the dial currently sits on 0 increase the count
      count++;
  }

  printf("Times Passed '0': %d\n", count);
  exit(EXIT_SUCCESS);
}
