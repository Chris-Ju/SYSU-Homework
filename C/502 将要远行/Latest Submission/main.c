#include<stdio.h>
#include<string.h>
int main()
{
	char number[100];
	scanf("%s",number);
	int time,times;
	times=strlen(number);
	int sum=0,result;
	for(time=0;time<times;time++)
	{
		number[time]-=48;
		sum+=number[time]%3;
	}
	result=sum%3;
	if(result==0)
	printf("God\n");
	else
	printf("Issac\n");
	return 0;
}