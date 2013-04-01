#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include"/usr/include/pthread.h"

typedef struct _pixel
{       unsigned int r;
        unsigned char g;
        unsigned char b;
} pixel;
pixel uint_pixel(Uint32 in)
{       pixel temp;
        temp.r=in>>16;
        temp.g=in>>8;
        temp.b=in;
        return temp;
}
int main()
{	Uint32 abc;
	pixel	test;
	abc=0x30ffd0;
	test=uint_pixel(abc);
	printf("%x %x %x",abc<<6,0,0);
}	
