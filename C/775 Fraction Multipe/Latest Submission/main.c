#include <stdio.h>
int min(int a,int b);
int main ()
{
	int a1,a2,b1,b2,result1,result2,times;
	int i,num,great;
	scanf("%d",&times);
	while(times--)
	{
		scanf("%d %d %d %d",&a1,&a2,&b1,&b2);
		if(a2==0||b2==0)
			printf("Not A Number\n");
		else if(a1==0||b1==0)
			printf("0\n");
		else
		{
			result1=a1*b1;
			result2=a2*b2;
			if(result1%result2==0)
				printf("%d",result1/result2);
			else
			{
				num=min(result1,result2);
				for(i=1;i<=num;i++)
					if(result1%i==0&&result2%i==0)
						great=i;
				printf("%d/%d",result1/great,result2/great);
			}
		}
	}
	return 0;
}
int min(int a,int b)
{
	 int num;
  if(a>b)
    num=b;
  else
    num=a;
  return num;
}