#include<stdio.h>
int main()
{
    int money;
    int items;
    scanf("%d %d",&money,&items);
    int price[items];
    int time;
    for(time=0;time<items;time++)
    scanf("%d",&price[time]);
    int left=money;
    int num;
    for(;;)
    {
        scanf("%d",&num);
        if(num==-1)
            break;
        else if(num==10)
        {
            printf("Ihen!\n");
            break;
        }
        else
                  {
            left-=price[num];
            if(left>=0)
                printf("You have %d yen now.\n",left);
            else
            {
                printf("BAKA!\n");
                break;
            }
        }
    }
    printf("Bye.\n");
    return 0;
}

