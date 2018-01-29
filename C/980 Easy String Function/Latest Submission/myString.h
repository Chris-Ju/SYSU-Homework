int myStrlen(char a[])
{
    int i=0;
    while(a[i]!=0)
        i++;
    return i;
}
int myStrcmp(char a[],char b[])
{
    int i=0;
    while(a[i]!=0&&b[i]!=0)
    {
        if(a[i]>b[i])
            return 1;
        else if(a[i]<b[i])
            return -1;
        else
        {
        i++;
        continue;
        }
    }
    return 0;
}
void myStrcpy(char des[], char src[]) 
{
    int i=0;
    while(src[i]!=0)
    {
        des[i]=src[i];
        i++;
    }
    des[i]=0;
}