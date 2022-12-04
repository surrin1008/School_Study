#include <stdio.h>
int main ()
{
	int TC;
	int a;
	scanf("%d",&TC);
	for(int i=0;i<TC;i++)
	{
		int money =0;
		int cnt=1;
		int day=0;
		scanf("%d",&a);
		while(1)
		{
			if(money>=a)
			{
				printf("%d\n",day);
				break;
			}
			if(cnt==1)
			{
				day++;
				money +=45000;
				cnt++;
			}
			else if(cnt==2)
			{
				day++;
				money +=36000;
				cnt++;
			}
			else if(cnt==3)
			{
				day++;
				money +=54000;
				cnt++;
			}
			else if(cnt==4)
			{
				day++;
				money +=66000;
				cnt++;
			}
			else if(cnt==5)
			{
				day++;
				money +=88000;
				cnt++;
			}
			else
			{
				cnt =1;
			}
		}	
	}		
}
