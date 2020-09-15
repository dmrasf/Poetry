#ifndef CSV_H__
#define CSV_H__

typedef void csv_t;

csv_t * CsvInit(const char*);

void CsvDestroy(csv_t*);

#endif

