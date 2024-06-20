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
};

SRec *input(char *);
void output(char *, SRec *);
void printRecords(SRec *);
void freeList(SRec *);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Error: you must pass 3 arguments.\n");
        fprintf(stderr, "Usage: ./ex08 <target> <inFile> <outFile>\n");
        exit(EXIT_FAILURE);
    }

    SRec *student;
    if ((student = input(argv[2])) == NULL) {
        fprintf(stderr, "Failed\n");
        exit(EXIT_FAILURE);
    }
    printf("---------Input---------\n");
    printRecords(student);

    output(argv[3], student);
    printf("---------Output---------\n");
    printRecords(student);

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
        token = strtok(buf, " ");
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
        // Credit
        errno = 0;
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error(record %d, Credit): No digits were found\n",
                    row);
            return NULL;
        }
        p->credit = (int)strtol(token, &endptr, 10);
        if (endptr == token) {
            fprintf(stderr,
                    "Error(record %d, Credit): cannot parse any digits\n", row);
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
        // Name
        errno = 0;
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error(record %d, Name): No strings were found\n",
                    row);
            return NULL;
        }
        if (strlen(token) >= MAX_NAME_LENGTH) {
            fprintf(stderr,
                    "Error(record %d, Name): Name size is too large\n"
                    "Name length must be less than 200\n",
                    row);
            return NULL;
        }
        snprintf(p->name, MAX_NAME_LENGTH, "%s", token);

        // セルの更新
        p->next = NULL;
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

void output(char *outFilename, SRec *list) {
    FILE *fp;
    if ((fp = fopen(outFilename, "w")) == NULL) {
        fprintf(stderr, "Failed to open the file \'%s\': %s\n", outFilename,
                strerror(errno));
        exit(EXIT_FAILURE);
    }

    while (list != NULL) {
        fprintf(fp, "%9f %3d %s", list->gpa, list->credit, list->name);
        list = list->next;
    }

    fclose(fp);
}

void printRecords(SRec *list) {
    while (list != NULL) {
        printf("%9f %3d %s", list->gpa, list->credit, list->name);
        list = list->next;
    }
    putchar('\n');
}

void freeList(SRec *head) {
    SRec *temp;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}