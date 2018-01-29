#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* mul( char* , char*, int, int );
int main()
{
	char*	num1	= (char *)malloc(1002);
	char*	num2	= (char *)malloc(1002);
	scanf("%s", num1);
	scanf("%s", num2);

	int	size1	= strlen( num1 );
	int	size2	= strlen( num2 );

	for ( int i = 0, tmp; i < size1 / 2; i++ )
	{
		tmp			= num1[i];
		num1[i]			= num1[size1 - i - 1];
		num1[size1 - i - 1]	= tmp;
	}
	for ( int i = 0, tmp; i < size2 / 2; i++ )
	{
		tmp			= num2[i];
		num2[i]			= num2[size2 - i - 1];
		num2[size2 - i - 1]	= tmp;
	}
	int *result = mul( num1, num2, size1, size2 );
	for ( int i = size1 + size2 - 1; i >= 0; i--)
	{
		if ( result[i] == 0 && i == size1 + size2 - 1)
			continue;
		printf("%d",result[i]);
	}
	printf("\n");
	free(result);
	return 0;
}


int* mul( char* num1, char* num2, int size1, int size2 )
{
	int	size	= size1 + size2;
	int*	result	= (int*)malloc(size * sizeof(int));
	for ( int i = 0; i < size; i++ )
		result[i] = 0;
	for ( int i = 0, k; i < size1; i++ )
	{
		k = i;
		for ( int j = 0; j < size2; j++ )
		{
			result[k++] += (num1[i] - 48) * (num2[j] - 48);
		}
	}
	for ( int i = 0; i < size; i++ )
	{
		if ( result[i] > 10 )
		{
			result[i + 1]	+= result[i] / 10;
			result[i]	%= 10;
		}
	}
	free(num1);
	free(num2);
	return result;
}