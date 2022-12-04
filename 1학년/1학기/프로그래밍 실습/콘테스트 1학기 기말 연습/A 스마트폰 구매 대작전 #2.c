#include <stdio.h>
int main ()
{
	int x,a;
	scanf("%d",&x);
	for(int i=1;i<=x;i++)
	{
		scanf("%d",&a);
		if(a%57000>0)
		printf("%d",a/57000+1);
		else
		printf("%d",a/57000);
	}
}
