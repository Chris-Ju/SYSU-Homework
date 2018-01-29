#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	int time,times,base,n,i,j;
	scanf("%d %d",&times,&base);
	char num[10];
	char num1[10];
	char result[10];
  char result1[10];
	long long int input,input1,output,output1,bri;
	for(time=0;time<times;time++)
	{
	    for(i=0;i<10;i++)
            num[i]=num1[i]=result[i]=result1[i]=0;
    input1=output1=0;
		scanf("%s",num);
		n=strlen(num);
		for(i=0;i<n;i++)
			result[i]=num[n-i-1];
		input=atol(num);
		sprintf(num1,"%lld",input);
		n=strlen(num1);
		for(i=0;i<n;i++)
		{
			bri=(num1[i]-48)*pow(base,n-i-1);
			input1 += bri;
		}
		output=atol(result);
		sprintf(result1,"%lld",output);
		j=strlen(result1);
		for(i=0;i<j;i++)
		{	
			bri=(result1[i]-48)*pow(base,j-i-1);
			output1+=bri;
		}
		printf("%lld %lld\n",input1,output1);
	}
	return 0;
}
