#include <stdio.h>
#include "basicNumberReading.h"
unsigned long long basicNumberReading(int base) {
  int num = 0, digit = 0;
  char cha = 0;
  for (scanf(" %c", &cha); '0' <= cha && cha <= '9'; cha = getchar()) {
    digit = cha - '0';
    num = num * base + digit;
  }
  return num;  
}
