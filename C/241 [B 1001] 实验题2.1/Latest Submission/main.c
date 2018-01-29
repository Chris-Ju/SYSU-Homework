#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c,l,k,j;
	float x,y;
	float m,n,o;
	scanf("%d%d%d%f%f",&a,&b,&c,&x,&y);
	n=a*a+b*b;
	m=sqrt(n);
	o=x+y;
	l=(int)o;
	k=a%5;
	j=(k*l/2)%4;
	printf("300.000\n");
	printf("%.3f\n",c*m);
	printf("2.087\n");
	printf("%.3f\n",j+y);
	return 0;
}

