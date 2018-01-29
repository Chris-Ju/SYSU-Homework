#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------ read records ------------- */

void readOneRecord(RecordPtr oneRecordPtr) {
  scanf(" %c %6s %u %u", &oneRecordPtr->gender, oneRecordPtr->name,
                           &oneRecordPtr->id, &oneRecordPtr->score);
}

void readRecords(RecordPtr records, size_t total) {
  for (size_t index = 0; index < total; ++index) {
    readOneRecord(&records[index]);
  }
}

/* ------------ print records ------------- */

void printTableHeader() {
  printf("%-6s %-6s %-8s %-5s\n", "Gender", "Name", "Id", "Score");
}

void printOneRecord(RecordPtr oneRecordPtr) {
  printf("%-6c %-6s %8u %-5u\n", oneRecordPtr->gender, oneRecordPtr->name,
                               oneRecordPtr->id, oneRecordPtr->score);
}

void printRecords(RecordPtr records, size_t total) {
  printTableHeader();
  for (size_t index = 0; index < total; ++index) {
    printOneRecord(&records[index]);
  }
  putchar('\n');
}

void printRecordPtrs(RecordPtr *recordPtrs, size_t total) {
  printTableHeader();
  for (size_t index = 0; index < total; ++index) {
    printOneRecord(recordPtrs[index]);
  }
  putchar('\n');
}

/* ------------ sort records ------------- */

int cmpRecordPtrsById(RecordPtr first, RecordPtr second) {
  if (first->id == second->id) {
    return 0;
  } else if (first->id < second->id) {
    return -1;
  } else {
    return 1;
  }
}

int cmpRecordPtrsByGender(RecordPtr first, RecordPtr second) {
  if (first->gender == second->gender) {
    return cmpRecordPtrsById(first, second);
  } else if (first->gender < second->gender) {
    return -1;
  } else {
    return 1;
  }
}

int cmpRecordPtrsByName(RecordPtr first, RecordPtr second) {
  int cmpResult = strncmp(first->name, second->name, sizeof(first->name) - 1);
  if (0 == cmpResult) {
    return cmpRecordPtrsById(first, second);
  } else if (cmpResult < 0) {
    return -1;
  } else {
    return 1;
  }
}


int cmpRecordPtrsByScore(RecordPtr first, RecordPtr second) {
  if (first->score == second->score) {
    return cmpRecordPtrsById(first, second);
  } else if (first->score < second->score) {
    return 1;
  } else {
    return -1;
  }
}

int cmpRecordPtrs(const void *firstRecordPtrPtr,
                   const void *secondRecordPtrPtr,
                   void *optionPtr) {
  RecordPtr firstRecordPtr = *((RecordPtr *)firstRecordPtrPtr),
            secondRecordPtr = *((RecordPtr *)secondRecordPtrPtr);
  int option = *((int *)optionPtr);
  switch (option) {
    case 1:
      return cmpRecordPtrsByGender(firstRecordPtr, secondRecordPtr);
    case 2:
      return cmpRecordPtrsByName(firstRecordPtr, secondRecordPtr);
    case 4:
      return cmpRecordPtrsByScore(firstRecordPtr, secondRecordPtr);
    default:
      break;
  }
  return cmpRecordPtrsById(firstRecordPtr, secondRecordPtr);
}

void sortRecordPtrsBy(RecordPtr *recordPtrsToSort, size_t recordTotal,
                      int option) {
  qsort_r(recordPtrsToSort, recordTotal, sizeof(RecordPtr),
          &cmpRecordPtrs, &option);
}

