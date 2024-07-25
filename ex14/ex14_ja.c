#include "ex14.h"

static const char *month_names_ja[] = {
    "存在しないよ", "睦月", "如月", "弥生",   "卯月", "皐月", "水無月",
    "文月",         "葉月", "長月", "神無月", "霜月", "師走"};

void whatday_ja(int day_of_the_year) {
    int month, day;
    int status = whatday(day_of_the_year, &month, &day);
    if (status == WHATDAY_NG) {
        fprintf(stderr, "与えられた日数が正しい範囲にありません．\n");
        exit(EXIT_FAILURE);
    }

    printf("年頭から%d日目は%s%d日\n", day_of_the_year, month_names_ja[month],
           day);
}