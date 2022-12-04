#include <stdio.h>
int main ()
{
	int count = 1;
	int TC;
	scanf("%d",&TC);
	while(TC--)
	{
			int x;
			scanf("%d",&x);
			int y=x;
			count =1;
			int z=1;
			for(int i=1;i<=x;i++)
		{
			
			for(int n=1;n<y;n++)
			{
				printf(" ");
			}
			y--;
			for(int j=1;j<=z;j++)
			{
				printf("%d",count);
				
			}
			z+=2;
			printf("\n");
			count++;
		}
	}
	
	return 0;
}
