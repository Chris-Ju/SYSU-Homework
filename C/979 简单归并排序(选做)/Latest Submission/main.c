 #include<stdio.h>
int many,bri[100];
void sort(int num[],int start,int end);
void add(int num[],int start,int mid,int end);
int main()
{       
    int n;
    scanf("%d",&n);
    int i,num[n];
    many=n;
    for(i=0;i<n;i++)
        scanf("%d",&num[i]);
    sort(num,0,n-1);
    return 0;
}
void sort(int num[],int start,int end)
{
    int mid=(end+start)/2;
    if(end-start>1)
    {
        sort(num,start,mid);
        sort(num,mid+1,end);
    }
    add(num,start,mid,end);
}
void add(int num[],int start,int mid,int end)
{
    int i,j,k;
    if(end-start==1)
    {
        if(num[start]<num[end])
        {
            bri[0]=num[start];
            bri[1]=num[end];
        }
        else
        {
            bri[1]=num[start];
            bri[0]=num[end];
        }
    }
    else if(end==start)
        return;
    else
    {
        for(i=0,j=1,k=0;;)
        {
            if(num[i+start]<num[mid+j])
            {
                bri[k++]=num[i+start];
                i++;
            }
            else
            {
                bri[k++]=num[mid+j];
                j++;
            }
            if(start+i>mid)
            {
                for(;j+mid<=end;j++)
                    bri[k++]=num[j+mid];
                break;
            }
            else if(mid+j>end)
            {
                for(;i+start<=mid;i++)
                    bri[k++]=num[i+start];
                break;
            }
        }
    }
    for(i=start,j=0;i<=end;i++,j++)
        num[i]=bri[j];
    for(i=0;i<many-1;i++)
        printf("%d ",num[i]);
    printf("%d\n",num[i]);
}