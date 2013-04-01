#include<SDL.h>
#include<time.h>
#include<stdlib.h>
//#define EQ1     a=(a+b)/(c-b);                                              
//#define EQ2     b=(a-b)/(c+b);                                               
//#define EQ3     c=(b-a)/(c-b);  
#define EQ1     a=(b-c)/(b+a);                                              
#define EQ2     b=(a+c)/(b-c);                                               
#define EQ3     c=(b+a)/(a+c);  

int main(int argc,char*argv[])
{ 	int		row,cyc,cycC,iterc,f1,f2,
	                hei,wid,xmp,ymp,msx,msy;
	Uint8		*p,iter,mouse,tmpmouse;
	double          a,b,c,
			x_p,y_p,
			x_max=10,y_max=10,
			x_min=-10,y_min=-10,
			x_factor,y_factor,
			bri=10,gf=4,c_m=10;
	SDL_Surface    *scr;
	SDL_Event	event;
	char		flag=1;
	struct timespec	time;

	time.tv_sec=0;
	time.tv_nsec=1000000;

	row 	=hei=atoi(*++argv);
	wid 	=atoi(*++argv);
	cycC 	=atoi(*++argv);
	scr 	=SDL_SetVideoMode(hei,wid,24,0);
	SDL_Init(SDL_INIT_VIDEO);
while(1)
{ 	iter=10;
	x_p=hei/(x_max-x_min);
	y_p=wid/(y_max-y_min);
	x_factor=(x_max-x_min)/2;
	y_factor=(y_max-y_min)/2;
	xmp=x_max*x_p;
	ymp=y_max*y_p;

	while(iter--)
	{ 	a=c=1;
		b=iter<<3;
		cyc=cycC;
		iterc=iter/gf;
		while(cyc--){
			EQ1 EQ2 EQ3
			if(a<x_max&&a>x_min&&b<y_max&&b>y_min)
			{ 	f1=ymp-b*y_p;
				f2=xmp-a*x_p;
				p=(Uint8*)scr->pixels+f1*scr->pitch+f2*3;
				if(p[2]<230)
				{	p[2]+=bri;
					p[1]=iterc;
					if(p[0]<230)
						p[0]+=c*c_m;
				}
			}
		}
	}
	SDL_UpdateRect(scr,0,0,scr->w,scr->h);
	flag=1;
	mouse=0;
	while(flag)
	{ 	while(SDL_PollEvent(&event));
		nanosleep(&time,0x0);
		switch(event.type)
		{ 	case SDL_KEYDOWN:
				flag=0;
				switch(event.key.keysym.sym)
				{	case SDLK_SPACE:SDL_Quit();return 0;break;
					case SDLK_j:bri*=1.25;break;
					case SDLK_k:bri/=1.25;break;
					case SDLK_h:c_m*=2;break;
					case SDLK_l:c_m/=2;break;
					case SDLK_o:gf*=1.5;break;
					case SDLK_n:gf/=1.5;break;
					default:flag=1;
				}
				break;	
			case SDL_MOUSEBUTTONDOWN:
				tmpmouse=SDL_GetMouseState(&msx,&msy);
				if(tmpmouse)mouse=tmpmouse;
				break;
			case SDL_MOUSEBUTTONUP:
				if(mouse>0)
				{	if(mouse==2)
					{	x_factor*=2;	y_factor*=2;
						cycC/=2;
						bri/=2;
					}else
					if(mouse==4)
					{	x_factor/=2;	y_factor/=2;
						cycC*=2;
						bri*=2;
					}
					x_min+=(x_max-x_min)*((double)(hei-msx)/(double)hei)-x_factor;
					y_min+=(y_max-y_min)*((double)(wid-msy)/(double)wid)-y_factor;
					x_max=x_min+x_factor*2;y_max=y_min+y_factor*2;
					flag=0;
				}
		}
	}
	SDL_FillRect(scr,0x0,0x0);
	}
}
