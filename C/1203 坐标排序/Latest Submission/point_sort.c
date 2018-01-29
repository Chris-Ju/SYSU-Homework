 #include<stdio.h>
#include "point_sort.h"
void point_sort(struct point a[], int n)
{
    int i,j,tmp;
    for(i=0;i<n;i++)
    {
        for(j=n-1;j>0;j--)
        {
            if(a[j].x<a[j-1].x)
            {
                tmp=a[j].x;
                a[j].x=a[j-1].x;
                a[j-1].x=tmp;
                tmp=a[j].y;
                a[j].y=a[j-1].y;
                a[j-1].y=tmp;
            }
            if(a[j].x==a[j-1].x)
            {
                if(a[j].y<a[j-1].y)
                {
                    tmp=a[j].x;
                    a[j].x=a[j-1].x;
                    a[j-1].x=tmp;
                    tmp=a[j].y;
                    a[j].y=a[j-1].y;
                    a[j-1].y=tmp;
                } 
            }
        }   
    }
}