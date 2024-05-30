#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 10
#define BUF_SIZE 1024
#define INT_STRLEN_MAX 10
#define IS_PLUS 0
#define IS_MINUS 0

int input(int[], char*);
void sort(int[], int);
void output(int[], int, char*);

bool isInteger(char*);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Error: wrong number of argument.\n");
    fprintf(stderr, "Usage: ./ex01 <input_file> <output_file>\n");
    exit(1);
  }

  int arr[N_MAX], n;
  n = input(arr, argv[1]);
  if (!n) {
    fprintf(stderr, "Abort!\n");
    exit(1);
  }

  sort(arr, n);

  output(arr, n, argv[2]);
  printf("Success!\n");

  return 0;
}

int input(int arr[], char* inFilename) {
  FILE* fp = fopen(inFilename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: can't open the input file \"%s\"\n", inFilename);
    return 0;
  }

  int len = 0;
  char buf[BUF_SIZE + 1];
  while (fscanf(fp, "%s", buf) == 1) {
    if (len >= N_MAX) {
      fprintf(stderr, "Error: data size is too large\n");
      fprintf(stderr, "Use an input file which has 10 or less data.\n");
      return 0;
    }

    if (!isInteger(buf)) {
      fprintf(stderr, "Error: input data contains an invalid value\n");
      fprintf(stderr, "\t=> \"%s\"\n", buf);
      fprintf(stderr, "Input file must contain only <int> values.\n");
      return 0;
    }

    arr[len++] = atoi(buf);
  }

  if (len == 0) {
    fprintf(stderr, "Error: data not found\n");
    fprintf(stderr, "Input file must contain at least 1 data.\n");
    return 0;
  }

  return len;
}

// 今回は何もしない
void sort(int arr[], int len) {}

void output(int arr[], int len, char* outFilename) {
  FILE* fp = fopen(outFilename, "w");
  if (fp == NULL) {
    fprintf(stderr, "Error: can't open the output file \"%s\"\n", outFilename);
  }
  for (int i = 0; i < len; i++) fprintf(fp, "%d ", arr[i]);
  fprintf(fp, "\n");
}

bool isInteger(char* str) {
  int sign = IS_PLUS;

  for (int i = 0; str[i] != '\0'; i++) {
    if (i >= INT_STRLEN_MAX ||
        (i == INT_STRLEN_MAX - 1 && strncmp(str, "2147483647", 10) == 1)) {
      fprintf(stderr, "stack overflow\n");
      return false;
    }

    if (str[1] == '\0' && !('0' <= str[0] && str[0] <= '9')) {
      return false;
    } else if (i == 0) {
      if (!(str[i] == '-' || str[i] == '+' ||
            ('0' <= str[i] && str[i] <= '9'))) {
        return false;
      }
    } else if (i > 0) {
      if (!('0' <= str[i] && str[i] <= '9')) {
        return false;
      }
    }
  }

  return true;
}