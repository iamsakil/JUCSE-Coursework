#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void lineplot(int x, int y, int size=10)
{
    int xp=640/2+size*x , yp=480/2-size*y;
	setfillstyle(SOLID_FILL,BLUE);
	bar(xp+1,yp-size+1,xp+size+1,yp+1);
    //putpixel(x+(getmaxx()/2), (getmaxy()/2)-y, WHITE);
}

int sign(int n1, int n2)
{
    if(n1==n2)
	return 0;
    if(n1<n2)
	return 1;
    else
	return -1;
}

void DDAline(int X0, int Y0, int X1, int Y1)
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
        lineplot (X,Y);  // put pixel at (X,Y)
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


int main()
{
	
	int n,i,j,k,gd,gm,dy,dx;
	int x,y,temp;
	int a[20][2],xi[20];
	float slope[20];
	
	int polyx[7],polyy[7];
    
    polyx[0]=0;polyy[0]=2;
	polyx[1]=6;polyy[1]=7;
	polyx[2]=13;polyy[2]=-7;
	polyx[3]=-13;polyy[3]=-7;
	polyx[4]=-6;polyy[4]=7;
	//polyx[5]=-7;polyy[5]=7;
	polyx[5]=polyx[0];polyy[5]=polyy[0];    
    
    n=5;
    
	for(i=0;i<=n;i++)
	{
    	a[i][0]=polyx[i];
    	a[i][1]=polyy[i];
	}
	
	
	detectgraph(&gd,&gm);
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	
    cleardevice();
    setbkcolor(BLACK);
	
	grid();

	
	/*- draw polygon -*/
	
	for(i=0;i<n;i++) 
	{
		DDAline(a[i][0],a[i][1],a[i+1][0],a[i+1][1]);
	}
		
	for(i=0;i<n;i++)
		{
		dy=a[i+1][1]-a[i][1];
		dx=a[i+1][0]-a[i][0];
		
		if(dy==0) slope[i]=1.0;
		if(dx==0) slope[i]=0.0;
		
		if((dy!=0)&&(dx!=0)) //- calculate inverse slope  
		{
			slope[i]=(float) dx/dy;
		}
	}
	
	for(y=-30;y<30;y++)
	{
		k=0;
		for(i=0;i<n;i++)
		{
			
			if( ((a[i][1]<=y)&&(a[i+1][1]>y)) || ((a[i][1]>y)&&(a[i+1][1]<=y)) )
			{
				xi[k]=(int)(a[i][0]+slope[i]*(y-a[i][1]));
				k++;
			}
		}
		
		for(j=0;j<k-1;j++) //- Arrange x-intersections in order -
			for(i=0;i<k-1;i++)
			{
				if(xi[i]>xi[i+1])
				{
					temp=xi[i];
					xi[i]=xi[i+1];
					xi[i+1]=temp;
				}
			}
		for(i=0;i<k;i+=2)
		{
			delay(500);
			DDAline(xi[i],y,xi[i+1],y);
			//getch();
		}
		
	}
	getch();
	return 0;
}
