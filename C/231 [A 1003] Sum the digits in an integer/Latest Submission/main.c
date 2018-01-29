#include<stdio.h>
int main()
{
	int a;
	scanf("%d",&a);
	int z=a/100;
	int x=(a-z*100)/10;
	int c=a-z*100-x*10;
	printf("%d\n",z+x+c);
	return 0;
}