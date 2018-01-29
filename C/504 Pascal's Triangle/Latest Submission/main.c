#include<stdio.h>
int main()
{
    int lines;
    scanf("%d",&lines);
    int num[32][32];
    int line;
    int no;
    int space;
    if(lines==0);
    else if(lines==1)
        printf("1\n");
    else if(lines==2)
        printf(" 1\n1 1\n");
    else
    {
        for(space=0;space<(lines-1);space++)
            printf(" ");
        printf("1\n");
        for(space=0;space<(lines-2);space++)
            printf(" ");
        printf("1 1\n");
        for(line=2;line<lines;line++)
        {
            num[line-1][line-1]=1;
            num[line-1][0]=1;
            for(space=0;space<(lines-line-1);space++)
                printf(" ");
            printf("1");
            for(no=1;no<line;no++)
            {
                num[line][no]=num[line-1][no-1]+num[line-1][no];
                printf(" %d",num[line][no]);
            }
            printf(" 1\n");
        }
    }
    return 0;
}


