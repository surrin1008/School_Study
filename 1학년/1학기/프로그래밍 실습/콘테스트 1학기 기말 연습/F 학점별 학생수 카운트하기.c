#include <stdio.h>
int main ()
{
	int TC,x;
	int cou=0;
	int A=0, B=0, C=0, D=0, F=0;
	while(1)
	{
		scanf("%d",&TC);
		A=0, B=0, C=0, D=0, F=0;
		if(TC==0)
		{
			break;
		}
		for(int i=1;i<=TC;i++)
		{
			scanf("%d",&x);
			if(x<=100&&x>=90)
			{
				A++;
			}
			else if(x<=89&&x>=80)
			{
				B++;
			}
			else if(x<=79&&x>=70)
			{
				C++;
			}
			else if(x<=69&&x>=60)
			{
				D++;
			}
			else if(x<=59&&x>=0)
			{
				F++;
			}
		}
		cou++;
		printf("<%d>\n",cou);
			printf("A : %d\n",A);
			printf("B : %d\n",B);
			printf("C : %d\n",C);
			printf("D : %d\n",D);
			printf("F : %d\n\n",F);
	}
}
