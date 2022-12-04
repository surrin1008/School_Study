#include <stdio.h>
int main ()
{
	int TC;
	int n,m;
	int i,k,j;
	int temp;
	int arr[10][10];
	int result[21];
	int cnt;
	
	scanf("%d",&TC);
	while(TC--)
	{
		scanf("%d %d",&n,&m);
		
		for(i=0;i<10;i++)
		{
			for(k=0;k<10;k++)
			{
				arr[i][k] = 0;
			}
		}
			
		for(i=0;i<n;i++)
		{
			for(k=0;k<m;k++)
			{
				scanf("%d",&arr[i][k]);
			}	
		}
		
		for(i=0;i<21;i++)
		{
			result[i] = 0;
		}
		for (j = 0; j < n; j++) 
		{
	        for (i = 0; i < m; i++) 
			{
	            for (k = 0; k < m - 1 - i; k++)
	            {
	                if (arr[j][k] < arr[j][k + 1]) 
					{
	                    temp = arr[j][k];
	                    arr[j][k] = arr[j][k + 1];
	                    arr[j][k + 1] = temp;
	                }
	            }
	        }
    	}
    
    cnt = 0;
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < m; k++)
        {
            if (k == 0 || k == m - 1) {
                result[cnt] = arr[i][k];
                cnt++;
            }
        }
    }
		
		for (i = 0; i < n*2; i++)
    	{
	        for (k = 0; k < n * 2 - 1 - i; k++)
	        {
	            if (result[k] < result[k + 1]) {
	                temp = result[k];
	                result[k] = result[k + 1];
	                result[k + 1] = temp;
	            }
	        }
	    }
		
		for(i=0;i<n*2;i++)
		{
			printf("%d ",result[i]);
		}
		printf("\n");
	}
	
	return 0;
}
