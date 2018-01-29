#include<stdio.h>
int main()
{
	int n,m,i;
	scanf("%d%d",&n,&m);
	for(;n<=m;n++)
	{
		for(i=2;i<n;i++)
		{
			if(n%i==0)
			break;
		}
		if(i==n)
		break;
	}
	if(n==m+1)
	printf("none\n");
	else
	printf("%d\n",n);
	return 0;
}