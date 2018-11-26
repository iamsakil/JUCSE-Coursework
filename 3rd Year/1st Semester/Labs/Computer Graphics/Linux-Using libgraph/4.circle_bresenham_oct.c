#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

void bresenhamCircle(int xc, int yc, int r)
{
    int x, y, d, D;
    refEllipse(xc, yc, r, r); //reference
    x=0; //start at (0,r)
    y=r;
    D=2-r; //initial error
    fillPixel(xc, yc+r); //plot starting points
    fillPixel(xc, yc-r);
    fillPixel(xc-r, yc);
    fillPixel(xc+r, yc);
    while(y>x) //rasterise 2nd octant clockwise
    {
		if(D>0) D-=((--y)<<1); //diagonal move
	    D+=((++x)<<1)+1; //horizontal move
        fillPixel(xc+x, yc+y); //plot symmetric points
        fillPixel(xc+x, yc-y);        
        fillPixel(xc-x, yc+y);
        fillPixel(xc-x, yc-y);
        fillPixel(xc+y, yc+x);
        fillPixel(xc+y, yc-x);
        fillPixel(xc-y, yc+x);
        fillPixel(xc-y, yc-x);
    }
}
    
int main(int argc, char** argv)
{
	int xc,yc,r;
	if(argc<4)
	{
	    printf("[ ERROR ] Usage : x_center y_center radius\n");
	    return 1;
	}
	xc=atoi(argv[1]); //get arguments
	yc=atoi(argv[2]);
	r=atoi(argv[3]);
	int gd=DETECT,gm; //initialize graphics
	initgraph(&gd, &gm, NULL);
	grid();
	bresenhamCircle(xc, yc, r); //call algorithm
	getchar();
	closegraph();
	return 0;
}
