#include <stdio.h>
int main ()
{
	int x;
	int a,b,c;
	scanf("%d",&x);
	while(x--)
	{
	scanf("%2d%2d%4d",&a,&b,&c);
	printf("%02d\n",b);	
	}
	return 0;
}
