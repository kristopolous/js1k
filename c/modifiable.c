#include<SDL.h>
#include<time.h>
#include<stdlib.h>
/*#define EQ1     a=(a+c)/(a-b);
  #define EQ2     b=(a-c)/(b-c);
  #define EQ3     c=(b-a)/(c-b);
 *
  #define EQ1     a=(a+c)/(a-b);
  #define EQ2     b=(a+b)/(b-c);
  #define EQ3     c=(b+c)/(a-c);
 *
  #define EQ1     a=(a-c)/(a+b);
  #define EQ2     b=(a-c)/(b+c);
  #define EQ3     c=(b-c)/(a+c);
 *
  #define EQ1     a=(a+b+4+c)/(a+b-2*c);
  #define EQ2     b=(2*a-b+c)/(a-b-c);
  #define EQ3     c=(-a+b+c)/(3-a+b-c);
 *
  #define EQ1     a=(a+b+c)/(a+b-c+2);
  #define EQ2     b=(a-b+c-2)/(a-b-c+1);
  #define EQ3     c=(-a+b+c-1)/(a+b-c+2);
 *
 * Spiral
  #define EQ1     a=(a-c)/(a+b);
  #define EQ2     b=(a-b)/(b+c);
  #define EQ3     c=(b-c)/(a+c); 
 *
  #define EQ1     a=(a+b+c)/(a+b-c);
  #define EQ2     b=(a+b+c)/(a+b-c);
  #define EQ3     c=(a+b+c)/(a+b-c);
 *
  #define EQ1     a=(a-c)/(a+b-c);
  #define EQ2     b=(a-c)/(b-c);
  #define EQ3     c=(a-c)/(a+b-c);
 *  
  #define EQ1     a=(a-c)/(a-b+c);
  #define EQ2     b=(a-c)/(b-c);
  #define EQ3     c=(a-c)/(a+b-c);
 *Has Spiral VV
  #define EQ1     a=(a-c)/(a+b+c);
  #define EQ2     b=(a-c)/(b-c);
  #define EQ3     c=(a-c)/(a-b+c);
 *Increadible variation of above 
  #define EQ1     a=(a-c)/(a+b+c);
  #define EQ2     b=(a+c)/(b-c);
  #define EQ3     c=(a-c)/(a-b+c);
 */
  #define EQ1     a=(a-c)/(a+b+c);
  #define EQ2     b=(a+c)/(b+c);
  #define EQ3     c=(a-c)/(a-b+c);
 
typedef struct
{	float	x;
	float	y;
	Uint8	b;
} point;

int sort(void const*a,void const*b)
{	return(((((point*)a)->x)*256)-((((point*)b)->x)*256));
}

int main(int argc,char*argv[])
{ 	int		row,cyc,cycC,f1,f2,
	                hei,wid,xmp,ymp,msx,msy,cur=0,total;
	Uint8		*p,iter,mouse,tmpmouse;
	double          a,b,c,
			x_p,y_p,
			x_max=10,y_max=10,
			x_min=-10,y_min=-10,
			x_factor,y_factor,
			bri=3,gf=20,c_m=10;
	SDL_Surface    *scr;
	SDL_Event	event;
	char		flag=1;
	struct timespec	time;
	point	       *points;

	time.tv_sec=0;
	time.tv_nsec=1000000;

	row 	=hei=atoi(*++argv);
	wid 	=atoi(*++argv);
	cycC 	=atoi(*++argv);
	iter=255;
	points  =(point*)malloc(sizeof(point)*cycC*iter);
		
	scr 	=SDL_SetVideoMode(hei,wid,24,0);
	SDL_Init(SDL_INIT_VIDEO);
	fprintf(stderr,"Generating");
	while(iter--)
	{ 	fprintf(stderr,".");
		a=c=1;
		b=iter<<3;
		cyc=cycC;
		while(cyc--){
			EQ1 EQ2 EQ3
			points[++cur].x=a;
			points[cur].y=b;	
			points[cur].b=c;
		}
	}
	qsort(&points[1],(int)(0.75*cur),sizeof(point),sort);
	fprintf(stderr,"Sorting Done\n");
	total=cur;	
while(1)
{ 	x_p=hei/(x_max-x_min);
	y_p=wid/(y_max-y_min);
	x_factor=(x_max-x_min)/2;
	y_factor=(y_max-y_min)/2;
	xmp=x_max*x_p;
	ymp=y_max*y_p;
	cur=1;
	points[total+1].x=x_max+1;
	while(points[++cur].x<x_max)
	{	while(points[++cur].x<=x_min);
		if(points[cur].y>y_min&&points[cur].y<y_max)
		{	f1=ymp-points[cur].y*y_p;
                        f2=xmp-points[cur].x*x_p;
			p=(Uint8*)scr->pixels+f1*scr->pitch+f2*3;	
			if(p[2]==0){p[2]=96;}
			if(p[2]>230)p[2]=255;
			else 	p[2]+=bri;
				p[1]=gf;
			if(p[0]>230)p[0]=255;
			else	p[0]+=points[cur].b*c_m;
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
					case SDLK_j:bri+=2;break;
					case SDLK_k:bri-=2;break;
					case SDLK_h:c_m+=2;break;
					case SDLK_l:c_m-=2;break;
					case SDLK_o:gf-=5;break;
					case SDLK_n:gf+=5;break;
					default:flag=1;
				}
				break;	
			case SDL_MOUSEBUTTONDOWN:
				tmpmouse=SDL_GetMouseState(&msx,&msy);
				if(tmpmouse)mouse=tmpmouse;
				break;
			case SDL_MOUSEBUTTONUP:
				if(mouse>0)
				{	if(mouse==2)     {x_factor*=2;	y_factor*=2;}
					else if(mouse==4){x_factor/=2;	y_factor/=2;}
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
