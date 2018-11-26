#include<bits/stdc++.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
#define N 3
using namespace std;

void mu(double mat1[][N], double mat2[][N], double r[][N])
{
    int i, j, k;
    double res[N][N];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < N; k++)
                res[i][j] += mat1[i][k]*mat2[k][j];
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
        	r[i][j]=res[i][j];
        }
    }
}

void identity(double a[][N])
{
	int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i!=j)
   				a[i][j] = 0;
   			else
			    a[i][j] = 1;
        }
    }
}

//choice=0 is about x-axis
void reflection( double a[][N] , int choice=0 )
{
	identity(a);	
    if(choice==0)
    	a[1][1]=-1;
    else
		a[0][0]=-1;	
}

//choice=0 if in degrees
void rotation( double a[][N], double deg, int choice=0)
{
	double rad=deg;
	if (choice==0)
		rad= deg*3.141592/180.0;
	identity(a);
	a[0][0]=cos(rad);
	a[0][1]=-1*sin(rad);
	a[1][0]=sin(rad);
	a[1][1]=cos(rad);
}

void shear( double a[][N], double x,double y)
{
	identity(a);
	a[0][1]=y;
	a[1][0]=x;
}

void translation( double a[][N], double x,double y)
{
	identity(a);
	a[2][0]=x;
	a[2][1]=y;
}

void scaling( double a[][N], double m)
{
	identity(a);
	a[0][0]=m;
	a[1][1]=m;
}


void reflect_around_line(int a[][2], int n,double m, double c)
{
	int i;
	double trn[N][N],rot[N][N],ref[N][N],rotb[N][N],trnb[N][N],mul[N][N],pt[N][N];
	double deg;
	deg=atan(m);
	translation(trn,0,-1.0*c);
	rotation(rot,deg,1);
	reflection(ref);
	rotation(rotb,-1.0*deg,1);
	translation(trnb,0,c);
	mu(trn,rot,mul);
	mu(mul,ref,mul);
	mu(mul,rotb,mul);
	mu(mul,trnb,mul);
	for(i=0;i<n;i++) 
	{
		identity(pt);
		pt[0][0]=a[i][0];
		pt[0][1]=a[i][1];
		pt[0][2]=1;
		mu(pt,mul,pt);
		a[i][0]=round(pt[0][0]);
		a[i][1]=round(pt[0][1]);
	}
	a[n][0]=a[0][0];
	a[n][1]=a[0][1];
}

void shear_and_bend(int a[][2], int n,double x, double y)
{
	int i;
	double mul[N][N],pt[N][N];
	shear(mul,x,y);
	for(i=0;i<n;i++) 
	{
		identity(pt);
		pt[0][0]=a[i][0];
		pt[0][1]=a[i][1];
		pt[0][2]=1;
		mu(pt,mul,pt);
		a[i][0]=round(pt[0][0]);
		a[i][1]=round(pt[0][1]);
	}
	a[n][0]=a[0][0];
	a[n][1]=a[0][1];
}

void scale_up(int a[][2], int n,double m)
{
	int i;
	double mul[N][N],pt[N][N];
	scaling(mul,m);
	for(i=0;i<n;i++) 
	{
		identity(pt);
		pt[0][0]=a[i][0];
		pt[0][1]=a[i][1];
		pt[0][2]=1;
		mu(pt,mul,pt);
		a[i][0]=round(pt[0][0]);
		a[i][1]=round(pt[0][1]);
	}
	a[n][0]=a[0][0];
	a[n][1]=a[0][1];
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
    	delay(10);
        putpxl (X,Y,colour);  // put pixel at (X,Y)
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step         // for visualization of line-
                             // generation step by step
    }
}

void grid(){
	int i;
	    setcolor(8);
    for(i=0;i<640;i+=10)
	{
		line(i,0,i,480);
	}
    for(i=0;i<480;i+=10)
	{
		line(0,i,640,i);
	}
    DDAline(0,28,0,-26,WHITE);
    DDAline(31,0,-32,0,WHITE);

    
}

int getpxl(int x, int y,int size=10)
{
	int xp=640/2+size*x , yp=480/2-size*y;
	return getpixel(xp+6,yp-4);
}


int main()
{
	
	int n,i,gd,gm,flag=0;
	double shx,shy,m,c,x1,y1,x2,y2;
	int a[20][2];
	cout<<"Enter the number of sides of the polygon: ";
	cin>>n;
	
	for(i=0;i<n;i++) 
	{
		cout<<"Enter "<<i+1<<"th vertice coordinate (-30,30) as x y : ";
    	cin>>a[i][0]>>a[i][1];
	}
	
	a[n][0]=a[0][0];
	a[n][1]=a[0][1];
	
	/*
	cout<<"Enter shear x: ";
	cin>>shx;
	cout<<"enter shear y: ";
	cin>>shy;
	*/
	
	
	cout<<"enter line (y=mx+c) about to rotate m c:";
	cin>>m>>c; 
	cout<<"Do you want to draw the sepearting line (1/0) :";
	cin>>flag;
	if(flag==1)
	{	
		cout<<"Enter the coordinates of the separating line x1 y1 x2 y2: ";
		cin>>x1>>y1>>x2>>y2;
	}
	
	/*
	cout<<"enter scale factor: ";
	cin>>m;
	*/
	
	detectgraph(&gd,&gm);
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	
    cleardevice();
    setbkcolor(BLACK);
	
	grid();

	
	/*- draw polygon -*/
	
	for(i=0;i<n;i++) 
	{
		DDAline(a[i][0],a[i][1],a[i+1][0],a[i+1][1],GREEN);
	}
	
	if (flag==1)
		DDAline(x1,y1,x2,y2,BLUE);
	
	reflect_around_line(a,n,m,c);
	
	//shear_and_bend(a,n,shx,shy);
	//scale_up(a,n,m);
	
	for(i=0;i<n;i++) 
	{
		DDAline(a[i][0],a[i][1],a[i+1][0],a[i+1][1],YELLOW);
	}
	
	getch();
	return 0;
}

/*
4
0 4
0 8
8 8
8 4
-1 0
1
13 -13 -13 13
*/

