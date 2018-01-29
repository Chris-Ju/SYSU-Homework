#include<stdio.h>
#include<string.h>
#include <stdlib.h>
void rem(int a[],int b,int c);
void print();
int main()
{
    int n,i,j,random;
    unsigned seed;
    scanf("%d",&n);
    int num[n],copy[n];
    for(i=0;i<n;i++)
        scanf("%d",&num[i]);
    memcpy(copy,num,sizeof(copy));
    scanf("%u",&seed);
    srand(seed);
    for(i=0,j=n;i<n-1;i++,j--)
    {
        random = rand()%j;
        rem(num,random,j);
    }
    print(num,n);
    for(i=0,j=n;i<n-1;i++,j--)
    {
        random = rand()%j;
        rem(copy,random,j);
    }
    print(copy,n);
    return 0;
}
void rem(int a[],int b,int c)
{
    c--;
    int bri;
    bri=a[c];
    a[c]=a[b];
    a[b]=bri;
}
void print(int a[],int n)
{
    int i;
    if(n>1)
    {    
        printf("{%d,",a[0]);
        for(i=1;i<n-1;i++)
            printf(" %d,",a[i]);
        printf(" %d}\n",a[i]);
    }
    else
        printf("{%d}\n",a[0]);
}