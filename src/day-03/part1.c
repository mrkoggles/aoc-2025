#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define JOLTSIZE 2

char bank[MAXLINE];
size_t bSize = MAXLINE;

void getJoltage(char *bank, char *joltage);

int main(int argc, char **argv) {
  char *p = bank;

  int maximumJoltage = 0;
  while (getline(&p, &bSize, stdin) > 1) {

    char joltage[JOLTSIZE] = {'0', '0'};
    getJoltage(bank, joltage);
    maximumJoltage += atoi(joltage);
  }

  printf("Maximum Joltage: %d\n", maximumJoltage);
}

void getJoltage(char *bank, char *joltage) {

  char *j1 = joltage;
  char *j2 = joltage + 1;

  while (*(bank + 1) != '\0') {
    if (*bank > *j1 && *(bank + 1) != '\n' && *(bank + 1) != EOF) {
      *j1 = *bank;
      *j2 = *(bank + 1);
    } else if (*bank > *j2) {
      *j2 = *bank;
    }
    bank++;
  }
}
