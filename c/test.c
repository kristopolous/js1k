#include <stdio.h>
void main()
{	double a=1, b=2, c=1;
	while(1)
	{	printf("%f %f %f\n",a,b,c);
		a=(b+c)/(a-b);
		b=(b+c)/(a-b);
		c=(b+c)/(a-b);
	}
}
