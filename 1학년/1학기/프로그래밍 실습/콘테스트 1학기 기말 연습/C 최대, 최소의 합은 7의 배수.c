#include<stdio.h>
int main()
{
	int TC,x,a,min=0,max=0;
	scanf("%d",&TC);
	while(TC--)
	{
	scanf("%d",&x);
	min=0;
	max=0;
		while(x--)
		{
			scanf("%d",&a);
			
			if(min == 0)
			{
			min = a;	
			}		
			else if(min>a)
			{
				min = a;
			}
			
			if(max == 0)
			{
			max = a;	
			}		
			else if(max<a)
			{
				max = a;
			}
		}	
		if(min<0 || max<0)
		{
			printf("HMM!\n");
		}
		else 
		{
			if(min+max==0)
			{
				printf("ZERO\n");
			}
			else if((min+max)%7==0)
			{
				printf("YES\n");
			}
			else 
			{
				printf("NO\n");
			}	
		}
		
	}
	return 0;
}

