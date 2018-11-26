#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>

void plot(float,float,float,float,int);

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
	return;
}
void grid()
{
	int i;
	setcolor(8);
    for(i=0;i<640;i+=10)
	{
		if(i==320)
	    	setcolor(12);
		line(i,0,i,480);
		if(i==320)
	    	setcolor(8);
    }
    for(i=0;i<480;i+=10)
	{
		if(i==240)
	    	setcolor(12);
		line(0,i,640,i);
		if(i==240)
	    	setcolor(8);
    }
}

void brcircle(int r,int xc,int yc,int cl)
{
	int x,y,d,del,del1;
	x=0;
	y=r;

	d=2*(1-r);
	
	while(x<=r&&y>=0){
		plot(xc+x,yc+y,1,-1,cl);
		plot(xc+x,yc-y,1,1,cl);
		plot(xc-x,yc+y,-1,-1,cl);
		plot(xc-x,yc-y,-1,1,cl);
		if(d<0){
			del=2*(d+y)-1;
			if(del<=0){
				x++;
				d+=2*x+1;
			}
			else{
				x++;
				y--;
				d+=2*(x-y+1);
			}
		}
		else if(d>0){
			del1=2*(d-x)-1;
			if(del1<=0){
				x++;
				y--;
				d+=2*(x-y+1);
			}
			else{
				y--;
				d+=1-2*y;
			}
		}
		else{
			x++;
			y--;
			d+=2*(x-y+1);
		}
	}
}

int main(){
    int gd=DETECT,gm,i,j,k,sign;
    int r,xc,yc;

    /*printf("\nEnter coordinate of center of circle: ");
    scanf("%d%d",&xc,&yc);
    printf("\nEnter radius of circle: ");
    scanf("%d",&r);*/

    initgraph(&gd,&gm,"c:/tc/bgi");
    cleardevice();
    setbkcolor(15);
	
	grid();

    brcircle(5,-10,5,1);
    brcircle(5,0,5,8);
    brcircle(5,10,5,4);
	brcircle(5,-5,0,14);
	brcircle(5,5,0,2);
    getch();
    closegraph();
    return 0;
}

void plot(float x,float y,float dx,float dy,int col){
	int k,j;
	if(dx>0&&dy>0)
		for(k=320+x*10+1;k<320+x*10+10;k++){
			for(j=240-y*10-1;j>240-y*10-10;j--){
	   			putpixel(k,j,col);
			}
		}
	else if(dx>0&&dy<0)
		for(k=320+x*10+1;k<320+x*10+10;k++){
			for(j=240-y*10+1;j<240-y*10+10;j++){
	   			putpixel(k,j,col);
			}	
		}
	else if(dx<0&&dy>0)
		for(k=320+x*10-1;k>320+x*10-10;k--){
			for(j=240-y*10-1;j>240-y*10-10;j--){
	   			putpixel(k,j,col);
			}
		}
	else
		for(k=320+x*10-1;k>320+x*10-10;k--){
			for(j=240-y*10+1;j<240-y*10+10;j++){
	   			putpixel(k,j,col);
			}	
		}
	return ;
}
