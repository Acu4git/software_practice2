#include "ex14.h"

static const char *month_names_en[] = {
    "Not exist", "January",  "February", "March",  "April",
    "May",       "June",     "July",     "August", "September",
    "October",   "November", "December"};

static const char *suffix[] = {"th", "st", "nd", "rd", "th",
                               "th", "th", "th", "th", "th"};

void whatday_en(int day_of_the_year) {
    int month, day;
    int status = whatday(day_of_the_year, &month, &day);
    if (status == WHATDAY_NG) {
        fprintf(stderr, "Day is not in the range of a year.\n");
        exit(EXIT_FAILURE);
    }
    printf("The %d%s day of a year is %s %d%s.\n", day_of_the_year,
           suffix[day_of_the_year % 10], month_names_en[month], day,
           suffix[day % 10]);
}