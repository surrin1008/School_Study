#include <stdio.h>
int main ()
{
	int x,a,b;
	char n;
	scanf("%d",&x);
	for(int i=1;i<=x;i++)
	{
	scanf("%d  %c %d",&a,&n,&b);
		if(n=='+')
		{
			printf("%d\n",a+b);
		}
		else if(n=='-')
		{
			printf("%d\n",a-b);
		}
		else if(n=='x')
		{
			printf("%d\n",a*b);
		}
		else if(n=='/')
		{
			if(a!=0)
			printf("%.5f\n",(float)a/b);
			else
			printf("Mission Impossible\n");
		}
		else if(n=='%')
		{
			printf("%d\n",a%b);
		}
	} 
	
	return 0; 
}

