#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

typedef struct {
  char gender;
  char name[7];
  unsigned id;
  unsigned score;
} Record;

typedef Record *RecordPtr;

void readRecords(RecordPtr records, size_t total);
void printRecords(RecordPtr records, size_t total);
void printRecordPtrs(RecordPtr *recordPtrs, size_t total);
void sortRecordPtrsBy(RecordPtr *recordPtrsToSort,
                      size_t recordTotal,
                      int option);

#endif  // TABLE_H
