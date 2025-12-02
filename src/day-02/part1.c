

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max ulong = 20 chars + 1 for \0
#define LONG_MAX_LEN 21

char min[LONG_MAX_LEN];
char max[LONG_MAX_LEN];
char next[LONG_MAX_LEN];

int parse(char *min, char *max);
int is_equal(char *num);
void next_smallest(char *num, char *next);

int main(int argc, char **argv) {

  ulong count = 0;
  while (parse(min, max) > 0) {

    char *eval_s = min;
    ulong eval_n = atol(eval_s);
    ulong max_n = atol(max);
    while (eval_n <= max_n) {

      if (is_equal(eval_s))
        count += eval_n;

      next_smallest(eval_s, next);
      strcpy(eval_s, next);
      eval_n = atol(eval_s);
    }
  }

  printf("Result: %ld\n", count);
  exit(EXIT_SUCCESS);
}

int is_equal(char *num) {

  int len = strlen(num);
  if (len % 2 != 0)
    return 0;

  char *fh = &num[0];
  char *bh = fh + (len / 2);
  while (*bh != '\0' && *fh == *bh) {
    fh++;
    bh++;
  };
  return *bh == '\0';
}

void next_smallest(char *num, char *next) {
  int len = strlen(num);
  int midpt = len / 2;

  ulong r;
  if (len % 2 != 0) {
    r = pow((double)10, (double)midpt);

  } else {
    char fh[midpt];
    strncpy(fh, num, sizeof(fh));

    char *bh = num + midpt;

    long fh_n = atol(fh);
    long bh_n = atol(bh);

    r = bh_n >= fh_n ? fh_n + 1 : fh_n;
  }

  sprintf(next, "%ld", r); // write the fronthalf
  char *bh = next + strlen(next);
  sprintf(bh, "%ld", r); // write to backhalf
}

int parse(char *min, char *max) {
  char c;
  while (((c = getchar()) != '-') && c != ',' && c != EOF) {
    if (c != '\n')
      *min++ = c;
  }
  *min = '\0';

  while (((c = getchar()) != '-' && c != ',' && c != EOF)) {
    if (c != '\n')
      *max++ = c;
  }
  *max = '\0';

  return c != EOF;
}
