#include<stdlib.h>
#include<stdio.h>
#include"/usr/local/include/ppm.h"
#include"/usr/local/include/pgm.h"

#define EQ1	a=(b+c)/(b-a);
#define EQ2	b=(a+c)/(c-b);
#define EQ3	c=(a+b)/(b-c);
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
		x_p,y_p,
		x_m,y_m;

	if(argc!=8)
	{       fprintf(stderr,"use 7 args; Generating default\n");
		ppm_writeppminit(stdout,256,256,255,0);
        	for(col=0;col<65536;col++)
               	printf("%c%c%c",col>>8,col>>4,col<<4); 
		return(0);
	}
	wid=atoi(*++argv);
	row=hei=atoi(*++argv);	
        line=(pixel**)malloc(sizeof(pixel)*hei);
	cycC=cyc=atoi(*++argv),
	x_m=strtol(*++argv,(char**)NULL,10);
	y_m=strtol(*++argv,(char**)NULL,10);
	c_m=atoi(*++argv);
	bri=atoi(*++argv);
	xmp=x_m*(x_p=hei/(x_m*2));
	ymp=y_m*(y_p=wid/(y_m*2));

	fprintf(stderr,"%dx%d(%d)[%.2f:%.2f]{%d,%d}",wid,hei,cyc,x_m,y_m,c_m,bri);
	while(row--)
	{	do
		{	line[row]=(pixel*)malloc(sizeof(pixel)*wid);
		}while(!line[row]);
		for(col=0;col<wid;col++)
			line[row][col].r=line[row][col].g=line[row][col].b=0;
	}
	row=hei/2;
	for(col=0;col<wid;col++)
		line[row][col].g=100;
	row=wid/2;
	for(col=0;col<hei;col++)
		line[col][row].g=100;
	while(iter--)
	{	fprintf(stderr,".");
		a=c=1;
		b=iter<<3;
		cyc=cycC;
		while(cyc--)
		{	EQ1	EQ2	EQ3	
			if(abs(a)<x_m&&abs(b)<y_m)
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
