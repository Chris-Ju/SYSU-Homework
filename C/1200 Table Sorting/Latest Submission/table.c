 #include<stdio.h>
#include<string.h>
#include"table.h"
int cmp1(const void *a,const void *b)
{
    if((*(Table *)a).gender!=(*(Table *)b).gender)
        return (*(Table *)a).gender>(*(Table *)b).gender?1:-1;
    return (*(Table *)a).id-(*(Table *)b).id;
}
int cmp2(const void *a,const void *b)
{
    return strcmp((*(Table *)a).name,(*(Table *)b).name);
}
int cmp3(const void *a,const void *b)
{
    return (*(Table *)a).id-(*(Table *)b).id;
}
int cmp4(const void *a,const void *b)
{
    if((*(Table *)a).score-(*(Table *)b).score==0)
        return (*(Table *)a).id-(*(Table *)b).id;
    return (*(Table *)b).score-(*(Table *)a).score;
}
void print(Table people[n])
{
    printf("%-6s %-6s %-8s %-5s\n","Gender","Name","Id","Score");
    for(int i=0;i<n;i++)
    {
        printf("%-6c ",people[i].gender);
        printf("%-6s ",people[i].name);
        printf("%-8d ",people[i].id);
        printf("%-5d\n",people[i].score);
    }
}