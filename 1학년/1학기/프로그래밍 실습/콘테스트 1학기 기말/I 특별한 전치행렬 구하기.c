#include <stdio.h>
int main ()
{
	int TC;
	scanf("%d",&TC);
	while(TC--)
	{
		int a,b;
		
		scanf("%d %d",&a,&b);
		int arr[10][10]={0};
		for(int i=0;i<a;i++)
		{
			for(int n=0;n<b;n++)
			{
				scanf("%d",&arr[i][n]);
			}
		}
		if(a-b==0)
		{
			for(int i=0;i<a;i++)
			{
				for(int n=0;n<b;n++)
				{
					printf("%d ",arr[i][n]);
				}
				printf("\n");
			}	
		}
		else
		{
			for(int i=0;i<b;i++)
			{
				for(int n=0;n<a;n++)
				{
					printf("%d ",arr[n][i]);
				}
				printf("\n");
			}
		}
	}
}
