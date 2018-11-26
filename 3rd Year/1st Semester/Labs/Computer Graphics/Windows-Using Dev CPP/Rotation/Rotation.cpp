
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
    	//delay(100);
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
    DDAline(0,28,0,-26,RED);
    DDAline(31,0,-32,0,RED);
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
	int x2,y2,x1,y1,x3,y3,xn,yn,xn1,yn1,xn2,yn2;
	double r11,r12,r21,r22,th;
	printf("Enter the 3 triangle end points:");
	printf(" x1 y1 x2 y2 x3 y3: ");
	scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
	printf("\nEnter the angle: ");
	scanf("%lf",&th);
	
	initgraph(&graphdriver,&graphmode,"c:\\tc\\bgi");
	grid();
	DDAline(x1,y1,x2,y2,BLUE);
	DDAline(x3,y3,x2,y2,BLUE);
	DDAline(x1,y1,x3,y3,BLUE);
	r11=cos((th*3.1428)/180);
	r12=sin((th*3.1428)/180);
	r21=(-sin((th*3.1428)/180));
	r22=cos((th*3.1428)/180);
	//printf("%lf  %lf  %lf  %lf",r11,r12,r21,r22);
	xn=((x2*r11)-(y2*r12));
	yn=((x2*r12)+(y2*r11));
	xn1=((x1*r11)-(y1*r12));
	yn1=((x1*r12)+(y1*r11));
	xn2=((x3*r11)-(y3*r12));
	yn2=((x3*r12)+(y3*r11));
	DDAline(xn1,yn1,xn,yn,WHITE);
	DDAline(xn1,yn1,xn2,yn2,WHITE);
	DDAline(xn2,yn2,xn,yn,WHITE);
	getch();
	closegraph();
}

