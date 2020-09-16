#include "csv.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CSV 100
#define MAX_CONT 10240

struct csv_st {
    FILE* fp;
    char* fileName;
    int pos;
    unsigned int x;
    unsigned int y;
    char dlia;
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
    cst->x = 0;
    cst->y = 0;
    cst->fileName = malloc(sizeof(s));
    strcpy(cst->fileName, s);
    cst->dlia = ',';

    return cst;
}

static void csvSeek(csv_t* ptr, const unsigned int x, const unsigned int y)
{
    struct csv_st* cst = ptr;

    char* line = NULL;
    size_t st = 0;

    if (x < cst->x) {
        fseek(cst->fp, 0, SEEK_SET);
        cst->x = 0;
        cst->y = 0;
    }

    if (x != cst->x) {
        while (x != cst->x) {
            if (getline(&line, &st, cst->fp) == -1) {
                perror("x error!");
                exit(1);
            }
            cst->x++;
            cst->y = 0;
        }
    }

    if (y < cst->y && x == cst->x) {
        char c;
        while (1) {
            fseek(cst->fp, -2, SEEK_CUR);
            c = fgetc(cst->fp);
            if (c == '\n')
                break;
        }
        cst->y = 0;
    }

    char c;
    while (y != cst->y) {
        c = fgetc(cst->fp);
        if (c == EOF || c == '\n') {
            fprintf(stderr, "y error!\n");
            exit(1);
        }
        if (c == cst->dlia) {
            cst->y++;
        }
    }
}

static int titleInit = 1;
char* CsvGetTitle(csv_t* ptr)
{
    struct csv_st* cst = ptr;

    if (titleInit) {
        csvSeek(ptr, 0, 0);
        titleInit = 0;
    }

    if (cst->x != 0) {
        titleInit = 1;
        return NULL;
    }

    char tmpWord[100];
    static char* title;

    char c;
    int size = 0;
    for (size = 0;; size++) {
        c = fgetc(cst->fp);
        if (c == '\n' || c == EOF) {
            cst->x++;
            cst->y = 0;
            break;
        } else if (c == cst->dlia) {
            cst->y++;
            break;
        }
        tmpWord[size] = c;
    }
    tmpWord[size] = '\0';

    title = realloc(title, size);
    strcpy(title, tmpWord);

    return title;
}

void CsvGetContByPos(char** cont, const unsigned int x, const unsigned int y, csv_t* ptr)
{
    csvSeek(ptr, x, y);
    struct csv_st* cst = ptr;

    char tmpCont[MAX_CONT];
    int size = 0;
    char c;

    for (size = 0;; size++) {
        c = fgetc(cst->fp);
        if (c == '\n' || c == EOF) {
            cst->x++;
            cst->y = 0;
            break;
        } else if (c == cst->dlia) {
            cst->y++;
            break;
        }
        tmpCont[size] = c;
    }
    tmpCont[size] = '\0';

    *cont = realloc(*cont, 1 + size);

    if (cont == NULL) {
        fprintf(stderr, "realloc failed!\n");
        exit(1);
    }
    strcpy(*cont, tmpCont);
}

void CsvDestroy(csv_t* ptr)
{
    struct csv_st* cst = ptr;
    free(cst->fileName);
    if (fclose(cst->fp) != 0) {
        perror("fclose!");
        exit(1);
    }
    jobs[cst->pos] = NULL;
    free(cst);
}

static int getFreePos()
{
    int i = 0;
    while (jobs[i] != NULL)
        i++;
    return i;
}
