/*
*
* FORMAT FOR .kpg (KANTI PANDEY GRAPHICS) FILES
*
* FORMAT IS NOT CASE SENSITIVE
*
* # ...                   => COMMENT (BEGINNING OF LINE)
* L X1 Y1 X2 Y2           => DEFINES A LINE
* P N X1 Y1 X2 Y2 ...     => DEFINES A POLYGON WITH N VERTICES (INPUT IN CLOCKWISE ORDER)
* S X Y                   => DEFINES A SEED POINT
* C X Y R                 => DEFINES A CIRCLE
* E X Y A B               => DEFINES AN ORTHOGONAL ELLIPSE
*
* G N X1 Y1 Z1            => DEFINES A 3D OBJECT GRAPH
*     X2 Y2 Z2               (INPUT AS VERTICES AND ADJACENCY MATRIX)
*     .
*     .
*     .
*     A11 A12 A13 ...
*     A21 A22 A23 ...
*     .
*     .
*     .
*
*/
#ifndef Soumya_Kanti_Naskar_001410501044_and_Sahil_Pandey_001410501057_Graphics_Format
#define Soumya_Kanti_Naskar_001410501044_and_Sahil_Pandey_001410501057_Graphics_Format
#include <stdio.h>
#include <stdlib.h>

struct point
{
    int x, y;
    struct point *next;
};

typedef struct point *SHAPE;

void erase(SHAPE shape)
{
    SHAPE temp;
    while(shape)
    {
        temp=shape;
        shape=shape->next;
        free(temp);
    }
}

SHAPE parseComment(FILE* kpg)
{
    char c;
    while((c=fgetc(kpg))!='\n');
    return NULL;
}

SHAPE parseLine(FILE *kpg)
{
    SHAPE v1=(SHAPE)malloc(sizeof(struct point));
    SHAPE v2=(SHAPE)malloc(sizeof(struct point));
    if(fscanf(kpg, "%d %d %d %d ", &(v1->x), &(v1->y), &(v2->x), &(v2->y))!=4)
    {
        free(v1);
        free(v2);
        return NULL;
    }
    v1->next=v2;
    v2->next=NULL;
    return v1;
}

SHAPE parsePoly(FILE *kpg)
{
    int n, i;
    SHAPE pre=NULL;
    fscanf(kpg, "%d ", &n);
    for(i=0; i<n; ++i)
    {
        SHAPE v=(SHAPE)malloc(sizeof(struct point));
        if(fscanf(kpg, "%d %d ", &(v->x), &(v->y))!=2)
        {
            erase(pre);
            free(v);
            return NULL;
        }
        v->next=pre;
        pre=v;
    }
    return pre;
}

SHAPE parseSeed(FILE *kpg)
{
    SHAPE v=(SHAPE)malloc(sizeof(struct point));
    if(fscanf(kpg, "%d %d ", &(v->x), &(v->y))!=2)
    {
        free(v);
        return NULL;
    }
    v->next=NULL;
    return v;
}

SHAPE parseCircle(FILE *kpg)
{
    SHAPE c=(SHAPE)malloc(sizeof(struct point));
    SHAPE r=(SHAPE)malloc(sizeof(struct point));
    if(fscanf(kpg, "%d %d %d ", &(c->x), &(c->y), &(r->x))!=3)
    {
        free(c);
        free(r);
        return NULL;
    }
    r->y=r->x;
    c->next=r;
    r->next=NULL;
    return c;
}

SHAPE parseEllipse(FILE *kpg)
{
    SHAPE c=(SHAPE)malloc(sizeof(struct point));
    SHAPE r=(SHAPE)malloc(sizeof(struct point));
    if(fscanf(kpg, "%d %d %d %d ", &(c->x), &(c->y), &(r->x), &(r->y))!=4)
    {
        free(c);
        free(r);
        return NULL;
    }
    c->next=r;
    r->next=NULL;
    return c;
}

SHAPE expectLine(FILE *kpg)
{
    char c;
    fscanf(kpg, "%c ", &c);
    if(c=='l' || c=='L')
        return parseLine(kpg);
    else if(c=='#')
    {
        parseComment(kpg);
        return expectLine(kpg);
    }
    else return NULL;        
}

