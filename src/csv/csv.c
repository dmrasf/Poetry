#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CSV 100

struct csv_st {
    FILE* fp;
    char* fileName;
    int pos;
};

static struct csv_st* jobs[MAX_CSV];

static int getFreePos();

csv_t* CsvInit(const char* s)
{
    struct csv_st* cst;
    if ((cst = malloc(sizeof(*cst))) == NULL)
        return NULL;

    if ((cst->fp = fopen(s, "r")) == NULL) {
        perror("fopen failed!");
        exit(1);
    }
    cst->pos = getFreePos();
    cst->fileName = malloc(sizeof(char));
    strcpy(cst->fileName, s);

    return cst;
}

void CsvDestroy(csv_t* ptr)
{
    struct csv_st* cst = ptr;
    jobs[cst->pos] = NULL;
    fclose(cst->fp);
    free(cst->fileName);
    free(cst);
}

static int getFreePos()
{
    int i = 0;
    while (jobs[i] != NULL)
        i++;
    return i;
}
