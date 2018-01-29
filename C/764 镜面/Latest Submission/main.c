#include<stdio.h>
int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    char input[M];
    int i,j;
    for(i=0;i<N;i++)
    {
        scanf("%s",input);
        for(j=0;j<M;j++)
        {
            if(input[M-j-1]=='b')
                printf("d");
            else if(input[M-j-1]=='d')
                printf("b");
            else if(input[M-j-1]=='p')
                printf("q");
            else if(input[M-j-1]=='q')
                printf("p");
            else
                printf("%c",input[M-j-1]);
        }
        printf("\n");
    }
    return 0;
}
