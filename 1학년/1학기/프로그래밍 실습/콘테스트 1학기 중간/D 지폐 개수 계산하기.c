#include <stdio.h>
int main ()
{
	int a;
	scanf("%d",&a);
	printf("%d %d %d %d",a/50000,a%50000/10000,a%50000%10000/5000,a%50000%10000%5000/1000);
	return 0;
}
