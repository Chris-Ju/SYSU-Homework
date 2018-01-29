#define size_t unsigned int
void swapAnyThing(void *a, void *b, size_t val_size)
{

    void *e = malloc(val_size);
    memcpy(e, a, val_size);
    memcpy(a, b, val_size);
    memcpy(b, e, val_size);
    free(e);
}