#include <stdio.h>

int main(void)
{
	int TC;
	scanf("%d",&TC);
	while(TC--)
	{
    int num;
    int x;
    
    scanf("%d",&num);
	
    for(int i=0; i<num; i++)
    {
    	x=65+num;
    	
        for(int k=i; k<(num-1); k++)
        {
            printf(" ");
        }
        
        
        for(int k=0; k<=(i*2); k++)
        {
        	if(k<=i)
        	{
        		x--;
        		printf("%c",x);
        		
			}
			else
			{
				x++;
				printf("%c",x);
				
			}
			
            
        }
        printf("\n");
    }
    
    for(int i=(num-2); i>=0; i--)
    {
    	x=65+num;
        for(int k=i; k<(num-1); k++)
        {
            printf(" ");
        }
        for(int k=0; k<=(i*2); k++)
        {
        	if(k<i+1)
        	{
        		x--;
        	printf("%c",x);	
			}
			else
			{
				x++;
			printf("%c",x);
			}
            
        }
        printf("\n");

    }
}
    return 0;
}
