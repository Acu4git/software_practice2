#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 200
#define BUFSIZE 512

typedef struct school_record SRec;
struct school_record {
    float gpa;
    int credit;
    char name[MAX_NAME_LENGTH];
    SRec *next;
    SRec *left, *right;
};

SRec *input(char *);
int output(char *, SRec *);
void dumpList(SRec *);
void freeList(SRec *);
int compGpa(const void *, const void *);
int compCredit(const void *, const void *);
int compName(const void *, const void *);
void insert(SRec **, SRec *, int (*)(const void *, const void *));
SRec *binTreeSort(SRec *, int (*)(const void *, const void *));

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Error: invalid arguments\n");
        fprintf(stderr, "Usage: ./ex11 <target> <inFile> <outFile>\n");
        exit(EXIT_FAILURE);
    }

    SRec *student;
    if ((student = input(argv[2])) == NULL) {
        fprintf(stderr, "Failed\n");
        exit(EXIT_FAILURE);
    }
    printf("---------Input---------\n");
    dumpList(student);

    if (strcmp(argv[1], "gpa") == 0)
        student = binTreeSort(student, compGpa);
    else if (strcmp(argv[1], "credit") == 0)
        student = binTreeSort(student, compCredit);
    else if (strcmp(argv[1], "name") == 0)
        student = binTreeSort(student, compName);
    else {
        fprintf(stderr,
                "Error: invalid first argument \'%s\'\n"
                "Please choice \'gpa\', \'credit\' or \'name\'\n",
                argv[1]);
    }

    int ok = output(argv[3], student);
    if (ok) {
        printf("---------Output---------\n");
        dumpList(student);
    }

    freeList(student);

    return 0;
}

SRec *input(char *inFilename) {
    FILE *fp;
    if ((fp = fopen(inFilename, "r")) == NULL) {
        fprintf(stderr, "Failed to open the file \'%s\': %s\n", inFilename,
                strerror(errno));
        return NULL;
    }

    SRec *head = NULL, *p;
    SRec **tail = &head;

    char buf[BUFSIZE];
    char *token, *endptr;
    int row = 1;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if ((p = (SRec *)malloc(sizeof(SRec))) == NULL) {
            perror("malloc() (input)");
            return NULL;
        }

        // GPA
        errno = 0;
        token = strtok(buf, " \t");
        p->gpa = strtof(token, &endptr);
        if (endptr == token) {
            fprintf(stderr, "Error(record %d, GPA): Cannot parse any digits\n",
                    row);
            return NULL;
        }
        if (errno != 0) {
            fprintf(stderr, "Error(record %d, GPA): %s\n", row,
                    strerror(errno));
            return NULL;
        }
        if (*endptr != '\0') {
            fprintf(stderr,
                    "Error(record %d, GPA): Invalid strings were found\n", row);
            return NULL;
        }
        if (p->gpa < 0.0f) {
            fprintf(stderr, "Error(record %d, GPA): Negative GPA\n", row);
            return NULL;
        }
        // Credit
        errno = 0;
        token = strtok(NULL, " \t");
        if (token == NULL) {
            fprintf(stderr, "Error(record %d, Credit): No more data\n", row);
            return NULL;
        }
        p->credit = (int)strtol(token, &endptr, 10);
        if (endptr == token) {
            fprintf(stderr,
                    "Error(record %d, Credit): Cannot parse any digits\n", row);
            return NULL;
        }
        if (errno != 0) {
            fprintf(stderr, "Error(record %d, Credit): %s\n", row,
                    strerror(errno));
            return NULL;
        }
        if (*endptr != '\0') {
            fprintf(stderr,
                    "Error(record %d, Credit): Invalid strings were found\n",
                    row);
            return NULL;
        }
        if (p->credit < 0) {
            fprintf(stderr, "Error(record %d, Credit): Negative Credit\n", row);
            return NULL;
        }
        // Name
        errno = 0;
        token = strtok(NULL, " \t");
        if (token == NULL) {
            fprintf(stderr, "Error(record %d, Name): No more data\n", row);
            return NULL;
        }
        if (strlen(token) >= MAX_NAME_LENGTH) {
            fprintf(stderr,
                    "Error(record %d, Name): Name size is too large\n"
                    "Name length must be less than 200\n",
                    row);
            return NULL;
        }
        if (token[strlen(token) - 1] == '\n') token[strlen(token) - 1] = '\0';
        snprintf(p->name, MAX_NAME_LENGTH, "%s", token);

        // セルの更新
        p->next = p->left = p->right = NULL;
        *tail = p;
        tail = &(p->next);

        row++;
    }

    // 入力ファイルが空のとき
    if (feof(fp) && row == 1) {
        fprintf(stderr, "Error: \'%s\' contains no data\n", inFilename);
        return NULL;
    }

    fclose(fp);
    return head;
}

int output(char *outFilename, SRec *list) {
    FILE *fp;
    if ((fp = fopen(outFilename, "w")) == NULL) {
        fprintf(stderr, "Failed to open the file \'%s\': %s\n", outFilename,
                strerror(errno));
        return 0;
    }

    while (list != NULL) {
        fprintf(fp, "%9f %3d %s\n", list->gpa, list->credit, list->name);
        list = list->next;
    }

    fclose(fp);
    return 1;
}

void dumpList(SRec *list) {
    while (list != NULL) {
        printf(
            "(%5.3f %3d %10s) address:%p\n"
            "left:%-14p\tright:%p\n"
            "----------------------------------------------------------\n",
            list->gpa, list->credit, list->name, list, list->left, list->right);
        list = list->next;
    }
}

void freeList(SRec *head) {
    SRec *temp;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
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

void insert(SRec **tree, SRec *elem, int (*comp)(const void *, const void *)) {
    SRec **p = tree;
    while (*p != NULL) {
        int order = comp(elem, *p);
        if (order <= 0)
            p = &((*p)->left);
        else if (order > 0)
            p = &((*p)->right);
    }
    *p = elem;
}

SRec *binTreeSort(SRec *list, int (*comp)(const void *, const void *)) {
    SRec *sorted, *tree, *p;
    sorted = tree = NULL;
    p = list;

    // 二分木の作成
    while (p != NULL) {
        insert(&tree, p, comp);
        p = p->next;
    }

    // ソート(未実装)

    return list;  // 課題11では，ソートせずに帰す
}