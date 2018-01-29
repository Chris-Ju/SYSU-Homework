#include<stdio.h>
int times(int *,char *,int,int);
int main()
{
    int N,L;
    scanf("%d %d",&N,&L);
    int dis[N];
    char way[N];
    int i=0;
    for(i=0;i<N;i++)
        scanf("%s %d",&way[i],&dis[i]);
    i=1;
    while(times(dis,way,N,L))
        i++;
    printf("%d\n",i);
}
int times(int dis[],char way[],int N,int L)
{
    int i,j;
    for(i=0;i<N;i++)
    {
        if(way[i]=='R')
            dis[i]++;
        else if(way[i]=='L')
            dis[i]--;
        if(dis[i]>=L||dis[i]<=0)
            way[i]='A';
    }
    for(i=0;i<N;i++)
        for(j=i+1;j<N;j++)
        {
            if(dis[i]==dis[j]&&way[i]!='A'&&way[j]!='A')
            {
                if(way[i]=='R')
                    way[i]='L';
                else if(way[i]=='L')
                    way[i]='R';
                if(way[j]=='R')
                    way[j]='L';
                else if(way[i]=='L')
                    way[j]='R';
            }
        }
    for(i=0;i<N;i++)
        if(way[i]!='A')
            break;
    if(i==N)
        return 0;
    else
        return 1;
}