#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <graphics.h>
//#include <X11/Xlib.h>
 void flood(int x, int y, int fillcolor, int old_color)
 {
 	//outtextxy(x-200, y-200, "+");
  setcolor(1);
  floodfill(x-200,y-200,RED);
 	//if(getpixel(x,y)==old_color)
 //	if(getpixel(x,y)==15)
  if(getpixel(x,y)==15||getpixel(x,y)==1)
 		{
 			return;
 		}
    delay(10);
    int i,j;
 		putpixel(x,y,BLUE);
    //floodfill(377,254,WHITE);
 		flood(x+1,y,fillcolor,old_color);
 		flood(x-1,y,fillcolor,old_color);
 		flood(x,y+1,fillcolor,old_color);
 		flood(x,y-1,fillcolor,old_color);
 	}
int main()
{
   int gd=DETECT,gm,points[]={365,265, 345,245, 365,225, 405,225, 425,245, 405,265, 365,265};
 	//XInitThreads();
   initgraph(&gd, &gm, "c:\\tc\\bgi");
int x1=0,y1=0;
  int x2=500,y2=0;
  int x3=0,y3=0;
  int x4=0,y4=500;
  while(y1<450&&y2<450)
  {
  		setcolor(RED);
      line(x1,y1,x2,y2);
      y1=y1+10,y2=y2+10;
  }
  while(x3<450&&x4<450)
  {
      line(x3,y3,x4,y4);
      x3=x3+10,x4=x4+10;
  }
  setcolor(WHITE);
  drawpoly(7, points);
 	flood(377,252,BLUE,0);
  putpixel(377,252,BLUE);
   getch();
   closegraph();
   delay(1000);
   return 0;
}

