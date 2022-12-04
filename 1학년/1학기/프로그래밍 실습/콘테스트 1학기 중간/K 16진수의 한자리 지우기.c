#include <stdio.h>
int main ()
{
	int TC;
	unsigned short a;
	int b;
	int cnt;
	scanf("%d",&TC);
	
	while(TC--)
	{
		scanf("%hx %d",&a,&cnt);
		
		if(cnt == 1)
		{
			b = 4095;	
		}
		if(cnt == 2)
		{
			b = 61695;	
		}
		if(cnt == 3)
		{
			b = 65295;	
		}
		if(cnt == 4)
		{
			b = 65520;	
		}
		printf("%04hx\n",a & b);
	}
	return 0;
}
