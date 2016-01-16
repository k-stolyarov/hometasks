#ifndef __STRUCTURES_H_INCLUDED__
#define __STRUCTURES_H_INCLUDED__

typedef struct LineStruct Line;
typedef struct VertexStruct Vertex;
typedef struct EdgeStruct Edge;

struct LineStruct
{
    int pointA;
    int pointB;
    int pointC;
    int orientation;
    Line* next;
};

struct VertexStruct
{
    Line *a;
    Line *b;
    int X;
    int Y;
    Vertex *next;
    Edge *edges;
    int edgeCount;
};

struct EdgeStruct
{
    Vertex *dst;
    Vertex *src;
    Edge *next;
    float weight;
    int included;
};

#endif // #ifndef __STRUCTURES_H_INCLUDED__