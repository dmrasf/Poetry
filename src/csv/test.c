#include "csv.h"
#include <stdio.h>
#include <stdlib.h>

#define PATH "test.csv"

int main(void)
{
    csv_t* ct;
    char* title;

    ct = CsvInit(PATH);

    while ((title = CsvGetTitle(ct)) != NULL) {
        printf("%s\n", title);
    }

    while ((title = CsvGetTitle(ct)) != NULL) {
        printf("%s\n", title);
    }
    while ((title = CsvGetTitle(ct)) != NULL) {
        printf("%s\n", title);
    }
    while ((title = CsvGetTitle(ct)) != NULL) {
        printf("%s\n", title);
    }
    CsvDestroy(ct);

    exit(0);
}
