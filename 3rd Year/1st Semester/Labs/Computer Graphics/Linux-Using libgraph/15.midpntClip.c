#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "0.kpgparse.c"
#include "0.clipping.c"

#define MAXERROR 1 //how to make this 0

int gif(int a1, int a2) //greatest integer function
{
    double d=(a1+a2)*0.5;
    if(d<(int)d)
        return (int)d-1;
    return (int)d;
}

int window[4]; //regular window [l, r, b, t]

unsigned char calcEPC(int x, int y) //calculate End Point Code
{
    unsigned char c=0;
    if(y>window[3]) c+=8; //above t
    if(y<window[2]) c+=4; //below b
    if(x>window[1]) c+=2; //right of r
    if(x<window[0]) c+=1; //left of l
    return c;
}

void getFar(int *x1, int *y1, int x2, int y2) //get furthest visible point from P2
{
    int midx, midy;
    while(abs(*x1-x2)>MAXERROR || abs(y2-*y1)>MAXERROR)
    {
        midx=gif(*x1, x2); //midpoints
        midy=gif(*y1, y2);
        if(calcEPC(*x1, *y1)&calcEPC(midx, midy)) { *x1=midx; *y1=midy; } //check visibility
        else { x2=midx; y2=midy; }
    }
    *x1=gif(*x1, x2); //update P1
    *y1=gif(*y1, y2);
}

void midpntClip(SHAPE lin)
{
    int i;
    unsigned char code;
    int y1=lin->y;       //get co-ordinates
    int y2=lin->next->y;
    int x1=lin->x;
    int x2=lin->next->x;
    erase(lin);
    refLine(x1, y1, x2, y2); //original line
    getchar();
    code=(calcEPC(x1, y1)<<4) + calcEPC(x2, y2); //calculate end point codes
    if(!code) //trivially visible
    {
        clippedLine(x1, y1, x2, y2); //output
        return;
    }
    if((code>>4)&code) return; //trivially invisible
    if(code>>4)
        getFar(&x1, &y1, x2, y2); //get furthest visible point from P2
    if(code&15)
        getFar(&x2, &y2, x1, y1); //get furthest visible point from P1
    if(!(calcEPC(x1, y1)&calcEPC(x2, y2)))
        clippedLine(x1, y1, x2, y2); //output
}

int main(int argc, char **argv)
{
    int gd=DETECT,gm;
    FILE *kpg;
    SHAPE wndw, lin;
    if(argc<2)
	{
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file\n");
	    return 1;
	}
    kpg = fopen(argv[1], "rx"); //open input file
    if(!kpg)
	{
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file\n");
	    return 1;
	}
    if(!(wndw=expectPoly(kpg))) //input regular window and line
    {
        printf("\nInvalid File Format\n");
        fclose(kpg);
        return 1;
    }    
    window[3]=wndw->y;       //get co-ordinates of window
    window[0]=wndw->x;
    window[2]=wndw->next->next->y;
    window[1]=wndw->next->next->x;
    if(window[3]<window[2]) { int t=window[3]; window[3]=window[2]; window[2]=t; }
    if(window[0]>window[1]) { int t=window[0]; window[0]=window[1]; window[1]=t; }
    initgraph(&gd, &gm, NULL); //initialize graphics
    clippingWindow(wndw); //draw window
    erase(wndw);
    while(lin=expectLine(kpg))
        midpntClip(lin); //call algorithm
	getchar();
	closegraph();
	if(!feof(kpg))
	{
	    printf("\nInvalid File Format\n");
        fclose(kpg);
        return 1;
	}
	fclose(kpg);
    return 0;
}
