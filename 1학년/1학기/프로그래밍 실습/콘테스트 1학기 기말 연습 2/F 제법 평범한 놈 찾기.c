#include <stdio.h>
#include <math.h>
int main ()
{
	int TC;		//TCÀÔ·Â  
	scanf("%d",&TC);
	while(TC--)
	{
		int arr[20]={0};
		int max=0, min=1000,sum=0,c=0;
		int n;
		float av;
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&arr[i]);
			if(max < arr[i])
				max = arr[i];
			if(min > arr[i])
				min = arr[i];
			sum += arr[i];
		}
		sum -= min+max;
		av=sum/(float)(n-2);
		float temp = 1000;
		for(int i=0;i<n;i++)
		{
			if(fabs(av - arr[i])<temp)
			{
				temp = fabs(av - arr[i]);
				c=i;
			}
		}
		printf("%d\n",arr[c]);
	}
}
