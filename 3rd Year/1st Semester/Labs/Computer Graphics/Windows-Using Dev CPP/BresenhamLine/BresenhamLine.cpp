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

void brline(int x_1,int y_1,int x_2,int y_2){
	int s=0;	
	int x,y,dx,dy,d,signx,signy;

	x=x_1;
	y=y_1;

	dx=x_2-x_1;
	dy=y_2-y_1;
	
	if(abs(dx)<abs(dy)){
		swap(&x_1,&y_1);
		swap(&x_2,&y_2);
		swap(&dx,&dy);
		s=1;						
	}
	
	signy=dy/abs(dy);
	signx=dx/abs(dx);
	
	d=2*(dy)-signy*signx*dx;
	
	if(signx==1){
		while(x<x_2){
			if(s==0){
				plot(x,y,dx,dy);
			}
			else{
				plot(y,x,dy,dx);
			}
		
			if(signy*d>=0){
				x=x+signx*1;
				y=y+signy*1;
				d+=2*(dy-signy*signx*dx);
			}
			else{
				x=x+signx*1;
				d+=2*dy;
			}
		}
	}
	else{
		while(x>x_2){
			if(s==0){
				plot(x,y,dx,dy);
			}
			else{
				plot(y,x,dy,dx);
			}
	
			if(signy*d>=0){
				x=x+signx*1;
				y=y+signy*1;
				d+=2*(dy-signy*signx*dx);
			}
			else{
				x=x+signx*1;
				d+=2*dy;
			}
		}
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

int main(){
    int gd=DETECT,gm,i,j,k,sign;
    float x1,y1,x2,y2;

    printf("Enter the value of x1 : ");
    scanf("%f",&x1);
    printf("Enter the value of y1 : ");
    scanf("%f",&y1);
    printf("Enter the value of x2 : ");
    scanf("%f",&x2);
    printf("Enter the value of y1 : ");
    scanf("%f",&y2);

    initgraph(&gd,&gm,"c:/tc/bgi");
    cleardevice();
    setbkcolor(15);
	
	grid();

   brline(x1,y1,x2,y2);

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
