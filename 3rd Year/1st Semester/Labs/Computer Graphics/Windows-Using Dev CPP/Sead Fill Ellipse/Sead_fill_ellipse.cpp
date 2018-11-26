#include<iostream>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<math.h>
 
using namespace std; 

void putpxl(int x, int y, int size=10)
{
    int xp=640/2+size*x , yp=480/2-size*y;
	setfillstyle(SOLID_FILL,BLUE);
	bar(xp+1,yp-size+1,xp+size+1,yp+1);
}

void grid(){
	int i;
	    setcolor(8);
    for(i=0;i<640;i+=10){
	if(i==320)
	    setcolor(12);
	line(i,0,i,480);
	if(i==320)
	    setcolor(8);
    }
    for(i=0;i<480;i+=10){
	if(i==240)
	    setcolor(12);
	line(0,i,640,i);
	if(i==240)
	    setcolor(8);
    }
}

int getpxl(int x, int y,int size=10)
{
	int xp=640/2+size*x , yp=480/2-size*y;
	return getpixel(xp+6,yp-4);
}

int count;
void floodFill(int x,int y,int oldcolor,int newcolor)
{
	count++;
    if(getpxl(x,y) == oldcolor)
    {
        putpxl(x,y);
    	delay(5);
        floodFill(x+1,y,oldcolor,newcolor);
        floodFill(x,y+1,oldcolor,newcolor);
        floodFill(x-1,y,oldcolor,newcolor);
        floodFill(x,y-1,oldcolor,newcolor);
    }
}
//getpxl(x,y) gives the color of specified pixel


 void ellipse(int xc,int yc,int rx,int ry)
 {
   int x, y, p;
   x=0;
   y=ry;
   p=(ry*ry)-(rx*rx*ry)+((rx*rx)/4);
   while((2*x*ry*ry)<(2*y*rx*rx))
   {
        putpxl(xc+x,yc-y);
        putpxl(xc-x,yc+y);
        putpxl(xc+x,yc+y);
        putpxl(xc-x,yc-y);

        if(p<0)
        {
     x=x+1;
     p=p+(2*ry*ry*x)+(ry*ry);
        }
        else
        {
     x=x+1;
     y=y-1;
     p=p+(2*ry*ry*x+ry*ry)-(2*rx*rx*y);
        }
   }
   p=((float)x+0.5)*((float)x+0.5)*ry*ry+(y-1)*(y-1)*rx*rx-rx*rx*ry*ry;

         while(y>=0)
   {
        putpxl(xc+x,yc-y);
        putpxl(xc-x,yc+y);
        putpxl(xc+x,yc+y);
        putpxl(xc-x,yc-y);

        if(p>0)
        {
     y=y-1;
     p=p-(2*rx*rx*y)+(rx*rx);

        }
        else
        {
     y=y-1;
     x=x+1;
     p=p+(2*ry*ry*x)-(2*rx*rx*y)-(rx*rx);
        }
   }
 }
 
int main()
{
    int gm,gd=DETECT;
    initgraph(&gd,&gm,"c:\\turboc3\\bgi");
    
    cleardevice();
    setbkcolor(BLACK);
	
	grid();

	ellipse(0,0,8,12);
	floodFill(1,1,BLACK,BLUE);
	cout<<count;
	getch();
    closegraph();
    
    return 0;
}

