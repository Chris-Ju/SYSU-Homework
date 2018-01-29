#include <stdio.h>
#include <math.h>

int main()
{
    double x=0,re=0;
    scanf("%lf",&x);
    if(x<-1){
        re = x+1;
    }
    else if(x<1){
        re = fabs(x);
    }
    else{
        re = log(x)/log(10);
    }
    printf("%.2lf\n",re);
    return 0;
}
