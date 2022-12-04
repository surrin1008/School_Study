#include <stdio.h>
int main ()
{
	long long x;
	scanf("%ld",&x);
			if(x%2==0 && x%7==0 || x%3 == 0 )
		{
			printf("Magic");
		}
		else
		{
			printf("No Magic");
		}
	
	return 0;
}
