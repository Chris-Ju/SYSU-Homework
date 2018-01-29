#include <stdio.h>
int main()
{
	int act;
	int que[11]={0};
	int push=0,pop=0;
	while(scanf("%d",&act)!=EOF)
	{
		if(act==0)
		{
			if(pop==push)
				printf("Pop Failed. The queue is empty.\n");
			else
			{
				printf("%d\n",que[pop]);
				pop++;
				pop%=11;
			}
		}
		else
		{
			scanf("%d\n",&que[push]);
			if(push==pop+10||pop==push+1)
				printf("Push Failed. The queue is full.\n");
			else
			{
				push++;
				push%=11;
			}
		}
	}
	return 0;
}