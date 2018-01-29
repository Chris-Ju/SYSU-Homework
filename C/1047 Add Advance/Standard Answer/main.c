#include <stdio.h>
#include "Oper.h"
int main() {
  char left[30] = {}, mid[30] = {}, right[30] = {};
  scanf("%s %s %s", left, mid, right);
  char *sum = addTripleNum(left, mid, right);
  printf("%s + %s + %s = %s\n", left, mid, right, sum);
  freeSum(sum);
  return 0;
}