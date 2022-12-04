#include <stdio.h>
int main ()
{
	int x;
	char word;
	scanf("%d",&x);
	
	while(x--)
	{
		scanf(" %c",&word);
		
		if(word >= 'A' && word <='Z')
		{
		printf("%c\n",word+32);	
		}
		else if(word >='a' && word <='z')
		{
		printf("%c\n",word-32);	
		}
	}	
		
	
	return 0;
}

