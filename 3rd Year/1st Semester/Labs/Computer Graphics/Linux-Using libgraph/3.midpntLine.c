#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

int gif(double d) //greatest integer function
{
    if((int)d>d)
        return (int)d-1;
    return (int)d;
}

void mpLine(int x1, int y1, int x2, int y2)
{
	int dy, dx, p, x, y, s1, s2, i, flag;
	refLine(x1, y1, x2, y2); //reference
	i=1; //initialize variables
    x=x1;
    y=y1;
    dx=x2-x1;
    dy=y2-y1;
    s1=dx>0?1:-1;
    s2=dy>0?1:-1;
    dx*=s1;
    dy*=s2;
    p=dy-(dx>>1); //initialize first error
    if(dy>dx) { int temp=dx; dx=dy; dy=temp;
    	            flag=1; } //interchange dx and dy taking lesser slope
    else flag=0;
    while(i<=dx)
    {
	    fillPixel(x,y); //plot
	    if(p>0) //above midpoint, diagonal move
	    {
	        p-=dx; //diagonal move
	        if(flag) x+=s1; //update
	        else y+=s2;
	    }
	    p+=dy; //orthogonal move
	    if(flag) y+=s2; //update
	    else x+=s1;
	    ++i;
	}
}

int main(int argc, char** argv)
{
	int x1,y1,x2,y2;
	int gd=DETECT,gm;
	if(argc<5)
	{
	    printf("[ ERROR ] Usage : x1 y1 x2 y2\n");
	    return 1;
	}
	x1=atoi(argv[1]); //get arguments
	y1=atoi(argv[2]);
	x2=atoi(argv[3]);
	y2=atoi(argv[4]);
	initgraph(&gd, &gm, NULL); //initialize graphics
	grid();
	if(x1==x2) //check for trivial cases
	    vertLine(x1, y1, y2);
	else if(y1==y2)
	    horiLine(x1, x2, y1);
	else if(abs(x1-x2)==abs(y1-y2))
	    diagLine(x1, y1, x2, y2);
	else mpLine(x1, y1, x2, y2); //call algorithm
	getchar();
	closegraph();
	return 0;
}
