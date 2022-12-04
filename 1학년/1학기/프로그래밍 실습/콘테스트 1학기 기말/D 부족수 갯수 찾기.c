#include <stdio.h>
#include <math.h>
int is(int n)
{
	int sum = 0;
	for(int i=1;i<n;i++)
	{
		if((n%i)==0)
		{
			sum += i;
		}
	}
	if(sum < n)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
int main ()
{
	int TC;
	int a,b;
	scanf("%d",&TC);
	while(TC--)
	{
	int cnt =0;
	scanf("%d %d",&a,&b);
			for(int i=a;i<=b;++i)
			{
				if(is(i)==1)
				++cnt;
			}
		printf("%d\n",cnt);
	}
	return 0;
}
