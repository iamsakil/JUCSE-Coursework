
#include <iostream>
#include <bitset>
#include <algorithm>
#include <list>
#include <climits>
#include <math.h>
#include <graphics.h>
#include <assert.h>
#define PI 3.14159
#define GSZ 12



using namespace std;

int f_color = RED, b_color = BLACK;
int no_row = (int) floor(6400/((double) (GSZ*10)));
int no_col = (int) floor(4800/((double) (GSZ*10)));

int x_min, y_min,x_max,y_max;

void drawBlocks(int x, int y, int color=f_color) {
	int points[10];
	setcolor(color);
	int x1,y1,minx,miny;
	x1 = x * GSZ;
	y1 = y * GSZ;
	minx = min(640,x1+GSZ);
	miny = min(480,y1+GSZ);
	points[0] = x1+1; points[1] = y1+1; points[2] = minx-1;points[3] = y1+1;points[4]=minx-1;points[5]=miny-1;points[6]=x1+1;points[7]=miny-1;
	points[8]=points[0];points[9] = points[1]; 
	fillpoly(5,points);
}


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
}

int getpxl(int x, int y,int size=10)
{
	int xp=640/2+size*x , yp=480/2-size*y;
	return getpixel(xp+6,yp-4);
}


int drawBlockPoly(int N, int* points, int color) {
	for(int i=0;i<=(2*N-3);i+=2)
		DDAline(points[i],points[i+1],points[i+2],points[i+3],color);
}

int* inputPoly(int N) {
	int* points = new int[2*N+2];
	cout << "Enter vertices of clipping polygon(in either clockwise or anticlockwise order):" << endl;
	for(int i=0;i<2*N;i+=2) {
		cout << "\tVertex " << (i/2+1) << " : ";
		cin >> points[i] >> points[i+1];
	}	
	points[2*N] = points[0];
	points[2*N+1] = points[1];
	return points;
}

int dot(int x0, int y0, int x1, int y1) {
	return (x0*x1 + y0*y1); 
}

int dot(float x0, float y0, int x1, int y1) {
	return (x0*x1 + y0*y1); 
}

int cross(int x0, int y0, int x1, int y1) {
	return (x0*y1 - y0*x1); 
}

int Pt(int P0, int P1, double t) {
	return (int) round(P0+t*(P1-P0));
}

void Clip(int x0, int y0, int x1, int y1, int N, int* vrtx) {
	int Nx, Ny;
	int Dx = x1-x0;
	int Dy = y1-y0;
	float PEx, PEy;
	double tL = 1, tU = 0;
	double t;
	if(Dx == 0 && Dy == 0) 
		return;
	for(int i=0;i<(2*N);i+=2) {
		cout << "i:" << i << " " << "vrtx:" << vrtx[i] << " " << vrtx[i+1] << " " << vrtx[i+2] << " " << vrtx[i+3] << endl;
		Nx = vrtx[i+1]-vrtx[i+3]; //-dy = Nx
		Ny = vrtx[i+2]-vrtx[i];	//dx = Ny
		
		PEx = (vrtx[i+2]+vrtx[i])/2;
		PEy = (vrtx[i+3]+vrtx[i+1])/2;
		
		cout << "Nx:" << Nx << "  Ny:" << Ny << endl;
		cout << "x0-PEx:" << x0-PEx << "  y0-PEy:" << y0-PEy << endl;
		
		assert(!(Nx == 0 && Ny == 0)); //!!!!N = 0?
		
		int DN = dot(Dx, Dy, Nx, Ny); // D.N
		cout << DN << " " << dot(x0-PEx, y0-PEy, Nx, Ny) << endl;
		if(DN != 0) {
			t = (dot(x0-PEx, y0-PEy, Nx, Ny))/-((double) DN);
			cout << t << endl;
			if(DN > 0) {
				if(t<tL)
					tL = t;
			}
			else {
				if(t>tU)
					tU = t;
			}
		}
		cout << tL << " " << tU << endl;
	}
	if(tL>=tU)
	{
		if(tU <= 1 && tL <= 1 && tU >=0 && tL >= 0) {
			int xL = Pt(x0, x1, tL);
			int yL = Pt(y0, y1, tL);
			int xU = Pt(x0, x1, tU);
			int yU = Pt(y0, y1, tU);
			DDAline(xL, yL, xU, yU, BLUE);
		}
		else
			DDAline(x0, y0, x1, y1, BLUE);
	}
}

int main(void) {
	int N;
	cout << "Enter no. of vertices:";
	cin >> N;
	int* points=inputPoly(N);
	
	int x0[3], y0[3], x1[3], y1[3];
	for(int i=0;i<3;i++) {
		cout << "Enter coordinates of line" << (i+1) << " :-" << endl << "\tx0 y0:";
		cin >> x0[i] >> y0[i];
		cout << "\tx1 y1:";
		cin >> x1[i] >> y1[i];
	}
	
	int gd,gm;
	
	detectgraph(&gd,&gm);
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	
    cleardevice();
    setbkcolor(BLACK);
	
	grid();
	
	drawBlockPoly(N+1,points, YELLOW);
	for(int i=0;i<3;i++) {
		
		DDAline(x0[i], y0[i], x1[i], y1[i], WHITE);
		
		Clip(x0[i], y0[i], x1[i], y1[i], N, points);
	}
	
	delete points;
	getch();
	closegraph();
	return 0;
}


