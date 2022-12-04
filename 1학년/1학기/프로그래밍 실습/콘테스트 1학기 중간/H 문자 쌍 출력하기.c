#include <stdio.h>
int main ()
{
	int x;
	int a,b;
	scanf("%d",&x);
	for(int i=1;i<=x;i++)
	{
		scanf("%d %d",&a,&b);
		if(((a>='a'&&a<='z')||(a>='A'&&a<='Z'))&&((b>='a'&&b<='z')||(b>='A'&&b<='Z')))
		{
			if(a>='A'&&a<='Z'&&b>='A'&&b<='Z')
			{
			printf("%c%c\n",a+32,b+32);
			}
			else if(a>='a'&&a<='z'&&b>='a'&&b<='z')
			{
			printf("%c%c\n",a-32,b-32);	
			}
			else
			{
			printf("%c%c\n",a,b);	
			}	
		}
		else
		{
			printf("No Alphabet!\n");
		}
		
	} 
	return 0; 
}
