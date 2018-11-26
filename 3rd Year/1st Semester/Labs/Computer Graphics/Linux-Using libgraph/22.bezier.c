#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include "0.kpgparse.c"

VSHAPE reverse(VSHAPE s)
{
    VSHAPE t;
    if(s==NULL || s->next==NULL)
        return s;
    t=reverse(s->next);
    s->next->next=s;
    s->next=NULL;
    return t;
}

VSHAPE bezier(VSHAPE s, double f)
{
    VSHAPE t;
    VSHAPE out=NULL;
    for(t=s; t->next!=NULL; t=t->next)
    {
        VSHAPE v = (VSHAPE)malloc(sizeof(struct vpoint));
        v->x=t->x+(t->next->x-t->x)*f;
        v->y=t->y+(t->next->y-t->y)*f;
        v->next=out;
        out=v;
    }
    if(out->next!=NULL)
    {
        out=reverse(out);
        t=bezier(out, f);
        eraseVector(out);
        return t;
    }
    else return out;
}

int main(int argc, char **argv)
{
    clock_t last=0, now;
    VSHAPE s, out=NULL;
    int n, i;
    int gd=DETECT,gm;
    float d;
    FILE *kpg;
    if(argc<2)
	{
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file [number_of_animation_frames] [frame_delay]\n");
	    return 1;
	}
    n = (argc>2) ? atoi(argv[2]) :  10;
    d = (argc>3) ? atof(argv[3]) : 0.1;
    kpg=fopen(argv[1], "rx");
    if(!kpg)
    {
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file [number_of_animation_frames] [frame_delay]\n");
	    return 1;
	}
    s=toVector(expectPoly(kpg));
    fclose(kpg);
	initgraph(&gd, &gm, NULL); //initialize graphics
    setcolor(WHITE); //draw axes
    bar(0, 0, 640, 480);
    setcolor(LIGHTGRAY);
    line(320, 0, 320, 480);
    line(0, 240, 640, 240);
    setcolor(BLUE);
    VSHAPE cur;
    for(cur=s; cur->next; cur=cur->next) //draw bounding polygon
        line(320+cur->x, 240-cur->y, 320+cur->next->x, 240-cur->next->y);
    for(i=0; i<=n; ++i)
    {
        VSHAPE t=bezier(s, i*1.0/n); //call algorithm with parameter
        t->next=out;
        out=t;
    }
    eraseVector(s);
    setcolor(RED);
    for(cur=out; cur->next; cur=cur->next)
    {
        while( ((now=clock()) - last)*1.0/CLOCKS_PER_SEC < d ); //animate output with delay
        last=now;
        line(320+cur->x, 240-cur->y, 320+cur->next->x, 240-cur->next->y);
    }
    eraseVector(out);
	getchar();
	closegraph();
	return 0;
}
