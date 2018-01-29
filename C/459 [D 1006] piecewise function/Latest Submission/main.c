#include<stdio.h>
#include<math.h>
int main()
{
	double x,y;
	scanf("%lf",&x);
	if(x<-1)
	y=x+1;
	else if(x>=1)
	y=log10(x);
	else
	y=fabs(x);
	printf("%.2lf\n",y);
	return 0;
}