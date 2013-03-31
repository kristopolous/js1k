#include<ppm.h>
#include<pgm.h>
#include<stdio.h>

#define HEIGHT	400	
#define WIDTH	400	
#define MAX	255	

void main(	int argc, 
		char *argv[])

{ 	pixel 	line[HEIGHT][WIDTH];

	int 	x_origin=WIDTH/2,
		y_origin=HEIGHT/2,
		col,
		row,
		cycles,
		x_max,
		y_max,
		x2_max,
		y2_max,
		x_prop,
		y_prop,

		xplot,
		yplot,

		bright;

	double 	a=1, 
		b=2, 
		c=1;

		cycles=atoi(*++argv);
		x_max=atoi(*++argv);
		y_max=atoi(*++argv);
		bright=atoi(*++argv);
		x2_max=x_max*2;
		y2_max=y_max*2;
		x_prop=WIDTH/x2_max;
		y_prop=HEIGHT/y2_max;

	for(	row=0;
		row<HEIGHT;
		row++)

	{	for(	col=0;
			col<WIDTH;
			col++)

		{	line[row][col].r=0;
			line[row][col].g=0;
			line[row][col].b=0;
		}
	}

	while(cycles--)
	{	a=(b+c)/(a-b);
		b=(a-c)/(b+c);
		c=(a-b)/(a-c);
		if(a<x_max&&a>(-x_max))
		{	if(b<y_max&&b>(-y_max))
			{	xplot=(int)((x_max-a)*x_prop);
				yplot=(int)((y_max-b)*y_prop);	
				if(line[xplot][yplot].r<(MAX-bright))
					line[xplot][yplot].r+=bright;
			}
		}
	}

	ppm_writeppminit(	stdout, 
				HEIGHT, 
				WIDTH, 
				MAX, 
				0);

	for(	col=0;
		col<HEIGHT;
		col++)

	{	ppm_writeppmrow(stdout,
				line[col],
				WIDTH,
				MAX,
				0);
	}	
}
