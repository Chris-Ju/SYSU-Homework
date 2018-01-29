#include<stdio.h>
int main()
{
	int num1,num2;
	scanf("%d %d",&num1,&num2);
	if(num1<=0||num2<=0)
		printf("invalid\n");
	else
	{
		int i,least,great;
		if(num1>num2)
		{
			num1+=num2;
			num2=num1-num2;
			num1-=num2;
		}
		for(i=1;i<=num1;i++)
			if(num1%i==0&&num2%i==0)
				great=i;
		least=num1*num2/great;
		printf("%d %d\n",great,least);
	}
	return 0;
}