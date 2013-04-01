#include<SDL.h>
#include<time.h>
#include<stdlib.h>

#define HEIGHT 100
#define WIDTH  100
#define CONST	25

typedef struct
{       float   x;
        float   y;
        Uint8   b;
} point;

int main(int argc,char*argv[])
{ 	int		flag=1,f1=0,f2=0,f1b,f2b;
	Uint8		*p;
	SDL_Surface    *scr;
	point	       *points;
        SDL_Event       event;

	double bignum[100];
	int size;
        struct timespec time;

        time.tv_sec=0;
        time.tv_nsec=1000000;


	scr 	=SDL_SetVideoMode(HEIGHT,WIDTH,24,0);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_FillRect(scr,0x0,0xFFFFFF);
	SDL_UpdateRect(scr,0,0,HEIGHT,WIDTH);

        for(count=126765060022822940149670320537;count<1267650600228229401496703205376;count+=100000)
	{	f2=0;
		size=count;
		do
		{	f1=rand()%HEIGHT;
			f2++;
			p=(Uint8*)scr->pixels+f1*scr->pitch+f2*3;	
	                p[0]=p[1]=p[2]=(size%2)*128;

			SDL_UpdateRect(scr,f2,f1,1,1);
	        }	while (size=size>>1);
	}
	while(flag)
	{       while(SDL_PollEvent(&event));
                nanosleep(&time,0x0);
                switch(event.type)
                {       case SDL_KEYDOWN:
                                flag=0;
                                switch(event.key.keysym.sym)
                                {       case SDLK_SPACE:SDL_Quit();return 0;break; 
default:flag=1;
                                }
                                break; 
}
}
        SDL_FillRect(scr,0x0,0x0);

return(0);
}//main