SHAPE expectPoly(FILE *kpg)
{
    char c;
    fscanf(kpg, "%c ", &c);
    if(c=='p' || c=='P')
        return parsePoly(kpg);
    else if(c=='#')
    {
        parseComment(kpg);
        return expectPoly(kpg);
    }
    else return NULL;
}

SHAPE expectSeed(FILE *kpg)
{
    char c;
    fscanf(kpg, "%c ", &c);
    if(c=='s' || c=='S')
        return parseSeed(kpg);
    else if(c=='#')
    {
        parseComment(kpg);
        return expectSeed(kpg);
    }
    else return NULL;
}

SHAPE expectCircle(FILE *kpg)
{
    char c;
    fscanf(kpg, "%c ", &c);
    if(c=='c' || c=='C')
        return parseCircle(kpg);
    else if(c=='#')
    {
        parseComment(kpg);
        return expectCircle(kpg);
    }
    else return NULL;        
}

SHAPE expectEllipse(FILE *kpg)
{
    char c;
    fscanf(kpg, "%c ", &c);
    if(c=='e' || c=='E')
        return parseEllipse(kpg);
    else if(c=='#')
    {
        parseComment(kpg);
        return expectEllipse(kpg);
    }
    else return NULL;        
}

struct vpoint //2d points
{
    double x, y;
    struct vpoint *next;
};

typedef struct vpoint *VSHAPE;

VSHAPE toVector(SHAPE s)
{
    SHAPE t;
    VSHAPE v=NULL;
    for(t=s; t; t=t->next)
    {
        VSHAPE m = (VSHAPE)malloc(sizeof(struct vpoint));
        m->x=t->x;
        m->y=t->y;
        m->next=v;
        v=m;
    }
    erase(t);
    return v;
}

void eraseVector(VSHAPE shape)
{
    VSHAPE temp;
    while(shape)
    {
        temp=shape;
        shape=shape->next;
        free(temp);
    }
}

typedef struct vgraph //3d object
{
    int n, **adj;
    double **vertices;
}VGRAPH;

void eraseGraph(VGRAPH shape)
{
    free(shape.vertices[0]);
    free(shape.vertices);
    free(shape.adj[0]);
    free(shape.adj);
}

VGRAPH parseGraph(FILE *kpg)
{
    VGRAPH graph;
    int i, j;
    if(fscanf(kpg, "%d ", &graph.n)!=1)
    {
        graph.n=0;
        return graph;
    }
    graph.vertices = (double**)malloc(graph.n*sizeof(double*));
    graph.vertices[0] = (double*)malloc(graph.n*3*sizeof(double));
    for(i=0; i<graph.n; ++i)
    {
        graph.vertices[i] = graph.vertices[0] + 3*i;
        if(fscanf(kpg, "%lf %lf %lf", &graph.vertices[i][0], &graph.vertices[i][1], &graph.vertices[i][2])!=3)
        {
            free(graph.vertices[0]);
            free(graph.vertices);
            graph.n=0;
            return graph;
        }
    }
    graph.adj = (int**)malloc(graph.n*sizeof(int*));
    graph.adj[0] = (int*)malloc(graph.n*graph.n*sizeof(int));
    for(i=0; i<graph.n; ++i)
    {
        graph.adj[i] = graph.adj[0] + graph.n*i;
        for(j=0; j<graph.n; ++j)
            if(fscanf(kpg, "%d ", &graph.adj[i][j])!=1)
            {
                free(graph.vertices[0]);
                free(graph.vertices);
                free(graph.adj[0]);
                free(graph.adj);
                graph.n=0;
                return graph;
            }
    }
    return graph;
}

VGRAPH expectGraph(FILE *kpg)
{
    char c;
    fscanf(kpg, "%c ", &c);
    if(c=='g' || c=='G')
        return parseGraph(kpg);
    else if(c=='#')
    {
        parseComment(kpg);
        return expectGraph(kpg);
    }
    else
    {
        VGRAPH g;
        g.n=0;
        return g;
    }
}

#endif
