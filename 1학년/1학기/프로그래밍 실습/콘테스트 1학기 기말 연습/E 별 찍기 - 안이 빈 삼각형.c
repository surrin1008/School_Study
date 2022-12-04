#include <stdio.h>
int main ()
{
	int TC,x;
	scanf("%d",&TC);
	while(TC--)
	{
		scanf("%d",&x);
		printf("*\n");
		if(x!=1)
		{
			for(int i=0;i<x-2;i++)
			{
			printf("*");
				for(int n=0;n<i;n++)
				{
					printf(" ");
				}
			printf("*\n");
			}
			for(int k=1;k<=x;k++)
			{
			printf("*");
			}
			printf("\n");
		 } 
		
	}
}
