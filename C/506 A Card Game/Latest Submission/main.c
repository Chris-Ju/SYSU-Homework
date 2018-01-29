#include<stdio.h>
int main()
{
    long int number;
    scanf("%ld",&number);
    int num[100000];
    int sum;
    int time;
    int apple;
    int boy;
    int bri;
    int num0=0;
    int num3=0;
    int num5=0; 
    int num7=0;
    int num9=0;
    for(time=0,sum=0;time<number;time++)
        {
            scanf("%d",&num[time]);
            sum+=num[time];
            sum%=3;
            switch(num[time])
            {
            	case 0:
            		num0++;
            		break;
            	case 3:
            		num3++;
            		break;
            	case 5:
            		num5++;
            		break;
            	case 7:
            		num7++;
            		break;
            	case 9:
            		num9++;
            		break;
            }
        }
    for(time=0;time<number;time++)
        if(num[time]==0)
            break;
    if(sum!=0||time==number||num0==number)
        printf("no such number\n");
    else
    {
        for(time=0;time<num9;time++)
        	printf("9");
        for(time=0;time<num7;time++)
        	printf("7");
        for(time=0;time<num5;time++)
        	printf("5");
        for(time=0;time<num3;time++)
        	printf("3");
        for(time=0;time<num0;time++)
        	printf("0");
        printf("\n");
    }
    return 0;
}

