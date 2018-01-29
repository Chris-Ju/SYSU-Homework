#include<stdio.h>
#include<math.h>
int main()
{
	long x,y,num;
	int i,result;
	scanf("%ld %ld",&x,&y);
	if(x>y)
	num=y;
	else
	num=x;
	for(i=1;i<=num;i++)
	{
		if((x%i==0)&&(y%i==0))
		result=i;
	}
	printf("%d\n",result);
	return 0;
}