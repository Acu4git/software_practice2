#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 10
#define BUF_SIZE 1024
#define INT_STRLEN_MAX 10
#define IS_PLUS 1
#define IS_MINUS -1
#define NO_SIGN 0

int input(int**, char*);
void sort(int[], int);
void output(int[], int, char*);

bool isInteger(char*);
bool isAllZero(char*);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Error: wrong number of argument.\n");
    fprintf(stderr, "Usage: ./ex05 <input_file> <output_file>\n");
    exit(1);
  }

  int *arr = NULL, n;
  n = input(&arr, argv[1]);
  if (!n) {
    fprintf(stderr, "Abort!\n");
    exit(1);
  }

  sort(arr, n);

  output(arr, n, argv[2]);
  printf("Success!\n");

  return 0;
}

int input(int** p, char* inFilename) {
  FILE* fp = fopen(inFilename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: can't open the input file \"%s\"\n", inFilename);
    return 0;
  }

  int n;
  fscanf(fp, "%d", &n);
  if (feof(fp)) {
    fprintf(stderr, "Error : not found the number of data.\n");
    return 0;
  }
  if ((*p = (int*)malloc(sizeof(int) * n)) == NULL) {
    fprintf(stderr, "Error : memory shortage\n");
    return 0;
  }

  int len = 0;
  char buf[BUF_SIZE + 1];
  while (fscanf(fp, "%s", buf) == 1) {
    if (len >= n) {
      fprintf(stderr, "Error: data size is too large\n");
      fprintf(stderr, "Use an input file which has %d or less data.\n", n);
      return 0;
    }

    if (!isInteger(buf)) {
      fprintf(stderr, "Error: input data contains an invalid value\n");
      fprintf(stderr, "\t=> \"%s\"\n", buf);
      fprintf(stderr, "Input file must contain only <int> values.\n");
      return 0;
    }

    (*p)[len++] = atoi(buf);
  }

  if (len == 0) {
    fprintf(stderr, "Error: data not found\n");
    fprintf(stderr, "Input file must contain at least 1 data.\n");
    return 0;
  }

  fclose(fp);
  return len;
}

void sort(int arr[], int len) {
  for (int k = len - 1; k >= 1; k--) {
    int max = arr[0], max_idx = 0;
    for (int i = 1; i <= k; i++) {
      if (arr[i] > max) {
        max = arr[i];
        max_idx = i;
      }
    }

    if (max_idx == k) continue;
    arr[k] += arr[max_idx];
    arr[max_idx] = arr[k] - arr[max_idx];
    arr[k] -= arr[max_idx];
  }
}

void output(int arr[], int len, char* outFilename) {
  FILE* fp = fopen(outFilename, "w");
  if (fp == NULL) {
    fprintf(stderr, "Error: can't open the output file \"%s\"\n", outFilename);
  }
  for (int i = 0; i < len; i++) fprintf(fp, "%d ", arr[i]);
  fprintf(fp, "\n");
  fclose(fp);
}

bool isInteger(char* str) {
  int sign = NO_SIGN;
  int i = 0, len = 1;

  switch (str[0]) {
    case '+':
      sign = IS_PLUS;
      i++;
      break;
    case '-':
      sign = IS_MINUS;
      i++;
      break;
  }

  if (isAllZero(str + i)) return true;
  if (str[0] == '0') return (str[1] == '\0') ? true : false;

  while (str[i] != '\0') {
    if (len > INT_STRLEN_MAX) return false;
    if (str[i] < '0' || str[i] > '9') return false;
    if (len == INT_STRLEN_MAX) {
      if (sign == IS_MINUS && strcmp(str, "-2147483648") > 0)
        return false;
      else if (sign != IS_MINUS && strcmp(str + sign, "2147483647") > 0)
        return false;
    }

    i++;
    len++;
  }

  return true;
}

bool isAllZero(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != '0') return false;
  }
  return true;
}