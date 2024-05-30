#include <stdbool.h>
#include <stdio.h>
#define N_MAX 5

void input_matrix(float (*)[N_MAX], int);
void multiply_matrix(float (*)[N_MAX], float (*)[N_MAX], float (*)[N_MAX], int);
void power_matrix(float (**)[N_MAX], float (*)[N_MAX], int, int);
void output_matrix(float (*)[N_MAX], int);

// 記憶用配列
float b[N_MAX][N_MAX], c[N_MAX][N_MAX];

int main() {
  int n, k;
  // Nの入力
  printf("Please input the value of N:");
  while (scanf("%d", &n), n > N_MAX || n <= 0) {
    printf("ERROR: Invalid number\n");
    printf("Please input a natural number less than or equal to %d: ", N_MAX);
  }
  // kの入力
  printf("Please input the value of k:");
  while (scanf("%d", &k), k < 0) {
    printf("ERROR: Invalid number\n");
    printf("Please input a natural number: ");
  }

  printf("\n----------%dx%d Matrix A----------\n\n", n, n);

  float a[N_MAX][N_MAX], (*ak)[N_MAX];
  input_matrix(a, n);
  power_matrix(&ak, a, n, k);
  printf("Matrix A^%d is...\n\n", k);
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

// Z=X×Y
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

// 行列のk乗
void power_matrix(float (**ak)[N_MAX], float (*a)[N_MAX], int n, int k) {
  if (k == 1)
    (*ak) = a;
  else if (k == 2) {
    (*ak) = b;
    multiply_matrix((*ak), a, a, n);
  } else {
    int i;
    float(*x)[N_MAX] = NULL, (*y)[N_MAX] = NULL, (*tmp)[N_MAX] = NULL;
    multiply_matrix(b, a, a, n);
    x = b;
    y = c;
    for (i = 3; i <= k; i++) {
      multiply_matrix(y, a, x, n);
      tmp = x;
      x = y;
      y = tmp;
    }
    (*ak) = x;
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