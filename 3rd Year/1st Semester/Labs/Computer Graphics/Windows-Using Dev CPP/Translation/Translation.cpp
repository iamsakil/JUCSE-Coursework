#include <iostream>
#include<dos.h>
#include<graphics.h>
#include<math.h>
#include<cstdio>
using namespace std;


 void putpxl(int x, int y,int colour, int size=10)
{
    int xp=640/2+size*x , yp=480/2-size*y;
	setfillstyle(SOLID_FILL,colour);
	bar(xp+1,yp-size+1,xp+size+1,yp+1);
    //putpixel(x+(getmaxx()/2), (getmaxy()/2)-y, WHITE);
}

void DDAline(int X0, int Y0, int X1, int Y1,int colour)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
    	delay(100);
        putpxl (X,Y,colour);  // put pixel at (X,Y)
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step         // for visualization of line-
                             // generation step by step
    }
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
    //DDAline(0,28,0,-26,RED);
    //DDAline(31,0,-32,0,RED);
}

int getpxl(int x, int y,int size=10)
{
	int xp=640/2+size*x , yp=480/2-size*y;
	return getpixel(xp+6,yp-4);
}


int main(void)
{
	int graphdriver=DETECT,graphmode,errorcode;
	int i;
	int x2,y2,x1,y1,x,y,x3,y3;
	printf("Enter the triangle end points:");
	printf(" x1 y1 x2 y2 x3 y3: ");
	scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
	printf("Enter translation co-ordinates ");
	printf(" x y :");
	scanf("%d%d",&x,&y);
	initgraph(&graphdriver,&graphmode,"c:\\tc\\bgi");
	grid();
	DDAline(x1,y1,x2,y2,RED);
	DDAline(x3,y3,x2,y2,RED);
	DDAline(x1,y1,x3,y3,RED);
	
	x1=x1+x;
	y1=y1+y;
	x2=x2+x;
	y2=y2+y;
	x3=x3+x;
	y3=y3+y;
	
	//printf("Line after translation");
	DDAline(x1,y1,x2,y2,GREEN);
	DDAline(x3,y3,x2,y2,GREEN);
	DDAline(x1,y1,x3,y3,GREEN);
	
	
	getch();
	closegraph();
	return 0;
}


