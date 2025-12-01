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

    int overflow = d - &dial[0] + (direction * (spin % DIAL_LEN));
    int n = (DIAL_LEN + overflow) % DIAL_LEN;

    int clicks =
        (spin / DIAL_LEN) +
        (((overflow <= 0 && (d - &dial[0]) > 0) || overflow >= DIAL_LEN) ? 1
                                                                         : 0);
    count += clicks;

    d = &dial[0] + n;

    printf("Direction: %d; Spin: %d; Overflow: %d; Dial: %ld; Clicks: %d; "
           "Count: %d\n",
           direction, spin, overflow, d - &dial[0], clicks, count);
  }

  printf("Times Passed '0': %d\n", count);
  exit(EXIT_SUCCESS);
}
