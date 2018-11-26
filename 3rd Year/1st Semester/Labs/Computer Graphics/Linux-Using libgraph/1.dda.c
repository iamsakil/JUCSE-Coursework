#include <stdio.h>
#include <stdlib.h>
#ifndef magnified_raster_display
#define magnified_raster_display
#include <stdio.h>
#include <graphics.h>
#include <time.h>

struct Raster //holds configuration settings for exploded raster display
{
    int centerX, centerY, width; //origin co-ordinates and pixel width
    float dely; //delay between pixels
    clock_t pre, cur; //used to realize delays
} raster;

void fillPixel(int x, int y) //fills the specified pixel
{
    while(((raster.cur=clock())-raster.pre)<(raster.dely*CLOCKS_PER_SEC));
                                    //wait for the required delay
    int i, j;
	int bLeftX=raster.centerX+x*raster.width;
	int bLeftY=raster.centerY-y*raster.width;
	for(i=1; i<raster.width; ++i)
	    for(j=0; j<raster.width; ++j)
	        if(getpixel(bLeftX+i, bLeftY-j)==WHITE)
	            putpixel(bLeftX+i, bLeftY-j, BLUE); //fill pixel by pixel if empty
	raster.pre=raster.cur=clock();
}

void refLine(int x1, int y1, int x2, int y2) //reference line
{
    setcolor(RED);
    line(raster.centerX+x1*raster.width,
            raster.centerY-y1*raster.width,
                raster.centerX+x2*raster.width,
                    raster.centerY-y2*raster.width);
}

void refEllipse(int xc, int yc, int a, int b) //reference ellipse
                                  //also used for circle
{
    setcolor(RED);
    ellipse(raster.centerX+xc*raster.width,
            raster.centerY-yc*raster.width,
                0, 360,
                a*raster.width,
                    b*raster.width);
}


void horiLine(int x1, int x2, int y) //trivial algorithm for horizontal case
{
    int i;
    refLine(x1, y, x2, y);
    for(i=(x1>x2?x2:x1); i<(x1>x2?x1:x2); ++i)
        fillPixel(i, y);
}

void vertLine(int x, int y1, int y2) //trivial algorithm for vertical case
{
    int i;
    refLine(x, y1, x, y2);
    for(i=(y1>y2?y2:y1); i<(y1>y2?y1:y2); ++i)
        fillPixel(x, i);
}

void diagLine(int x1, int y1, int x2, int y2) //trivial algorithm for diagonal cases
{
    int i, j, sign=(x1-x2)+(y1-y2)?1:-1;
    refLine(x1, y1, x2, y2);
    for(i=(x1>x2?x2:x1), j=(x1>x2?y2:y1); i<(x1>x2?x1:x2); ++i, j+=sign)
        fillPixel(i, j);
}

void grid() //initializes grid for graphics
{
    FILE *setting;
    int i, mx, my;
    setting=fopen("settings.kpd", "rx"); //open settings file
    if(!setting) //file not opened, use defaults
    {
    	raster.centerX=320; //origin at center of screen
    	raster.centerY=240;
    	raster.width=10; //width 10p
    	raster.dely=0.25; //delay 1/4s
    	setting=fopen("settings.kpd","w"); //force create settings file...
    	if(!setting)
            printf("\nLOG [ERROR] : could not create file settings.kpd\n");
    	else
    	{
    	    fwrite(&raster, sizeof(raster), 1, setting); //...and store defaults
    	    fclose(setting);
    	}
    }
    else
    {
    	fread(&raster, sizeof(raster), 1, setting); //read settings
    	fclose(setting);
    }
    raster.pre=0; //set previous time to beginning of program
    setcolor(WHITE);
    bar(0, 0, mx=getmaxx(), my=getmaxy()); //white out grid
    setcolor(LIGHTGRAY); 
    for(i=raster.centerY; i<=my; i+=raster.width) //draw gridlines
		line(0, i, mx, i);
    for(i=raster.centerX; i<=mx; i+=raster.width) //(begin at origin,
		line(i, 0, i, my);
	for(i=raster.centerY; i>=0; i-=raster.width) //proceed in both directions)
		line(0, i, mx, i);
    for(i=raster.centerX; i>=0; i-=raster.width)
		line(i, 0, i, my);
    setcolor(BLACK);
    line(0, raster.centerY, mx, raster.centerY);  //draw axes
    line(raster.centerX, 0, raster.centerX, my);
}

#endif

int gif(double d) //greatest integer function
{
    if((int)d>d)
        return (int)d-1;
    return (int)d;
}

void ddaLine(int x1, int y1, int x2, int y2)
{
	double x, y, xinc, yinc, dx, dy;
	int step, k;
	dy = y2-y1;
	dx = x2-x1;
	step=(abs(dx)>abs(dy))?abs(dx):abs(dy); //choose the larger number of divisions
	xinc = dx/step; //change at each step
	yinc = dy/step;
	x=gif(x1+0.5); //round down
	y=gif(y1+0.5);
	refLine(x1, y1, x2, y2); //reference
	for(k=1; k<=step; ++k)
	{
		fillPixel(gif(x), gif(y)); //plot
		x+=xinc; //update
		y+=yinc; 
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
	initgraph(&gd, &gm, NULL);  //initialize graphics
	grid();
	if(x1==x2) //check for trivial cases
	    vertLine(x1, y1, y2);
	else if(y1==y2)
	    horiLine(x1, x2, y1);
	else if(abs(x1-x2)==abs(y1-y2))
	    diagLine(x1, y1, x2, y2);
	else ddaLine(x1, y1, x2, y2); //call algorithm
	getchar();
	closegraph();
	return 0;
}
