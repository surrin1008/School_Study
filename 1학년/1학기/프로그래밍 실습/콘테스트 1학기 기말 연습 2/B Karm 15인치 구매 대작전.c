#include <stdio.h>
int main ()
{
	int TC;
	scanf("%d",&TC);
	for(int i=0;i<TC;i++)
	{
		int a;
		int pday=0;
		int jday=0;
		int money=0;
		int cnt=1;
		
		scanf("%d",&a);
		
		while(1)
		{
			if(money >= a)
			{
				printf("%d\n",pday+jday);
				break;
			}
			if(cnt<=5)
			{
				pday++;
				for(int i=0;i<5;i++)
				{
					money += 8000;
				}
				cnt++;
			}
			else 
			{
				if(cnt<=7)
				{
					jday++;
					for(int i=0;i<8;i++)
					{
						money+=10000;
					}
					cnt++;
				}
				else
				{
					cnt = 1;
				}
			}
		}
	}
}
