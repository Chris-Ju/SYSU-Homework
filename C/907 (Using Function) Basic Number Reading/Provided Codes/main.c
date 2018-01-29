#include <stdio.h>
#include "basicNumberReading.h"
int main() {
  int caseNum = 0, base = 0;
  scanf("%d %d", &caseNum, &base);
  for (int caseIndex = 0; caseIndex < caseNum; ++caseIndex) {
    printf("%llu\n", basicNumberReading(base));
  }   
  return 0;
} 
