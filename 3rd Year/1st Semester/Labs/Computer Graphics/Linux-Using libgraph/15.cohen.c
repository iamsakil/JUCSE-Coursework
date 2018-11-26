#include <stdio.h>
#include <graphics.h>
#include "0.kpgparse.c"
#include "0.clipping.c"

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

void cohenClip(SHAPE lin)
{
    int i;
    unsigned char code;
    double slope;
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
    slope=(x1==x2)?0:(double)(y2-y1)/(x2-x1); //calculate slope
    while(code) //while partially visible
    {
        for(i=0; i<4; ++i) //each window edge
        {
            if(((code>>(4+i))&1)==((code>>i)&1)) continue; //does not cross the edge
            if(!((code>>(4+i))&1)) { int t=x1; x1=x2; x2=t;  //(x1,y2) is inside relative to edge
                                         t=y1; y1=y2; y2=t;
                                         code=((code&15)<<4)+(code>>4); } //so swap
            if(x1!=x2 && i<2) //left and right edges
            {
                y1+=slope*(window[i]-x1); //find intersection
                x1=window[i];
            }
            else if(y1!=y2 && i>1) //top and bottom edges
            {
                x1+=slope?(window[i]-y1)/slope:0; //find intersection
                y1=window[i];
            }
            code=(calcEPC(x1, y1)<<4)+(code&15); //update end point codes
            if(!code) break; //totally visible
            if((code>>4)&code) return; //totally invisible
        }
    }
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
        printf("\nInvalid Format\n");
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
        cohenClip(lin); //call algorithm
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
