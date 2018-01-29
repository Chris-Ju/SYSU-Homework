#include "Oper.h"
#include <string.h>

void add(char lhs[], char rhs[], char sum[]) {
  int len_lhs = strlen(lhs), len_rhs = strlen(rhs);
  if (len_lhs < len_rhs) {
    add(rhs, lhs, sum);
    return;
  }
  int diff = len_lhs - len_rhs;
  sum[0] = sum[len_lhs + 1] = 0;
  for (int i = 1; i <= len_rhs; ++i) {
    sum[len_lhs - i + 1] = (lhs[len_lhs - i] - '0') + (rhs[len_rhs - i] - '0');
  }
  for (int i = 0; i < diff; ++i) {
    sum[i + 1] = lhs[i] - '0';
  }
  for (int i = len_lhs; i > 0; --i) {
    if (sum[i] > 9) {
      sum[i - 1] += sum[i] / 10;
      sum[i] %= 10;
    }
    sum[i] += '0';
  }
  if (!sum[0]) {
    for (int i = 0; i < len_lhs; ++i) {
      sum[i] = sum[i + 1];
    }
    sum[len_lhs] = 0;
  } else {
    sum[0] += '0';
  }
}