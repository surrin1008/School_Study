#include <stdio.h>
int main ()
{
	int n;
	
	while(1)
	{
		int m[50];
		float aver =0.0;
		int sum =0;
		int cnt =0;
		scanf("%d",&n);
		if(n==0)
		{
			break;
		}
		for(int i=0;i<n;i++)
		{
			scanf("%d",&m[i]);
			sum += m[i];
		}
		aver = (float)sum/n;
		printf("%d ",(int)aver);
		for(int k=0;k<n;k++)
		{
			if((int)aver>=m[k])
			{
				cnt++;
			}
		}
		printf("%d %d\n",cnt,n-cnt);
	}
}
