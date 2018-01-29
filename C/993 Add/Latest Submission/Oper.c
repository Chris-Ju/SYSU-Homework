#include<stdlib.h>
void add(char a[], char b[], char c[])
{
    long plus;
    plus=atol(a)+atol(b);
    sprintf(c,"%ld",plus);
}