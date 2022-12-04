#include <stdio.h>
#include <math.h>
int main ()
{
	int TC;
	int a,b,c;
	int x;
	scanf("%d",&TC);
	while(TC--)
	{
		scanf("%d %d %d",&a,&b,&c);
		x= (b*b)-(4*a*c);
		if(a==0)
		{
			printf("No quadratic\n");
		}
		else
		{
			if(x>0)
			{
				if((float)(-1*b+sqrt(x))/(2*a)>(float)(-1*b-sqrt(x))/(2*a))
				printf("%.3f %.3f\n",(float)(-1*b+sqrt(x))/(2*a),(float)(-1*b-sqrt(x))/(2*a));
				else
				printf("%.3f %.3f\n",(float)(-1*b-sqrt(x))/(2*a),(float)(-1*b+sqrt(x))/(2*a));
			}
			else if(x==0)
			{
				printf("%.3f\n",(float)(-1*b)/(2*a));
			}
			else if(x<0)
			{
				printf("Imaginary\n");
			}	
		} 
	}
	return 0;
}
