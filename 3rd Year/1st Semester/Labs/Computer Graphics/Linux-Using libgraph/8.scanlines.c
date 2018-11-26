#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include "0.kpgparse.c"
#include "0.raster.c"

int gif(double d) //greatest integer function
{
    if(d<0 && (int)d>d)
        return (int)d-1;
    return (int)d;
}

int numCol, numSL, top, left;
int *SL=NULL; //single scan line

typedef struct edge
{
    double x, dx;
    int dy;
    struct edge *next;
}EDGE;

EDGE **buckets=NULL, *ael=NULL;

void fillBucket(SHAPE shape)
{
    int dy;
    double dx;
    EDGE *add;
    int x1=shape->x;
    int y1=shape->y;
    int x2=shape->next->x;
    int y2=shape->next->y;
    erase(shape);
    if(y2>y1) { int t=x1; x1=x2; x2=t;
					t=y1; y1=y2; y2=t; } //P1 is the upper point
    dy = y1-y2;
    if(dy) dx=(x2-x1)*1.0/dy;
    else //horizontal line
    {
        if(x1>x2) { int t=x1; x1=x2; x2=t; } //P1 is the leftmost point
        dx=x2-x1;
    }
	if(y1<top-numSL || y2>top) return; //totally above or below
	if(y1>top) //clipping needed
	{
		x1 += dx*(y1-top); //calculate
		dy = top-y2;
		y1 = top;
	}
	add = (EDGE*)malloc(sizeof(EDGE));
	add->x=x1;
	add->dx=dx;
	add->dy=dy;
	add->next=buckets[top-gif(y1)]; //add to the bucket
	buckets[top-gif(y1)]=add;
}

void scanConvert()
{
	EDGE *cur;
	int i, j, var;
	for(i=0; i<numSL; ++i)
	{
	    for(j=0; j<numCol; ++j) SL[j]=0; //clear the Scan Line
		for(cur=buckets[i]; cur; cur=cur->next)
		    if(cur->dy==0) //horizontal line
		    {
		        for(j=0; j<cur->dx; ++j)
		            SL[gif(cur->x+j)+left]=1;
		    }
		    else //add to Active Edge List
		    {
		        EDGE *temp = (EDGE*)malloc(sizeof(EDGE));
		        temp->x=cur->x;
		        temp->dx=cur->dx;
		        temp->dy=cur->dy;
		        temp->next=ael;
		        ael=temp;
		    }
		for(cur=ael; cur; cur=cur->next)
		    if(cur->dy > 0)
		    {
		        if(cur->dx > 1) //not steep slope, multiple points
			        for(var=gif(cur->x+cur->dx); var > gif(cur->x); --var)
				        SL[var+left]=1;
		        else if(cur->dx < -1) //not steep slope, multiple points
			        for(var=gif(cur->x+cur->dx); var < gif(cur->x); ++var)
				        SL[var+left]=1;
			    else SL[gif(cur->x)+left]=1; //steep slope, single point
		        --cur->dy; //update
		        cur->x+=cur->dx;
		    }
		for(j=0; j<numCol; ++j)
		    if(SL[j]) fillPixel(j-left, top-i); //display Scan Line
	}
}

int main(int argc, char **argv)
{    
    SHAPE T;
	int i;
	int gd=DETECT,gm;
	FILE *kpg;
	if(argc<2)
	{
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file\n");
	    return 1;
	}
    kpg = fopen(argv[1], "rx");
    if(!kpg)
    {
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file\n");
	    return 1;
	}
	initgraph(&gd, &gm, NULL); //initialize graphics
	grid();
	numSL = (top=raster.centerY/raster.width) + (480-raster.centerY)/raster.width; //number of Scan Lines
	SL = (int*)malloc(sizeof(int)*(numCol=(left=raster.centerX/raster.width)+(640-raster.centerX)/raster.width)); //Number of Pixels per Line
	--top; --left;
	buckets = (EDGE**)malloc(sizeof(EDGE*)*numSL); //initialize buckets
	for(i=0; i<numSL; ++i) buckets[i]=NULL;
	while(T=expectLine(kpg)) fillBucket(T); //add lines to respective buckets
    fclose(kpg);
    scanConvert(); //call algorithm
    getchar();
    closegraph();
	for(i=0; i<numSL; ++i) //free memory
	{
		EDGE *E=buckets[i];
		while(E)
		{
			buckets[i]=E;
			E=E->next;
			free(buckets[i]);
		}
	}
	free(buckets);
	free(ael);
	free(SL);
    return 0;
}
