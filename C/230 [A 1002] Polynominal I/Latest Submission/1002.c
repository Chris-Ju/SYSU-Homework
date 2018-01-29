#include<stdio.h>
int main(){
	int a1,b1,a2,b2;
	scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
	int q=a1*a2,w=b1*a2+b2*a1,e=b1*b2;
	printf("%dx^2+%dx+%d\n",q,w,e);
	return 0;
}