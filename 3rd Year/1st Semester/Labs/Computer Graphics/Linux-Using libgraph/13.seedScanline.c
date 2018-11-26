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
int **SL=NULL; //single scan line

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
	    for(j=0; j<numCol; ++j) SL[i][j]=0; //clear the Scan Line
		for(cur=buckets[i]; cur; cur=cur->next)
		    if(cur->dy==0) //horizontal line
		    {
		        for(j=0; j<cur->dx; ++j)
		            SL[i][gif(cur->x+j)+left]=1;
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
				        SL[i][var+left]=1;
		        else if(cur->dx < -1) //not steep slope, multiple points
			        for(var=gif(cur->x+cur->dx); var < gif(cur->x); ++var)
				        SL[i][var+left]=1;
			    else SL[i][gif(cur->x)+left]=1; //steep slope, single point
		        --cur->dy; //update
		        cur->x+=cur->dx;
		    }
		for(j=0; j<numCol; ++j)
		    if(SL[i][j]) fillPixel(j-left, top-i); //clear the Scan Line
	}
}

void seedSL(int x, int y)
{
    int l, r, i, pair;
    if(x<0 || y<0 || x>numCol || y>numSL) return; //out of bounds
    for(l=x; l>0 && !SL[y][l]; --l); //get left most point
    for(r=x; l<numCol && !SL[y][r]; ++r); //get right most point
    for(i=l+1; i<r; ++i)
    {
        SL[y][i] = 1;
        fillPixel(i-left, top-y); //fill
    }
    pair=1;
    if(y) //check upper line
    {
        for(i=l+1; i<r; ++i)
        {
            if(!SL[y-1][i] && pair) //if internal empty zone found
                seedSL(i, y-1);
            else if(i && SL[y-1][i]!=SL[y-1][i-1])
                pair = !pair;
        }
    }
    pair=1;
    if(y<numSL-1) //check lower line
    {
        for(i=l+1; i<r; ++i)
        {
            if(!SL[y+1][i] && pair) //if internal empty zone found
                seedSL(i, y+1);
            else if(i && SL[y+1][i]!=SL[y+1][i-1])
                pair = !pair;
        }
    }
}

int main(int argc, char **argv)
{    
    SHAPE T, cur;
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
	numCol = (left=raster.centerX/raster.width)+(640-raster.centerX)/raster.width; //number of columns
	SL = (int**)malloc(sizeof(int*)*numSL);
	SL[0] = (int*)malloc(sizeof(int)*numCol*numSL); //Number of Pixels per Line
	--top; --left;
	buckets = (EDGE**)malloc(sizeof(EDGE*)*numSL); //initialize buckets
	for(i=0; i<numSL; ++i)
	{
	    buckets[i]=NULL;
	    SL[i] = SL[0] + numCol*i; //array manipulation
	}
	if(!(T=expectPoly(kpg))) //input boundary
	{
        printf("\nInvalid File Format\n");
        fclose(kpg);
        return 1;
    }
	for(cur=T; cur->next; cur=cur->next)
	    fillBucket(cur); //add lines to respective buckets
    cur->next=T;
    fillBucket(cur);
    cur->next=NULL;
    erase(T);
    scanConvert(); //draw boundary
    getchar();
    if(!(T=expectSeed(kpg)))
    {
        printf("\nInvalid File Format\n");
        fclose(kpg);
        return 1;
    }
    seedSL(T->x+left, top-T->y); //call algorithm
    erase(T);
    fclose(kpg);
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
	free(SL[0]);
	free(SL);
    return 0;
}
