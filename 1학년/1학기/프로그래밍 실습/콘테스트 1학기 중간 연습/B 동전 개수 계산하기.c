#include <stdio.h>
int main ()
{
	int a;
	scanf("%d",&a);
	printf("500:%d 100:%d 50:%d",a/500,a%500/100,a%500%100/50);
	return 0;
}
