#include<stdlib.h>
#include<stdio.h>
#include<ppm.h>
#include<pgm.h>
/*
#define EQ1	a=(b+c)/(b-a);
#define EQ2	b=(a+c)/(c-b);
#define EQ3	c=(a+b)/(b-c);
  #define EQ1     a=(b-c)/(a+c);
  #define EQ2     b=(a+c)/(a-c);
  #define EQ3     c=(a-c)/(a+c);
*/
  #define EQ1     a=(a-c)/(a*mul-b);
  #define EQ2     b=(a-c)/(b-c);
  #define EQ3     c=(a-b)/(b+c);
/*
#define EQ1     a=(b-c)/(b+a);
#define EQ2     b=(a+c)/(b-c);
#define EQ3     c=(b+a)/(a+c);
*/

//#define EQ1	a=(b+c)/(b-a);
//#define EQ1	a+=a/b;
//#define EQ2	b-=a/b;
//#define EQ3	c=a+b;
//#define EQ2	b=(a-c)/(b+a);
//#define EQ3	c=(a+b)/(b-c);

int main(int argc,char*argv[])
{ 	pixel	**line;
	int 	col,row,cyc,
		c_m,
		xp,yp,cp,
		xmp,ymp,
		cycC,iter=255,
		hei,wid,bri;
	double 	a,b,c,
    mul,
		x_p,y_p,
		x_max,y_max,
		x_min,y_min;

	if(argc!=11)
	{       fprintf(stderr,"use 7 args; Generating default\n");
		ppm_writeppminit(stdout,256,256,255,0);
        	for(col=0;col<65536;col++)
               	printf("%c%c%c",col>>8,col>>4,col<<4); 
		return(0);
	}
//Width of image
	wid=atoi(*++argv);
//Height of image
	row=
	 hei=atoi(*++argv);	
        line=(pixel**)malloc(sizeof(pixel)*hei);
//Number of cycles
	cycC=cyc=atoi(*++argv),
	x_min=strtod(*++argv,(char**)NULL);
	y_min=strtod(*++argv,(char**)NULL);
	x_max=strtod(*++argv,(char**)NULL);
	y_max=strtod(*++argv,(char**)NULL);
	c_m=atoi(*++argv);
	bri=atoi(*++argv);
	mul=strtod(*++argv,(char**)NULL);

	x_p=hei/(x_max-x_min);
	y_p=wid/(y_max-y_min);
	xmp=x_max*x_p;
	ymp=y_max*y_p;

	fprintf(stderr,"%dx%d(%d)[%.2f:%.2f::%.2f:%.2f]{%d,%d}",wid,hei,cyc,x_min,y_min,x_max,y_max,c_m,bri);
	while(row--)
	{	do
		{	line[row]=(pixel*)malloc(sizeof(pixel)*wid);
		}while(!line[row]);
		for(col=0;col<wid;col++)
			line[row][col].r=line[row][col].g=line[row][col].b=0;
	}
	while(iter--)
	{	fprintf(stderr,".");
		a=c=iter;
		b=-iter;
		cyc=cycC;
		while(cyc--)
		{	EQ1	EQ2	EQ3	
			if(a<x_max&&a>x_min&&b<y_max&&b>y_min)
			{	xp=xmp-a*x_p;
				yp=ymp-b*y_p;	
				cp=c*c_m;
				if(line[xp][yp].r<230)
				{	line[xp][yp].r+=bri;
					line[xp][yp].g=iter;
					if(line[xp][yp].b<230)
						line[xp][yp].b+=cp;
				}	
			}
		}
	}
	ppm_writeppminit(stdout,wid,hei,255,0);
	for(col=0;col<hei;col++)
		ppm_writeppmrow(stdout,line[col],wid,255,0);
	return(fprintf(stderr,"\n"));
}
