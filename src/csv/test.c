#include "csv.h"
#include <stdio.h>
#include <stdlib.h>

/*#define PATH "/home/dmr/Desktop/Poetry/魏晋.csv"*/
#define PATH "../../元.csv"

int main(void)
{
    csv_t* ct;
    char* title;

    ct = CsvInit(PATH);


    char* cont = NULL;

    for (int i = 45; i < 140; i++) {
        for (int j = 2; j < 4; j++) {
            printf("i = %d, j = %d\n", i, j);
            CsvGetContByPos(&cont, i, j, ct);
            printf("%s\n", cont);
        }
    }

    CsvDestroy(ct);

    exit(0);
}
