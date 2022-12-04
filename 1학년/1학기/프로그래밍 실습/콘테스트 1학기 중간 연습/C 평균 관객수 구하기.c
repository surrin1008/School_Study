#include <stdio.h>
int main ()
{
	int a;
	int n = 0;
	for(int i=1;i<=7;i++)
	{
		scanf("%d",&a);
		n += a;
	}
	printf("%d",n/7);
	return 0;
}
