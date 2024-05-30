#include <stdbool.h>
#include <stdio.h>
#define N_MAX 5

void input_matrix(float (*)[N_MAX], int);
void multiply_matrix(float (*)[N_MAX], float (*)[N_MAX], float (*)[N_MAX], int);
void output_matrix(float (*)[N_MAX], int);

int main() {
  int n;
  printf("Please input the value of N:");
  while (scanf("%d", &n), n > N_MAX || n <= 0) {
    printf("ERROR: Invalid number\n");
    printf("Please input a natural number less than or equal to %d:", N_MAX);
  }

  printf("\n----------%dx%d Matrix A----------\n\n", n, n);

  float a[N_MAX][N_MAX], ak[N_MAX][N_MAX];
  input_matrix(a, n);
  multiply_matrix(ak, a, a, n);
  printf("Matrix A^2 is...\n\n");
  output_matrix(ak, n);
  return 0;
}

void input_matrix(float (*p)[N_MAX], int num) {
  int i, j;
  for (i = 0; i < num; i++) {
    for (j = 0; j < num; j++) {
      printf("Please input the value of A[%d][%d]:", i, j);
      scanf("%f", &p[i][j]);
    }
  }
  putchar('\n');
};

void multiply_matrix(float (*z)[N_MAX], float (*x)[N_MAX], float (*y)[N_MAX],
                     int num) {
  int i, j, k;
  for (i = 0; i < num; i++) {
    for (j = 0; j < num; j++) {
      z[i][j] = 0;
      for (k = 0; k < num; k++) z[i][j] += x[i][k] * y[k][j];
    }
  }
}

void output_matrix(float (*z)[N_MAX], int num) {
  int i, j;
  for (i = 0; i < num; i++) {
    for (j = 0; j < num; j++) {
      printf("%18f,", z[i][j]);
    }
    printf("\n\n");
  }
}