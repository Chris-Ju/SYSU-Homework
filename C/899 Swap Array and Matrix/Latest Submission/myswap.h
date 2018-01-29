void swapArray(int len, int arr1[len], int arr2[len])
{
  int i;
  for(i=0;i<len;i++)
  {
     arr1[i]+=arr2[i];
     arr2[i]=arr1[i]-arr2[i];
     arr1[i]-=arr2[i];
  }
    
}
void swapMatrix(int len, int mat1[len][len], int mat2[len][len])
{
  int i,j;
  for(i=0;i<len;i++)
    for(j=0;j<len;j++)
    {
      mat1[i][j]+=mat2[i][j];
  		mat2[i][j]=mat1[i][j]-mat2[i][j];
  		mat1[i][j]-=mat2[i][j];
    }
}