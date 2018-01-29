 #include<stdio.h>
int main()
{
    int times;
    int num,result;
    scanf("%d",&times);
    while(times--)
    {
        result=0;
        scanf("%d",&num);
        while(num!=0)
        {
            if(num&1)
                result++;
            num>>=1;
        }
        printf("%d\n",result);
    }
    return 0;
}