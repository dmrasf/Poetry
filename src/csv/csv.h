#ifndef CSV_H__
#define CSV_H__

typedef void csv_t;

csv_t* CsvInit(const char*);

char* CsvGetTitle(csv_t*);

void CsvDestroy(csv_t*);

#endif
