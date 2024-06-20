#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 200

typedef struct school_record {
  float gpa;
  int credit;
  char name[MAX_NAME_LENGTH];
  struct school_record *next;
} SRec;

SRec *tail = NULL;

SRec *input(char *);
void insert(SRec);
void printToScreen(SRec *);
void output(char *, SRec *);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Error:invalid arguments\n");
    exit(1);
  }
  SRec *head;
  head = input(argv[1]);
  printf("----------Input----------\n");
  printToScreen(head);
  output(argv[2], head);
  printf("----------Output----------\n");
  printToScreen(head);
  return 0;
}

SRec *input(char *inFileName) {
  FILE *sp;
  // ファイルが存在するかどうか
  if ((sp = fopen(inFileName, "r")) == NULL) {
    fprintf(stderr, "Failed to open the file \"%s\".", inFileName);
    exit(1);
  }

  SRec head, tmp;
  head.next = NULL;
  tail = &head;
  int cnt = 0;  // 読み込みカウント
  while (fscanf(sp, "%f", &tmp.gpa) != EOF) {
    fscanf(sp, "%d", &tmp.credit);
    fscanf(sp, "%s", tmp.name);
    insert(tmp);
    cnt++;
  }
  // 空データならカウントが進まない
  if (cnt == 0) {
    fprintf(stderr, "No data.\n");
    exit(1);
  }
  fclose(sp);
  return head.next;
}

// 後で追加できるようにグローバル変数宣言したtailを用いる
void insert(SRec record) {
  SRec *p;
  if ((p = (SRec *)malloc(sizeof(SRec))) == NULL) {
    fprintf(stderr, "Failed to allocate memory.");
    exit(1);
  }
  p->gpa = record.gpa;
  p->credit = record.credit;
  strcpy(p->name, record.name);
  p->next = NULL;
  tail->next = p;
  tail = p;
}

// 画面出力用
void printToScreen(SRec *p) {
  while (p != NULL) {
    printf("%-f %3d %-s\n", p->gpa, p->credit, p->name);
    p = p->next;
  }
  putchar('\n');
}

void output(char *outFileName, SRec *p) {
  FILE *tp;
  tp = fopen(outFileName, "w");
  while (p != NULL) {
    fprintf(tp, "%-f %3d %-s\n", p->gpa, p->credit, p->name);
    p = p->next;
  }
  fclose(tp);
}