#include<bits/stdc++.h>
#include<conio.h>
#include<graphics.h>
//#include<math.h>
using namespace std;
struct point
{
  float x,y;
};

int xmax,ymax,dis;
//int fl=0;
void displayGrid(){
	setcolor(7);
    int i;
    for(i = 0; i <=xmax; i+=dis)
    {
	line(i, 0, i, ymax);
    }
    for(i=0;i<=ymax;i+=dis) line(0,i,xmax,i);
	//setcolor(14);
	//line((xmax)/2, 0, (xmax)/2, ymax);
	//line(0,(ymax)/2, xmax,(ymax)/2);
}

void putpixe(int x,int y,int c){
    //	setfillstyle(SOLID_FILL,c); //setcolor(RED);
    //	putpixel(x,y,c);//to fill inside
	//putpixel(x-1,y,c);putpixel(x+1,y,c);putpixel(x,y+1,c);putpixel(x,y-1,c);
   //	floodfill(x,y,7);
	//floodfill(x,y+1,7);
	//floodfill(x+1,y,7);
	int xm=x/dis;
	xm=xm*dis;
	int ym=y/dis;
	ym=ym*dis;
	for(int i=xm;i<(xm+dis);i++)
	{
		for(int j=ym;j<(ym+dis);j++)
		{
		   //	if(fl==1)
		   //	{
		   //		if(getpixel(i,j)!=RED)
		   //			putpixe(i,j,c);
		   //	}
		   //	else
			     putpixel(i,j,c);
		}
	}
}

void DDA(int X0, int Y0, int X1, int Y1,int c)
{

    int dx = X1 - X0;
    int dy = Y1 - Y0;
    if(Y1==Y0)
    {
	if(X0>X1)
	{
	      int t=X0; X0=X1; X1=t;
	}
	for(int i=X0;i<=X1;i++)
	{
		putpixe(i,Y0,c);
	}
	return;
    }
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
	putpixe(X,Y,c);  // put pixel at (X,Y)
	X += Xinc;
	Y += Yinc;
    }
}

int getpixe(int x,int y)
{
	int xm=x/dis;
	xm=xm*dis;
	int ym=y/dis;
	ym=ym*dis;
	for(int i=xm-4;i<=(xm+dis+4);i++)
	{
		for(int j=ym-4;j<=(ym+dis+4);j++)
		{
			if(getpixel(i,j)==RED)
			  return 1;
		}
	}
	return 0;
}

void clip(point pol[10], point p1, point p2, int n)
{
/*
  setcolor(BLUE);
  DDA(320,0,320,480,RED);
  setcolor(RED);
  DDA(0,240,640,240,RED);
*/
 // setcolor(YELLOW);
  for(int i=0;i<n;i++)
  {
     DDA(pol[i].x,pol[i].y,pol[i+1].x,pol[i+1].y,RED);
  }
  DDA(p1.x,p1.y,p2.x,p2.y,YELLOW);
  getch();
  float t_enter=0,t_leave=1;
  for(int i=0;i<n;i++)
  {
    point n,pei;
    pei=pol[i];
    n.x=(pol[i+1].y-pol[i].y);
    n.y=(pol[i+1].x-pol[i].x);
    float num,den;
    num = n.x*(pei.x-p1.x) - n.y*(pei.y-p1.y);
    den = n.x*(p2.x-p1.x) + n.y*(p1.y-p2.y);
    float t;
    if(den!=0)
      t= num*1.0/den;

    if(t>=0 && t<=1)
    {
      if(den<0)
      {
	if(t>t_enter)
	  t_enter = t;
      }
      else if(den>0)
      {
	if(t<t_leave)
	  t_leave = t;
      }
    }
  }

  point pi,pl;
  pi.x=p1.x+(p2.x-p1.x)*t_enter;
  pi.y=p1.y+(p2.y-p1.y)*t_enter;
  pl.x=p1.x+(p2.x-p1.x)*t_leave;
  pl.y=p1.y+(p2.y-p1.y)*t_leave;
 // fl=1;
  if(getpixe(pi.x,pi.y)==1 || getpixe(pl.x,pl.y)==1)
     DDA(pi.x,pi.y,pl.x,pl.y,GREEN);
}


int main()
{
  int gd = DETECT, gm;
  initgraph(&gd,&gm,"..\\bgi");
  xmax=900;ymax=750;dis=5;
  cout<<"Enter the no. of vertices of clipping window : ";
  int n,i;
  cin>>n;

  point pol[10];
  cout<<"Enter the vertices in clockwise order \n";
  for( i=0;i<n;i++)
  {
    cout<<" Enter vertex : ";
    cin>>pol[i].x>>pol[i].y;
  }
  pol[i].x=pol[0].x;
  pol[i].y=pol[0].y;

  cout<<"Enter the end points of the line : ";
  point p1,p2;
  cin>>p1.x>>p1.y>>p2.x>>p2.y;

  int t;
  if(p1.x>p2.x)
  {
    t=p1.x;
    p1.x=p2.x;
    p2.x=t;
    t=p1.y;
    p1.y=p2.y;
    p2.y=t;
  }

  cleardevice();
  displayGrid();

  clip(pol,p1,p2,n);
  getch();
  closegraph();
  return 0;
}
