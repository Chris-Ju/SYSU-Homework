#include<string.h>
int split(char ret[][100], const char str[], const char del)
{
    int n=strlen(str);
    int i,j,k;
    for(i=0,j=0,k=0;i<n;i++)
    {
        if(str[i]!=del)
            ret[j][k++]=str[i];
        else
        {
            ret[j][k]=0;
            j++;
            k=0;
        }
    }
    for(k=0;k<=j;k++)
        printf("%s\n",ret[k]);
    return 0;
}
void lstrip(char str[], const char del)
{
    int n=strlen(str);
    int i;
    for(i=0;i<n;i++)
        if(str[i]!=del)
            break;
    printf("%s\n",str+i);
}
void rstrip(char str[], const char del)
{
    int n=strlen(str);
    int i,j;
    for(i=0;i<n;i++)
        if(str[i]!=del)
            break;
    for(j=n-1;j>0;j--)
        if(str[j]!=del)
            break;
    for(;i<=j;i++)
        printf("%c",str[i]);
    printf("\n");
}
void strip(char str[], const char del)
{
    int n=strlen(str);
    int i,j;
    for(i=0;i<n;i++)
        if(str[i]!=del)
            break;
    for(j=n-1;j>0;j--)
        if(str[j]!=del)
            break;
    for(;i<=j;i++)
        printf("%c",str[i]);
    printf("\n");
}