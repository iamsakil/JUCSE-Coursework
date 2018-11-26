#include <stdio.h>
#include <dos.h>
#include <graphics.h>
#include<conio.h>
#include <iostream>
#define false 0
#define true 1
#define bool int
using namespace std;
int xmax,ymax,dis;
float ab(float x){
	if (x<0) return -x;
	return x;
}

void displayGrid(){
	setcolor(8);
    int i;
    for(i = 0; i <=xmax; i+=dis)
    {
	line(i, 0, i, ymax);
    }
    for(i=0;i<=ymax;i+=dis) line(0,i,xmax,i);
	setcolor(11);
	//line((xmax)/2, 0, (xmax)/2, ymax);
	//line(0,(ymax)/2, xmax,(ymax)/2);
}

void putpixe(int x,int y,int c){
	int lx=x/5 *5;
	int ly=(y/5)*5;
	for(int i=lx;i<=lx+5;i++) for(int j=ly;j<=ly+5;j++) putpixel(i,j,c);
	//delay(10);
}

void dda_line(int x0,int y0,int x1,int y1,int c){
	int i,j,k,p,q;
	float dy=y1-y0,dx=x1-x0;
	if(dx==0){
		if(y1<y0){
			i=x1;
			x1=x0;
			x0=i;i=y1;
			y1=y0;
			y0=i;
		}
		for(i=y0;i<=y1;i++){
			putpixe((int)x1,(int)i,c);
			//putpixel(x1,i,RED);
			//setfillstyle(SOLID_FILL,RED);
			//setcolor(RED);
			//floodfill(x1,i,7);
			//putpixel(x1,i,RED);
			//delay(10);
		}
		return;
	}
	if(dy==0){
		if(x1<x0){
			i=x1;
			x1=x0;
			x0=i;i=y1;
			y1=y0;
			y0=i;
		}
		for(i=x0;i<=x1;i++){
		//	putpixel(i,y1,RED);
		//	putpixel(i,y1+1,RED);
		//	setfillstyle(SOLID_FILL,RED);
			//setcolor(RED);
		//	floodfill(i,y1+1,7);
			//putpixel(x1,i,RED);
			putpixe((int)i,(int)y1,c);
			//delay(10);
		}
		return;
	}
	float m=dy/dx;
	if(ab(m)<1){
		float x=x0,y=y0;
		if(x1<x0){
			i=x1;
			x1=x0;
			x0=i;i=y1;
			y1=y0;
			y0=i;
		}
		while(x<=x1){
			//setcolor(14);
			putpixe((int)x,(int)y,c);
		//	putpixel((int)x,(int)y,RED);
		//	setfillstyle(SOLID_FILL,RED);
		//	floodfill((int)x,(int)y,7);
			//putpixel((int)x,(int)y,RED);
			x++;
			y=y+m;
			//delay(10);
		}
	}else{
		m=1/m;
		if(y1<y0){
			i=x1;
			x1=x0;
			x0=i;i=y1;
			y1=y0;
			y0=i;
		}
		float x=x0,y=y0;
		while(y<=y1){
			putpixe((int)x,(int)y,c);
			//setcolor(14);
			//setfillstyle(SOLID_FILL,RED);
			//floodfill((int)x,(int)y,7);
			//putpixel((int)x,(int)y,RED);
			y++;
			x=x+m;
			//delay(10);
		}
	}
}
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
const int x_max = 300;
const int y_max = 250;
const int x_min = 40;
const int y_min = 40;
int computeCode(double x, double y){
    int code = INSIDE;

    if (x < x_min)
	code |= LEFT;
    else if (x > x_max)
	code |= RIGHT;
    if (y < y_min)
	code |= BOTTOM;
    else if (y > y_max)
	code |= TOP;

    return code;
}
void cohenSutherlandClip(double x1, double y1,double x2, double y2){
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;
    while (true)
    {
	if ((code1 == 0) && (code2 == 0))
	{
	    accept = true;
	    break;
	}
	else if (code1 & code2)
	{
	    break;
	}
	else
	{
	    int code_out;
	    double x, y;
	    if (code1 != 0)
		code_out = code1;
	    else
		code_out = code2;
	    if (code_out & TOP)
	    {
		x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
		y = y_max;
	    }
	    else if (code_out & BOTTOM)
	    {
		x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
		y = y_min;
	    }
	    else if (code_out & RIGHT)
	    {
		y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
		x = x_max;
	    }
	    else if (code_out & LEFT)
	    {
		y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
		x = x_min;
	    }

	    if (code_out == code1)
	    {
		x1 = x;
		y1 = y;
		code1 = computeCode(x1, y1);
	    }
	    else
	    {
		x2 = x;
		y2 = y;
		code2 = computeCode(x2, y2);
	    }
	}
    }
    if (accept)
    {
      //	cout <<"Line accepted from " << x1 << ", "
	//     << y1 << " to "<< x2 << ", " << y2 << endl;
	dda_line(x1,y1,x2,y2,5);
    }
   // else
     //	cout << "Line rejected" << endl;
}
//hhjk
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "..//BGI"); // initialize graph
    xmax=650;ymax=400;dis=5;
    displayGrid();
    dda_line(x_max,y_max,x_max,y_min,11);
    dda_line(x_min,y_max,x_min,y_min,11);
    dda_line(x_max,y_max,x_min,y_max,11);
    dda_line(x_max,y_min,x_min,y_min,11);
	//dda_line(,80,40,40,14);dda_line(100,40,40,40,14);dda_line(100,80,40,80,14);
    int x1,x2,y1,y2;
    x1=20;y1=40;x2=430;y2=320;
    dda_line(x1,y1,x2,y2,12);
    getch();
    cohenSutherlandClip(x1,y1,x2,y2);
    getch();
    x1=100;y1=150;x2=200;y2=230;
    dda_line(x1,y1,x2,y2,12);
    getch();
    cohenSutherlandClip(x1,y1,x2,y2);
    getch();
    x1=20;y1=300;x2=340;y2=50;
    dda_line(x1,y1,x2,y2,12);
    getch();
    cohenSutherlandClip(x1,y1,x2,y2);
    getch();
    return 0;
}

