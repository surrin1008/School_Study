#include <stdio.h>
int main ()
{
	int a;
	int n=0;
	for(int i=1;i<=5;i++)
	{
		scanf("%d",&a);
		n+=a;
	}
	printf("%.3f",(float)n/5);
	return 0;
}
