#include<ppm.h>
#include<pgm.h>
#include<stdio.h>

#define HEIGHT	400	
#define WIDTH	400	
#define MAX	255	
void main()
{ 	pixel line[HEIGHT][WIDTH];
	int r=3,g,b,col,row;
	ppm_writeppminit(stdout,
			 HEIGHT,
			 WIDTH,
			 MAX,
			 0);
	for(row=0;row<HEIGHT;row++)
	{	for(col=0;col<WIDTH;col++)
		{	line[row][col].r=0;
			line[row][col].g=0;
			line[row][col].b=0;
		}
	}

	for(g=0;g<255;g++)
	{	for(b=0;b<255;b++)
		{	line[g][b].r=r;
			line[g][b].g=g;
			line[g][b].b=b;
		}
	}

	for(col=0;col<HEIGHT;col++)
	{	ppm_writeppmrow(stdout,
				line[col],
				WIDTH,
				MAX,
				0);
	}	
}
