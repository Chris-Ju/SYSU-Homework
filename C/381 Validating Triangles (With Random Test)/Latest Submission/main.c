#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	if((a+b>c)&&(a+c>b)&&(b+c>a))
	printf("valid\n");
	else
	printf("invalid\n");
	return 0;
}