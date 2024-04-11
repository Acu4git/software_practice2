#include <stdio.h>
#include <stdlib.h>

int input(char *, int **);
void sort(int *, int);
void output(char *, int *, int);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Error\n");
    return 1;
  }

  int *arr = NULL, N;
  N = input(argv[1], &arr);
  printf("Input  Array:");
  for (int i = 0; i < N; i++) printf("%d ", arr[i]);
  putchar('\n');

  sort(arr, N);

  printf("Output Array:");
  for (int i = 0; i < N; i++) printf("%d ", arr[i]);
  putchar('\n');
  output(argv[2], arr, N);

  return 0;
}

int input(char *sfname, int **p) {
  FILE *sp;
  sp = fopen(sfname, "r");

  int n;
  fscanf(sp, "%d ", &n);
  if (feof(sp)) {
    fprintf(stderr, "No data");
    exit(1);
  }
  if ((*p = (int *)malloc(sizeof(int) * n)) == NULL) {
    fprintf(stderr, "Memory shortage");
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    fscanf(sp, "%d ", &(*p)[i]);
  }
  fclose(sp);
  return n;
}

void sort(int *a, int n) {
  int i, j, k, x;
  for (i = 1; i < n; i++) {
    x = a[i];
    for (j = 0; j < i; j++) {
      if (a[j] > x) {
        for (k = i - 1; k >= j; k--) {
          a[k + 1] = a[k];
        }
        a[j] = x;
        // break;
        for (int p = 0; p < n; p++) printf("%d ", a[p]);
        putchar('\n');
      }
    }
  }
}

void output(char *tfname, int *x, int n) {
  FILE *tp;
  tp = fopen(tfname, "w");

  for (int i = 0; i < n; i++) {
    fprintf(tp, "%d ", x[i]);
  }

  fclose(tp);
}