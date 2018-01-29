#include<stdio.h>
int main()
{
	char a;
	long long int z,x,c;
	double v,b;
	scanf("%c %lld %lf %lld %lld %lf",&a,&z,&v,&x,&c,&b);
	printf("%c %lld %.2lf %lld %lld %.7lf\n",a,z,v,x,c,b);
	return 0; 
} 