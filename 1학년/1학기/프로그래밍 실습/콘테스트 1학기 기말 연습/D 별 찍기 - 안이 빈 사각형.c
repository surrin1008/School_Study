#include <stdio.h>
int main ()
{
	int x,a,b;
	scanf("%d",&x);
	while(x--)
	{
		scanf("%d %d",&a,&b);
		if(a==1 || b==1)
		{
			for(int n=1;n<=b;n++)
			{
				for(int i=1;i<=a;i++)
				{
					printf("*");
				}
			printf("\n");
			}
		}
		else
		{
			for(int k=1;k<=a;k++)
			{
				printf("*");
			}
			printf("\n");
			for(int l=1;l<=b-2;l++)
			{
				printf("*");
				for(int u=1;u<=a-2;u++)
				{
					printf(" ");
				}
				printf("*\n");
			}
			for(int k=1;k<=a;k++)
			{
				printf("*");
			}
			printf("\n");
		}
	}
	return 0;
}
