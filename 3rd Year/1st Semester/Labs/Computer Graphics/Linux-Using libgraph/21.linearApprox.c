#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <math.h>
#define PI 3.1415926

void la_circle(double *x, double *y, int n)
{
    double cx, cy, r, cosd, sind;
    int i;
    printf("\nEnter center of circle : ");
    scanf("%lf %lf", &cx, &cy);
    printf("\nEnter radius of circle : ");
    scanf("%lf", &r);
    x[0]=r; //starting point
    y[0]=0;
    cosd = cos(2*PI/n); //cos(dt)
    sind = sin(2*PI/n); //sin(dt)
    for(i=1; i<n+1; ++i)
    {
        x[i] = x[i-1]*cosd - y[i-1]*sind; //calculate r*cos(t+dt)
        y[i] = x[i-1]*sind + y[i-1]*cosd; //calculate r*sin(t+dt)
        x[i-1] += cx; //move center
        y[i-1] += cy;
    }
    x[n] += cx;
    y[n] += cy;
}

void la_ellipse(double *x, double *y, int n)
{
    double t, cx,   cy,
               a,    b,
              mx,   my,
            cosd, sind;
    int i;
    printf("\nEnter center of ellipse : ");
    scanf("%lf %lf", &cx, &cy);
    printf("\nEnter semi-major axis and semi-minor axis of ellipse : ");
    scanf("%lf %lf", &a, &b);
    printf("\nEnter direction ratio of major axis : ");
    scanf("%lf %lf", &mx, &my);
    x[0]=a; //starting point
    y[0]=0;
    t = pow(mx*mx+my*my, 0.5);
    mx /= t; //normalize to direction cosines
    my /= t;
    cosd = cos(2*PI/n); //cos(dt)
    sind = sin(2*PI/n); //sin(dt)
    for(i=1; i<n+1; ++i)
    {
        x[i] = x[i-1]*cosd - a*y[i-1]*sind/b; //calculate a*cos(t+dt)
        y[i] = b*x[i-1]*sind/a + y[i-1]*cosd; //calculate b*sin(t+dt)
        t = x[i-1]*mx - y[i-1]*my; //rotate to match axis
        y[i-1] = x[i-1]*my + y[i-1]*mx;
        x[i-1] = t;
        x[i-1] += cx; //move center
        y[i-1] += cy;
    }
    t = x[n]*mx - y[n]*my;
    y[n] = x[n]*my + y[n]*mx;
    x[n] = t;
    x[n] += cx;
    y[n] += cy;
}

void la_parabola(double *x, double *y, int n)
{
    double t, cx, cy,
              mx, my,
              t1, t2,
               a, dt;
    int i;
    printf("\nEnter vertex of parabola : ");
    scanf("%lf %lf", &cx, &cy);
    printf("\nEnter focal length of parabola : ");
    scanf("%lf", &a);
    printf("\nEnter direction ratio of axis : ");
    scanf("%lf %lf", &mx, &my);
    printf("\nEnter range of parameter t : ");
    scanf("%lf %lf", &t1, &t2);
    x[0]=a*t1*t1; //starting point
    y[0]=2*a*t1;
    t = pow(mx*mx+my*my, 0.5);
    mx /= t; //normalize to direction cosines
    my /= t;
    dt = (t2-t1)/n; //dt
    for(i=1; i<n+1; ++i)
    {
        x[i] = x[i-1] + y[i-1]*dt + a*dt*dt; //calculate a(t+dt)^2
        y[i] = y[i-1] + 2*a*dt; //calculate 2a(t+dt)
        t = x[i-1]*mx - y[i-1]*my; //rotate to match axis
        y[i-1] = x[i-1]*my + y[i-1]*mx;
        x[i-1] = t;
        x[i-1] += cx; //move vertex
        y[i-1] += cy;
    }
    t = x[n]*mx - y[n]*my;
    y[n] = x[n]*my + y[n]*mx;
    x[n] = t;
    x[n] += cx;
    y[n] += cy;
}

int xc, yc, mirrorFlag=0;

void la_hyperbola(double *x, double *y, int n)
{
    double t, cx,   cy,
               a,    b,
              mx,   my,
            cosd, sind;
    int i;
    printf("\nEnter center of hyperbola : ");
    scanf("%lf %lf", &cx, &cy);
    xc = cx + cx;
    yc = cy + cy;
    mirrorFlag = 1; //hyperbola requires 2 curves to be drawn
    printf("\nEnter transverse axis and conjugate axis of hyperbola : ");
    scanf("%lf %lf", &a, &b);
    printf("\nEnter direction ratio of transverse axis : ");
    scanf("%lf %lf", &mx, &my);
    x[0] = a*cosh(acosh(320/a)); //adaptive starting point, to fit screen
    y[0] = b*sinh(acosh(320/a));
    t = pow(mx*mx+my*my, 0.5);
    mx /= t; //normalize to direction cosines
    my /= t;
    cosd = cosh(2*acosh(320/a)/n); //cosh(dt)
    sind = sinh(2*acosh(320/a)/n); //sinh(dt)
    for(i=1; i<n+1; ++i)
    {
        x[i] = x[i-1]*cosd - a*y[i-1]*sind/b; //calculate a*cosh(t+dt)
        y[i] = y[i-1]*cosd - b*x[i-1]*sind/a; //calculate b*sinh(t+dt)
        t = x[i-1]*mx - y[i-1]*my; //rotate to match axis
        y[i-1] = x[i-1]*my + y[i-1]*mx;
        x[i-1] = t;
        x[i-1] += cx; //move center
        y[i-1] += cy;
    }
    t = x[n]*mx - y[n]*my;
    y[n] = x[n]*my + y[n]*mx;
    x[n] = t;
    x[n] += cx;
    y[n] += cy;
}

int main(int argc, char **argv)
{
    clock_t last=0, now;
    double dely;
    int n, i, ch;
    double  *x, *y;
    int gd=DETECT,gm;
    printf("Linear Approximations:\n1. Circle\n2. Ellipse\n3. Parabola\n4. Hyperbola\n : ");
    scanf("%d", &ch);
    printf("Number of Segments? "); scanf("%d", &n);
    printf("Delay time (in seconds)? "); scanf("%lf", &dely);
    x = (double*)malloc((n+1)*sizeof(double));
    y = (double*)malloc((n+1)*sizeof(double));
    switch(ch) //generate points
    {
        case 1: la_circle(x, y, n); break;
        case 2: la_ellipse(x, y, n); break;
        case 3: la_parabola(x, y, n); break;
        case 4: la_hyperbola(x, y, n); break;
        default: printf("Invalid!"); return 1; break;
    }
    initgraph(&gd, &gm, NULL); //initialize graphics
    setcolor(WHITE); //draw axes
    bar(0, 0, 640, 480);
    setcolor(LIGHTGRAY);
    line(320, 0, 320, 480);
    line(0, 240, 640, 240);
    setcolor(BLUE);    
    for(i=0; i<n; ++i)
    {
        while( ((now=clock()) - last)*1.0/CLOCKS_PER_SEC < dely ); //animate output with delay
        last=now;
        line(320+x[i], 240-y[i], 320+x[i+1], 240-y[i+1]);
        if(mirrorFlag) line(320+xc-x[i], 240-yc+y[i], 320+xc-x[i+1], 240-yc+y[i+1]); //special case for hyperbola only
    }
    getchar();
	closegraph();
	free(x); //free memory
	free(y);
	return 0;
}
