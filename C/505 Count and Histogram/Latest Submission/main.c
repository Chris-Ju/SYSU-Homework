#include<stdio.h>
int main()
{
    int num=0,nob=0,nout=0,nliz=0,nlix=0;
    char letter[405];
    char out[27];
    int time[27];
    char bri=0;
    int word=0;
    for(nliz=0;nliz<405;nliz++)
        letter[nliz]=' ';
    for(nliz=0;nliz<27;nliz++)
    {
        out[nliz]=' ';
        time[nliz]=0;
    }
    while(scanf("%c",&letter[num])!=EOF)
        num++;
    for(nob=0;nob<num;nob++)
    {
        if((letter[nob]!=' ')&&(letter[nob]!=10))
        {
            for(nliz=nob+1;nliz<num;nliz++)
            {
                if(letter[nliz]==' '||letter[nliz]==10)
                    break;
            }
            word++;
            nob=nliz;
        }
    }
    for(nob=0;nob<num;nob++)
    {
        if((letter[nob]!=' ')&&(letter[nob]!=10))
        {
            for(nliz=0;nliz<nout;nliz++)
                if(out[nliz]==letter[nob])
                    break;
            if(nliz==nout)
            {

                out[nout]=letter[nob];
                nout++;
            }   
        }
    }
    for(nliz=0;nliz<nout;nliz++)
      for(nlix=nout-1;nlix>nliz;nlix--)
        {
            if(out[nlix-1]>out[nlix])
            {
                bri=out[nlix-1];
                out[nlix-1]=out[nlix];
                out[nlix]=bri;
            }
        }
    for(nliz=0;nliz<nout;nliz++)
    {
        time[nliz]=0;
        for(nlix=0;nlix<num;nlix++)
        {
            if(letter[nlix]==out[nliz])
                time[nliz]++;
        }
    }
    int max=0;
    for(nliz=0;nliz<nout;nliz++)
    {
        if(time[nliz]>max)
            max=time[nliz];
    }
    if(word>max)
        max=word;
    int line=max;
    for(nliz=0;nliz<max;nliz++,line--)
    {
        printf("%d\t",line);
        for(nlix=0;nlix<nout;nlix++)
        {
            
            if(time[nlix]>=line)
                printf("*");
            else
                printf(" ");
        }
        if(word>=line)
            printf("*\n");
        else
            printf(" \n");
    }
    if(num!=0)
    {
        printf(" \t");
        for(nliz=0;nliz<nout;nliz++)
            printf("%c",out[nliz]);
        printf("W\n");
    }
    return 0;
}
