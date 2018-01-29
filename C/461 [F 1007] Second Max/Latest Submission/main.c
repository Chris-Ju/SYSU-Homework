#include<stdio.h>
int main()
{
	int i,j,number,every,remove;
	scanf("%d",&number);
	int result[number];
	for(i=0;i<number;i++)
	{
		scanf("%d",&every);
		int string[every];
		for(j=0,result[i]=0;j<every;j++)
		{
			scanf("%d",&string[j]);
			if(string[j]>=result[i])
            {
            result[i]=string[j];
            remove=j;
            }
		}
		for(j=0,result[i]=0;j<every;j++)
		{
			if((string[j]>=result[i])&&(j!=remove))
			result[i]=string[j];
		}
		printf("%d\n",result[i]);
	}
	return 0;
}