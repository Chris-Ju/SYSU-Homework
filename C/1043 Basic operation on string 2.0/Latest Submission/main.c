#include<stdio.h>
#include"function.h"
int main()
{
    char str[101];
    char ret[10][100];
    char del;
    scanf("%s",str);
    scanf("%c",&del);
    split(ret,str,del);
    scanf("%s",str);
    scanf("%c",&del);
    lstrip(str,del);
    rstrip(str,del);
    scanf("%s",str);
    scanf("%c",del);
    strip(str,del);
    return 0;
}
