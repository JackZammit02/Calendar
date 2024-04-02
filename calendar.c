#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NUM_PER_LINE 7

char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int dayList[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

char* week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int dayOfWeek(int month, int day, int year) {
    if (year < 1753 || month < 1 || month > 12 || day < 1 || day > dayList[month - 1]) {
        printf("Invalid input\n");
        return -1;
    }

    int dayCount = 0;

    for (int i = 1753; i < year; i++) {
        if (isLeapYear(i) == 1) {
            dayCount += 366;
        } else {
            dayCount += 365;
        }
    }

    if (isLeapYear(year) == 1) {
        dayList[1] = 29;
    } else {
        dayList[1] = 28; // Reset to default value
    }

    for (int i = 0; i < month - 1; i++) {
        dayCount += dayList[i];
    }

    return dayCount % 7;
}

int printMonth(int index, int year) {
    char* month = months[index - 1];
    int monLength = strlen(month);
    int length = monLength + 5;
    int numSpace = (20 - length) / 2;

    for (int i = 0; i < numSpace; i++) {
        printf(" ");
    }

    printf("%s %d\n", month, year);

    int newDay = dayOfWeek(index, 1, year);

    printf("Su Mo Tu We Th Fr Sa\n");

    int daySpaces = newDay * 3;

    for (int i = 0; i < daySpaces; i++) {
        printf(" ");
    }

    for (int i = 1; i <= dayList[index - 1]; i++) {
        printf("%2d ", i);
        newDay++;
        if (newDay % 7 == 0) {
            printf("\n");
        }
    }

    printf("\n");

    return 0;
}

int printYear(int year) {
    for (int i = 1; i <= 12; i++) {
        printMonth(i, year);
        printf("\n");
    }
}

int firstThree(char* input) {
    char firstThreeInput[4];
    strncpy(firstThreeInput, input, 3);
    firstThreeInput[3] = '\0';

    for (int i = 0; i <= 11; i++) {
        char* theMonth = months[i];
        char firstThreeMonth[4];
        strncpy(firstThreeMonth, theMonth, 3);
        firstThreeMonth[3] = '\0';

        if (strcasecmp(firstThreeMonth, firstThreeInput) == 0) {
            return i + 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    time_t s;
    struct tm* current_time;

    s = time(NULL);
    current_time = localtime(&s);

    if (argc == 1) {
        printMonth(current_time->tm_mon + 1, current_time->tm_year + 1900);
    } else if (argc == 2) {
        if (atoi(argv[1]) > 1752) {
            printYear(atoi(argv[1]));
        } else {
            printf("Invalid input: Year should be greater than 1752.\n");
        }
    } else if (argc == 3) {
        if (atoi(argv[1]) >= 1 && atoi(argv[1]) <= 12 && atoi(argv[2]) > 1752) {
            printMonth(atoi(argv[1]), atoi(argv[2]));
        } else if (strcasecmp(argv[1], "-m") == 0 && atoi(argv[2]) > 0) {
            printMonth(atoi(argv[2]), current_time->tm_year + 1900);
        } else if (strcasecmp(argv[1], "-m") == 0 && firstThree(argv[2]) != 0) {
            printMonth(firstThree(argv[2]), current_time->tm_year + 1900);
        } else {
            printf("Invalid input.\n");
        }
    } else if (argc == 4) {
        if (strcasecmp(argv[1], "-m") == 0 && firstThree(argv[2]) != 0 && atoi(argv[3]) > 1752) {
            printMonth(firstThree(argv[2]), atoi(argv[3]));
        } else if (strcasecmp(argv[1], "-m") == 0 && atoi(argv[2]) >= 1 && atoi(argv[2]) <= 12 && atoi(argv[3]) > 1752) {
            printMonth(atoi(argv[2]), atoi(argv[3]));
        } else {
            printf("Invalid input.\n");
        }
    } else {
        printf("You need an index.\n");
    }
    return 0;
}
