#include <stdio.h>
int main ()
{
	int a;
	while(1)
	{
		int arr[50] ={0};
		int max=0,min=1001;
		scanf("%d",&a);
		if(a==0)
		{
			break;
		}
		for(int i=0;i<a;i++)
		{
			scanf("%d",&arr[i]);
			if(max < arr[i])
				max= arr[i];
			if(min > arr[i])
				min= arr[i];
		}
		printf("%d %d\n",max,min);
	}
}
