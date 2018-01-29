#include<stdio.h>
#include<math.h>
#include<string.h>
long long unsigned basicNumberReading(int base)
{
  char num[1000];
  long long unsigned result=0,bri;
  scanf("%s",num);
  int i,n;
  n=strlen(num);
  for(i=0;i<n;i++)
  {
    num[i]-=48;
    bri=pow(base,n-i-1)*num[i];
    result+=bri;
  }
  return result;
}