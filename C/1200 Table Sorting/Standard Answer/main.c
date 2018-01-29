#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main() {
  size_t recordTotal = 0;
  scanf("%zu", &recordTotal);

  RecordPtr records = calloc(recordTotal, sizeof(Record));
  readRecords(records, recordTotal);

  RecordPtr *recordPtrsToSort = calloc(recordTotal, sizeof(RecordPtr));
  for (size_t recordIndex = 0; recordIndex < recordTotal; ++recordIndex) {
    recordPtrsToSort[recordIndex] = &records[recordIndex];
  }

  int option = 0;
  while (scanf("%d", &option) == 1 && -1 != option) {
    if (option) {
      sortRecordPtrsBy(recordPtrsToSort, recordTotal, option);
      printRecordPtrs(recordPtrsToSort, recordTotal);
    } else {
      printRecords(records, recordTotal);
    }
  }

  free(records);
  free(recordPtrsToSort);
}
