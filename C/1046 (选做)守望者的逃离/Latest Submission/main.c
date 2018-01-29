#include <stdio.h>
int main() 
{
    int m,s,t;
    int i,d1,d2;
    while(scanf("%d",&m)!=EOF){
    scanf("%d %d", &s, &t);
    d1 = d2 = 0;
    for (i = 1; i <= t; i++) 
    {
        if (m >= 10) 
        {
            d1 += 60; 
            m-= 10;                                    
        } 
        else
            m += 4;
        if (d1 > d2 + 17) 
            d2 = d1;
        else 
            d2 += 17;
        if (d2 >= s) 
            break;                                        
    }
    if (i > t) 
        printf("No\n%d\n", d2);
    else 
        printf("Yes\n%d\n", i);
    }
    return 0;

}