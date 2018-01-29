 #include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	float x1,x2;
	float e;
	e=sqrt(b*b-4*a*c);
	x1=(-b-e)/2/a;
	x2= (-b+e)/2/a;
	printf("%.3f %.3f\n",x1,x2);
	return 0;
} 
 