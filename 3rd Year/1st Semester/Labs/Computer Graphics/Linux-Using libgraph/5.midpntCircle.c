#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

void mpCircle(int xc, int yc, int r)
{
    int x, y, d;
    refEllipse(xc, yc, r, r); //reference
    x=0; //start at (r,0)
    y=r;
    d=1-r; //initial error
    fillPixel(xc, yc+r); //plot starting points
    fillPixel(xc, yc-r);
    fillPixel(xc-r, yc);
    fillPixel(xc+r, yc);
    while(x<y) //rasterise 2nd octant
    {
	    if(d>=0) d-=((--y)<<1); //update error diagonal move
	    ++x; //rasterise clockwise
	    d+=(x<<1)+1; //update error horizontal move
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
	int gd=DETECT,gm;
	if(argc<4)
	{
	    printf("[ ERROR ] Usage : x_center y_center radius\n");
	    return 1;
	}
	xc=atoi(argv[1]); //get arguments
	yc=atoi(argv[2]);
	r=atoi(argv[3]);
	initgraph(&gd, &gm, NULL); //initialize graphics
	grid();
	mpCircle(xc, yc, r); //call algorithm
	getchar();
	closegraph();
	return 0;
}
