#include <stdio.h>
int main ()
{
	int x;
	int a,b,c;
	int result;
	scanf("%d",&x);
	for(int i=1;i<=x;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		result = (b*b)-(4*a*c);
		if(a==0)
		{
			printf("No quadratic\n");
		}
		else
		{
				if(result > 0)
				{
				printf("Real\n");	
				}
				else if(result == 0)
				{
					printf("%.3f\n",(float)-1*b/(2*a));
				}
				else if(result < 0)
				{
					printf("Imaginary\n");
				}
		}
		
	}
	return 0; 
}
