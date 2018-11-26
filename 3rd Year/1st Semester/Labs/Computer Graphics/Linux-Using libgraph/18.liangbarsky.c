#include <stdio.h>
#include <graphics.h>
#include "0.kpgparse.c"
#include "0.clipping.c"

int window[4]; //regular window [l, r, b, t]
double tl, tu;

int isIn(int d, int q)
{
    if(!d) //parallel
        if(q<0) return 0; //totally outside
        else return 1; //totally inside
    double t=q*(-1.0)/d;//calculate parameter
    if(d>0) //entering
    {
        if(t>1) return 0; //totally outside
        else if(t>tl) tl=t; //maximum of lower limits
    }
    else if(t<0) return 0; //totally outside
    else if(t<tu) tu=t; //exiting, minimum of upper limits
    if(tl>tu) return 0; //exits before entering, totally outside
    return 1;
}

void liangBarsky(SHAPE lin)
{
    int y1=lin->y;       //get co-ordinates
    int y2=lin->next->y;
    int x1=lin->x;
    int x2=lin->next->x;
    int del = x2-x1; //direction of line
    erase(lin);
    refLine(x1, y1, x2, y2); //original line
    getchar();
    tl=0.0; tu=1.0;
    if( !isIn(del, x1-window[0]) || !isIn(-del, window[1]-x1) ) return; //clip along x-axis
    del = y2-y1; //direction of line
    if( !isIn(del, y1-window[2]) || !isIn(-del, window[3]-y1) ) return; //clip along y-axis
    clippedLine(x1+(int)((x2-x1)*tl), y1+(int)((y2-y1)*tl), x1+(int)((x2-x1)*tu), y1+(int)((y2-y1)*tu)); //output
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
    if(window[3]<window[2]) { int t=window[3]; window[3]=window[2]; window[2]=t; } //force ordering of edges
    if(window[1]<window[0]) { int t=window[0]; window[0]=window[1]; window[1]=t; }
    initgraph(&gd, &gm, NULL); //initialize graphics
    clippingWindow(wndw); //draw window
    erase(wndw);
    while(lin=expectLine(kpg))
        liangBarsky(lin); //call algorithm
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
