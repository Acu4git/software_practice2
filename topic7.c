#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 200

typedef struct school_record {
  float gpa;
  int credit;
  char name[MAX_NAME_LENGTH];
} SRec;

void printToScreen(SRec *, int);
int compGpa(const void *, const void *);
int compCredit(const void *, const void *);
int compName(const void *, const void *);
void singleSort(SRec *, int, int (*)(const void *, const void *));
int input(char *, SRec **);
void output(char *, SRec *, int);

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Error\n");
    exit(1);
  }

  SRec *student = NULL;
  int N;
  N = input(argv[2], &student);
  printf("---------Input---------\n");
  printToScreen(student, N);

  if (strcmp(argv[1], "gpa") == 0)
    singleSort(student, N, compGpa);
  else if (strcmp(argv[1], "credit") == 0)
    singleSort(student, N, compCredit);
  else if (strcmp(argv[1], "name") == 0)
    singleSort(student, N, compName);
  else {
    fprintf(stderr, "Invalid first argument:%s\n", argv[1]);
    exit(1);
  }

  printf("---------Output---------\n");
  printToScreen(student, N);
  output(argv[3], student, N);

  return 0;
}

void printToScreen(SRec *p, int n) {
  for (int i = 0; i < n; i++) {
    printf("%f %3d %-s", p[i].gpa, p[i].credit, p[i].name);
    putchar('\n');
  }
  putchar('\n');
}

int compGpa(const void *a, const void *b) {
  if (((SRec *)a)->gpa > ((SRec *)b)->gpa)
    return 1;
  else if (((SRec *)a)->gpa < ((SRec *)b)->gpa)
    return -1;
  else
    return 0;
}

int compCredit(const void *a, const void *b) {
  if (((SRec *)a)->credit > ((SRec *)b)->credit)
    return 1;
  else if (((SRec *)a)->credit < ((SRec *)b)->credit)
    return -1;
  else
    return 0;
}

int compName(const void *a, const void *b) {
  return strcmp(((SRec *)a)->name, ((SRec *)b)->name);
}

void singleSort(SRec *arr, int n_array,
                int (*cmp)(const void *, const void *)) {
  int i, j, k;
  SRec temp;
  for (i = 1; i < n_array; i++) {
    temp = arr[i];
    for (j = 0; j < i; j++) {
      if (cmp(&temp, &arr[j]) == -1) {
        for (k = i - 1; k >= j; k--) {
          arr[k + 1] = arr[k];
        }
        arr[j] = temp;
        break;
      }
    }
  }
}

int input(char *sfname, SRec **p) {
  FILE *sp;
  if ((sp = fopen(sfname, "r")) == NULL) {
    fprintf(stderr, "Failed to open the file %s\n", sfname);
    exit(1);
  }

  int n;
  fscanf(sp, "%d", &n);
  if (feof(sp)) {
    fprintf(stderr, "No data\n");
    exit(1);
  }
  if ((*p = (SRec *)malloc(sizeof(SRec) * n)) == NULL) {
    fprintf(stderr, "Memory shortage");
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    fscanf(sp, "%f", &((*p)[i].gpa));
    fscanf(sp, "%d", &((*p)[i].credit));
    fscanf(sp, "%s", (*p)[i].name);
  }
  fclose(sp);
  return n;
}

void output(char *tfname, SRec *p, int n_array) {
  FILE *tp;
  tp = fopen(tfname, "w");
  fprintf(tp, "%d\n", n_array);
  for (int i = 0; i < n_array; i++) {
    fprintf(tp, "%-f %3d %-199s\n", p[i].gpa, p[i].credit, p[i].name);
  }

  fclose(tp);
}