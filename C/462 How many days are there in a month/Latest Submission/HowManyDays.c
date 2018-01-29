#include<stdio.h>
int main()
{
	int month,year,leap;
	scanf("%d %d",&year,&month);
	if(year>=10000||year<=-1||month>12||month<1)
	printf("Invalid Input Detected.\n");
	else
	{
		if(year%100==0&&year%400==0)
	    leap=1;
	    else if(year%100!=0&&year%4==0)
	    leap=1;
	    else
	    leap=2;
	    switch(month)
	{
	    case 1:
	    case 3:
	    case 5:
	    case 7:
	    case 8:
	    case 10:
	    case 12:
		    printf("%04d/%02d has 31 days.\n",year,month);
		    break;
	    case 4:
	    case 6:
	    case 9:
	    case 11:
		    printf("%04d/%02d has 30 days.\n",year,month);
		    break;
	}
	if(month==2&&leap==1)
	printf("%04d/%02d has 29 days.\n",year,month);
	else if(month==2&&leap==2)
	printf("%04d/%02d has 28 days.\n",year,month);
	}
	return 0;
}