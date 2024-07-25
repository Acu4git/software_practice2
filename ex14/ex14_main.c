#include <errno.h>

#include "ex14.h"

#define BUFSIZE 64

static const int num_of_days[] = {-1, 31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};

int main() {
    int day_of_the_year;
    char lang[BUFSIZE], day_str[BUFSIZE], *endptr;

    printf("Language? (\"Japanese\" or \"English\") : ");
    fgets(lang, BUFSIZE - 1, stdin);
    lang[strlen(lang) - 1] = '\0';
    printf("Day of the year? : ");
    fgets(day_str, BUFSIZE - 1, stdin);
    day_str[strlen(day_str) - 1] = '\0';

    errno = 0;
    day_of_the_year = (int)strtol(day_str, &endptr, 10);

    if (strcmp(lang, "Japanese") == 0) {
        // オーバーフロー等のエラー
        if (errno != 0) {
            fprintf(stderr, "数値がオーバーフローした可能性があります\n");
            exit(EXIT_FAILURE);
        }

        // 数字が存在しない場合
        if (endptr == day_str) {
            fprintf(stderr, "数値が見つかりません．\n");
            exit(EXIT_FAILURE);
        }

        // 変換に余分な文字が含まれている場合
        if (*endptr != '\0') {
            printf("余分な文字列が含まれています: %s\n", endptr);
            exit(EXIT_FAILURE);
        }
        whatday_ja(day_of_the_year);
    } else if (strcmp(lang, "English") == 0) {
        // オーバーフロー等のエラー
        if (errno != 0) {
            fprintf(stderr, "Numerical overflow may have occurred.\n");
            exit(EXIT_FAILURE);
        }

        // 数字が存在しない場合
        if (endptr == day_str) {
            fprintf(stderr, "No digits were found.\n");
            exit(EXIT_FAILURE);
        }

        // 変換に余分な文字が含まれている場合
        if (*endptr != '\0') {
            printf("Further characters after number: %s\n", endptr);
            exit(EXIT_FAILURE);
        }
        whatday_en(day_of_the_year);
    } else {
        fprintf(stderr, "Invalid language\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int whatday(int __day, int *month, int *day) {
    if (__day <= 0 || __day > 365) return WHATDAY_NG;

    int __month;
    *day = 0;
    for (__month = 1; __month <= 12; __month++) {
        if (__day <= num_of_days[__month]) break;
        __day -= num_of_days[__month];
    }

    *month = __month;
    *day = __day - *day;

    return WHATDAY_OK;
}