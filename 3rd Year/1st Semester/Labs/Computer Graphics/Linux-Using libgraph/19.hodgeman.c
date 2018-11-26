#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "0.kpgparse.c"
#include "0.clipping.c"

SHAPE window;

void DrawPoly(SHAPE gon, int color)
{
    setcolor(color);
    SHAPE vertex1=gon;
    do
    {
        line(320+(gon->x), 240-(gon->y), 320+(gon->next->x), 240-(gon->next->y));
        gon=gon->next;
    }while(gon->next);
    line(320+(gon->x), 240-(gon->y), 320+(vertex1->x), 240-(vertex1->y));
}

int isVis(SHAPE pnt, SHAPE w1, SHAPE w2) // outside=-1, inside=1, on_the_boundary=0
{
    long t= (pnt->y - w1->y)*(w2->x - w1->x) - (pnt->x - w1->x)*(w2->y - w1->y);
    return t>0?1:t<0?-1:0;
}

void hodgeman(SHAPE oriGon)
{
    SHAPE gon=oriGon;
    SHAPE wcur = window; //window_vertex_1
    int vc, vn;
    DrawPoly(gon, RED); //reference
    do
    {
        SHAPE out=NULL; //temporary polygon
        SHAPE wnxt = wcur->next?wcur->next:window; //closed polygon, vertex_1 follows vertex_N
        SHAPE pcur = gon; //polygon_vertex_1
        vn=isVis(pcur, wcur, wnxt); //check visibility of object_vertex_1 w.r.t. window edge
        do
        {   
            SHAPE pnxt = pcur->next?pcur->next:gon; //closed polygon, vertex_1 follows vertex_N
            vc=vn;
            vn=isVis(pnxt, wcur, wnxt); //check visibility w.r.t. window edge
            if( (vc<0 && vn>0) || (vc>0 && vn<0) ) //intersection
            {   
                SHAPE tmp = (SHAPE)malloc(sizeof(struct point));
                
                /*int x1=pcur->x;                              //calculate values
                int y1=pcur->y;
                int x2=pnxt->x;
                int y2=pnxt->y;
                int x3=wcur->x;
                int y3=wcur->y;
                int x4=wnxt->x;
                int y4=wnxt->y;
                tmp->x = ( (x1*y2-y1*x2)*(x3-x4) - (x3*y4-y3*x4)*(x1-x2) ) / ( (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) );
                tmp->y = ( (x1*y2-y1*x2)*(y3-y4) - (x3*y4-y3*x4)*(y1-y2) ) / ( (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) );*/

                int T1, T2, T3, T4; //calculate intersection point by algebraic method
                int A = pcur->x*pnxt->y-pcur->y*pnxt->x;
                int B = wcur->x*wnxt->y-wcur->y*wnxt->x;
                int D = (T1=pcur->x-pnxt->x)*(T2=wcur->y-wnxt->y)-(T3=pcur->y-pnxt->y)*(T4=wcur->x-wnxt->x);
                tmp->x = ( A*T4 - B*T1 ) / D;
                tmp->y = ( A*T2 - B*T3 ) / D;
                
                tmp->next=out;                          //add intersection point to temporary polygon
                out=tmp;
            }
            if(vn>=0) //add visible points to temporary polygon
            {
                SHAPE tmp = (SHAPE)malloc(sizeof(struct point));
                tmp->x=pnxt->x;
                tmp->y=pnxt->y;
                tmp->next=out;
                out=tmp;
            }
        }while(pcur=pcur->next); //loop over polygon vertices/edges
        if(gon!=oriGon)
            erase(gon);
        if(!out) return;
        gon=out; //update polygon
        getchar(); //show progress based clipping against current line
        clippingWindow(window);
        DrawPoly(oriGon, RED);
        setcolor(MAGENTA);
        line(320+wcur->x, 240-wcur->y, 320+wnxt->x, 240-wnxt->y);
        DrawPoly(gon, BLUE);
    }while(wcur=wcur->next); //loop over window edges
    clippingWindow(window);
    DrawPoly(oriGon, RED);
    DrawPoly(gon, BLUE); //output
    erase(gon);
    erase(oriGon);
}

int main(int argc, char **argv)
{
    int gd=DETECT,gm;
    FILE *kpg;
    SHAPE gon;
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
    while(gon=expectPoly(kpg))
        hodgeman(gon); //call algorithm
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
