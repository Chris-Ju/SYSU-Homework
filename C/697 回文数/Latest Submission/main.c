#include<stdio.h>
#include<string.h>
int main()
{
	int time,times,num,every;
	char str1[10],str2[10];
	scanf("%d",&times);
	for(time=0;time<times;time++)
	{
	for(every=0;every<10;every++)
		str1[every]=str2[every]=0;
 	scanf("%s",str1);
	num=strlen(str1);
	for(every=0;every<num;every++)
		str2[every]=str1[num-every-1];
	if(strcmp(str1,str2)==0)
		printf("Yes\n");
	else
		printf("No\n");
	}
	return 0;
}
