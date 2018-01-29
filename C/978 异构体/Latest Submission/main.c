#include<stdio.h>
#include<string.h>
int main()
{
    char str1[51],str2[51];
    scanf("%s %s",str1,str2);
    int n1,n2;
    n1=strlen(str1);
    n2=strlen(str2);
    if(n1!=n2)
        printf("NO\n");
    else
    {
        int i,j,bri;
        for(j=0;j<n1;j++)
            for(i=n1-1;j<i;i--)
            {
                if(str1[i]<str1[i-1])
                {
                    bri=str1[i];
                    str1[i]=str1[i-1];
                    str1[i-1]=bri;
                }
                if(str2[i]<str2[i-1])
                {   
                    bri=str2[i];
                    str2[i]=str2[i-1];
                    str2[i-1]=bri;
                }
            }
        for(i=0;i<n1;i++)
            if(str1[i]!=str2[i])
                break;
        if(i!=n1)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}