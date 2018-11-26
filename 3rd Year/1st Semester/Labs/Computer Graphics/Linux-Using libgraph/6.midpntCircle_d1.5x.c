#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

void mpCircle_d1p5x(int xc, int yc, int r)
{
    int x, y, d, dhorz, dvert;
    refEllipse(xc, yc, r, r); //reference
    x=0; //start at (r,0)
    y=r;
    d=1-r; //initial error
    dhorz=1; //initial change in error
    dvert=-(r<<1);
    fillPixel(xc, yc+r); //plot starting points
    fillPixel(xc, yc-r);
    fillPixel(xc-r, yc);
    fillPixel(xc+r, yc);
    while(x<y) //rasterise 2nd octant
    {
        if(d>=0) //diagonal move
        {
	        --y;
	        dvert+=2; //update change in error
	        d+=dvert; //update error
	    }
	    ++x; //rasterise clockwise
	    dhorz+=2; //update change in error
	    d+=dhorz; //update error
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
	mpCircle_d1p5x(xc, yc, r); //call algorithm
	getchar();
	closegraph();
	return 0;
}
