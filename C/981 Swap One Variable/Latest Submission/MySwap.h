void mySwapInt(int *a, int *b)
{
    int *p = a;
    int *q = b;
    int bri = *a;
    *p = *b;
    *q = bri;
}