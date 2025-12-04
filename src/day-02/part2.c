#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max ulong = 20 chars + 1 for \0
#define LONG_MAX_LEN 21

char min[LONG_MAX_LEN];
char max[LONG_MAX_LEN];
char next[LONG_MAX_LEN];

ulong recordedValues[1000];
ulong *rc = &recordedValues[0];

int parse(char *min, char *max);
int is_equal(char *num, int mod);
void next_smallest(char *num, char *next, int mod);
int notTracked(ulong num);

int main(int argc, char **argv) {

  ulong count = 0;
  while (parse(min, max) > 0) {

    ulong max_n = atol(max);
    int maxMod = strlen(max);

    for (ulong eval_n = atol(min); eval_n <= atol(max); eval_n++) {
      for (int mod = 2; mod <= maxMod; mod++) {

        char eval_s[LONG_MAX_LEN];
        sprintf(eval_s, "%ld", eval_n);

        if (is_equal(eval_s, mod) && !notTracked(eval_n)) {
          count += eval_n;
          *(rc++) = eval_n;
        }
      }
    }
  }
  printf("Result: %ld\n", count);
  exit(EXIT_SUCCESS);
}

int notTracked(ulong num) {

  ulong *i = &recordedValues[0];
  while (i <= rc && *i != num) {
    i++;
  }
  return rc - i - 1 == 0;
}

int is_equal(char *num, int mod) {

  int len = strlen(num);
  if (len % mod != 0)
    return 0;

  char *fh = &num[0];
  int subStrLen = (len / mod);
  int isEqual = 1;
  for (int j = 0; j < subStrLen; j++) {
    for (int i = 1; i < mod; i++) {
      isEqual = *fh == *(fh + (subStrLen * i));
      if (!isEqual)
        return 0;
    }
    fh++;
  }
  return isEqual;
}

int parse(char *min, char *max) {
  char c;
  while (((c = getchar()) != '-') && c != ',' && c != EOF) {
    if (c != '\n')
      *min++ = c;
  }
  *min = '\0';

  if (c == EOF)
    return 0;

  int maxFilled = 0;
  while (((c = getchar()) != '-' && c != ',' && c != EOF)) {
    if (c != '\n') {
      maxFilled = 1;
      *max++ = c;
    }
  }
  *max = '\0';

  return maxFilled;
}
