#include <stdio.h>
#include "MySwap.h"

void mySwapInt(int *a, int *b);

int main() {
  int a = 0, b = 0;
  scanf("%d%d", &a, &b);

  mySwapInt(&a, &b);
  printf("a == %d, b == %d\n", a, b);
  return 0;
}
