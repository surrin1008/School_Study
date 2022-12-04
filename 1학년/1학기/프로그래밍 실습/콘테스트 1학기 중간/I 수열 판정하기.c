#include <stdio.h>
int main ()
{
	int x;
	int a,b,c,d;
	int n;
	scanf("%d",&x);
	for(int i=1;i<=x;i++)
	{
		scanf("%d %d %d %d",&a,&b,&c,&d);
		
		n= b-a;
		if((b-a)==(c-b)&&(b-a)==(d-c))
		{
			printf("AS\n");
		}
		else if((b/a)==(c/b)&&(b/a)==(d/c))
		{
			printf("GS\n");
		}
		else if((a+n==b) && (b+n+1==c) && (c+n+2==d))
		{
			printf("OS\n");
		}
		else 
		{
			printf("Others\n");
		}
	} 
	return 0; 
}
/*
1 1 =2
1 1 2 =4
1 1 2 3 =7
1 1 2 3 4 =11
*/
