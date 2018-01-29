 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"table.h"
void main()
{
    scanf("%d",&n);
    Table people[n];
    Table original[n];
    for(int i=0;i<n;i++)
    {
        scanf(" %c",&people[i].gender);
        scanf(" %s",people[i].name);
        scanf("%d",&people[i].id);
        scanf("%d",&people[i].score);
    }
    
    memcpy(original,people,n*sizeof(Table));
    int act;
    while(scanf("%d",&act)&&act!=-1)
    {
        memcpy(people,original,n*sizeof(Table));
      	switch(act)
        {
            case 0:print(original);printf("\n");continue;
            case 1:qsort_r(people,n,sizeof(Table),cmp1);break;
            case 2:qsort_r(people,n,sizeof(Table),cmp2);break;
            case 3:qsort_r(people,n,sizeof(Table),cmp3);break;
            case 4:qsort_r(people,n,sizeof(Table),cmp4);break;
        }
        print(people);
      	printf("\n");
    }
}