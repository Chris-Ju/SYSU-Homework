#include<stdio.h>
#include<math.h>
int main()
{
	long num,i=2;
	scanf("%ld",&num);
	for(i=2;;i++)
	{
		if(num==1)
        {
        printf("No\n");
          break;
        }
        if(num==i)
		{
	    printf("Yes\n");
	    break;
	    }
		else if((num>i)&&(num%i==0))
		{
		printf("No\n");
		break;
	    }
	    else
	    continue;
	}
	return 0;
}