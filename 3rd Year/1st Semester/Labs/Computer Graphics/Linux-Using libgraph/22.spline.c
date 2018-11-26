#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

void gauss(double **mat, int n)
{
    double ratio;
    int i, j, k;
    for(i = 0; i < n; ++i)
        for(j = 0; j < n; ++j)
            if(i!=j)
            {
                ratio = mat[j][i]/mat[i][i];
                for(k = 0; k < 2*n; k++)
                    mat[j][k] -= ratio * mat[i][k];
            }
    for(i = 0; i < n; i++){
        ratio = mat[i][i];
        for(j = 0; j < 2*n; j++)
            mat[i][j] /= ratio;
    }
}

int main(int argc, char **argv)
{
    clock_t last=0, now;
    int n, i, j;
    double  *x, *y, **mat, *ts, *tanx, *tany;
    double t, b1x, b1y, b2x, b2y, b3x, b3y, b4x, b4y;
    double curx, cury, prex, prey;
    int gd=DETECT,gm;
    char choice;
    
    printf("Cubic Spline:\nEnter the number of control points: ");
    scanf("%d", &n);
    x = (double*)malloc(n*sizeof(double));
    y = (double*)malloc(n*sizeof(double));
    ts = (double*)malloc(n*sizeof(double));
    tanx = (double*)malloc(n*sizeof(double));
    tany = (double*)malloc(n*sizeof(double));
    mat = (double**)malloc(n*sizeof(double));
    mat[0] = (double*)malloc(2*n*n*sizeof(double));
    memset(mat[0], 0, 2*n*n*sizeof(double));
    printf("Enter the points: ");
    for(i=0; i<n; ++i) scanf("%lf %lf", x+i, y+i);
    printf("\nUse Normalized Parameters (Y/N)? "); scanf(" %c", &choice);
    if(choice=='n') choice='N';
    for(i=1; i<n; ++i)
        if(choice=='N')
        {
            printf("Enter t[%d]: ", i);
            scanf("%lf", ts+i);
            if(ts[i]<0) ts[i]=-ts[i];
        }
        else ts[i]=1.0;
    for(i=1; i<n-1; ++i)
    {
        mat[i] = mat[0]+2*n*i;
        mat[i][i-1] = ts[i+1];
        mat[i][i] = 2*ts[i+1]+2*ts[i];
        mat[i][i+1] = ts[i];
        tanx[i] = 3/(ts[i]*ts[i+1])*(ts[i]*ts[i]*(x[i+1]-x[i])+ts[i+1]*ts[i+1]*(x[i]-x[i-1]));
        tanx[i] = 3/(ts[i]*ts[i+1])*(ts[i]*ts[i]*(y[i+1]-y[i])+ts[i+1]*ts[i+1]*(y[i]-y[i-1]));
    }
    mat[n-1] = mat[n-2]+2*n;
    printf("Choose spline form:\n1. Clamped\n2. Relaxed\n3. Cyclic\n4. Anti-cyclic\n : ");
    scanf(" %c", &choice);
    switch(choice)
    {
        case '2':
            mat[0][0]=1;
            mat[0][1]=2;
            mat[n-2][n-2]=0.5;
            mat[n-1][n-1]=4;
            tanx[0]=3/2*(x[n-1]-x[n-2])/ts[n-1];
            tany[0]=3/2*(y[n-1]-y[n-2])/ts[n-1];
            tanx[n-1]=6*(x[n-1]-x[n-2])/ts[n-1];
            tany[n-1]=6*(y[n-1]-y[n-2])/ts[n-1];
            break;
        case '3':
            mat[0][0]=2*(1+ts[n-1]/ts[1]);
            mat[0][1]=ts[n-1]/ts[1];
            mat[0][n-2]=1;
            tanx[0]=3*(x[n-1]-x[n-2])/ts[n-1] + 3*ts[n-1]*(x[1]-x[0])/ts[1];
            tany[0]=3*(y[n-1]-y[n-2])/ts[n-1] + 3*ts[n-1]*(y[1]-y[0])/ts[1];
            break;
        case '4':
            mat[0][0]=2*(1+ts[n-1]/ts[1]);
            mat[0][1]=ts[n-1]/ts[1];
            mat[0][n-2]=-1;
            tanx[0]=3*ts[n-1]*(x[1]-x[0])/ts[1] - 3*(x[n-1]-x[n-2])/ts[n-1];
            tany[0]=3*ts[n-1]*(y[1]-y[0])/ts[1] - 3*(y[n-1]-y[n-2])/ts[n-1];
            break;
        default:
            mat[0][0]=1;
            mat[n-1][n-1]=1;
            printf("Enter Direction Ratios at first point : "); scanf("%lf %lf", tanx, tany);
            printf("Enter Direction Ratios at last point : "); scanf("%lf %lf", tanx+n-1, tany+n-1);
    }
    gauss(mat, n);
    for(i=0; i<n; ++i)
    {
        mat[i][0]=0;
        mat[i][1]=0;
        for(j=0; j<n; ++j)
        {
            mat[i][0] += mat[i][n+j]*tanx[j];
            mat[i][1] += mat[i][n+j]*tany[j];
        }
    }
    initgraph(&gd, &gm, NULL); //initialize graphics
    setcolor(WHITE); //draw axes
    bar(0, 0, 640, 480);
    setcolor(LIGHTGRAY);
    line(320, 0, 320, 480);
    line(0, 240, 640, 240);
    setcolor(BLUE);
    for(i=0; i<n-1; ++i)
    {
        b1x = x[i];
        b1y = y[i];
        b2x = mat[i][0];
        b2y = mat[i][1];
        b3x = 3*(x[i+1]-x[i])/(ts[i+1]*ts[i+1]) - 2*mat[i][0]/ts[i+1] - mat[i+1][0]/ts[i+1];
        b3y = 3*(y[i+1]-y[i])/(ts[i+1]*ts[i+1]) - 2*mat[i][1]/ts[i+1] - mat[i+1][1]/ts[i+1];
        b4x = 2*(x[i]-x[i+1])/(ts[i+1]*ts[i+1]) + mat[i][0]/ts[i+1] + mat[i+1][0]/ts[i+1];
        b4x /= ts[i+1];
        b4y = 2*(y[i]-y[i+1])/(ts[i+1]*ts[i+1]) + mat[i][1]/ts[i+1] + mat[i+1][1]/ts[i+1];
        b4y /= ts[i+1];
        prex = x[i];
        prey = y[i];
        for(t=0; t<ts[i+1]; t+=0.1)
        {
            while( ((now=clock()) - last)*1.0/CLOCKS_PER_SEC < 0.1 ); //animate output with delay
            last=now;
            curx = b1x + b2x*t + b3x*t*t + b4x*t*t*t;
            cury = b1y + b2y*t + b3y*t*t + b4y*t*t*t;
            line(320+curx, 240-cury, 320+prex, 240-prey);
            prex = curx;
            prey = cury;
        }
    }
    getchar();
	closegraph();
	free(x);
	free(y);
	free(ts);
	free(tanx);
	free(tany);
	free(mat[0]);
	free(mat);
	return 0;
}
