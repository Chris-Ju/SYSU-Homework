#include<stdio.h>
int main()
{
	int ax,bx,cx,dx,ex,fx,gx,hx,ix;
	short a;
	ax=sizeof a;
	unsigned short b;
	bx=sizeof b;
	int c;
	cx=sizeof c;
	unsigned int d;
	dx=sizeof d;
	long e;
	ex=sizeof e;
	unsigned long f;
	fx=sizeof f;
	float g;
	gx=sizeof g;
	double h;
	hx=sizeof h;
	long double i;
	ix=sizeof i;
	printf("%d %d %d %d %d %d %d %d %d\n",ax,bx,cx,dx,ex,fx,gx,hx,ix);
	return 0;
}