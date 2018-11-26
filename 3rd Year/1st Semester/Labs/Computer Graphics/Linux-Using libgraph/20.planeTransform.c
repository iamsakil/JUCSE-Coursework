/*
*   2D TRANSFORMATIONS
*   provide a .kpg file as input
*  
*   translation -t:x,y
*   rotation    -r:x,y,0
*   shear       -f:x,y
*   reflection  -m:a,b,c
*   scaling     -s:x,y
*   zoom        -z:h
*   custom      -c:a,b,p,c,d,q,m,n,s
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

typedef struct
{
    VSHAPE data;
    char type;
}OBJECT;

OBJECT *objects=NULL;
int aniFlag, num_objs=0;
clock_t last=0, now;
double dely=0;

typedef struct
{
    double v[3][3];
}TRANSFORMATION;

TRANSFORMATION multiply(TRANSFORMATION R, TRANSFORMATION T)
{
    int i, j, k;
    TRANSFORMATION F;
    for(i=0; i<3; ++i)
        for(j=0; j<3; ++j)
        {
            F.v[i][j]=0;
            for(k=0; k<3; ++k)
                F.v[i][j] += R.v[i][k]*T.v[k][j];
        }
    return F;
}

void loadObjects(FILE *kpg)
{
    int gd=DETECT,gm; //initialize graphics
	initgraph(&gd, &gm, NULL);
	setcolor(WHITE);
    bar(0, 0, 640, 480);
    setcolor(LIGHTGRAY); //draw axes
    line(320, 0, 320, 480);
    line(0, 240, 640, 240);
    setcolor(BLACK);
    do
    {
        char tp;
        fscanf(kpg, "%c ", &tp);
        if(tp=='l' || tp=='L') //line
        {
            objects = (OBJECT*)realloc(objects, sizeof(OBJECT)*(num_objs+1));
            objects[num_objs].data = toVector(parseLine(kpg)); //read line from file
            objects[num_objs].type = tp;
            if(objects[num_objs].data) ++num_objs;
            else parseComment(kpg);
        }
        else if(tp=='p' || tp=='P') //polygon
        {
            objects = (OBJECT*)realloc(objects, sizeof(OBJECT)*(num_objs+1));
            objects[num_objs].data = toVector(parsePoly(kpg)); //read polygon from file
            objects[num_objs].type = tp;
            if(objects[num_objs].data) ++num_objs;
            else parseComment(kpg);
        }
        else parseComment(kpg);
    }while(!feof(kpg));
    if(kpg) fclose(kpg);
}
void display(TRANSFORMATION T)
{
    int i;
    VSHAPE cur;
    int j;
    while( ((now=clock()) - last)*1.0/CLOCKS_PER_SEC < dely); //animate output with required delay
    last=now;
    if(aniFlag>0) //animate
    {
        setcolor(WHITE);
        bar(0, 0, 640, 480);
        setcolor(LIGHTGRAY); //draw axes
        line(320, 0, 320, 480);
        line(0, 240, 640, 240);
        setcolor(BLACK);
    }
    else if(!aniFlag) //no animation, show original
    {
        setcolor(RED);
        aniFlag=-1;
    }
    else setcolor(BLUE); //no animation, show transformed object
    for(i=0; i<num_objs; ++i)
    {
        for(cur=objects[i].data; cur!=NULL; cur=cur->next)
        {
            TRANSFORMATION X = {{ {cur->x, cur->y, 1},      //multiply homogeneous
                                  {     0,      0, 0},
                                  {     0,      0, 0}  }};
            X = multiply(X, T);
            cur->x = X.v[0][0]/X.v[0][2];
            cur->y = X.v[0][1]/X.v[0][2];
        }
        if(objects[i].type=='l') //display line
            line(320+objects[i].data->x,
                     240-objects[i].data->y,
                         320+objects[i].data->next->x,
                             240-objects[i].data->next->y);
        else
        {
            VSHAPE pcur, pnxt;      //display polygon
            pcur = objects[i].data;
            do
            {
                VSHAPE pnxt = pcur->next?pcur->next:objects[i].data; //closed polygon, vertex_1 follows vertex_N
                line(320+pcur->x, 240-pcur->y, 320+pnxt->x, 240-pnxt->y);
            }while(pcur=pcur->next);
        }
    }
}

void menu(int *argc, char ***argv)
{
    int choice;
    double x, y, other;
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
            sprintf((*argv)[3], "-s:%lf,%lf", x, y);
            break;
        case 2:
            printf("Enter X Shear Factor : "); scanf("%lf", &x);
            printf("Enter Y Shear Factor : "); scanf("%lf", &y);
            sprintf((*argv)[3], "-f:%lf,%lf", x, y);
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
            sprintf((*argv)[3], "-t:%lf,%lf", x, y);
            break;
        default:
            strcpy((*argv)[3], "");
    }
}

int main(int argc, char **argv)
{
	int steps;
	int cnt, i=1;
    int gd=DETECT,gm;
    FILE *kpg;
    double x, y, angle;
    double a, b, p,
           c, d, q,
           m, n, s;
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
    TRANSFORMATION T = {{ {1, 0, 0},
			              {0, 1, 0},
			              {0, 0, 1} }};
    TRANSFORMATION I = T;
    aniFlag=0;
    if(argc==2) menu(&argc, &argv); //default to menu driven
	while((i++)<argc-1) //parse the arguments
	{
		if(argv[i][0]=='-') //commands start with a '-'
			switch(argv[i][1])
			{
			    case 'a': case 'A': //animation
			        if(sscanf(argv[i]+2, ":%d,%lf", &steps, &dely)==2) //number of steps per operation, time delay per step
			        {
			            aniFlag = 1;
			            loadObjects(kpg); //load from file
			            display(I); //display original
			            getchar();
			            display(T); //display current
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -A:FRAMES/OP,DELAY\n");
			    break;
			    
			    case 't': case 'T': //translation
			        if(sscanf(argv[i]+2, ":%lf,%lf", &x, &y)==2) //along x-axis, along y-axis
			        {
			            TRANSFORMATION R = {{ {1, 0, 0}, //translate
			                                  {0, 1, 0},
			                                  {x, y, 1}  }};
			            if(aniFlag)
			            {
			                R.v[2][0]/=steps; //break into n steps
			                R.v[2][1]/=steps;
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R); //animate
			            }
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -T:X_DISP,Y_DISP\n");
			    break;
			    
			    case 's': case 'S': //scaling
			        if(sscanf(argv[i]+2, ":%lf,%lf", &x, &y)==2) //scale x, scale y
			        {
			            x=x>0?x:-x;
			            y=y>0?y:-y;
			            TRANSFORMATION R = {{ {x, 0, 0}, //scale
			                                  {0, y, 0},
			                                  {0, 0, 1}  }};
			            if(aniFlag)
			            {
			                R.v[0][0] = pow(R.v[0][0], 1.0/steps); //break into n steps
			                R.v[1][1] = pow(R.v[1][1], 1.0/steps);
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R); //animate
			            }
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -S:X_SCALE,Y_SCALE\n");
			    break;
			    
			    case 'r': case 'R': //rotation
			        if(sscanf(argv[i]+2, ":%lf,%lf,%lf", &x, &y, &angle)==3) //center of rotation x, y, angle of rotation
			        {
			            angle*=3.1415926/180;
			            TRANSFORMATION R = {{ { 1,  0, 0}, //pass axis of rotation through origin
			                                  { 0,  1, 0},
			                                  {-x, -y, 1}  }};
			            TRANSFORMATION R_INV = {{ {1, 0, 0},
			                                      {0, 1, 0},
			                                      {x, y, 1}  }};
			            if(aniFlag) angle/=steps; //break into n steps
			            c=cos(angle);
			            s=sin(angle);
			            TRANSFORMATION W = {{ { c, s, 0}, //rotate
			                                  {-s, c, 0},
			                                  { 0, 0, 1}  }};
			            R = multiply(R, multiply(W, R_INV)); //calculate effective transformation matrix
			            if(aniFlag)
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R); //animate
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -R:X_CEN,Y_CEN,ANGLE\n");
			    break;

			    case 'f': case 'F': //shearing
			        if(sscanf(argv[i]+2, ":%lf,%lf", &x, &y)==2) //x shear, y shear
			        {
			            TRANSFORMATION R = {{ {1, y, 0}, //shear
			                                  {x, 1, 0},
			                                  {0, 0, 1}  }};
			            if(aniFlag)
			            {
			                R.v[0][1] = y/steps;
			                R.v[1][0] = 0;
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R); //animate shear along y-axis
			                R.v[1][0] = x/steps;
			                R.v[0][1] = 0;
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R); //animate shear along x-axis
			                R.v[1][0]=x*x*y;
			                R.v[0][1]=0;
			                R.v[0][0]=1-x*y;
			                display(R); //correction term
			            }
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -F:X_SHEAR,Y_SHEAR\n");
			    break;

			    case 'z': case 'Z': //zooming
			        if(sscanf(argv[i]+2, ":%lf", &s)==1) //homogeneous zoom factor
			        {
			            if(s==0.0)
			            {
			                fprintf(stderr, "LOG [ERROR] : CANNOT DELETE PICTURE!");
			                break;
			            }
			            TRANSFORMATION R = {{ {1, 0,   0}, //homogeneous scaling
			                                  {0, 1,   0},
			                                  {0, 0, 1/s}  }};
			            if(s<0) //cannot animate reflection, correction term
			            {
			                R.v[0][0]=-R.v[0][0];
			                R.v[1][1]=-R.v[1][1];
			                R.v[2][2]=-R.v[2][2];
			            }
			            if(aniFlag)
			            {
			                R.v[2][2] = pow(R.v[2][2], 1.0/steps); //break into n steps
			                for(cnt=0; cnt<steps; ++cnt)
			                    display(R); //animate
			            }
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -Z:ZOOM\n");
			    break;

			    case 'm': case 'M': //reflection
			        if(sscanf(argv[i]+2, ":%lf,%lf,%lf", &a, &b, &c)==3) //equation of mirror line
			        {
			            if(b)
			            {
			                x = -a/b; //slope
			                y = -c/b; //intercept
			            }
			            c = pow(1/(x*x + 1), 0.5); //calculate cos and sin from tan
			            s = (x>0?1:-1)*pow(1-c*c, 0.5);
			            TRANSFORMATION R = {{ {1, 0, 0}, //pass mirror line through origin
			                                  {0, 1, 0},
			                                  {0, y, 1}  }};
			            
			            TRANSFORMATION R_INV = {{ {1,  0, 0},
			                                      {0,  1, 0},
			                                      {0, -y, 1}  }};
			            
			            TRANSFORMATION H = {{ { c, -s, 0}, //remove y component
			                                  { s,  c, 0},
			                                  { 0,  0, 1}  }};
			                                  
			            TRANSFORMATION H_INV = {{ { c, s, 0},
			                                      {-s, c, 0},
			                                      { 0, 0, 1}  }};
			            
			            TRANSFORMATION M = {{ {1,  0, 0},
			                                  {0, -1, 0},
			                                  {0,  0, 1}  }};
			            if(!b) //special case mirror is vertical
			            {
			                M.v[0][0]=-1;
			                M.v[1][1]=1;
			            }
			            R = multiply( b?multiply(R, H):I, multiply(M, b?multiply(H_INV, R_INV):I ) ); //calculate effective transformation matrix
			            if(aniFlag) display(R); //cannot animate reflection, show immediately
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID LINE ax+by+c=0. PLEASE USE WITH NO SPACES : -M:a,b,c\n");
			    break;
			    
			    case 'c': case 'C': //custom homogeneous matrix
			        if(sscanf(argv[i]+2, ":%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &a, &b, &p, &c, &d, &q, &m, &n, &s)==9)
			        {
			            TRANSFORMATION R = {{ {a, b, p},
			                                  {c, d, q},
			                                  {m, n, s}  }};
			            if(aniFlag) display(R); //cannot animate, show immediately
			            else T = multiply(T, R); //update transformation matrix
			        }
			        else fprintf(stderr, "LOG [ERROR] : INVALID SYNTAX. PLEASE USE WITH NO SPACES : -C:\n");
			    break;
			    
			    default:
			        fprintf(stderr, "LOG [ERROR] : INVALID OPERATION NOT RECOGINZED : %s\n", argv[i]);
			    break;
			    
			}
	}
	
	if(!aniFlag)
	{
	    loadObjects(kpg); //load from file
		display(I); //display original object
		getchar();
	    display(T); //display transformed object
	}
	for(i=0; i<num_objs; ++i) eraseVector(objects[i].data); //clear memory
	getchar();
	closegraph();
	return 0;
}
