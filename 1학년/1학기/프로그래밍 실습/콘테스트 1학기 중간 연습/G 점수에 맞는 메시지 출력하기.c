#include <stdio.h>
int main ()
{
	int x;
	int a;
	scanf("%d",&x);
	while(x--)
	{
		scanf("%d",&a);
		if(a==100)
		{
			printf("You are perfect!\n");
		}
		else if(80 <=a)
		{
			printf("You are excellent.\n");
		}
		else if(60 <=a)
		{
			printf("You did a good job.\n");	
		}
		else if(0< a)
		{
			printf("You have to study hard.\n");	
		}
		else if(a == 0)
		{
			printf("No score.\n");
		}
	}
	return 0;
}

