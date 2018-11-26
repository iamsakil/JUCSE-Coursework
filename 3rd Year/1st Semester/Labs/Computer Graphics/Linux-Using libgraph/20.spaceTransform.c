/*
*   3D TRANSFORMATIONS AND PROJECTIONS
*   provide a .kpg file as input
*  
*   translation -t:x,y,z
*   rotation    -r:x,y,z,a,b,c,0
*   reflection  -m:x,y,z,a,b,c
*   scaling     -s:x,y,z
*   zoom        -z:h
*   perspective -p:x,y,z,a,b,c
*   axonometric -x:x,y,z,a,b,c
*   animate     -a:n,d
*   
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <graphics.h>
#include "0.kpgparse.c"

VGRAPH objects;
int aniFlag, num_objs=0;
clock_t last=0, now;
double dely=0;

typedef struct
{
    double v[4][4];
}TRANSFORMATION;

TRANSFORMATION multiply(TRANSFORMATION R, TRANSFORMATION T)
{
    int i, j, k;
    TRANSFORMATION F;
    for(i=0; i<4; ++i)
        for(j=0; j<4; ++j)
        {
            F.v[i][j]=0;
            for(k=0; k<4; ++k)
                F.v[i][j] += R.v[i][k]*T.v[k][j];
        }
    return F;
}

TRANSFORMATION axes[6] = {{{ {  1,  0,  0, 0}, //x-axis
                             { -1,  0,  0, 0},
                             {  0,  0,  0, 0},
                             {  0,  0,  0, 0}, }},
                          {{ {  0,  1,  0, 0}, //y-axis
                             {  0, -1,  0, 0},
                             {  0,  0,  0, 0},
                             {  0,  0,  0, 0}, }},
                          {{ {  0,  0,  1, 0}, //z-axis
                             {  0,  0, -1, 0},
                             {  0,  0,  0, 0},
                             {  0,  0,  0, 0}, }}};
 
void xclip(double x1, double y1, double x2, double y2) //sutherland-cohen clipping
{
    unsigned char code;
    double slope;
    int i, window[4]={-320, 320, -240, 240};
    unsigned char calcEPC(double x, double y) //calculate End Point Code
    {
        unsigned char c=0;
        if(y>240) c+=8; //above t
        if(y<-240) c+=4; //below b
        if(x>320) c+=2; //right of r
        if(x<-320) c+=1; //left of l
        return c;
    }
    code=(calcEPC(x1, y1)<<4) + calcEPC(x2, y2); //calculate end point codes
    if(!code) //trivially visible
    {
        line(320+(int)x1, 240-(int)y1, 320+(int)x2,240-(int)y2);
        return;
    }
    if((code>>4)&code) return; //trivially invisible
    slope=(x1==x2)?0:(double)(y2-y1)/(x2-x1); //calculate slope
    while(code) //while partially visible
    {
        for(i=0; i<4; ++i) //each window edge
        {
            if(((code>>(4+i))&1)==((code>>i)&1)) continue; //does not cross the edge
            if(!((code>>(4+i))&1)) { int t=x1; x1=x2; x2=t;  //(x1,y2) is inside relative to edge
                                         t=y1; y1=y2; y2=t;
                                         code=((code&15)<<4)+(code>>4); } //so swap
            if(x1!=x2 && i<2) //left and right edges
            {
                y1+=slope*(window[i]-x1); //find intersection
                x1=window[i];
            }
            else if(y1!=y2 && i>1) //top and bottom edges
            {
                x1+=slope?(window[i]-y1)/slope:0; //find intersection
                y1=window[i];
            }
            code=(calcEPC(x1, y1)<<4)+(code&15); //update end point codes
            if(!code) break; //totally visible
            if((code>>4)&code) return; //totally invisible
        }
    }
    line(320+(int)x1, 240-(int)y1, 320+(int)x2,240-(int)y2);
}

void drawAxes(TRANSFORMATION P)
{
    int i;
    setcolor(WHITE);
    bar(0, 0, 640, 480);
    setcolor(LIGHTGRAY);
    for(i=0; i<3; ++i)
    {
        axes[3+i] = multiply(axes[i], P);
        axes[3+i].v[0][0]/=axes[3+i].v[0][3];
        axes[3+i].v[0][1]/=axes[3+i].v[0][3];
        axes[3+i].v[1][0]/=axes[3+i].v[1][3];
        axes[3+i].v[1][1]/=axes[3+i].v[1][3];
        xclip( axes[3+i].v[0][0], axes[3+i].v[0][1],
               axes[3+i].v[1][0], axes[3+i].v[1][1]  );
    }
    setcolor(BLACK);
}

void loadObjects(FILE *kpg, TRANSFORMATION P)
{
    int gd=DETECT,gm; //initialize graphics
	initgraph(&gd, &gm, NULL);
    objects=expectGraph(kpg); //load picture from file
    fclose(kpg);
    drawAxes(P);
}

void display(TRANSFORMATION T, TRANSFORMATION P)
{
    int i, j;
    VGRAPH temp;
    temp.n=objects.n;
	temp.vertices = (double**)malloc(temp.n*sizeof(double*));
    temp.vertices[0] = (double*)malloc(temp.n*3*sizeof(double));
    while( ((now=clock()) - last)*1.0/CLOCKS_PER_SEC < dely); //animate with time delay
    last=now;
    if(aniFlag>0) drawAxes(P); //animate
    else if(!aniFlag) //no animation, show original
    {
        setcolor(RED);
        aniFlag=-1;
    }
    else setcolor(BLUE); //no animation, show transformed object
    for(i=0; i< objects.n; ++i)
    {
    	int ii, jj;
    	temp.vertices[i] = temp.vertices[0] + 3*i;
        TRANSFORMATION X = {{ {objects.vertices[i][0], objects.vertices[i][1], objects.vertices[i][2], 1},
                              {     		  		0,  	                0,                      0, 0},
                              {     				0, 			            0,                      0, 0},
                              {     			 	0, 			            0,                      0, 0}  }};
        X = multiply(X, T);
        objects.vertices[i][0] = X.v[0][0]/X.v[0][3]; //update picture
        objects.vertices[i][1] = X.v[0][1]/X.v[0][3];
        objects.vertices[i][2] = X.v[0][2]/X.v[0][3];
        X = multiply(X, P);
        temp.vertices[i][0] = X.v[0][0]/X.v[0][3]; //project picture
        temp.vertices[i][1] = X.v[0][1]/X.v[0][3];
        temp.vertices[i][2] = X.v[0][2]/X.v[0][3];
    }
    for(i=0; i<objects.n; ++i)
        for(j=0; j<i; ++j)
	    {
	        if(objects.adj[i][j]==1) //output
	            xclip(temp.vertices[i][0], temp.vertices[i][1],
	                  temp.vertices[j][0], temp.vertices[j][1]);
	    }
	free(temp.vertices[0]); //free memory
    free(temp.vertices);
}

void menu(int *argc, char ***argv)
{
    int choice;
    double x, y, z, other;
    char **temp;
    printf("Enter your choice:\n1)Scaling\n2)Shearing\n3)Rotation");
    printf("\n4)Reflection\n5)Translation\n6)Exit : ");
    scanf("%d", &choice);
    *argc=4;
    temp = (char**)malloc(4*sizeof(char*));
    temp[0]=(*argv)[0];
    temp[1]=(*argv)[1];
    *argv=temp;
    (*argv)[2] = (char*)malloc(sizeof(char)*20);
    strcpy((*argv)[2], "-a:10,0.1");
    (*argv)[3] = (char*)malloc(sizeof(char)*100);
    switch(choice)
    {
        case 1:
            printf("Enter X Scale Factor : "); scanf("%lf", &x);
            printf("Enter Y Scale Factor : "); scanf("%lf", &y);
            printf("Enter Z Scale Factor : "); scanf("%lf", &z);
            sprintf((*argv)[3], "-s:%lf,%lf,%lf", x, y, z);
            break;
        case 2:
            printf("Enter X Shear Factor : "); scanf("%lf", &x);
            printf("Enter Y Shear Factor : "); scanf("%lf", &y);
            printf("Enter Z Shear Factor : "); scanf("%lf", &z);
            sprintf((*argv)[3], "-f:%lf,%lf,%lf", x, y, z);
            break;
        case 3:
            printf("Enter X Center Location : "); scanf("%lf", &x);
            printf("Enter Y Center Location : "); scanf("%lf", &y);
            printf("Enter Rotation Angle : "); scanf("%lf", &other);
            sprintf((*argv)[3], "-r:%lf,%lf,%lf", x, y, other);
            break;
        case 4:
            printf("Reflect About Line...\nEnter Slope : "); scanf("%lf", &x);
            printf("Enter Y Intercept : "); scanf("%lf", &y);
            sprintf((*argv)[3], "-m:%lf,%lf", x, y);
            break;
        case 5:
            printf("Translate Along X Axis : "); scanf("%lf", &x);
            printf("Translate Along Y Axis: "); scanf("%lf", &y);
            printf("Translate Along Z Axis: "); scanf("%lf", &z);
            sprintf((*argv)[3], "-t:%lf,%lf,%lf", x, y, z);
            break;
        default:
            strcpy((*argv)[3], "");
    }
}

int main(int argc, char **argv)
{
	int steps;
	int cnt, i=1;
	FILE *kpg;
	if(argc<2)
	{
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file [options...]\n");
	    return 1;
	}
    kpg = fopen(argv[1], "rx"); //open input file
    if(!kpg)
    {
	    printf("[ ERROR ] Usage : <.kpg>_format_input_file [options...]\n");
	    return 1;
	}
    TRANSFORMATION T = {{ {1, 0, 0, 0},
			              {0, 1, 0, 0},
			              {0, 0, 1, 0},
			              {0, 0, 0, 1} }};
    TRANSFORMATION I = T;
    TRANSFORMATION P = I;
    aniFlag=0;
    if(argc==2) menu(&argc, &argv); //default to menu
    double x, y, z, angle;
    double a, b, c, d, p, q, s;
	while((i++)<argc-1) //parse the arguments
	{
		if(argv[i][0]=='-') //commands start with a '-'
			switch(argv[i][1])
			{
			    case 'a': case 'A': //animation
			        if(sscanf(argv[i]+2, ":%d,%lf", &steps, &dely)==2) //number of steps per operation, time delay per step
			        {
			            aniFlag = 1;
			            loadObjects(kpg, P);
			            display(I, P);
			            getchar();
			            display(T, P);
			        }
			        else printf("LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -A:FRAMES/OP,DELAY\n");
			        break;
			    case 't': case 'T': //translation
			        if(sscanf(argv[i]+2, ":%lf,%lf,%lf", &x, &y, &z)==3) //along x-axis, along y-axis, along z-axis
			        {
			            TRANSFORMATION R = {{ {1, 0, 0, 0}, //translate
			                                  {0, 1, 0, 0},
			                                  {0, 0, 1, 0},
			                                  {x, y, z, 1}  }};
			            if(aniFlag)
			            {
			                R.v[3][0]/=steps; //break into n steps
			                R.v[3][1]/=steps;
			                R.v[3][2]/=steps;
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R, P); //animate
			            }
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else printf("LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -T:X_DISP,Y_DISP,Z_DISP\n");
			        break;
			    case 's': case 'S': //scaling
			        if(sscanf(argv[i]+2, ":%lf,%lf,%lf", &x, &y, &z)==3) //scale x, scale y, scale z
			        {
			            x=x>0?x:-x;
			            y=y>0?y:-y;
			            z=z>0?z:-z;
			            TRANSFORMATION R = {{ { x, 0, 0, 0}, //scale
			                        	      { 0, y, 0, 0},
			                          	      { 0, 0, z, 0},
			                                  { 0, 0, 0, 1}  }};
			            if(aniFlag)
			            {
			                R.v[0][0] = pow(R.v[0][0], 1.0/steps); //break into n steps
			                R.v[1][1] = pow(R.v[1][1], 1.0/steps);
			                R.v[2][2] = pow(R.v[2][2], 1.0/steps);
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R, P); //animate
			            }
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else printf("LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -S:X_SCALE,Y_SCALE,Z_SCALE\n");
			        break;
			    case 'r': case 'R': //rotation
			        if(sscanf(argv[i]+2, ":%lf,%lf,%lf,%lf,%lf,%lf,%lf", &x, &y, &z, &a, &b, &c, &angle)==7)
			                                    //axis of rotation - (position vector x, y, z, direction vector a, b, c), angle of rotation
			        {
			            angle*=3.1415926/180;
			            q = sqrt(a*a+c*c);
			            d = sqrt(a*a+b*b+c*c);
			            TRANSFORMATION T1 = {{ {  1,  0,  0, 0}, //pass axis of rotation through origin
			                            	   {  0,  1,  0, 0},
			                              	   {  0,  0,  1, 0},
			                                   { -x, -y, -z, 1}  }};
			                                   
			            TRANSFORMATION T1_INV = {{ { 1, 0, 0, 0},
			                            	       { 0, 1, 0, 0},
			                              	       { 0, 0, 1, 0},
			                                       { x, y, z, 1}  }};
			            
			            TRANSFORMATION Ry = {{ {  c, 0, a, 0}, //remove x component
			                            	   {  0, q, 0, 0},
			                              	   { -a, 0, c, 0},
			                                   {  0, 0, 0, q}  }};
			                                   
			            TRANSFORMATION Ry_INV = {{ { c, 0, -a, 0},
			                            	       { 0, q,  0, 0},
			                              	       { a, 0,  c, 0},
			                                       { 0, 0,  0, q}  }};

			            TRANSFORMATION Rx = {{ { d,  0, 0, 0}, //remove y component
			                            	   { 0,  q, b, 0},
			                              	   { 0, -b, q, 0},
			                                   { 0,  0, 0, d}  }};
			                                   
			            TRANSFORMATION Rx_INV = {{ { d, 0,  0, 0},
			                            	       { 0, q, -b, 0},
			                              	       { 0, b,  q, 0},
			                                       { 0, 0,  0, d}  }};
			            if(aniFlag) angle/=steps; //break into n steps
			            b = cos(angle);
			            s = sin(angle);
			            TRANSFORMATION R = {{ {  b, s, 0, 0}, //rotate
			                        	      { -s, b, 0, 0},
			                          	      {  0, 0, 1, 0},
			                                  {  0, 0, 0, 1}  }};
						R = multiply(multiply(T1, (a||c)?Ry:I), multiply(Rx, R));
						R = multiply(multiply(R, Rx_INV), multiply((a||c)?Ry_INV:I, T1_INV));
			            if(aniFlag)
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R, P); //animate
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else printf("LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -R:Cx,Cy,Cz,Nx,Ny,Nz,ANGLE\n");
			        break;
			    case 'z': case 'Z': //zooming
			        if(sscanf(argv[i]+2, ":%lf", &s)==1)//homogeneous zoom factor
			        {
			            if(s==0.0)
			            {
			                fprintf(stderr, "LOG [ERROR] : CANNOT DELETE PICTURE!");
			                break;
			            }
			            TRANSFORMATION R = {{ { 1, 0, 0,   0}, //homogeneous scaling
			                            	  { 0, 1, 0,   0},
			                              	  { 0, 0, 1,   0},
			                                  { 0, 0, 0, 1/s}  }};
			            if(s<0)
			            {
			                R.v[0][0]=-R.v[0][0];
			                R.v[1][1]=-R.v[1][1];
			                R.v[2][2]=-R.v[2][2];
			                R.v[3][3]=-R.v[3][3];
			            }
			            if(aniFlag)
			            {
			                R.v[3][3] = pow(R.v[3][3], 1.0/steps); //break into n steps
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R, P); //animate
			            }
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else printf("LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -Z:ZOOM\n");
			        break;

			    case 'm': case 'M': //reflection
			        if(sscanf(argv[i]+2, ":%lf,%lf,%lf,%lf,%lf,%lf", &x, &y, &z, &a, &b, &c)==6)
			                                    //mirror plane - (position vector x, y, z, normal vector a, b, c)
			        {
			            q = sqrt(a*a+c*c);
			            d = sqrt(a*a+b*b+c*c);
			            TRANSFORMATION T1 = {{ {  1,  0,  0, 0}, //pass mirror plane through origin
			                            	   {  0,  1,  0, 0},
			                              	   {  0,  0,  1, 0},
			                                   { -x, -y, -z, 1}  }};
			                                   
			            TRANSFORMATION T1_INV = {{ { 1, 0, 0, 0},
			                            	       { 0, 1, 0, 0},
			                              	       { 0, 0, 1, 0},
			                                       { x, y, z, 1}  }};
			            
			            TRANSFORMATION Ry = {{ {  c, 0, a, 0}, //remove x component
			                            	   {  0, q, 0, 0},
			                              	   { -a, 0, c, 0},
			                                   {  0, 0, 0, q}  }};
			                                   
			            TRANSFORMATION Ry_INV = {{ { c, 0, -a, 0},
			                            	       { 0, q,  0, 0},
			                              	       { a, 0,  c, 0},
			                                       { 0, 0,  0, q}  }};

			            TRANSFORMATION Rx = {{ { d,  0, 0, 0}, //remove y component
			                            	   { 0,  q, b, 0},
			                              	   { 0, -b, q, 0},
			                                   { 0,  0, 0, d}  }};
			                                   
			            TRANSFORMATION Rx_INV = {{ { d, 0,  0, 0},
			                            	       { 0, q, -b, 0},
			                              	       { 0, b,  q, 0},
			                                       { 0, 0,  0, d}  }};

			            TRANSFORMATION R = {{ { 1, 0,  0, 0}, //reflect
			                        	      { 0, 1,  0, 0},
			                          	      { 0, 0, -1, 0},
			                                  { 0, 0,  0, 1}  }};
						R = multiply(multiply(T1, (a||c)?Ry:I), multiply(Rx, R));
						R = multiply(multiply(R, Rx_INV), multiply((a||c)?Ry_INV:I, T1_INV));			            
			            if(aniFlag) display(R, P); //animate
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else printf("LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -M:Px,Py,Pz,Nx,Ny,Nz\n");
			        break;
			    
			    case 'x': case 'X': //axonometric projection
			    case 'p': case 'P': //perspective projection
				    if(sscanf(argv[i]+2, ":%lf,%lf,%lf,%lf,%lf,%lf", &x, &y, &z, &a, &b, &c)==6)
			                             //camera position vector x, y, z, focus point on projection plane a, b, c
			        {
			        
			            TRANSFORMATION T1 = {{ {  1,  0,  0, 0}, //pass projection plane through origin
			                            	   {  0,  1,  0, 0},
			                              	   {  0,  0,  1, 0},
			                                   { -a, -b, -c, 1}  }};
			            a=x-a; b=y-b; c=z-c; //get normal vector
			            q = sqrt(a*a+c*c); d = sqrt(a*a+b*b+c*c);
			            p = (argv[i][1]=='p' || argv[i][1]=='P') ? (d ? -1/d : 0) : 0;
			            s = a*x+b*y+c*z; //clip co-ordinate axes
			            if(x && s/x>0) //x-axis +infinity behind camera
			            {
			                axes[0].v[0][0]=s/x;
			                axes[0].v[0][3]=1;
			                axes[0].v[1][0]=-1;
			                axes[0].v[1][3]=0;
			            }
			            else if(x && s/x<0) //x-axis -infinity behind camera
			            {
			                axes[0].v[0][0]=1;
			                axes[0].v[0][3]=0;
			                axes[0].v[1][0]=s/x;
			                axes[0].v[1][3]=1;
			            }
			            if(y && s/y>0) //y-axis +infinity behind camera
			            {
			                axes[1].v[0][1]=s/y;
			                axes[1].v[0][3]=1;
			                axes[1].v[1][1]=-1;
			                axes[1].v[1][3]=0;
			            }
			            else if(y && s/y<0) //y-axis -infinity behind camera
			            {
			                axes[1].v[0][1]=1;
			                axes[1].v[0][3]=0;
			                axes[1].v[1][1]=s/y;
			                axes[1].v[1][3]=1;
			            }
			            if(z && s/z>0) //z-axis +infinity behind camera
			            {
			                axes[2].v[0][2]=s/z;
			                axes[2].v[0][3]=1;
			                axes[2].v[1][2]=-1;
			                axes[2].v[1][3]=0;
			            }
			            else if(z && s/z<0) //z-axis -infinity behind camera
			            {
			                axes[2].v[0][2]=1;
			                axes[2].v[0][3]=0;
			                axes[2].v[1][2]=s/z;
			                axes[2].v[1][3]=1;
			            }
			            TRANSFORMATION Ry = {{ {  c, 0, a, 0}, //remove x-component
			                            	   {  0, q, 0, 0},
			                              	   { -a, 0, c, 0},
			                                   {  0, 0, 0, q}  }};

			            TRANSFORMATION Rx = {{ { d,  0, 0, 0}, //remove y-component
			                            	   { 0,  q, b, 0},
			                              	   { 0, -b, q, 0},
			                                   { 0,  0, 0, d}  }};
						
						TRANSFORMATION Pj = {{ { 1, 0, 0, 0}, //project
			                            	   { 0, 1, 0, 0},
			                              	   { 0, 0, 0, p},
			                                   { 0, 0, 0, 1}  }};						
						P = multiply(multiply(T1, (a||c)?Ry:I), multiply(Rx, Pj)); //update projection vector
			            if(aniFlag) display(T, P); //animate
			        }
			        else printf("LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -P/X:Eye_X,Eye_Y,Eye_Z,Ref_X,Ref_Y,Ref_Z\n");
			        break;
			    default:
			        printf("LOG [ERROR] : INVALID OPERATION NOT RECOGINZED : %s\n", argv[i]);
			        break;			    
			}
	}	
	if(!aniFlag)
	{
	    loadObjects(kpg, P); //load object from file
		display(I, P); //display original object
		getchar();
		display(T, P); //display transformed object
	}
	eraseGraph(objects);
	getchar();
	closegraph();
	return 0;
}
