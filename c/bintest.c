#include<stdio.h>
int main(void)
{    	int count,size,direction,to;
	for(count=0;count<1000;++count)
	{	size=count;
		printf("\n%.3d: ",count);
		do
    			printf("%d",size%2);
		while (size=size>>1);

		if(count%2)to=count-2;
		else to=(count>>1);
	}
}
