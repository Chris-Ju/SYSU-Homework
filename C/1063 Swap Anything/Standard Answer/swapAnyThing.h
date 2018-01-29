#include <stdlib.h>
#include <string.h>
void swapAnyThing(void *a, void *b, size_t val_size) {
  void *mid = malloc(val_size);
  memcpy(mid, a, val_size);
  memcpy(a, b, val_size);
  memcpy(b, mid, val_size);
  free(mid);
}
