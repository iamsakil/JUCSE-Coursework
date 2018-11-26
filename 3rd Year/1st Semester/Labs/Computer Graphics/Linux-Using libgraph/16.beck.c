#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "0.kpgparse.c"
#include "0.clipping.c"

SHAPE window;

void beck(SHAPE lin)
{
    double t, tu=1.0, tl=0.0;
    int y1=lin->y;       //get co-ordinates
    int y2=lin->next->y;
    int x1=lin->x;
    int x2=lin->next->x;
    SHAPE cur = window; //vertex_1
    erase(lin);
    refLine(x1, y1, x2, y2); //original line
    getchar();
    do
    {
        SHAPE nxt = cur->next?cur->next:window; //closed polygon, vertex_1 follows vertex_N
        int Dn = (nxt->x - cur->x)*(y2-y1) - (nxt->y - cur->y)*(x2-x1); //Dot product of Direction of Line and Inward Normal
        int Wn = (nxt->x - cur->x)*(y1 - cur->y) - (nxt->y - cur->y)*(x1 - cur->x); //Dot product of Weight Vector and Inward Normal
        if(!Dn) //If parallel
            if(Wn<0) return; //totally outside
            else continue; //totally inside
        t=Wn*(-1.0)/Dn; //calculate parameter
        if(Dn>0) //entering
        {
            if(t>1) return; //totally outside
            else if(t>tl) tl=t; //maximum of lower limits
        }
        else if(t<0) return; //totally outside
        else if(t<tu) tu=t; //exiting, minimum of upper limits
        if(tl>tu) return; //exits before entering, totally outside
    }while(cur=cur->next); //loop over window edges
    clippedLine(x1+(int)((x2-x1)*tl), y1+(int)((y2-y1)*tl), x1+(int)((x2-x1)*tu), y1+(int)((y2-y1)*tu)); //output
}

int main(int argc, char **argv)
{
    int gd=DETECT,gm;
    SHAPE lin;
    FILE *kpg;
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
    if(!(window=expectPoly(kpg))) //input regular window and line
    {
        printf("\nInvalid File Format\n");
        fclose(kpg);
        return 1;
    }
	initgraph(&gd, &gm, NULL); //initialize graphics
    clippingWindow(window); //draw window
    while(lin=expectLine(kpg))
        beck(lin); //call algorithm
	getchar();
	closegraph();
	erase(window);
	if(!feof(kpg))
	{
	    printf("\nInvalid File Format\n");
        fclose(kpg);
        return 1;
	}
	fclose(kpg);
    return 0;
}
