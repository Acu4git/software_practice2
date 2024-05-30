#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 200

typedef struct school_record {
  float gpa;
  int credit;
  char name[MAX_NAME_LENGTH];
} SRec;

int input(char *, SRec **);
void output(char *, SRec *, int);
int compGpa(const void *, const void *);
int compCredit(const void *, const void *);
int compName(const void *, const void *);
void simpleSort(SRec *, int, int (*)(const void *, const void *));
void printRecords(SRec *, int);

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "\033[33mError: you must pass 3 arguments.\n");
    fprintf(stderr, "Usage: ./ex07 <target> <inFile> <outFile>\033[39m\n");
    exit(EXIT_FAILURE);
  }

  SRec *student = NULL;
  int N = input(argv[2], &student);
  printf("---------Input---------\n");
  printRecords(student, N);

  if (strcmp(argv[1], "gpa") == 0)
    simpleSort(student, N, compGpa);
  else if (strcmp(argv[1], "credit") == 0)
    simpleSort(student, N, compCredit);
  else if (strcmp(argv[1], "name") == 0)
    simpleSort(student, N, compName);
  else {
    fprintf(stderr, "\033[33mError: invalid first argument \'%s\'\n", argv[1]);
    fprintf(stderr, "Please choice \'gpa\', \'credit\' or \'name\'\033[39m\n");
  }

  printf("---------Output---------\n");
  printRecords(student, N);
  output(argv[3], student, N);

  return 0;
}

int input(char *sfname, SRec **p) {
  FILE *sp;
  if ((sp = fopen(sfname, "r")) == NULL) {
    fprintf(stderr, "\033[33mError: failed to open the file \'%s\'\033[39m\n",
            sfname);
    exit(EXIT_FAILURE);
  }

  int n;
  if (fscanf(sp, "%d", &n) == EOF) {
    fprintf(stderr, "\033[33mError: falied to parse total num\n");
    fprintf(stderr,
            "Please check if the data types are appropriate.\033[39m\n");
  }
  if (feof(sp)) {
    fprintf(stderr, "\033[33mError: no data\n");
    fprintf(stderr,
            "Please put the total number of records at the head, followed by "
            "the records.\033[39m\n");
    exit(EXIT_FAILURE);
  }
  if ((*p = (SRec *)malloc(sizeof(SRec) * n)) == NULL) {
    fprintf(stderr, "\033[33mError: memory shortage\n");
    fprintf(stderr, "Data size is too large.\n\033[39m");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    int ret;
    ret =
        fscanf(sp, "%f %d %s", &((*p)[i].gpa), &((*p)[i].credit), (*p)[i].name);
    if (ret < 3) {
      fprintf(stderr, "\033[33mError: failed to scan the records\n");
      fprintf(
          stderr,
          "Please check the data format and the num of elements.\033[39m\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(sp);
  return n;
}

void output(char *tfname, SRec *p, int n) {
  FILE *tp;
  if ((tp = fopen(tfname, "w")) == NULL) {
    fprintf(stderr, "\033[33mError: failed to open the file \'%s\'\033[39m\n",
            tfname);
    exit(EXIT_FAILURE);
  }

  fprintf(tp, "%d\n", n);

  for (int i = 0; i < n; i++) {
    fprintf(tp, "%-f %3d %-s", p[i].gpa, p[i].credit, p[i].name);
    if (i + 1 != n) fprintf(tp, "\n");
  }

  fclose(tp);
}

void printRecords(SRec *p, int n) {
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    printf("%f %3d %-s\n", p[i].gpa, p[i].credit, p[i].name);
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

void simpleSort(SRec *arr, int len, int (*comp)(const void *, const void *)) {
  for (int k = len - 1; k >= 1; k--) {
    SRec max = arr[0];
    int max_idx = 0;
    for (int i = 1; i <= k; i++) {
      if ((*comp)(&arr[i], &max) >= 1) {
        max = arr[i];
        max_idx = i;
      }
    }

    if (max_idx == k) continue;
    SRec tmp = arr[k];
    arr[k] = arr[max_idx];
    arr[max_idx] = tmp;
  }
}