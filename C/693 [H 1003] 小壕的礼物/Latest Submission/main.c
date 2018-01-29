#include<stdio.h>
int main()
{
int time,times;
int con;
char get[100][100],give[100][100];
int apple=-1,boy=-1;
scanf("%d",&times);
for(time=0;time<times;time++)
{
scanf("%d",&con);
if(con==1)
{
apple++;
scanf("%s",get[apple]);
}
else if(con==2)
{
boy++;
scanf("%s",give[boy]);
printf("%s %s\n",give[boy],get[apple]);
apple--;
}
}
return 0;
}