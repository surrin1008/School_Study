#include <stdio.h>
int main ()
{
	int a,b;
	int result;
	scanf("%d",&a);
	for(int i=1;i<=a;i++)
	{
		for(int n=1;n<=6;n++)
		{
			scanf("%d",&b);
			result+=b;
		}
		if(result >= 81 && result <=180)
		{
			printf("GOOD\n");
		}
		else
		{
			printf("NOT GOOD\n");
		}
	}
	return 0;
}
