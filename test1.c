#include <stdio.h>
int main(int argc, char *argv[])
{	double a=2,b=2.1,c=2;
	while(1)
	{	printf("%.19f %.19f %.19f \n",a,b,c);
		c=(a+b)/(a-b);
		b=(a-b)/(b-c);
		a=(b-c)/(a+b);
	}
return (0);
}
