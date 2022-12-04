#include <stdio.h>
#include <math.h>
int main ()
{
	int TC;
	int a;
	double root3;
	root3 = sqrt(3.0);
	scanf("%d",&TC);
	while(TC--)
	{
		scanf("%d",&a);
		printf("%.5f\n",(double)(a*a*root3)/4);
	}
	return 0;
}
