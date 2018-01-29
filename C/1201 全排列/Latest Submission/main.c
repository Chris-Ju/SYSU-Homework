 #include<stdio.h>
int n[9]={0};
int num;
void sort(int);
void print();
void main()
{
    scanf("%d",&num);
    sort(0);
}
void sort(int i)
{
    int j,k;
    for(j=1;j<=num;j++)
    {
        for(k=0;k<i;k++)
            if(n[k]==j)
                break;
        if(k==i)
        {
            n[i]=j;
            if(i==num-1)
            {
                print();
                return;
            }
            sort(i+1);
        }
    }
}
void print()
{
    int i;
    for(i=0;i<num;i++)
        printf("%d%c",n[i],i==num-1?'\n':' ');
}
