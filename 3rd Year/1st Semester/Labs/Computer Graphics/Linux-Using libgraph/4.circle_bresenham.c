#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

void bresenhamCircle(int xc, int yc, int r)
{
    int x, y, d, D;
    refEllipse(xc, yc, r, r); //reference
    x=0; //start at (0,r)
    y=r;
    D=((1-r)<<1); //initial error
    fillPixel(xc, yc+r); //plot starting points
    fillPixel(xc, yc-r);
    while(y) //rasterise 1st quadrant clockwise
    {
        d=0; //change in error
        if(D-x<=0) d+=((++x)<<1)+1; //horizontal move
        if(D+y>0) d+=1-((--y)<<1); //vertical move
        D+=d; //update error
        
/*   //Grouping the Diagonal Moves together        
        if(D+y<=0) D+=((++x)<<1)+1; //move east
        else if(D-x>0) D+=1-((--y)<<1); //move south
        else D+=(((++x)-(--y)+1)<<1); //move south-east   */
        
/*  //Original structure
        //if (D<0) //move east or south-east
			if(D+y<=0) D+=((++x)<<1)+1; //move east
			//else D+=(((++x)-(--y)+1)<<1); //move south-east
		else if(D>0) //move south or south-east
			if(D-x<=0) D+=(((++x)-(--y)+1)<<1); //move south-east
			else D+=1-((--y)<<1); //move south
		else D+=(((++x)-(--y)+1)<<1); //move south-east   */
		
        fillPixel(xc+x, yc+y); //plot symmetric points
        fillPixel(xc+x, yc-y);        
        fillPixel(xc-x, yc+y);
        fillPixel(xc-x, yc-y);
    }
}
    
int main(int argc, char** argv)
{
	int xc,yc,r;
	int gd=DETECT,gm;
    scanf("%d %d %d",&xc,&yc,&r);
	initgraph(&gd, &gm, NULL); //initialize graphics
	grid();
	bresenhamCircle(xc, yc, r); //call algorithm
	getchar();
	closegraph();
	return 0;
}
