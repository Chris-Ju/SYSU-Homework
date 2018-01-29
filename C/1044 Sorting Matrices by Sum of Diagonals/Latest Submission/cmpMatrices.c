void inputMatrices(int *a,int size)
{
  	int i,j;
   for(i=0;i<size;i++)
  	for(j=0;j<size;j++)
     scanf("%d",a+i*4+j);
		return;
}
void printMatrices(int *a,int size)
{
  	int i,j;
  	for(i=0;i<size;i++)
  	{
   for(j=0;j<size-1;j++)  
      printf("%d ",a+i*4+j);
  	printf("%d\n",a+i*4+j);
  	}
  	printf("\n");
   return;
}