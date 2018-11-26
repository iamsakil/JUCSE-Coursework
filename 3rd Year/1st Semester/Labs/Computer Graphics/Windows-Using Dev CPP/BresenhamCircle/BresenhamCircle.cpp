#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>

void plot(float,float,float,float);

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
	return;
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

void brcircle(int r,int xc,int yc)
{
	int x,y,d,del,del1;
	x=0;
	y=r;

	d=2*(1-r);
	
	while(x<=r&&y>=0){
		plot(xc+x,yc+y,1,-1);
		plot(xc+x,yc-y,1,1);
		plot(xc-x,yc+y,-1,-1);
		plot(xc-x,yc-y,-1,1);
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

    printf("\nEnter coordinate of center of circle: ");
    scanf("%d%d",&xc,&yc);
    printf("\nEnter radius of circle: ");
    scanf("%d",&r);

    initgraph(&gd,&gm,"c:/tc/bgi");
    cleardevice();
    setbkcolor(15);
	
	grid();

   brcircle(r,xc,yc);

    getch();
    closegraph();
}

void plot(float x,float y,float dx,float dy){
	int k,j;
	if(dx>0&&dy>0)
	for(k=320+x*10+1;k<320+x*10+10;k++){
	for(j=240-y*10-1;j>240-y*10-10;j--){
	   putpixel(k,j,11);
	}}
	else if(dx>0&&dy<0)
	for(k=320+x*10+1;k<320+x*10+10;k++){
	for(j=240-y*10+1;j<240-y*10+10;j++){
	   putpixel(k,j,11);
	}}
	else if(dx<0&&dy>0)
	for(k=320+x*10-1;k>320+x*10-10;k--){
	for(j=240-y*10-1;j>240-y*10-10;j--){
	   putpixel(k,j,11);
	}}
	else
	for(k=320+x*10-1;k>320+x*10-10;k--){
	for(j=240-y*10+1;j<240-y*10+10;j++){
	   putpixel(k,j,11);
	}}
	return;
}
