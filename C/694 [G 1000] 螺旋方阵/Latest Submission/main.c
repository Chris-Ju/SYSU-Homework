#include<stdio.h>
int main()
{
int plat;
int row=0,col=-1;
int num=1;
scanf("%d",&plat);
int max=plat;
int matrix[plat][plat];
while(num<=plat*plat)
{
for(col++;col<max;col++,num++)
matrix[row][col]=num;
col--;
for(row++;row<max;row++,num++)
matrix[row][col]=num;
row--;
for(col--;col>=plat-max;col--,num++)
matrix[row][col]=num;
max--;
col++;
for(row--;row>=plat-max;row--,num++)
matrix[row][col]=num;
row++;
}
for(row=0;row<plat;row++)
{
for(col=0;col<plat-1;col++)
printf("%d ",matrix[row][col]);
printf("%d\n",matrix[row][col]);
}
return 0;
}

