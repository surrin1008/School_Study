#include <stdio.h>
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
	if(sum > n)
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
	int m,n;
	scanf("%d",&TC);
	while(TC--)
	{
		int cnt =0;
		scanf("%d %d",&m,&n);
		if(n<m)
		{
			for(int i=n;i<=m;++i)
			{
				if(is(i)==1)
				++cnt;
			}
		}
		else
		{
			for(int i=m;i<=n;++i)
			{
				if(is(i)==1)
				++cnt;
			}
		}
		printf("%d-%d:%d \n",m,n,cnt);
	}
	return 0;
}
