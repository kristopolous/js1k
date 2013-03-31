#include<ppm.h>
#include<pgm.h>
#include<stdio.h>

#define HEIGHT	417
#define WIDTH	417
#define MAX	255

#define EQ1	a=(b+c)/(a-b);
#define EQ2	b=(a-c)/(b+c);
#define EQ3	c=(a-b)/(a-c);

int main(	int argc, 
		char *argv[])

{ 	pixel	line[HEIGHT][WIDTH];

	int 	x_origin=WIDTH/2,
		y_origin=HEIGHT/2,
		col,
		row,
		cycles,
		x_max,
		y_max,
		c_max,
		x_prop,
		y_prop,

		xplot,
		yplot,
		cplot,

		cyclesconst,
		iter,

		bright,
		delta;

	double 	a, 
		b, 
		c;

		if(argc!=7)
			return(printf("cycles x_range y_range c_range brightness delta\n"));

		cycles=atoi(*++argv),
		cyclesconst=cycles;
		x_max=atoi(*++argv);
		y_max=atoi(*++argv);
		c_max=atoi(*++argv);
		bright=atoi(*++argv);
		delta=atoi(*++argv);
		x_prop=WIDTH/(x_max*2);
		y_prop=HEIGHT/(y_max*2);

		fprintf(stderr,"cycles: %d\nx_max: %d\ny_max: %d\nbright: %d\ndelta: %d\n",
			cycles,x_max,y_max,bright,delta);
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
	for(iter=0;iter<MAX;iter++)
	{	fprintf(stderr,".");
		a=1;
		b=1+(iter/delta);
		c=1;
		cycles=cyclesconst;
		while(cycles--)
		{	EQ1	
			EQ2	
			EQ3	
			if(a<x_max&&a>(-x_max))
			{	if(b<y_max&&b>(-y_max))
				{	xplot=(int)((x_max-a)*x_prop);
					yplot=(int)((y_max-b)*y_prop);	
					cplot=(int)((c_max-c)*MAX);
					if(line[xplot][yplot].r<(MAX-bright))
					{	line[xplot][yplot].r+=bright;
						line[xplot][yplot].g=iter;
						line[xplot][yplot].b=cplot;
					}
				}
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
	return(0);
}
