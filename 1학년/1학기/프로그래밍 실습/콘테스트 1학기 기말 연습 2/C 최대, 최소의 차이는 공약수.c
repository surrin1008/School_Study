#include <stdio.h>
int main ()
{
	int TC;
	scanf("%d",&TC);
	while(TC--)
	{
		int arr[50] ={0};
		int m;
		int max=0,min=1000;
		int mn;
		scanf("%d",&m);
		for(int i=0;i<m;i++)
		{
			scanf("%d",&arr[i]);
			if(max < arr[i])
				max= arr[i];
			if(min > arr[i])
				min= arr[i];
		
		}
		mn=max-min;
		if(mn!=0&&(max%mn==0&&min%mn==0))
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
