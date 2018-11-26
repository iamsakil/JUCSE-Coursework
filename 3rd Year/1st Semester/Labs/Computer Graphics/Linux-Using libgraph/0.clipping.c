#ifndef clipping_graphics
#define clipping_graphics
#include <graphics.h>
#include "0.kpgparse.c"

void clippingWindow(SHAPE window) //draws the clipping window polygon
{
    setcolor(WHITE);
    bar(0, 0, 640, 480);
    setcolor(LIGHTGRAY);
    line(320, 0, 320, 480);
    line(0, 240, 640, 240);
    setcolor(BLACK);
    SHAPE vertex1=window;
    do
    {
        line(320+(window->x), 240-(window->y), 320+(window->next->x), 240-(window->next->y));
        window=window->next;
    }while(window->next);
    line(320+(window->x), 240-(window->y), 320+(vertex1->x), 240-(vertex1->y)); //last edge
}

void refLine(x1, y1, x2, y2) //original line
{
    setcolor(RED);
    line(320+x1, 240-y1, 320+x2, 240-y2);
    ellipse(320+x1, 240-y1, 0, 360, 2, 2);
    ellipse(320+x2, 240-y2, 0, 360, 2, 2);
}

void clippedLine(x1, y1, x2, y2) //clipped lines
{
    setcolor(BLUE);
    line(320+x1, 240-y1, 320+x2, 240-y2);
    ellipse(320+x1, 240-y1, 0, 360, 3, 3);
    ellipse(320+x2, 240-y2, 0, 360, 3, 3);
}
              
#endif
