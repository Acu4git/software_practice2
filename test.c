#include <stdio.h>
#include <stdlib.h>
#define BUCKET_SIZE 100

typedef struct cell {
  int key;
  int data;
  struct cell *next;
} CELL;

CELL *table[BUCKET_SIZE];

void init() {
  int i;
  for (i = 0; i < BUCKET_SIZE; i++) {
    table[i] = NULL;
  }
}

int hash(char *s) {
  int sum = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    sum += (i + 1) * s[i];
  }
  return sum % BUCKET_SIZE;
}

void insert(char *s) {}

int main() {
  init();
  return 0;
}