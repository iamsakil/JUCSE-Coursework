#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<iostream>

#define XORIGIN 250
#define YORIGIN 300
#define XSTART 50
#define YSTART 50
#define HEIGHT 600
#define WIDTH 450
#define BOUNDARY_VALUE 8
#define NEW_VALUE 10
#define MAX 10000
#define DELAY 10000
using namespace std;

typedef struct pix{
	int x;
	int y;
} pixel;

class stack{
	pixel st[MAX];
	int top;

	public:
		stack(){
			top=-1;
		}
		void push(pixel p){
			if(top==MAX-1){
				cout<<"Stack Overflow!"<<endl;
				return;
			}
			st[++top]=p;
		}
		pixel pop(){
			return st[top--];
		}
		int stacklen(){
			return (top+1);
		}
		int empty(){
			if(top==-1)
				return 1;
			return 0;
		}
};

void draw_line(int,int,int,int);
void seed_fill(pixel);
int sign(int n){
	if(n>0)
		return 1;
	else if(n==0)
		return 0;
	else
		return -1;
}
void fillpixel(int x,int y,int col){
	int x1_actual,y1_actual,x2_actual,y2_actual;
	x1_actual=YORIGIN+(5*x);
	y1_actual=XORIGIN-(5*y);
	x2_actual=x1_actual-5;
	y2_actual=y1_actual+5;
	setfillstyle(1,col);
	bar(x1_actual,y1_actual,x2_actual,y2_actual);

}

int getpixelcolor(pixel p){
	int x1_actual,y1_actual;
	x1_actual=YORIGIN+(p.x*5)-2;
	y1_actual=XORIGIN-(p.y*5)+2;
	return getpixel(x1_actual,y1_actual);
}

