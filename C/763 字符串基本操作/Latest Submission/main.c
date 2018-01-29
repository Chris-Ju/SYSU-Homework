#include<stdio.h>
#include<string.h>
int lower(char a);
int uppter(char a);
int main()
{
    char str1[41],str2[41];
    scanf("%s %s",str1,str2);
    int n,x,y;
    scanf("%d %d %d",&n,&x,&y);
    int result,length;
    result = strcmp(str1,str2);
    if(result<0)
        printf("%s < %s\n",str1,str2);
    else if(result>0)
        printf("%s > %s\n",str1,str2);
    else
        printf("%s = %s\n",str1,str2);
    length = strlen(str2);
    if(n>=length)
        strcat(str1,str2);
    else
        strncat(str1,str2,n);
    for(;x<=y;x++)
        str1[x]=uppter(str1[x]);
    length = strlen(str1);
    printf("the length of \"%s\" is %d\n",str1,length);
    strcpy(str2,str1);
    for(n=0;n<length;n++)
        str2[n]=lower(str2[n]);
    result = strcmp(str1,str2);
    if(result<0)
        printf("%s < %s\n",str1,str2);
    else if(result>0)
        printf("%s > %s\n",str1,str2);
    else
        printf("%s = %s\n",str1,str2);
    if((length/2-10)>0)
        printf("%s\n",str1);
    else
        printf("%s\n",str2);
    return 0;
}
int lower(char a)
{
    if(a<='Z'&&a>='A')
        a+=32;
    return a;
}
int uppter(char a)
{
    if(a<='z'&&a>='a')
        a-=32;
    return a;
}