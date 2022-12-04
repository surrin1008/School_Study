#include <stdio.h>
int main ()
{
	int x,a,b;
	scanf("%d",&x);
	while(x--)
	{
		scanf("%d %d",&a,&b);
		if(a==1&&b==1)
		{
			printf("@\n");
		}
		else if(a==1)
		{
		for(int i=0;i<a;i++)
		{
			printf("@\n");
			for(int n=0;n<b-2;n++)
			{
				printf("*\n");
			}
			printf("@\n");
		}
		
		}
		else if(b==1)
		{
			for(int n=1;n<=b;n++)
			{
				printf("@");
				for(int i=1;i<=a-2;i++)
				{
					printf("*");
				}
				printf("@");
			printf("\n");
			}
		}
		else
		{
			printf("@");
			for(int k=1;k<=a-2;k++)
			{
				printf("*");
			}
			printf("@");
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
			printf("@");
			for(int k=1;k<=a-2;k++)
			{
				printf("*");
			}
			printf("@");
			printf("\n");
		}
	}
	return 0;
}
