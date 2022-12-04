#include <stdio.h>
int main ()
{
	int x; 	
	int a,b,c;
	scanf("%d",&x);
	while(x--)
	{
		scanf("%d %d %d",&a,&b,&c);
		if((a >= 'A' && a <='Z') &&(b >= 'A' && b <='Z')&&(c >= 'A' && c <='Z'))
		{
			printf("%c%c%c\n",a,b,c);
		}
		else
		{
			printf("No Uppercase!\n");
		}
		
	}
	return 0;
}

