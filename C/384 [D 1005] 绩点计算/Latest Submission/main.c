#include<stdio.h>
#include<math.h>
int main()
{
    float grade,GPA;
	scanf("%f",&grade);
	if((grade<0)||(grade>100))
	printf("Invalid\n");
	else if(grade<60)
	printf("Failed\n");
	else
	printf("%.1f\n",GPA=(grade-50)/10);
	return 0;
}