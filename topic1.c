#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE_MAX 10
#define N_MAX 2147483647

int arr[ARR_SIZE_MAX];

int input(char *);
void sort(int);
void output(char *, int);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Error\n");
    return 1;
  }

  for (int i = 0; i < ARR_SIZE_MAX; i++) arr[i] = N_MAX;

  int n;
  n = input(argv[1]);
  printf("Input  Array:");
  for (int i = 0; i < n; i++) printf("%d ", arr[i]);
  putchar('\n');

  sort(n);

  printf("Output Array:");
  for (int i = 0; i < n; i++) printf("%d ", arr[i]);
  putchar('\n');
  output(argv[2], n);

  return 0;
}

int input(char *sfname) {
  FILE *sp;
  sp = fopen(sfname, "r");

  int cnt = 0, tmp;
  while (fscanf(sp, "%d", &tmp) == 1) {
    if (cnt >= ARR_SIZE_MAX) {
      fprintf(stderr, "Nanishitenda omaeeeeeee!!\n");
      exit(1);
    }
    arr[cnt++] = tmp;
  }
  if (cnt == 0) {
    fprintf(stderr, "No data.\n");
    exit(1);
  }
  fclose(sp);
  return cnt;
}

void sort(int arr_size1) {
  int i, j, k, x;
  for (i = 1; i < arr_size1; i++) {
    x = arr[i];
    for (j = 0; j < i; j++) {
      if (x < arr[j]) {
        for (k = i - 1; k >= j; k--) {
          arr[k + 1] = arr[k];
        }
        arr[j] = x;
        break;
      }
    }
  }
}

void output(char *tfname, int arr_size2) {
  FILE *tp;
  tp = fopen(tfname, "w");

  for (int i = 0; i < arr_size2; i++) {
    fprintf(tp, "%d ", arr[i]);
  }

  fclose(tp);
}