int main(){
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	int row,col;
	setbkcolor(12);
	for(row=YSTART;row<=HEIGHT;row+=5){
		if(row==YORIGIN){
			setcolor(15);
			setlinestyle(0,0,3);
		}
		else if(row%50==0){
			setcolor(7);
			setlinestyle(0,0,3);
		}
		else{
			setcolor(7);
			setlinestyle(0,0,1);
		}
		line(row,XSTART,row,WIDTH);
	}
	for(col=XSTART;col<=WIDTH;col+=5){
		if(col==XORIGIN){
			setcolor(15);
			setlinestyle(0,0,3);
		}
		else if(col%50==0){
			setcolor(7);
			setlinestyle(0,0,3);
		}
		else{
			setcolor(7);
			setlinestyle(0,0,1);
		}
		line(YSTART,col,HEIGHT,col);
	}
	setcolor(8);

	/*
	// SQUARE
	draw_line(-10,10,10,10);
	draw_line(-10,10,-10,-10);
	draw_line(-10,-10,10,-10);
	draw_line(10,10,10,-10);
	*/

	/*
	// HEXAGON
	draw_line(-10,10,10,10);
	draw_line(-10,-10,10,-10);
	draw_line(-10,10,-20,0);
	draw_line(-10,-10,-20,0);
	draw_line(20,0,10,10);
	draw_line(20,0,10,-10);
	*/
	/*
	draw_line(0,30,15,15);
	draw_line(15,15,15,-15);
	draw_line(15,-15,0,-30);
	draw_line(0,-30,-15,-15);
	draw_line(-15,-15,-15,15);
	draw_line(-15,15,0,30);
	*/

	/*
	draw_line(0,25,10,10);
	draw_line(10,10,15,20);
	draw_line(15,20,0,-15);
	draw_line(0,-15,-15,20);
	draw_line(-20,20,-5,10);
	draw_line(-5,10,0,25);
	*/

	/*
	draw_line(-5,25,15,25);
	draw_line(15,25,15,5);
	draw_line(15,5,5,5);
	draw_line(5,5,5,-25);
	draw_line(5,-25,-5,-25);
	draw_line(-5,-25,-5,25);
	*/

	draw_line(0,30,-35,-10);
	draw_line(-35,-10,35,-10);
	draw_line(35,-10,0,30);
	draw_line(-10,10,10,10);
	draw_line(10,10,10,-5);
	draw_line(10,-5,-10,-5);
	draw_line(-10,-5,-10,10);

	pixel seed={10,12};
	seed_fill(seed);
	getch();
	closegraph();
}
void draw_line(int x1,int y1,int x2,int y2){
	int i,err,interchange;
	int cur_x=x1;
	int cur_y=y1;
	int del_x=fabs(x2-x1);
	int del_y=fabs(y2-y1);
	int sx=sign(x2-x1);
	int sy=sign(y2-y1);
	if(del_y>del_x){
		int temp=del_y;
		del_y=del_x;
		del_x=temp;
		interchange=1;
	}
	else
		interchange=0;
	err=2*del_y-del_x;
	for(i=1;i<=del_x;i++){
		fillpixel(cur_x,cur_y,BOUNDARY_VALUE);
		while(err>0){
			if(interchange==1)
				cur_x=cur_x+sx;
			else
				cur_y=cur_y+sy;
			err=err-2*del_x;
		}
		if(interchange==1)
			cur_y=cur_y+sy;
		else
			cur_x=cur_x+sx;
		err=err+2*del_y;
	}
}
void seed_fill(pixel seed){
	int maxlen=0;
	stack st;
	st.push(seed);
	//int count=0;
	while(!st.empty()){
		pixel curr=st.pop();
		///*
		double c=-DELAY;
		for(;c<=DELAY;c+=0.01);
		//*/
		fillpixel(curr.x,curr.y,NEW_VALUE);
		int savex=curr.x;
		curr.x=curr.x+1;
		while(getpixelcolor(curr)!=BOUNDARY_VALUE){
			///*
			double c=-DELAY;
			for(;c<=DELAY;c+=0.1);
			//*/
			fillpixel(curr.x,curr.y,NEW_VALUE);
			curr.x=curr.x+1;
		}
		int xright=curr.x-1;
		curr.x=savex;
		curr.x=curr.x-1;
		while(getpixelcolor(curr)!=BOUNDARY_VALUE){
			double c=-DELAY;
			for(;c<=DELAY;c+=0.01);

			fillpixel(curr.x,curr.y,NEW_VALUE);
			curr.x=curr.x-1;
		}
		int xleft=curr.x+1;
		curr.x=savex;
		//
		curr.x=xleft;
		curr.y=curr.y+1;
		while(curr.x<=xright){
			int pflag=0;
			while(getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE && curr.x<xright){
				if(pflag==0)
					pflag=1;
				curr.x=curr.x+1;
			}
			if(pflag==1){
				if(curr.x==xright && getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE)
					st.push(curr);
				else{
					pixel temp={curr.x-1,curr.y};
					st.push(temp);
				}
				pflag=0;
			}
			int xenter=curr.x;
			while((getpixelcolor(curr)==BOUNDARY_VALUE || getpixelcolor(curr)==NEW_VALUE) && curr.x<xright)
				curr.x=curr.x+1;
			if(curr.x==xenter)
				curr.x=curr.x+1;
		}
		curr.x=xleft;
		curr.y=curr.y-2;
		while(curr.x<=xright){
			int pflag=0;
			while(getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE && curr.x<xright){
				if(pflag==0)
					pflag=1;
				curr.x=curr.x+1;
			}
			if(pflag==1){
				if(curr.x==xright && getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE)
					st.push(curr);
				else{
					pixel temp={curr.x-1,curr.y};
					st.push(temp);
				}
				pflag=0;
			}
			int xenter=curr.x;
			while((getpixelcolor(curr)==BOUNDARY_VALUE || getpixelcolor(curr)==NEW_VALUE) && curr.x<xright)
				curr.x=curr.x+1;
			if(curr.x==xenter)
				curr.x=curr.x+1;
		}
		if(maxlen<st.stacklen())
			maxlen=st.stacklen();

	}
	cout<<"Maximum length of stack: "<<maxlen<<endl;
}

