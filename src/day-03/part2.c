#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define JOLTSIZE 12

char bank[MAXLINE];
size_t bSize = MAXLINE;

void getJoltage(char *bank, char *joltage);
char *rtrim(char *bank);

int main(int argc, char **argv) {
  char *p = bank;

  ulong maximumJoltage = 0;
  while (getline(&p, &bSize, stdin) > 1) {
    char joltage[JOLTSIZE + 1] = {'0', '\0'};
    getJoltage(bank, joltage);
    maximumJoltage += atol(joltage);
  }

  printf("Maximum Joltage: %lu\n", maximumJoltage);
}

char *rtrim(char *bank) {
  char *end = bank + strlen(bank);
  while (end > bank && isspace((unsigned char)*--end))
    ;
  *(end + 1) = '\0';
  return end;
}

void getJoltage(char *bank, char *joltage) {
  rtrim(bank);

  char *j = joltage;
  char *lastCell = &joltage[JOLTSIZE] - 1;

  // j points to previous
  // bank points to current
  while (*bank != '\0') {

    // if bank is less than previous AND concatenating will push j out of bounds
    if (*bank <= *j && j < lastCell) {
      j++;
      *j = *bank;
      *(j + 1) = '\0';
    }
    // rewind
    else if (*bank > *j) {
      // set j back to beginning + minimum
      int bankLen = strlen(bank);
      int jIndex = bankLen >= JOLTSIZE ? 0 : JOLTSIZE - bankLen;
      j = joltage + jIndex;

      while (*bank <= *j && *(j + 1) != '\0' && j < lastCell) {
        j++;
      }
      *j = *bank;
      *(j + 1) = '\0';
    }

    bank++;
  }
}
