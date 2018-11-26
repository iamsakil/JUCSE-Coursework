#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

void mpEllipse(int xc, int yc, int a, int b)
{    
    int x, y, dp, dhorz, dvert;
    int Asq, Bsq, fourAsq, fourBsq;
    refEllipse(xc, yc, a, b); //reference
    Asq=a*a; //calculate constants
    Bsq=b*b;
    fourAsq=(Asq<<2);
    fourBsq=(Bsq<<2);
    x=dhorz=0; //start ar (0,b)
    y=b;
    dvert=((fourAsq*b)<<1);
    fillPixel(xc, yc+b); //plot initial points
    fillPixel(xc, yc-b);
    dp=fourBsq-(fourAsq*b)+Asq; //calculate initial error
    while(dhorz<dvert) //in region 1
    {
        if(dp>=0)
        {
            --y;
            dvert-=(fourAsq<<1); //update change in error
            dp-=dvert; //update error diagonal move
        }
        ++x; //rasterise clockwise
        dhorz+=(fourBsq<<1); //update change in error
        dp+=fourBsq+dhorz; //update error horizontal move
        fillPixel(xc+x, yc+y); //plot symmetric points
        fillPixel(xc+x, yc-y);
        fillPixel(xc-x, yc+y);
        fillPixel(xc-x, yc-y);
    }
    dp+=Bsq-(fourBsq*x)+Asq-(fourAsq*y); //update error for region 2
    while(y>0) //in region 2
    {
        if(dp<=0)
        {
            ++x;
            dhorz+=(fourBsq<<1); //update change in error
            dp+=dhorz; //update error diagonal move
        }
        --y;
        dvert-=(fourAsq<<1); //update change in error
        dp+=fourAsq-dvert; //update error vertical move
        fillPixel(xc+x, yc+y); //plot symmetric points
        fillPixel(xc+x, yc-y);
        fillPixel(xc-x, yc+y);
        fillPixel(xc-x, yc-y);
    }    
}
    
int main(int argc, char** argv)
{
	int xc, yc, a, b;
	int gd=DETECT,gm;
	if(argc<5)
	{
	    printf("[ ERROR ] Usage : x_center y_center a b\n");
	    return 1;
	}
	xc=atoi(argv[1]); //get arguments
	yc=atoi(argv[2]);
	a=atoi(argv[3]);
	b=atoi(argv[4]);	
	initgraph(&gd, &gm, NULL); //initialize graphics
	grid();
	mpEllipse(xc, yc, a, b); //call algorithm
	getchar();
	closegraph();
	return 0;
}
